#include <iostream>

#include "Geoparse.hpp"

int main(int argc, char** argv) {

	Simplexer::Lexer lexer;
	/*
	if (!lexer.readFile("test.txt")) {
		std::cerr << "Failed to read file" << std::endl;
		return -1;
	}
	*/

	lexer.setString("'hello' + 2 * (34 - 1) + 3");

	std::list<Simplexer::Token> tokens;
	Simplexer::Token* token;
	for (token = &lexer.next(); token->type != Simplexer::TokenType::END_OF_FILE; token = &lexer.next()) {
		tokens.emplace_back(std::move(*token));
	}
	tokens.emplace_back(std::move(*token)); // push last END_OF_FILE token

	Geoparse::Parser parser;
	parser.parse(tokens);
	parser.debugPrint();

	return 0;
}