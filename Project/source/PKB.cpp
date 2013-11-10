#include "PKB.h"

PKB::PKB(void)
{
	_traverser = new ASTTraverser();
	_matcher = new ASTMatcher();
	_exprBuilder = new ASTExpressionBuilder();

	_ast = NULL;
	
	_varTable = NULL;
	_procTable = NULL;
	
	_follows = NULL;
	_parent = NULL;
	
	_modifies = NULL;
	_uses = NULL;
	
	_calls = NULL;
	_next = NULL;
	_affects = NULL;

	_numOfStmt = 0;
	//_stats = NULL;
}

PKB::~PKB(void)
{}

AST* PKB::getAST()
{
	return _ast;
}

void PKB::setAST(AST* ast)
{
	_ast = ast;
}

ASTTraverser* PKB::getASTTraverser()
{
	return _traverser;
}

ASTMatcher* PKB::getASTMatcher()
{
	return _matcher;
}

ASTExpressionBuilder* PKB::getASTExpressionBuilder()
{
	return _exprBuilder;
}

VarTable* PKB::getVarTable()
{
	return _varTable;
}

void PKB::setVarTable(VarTable* varTable)
{
	_varTable = varTable;
}

ProcTable* PKB::getProcTable()
{
	return _procTable;
}

void PKB::setProcTable(ProcTable* procTable)
{
	_procTable = procTable;
}

ConstTable* PKB::getConstTable()
{
	return _constTable;
}

void PKB::setConstTable(ConstTable* constTable)
{
	_constTable = constTable;
}

Follows* PKB::getFollows()
{
	return _follows;
}

void PKB::setFollows(Follows* follows)
{
	_follows = follows;
}

Parent* PKB::getParent()
{
	return _parent;
}

void PKB::setParent(Parent* parent)
{
	_parent = parent;
}

Modifies* PKB::getModifies()
{
	return _modifies;
}

void PKB::setModifies(Modifies* modifies)
{
	_modifies = modifies;
}

Uses* PKB::getUses()
{
	return _uses;
}

void PKB::setUses(Uses* uses)
{
	_uses = uses;
}

Calls* PKB::getCalls()
{
	return _calls;
}

void PKB::setCalls(Calls* calls)
{
	_calls = calls;
}

Next* PKB::getNext()
{
	return _next;
}

void PKB::setNext(Next* next)
{
	_next = next;
}

Affects* PKB::getAffects()
{
	return _affects;
}

void PKB::setAffects(Affects* affects)
{
	_affects = affects;
}

int PKB::getNumOfStmt()
{
	return _numOfStmt;
}

void PKB::setNumOfStmt(int numOfStmt)
{
	_numOfStmt = numOfStmt;
}

Stats* PKB::getStats()
{
	return _stats;
}

void PKB::setStats(Stats* stats)
{
	_stats = stats;
}

