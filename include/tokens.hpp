#pragma once 

#include <optional>
#include <string>

using namespace std;

enum class TokenType{
    EXIT,
    OPEN_PAREM,
    CLOSE_PAREM,
    SEMICOLON,
    INT_LIT
};

struct Token{
    TokenType type;
    optional<string> value {};
};    
