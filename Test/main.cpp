#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "../expression_parser.hpp"

TEST_CASE("ExpressionParser::ExpressionParser") {
    SUBCASE("Empty expression") {
        CHECK_THROWS_AS(ExpressionParser expression_parser("     "), std::invalid_argument const &);
    }

    SUBCASE("Reserved term name") {
        CHECK_THROWS_AS(ExpressionParser expression_parser("E_0", { { "E_0", std::shared_ptr<Node>(new Node()) } }), std::invalid_argument const &);
        CHECK_THROWS_AS(ExpressionParser expression_parser("F_0", { { "F_0", std::shared_ptr<Node>(new Node()) } }), std::invalid_argument const &);
        CHECK_THROWS_AS(ExpressionParser expression_parser("C_0", { { "C_0", std::shared_ptr<Node>(new Node()) } }), std::invalid_argument const &);
    }
}

TEST_CASE("ExpressionParser::Parse") {
    SUBCASE("Unrecognized function") {
        CHECK_THROWS_AS(ExpressionParser expression_parser("unrecognized\\left(3.14\\right)"); expression_parser.Parse(), std::invalid_argument const &);
    }

    SUBCASE("Bracket mismatch") {
        CHECK_THROWS_AS(ExpressionParser expression_parser("1 * \\left{ 3 + 2 \\right)"); expression_parser.Parse(), std::invalid_argument const &);
    }

    SUBCASE("Undefined term") {
        CHECK_THROWS_AS(ExpressionParser expression_parser("undefined * 2"); expression_parser.Parse(), std::invalid_argument const &);
    }
}
