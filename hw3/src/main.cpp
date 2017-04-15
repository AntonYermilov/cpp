#include <iostream>
#include <cstring>
#include <string>

#include "huffman.h"

using std::cout;
using std::cerr;
using std::string;

bool parseArguments(int pos, char** argv, int& type_id, int& fin_id, int& fout_id) {
    if (pos > 6)
        return false;
    if (pos == 6)
        return true;
    if (strcmp(argv[pos], "-c") == 0 || strcmp(argv[pos], "-u") == 0) {
        type_id = pos;
        return parseArguments(pos + 1, argv, type_id, fin_id, fout_id);
    }
    if (strcmp(argv[pos], "-f") == 0 || strcmp(argv[pos], "--file") == 0) {
        fin_id = pos + 1;
        return parseArguments(pos + 2, argv, type_id, fin_id, fout_id);
    }
    if (strcmp(argv[pos], "-o") == 0 || strcmp(argv[pos], "--output") == 0) {
        fout_id = pos + 1;
        return parseArguments(pos + 2, argv, type_id, fin_id, fout_id);
    }
    return false;
}

void typeHelp() {
    cout << "NAME\n";
    cout << "    huffman - create new archive or unpack existed one\n\n";
    cout << "DESCRIPTION\n";
    cout << "    -c    create new archive\n\n";
    cout << "    -u    unpack archive\n\n";
    cout << "    -f, --file <path>\n";
    cout << "          input file name\n\n";
    cout << "    -o, --output <path>\n";
    cout << "          output file name\n\n";
    cout << "    -h, --help\n";
    cout << "          display this help and exit\n\n";
    cout.flush();
    exit(0);
}

void typeParseError() {
    cerr << "Invalid arguments, please type '-h' or '--help' for more information\n";
    exit(1);
}

int main(int argc, char** argv) {
    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
        typeHelp();
    if (argc != 6)
        typeParseError();
    
    int type_id = -1, fin_id = -1, fout_id = -1;
    parseArguments(1, argv, type_id, fin_id, fout_id);
    if (type_id == -1 || fin_id == -1 || fout_id == -1)
        typeParseError();

    string type = string(argv[type_id]);
    string fin = string(argv[fin_id]);
    string fout = string(argv[fout_id]);

    
    Archiver archive;
    if (type == "-c") {
        archive.createArchive(fin, fout);
    } else {
        archive.unpackArchive(fin, fout);
    }
    

    return 0;
}
