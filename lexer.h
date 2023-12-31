#include <stdio.h>
#include <string.h>

#define CREATE_TOKEN(t,c) (token){ .literal = c, .type = t }

typedef enum {
    token_illegal,
    token_eof,
    token_ident,
    token_int,
    token_assign,
    token_plus,
    token_minus,
    token_bang,
    token_asterisk,
    token_slash,
    token_lt,
    token_gt,
    token_equal,
    token_notequal,
    token_comma,
    token_semicolon,
    token_lparen,
    token_rparen,
    token_lsquirly,
    token_rsquirly,
    token_function,
    token_let,
    token_true,
    token_false,
    token_if,
    token_else,
    token_return,

    len_token_type
} token_type;

static const char* const str_token_type[len_token_type] = {
    [token_illegal] = "illegal",
    [token_eof] = "eof",
    [token_ident] = "ident",
    [token_int] = "int",
    [token_assign] = "assign",
    [token_plus] = "plus",
    [token_minus] = "minus",
    [token_bang] = "bang",
    [token_asterisk] = "asterisk",
    [token_slash] = "slash",
    [token_lt] = "lt",
    [token_gt] = "gt",
    [token_equal] = "equal",
    [token_notequal] = "notequal",
    [token_comma] = "comma",
    [token_semicolon] = "semicolon",
    [token_lparen] = "lparen",
    [token_rparen] = "rparen",
    [token_lsquirly] = "lsquirly",
    [token_rsquirly] = "rsquirly",
    [token_function] = "function",
    [token_let] = "let",
    [token_true] = "true",
    [token_false] = "false",
    [token_if] = "if",
    [token_else] = "else",
    [token_return] = "return",
};

typedef struct {
    // 512 is even being generous, if a literal is more than that, there is a
    // serious problem.
    char literal[512];
    token_type type;
} token;

typedef struct {
    char ch;
    int pos;
    int readPos;

    char* source;
    int sourceLen;
} lexer;

void debug_token(token t);
lexer create_lexer(char* source);
token next_token(lexer* l);
void read_char(lexer* l);

// I couldn't figure out how to make these functions without dynamic memory so I had to
// 'take inspiration' from @zivlakmilos implementation. Thankyou.
const char* read_identifier(lexer* l, size_t* len);
const char* read_number(lexer* l, size_t* len);

int is_letter(const char c);
int is_number(const char c);
token_type identifier_from_literal(const char* literal, size_t len);
void skip_whitespace(lexer* l);
