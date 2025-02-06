#pragma once

#include <string>
#include <vector>
#include <ctype.h>
#include <iostream>
#include <optional>
#include <stdio.h>

#include "tokens.hpp"
#include "debug.hpp"

using namespace std;

class Tokenizer{
public:
    inline explicit Tokenizer(string& src):
        m_src(move(src)){}
        
    inline vector<Token> tokenize(){
         std::vector<Token> tokens;
        std::string buf;
        while (peak().has_value()) {
            if (std::isalpha(peak().value())) {
                buf.push_back(consume());
                while (peak().has_value() && std::isalnum(peak().value())) {
                    buf.push_back(consume());
                }
                if (buf == "exit") {
                    tokens.push_back({ .type = TokenType::EXIT });
                    buf.clear();
                    continue;
                }
                else {
                    std::cerr << "You messed up!" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if (peak().value() == '(') {
                consume();
                tokens.push_back({ .type = TokenType::OPEN_PAREM});
                continue;
            }
            else if (std::isdigit(peak().value())) {
                buf.push_back(consume());
                while (peak().has_value() && std::isdigit(peak().value())) {
                    buf.push_back(consume());
                }
                tokens.push_back({ .type = TokenType::INT_LIT, .value = buf });
                buf.clear();
                continue;
            }
            else if (peak().value() == ')') {
                consume();
                tokens.push_back({ .type = TokenType::CLOSE_PAREM});
                continue;
            }
            else if (peak().value() == ';') {
                consume();
                tokens.push_back({ .type = TokenType::SEMICOLON});
                continue;
            }
            else if (std::isspace(peak().value())) {
                consume();
                continue;
            }
            else {
                std::cerr << "You messed up!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        index = 0;
        return tokens;
    }

private:

    [[nodiscard]] inline std::optional<char> peak(int ahead = 1) const
    {
        if (index + ahead > m_src.length()) {
            return {};
        }
        else {
            return m_src.at(index);
        }
    }
    inline char consume()
    {
        return m_src.at(index++);
    }

    
    const string m_src;
    size_t index = 0;
};