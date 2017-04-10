#include "matrix.h"
#include <iostream>
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

size_t getRegister(const string& reg) {
    return reg[1] - '0';
}

int main() {
    Matrix reg[10];
    string cmd;

    while (true) {
        cin >> cmd;
        if (cmd == "exit")
            break;
        if (cmd == "load") {
            string reg_id, name;
            cin >> reg_id >> name;
            ifstream in(name);
            in >> reg[getRegister(reg_id)];
            in.close();
        }
        if (cmd == "print") {
            string reg_id;
            cin >> reg_id;
            cout << reg[getRegister(reg_id)];
        }
        if (cmd == "elem") {
            string reg_id;
            int i, j;
            cin >> reg_id >> i >> j;
            try {
                int elem = reg[getRegister(reg_id)].get(i, j);
                cout << elem << endl;
            } catch (MatrixException &e) {
                cout << e.get() << endl;
            }
        }
        if (cmd == "add") {
            string reg1_id, reg2_id;
            cin >> reg1_id >> reg2_id;
            try {
                reg[getRegister(reg1_id)] += reg[getRegister(reg2_id)];
            } catch (MatrixException &e) {
                cout << e.get() << endl;
            }
        }
        if (cmd == "mul") {
            string reg1_id, reg2_id;
            cin >> reg1_id >> reg2_id;
            try {
                reg[getRegister(reg1_id)] *= reg[getRegister(reg2_id)];
            } catch (MatrixException &e) {
                cout << e.get() << endl;
            }
        }
    }
    return 0;
}
