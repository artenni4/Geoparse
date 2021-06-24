#include "Geoparse.hpp"

#include <iostream>
#include <string>
#include <stdexcept>

namespace Geoparse {

	// helper function for debugPrint()
	// prints given count of \t
	void debugPrintIndent(std::size_t indent)
	{
		for (std::size_t i = 0; i < indent; ++i) {
			std::cout << '\t';
		}
	}

	// ============ PARSER FUNCTIONS ===============

	std::unique_ptr<ASTExpression> Parser::expectExpression()
	{
		auto firstValue = expectOneValue();
		auto expectBinary = expectBinaryOperation(std::move(firstValue), 0);
		++m_currToken; // eat last token because expression was already parsed
		return std::move(expectBinary);
	}

	std::unique_ptr<ASTExpression> Parser::expectPrimary()
	{
		++m_currToken;
		return std::move(expectOneValue());
	}

	std::unique_ptr<ASTExpression> Parser::expectOneValue()
	{
		std::unique_ptr<ASTExpression> result;
		switch (m_currToken->type) {
		case Simplexer::TokenType::INTEGER:
			result = std::make_unique<GeoInterger>(m_currToken->symbol);
			break;
		case Simplexer::TokenType::RATIONAL:
			result = std::make_unique<GeoRational>(m_currToken->symbol);
			break;
		case Simplexer::TokenType::LEFT_PARAN:
			++m_currToken; // eat left paranthesis
			result = expectExpression();
			if (m_currToken->type != Simplexer::TokenType::RIGHT_PARAN) {
				throw std::runtime_error("Ìissing closing bracket ')'");
			}
			break;
		case Simplexer::TokenType::STRING:
			result = std::make_unique<GeoString>(m_currToken->symbol);
			break;
		default:
			result = nullptr;
			break;
		}
		return std::move(result);
	}

	std::unique_ptr<ASTExpression> Parser::expectBinaryOperation(std::unique_ptr<ASTExpression> lhs, int minPrecedence)
	{
		// Precedence climbing method
		// https://en.wikipedia.org/wiki/Operator-precedence_parser

		std::list<Simplexer::Token>::const_iterator lookahead = std::next(m_currToken);
		while (operatorPrecedence(lookahead->type) >= minPrecedence) {
			std::list<Simplexer::Token>::const_iterator op = lookahead;
			++m_currToken;
			auto rhs = expectPrimary();

			lookahead = std::next(m_currToken);
			while (operatorPrecedence(lookahead->type) >= operatorPrecedence(op->type)) {
				rhs = expectBinaryOperation(std::move(rhs), minPrecedence + 1);
				lookahead = std::next(m_currToken);
			}

			lhs = std::make_unique<BinaryOperator>(std::move(lhs), op->type, std::move(rhs));
		}
		// should return same value if nothing found
		// or new value with expression
		return std::move(lhs);
	}

	int Parser::operatorPrecedence(const Simplexer::TokenType op)
	{
		switch (op) {
		case Simplexer::TokenType::PLUS:
		case Simplexer::TokenType::MINUS:
			return 1;
		case Simplexer::TokenType::ASTERISK:
		case Simplexer::TokenType::SLASH:
			return 2;
		default:
			return -1;
		}
	}

	void Parser::parse(const std::list<Simplexer::Token>& tokens)
	{
		m_currToken = tokens.begin();
		m_expr = std::move(expectExpression());
	}

	void Parser::debugPrint()
	{
		std::cout << "Debug print" << std::endl;
		m_expr->debugPrint(0);
	}

	// ============ GeoObject ======================

	void GeoObject::debugPrint(std::size_t indent)
	{
		debugPrintIndent(indent);
		std::cout << "GeoObject: " << m_rawValue << std::endl;
	}

	// ============ GeoInteger =================

	GeoInterger::GeoInterger(std::string_view value)
	{
		m_rawValue = value;
		m_value = std::stoll(value.data());
	}

	// ============ GeoRational =================

	GeoRational::GeoRational(std::string_view value)
	{
		m_rawValue = value;
		m_value = std::stold(value.data());
	}

	// =============== GeoString ================
	GeoString::GeoString(std::string_view value)
	{
		m_rawValue = value;
		m_value = value;
	}

	// ============= Binary Operator ================

	BinaryOperator::BinaryOperator(std::unique_ptr<ASTExpression> lhs, Simplexer::TokenType op, std::unique_ptr<ASTExpression> rhs)
		: m_lhs(std::move(lhs)), m_op(op), m_rhs(std::move(rhs)) {}

	void BinaryOperator::debugPrint(std::size_t indent)
	{
		++indent;
		debugPrintIndent(indent);
		std::cout << "Binary operation (" << std::endl;
		m_lhs->debugPrint(indent);
		debugPrintIndent(indent);
		switch (m_op) {
		case Simplexer::TokenType::PLUS:
			std::cout << "Binary operator: +" << std::endl;
			break;
		case Simplexer::TokenType::MINUS:
			std::cout << "Binary operator: -" << std::endl;
			break;
		case Simplexer::TokenType::ASTERISK:
			std::cout << "Binary operator: *" << std::endl;
			break;
		case Simplexer::TokenType::SLASH:
			std::cout << "Binary operator: /" << std::endl;
			break;
		default:
			std::cout << "Unknown binary operator" << std::endl;
			break;
		}
		m_rhs->debugPrint(indent);
		debugPrintIndent(indent);
		std::cout << ')' << std::endl;
	}

	// ============ Variable =======================

	void Variable::debugPrint(std::size_t indent)
	{
		debugPrintIndent(indent);
		std::cout << "Variable with name: " << m_name << std::endl;
	}

}