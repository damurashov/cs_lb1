#ifndef KEY_H
#define KEY_H

#include <map>
#include <string>

class Key {
private:
    std::map<char, char>        m_keymap; /* <KEY, VALUE> */
public:
    static const char           MOCK = '@';

    const std::map<char, char>& get_keymap      () const;
    bool                        has_key         (char key) const;
    void                        set             (char key, char value);
    void                        unset           (char key);
    void                        set_by_template (const std::string& encrypted_word, 
                                                 const std::string& decrypted_word);
    void                        swap_keys       (char key_1, char key_2);
    char                        get             (char key) const;
                                Key             ();
                                Key             (const Key&);
    Key                         operator=       (const Key&);
};

#endif /* KEY_H */