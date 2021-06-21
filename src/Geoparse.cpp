#include "Geoparse.hpp"

#include <iostream>

namespace Geoparse {

	// ============ PARSER FUNCTIONS ===============

	void Parser::parse(const std::list<Simplexer::Token>& tokens)
	{
		m_currToken = tokens.begin();

		std::cout << m_currToken->symbol << std::endl;
	}

	void Parser::debugPrint()
	{
		std::cout << "Debug print" << std::endl;
	}

}