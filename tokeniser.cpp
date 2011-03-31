#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "tokeniser.hpp"

#define PR(x)                                   \
    std::cout << #x << " = " << x << std::endl;

bool StdTokeniser::is_alphanum(char c) {
    return (std::isalpha(c) || std::isdigit(c));
}

size_t StdTokeniser::find_first_alphanum(const std::string& s, size_t start=0) {
    size_t index = start;
    for(; index < s.length(); index++) {
        if (is_alphanum(s[index]))
            break;
    }
    return index;
}

size_t StdTokeniser::find_first_not_alphanum(const std::string& s, size_t start=0) {
    size_t index = start;
    for(; index < s.length(); index++) {
        if (!(is_alphanum(s[index])))
            break;
    }
    return index;
}

void StdTokeniser::tokenise(const std::string& s, std::vector<std::string>& tokens) {
    size_t start = 0;
    size_t end = start + 1;
    while (start != end) {
        start = find_first_alphanum(s, start);
        if (start >= s.length())
            break;
        end = find_first_not_alphanum(s, start);
        tokens.push_back(std::string(s.begin() + start, s.begin() + end));
        start = end + 1;
    }
}
