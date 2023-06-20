#include "lexer.h"

int main(void) {
    char* input = "+=(){},;\0";
    lexer l = create_lexer(input);
    token tok;
    do {
        tok = next_token(&l);
        debug_token(tok);
    } while (tok.type != token_eof);
    return 0;
}
