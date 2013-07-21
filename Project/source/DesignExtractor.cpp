#include "DesignExtractor.h"

DesignExtractor::DesignExtractor(void)
{}

DesignExtractor::~DesignExtractor(void)
{}

void DesignExtractor::extract(PKB* pkb)
{
	_pkb = pkb;

	ASTNode* rootNode = _pkb->getAST()->getRootNode();

	_varTable = _pkb->getVarTable();
	_procTable = _pkb->getProcTable();

	_numOfStmt = _pkb->getNumOfStmt();

	_follows = new Follows();
	_parent = new Parent();

	_modifies = new Modifies(_numOfStmt, _varTable, _procTable);
	_uses = new Uses(_numOfStmt, _varTable, _procTable);

	std::vector<int> statements;
	std::string procedure = "";

	traverseAndExtract(rootNode, statements, procedure, 0);

	pkb->setFollows(_follows);
	pkb->setParent(_parent);
	pkb->setModifies(_modifies);
	pkb->setUses(_uses);
}

void DesignExtractor::traverseAndExtract(ASTNode* node, std::vector<int> statements, std::string procedure, int prevLine)
{
	while (node != NULL) {		
		updateStatements(node, statements);
		updateProcedure(node, procedure);
		
		extractFollows(node);
		extractParent(node);

		extractModifies(node, statements, procedure);
		extractUses(node, statements, procedure);

		extractCalls(node, procedure);

		if (node->getChild() != NULL) {
			traverseAndExtract(node->getChild(), statements, procedure, prevLine);
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
		for (int i=0; i<statements.size(); i++) {
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
		for (int i=0; i<statements.size(); i++) {
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
			
		//std::cout << "Calls(" << procedure << ", " << node->getName() << ")" << std::endl;

		_calls.push_back(node);
	}
}

//void DesignExtractor::extractModifiesFromCallNodes()
//{
//	ASTNode* node;
//	std::vector<std::string> variables;
//
//	for (int i = 0; i < _calls.size(); i++) {
//		node = _calls[i];
//		
//		variables = _modifies->getModifiedVar(node->getName());
//
//		while (isStatement(node)) {
//			for (int j = 0; j < variables.size(); j++) {
//				//std::cout << "Modifies(" << node->getStatementNumber() << ", " << variables[j] << ")" << std::endl;
//				_modifies->addModifiesStmt(node->getStatementNumber(), variables[j]);
//			}
//
//			node = node->getParent()->getParent();
//		}
//	}
//}
//
//void DesignExtractor::extractUsesFromCallNodes()
//{
//	ASTNode* node;
//	std::vector<std::string> variables;
//
//	for (int i = 0; i < _calls.size(); i++) {
//		node = _calls[i];
//		
//		variables = _uses->getUsedVar(node->getName());
//
//		while (isStatement(node)) {
//			for (int j = 0; j < variables.size(); j++) {
//				//std::cout << "Uses(" << node->getStatementNumber() << ", " << variables[j] << ")" << std::endl;
//				_uses->addUsesStmt(node->getStatementNumber(), variables[j]);
//			}
//
//			node = node->getParent()->getParent();
//		}
//	}
//}

bool DesignExtractor::isStatement(ASTNode* node)
{
	return node->getType() == ASSIGN || node->getType() == WHILE || node->getType() == IF || node->getType() == CALL;
}

bool DesignExtractor::isFirstChild(ASTNode* node)
{
	return node->getPrevious() == NULL;
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

void DesignExtractor::validateCall(ASTNode* node)
{
	if (_procTable->getIndex(node->getName()) < 0) {
		throw ParseException(node->getStatementNumber(), node->getName(), "Called procedure does not exist");
	}
}