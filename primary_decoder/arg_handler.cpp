#include "arg_handler.h"

using namespace std;

extern Vocabulary*  p_vocabulary;   /* main.cpp */
extern Ciphertext*  p_ciphertext;   /* main.cpp */
extern Key*         p_key;          /* main.cpp */

static void         handle      (int argc, const list<string>& arg_list); 
static int          count_args  (const string& args);
static string       make_pattern(const string& word, const Key& key);

/* ================== Header definitions ================== */

void handle_args(const string& args) {
    try {
        handle(count_args(args), split_args(args));
    } catch (...) {
        print_general_help();
    }
}

list<string> split_args(const string& args) {
    list<string> splitted;
    string       buf;
    const char   SPACE = ' ';

    for (auto it = args.begin(); it != args.end(); ++it) {
        switch (*it) {
        case SPACE:
            if (!buf.empty()) {
                splitted.push_back(buf);
                buf.clear();
            }
            break;
        default:
            buf.push_back(*it);
            break;
        }
    }

    if (!buf.empty()) {
        splitted.push_back(buf);
    }

    return splitted;
}

/* ================== Static definitions ================== */

static void handle(int argc, const list<string>& arg_list) {
    string first;
    string second;
    string third;

    if (argc > 0) {
        first = arg_list.front();
    }

    switch (argc) {
    case 3:
        second = *(++(arg_list.begin()));
        third = arg_list.back();

        if (first == "set_example") {
            p_key->set_by_template(second, third);
        } else if (first == "find_similar") {
            print_closest(*p_vocabulary, second, stoi(third));
        } else if (first == "swap") {
            p_key->swap_keys(second[0], third[0]);
        } else if (first == "set") {
            p_key->set(second[0], third[0]);
        } else {
            print_general_help();
        }
        break;
    case 2:
        second = *(++(arg_list.begin()));

        if (first == "unset") {
            for (auto it = second.begin(); it != second.end(); ++it) {
                p_key->unset(*it);
            }
        } else if (first == "find_by_pattern") {
            print_by_pattern(*p_vocabulary, second);
        } else if (first == "decode") {
            print_by_pattern(*p_vocabulary, make_pattern(second, *p_key));
        } else {
            print_general_help();
        }

        break;
    case 1:
        if (first == "show_decoded") {
            print_decoded_text(*p_ciphertext, *p_key); 
        } else if (first == "count_stat") {
            print_text_stat(*p_ciphertext);
        } else if (first == "show_key") {
            print_key(*p_key);
        } else if (first == "find_paired") {
            print_paired_letters(*p_ciphertext);
        } else if (first == "show_encoded") {
            print_encoded_text(*p_ciphertext);
        } else if (first == "clear_key") {
            delete p_key;
            p_key = new Key();
        } else if (first == "show_all") {
            print_key(*p_key);
            cout << "---" << endl;
            print_encoded_text(*p_ciphertext);
            cout << "---" << endl;
            print_decoded_text(*p_ciphertext, *p_key); 
        } else {
            print_general_help();
        }
        break;
    default:
        print_general_help();
    }
}

int count_args(const string& args) {
    int         counter         = 0;
    bool        f_got_symbol    = false;
    const char  SPACE           = ' ';

    for (auto it = args.cbegin(); it != args.cend(); ++it) {
        switch (*it) {
        case SPACE:
            f_got_symbol = false;
            break;
        default:
            if (!f_got_symbol) {
                counter++;
            }
            f_got_symbol = true;
            break;
        }
    }

    return counter;
}


/* ================== Static definitions ================== */

static string make_pattern(const string& word, const Key& key) {
    map<char, int>  char_group;
    int             group_num = 0;
    string          pattern = word;

    for (int i = 0; i < word.length(); ++i) {
        if (key.get(word[i]) != Key::MOCK) {
            pattern[i] = key.get(word[i]);
        } else {
            if (char_group.find(word[i]) == char_group.end()) {
                char_group[word[i]] = group_num;
                group_num++;
            }
            pattern[i] = Vocabulary::to_group(char_group[word[i]]);
        }
    }

    return pattern;
}