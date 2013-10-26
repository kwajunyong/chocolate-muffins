#include "DesignExtractor.h"

DesignExtractor::DesignExtractor(void)
{}

DesignExtractor::~DesignExtractor(void)
{}

void DesignExtractor::extract(PKB* pkb)
{
	_pkb = pkb;

	_ast = _pkb->getAST();
	_varTable = _pkb->getVarTable();
	_procTable = _pkb->getProcTable();
	_numOfStmt = _pkb->getNumOfStmt();
	
	ASTNode* rootNode = _pkb->getAST()->getRootNode();
	
	_follows = new Follows();
	_parent = new Parent();
	_modifies = new Modifies(_numOfStmt, _varTable, _procTable);
	_uses = new Uses(_numOfStmt, _varTable, _procTable);
	_calls = new Calls();
	_next = new Next();
	//_stats = new Stats(_procTable, _numOfStmt);
	_affects = new Affects(_ast, _modifies, _uses, _next, _procTable, _numOfStmt);

	std::vector<int> statements;
	std::string procedure = "";

	traverseAST(rootNode, statements, procedure);

	pkb->setFollows(_follows);
	pkb->setParent(_parent);
	pkb->setModifies(_modifies);
	pkb->setUses(_uses);
	pkb->setCalls(_calls);
	pkb->setNext(_next);
	pkb->setAffects(_affects);
	//pkb->setStats(_stats);

	traverseCalls();
	extractFromCallNodes();
}

void DesignExtractor::traverseAST(ASTNode* node, std::vector<int> statements, std::string procedure)
{
	while (node != NULL) {
		updateStatements(node, statements);
		updateProcedure(node, procedure);
		
		extractStatementNodes(node);

		extractFollows(node);
		extractParent(node);

		extractModifies(node, statements, procedure);
		extractUses(node, statements, procedure);

		extractCalls(node, procedure);
		extractNext(node);

		//extractStats(node, statements, procedure);

		if (node->getChild() != NULL) {
			traverseAST(node->getChild(), statements, procedure);
		}

		node = node->getNext();
	}
}

void DesignExtractor::updateStatements(ASTNode* node, std::vector<int> &statements)
{
	if (isStatement(node)) {
		if (!isFirstChild(node) && !statements.empty()) {
			statements.pop_back();
		}

		statements.push_back(node->getStatementNumber());
	}
}

void DesignExtractor::updateProcedure(ASTNode* node, std::string &procedure)
{
	if (node->getType() == PROCEDURE) {
		procedure = node->getName();
	}
}

void DesignExtractor::extractStatementNodes(ASTNode* node)
{
	if (isStatement(node)) {
		//std::cout << node->print() << std::endl;
		_ast->storeStatementNode(node);
	}
}

void DesignExtractor::extractFollows(ASTNode* node)
{
	if (isFollows(node)) {
		//std::cout << "Follows(" << node->getStatementNumber() << ", " << node->getNext()->getStatementNumber() << ")" << std::endl;
		_follows->addFollows(node->getStatementNumber(), node->getNext()->getStatementNumber());
	}
}

void DesignExtractor::extractParent(ASTNode* node)
{
	if (isParent(node)) {
		//std::cout << "Parent(" << node->getParent()->getParent()->getStatementNumber() << ", " << node->getStatementNumber() << ")" << std::endl;
		_parent->addParent(node->getParent()->getParent()->getStatementNumber(), node->getStatementNumber());
	}
}

void DesignExtractor::extractModifies(ASTNode* node, std::vector<int> statements, std::string procedure)
{
	if (isModifies(node)) {
		for (size_t i=0; i<statements.size(); i++) {
			//std::cout << "Modifies(" << statements[i] << ", " << node->getName() << ")" << std::endl;
			_modifies->addModifiesStmt(statements[i], node->getName());
		}

		//std::cout << "Modifies(" << procedure << ", " << node->getName() << ")" << std::endl;
		_modifies->addModifiesProc(procedure, node->getName());
	}
}

void DesignExtractor::extractUses(ASTNode* node, std::vector<int> statements, std::string procedure)
{
	if (isUses(node)) {
		for (size_t i=0; i<statements.size(); i++) {
			//std::cout << "Uses(" << statements[i] << ", " << node->getName() << ")" << std::endl;
			_uses->addUsesStmt(statements[i], node->getName());
		}

		//std::cout << "Uses(" << procedure << ", " << node->getName() << ")" << std::endl;
		_uses->addUsesProc(procedure, node->getName());
	}
}

