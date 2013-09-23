#include "ASTExpressionBuilder.h"

ASTExpressionBuilder::ASTExpressionBuilder(void)
{}

ASTExpressionBuilder::~ASTExpressionBuilder(void)
{}

ASTNode* ASTExpressionBuilder::build(std::string expression)
{
	if (expression.empty()) {
		throw ParseException("Unable to parse expression");
	}

	_expression.clear();
	_expression.str(expression);

	tokeniseExpression();

	return shuntingYardAlgorithm();
}

ASTNode* ASTExpressionBuilder::build(std::list<std::string> tokens)
{
	_tokens = tokens;

	if (_tokens.empty()) {
		throw ParseException("Unable to parse expression");
	}

	return shuntingYardAlgorithm();
}

void ASTExpressionBuilder::getToken()
{
	std::string token;

	while (_expression.good()) {
		if (isalnum(_expression.peek())) {
			token += _expression.get();
		} else if (ispunct(_expression.peek())) {
			if (token.empty()) {
				token += _expression.get();
			}

			break;
		} else if (isspace(_expression.peek())) {
			_expression.get();

			if (!token.empty()) {
				break;
			}
		}
	}

	_token = token;
}

void ASTExpressionBuilder::tokeniseExpression()
{
	_tokens.clear();

	getToken();

	while (_token != "") {
		_tokens.push_back(_token);

		getToken();
	}
}

bool ASTExpressionBuilder::isKeyword(std::string keyword)
{
	return _token == keyword;
}

bool ASTExpressionBuilder::isName()
{
	if (!isalpha(_token[0])) {
		return false;
	}

	for (size_t i = 1; i < _token.length(); i++) {
		if (!isalnum(_token[i])) {
			return false;
		}
	}

	return true;
}

bool ASTExpressionBuilder::isDigits()
{
	for (size_t i = 0; i < _token.size(); i++) {
		if (!isdigit(_token[i])) {
			return false;
		}
	}

	return true;
}

ASTNode* ASTExpressionBuilder::shuntingYardAlgorithm()
{
	_operators.clear();
	_results.clear();

	while (!_tokens.empty()) {
		_token = _tokens.front();
		_tokens.pop_front();

		if (isKeyword("+") || isKeyword("-") || isKeyword("*") || isKeyword("/")) {
			while (!_operators.empty() && getOprPriority(_token) <= getOprPriority(_operators.back())) {				
				buildOperators();
			}

			_operators.push_back(_token);
		} else if (isKeyword("(")) {
			_operators.push_back("(");
		} else if (isKeyword(")")) {
			while (!_operators.empty() && _operators.back() != "(") {				
				buildOperators();
			}

			if (_operators.empty()) {
				throw ParseException(_token, "Mismatched parentheses");
			}

			_operators.pop_back();
		} else if (isDigits() || isName()) {
			buildOperands();
		} else {
			throw ParseException(_token, "Unable to parse expression");
		}

		getToken();
	}

	while (!_operators.empty()) {
		if (_operators.back() == "(") {
			throw ParseException(_token, "Mismatched parentheses");
		}

		buildOperators();
	}

	ASTNode* expNode = _results.back();
	_results.pop_back();

	return expNode;
}


int ASTExpressionBuilder::getOprPriority(std::string operate)
{
	if (operate == "*" || operate == "/") {
		return 2;
	} else if (operate == "+" || operate == "-") {
		return 1;
	} else {
		return 0;	
	}
}

void ASTExpressionBuilder::buildOperators()
{
	ASTNode* operatorNode;
	ASTNode* leftNode;
	ASTNode* rightNode;

	ASTType type;

	if (_operators.back() == "+") {
		type = PLUS;
	} else if (_operators.back() == "-") {
		type = MINUS;
	} else if (_operators.back() == "*") {
		type = TIMES;
	}else if (_operators.back() == "/") {
		type = DIVIDE;
	}

	operatorNode = new ASTNode("", type, 0);

	if (!_results.empty()) {
		rightNode = _results.back();
		_results.pop_back();
	} else {
		throw ParseException(_token, "Unable to parse expression");
	}

	if (!_results.empty()) {
		leftNode = _results.back();
		_results.pop_back();
	} else {
		throw ParseException(_token, "Unable to parse expression");
	}

	operatorNode->joinChild(leftNode);
	leftNode->joinNext(rightNode);

	_results.push_back(operatorNode);

	_operators.pop_back();
}

void ASTExpressionBuilder::buildOperands()
{
	ASTType type;

	if (isDigits()) {
		type = CONSTANT;
	} else if (isName()) {
		type = VARIABLE;
	}

	_results.push_back(new ASTNode(_token, type, 0));
}