#include "Parser.h"

Parser::Parser(void)
{}

Parser::~Parser(void)
{}

PKB* Parser::parse(std::string fileName)
{
	_file.open(fileName);	
	
	PKB* pkb = new PKB();

	_stmtNum = 0;
	_ast = new AST();
	_varTable = new VarTable();
	_procTable = new ProcTable();

	getToken();

	_ast->setRootNode(program());

	pkb->setStmtNum(_stmtNum);
	pkb->setAST(_ast);
	pkb->setVarTable(_varTable);
	pkb->setProcTable(_procTable);

	return pkb;
}

void Parser::getToken()
{
	std::string token;

	while (_file.good()) {
		if (isalnum(_file.peek())) {
			token += _file.get();
		} else if (ispunct(_file.peek())) {
			if (token.empty()) {
				token += _file.get();
			}

			break;
		} else if (isspace(_file.peek())) {
			_file.get();

			if (!token.empty()) {
				break;
			}
		}
	}

	_token = token;
}

ASTNode* Parser::program()
{
	ASTNode* progNode = new ASTNode("Simple", PROGRAM, 0);

	ASTNode* procNode = procedure();

	_ast->joinChild(progNode, procNode);

	ASTNode* prevProcNode;

	while (isKeyword("procedure")) {
		prevProcNode = procNode;
		procNode = procedure();

		_ast->joinNext(prevProcNode, procNode);
	}

	return progNode;
}

ASTNode* Parser::procedure()
{
	matchKeyword("procedure");

	_procTable->addProcedure(_token);
	ASTNode* procNode = new ASTNode(_token, PROCEDURE, 0);
	matchName();

	matchKeyword("{");
	
	ASTNode* stmtListNode = statementList();
	
	matchKeyword("}");

	_ast->joinChild(procNode, stmtListNode);

	return procNode;
}

ASTNode* Parser::statementList()
{
	ASTNode* stmtListNode = new ASTNode("", STATEMENT_LIST, 0);

	ASTNode* stmtNode = statement();

	_ast->joinChild(stmtListNode, stmtNode);

	ASTNode* prevStmtNode;

	while (!isKeyword("}")) {
		prevStmtNode = stmtNode;
		stmtNode = statement();

		_ast->joinNext(prevStmtNode, stmtNode);
	}

	return stmtListNode;
}

ASTNode* Parser::statement()
{
	_stmtNum++;

	if (isKeyword("while")) {
		return whileStmt();
	}

	if (isKeyword("if")) {
		return ifStmt();
	}

	if (isKeyword("call")) {
		return callStmt();
	}

	if (isName()) {
		return assignStmt();
	}

	throw ParseException(_stmtNum, _token, "Unable to parse statements");
}

ASTNode* Parser::assignStmt()
{
	_varTable->addVariable(_token);
	ASTNode* varNode = new ASTNode(_token, VARIABLE, 0);
	matchName();

	matchKeyword("=");
	ASTNode* assignNode = new ASTNode("", ASSIGN, _stmtNum);

	ASTNode* expNode = expression();

	matchKeyword(";");

	_ast->joinChild(assignNode, varNode);
	_ast->joinNext(varNode, expNode);

	return assignNode;
}

ASTNode* Parser::whileStmt()
{
	matchKeyword("while");
	ASTNode* whileNode = new ASTNode("", WHILE, _stmtNum);

	_varTable->addVariable(_token);
	ASTNode* varNode = new ASTNode(_token, VARIABLE, 0);
	matchName();

	matchKeyword("{");

	ASTNode* stmtListNode = statementList();
	
	matchKeyword("}");

	_ast->joinChild(whileNode, varNode);
	_ast->joinNext(varNode, stmtListNode);

	return whileNode;
}

ASTNode* Parser::ifStmt()
{
	matchKeyword("if");
	ASTNode* ifNode = new ASTNode("", IF, _stmtNum);

	_varTable->addVariable(_token);
	ASTNode* varNode = new ASTNode(_token, VARIABLE, 0);
	matchName();

	matchKeyword("{");

	ASTNode* ifStmtListNode = statementList();

	matchKeyword("}");
	matchKeyword("else");
	matchKeyword("{");
	
	ASTNode* elseStmtListNode = statementList();

	matchKeyword("}");

	_ast->joinChild(ifNode, varNode);
	_ast->joinNext(varNode, ifStmtListNode);
	_ast->joinNext(ifStmtListNode, elseStmtListNode);

	return ifNode;
}

ASTNode* Parser::callStmt() {
	matchKeyword("call");

	ASTNode* callNode = new ASTNode(_token, CALL, _stmtNum);
	matchName();

	matchKeyword(";");

	return callNode;
}

ASTNode* Parser::expression()
{
	return shuntingYardAlgorithm();
}

bool Parser::isDigits()
{
	for (size_t i = 0; i < _token.size(); i++) {
		if (!isdigit(_token[i])) {
			return false;
		}
	}

	return true;
}

void Parser::matchDigits()
{
	if (isDigits()) {
		getToken();
	} else {
		throw ParseException(_stmtNum, _token, "Constant should contain only digits");
	}
}

bool Parser::isName()
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

void Parser::matchName()
{
	if (isName()) {
		getToken();
	} else {
		throw ParseException(_stmtNum, _token, "Name should contains only letters & digits with a letter as beginning");
	}
}

bool Parser::isKeyword(std::string keyword)
{
	return _token == keyword;
}

void Parser::matchKeyword(std::string keyword)
{
	if (isKeyword(keyword)) {
		getToken();
	} else {
		throw ParseException(_stmtNum, _token, "Token does not match with keyword \"" + keyword + "\"");
	}
}

int Parser::getOprPriority(std::string operate)
{
	if (operate == "*" || operate == "/") {
		return 2;
	} else if (operate == "+" || operate == "-") {
		return 1;
	} else {
		return 0;	
	}
}

ASTNode* Parser::shuntingYardAlgorithm() {
	std::stack<std::string> operators;
	std::stack<ASTNode*> results;

	ASTNode* operatorNode;
	ASTNode* leftNode;
	ASTNode* rightNode;

	ASTType type;

	while (!isKeyword(";")) {
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

				_ast->joinChild(operatorNode, leftNode);
				_ast->joinNext(leftNode, rightNode);

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

				_ast->joinChild(operatorNode, leftNode);
				_ast->joinNext(leftNode, rightNode);

				results.push(operatorNode);

				operators.pop();
			}

			if (operators.empty()) {
				throw ParseException(_stmtNum, _token, "Mismatched parentheses");
			}

			operators.pop();
		} else if (isDigits() || isName()) {
			if (isDigits()) {
				type = CONSTANT;
			} else if (isName()) {
				type = VARIABLE;

				_varTable->addVariable(_token);
			}

			results.push(new ASTNode(_token, type, 0));
		} else {
			throw ParseException(_stmtNum, _token, "Unable to parse expression");
		}

		getToken();
	}

	while (!operators.empty()) {
		if (operators.top() == "(") {
			throw ParseException(_stmtNum, _token, "Mismatched parentheses");
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

		_ast->joinChild(operatorNode, leftNode);
		_ast->joinNext(leftNode, rightNode);

		results.push(operatorNode);

		operators.pop();
	}

	ASTNode* expNode = results.top();
	results.pop();

	return expNode;
}