void DesignExtractor::extractCalls(ASTNode* node, std::string procedure)
{
	if (node->getType() == CALL) {
		validateCall(node);
			
		//std::cout << "Calls(" << procedure << ", " << node->getName() << ", "  << node->getStatementNumber() << ")" << std::endl;
		_calls->addCalls(procedure, node->getName(), node->getStatementNumber());

		_callNodes.push_back(node);
	}
}

void DesignExtractor::extractNext(ASTNode* node)
{
	if (isStatement(node)) {
		// Last child - Assign/Call/While
		if (node->getType() != IF && isLastChild(node)) {
			ASTNode* parent = node->getParent()->getParent();

			while (isStatement(parent)) {
				if (parent->getType() == IF && parent->getNext() != NULL) {
					//std::cout << "Next(" << node->getStatementNumber() << ", " << parent->getNext()->getStatementNumber() << ")" << std::endl;
					_next->addNext(node->getStatementNumber(), parent->getNext()->getStatementNumber());
					break;
				}
				
				if (parent->getType() == WHILE) {
					//std::cout << "Next(" << node->getStatementNumber() << ", " << parent->getStatementNumber() << ")" << std::endl;
					_next->addNext(node->getStatementNumber(), parent->getStatementNumber());
					break;
				}

				parent = parent->getParent()->getParent();
			}
		}
		
		// Parent
		if (node->getType() == IF || node->getType() == WHILE) {
			ASTNode* stmtListNode = node->getChild()->getNext();

			while (stmtListNode != NULL) {
				//std::cout << "Next(" << node->getStatementNumber() << ", " << stmtListNode->getChild()->getStatementNumber() << ")" << std::endl;
				_next->addNext(node->getStatementNumber(), stmtListNode->getChild()->getStatementNumber());

				stmtListNode = stmtListNode->getNext();
			}
		}

		// Follows
		if ((node->getType() == ASSIGN || node->getType() == CALL || node->getType() == WHILE) && !isLastChild(node)) {
			//std::cout << "Next(" << node->getStatementNumber() << ", " << node->getNext()->getStatementNumber() << ")" << std::endl;
			_next->addNext(node->getStatementNumber(), node->getNext()->getStatementNumber());
		}
	}
}

//void DesignExtractor::extractStats(ASTNode* node, std::vector<int> statements, std::string procedure)
//{
//	if (isStatement(node)) {
//		_stats->addNumOfStmt(procedure, node->getType());
//
//		for (size_t i=0; i<statements.size(); i++) {
//			_stats->setLevel(statements[i], statements.size() - i);
//		}
//	}
//}

std::vector<int> DesignExtractor::processIfNode(ASTNode* node)
{
	std::vector<int> results;

	process(node->getChild(), results);

	return results;
}

void DesignExtractor::process(ASTNode* node, std::vector<int> &results)
{
	while (node != NULL) {
		if (isLastChild(node) && isStatement(node) && node->getType() != IF) {
			results.push_back(node->getStatementNumber());
		}

		if (isLastChild(node) && node->getType() == IF) {
			process(node->getChild(), results);
		}

		node = node->getNext();
	}
}

void DesignExtractor::validateCall(ASTNode* node)
{
	if (_procTable->getIndex(node->getName()) < 0) {
		throw ParseException(node->getStatementNumber(), node->getName(), "Called procedure does not exist");
	}
}

void DesignExtractor::traverseCalls()
{
	std::vector<std::pair<std::string, std::string>> calls;
	std::vector<int> visited(_procTable->getSize(), 0);

	for (int i = 0; i < _procTable->getSize(); i++) {
		if (visited[i] == 0) {
			traverseCalls(_procTable->getName(i), visited, calls);
		}
	}

	while (!calls.empty()) {
		//std::cout << "Calls(" << calls.back().first << ", " << calls.back().second << ")" << std::endl;
		extractModifiesFromCall(calls.back());
		extractUsesFromCall(calls.back());
		
		calls.pop_back();
	}
}

