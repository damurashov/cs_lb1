#ifndef PRINT_OPS_H
#define PRINT_OPS_H

#include <string>
#include <iostream>
#include <list>
#include <utility>
#include <set>
#include "vocabulary.h"
#include "key.h"
#include "ciphertext.h"

void print_general_help     ();
void print_closest          (const Vocabulary& voc, const std::string& word, int precision);
void print_key              (const Key& key);
void print_decoded_text     (const Ciphertext& text, const Key& key);
void print_encoded_text     (const Ciphertext& text);
void print_paired_letters   (const Ciphertext& text);
void print_by_pattern       (const Vocabulary& voc, const std::string& pattern);
void print_by_pattern       (const Vocabulary& voc,
                             const Key& key, 
                             const std::string& encoded, 
                             const std::string& partially_decoded);
void print_text_stat        (const Ciphertext& text);

#endif /* PRINT_OPS_H */