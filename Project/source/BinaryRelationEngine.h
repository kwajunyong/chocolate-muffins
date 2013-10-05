#pragma once
#include "QueryClass.h"

/* For you li 
==================
  How to use BinaryRelationEngine
  So when you have something like p.procName = "Yourock"

  Then BinaryRelationEngine bre * = new BinaryRelationEngine();
  bre->addParam("p", VT_PROCEDURE, "procName");
  bre->addParam("yourock", VT_CONSTANTSTRING);

  You have something like 
  var.VarName = callmecallme.procName

  bre->addParam("var", VT_VARIABLELIST, "varName");
  bre->addParam("callmecallme", VT_CALL,  "procName");
*/

class BinaryRelationEngine: public QueryClass {
public:
	BinaryRelationEngine(QueryManager* qm, PKB *pkb);
	void addParam(const string &parameterName, VARIABLETYPE parameterType, const string &attribute);
	void addParam(const string &parameterName, VARIABLETYPE parameterType);
	void run();

private:
	vector<string> attributePair;

};