#pragma once

#include <memory>
#include <list>
#include <string_view>

#include "Simplexer.hpp"

namespace Geoparse {

	// Main interface to Geoparse
	class Parser {
	public:
		void parse(const std::list<Simplexer::Token>&);
		void debugPrint();
	};


	// Base class for all language constructions
	class ASTExpression {

	};

	// GeoObject represents any data that take part in GEOLOG program
	// including numbers, strings, functions, user-defined classes
	//
	// Note: Hence GEOLOG will not have a garbage collector, instead it will
	// delete an object immediately
	//
	// Functions will have reference(variable) with its own name in order
	// not to delete it after creating
	class GeoObject : public ASTExpression {

	};

	// Operator is a parent for u-,bi-,ternary, conditional, loop operators, etc.
	class Operator : public ASTExpression {

	};

	// Represents binary operation, has left and right AST childs
	class BinaryOperator : public Operator {
		std::unique_ptr<ASTExpression> m_lhs;
		std::unique_ptr<ASTExpression> m_rhs;
		Simplexer::TokenType m_op;
	};

	// Variable in GEOLOG is generally a reference to an GeoObject
	class Variable : public ASTExpression {
		std::unique_ptr<GeoObject> m_ref;
	};
}