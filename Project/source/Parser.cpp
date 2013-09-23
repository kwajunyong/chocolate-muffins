#include "Parser.h"

Parser::Parser(void)
{}

Parser::~Parser(void)
{}

PKB* Parser::parse(std::string fileName)
{
	openFile(fileName);

	_pkb = new PKB();

	_stmtNum = 0;
	_ast = new AST();
	_varTable = new VarTable();
	_procTable = new ProcTable();

	getToken();

	ASTNode* rootNode = program();
	
	_ast->setRootNode(rootNode);

	_pkb->setNumOfStmt(_stmtNum);
	_pkb->setAST(_ast);
	_pkb->setVarTable(_varTable);
	_pkb->setProcTable(_procTable);

	checkRedundantToken();

	closeFile();

	return _pkb;
}

void Parser::openFile(std::string fileName)
{
	closeFile();

	_file.open(fileName);

	if (_file.fail()) {
		throw ParseException(fileName, "Unable to find/open file");
	}
}

void Parser::closeFile()
{
	if (_file.is_open()) {
		_file.close();
	}
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

	progNode->joinChild(procNode);

	ASTNode* prevProcNode;

	while (isKeyword("procedure")) {
		prevProcNode = procNode;
		procNode = procedure();

		prevProcNode->joinNext(procNode);
	}

	return progNode;
}

ASTNode* Parser::procedure()
{
	matchKeyword("procedure");

	if (_procTable->addProcedure(_token) == false) {
		throw ParseException(_stmtNum, _token, "Duplicate procedure names");
	}

	ASTNode* procNode = new ASTNode(_token, PROCEDURE, 0);
	matchName();

	matchKeyword("{");
	
	ASTNode* stmtListNode = statementList();
	
	matchKeyword("}");

	procNode->joinChild(stmtListNode);

	return procNode;
}

ASTNode* Parser::statementList()
{
	ASTNode* stmtListNode = new ASTNode("", STATEMENT_LIST, 0);

	ASTNode* stmtNode = statement();

	stmtListNode->joinChild(stmtNode);

	ASTNode* prevStmtNode;

	while (!isKeyword("}")) {
		prevStmtNode = stmtNode;
		stmtNode = statement();

		prevStmtNode->joinNext(stmtNode);
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

	throw ParseException(_stmtNum, _token, "Unable to parse statement");
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

	assignNode->joinChild(varNode);
	varNode->joinNext(expNode);

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

	whileNode->joinChild(varNode);
	varNode->joinNext(stmtListNode);

	return whileNode;
}

ASTNode* Parser::ifStmt()
{
	matchKeyword("if");
	ASTNode* ifNode = new ASTNode("", IF, _stmtNum);

	_varTable->addVariable(_token);
	ASTNode* varNode = new ASTNode(_token, VARIABLE, 0);
	matchName();

	matchKeyword("then");
	matchKeyword("{");

	ASTNode* ifStmtListNode = statementList();

	matchKeyword("}");
	matchKeyword("else");
	matchKeyword("{");
	
	ASTNode* elseStmtListNode = statementList();

	matchKeyword("}");

	ifNode->joinChild(varNode);
	varNode->joinNext(ifStmtListNode);
	ifStmtListNode->joinNext(elseStmtListNode);

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
	std::list<std::string> tokens = getExpressionTokens();

	ASTNode* expNode;

	try {
		expNode = _pkb->getASTExpressionBuilder()->build(tokens);
	} catch (ParseException pe) {
		pe.setStatementNumber(_stmtNum);

		throw pe;
	}

	return expNode;
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

void Parser::checkRedundantToken()
{
	if (!isKeyword("")) {
		throw ParseException(_stmtNum, _token, "Unnecessary token");
	}
}

std::list<std::string> Parser::getExpressionTokens()
{
	std::list<std::string> tokens;

	while (!isKeyword(";")) {
		if (isKeyword("(") || isKeyword(")")) {
			tokens.push_back(_token);
		} else if (isKeyword("+") || isKeyword("-") || isKeyword("*") || isKeyword("/")) {
			tokens.push_back(_token);
		} else if (isDigits()) {
			tokens.push_back(_token);
		} else if (isName()) {
			_varTable->addVariable(_token);
			
			tokens.push_back(_token);
		} else {
			throw ParseException(_stmtNum, _token, "Unable to parse expression");
		}
		
		getToken();
	}

	return tokens;
}