void DesignExtractor::traverseCalls(std::string procedure, std::vector<int> &visited, std::vector<std::pair<std::string, std::string>> &calls)
{
	visited[_procTable->getIndex(procedure)] = 1;

	std::vector<std::string> calledProc = _calls->getCalled(procedure, false);

	for (size_t i = 0; i < calledProc.size(); i++) {
		if (visited[_procTable->getIndex(calledProc[i])] == 0) {
			traverseCalls(calledProc[i], visited, calls);
		} else if (visited[_procTable->getIndex(calledProc[i])] == 1) {
			throw ParseException("call " + procedure, "Recursive procedure call");
		}
	}

	visited[_procTable->getIndex(procedure)] = 2;

	for (size_t i = 0; i < calledProc.size(); i++) {
		calls.push_back(make_pair<std::string, std::string>(calledProc[i], procedure));
	}
}

void DesignExtractor::extractModifiesFromCall(std::pair<std::string, std::string> call)
{
	std::vector<std::string> variables = _modifies->getModifiedVar(call.second);

	for (size_t i=0; i<variables.size(); i++) {
		//std::cout << "Modifies(" << call.first << ", " << variables[i] << ")" << std::endl;
		_modifies->addModifiesProc(call.first, variables[i]);
	}
}

void DesignExtractor::extractUsesFromCall(std::pair<std::string, std::string> call)
{
	std::vector<std::string> variables = _uses->getUsedVar(call.second);

	for (size_t i=0; i<variables.size(); i++) {
		//std::cout << "Uses(" << call.first << ", " << variables[i] << ")" << std::endl;
		_uses->addUsesProc(call.first, variables[i]);
	}
}

void DesignExtractor::extractFromCallNodes()
{
	extractModifiesFromCallNodes();
	extractUsesFromCallNodes();

	_callNodes.clear();
}

void DesignExtractor::extractModifiesFromCallNodes()
{
	ASTNode* node;
	std::vector<std::string> variables;

	for (size_t i = 0; i < _callNodes.size(); i++) {
		node = _callNodes[i];
		
		variables = _modifies->getModifiedVar(node->getName());

		while (isStatement(node)) {
			for (size_t j = 0; j < variables.size(); j++) {
				//std::cout << "Modifies(" << node->getStatementNumber() << ", " << variables[j] << ")" << std::endl;
				_modifies->addModifiesStmt(node->getStatementNumber(), variables[j]);
			}

			node = node->getParent()->getParent();
		}
	}
}

void DesignExtractor::extractUsesFromCallNodes()
{
	ASTNode* node;
	std::vector<std::string> variables;

	for (size_t i = 0; i < _callNodes.size(); i++) {
		node = _callNodes[i];
		
		variables = _uses->getUsedVar(node->getName());

		while (isStatement(node)) {
			for (size_t j = 0; j < variables.size(); j++) {
				//std::cout << "Uses(" << node->getStatementNumber() << ", " << variables[j] << ")" << std::endl;
				_uses->addUsesStmt(node->getStatementNumber(), variables[j]);
			}

			node = node->getParent()->getParent();
		}
	}
}

bool DesignExtractor::isStatement(ASTNode* node)
{
	return node->getType() == ASSIGN || node->getType() == WHILE || node->getType() == IF || node->getType() == CALL;
}

bool DesignExtractor::isFirstChild(ASTNode* node)
{
	return node->getPrevious() == NULL;
}

bool DesignExtractor::isLastChild(ASTNode* node)
{
	return node->getNext() == NULL;
}

bool DesignExtractor::isFollows(ASTNode* node)
{
	return isStatement(node) && node->getNext() != NULL;
}

bool DesignExtractor::isParent(ASTNode* node)
{
	return isStatement(node) && isStatement(node->getParent()->getParent());
}

bool DesignExtractor::isModifies(ASTNode* node)
{
	return node->getType() == VARIABLE && node->getParent()->getType() == ASSIGN && isFirstChild(node); 
}

bool DesignExtractor::isUses(ASTNode* node)
{
	if (node->getType() == VARIABLE) {
		if ((node->getParent()->getType() == WHILE || node->getParent()->getType() == IF) && isFirstChild(node)) {
			return true;
		}

		if (node->getParent()->getType() == ASSIGN && isFirstChild(node)) {
			return false;
		}

		return true;
	}

	return false;
}