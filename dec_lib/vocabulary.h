#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <fstream>
#include <string>
#include <list>
#include <map>
#include <cmath>
#include <stdlib.h>
#include <ctype.h>

class Vocabulary {
private:
    std::list<std::string>  m_vocabulary;
    static const char       PATTERN_LETTER  = '*';

    bool                    is_pattern_checked  (const std::string& word, const std::string& pattern) const;
    int                     to_int              (char numeric_char) const;
public:
    static const int        N_GROUPS            = 10;

    static char             to_group            (const int group_number);
    int                     count_diff          (const std::string& word_1, const std::string& word_2) const;
    bool                    is_existent         (const std::string& word) const;
    std::list<std::string>  get_closest         (const std::string& word, int precision) const;
    std::list<std::string>  get_by_pattern      (const std::string& patterned_word) const;
                            Vocabulary          (const std::string& path);
};

#endif /*VOCABULARY_H */