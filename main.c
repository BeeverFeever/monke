#include "lexer.h"

int main(void) {
    char* input = "let five = 5;"
                  "let ten = 10;"
                  "let add = fn(x, y) {"
                  "    x + y;"
                  "};"
                  "let result = add(five, ten);";
    // char* input = "+=(){},;\0";
    lexer l = create_lexer(input);
    token tok;
    do {
        tok = next_token(&l);
        debug_token(tok);
    } while (tok.type != token_eof);
    return 0;
}
