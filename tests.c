#ifndef TEST_LEXER
#define TEST_LEXER

#include "utest.h"
#include "lexer.h"

UTEST(lexer, basic_tokens) {
    char* input = "+=(){},;";
    lexer l = create_lexer(input);

    token expected[9] = {
        {.literal = "+", .type = token_plus},
        {.literal = "=", .type = token_equal},
        {.literal = "(", .type = token_lparen},
        {.literal = ")", .type = token_rparen},
        {.literal = "{", .type = token_lsquirly},
        {.literal = "}", .type = token_rsquirly},
        {.literal = ",", .type = token_comma},
        {.literal = ";", .type = token_semicolon},
        {.literal = "", .type = token_eof},
    };

    token tok;
    for (int i = 0; i < 9; i++) {
        tok = next_token(&l);
        ASSERT_STREQ(tok.literal, expected[i].literal);
        ASSERT_EQ(expected[i].type, tok.type);
    }
}

UTEST(lexer, complicated_tokens) {
    char* input = "let five = 5;"
                  "let ten = 10;"
                  "let add = fn(x, y) {"
                  "    x + y;"
                  "};"
                  "let result = add(five, ten);";
    lexer l = create_lexer(input);

    token expected[9] = {
        {.literal = "+", .type = token_plus},
        {.literal = "=", .type = token_equal},
        {.literal = "(", .type = token_lparen},
        {.literal = ")", .type = token_rparen},
        {.literal = "{", .type = token_lsquirly},
        {.literal = "}", .type = token_rsquirly},
        {.literal = ",", .type = token_comma},
        {.literal = ";", .type = token_semicolon},
        {.literal = "", .type = token_eof},
    };

}

UTEST_MAIN();

#endif // TEST_LEXER
