#ifndef CIPHERTEXT_H
#define CIPHERTEXT_H

#include <string>
#include <list>
#include <fstream>
#include "key.h"

class Ciphertext {
private:
    static const std::string        m_punctmarks;
    std::list<std::string>          m_clear_text;
    std::list<std::string>          m_punctuated_text;
protected:
    bool                            is_punctmark        (const char symbol) const;
    std::list<std::string>          decrypt             (const Key&, const std::list<std::string>& text) const;
public:
    const std::list<std::string>&   get_clear           () const;
    const std::list<std::string>&   get_punctuated      () const;
    std::list<std::string>          decrypt_clear       (const Key&) const;
    std::list<std::string>          decrypt_punctuated  (const Key&) const;
    void                            push_text           (const std::string&);
    void                            clear               ();
                                    Ciphertext          (const std::string& path);
};

#endif /* CIPHERTEXT_H */