#include "key.h"

using namespace std;

/* ============= Constr., destr. =============== */
Key::Key() {}

Key::Key(const Key& key) : m_keymap(key.m_keymap) {}

/* ============= Arithm. operators =============== */

Key Key::operator=(const Key& key) {
    m_keymap = key.m_keymap;
    return *this;
}

/* ============= Public methods =============== */

const map<char, char>& Key::get_keymap() const {
    return m_keymap;
}

bool Key::has_key(char key) const {
    return m_keymap.find(key) != m_keymap.end();
}

void Key::set(char key, char value) {
    m_keymap[key] = value;
}

void Key::unset(char key) {
    m_keymap.erase(key);
}

void Key::set_by_template(const string& encrypted, const string& decrypted) {   
    if (encrypted.length() != decrypted.length()) {
        return;
    }

    for (int i = 0; i < encrypted.length(); ++i) {
        m_keymap[encrypted[i]] = decrypted[i];
    }
}

void Key::swap_keys(char key_1, char key_2) {
    char tmp_k1 = m_keymap[key_1];

    m_keymap[key_1] = m_keymap[key_2];
    m_keymap[key_2] = tmp_k1;
}

char Key::get(char key) const {
    if (has_key(key)) {
        //return m_keymap[key];
        return m_keymap.at(key);
    } else {
        return MOCK;
    }
}