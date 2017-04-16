#ifndef __HUFFMAN_H
#define __HUFFMAN_H

#include <fstream>
#include <exception>
#include <string>
#include <map>

class DecodingException : public std::exception {
public:
    const char* what() const throw();
};

class Archiver {
  public:
    Archiver();

    void printStatistics() const;

    void createArchive(std::ifstream& fin, std::ofstream& fout);
    void unpackArchive(std::ifstream& fin, std::ofstream& fout);

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

    void putTable(std::ofstream& fout, const std::map<char, int>& frequency);
    void putBit(std::ofstream& fout, int bit, bool flush);
    void putCode(std::ofstream& fout, BinaryTrie::Node* node);
    
    void readTable(std::ifstream& fin, std::map<char, int>& frequency);

    int _before_size;
    int _after_size;
    int _table_size;
};

#endif
