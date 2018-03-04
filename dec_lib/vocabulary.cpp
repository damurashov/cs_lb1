#include "vocabulary.h"
using namespace std;

/* ========== Constructors, destructors ========== */

Vocabulary::Vocabulary(const string& path) {
    fstream input(path, std::ios::in);
    string  buf;

    while (getline(input, buf)) {
        m_vocabulary.push_back(buf);
    }
}

/* ================ Protected methods ================== */

bool Vocabulary::is_pattern_checked(const string& word, const string& pattern) const {
    static const char   MOCK                = '@';
    char                a_groups[N_GROUPS];
    char                buf_pattern;
    int                 group;

    for (int i = 0; i < N_GROUPS; ++i) {
        a_groups[i] = MOCK;
    }

    /* Pattern's and word's lentghs must be equal*/
    if (word.length() != pattern.length()) {
        return false;
    }
    
    for (int i = 0; i < word.length(); ++i) {
        /**/
        if (word[i] == pattern[i]) {
            continue;
        } else if (pattern[i] == PATTERN_LETTER) {
            continue;
        } else if (to_int(pattern[i] != -1)) {
            group = to_int(pattern[i]);
            if (a_groups[group] == word[i]) {
                continue;
            } else if (a_groups[group] == MOCK) {
                for (int j = 0; j < N_GROUPS; ++j) {
                    if ((j != group) && (a_groups[j] == word[i])) {
                        return false;
                    }
                }
                for (auto it_char_pattern = pattern.begin(); it_char_pattern != pattern.end(); ++it_char_pattern) {
                    if (*it_char_pattern == word[i]) {
                        return false;
                    }
                }
                a_groups[group] = word[i];
                continue;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

int Vocabulary::to_int(char numeric_char) const {
    int result;

    result = numeric_char - '0';
    if ((result < 0) || (result > 9)) {
        return -1;
    } else {
        return result;
    }
}

/* ================ Public methods ================== */

char Vocabulary::to_group(int offset)  {
    const char BASE = '0';

    if (offset > 9) {
        return PATTERN_LETTER;
    } else {
        return (char)(BASE + offset);
    }
}

int Vocabulary::count_diff(const string& word_1, const string& word_2) const {
    int diff = abs((int)(word_1.length() - word_2.length()));
    int minlen = min(word_1.length(), word_2.length());

    for (int i = 0; i <= minlen; ++i) {
        if (word_1[i] != word_2[i]) {
            diff++;
        }
    }

    return diff;
}

bool Vocabulary::is_existent(const string& word) const {
    list<string>::const_iterator it;

    for (it = m_vocabulary.cbegin(); it != m_vocabulary.cend(); it++) {
        if (*it == word) {
            return true;
        }
    }

    return false;
}

list<string> Vocabulary::get_closest(const string& user_word, int precision) const {
    list<string>    closest_list;
    string          word(user_word);
    char            lower;

    for (auto it = m_vocabulary.begin(); it != m_vocabulary.end(); ++it) {
        if (count_diff(word, *it) <= precision) {
            closest_list.push_back(*it);
        }
    }

    return closest_list;
}

list<string> Vocabulary::get_by_pattern(const string& pattern) const {
    list<string>    words_list;

    for (auto it_word = m_vocabulary.begin(); it_word != m_vocabulary.end(); ++it_word) {
        if (is_pattern_checked(*it_word, pattern)) {
            words_list.push_back(*it_word);
        }
    }

    return words_list;
}