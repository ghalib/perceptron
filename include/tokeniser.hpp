#ifndef _TOKENISER_HPP
#define _TOKENISER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

class StdTokeniser {
private:
    bool is_alphanum(char c);
    size_t find_first_alphanum(const std::string&, size_t);
    size_t find_first_not_alphanum(const std::string&, size_t);
public:
    void tokenise(const std::string&, std::vector<std::string>&);
};

#endif
