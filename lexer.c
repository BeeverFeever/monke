#include "lexer.h"

void debug_token(token t) 
{
    printf("TOKEN\n\r   %s\n\r   %s\n", t.literal, str_token_type[t.type]);
}

void read_char(lexer* l) 
{
    if (l->readPos >= l->sourceLen) {
        l->ch = '\0';
    } else {
        l->ch = l->source[l->readPos];
    }
    l->pos = l->readPos;
    l->readPos++;
}

lexer create_lexer(char* source) 
{
    lexer l = (lexer){
        .source = source,
        .sourceLen = strlen(source),
    };
    read_char(&l);
    return l;
}

static char* cpystr(const char* src, char* dest, size_t n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
    return dest;
}

token next_token(lexer* l) 
{
    token tok;
    skip_whitespace(l);

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
                size_t len = 0;
                const char* id = read_identifier(l, &len);
                strncpy(tok.literal, id, len);
                tok.type = identifier_from_literal(tok.literal, len);
                return tok;
            } else if (is_number(l->ch)) {
                size_t len = 0;
                const char* id = read_number(l, &len);
                strncpy(tok.literal, id, len);
                tok.type = token_int;
                return tok;
            } else {
                tok = CREATE_TOKEN(token_illegal, l->ch);
            }
    }

    read_char(l);
    return tok;
}

token_type identifier_from_literal(const char* literal, size_t len) 
{
    if (strncmp(literal, "fn", len) == 0) {
        return token_function;
    } else if (strncmp(literal, "let", len) == 0) {
        return token_let;
    }
    return token_ident;
}

const char* read_identifier(lexer* l, size_t* len)
{
    int pos = l->pos;
    while (is_letter(l->ch)) {
        read_char(l);
    }
    *len = l->pos - pos;

    // return the start of the identifier
    return l->source + pos;
}

const char* read_number(lexer* l, size_t* len) 
{
    int pos = l->pos;
    while (is_letter(l->ch)) {
        read_char(l);
    }
    *len = l->pos - pos;

    // return the start of the identifier
    return l->source + pos;
}

int is_letter(const char c) 
{
    return ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || c == '_');
}

int is_number(const char c) 
{
    return ('0' <= c && c <= '9');
}

void skip_whitespace(lexer* l) {
    while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
        read_char(l);
    }
}
