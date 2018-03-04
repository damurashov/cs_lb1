#ifndef ARG_HANDLER_H
#define ARG_HANDLER_H

#include "key.h"
#include "vocabulary.h"
#include "print_ops.h"
#include <list>
#include <string>

void                    handle_args (const std::string& args);
std::list<std::string>  split_args  (const std::string& args);

#endif /* ARG_HANDLER_H */