void PKB::extract()
{
	int i = 0;
	int j = 0;
	std::pair<int, int> range;
	std::vector<int> intResults;
	std::vector<std::string> strResults;
	std::vector<ASTNode*> nodeResults;

	mkdir("PKB");
	std::ofstream ast("PKB/AST.txt", std::ofstream::out | ios::trunc);
	std::ofstream astStmtNum("PKB/ASTStmtNum.txt", std::ofstream::out | ios::trunc);
	std::ofstream astContainer("PKB/ASTContainers.txt", std::ofstream::out | ios::trunc);
	std::ofstream follows("PKB/Follows.txt", std::ofstream::out | ios::trunc);
	std::ofstream followsStar("PKB/FollowsStar.txt", std::ofstream::out | ios::trunc);
	std::ofstream parent("PKB/Parent.txt", std::ofstream::out | ios::trunc);
	std::ofstream parentStar("PKB/ParentStar.txt", std::ofstream::out | ios::trunc);
	std::ofstream modifies("PKB/Modifies.txt", std::ofstream::out | ios::trunc);
	std::ofstream uses("PKB/Uses.txt", std::ofstream::out | ios::trunc);
	std::ofstream calls("PKB/Calls.txt", std::ofstream::out | ios::trunc);
	std::ofstream callsStar("PKB/CallsStar.txt", std::ofstream::out | ios::trunc);
	std::ofstream callsStmt("PKB/CallsStmt.txt", std::ofstream::out | ios::trunc);
	std::ofstream next("PKB/Next.txt", std::ofstream::out | ios::trunc);
	std::ofstream nextStar("PKB/NextStar.txt", std::ofstream::out | ios::trunc);
	std::ofstream affects("PKB/Affects.txt", std::ofstream::out | ios::trunc);
	std::ofstream affectsStar("PKB/AffectsStar.txt", std::ofstream::out | ios::trunc);
	std::ofstream varTable("PKB/VarTable.txt", std::ofstream::out | ios::trunc);
	std::ofstream procTable("PKB/ProcTable.txt", std::ofstream::out | ios::trunc);
	std::ofstream constTable("PKB/ConstTable.txt", std::ofstream::out | ios::trunc);
	
	strResults = _varTable->getAllNames();

	for (j = 0; j < strResults.size(); j++) {
		varTable << strResults[j] << ", ";
	}

	intResults = _constTable->getAllValues();

	for (j = 0; j < intResults.size(); j++) {
		constTable << intResults[j] << ", ";
	}

	strResults = _traverser->traverse(_ast->getRootNode());

	for (j = 0; j < strResults.size(); j++) {
		ast << strResults[j] << endl;
	}

	intResults = _ast->getStatementNumbers(ASSIGN);

	astStmtNum << "ASSIGN" << endl;

	for (j = 0; j < intResults.size(); j++) {
		astStmtNum << intResults[j] << ", ";
	}

	astStmtNum << endl << endl;

	intResults = _ast->getStatementNumbers(WHILE);

	astStmtNum << "WHILE" << endl;

	for (j = 0; j < intResults.size(); j++) {
		astStmtNum << intResults[j] << ", ";
	}

	astStmtNum << endl << endl;

	intResults = _ast->getStatementNumbers(IF);

	astStmtNum << "IF" << endl;

	for (j = 0; j < intResults.size(); j++) {
		astStmtNum << intResults[j] << ", ";
	}

	astStmtNum << endl << endl;

	intResults = _ast->getStatementNumbers(CALL);

	astStmtNum << "CALL" << endl;

	for (j = 0; j < intResults.size(); j++) {
		astStmtNum << intResults[j] << ", ";
	}

	astStmtNum << endl << endl;

	for (i = 1; i <= _numOfStmt; i++) {
		intResults = _follows->getFollowedBy(i, false);

		for (j = 0; j < intResults.size(); j++) {
			follows << i << "," << intResults[j] << endl;
		}
	}

	for (i = 1; i <= _numOfStmt; i++) {
		intResults = _follows->getFollowedBy(i, true);

		for (j = 0; j < intResults.size(); j++) {
			followsStar << i << "," << intResults[j] << endl;
		}
	}

	for (i = 1; i <= _numOfStmt; i++) {
		intResults = _parent->getChild(i, false);

		for (j = 0; j < intResults.size(); j++) {
			parent << i << "," << intResults[j] << endl;
		}
	}

	for (i = 1; i <= _numOfStmt; i++) {
		intResults = _parent->getChild(i, true);

		for (j = 0; j < intResults.size(); j++) {
			parentStar << i << "," << intResults[j] << endl;
		}
	}

	for (i = 1; i <= _numOfStmt; i++) {
		strResults = _modifies->getModifiedVar(i);

		for (j = 0; j < strResults.size(); j++) {
			modifies << i << "," << strResults[j] << endl;
		}
	}

	for (i = 1; i <= _numOfStmt; i++) {
		strResults = _uses->getUsedVar(i);

		for (j = 0; j < strResults.size(); j++) {
			uses << i << "," << strResults[j] << endl;
		}
	}

	for (i = 1; i <= _numOfStmt; i++) {
		intResults = _next->getNext(i, false);

		for (j = 0; j < intResults.size(); j++) {
			next << i << "," << intResults[j] << endl;
		}
	}

	for (i = 1; i <= _numOfStmt; i++) {
		intResults = _next->getNext(i, true);

		for (j = 0; j < intResults.size(); j++) {
			nextStar << i << "," << intResults[j] << endl;
		}
	}

	for (i = 1; i <= _numOfStmt; i++) {
		intResults = _affects->getAffects(i);

		for (j = 0; j < intResults.size(); j++) {
			affects << i << "," << intResults[j] << endl;
		}
	}

	for (i = 1; i <= _numOfStmt; i++) {
		intResults = _affects->getAffectsStar(i);

		for (j = 0; j < intResults.size(); j++) {
			affectsStar << i << "," << intResults[j] << endl;
		}
	}

	std::vector<std::string> variable = _varTable->getAllNames();

	for (i = 0; i < variable.size(); i++) {
		intResults = _ast->getStatementNumbers(WHILE, variable[i]);

		for (j = 0; j < intResults.size(); j++) {
			astContainer << "WHILE " << variable[i] << " " << intResults[j] << endl;
		}
	}

	for (i = 0; i < variable.size(); i++) {
		intResults = _ast->getStatementNumbers(IF, variable[i]);

		for (j = 0; j < intResults.size(); j++) {
			astContainer << "IF " << variable[i] << " " << intResults[j] << endl;
		}
	}

	std::vector<std::string> procedure = _procTable->getAllNames();

	for (i = 0; i < procedure.size(); i++) {
		range = _procTable->getRange(procedure[i]);

		procTable << procedure[i] << endl;
	}

	for (i = 0; i < procedure.size(); i++) {
		strResults = _modifies->getModifiedVar(procedure[i]);

		for (j = 0; j < strResults.size(); j++) {
			modifies << procedure[i] << "," << strResults[j] << endl;
		}
	}

	for (i = 0; i < procedure.size(); i++) {
		strResults = _uses->getUsedVar(procedure[i]);

		for (j = 0; j < strResults.size(); j++) {
			uses << procedure[i] << "," << strResults[j] << endl;
		}
	}

	for (i = 0; i < procedure.size(); i++) {
		strResults = _calls->getCalls(procedure[i], false);

		for (j = 0; j < strResults.size(); j++) {
			calls << procedure[i] << "," << strResults[j] << endl;
		}
	}

	for (i = 0; i < procedure.size(); i++) {
		strResults = _calls->getCalls(procedure[i], true);

		for (j = 0; j < strResults.size(); j++) {
			callsStar << procedure[i] << "," << strResults[j] << endl;
		}
	}

	for (i = 0; i < procedure.size(); i++) {
		intResults = _calls->getCallsStmt(procedure[i]);

		for (j = 0; j < intResults.size(); j++) {
			callsStmt << intResults[j] << "," << procedure[i] << endl;
		}
	}
}