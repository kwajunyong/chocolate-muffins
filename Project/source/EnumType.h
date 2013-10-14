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
  QT_AFFECT, 
  QT_PARENT,
  QT_FOLLOWS,
  QT_CALLS, 
  QT_USES,
  QT_MODIFIES, 
  QT_PARENTS_S, 
  QT_FOLLOWS_S
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
