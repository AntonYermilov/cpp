#ifndef __HUFFMAN_H
#define __HUFFMAN_H

#include <fstream>
#include <string>
#include <map>

class Archiver {
  public:
    void createArchive(const std::string& in, const std::string& out) const;
    void unpackArchive(const std::string& in, const std::string& out) const;

  private:
    class BinaryTrie {
      public:
        BinaryTrie();
        BinaryTrie(const std::map<char, int>& frequency);
        ~BinaryTrie();

        class Node {
            friend class BinaryTrie;
          
          public:
            Node();

            Node* moveDown(int edge) const;
            bool canMoveDown(int edge) const;
            Node* moveUp() const;
            bool canMoveUp() const;

            bool isLeaf() const;
            bool isRoot() const;
            char getValue() const;

            bool operator<(const Node& other) const;

          private:
            Node(char value, Node* left, Node* right, Node* parent);
            int getNextId() const;

            char _value;
            Node* _left;
            Node* _right;
            Node* _parent;
            int _id;
        };

        bool exists(char symbol) const;
        Node* getNode(char symbol);
        Node* getRoot();

      private:
        BinaryTrie(const BinaryTrie& trie);
        BinaryTrie operator=(const BinaryTrie& trie);

        Node* _root;
        std::map<char, Node*> _pos;
    };

    void putTable(std::ofstream& fout, const std::map<char, int>& frequency) const;
    void putBit(std::ofstream& fout, int bit, bool flush) const;
    void putCode(std::ofstream& fout, BinaryTrie::Node* node) const;
    
    void readTable(std::ifstream& fin, std::map<char, int>& frequency) const;
};

#endif
