#include "scheme.h"
#include <cstddef>

Scheme::Scheme(int capacity) {
    _sz = 0;
    _figures = new Figure*[capacity];
}

Scheme::~Scheme() {
    for (int i = 0; i < _sz; i++)
        delete _figures[i];
    delete []_figures;
}

void Scheme::push_back_figure(Figure* fg) {
    _figures[_sz++] = fg;
}

void Scheme::remove_figure(int id) {
    int pos = find_pos(id);
    if (pos == _sz)
        return;

    delete _figures[pos];
    _sz--;
    while (pos < _sz) {
        _figures[pos] = _figures[pos + 1];
        pos++;
    }
}

void Scheme::print_all_figures() const {
    for (int i = 0; i < _sz; i++)
        _figures[i]->print();
}

void Scheme::zoom_figure(int id, int factor) const {
    int pos = find_pos(id);
    if (pos == _sz)
        return;

    _figures[pos]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) const {
    for (int i = 0; i < _sz; i++)
        if (_figures[i]->is_inside(x, y))
            return _figures[i];
    return NULL;
}

void Scheme::move(int id, int new_x, int new_y) const {
    int pos = find_pos(id);
    if (pos == _sz)
        return;

    _figures[pos]->move(new_x, new_y);
}

int Scheme::find_pos(int id) const {
    int pos = 0;
    while (pos < _sz && _figures[pos]->get_id() != id)
        pos++;
    return pos;
}
