#include "ExpressionParser.h"

ExpressionParser::ExpressionParser(void)
{}

ExpressionParser::~ExpressionParser(void)
{}

ASTNode* ExpressionParser::parse(std::string expression)
{
	_expression.clear();
	_expression.str(expression);

	getToken();

	return shuntingYardAlgorithm();
}

void ExpressionParser::getToken()
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

int ExpressionParser::getOprPriority(std::string operate)
{
	if (operate == "*" || operate == "/") {
		return 2;
	} else if (operate == "+" || operate == "-") {
		return 1;
	} else {
		return 0;	
	}
}

bool ExpressionParser::isKeyword(std::string keyword)
{
	return _token == keyword;
}

bool ExpressionParser::isName()
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

bool ExpressionParser::isDigits()
{
	for (size_t i = 0; i < _token.size(); i++) {
		if (!isdigit(_token[i])) {
			return false;
		}
	}

	return true;
}

ASTNode* ExpressionParser::shuntingYardAlgorithm()
{
	std::stack<std::string> operators;
	std::stack<ASTNode*> results;

	ASTNode* operatorNode;
	ASTNode* leftNode;
	ASTNode* rightNode;

	ASTType type;

	while (_token != "") {
		 if (isKeyword("+") || isKeyword("-") || isKeyword("*") || isKeyword("/")) {
			while (!operators.empty() && getOprPriority(_token) <= getOprPriority(operators.top())) {				
				if (operators.top() == "+") {
					type = PLUS;
				} else if (operators.top() == "-") {
					type = MINUS;
				} else if (operators.top() == "*") {
					type = TIMES;
				}else if (operators.top() == "/") {
					type = DIVIDE;
				}

				operatorNode = new ASTNode("", type, 0);

				rightNode = results.top();
				results.pop();
				
				leftNode = results.top();
				results.pop();

				operatorNode->joinChild(leftNode);
				leftNode->joinNext(rightNode);

				results.push(operatorNode);
				
				operators.pop();
			}

			operators.push(_token);
		} else if (isKeyword("(")) {
			operators.push("(");
		} else if (isKeyword(")")) {
			while (!operators.empty() && operators.top() != "(") {				
				if (operators.top() == "+") {
					type = PLUS;
				} else if (operators.top() == "-") {
					type = MINUS;
				} else if (operators.top() == "*") {
					type = TIMES;
				}else if (operators.top() == "/") {
					type = DIVIDE;
				}

				operatorNode = new ASTNode("", type, 0);

				rightNode = results.top();
				results.pop();
				
				leftNode = results.top();
				results.pop();

				operatorNode->joinChild(leftNode);
				leftNode->joinNext(rightNode);

				results.push(operatorNode);

				operators.pop();
			}

			if (operators.empty()) {
				throw ParseException(_token, "Mismatched parentheses");
			}

			operators.pop();
		} else if (isDigits() || isName()) {
			if (isDigits()) {
				type = CONSTANT;
			} else if (isName()) {
				type = VARIABLE;
			}

			results.push(new ASTNode(_token, type, 0));
		} else {
			throw ParseException(_token, "Unable to parse expression");
		}

		getToken();
	}

	while (!operators.empty()) {
		if (operators.top() == "(") {
			throw ParseException(_token, "Mismatched parentheses");
		}
				
		if (operators.top() == "+") {
			type = PLUS;
		} else if (operators.top() == "-") {
			type = MINUS;
		} else if (operators.top() == "*") {
			type = TIMES;
		}else if (operators.top() == "/") {
			type = DIVIDE;
		}

		operatorNode = new ASTNode("", type, 0);

		rightNode = results.top();
		results.pop();
				
		leftNode = results.top();
		results.pop();

		operatorNode->joinChild(leftNode);
		leftNode->joinNext(rightNode);

		results.push(operatorNode);

		operators.pop();
	}

	ASTNode* expNode = results.top();
	results.pop();

	return expNode;
}