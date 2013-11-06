#pragma once
#include <string>
#include <map>

typedef std::pair<std::string, std::string> VectorRelation;
typedef std::map<std::string, bool> FastSearchString;
typedef std::map<int, bool> FastSearchInteger;

enum PARAMETERSTATUS {
	  UNINITIALIZED, 
	  LOADED	  
};
enum QUERYTYPE {
  QT_NEXT, 
  QT_NEXTSTAR, 
  QT_AFFECT, 
  QT_AFFECTSTAR, 
  QT_PARENT,
  QT_PARENTSTAR,
  QT_FOLLOWS,
  QT_FOLLOWSSTAR,
  QT_CALLS, 
  QT_CALLSSTAR, 
  QT_USES,
  QT_MODIFIES,
  QT_IFPATTERN,
  QT_WHILEPATTERN,
  QT_BINARYRELATION,
  QT_EXPRESSIONPATTERN
};

enum VARIABLETYPE {
	VT_PROG_LINE,
	VT_ASSIGNMENT, 
  VT_CONSTANTINTEGER, 
  VT_CONSTANTSTRING, 
  VT_WHILE, 
  VT_IF, 
  VT_PROCEDURE, 
  VT_STATEMENTLIST, 
  VT_VARIABLELIST, // Variable 
  VT_CALL, 
  VT_UNDERSCORE, 
  VT_EXPRESSION_UNDERSCORE, // Used for pattern matching. 
  VT_CONSTANT
};
