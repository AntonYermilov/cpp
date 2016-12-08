#pragma once

#include "figure.h"

class Scheme {
  public:
    Scheme(int capacity); 
    ~Scheme();

    void push_back_figure(Figure* fg);
    void remove_figure(int id); // элементы смещаются влево

    void print_all_figures() const;
    void zoom_figure(int id, int factor) const;
    Figure* is_inside_figure(int x, int y) const; // если внутри нескольких фигур, то возвращается любая из них
    void move(int id, int new_x, int new_y) const;

  private:
    Scheme(const Scheme &sc);
    Scheme& operator=(const Scheme &sc);

    int find_pos(int id) const;

    int _sz;
    Figure** _figures; // размер массива задается в конструкторе и больше не растет
};
