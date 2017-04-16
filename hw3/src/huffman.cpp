#include <iostream>
#include <fstream>
#include <cstddef>
#include <set>

#include "huffman.h"

const char* DecodingException::what() const throw() {
    return "Error when unpacking archive occurred";
}

Archiver::Archiver() : 
        _before_size(0), _after_size(0), _table_size(0) {
}

void Archiver::printStatistics() const {
    std::cout << _before_size << '\n' << _after_size << '\n' << _table_size << '\n';
    std::cout.flush();
}

void Archiver::createArchive(std::ifstream& fin, std::ofstream& fout) {
    fin.seekg(0, fin.end);
    int length = _before_size = fin.tellg();
    fin.seekg(0, fin.beg);

    std::map<char, int> frequency;
    for (int i = 0; i < length; i++) {
        char symbol;
        fin.get(symbol);
        frequency[symbol]++;
    }
    BinaryTrie trie(frequency);

    putTable(fout, frequency);
    fout.write((char*) &length, 4);
    _table_size += 4;

    fin.seekg(0, fin.beg);
    for (int i = 0; i < length; i++) {
        char symbol;
        fin.get(symbol);
        putCode(fout, trie.getNode(symbol));
    }
    putBit(fout, 0, true);

    printStatistics();
}

void Archiver::unpackArchive(std::ifstream& fin, std::ofstream& fout) {
    std::map<char, int> frequency;
    readTable(fin, frequency);
    BinaryTrie trie(frequency);
    BinaryTrie::Node* node = trie.getRoot();

    int length;
    fin.read((char*) &length, 4);
    _table_size += 4;

    char byte;
    while (length) {
        if (!fin.good())
            throw DecodingException();
        _before_size++;
        fin.read(&byte, 1);
        for (int i = 0; i < 8 && length; i++) {
            int bit = (byte & (1 << i)) > 0;
            if (!node->canMoveDown(bit) && !node->isLeaf())
                throw DecodingException();
            if (!node->canMoveDown(bit))
                node = trie.getRoot();
            node = node->moveDown(bit);
            if (node->isLeaf()) {
                fout.put(node->getValue());
                _after_size++;
                length--;
            }
        }
    }

    printStatistics();
}

void Archiver::putTable(std::ofstream& fout, const std::map<char, int>& frequency) {
    int size = frequency.size();
    fout.write((char*) &size, 4);
    for (auto& symbol : frequency) {
        fout.write(&symbol.first, 1);
        fout.write((char*) &symbol.second, 4);
    }
    _table_size += size * 5 + 4;
}

void Archiver::putBit(std::ofstream& fout, int bit, bool flush) {
    static char buff = 0;
    static int cur_pos = 0;

    if (flush) {
        if (cur_pos) {
            fout.write(&buff, 1);
            _after_size++;
        }
        return;
    }

    buff |= bit << cur_pos;
    cur_pos = (cur_pos + 1) & 7;
    if (!cur_pos) {
        fout.write(&buff, 1);
        _after_size++;
        buff = 0;
    }
}

void Archiver::putCode(std::ofstream& fout, BinaryTrie::Node* node) {
    if (!node->canMoveUp())
        return;
    putCode(fout, node->moveUp());
    putBit(fout, node->moveUp()->moveDown(0) == node ? 0 : 1, false);
}

void Archiver::readTable(std::ifstream& fin, std::map<char, int>& frequency) {
    int size;
    fin.read((char*) &size, 4);
    for (int i = 0; i < size; i++) {
        char symbol;
        fin.read(&symbol, 1);
        int count;
        fin.read((char*) &count, 4);
        frequency[symbol] = count;
    }
    _table_size = size * 5 + 4;
}

Archiver::BinaryTrie::BinaryTrie() {
    _root = new Node();
}

Archiver::BinaryTrie::BinaryTrie(const std::map<char, int>& frequency) {
    auto compare = [](const std::pair<int, Node*>& o1, const std::pair<int, Node*>& o2)->bool {
        if (o1.first != o2.first)
            return o1.first < o2.first;
        return *o1.second < *o2.second;
    };

    std::set<std::pair<int, Node*>, decltype(compare)> storage(compare);
    for (auto& symbol : frequency) {
        Node* node = new Node(symbol.first, NULL, NULL, NULL);
        _pos[node->_value] = node;
        storage.insert(std::make_pair(symbol.second, node));
    }
    
    if (storage.empty()) {
        _root = new Node();
        return;
    }
    if (storage.size() == 1) {
        _root = new Node();
        _root->_left = storage.begin()->second;
        _root->_left->_parent = _root;
        return;
    }

    while (storage.size() > 1) {
        std::pair<int, Node*> l = *storage.begin();
        storage.erase(storage.begin());
        std::pair<int, Node*> r = *storage.begin();
        storage.erase(storage.begin());
        Node* node = new Node(0, l.second, r.second, NULL);
        storage.insert(std::make_pair(l.first + r.first, node));
    }
    _root = storage.begin()->second;
}

Archiver::BinaryTrie::~BinaryTrie() {
    Node* node = _root;
    while (true) {
        if (node->canMoveDown(0)) {
            node = node->moveDown(0);
            continue;
        }
        if (node->canMoveDown(1)) {
            node = node->moveDown(1);
            continue;
        }
        if (!node->canMoveUp())
            break;
        Node* par = node->moveUp();
        node == par->moveDown(0) ? par->_left = NULL : par->_right = NULL;
        delete node;
        node = par;
    }
    delete _root;
}

bool Archiver::BinaryTrie::exists(char symbol) const {
    return _pos.find(symbol) != _pos.end();
}

Archiver::BinaryTrie::Node* Archiver::BinaryTrie::getNode(char symbol) {
    return _pos[symbol];
}

Archiver::BinaryTrie::Node* Archiver::BinaryTrie::getRoot() {
    return _root;
}

Archiver::BinaryTrie::Node::Node() :
        _value(0), _left(NULL), _right(NULL), _parent(NULL) {
    _id = getNextId();
}

Archiver::BinaryTrie::Node::Node(char value, Node* left, Node* right, Node* parent) :
        _value(value), _left(left), _right(right), _parent(parent) {
    if (_left != NULL)
        _left->_parent = this;
    if (_right != NULL)
        _right->_parent = this;
    _id = getNextId();
}

int Archiver::BinaryTrie::Node::getNextId() const {
    static int GLOBAL_ID = 0;
    return GLOBAL_ID++;
}

Archiver::BinaryTrie::Node* Archiver::BinaryTrie::Node::moveDown(int edge) const {
    return edge == 0 ? _left : _right;
}

bool Archiver::BinaryTrie::Node::canMoveDown(int edge) const {
    return edge == 0 ? _left != NULL : _right != NULL;
}

Archiver::BinaryTrie::Node* Archiver::BinaryTrie::Node::moveUp() const {
    return _parent;
}

bool Archiver::BinaryTrie::Node::canMoveUp() const {
    return _parent != NULL;
}

bool Archiver::BinaryTrie::Node::isLeaf() const {
    return _left == NULL && _right == NULL;
}

bool Archiver::BinaryTrie::Node::isRoot() const {
    return _parent == NULL;
}

char Archiver::BinaryTrie::Node::getValue() const {
    return _value;
}

bool Archiver::BinaryTrie::Node::operator<(const Node& other) const {
    return _id < other._id;
}
