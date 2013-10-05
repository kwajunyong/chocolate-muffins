#pragma once
#include "EnumType.h"
#include <string>

using namespace std;

class ASTParameterValue;

class ASTParameter {
 public:
	 ASTParameter(){
	 }
  ASTParameter(string variableName, VARIABLETYPE parameterType); 
   VARIABLETYPE getParameterType() {
     return pParameterType;
   }
   
   string getVariableName() {
	   return pVariableName;
   }
   
   bool updateAble();

 private:
   string pVariableName;
   VARIABLETYPE pParameterType;
};
