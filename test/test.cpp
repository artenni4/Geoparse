#include <iostream>

#include "Geoparse.hpp"

int main(int argc, char** argv) {

	Simplexer::Lexer lexer;
	if (!lexer.readFile("test.txt")) {
		std::cerr << "Failed to read file" << std::endl;
		return -1;
	}

	std::list<Simplexer::Token> tokens;
	for (Simplexer::Token token = lexer.next(); token.type != Simplexer::TokenType::END_OF_FILE; token = lexer.next()) {
		tokens.emplace_back(std::move(token));
	}

	Geoparse::Parser parser;
	parser.parse(tokens);

	return 0;
}