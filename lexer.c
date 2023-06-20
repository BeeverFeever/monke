#include "lexer.h"

void debug_token(token t) {
    printf("TOKEN\n\r   %s\n\r   %s\n", t.literal, str_token_type[t.type]);
}

void read_char(lexer* l) {
    if (l->readPos >= l->sourceLen) {
        l->ch = '\0';
    } else {
        l->ch = l->source[l->readPos];
    }
    l->pos = l->readPos;
    l->readPos++;
}

lexer create_lexer(char* source) {
    lexer l = (lexer){
        .source = source,
        .sourceLen = strlen(source),
    };
    read_char(&l);
    return l;
}

token next_token(lexer* l) {
    token tok;
    switch(l->ch) {
        case '{':
            tok = CREATE_TOKEN(token_lsquirly, "{");
            break;
        case '}':
            tok = CREATE_TOKEN(token_rsquirly, "}");
            break;
        case '(':
            tok = CREATE_TOKEN(token_lparen, "(");
            break;
        case ')':
            tok = CREATE_TOKEN(token_rparen, ")");
            break;
        case ',':
            tok = CREATE_TOKEN(token_comma, ",");
            break;
        case ';':
            tok = CREATE_TOKEN(token_semicolon, ";");
            break;
        case '+':
            tok = CREATE_TOKEN(token_plus, "+");
            break;
        case '-':
            tok = CREATE_TOKEN(token_minus, "-");
            break;
        case '=':
            tok = CREATE_TOKEN(token_equal, "=");
            break;
        case '\0':
            tok = CREATE_TOKEN(token_eof, "");
            break;
        default:
            if (is_letter(l->ch)) {
                tok.literal = read_identifier(&l);
                return tok;
            } else {
                tok = CREATE_TOKEN(token_illegal, l->ch);
            }
    }

    read_char(l);
    return tok;
}

char* read_identifier(lexer* l) {

}
