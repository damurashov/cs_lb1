#include "print_ops.h"
#include "arg_handler.h"
#include <iostream>
#include <list>
#include <string>

using namespace std;

Ciphertext* p_ciphertext;
Vocabulary* p_vocabulary;
Key*        p_key;

int main(int argc, char* argv[]) {
    string args;
    p_key = new Key();
    
    system("chcp 1251 & cls");
    //system("chcp 65001 & cls");

    switch (argc) {
    case 1:
        print_general_help();
        return 0;
    case 3:
        p_ciphertext = new Ciphertext(argv[1]);
        p_vocabulary = new Vocabulary(argv[2]);
        break;
    default:
        print_general_help();
        return 0;
    }

    cout << ">>";
    while (getline(cin, args)) {
        //getline(cin, args);
        if (!args.empty()) {
            if (split_args(args).front() == "exit") {
                delete p_ciphertext;
                delete p_vocabulary;
                delete p_key;
                return 0;
            }
            handle_args(args);
        }
        
        cout << endl << ">>";
    }
    
    return 0;
}