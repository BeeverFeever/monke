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

    token expected[37] = {
        {.literal = "let", .type = token_let},
        {.literal = "five", .type = token_ident},
        {.literal = "=", .type = token_equal},
        {.literal = "5", .type = token_int},
        {.literal = ";", .type = token_semicolon},
        {.literal = "let", .type = token_let},
        {.literal = "ten", .type = token_ident},
        {.literal = "=", .type = token_equal},
        {.literal = "10", .type = token_int},
        {.literal = ";", .type = token_semicolon},
        {.literal = "let", .type = token_let},
        {.literal = "add", .type = token_ident},
        {.literal = "=", .type = token_equal},
        {.literal = "fn", .type = token_function},
        {.literal = "(", .type = token_lparen},
        {.literal = "x", .type = token_ident},
        {.literal = ",", .type = token_comma},
        {.literal = "y", .type = token_ident},
        {.literal = ")", .type = token_rparen},
        {.literal = "{", .type = token_lsquirly},
        {.literal = "x", .type = token_ident},
        {.literal = "+", .type = token_plus},
        {.literal = "y", .type = token_ident},
        {.literal = ";", .type = token_semicolon},
        {.literal = "}", .type = token_rsquirly},
        {.literal = ";", .type = token_semicolon},
        {.literal = "let", .type = token_let},
        {.literal = "result", .type = token_ident},
        {.literal = "=", .type = token_equal},
        {.literal = "add", .type = token_ident},
        {.literal = "(", .type = token_lparen},
        {.literal = "five", .type = token_ident},
        {.literal = ",", .type = token_comma},
        {.literal = "ten", .type = token_ident},
        {.literal = ")", .type = token_rparen},
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

UTEST_MAIN();

#endif // TEST_LEXER
