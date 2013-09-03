#include "ASTParameter.h"

ASTParameter::ASTParameter(string variableName, VARIABLETYPE parameterType) {
	pVariableName = variableName;
	pParameterType = parameterType;
}

bool ASTParameter::updateAble() {
	return pParameterType != VT_UNDERSCORE && pParameterType != VT_CONSTANTINTEGER && pParameterType != VT_CONSTANTSTRING;
}