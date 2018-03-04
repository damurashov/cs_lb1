#include "ciphertext.h"

using namespace std;

const string Ciphertext::m_punctmarks(".,;'\"!?-");

/* ===================== Constr., destr. ===================== */

Ciphertext::Ciphertext(const string& path) {
    fstream input_file(path, std::ios::in);
    string  buf;

    while (getline(input_file, buf)) {
        push_text(buf);
    }
}

/* ===================== Protected methods ===================== */

bool Ciphertext::is_punctmark(const char symb) const {
    for (auto it = m_punctmarks.begin(); it != m_punctmarks.end(); ++it) {
        if (*it == symb) {
            return true;
        }
    }
    return false;
}

list<string> Ciphertext::decrypt(const Key& key, const list<string>& text) const {
    list<string>            decrypted;
    string                  buf;
    char                    symb;
    
    for (auto it_list = text.cbegin(); it_list != text.cend(); ++it_list) {
        buf = *it_list;
        for (auto it_str = buf.begin(); it_str != buf.end(); ++it_str) {
            symb = key.get(*it_str);
            if (symb != Key::MOCK) {
                *it_str = symb;
            }
        }
        decrypted.push_back(buf);
    }
    return decrypted;
}

/* ======================= Public methods ====================== */

const list<string>& Ciphertext::get_clear() const {
    return m_clear_text;
}

const list<string>& Ciphertext::get_punctuated() const {
    return m_punctuated_text;
}

list<string> Ciphertext::decrypt_clear(const Key& key) const {
    return decrypt(key, m_clear_text);
}

list<string> Ciphertext::decrypt_punctuated(const Key& key) const {
    return decrypt(key, m_punctuated_text);
}

void Ciphertext::push_text(const string& text) {
    const char              SPACE = ' ';
    string                  buf_clr;
    string                  buf_pnc;

    for (auto it_char = text.cbegin();it_char != text.cend(); ++it_char) {
        if (*it_char == SPACE) {
            if (!buf_clr.empty()) {
                m_clear_text.push_back(buf_clr);
                buf_clr.clear();
            }
            if (!buf_pnc.empty()) {
                m_punctuated_text.push_back(buf_pnc);
                buf_pnc.clear();
            }
        } else {
            if (!is_punctmark(*it_char)) {
                buf_clr.push_back(*it_char);
            }
            buf_pnc.push_back(*it_char);
        }
    }

    if (!buf_clr.empty()) {
        m_clear_text.push_back(buf_clr);
    }
    if (!buf_pnc.empty()) {
        m_punctuated_text.push_back(buf_pnc);
    }
}

void Ciphertext::clear() {
    m_clear_text.clear();
    m_punctuated_text.clear();
}