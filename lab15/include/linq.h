#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename P>
class where_enumerator;
template<typename T, typename F>
class until_enumerator;
template<typename T>
class take_enumerator;

template<typename T>
class enumerator {
  public:
    virtual const T& operator*() = 0;
    virtual enumerator& operator++() = 0;
    virtual operator bool() const = 0;

    auto drop(int count) {
        return drop_enumerator<T>(*this, count);
    }

    template<typename U = T, typename F>
    auto select(F func) {
        return select_enumerator<U, T, F>(*this, func);
    }

    template <typename P>
    auto where(P pred) {
       return where_enumerator<T, P>(*this, pred);
    }
    
    auto where_neq(const T& o1) {
        auto pred = [o1](const T& o2) {
            return o1 != o2;
        };
        return where(pred);
    }

    template<typename P>
    auto until(P pred) {
        return until_enumerator<T, P>(*this, pred);
    }

    auto until_eq(const T& o1) {
        auto pred = [o1](const T& o2) {
            return o1 == o2;
        };
        return until(pred);
    }

    auto take(int count) {
        return take_enumerator<T>(*this, count);
    }

    std::vector<T> to_vector() {
        std::vector<T> result;
        while (*this) {
            result.push_back(**this);
            ++*this;
        }
        return result;
    }

    template<typename Iter>
    void copy_to(Iter it) {
        while (*this) {
            *it = **this;
            ++it;
            ++*this;
        }
    }
};


template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
  public:
    range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {
    }
    
    const T& operator*() {
        return *begin_;
    }
    range_enumerator& operator++() {
        begin_++;
        return *this;
    }
    operator bool() const {
        return begin_ != end_;
    }

  private:
    Iter begin_, end_;
};


template<typename Iter>
auto from(Iter begin, Iter end) {
    return range_enumerator<typename std::iterator_traits<Iter>::value_type, Iter>(begin, end);
}


template<typename T>
class drop_enumerator : public enumerator<T> {
  public:
    drop_enumerator(enumerator<T>& parent, int count) : parent_(parent) {
        while(parent_ && count > 0) {
            ++parent_;
            count--;
        }
    }

    const T& operator*() {
        return *parent_;
    }
    drop_enumerator& operator++() {
        ++parent_;
        return *this;
    }
    operator bool() const {
        return parent_;
    }

  private:
    enumerator<T>& parent_;
};


template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
  public:
    select_enumerator(enumerator<U>& parent, F func) : parent_(parent), func_(func) {
    }

    const T& operator*() {
        return last_ = func_(*parent_);
    }
    select_enumerator& operator++() {
        ++parent_;
        return *this;
    }
    operator bool() const {
        return parent_;
    }

  private:
    T last_;
    enumerator<U>& parent_;
    F func_;
};


template<typename T, typename P>
class where_enumerator : public enumerator<T> {
  public:
    where_enumerator(enumerator<T>& parent, P pred) : parent_(parent), pred_(pred) {
    }

    const T& operator*() {
        return *parent_;
    }
    where_enumerator& operator++() {
        ++parent_;
        return *this;
    }
    operator bool() const {
        while (parent_ && !pred_(*parent_))
            ++parent_;
        return parent_ && pred_(*parent_);
    }

  private:
    enumerator<T>& parent_;
    P pred_;
};


template<typename T, typename P>
class until_enumerator : public enumerator<T> {
  public:
    until_enumerator(enumerator<T>& parent, P pred) : parent_(parent), pred_(pred) {
    }

    const T& operator*() {
        return *parent_;
    }
    until_enumerator& operator++() {
        ++parent_;
        return *this;
    }
    operator bool() const {
        return parent_ && !pred_(*parent_);
    }

  private:
    enumerator<T>& parent_;
    P pred_;
};

template<typename T>
class take_enumerator : public enumerator<T> {
  public:
    take_enumerator(enumerator<T>& parent, int count) : parent_(parent), count_(count) {
    }

    const T& operator*() {
        return *parent_;
    }
    take_enumerator& operator++() {
        ++parent_;
        --count_;
        return *this;
    }
    operator bool() const {
        return parent_ && count_ > 0;
    }

  private:
    enumerator<T>& parent_;
    int count_;
};

#endif
