#include "print_ops.h"

using namespace std;

#define OUTLINE(arg) cout << arg << endl

/* 3 arg.*/
static const char*       HELP_HOW_TO_START        = "decrypt <ciphertext_path> <vocabulary_path>";

static const char*       HELP_SET_BY_EXAMPLE      = "set_example <encoded_word> <decoded_word>";
static const char*       HELP_PRINT_CLOSEST_WORDS = "find_similar <word> <max_diff>";
static const char*       HELP_SWAP                = "swap <symbol_1> <symbol_2>";
static const char*       HELP_SET_KEY             = "set <key> <value>";

/* 2 arg.*/
static const char*       HELP_UNSET_KEY           = "unset <key>";
static const char*       HELP_FIND_BY_PATTERN_2   = "find_by_pattern <pattern>";
static const char*		 HELP_DECODE			  = "decode <encoded_word>";

/* 1 arg. */
static const char*       HELP_PRINT_DECODED_TEXT  = "show_decoded";
static const char*       HELP_PRINT_KEY           = "show_key";
static const char*       HELP_CLEAR_KEY           = "clear_key";
static const char*       HELP_PRINT_ENCODED_TEXT  = "show_encoded";
static const char*       HELP_PRINT_KEYDECENC     = "show_all";
static const char*       HELP_PRINT_STAT          = "count_stat";
static const char*       HELP_FIND_PAIRED_LETTERS = "find_paired";
static const char*       HELP_GENERAL_HELP        = "help";
static const char*       HELP_EXIT                = "exit";

void print_general_help() {
    OUTLINE(HELP_HOW_TO_START);

    /*3 arg */
    OUTLINE(HELP_SET_BY_EXAMPLE);
    OUTLINE(HELP_PRINT_CLOSEST_WORDS);
    OUTLINE(HELP_SWAP);
    OUTLINE(HELP_SET_KEY);

    /* 2 arg.*/
    OUTLINE(HELP_UNSET_KEY);
    OUTLINE(HELP_FIND_BY_PATTERN_2);
	OUTLINE(HELP_DECODE);

    /* 1 arg. */
    OUTLINE(HELP_PRINT_DECODED_TEXT);
    OUTLINE(HELP_PRINT_KEY);
    OUTLINE(HELP_CLEAR_KEY);
    OUTLINE(HELP_PRINT_ENCODED_TEXT);
    OUTLINE(HELP_PRINT_KEYDECENC);
    OUTLINE(HELP_PRINT_STAT);
    OUTLINE(HELP_FIND_PAIRED_LETTERS);
    OUTLINE(HELP_GENERAL_HELP);
    OUTLINE(HELP_EXIT);
}

void print_closest (const Vocabulary& voc, const string& word, int precision) {
    list<string> closest_list = voc.get_closest(word, precision);
    for (auto it = closest_list.begin(); it != closest_list.end(); ++it) {
        OUTLINE(*it);
    }
}

void print_key(const Key& key) {
    for (auto it = key.get_keymap().cbegin(); it != key.get_keymap().cend(); ++it) {
        OUTLINE(it->first << "   -->   " << it->second);
    }
}

void print_decoded_text(const Ciphertext& text, const Key& key) {
    list<string> dectext = text.decrypt_punctuated(key);
    for (auto it = dectext.begin(); it != dectext.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;
}

void print_encoded_text(const Ciphertext& text) {
    const list<string>& enctext = text.get_punctuated();
    for (auto it = enctext.begin(); it != enctext.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;
}

void print_paired_letters(const Ciphertext& text) {
    const list<string>& clear = text.get_clear();
    list<char>          paired;
    
    for (auto it_word = clear.begin(); it_word != clear.end(); ++it_word) {
        const string& word = *it_word;
        for (int i = 1; i < word.length(); ++i) {
            if (word[i] == word[i-1]) { 
                paired.push_back(word[i]);
            }
        }
    }
    
    paired.unique();
    for (auto it = paired.begin(); it != paired.end(); ++it) {
        cout << *it << endl;
    }
}

void print_by_pattern(const Vocabulary& voc, const string& pattern) {
    list<string> result = voc.get_by_pattern(pattern);

    for (auto it = result.begin(); it != result.end(); ++it) {
        OUTLINE(*it);
    }
}

void print_text_stat(const Ciphertext& text) {
    const list<string>&     clear_encoded = text.get_clear();
    list<pair<char,double>> stat_ordered;
    map<char, int>          stat_unordered;
    int                     n_symb_total = 0;
    int                     max;
    char                    buf;

    /* Reg chars */
    for (auto it_string = clear_encoded.begin(); it_string != clear_encoded.end(); ++it_string) {
        for (auto it_char = it_string->begin(); it_char != it_string->end(); ++it_char) {
            if (stat_unordered.find(*it_char) == stat_unordered.end()) {
                stat_unordered[*it_char] = 0;
            } else {
                stat_unordered[*it_char] = stat_unordered[*it_char] + 1;
            }
            n_symb_total = n_symb_total + 1;
        }
    }

    /* Count stat */
    while (!stat_unordered.empty()) {
        max = 0;
        for (auto it = stat_unordered.begin(); it != stat_unordered.end(); ++it) {
            if (it->second >= max) {
                max = it->second;
                buf = it->first;
            }
        }
        stat_ordered.push_back(make_pair(buf, ((double)max / (double)n_symb_total)));
        stat_unordered.erase(buf);
    }

    /*Print stat */
    for (auto it = stat_ordered.begin(); it != stat_ordered.end(); ++it) {
        OUTLINE(it->first << "\t" << it->second);
    }    
}