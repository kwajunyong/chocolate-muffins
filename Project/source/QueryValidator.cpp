#include "QueryValidator.h"

#include <string>
#include <string.h>

using namespace std;

QueryValidator::QueryValidator(QueryManager *qm, PKB *p){
	queryManager = qm;
	pkb = p;
}

QueryValidator::~QueryValidator(void){}

//for splitting string
std::vector<std::string> &split(const std::string &inputString, char delimiter, std::vector<std::string> &tokens) {
    std::stringstream strStream(inputString);
    std::string item;
    while (std::getline(strStream, item, delimiter)) {
        tokens.push_back(item);
    }
    return tokens;
}

std::vector<std::string> split(const std::string &inputString, char delimiter) {
    std::vector<std::string> tokens;
    split(inputString, delimiter, tokens);
    return tokens;
}
//end of splitting string functions

std::string trim(const std::string& input, const std::string& whitespace = " ")
{
    const auto posStart = input.find_first_not_of(whitespace);
    if (posStart == std::string::npos)
        return ""; // no content

    const auto posEnd = input.find_last_not_of(whitespace);
    const auto range = posEnd - posStart + 1;

    return input.substr(posStart, range);
}

bool QueryValidator::replaceSubstring(string& inputString, const string& replaceTarget, const string& replaceValue){
	int loc = -1;
	int size = replaceTarget.size();

	while((loc = inputString.find(replaceTarget, loc+1)) != std::string::npos){
		inputString.replace(loc, size, replaceValue); //Single space in quotes
		loc = loc - size;
	}

	return true;
}

bool QueryValidator::is_number(const string& s){
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) 
		++it;
    return !s.empty() && it == s.end();
}

void QueryValidator::initQueryClauseTable(){
	tblQueryClauses.push_back("select");
	tblQueryClauses.push_back("such that");
	tblQueryClauses.push_back("with");
	tblQueryClauses.push_back("and");
	tblQueryClauses.push_back("pattern");
	tblQueryClauses.push_back("boolean");
}

void QueryValidator::initDesignEntityTable(){
	tblDesignEntities.push_back("program");
	tblDesignEntities.push_back("procedure");
	tblDesignEntities.push_back("stmtLst");
	tblDesignEntities.push_back("stmt");
	tblDesignEntities.push_back("assign");
	tblDesignEntities.push_back("call");
	tblDesignEntities.push_back("while");
	tblDesignEntities.push_back("if");
	tblDesignEntities.push_back("variable");
	tblDesignEntities.push_back("constant");
	tblDesignEntities.push_back("prog_line");
}

void QueryValidator::initQueryTypeTable(){
	vector<string> firstParaType, secondParaType;
	pair<vector<string>, vector<string>> paraTypePair;
	pair<string, pair<vector<string>, vector<string>>> queryTypePair;

	//modifies, uses
	firstParaType.push_back("assign");
	firstParaType.push_back("if");
	firstParaType.push_back("while");
	firstParaType.push_back("procedure");
	firstParaType.push_back("call");
	firstParaType.push_back("stmt");
	firstParaType.push_back("integer");
	firstParaType.push_back("string");
	firstParaType.push_back("prog_line");

	secondParaType.push_back("string");
	secondParaType.push_back("variable");
	secondParaType.push_back("_");

	paraTypePair = make_pair(firstParaType, secondParaType);

	queryTypePair = make_pair("modifies", paraTypePair);
	tblQueryTypes.push_back(queryTypePair);
	queryTypePair = make_pair("uses", paraTypePair);
	tblQueryTypes.push_back(queryTypePair);

	//parent, parent*
	firstParaType.clear();
	secondParaType.clear();

	firstParaType.push_back("if");
	firstParaType.push_back("while");
	firstParaType.push_back("integer");
	firstParaType.push_back("_");
	firstParaType.push_back("stmt");
	firstParaType.push_back("prog_line");

	secondParaType.push_back("integer");
	secondParaType.push_back("assign");
	secondParaType.push_back("if");
	secondParaType.push_back("while");
	secondParaType.push_back("call");
	secondParaType.push_back("stmt");
	secondParaType.push_back("prog_line");
	secondParaType.push_back("_");

	paraTypePair = make_pair(firstParaType, secondParaType);

	queryTypePair = make_pair("parent", paraTypePair);
	tblQueryTypes.push_back(queryTypePair);
	queryTypePair = make_pair("parent*", paraTypePair);
	tblQueryTypes.push_back(queryTypePair);

	//follows, follows*
	firstParaType.clear();
	secondParaType.clear();

	firstParaType.push_back("if");
	firstParaType.push_back("while");
	firstParaType.push_back("assign");
	firstParaType.push_back("stmt");
	firstParaType.push_back("prog_line");
	firstParaType.push_back("integer");
	firstParaType.push_back("_");
	firstParaType.push_back("call");

	secondParaType.push_back("integer");
	secondParaType.push_back("assign");
	secondParaType.push_back("if");
	secondParaType.push_back("while");
	secondParaType.push_back("call");
	secondParaType.push_back("stmt");
	secondParaType.push_back("prog_line");
	secondParaType.push_back("_");

	paraTypePair = make_pair(firstParaType, secondParaType);

	queryTypePair = make_pair("follows", paraTypePair);
	tblQueryTypes.push_back(queryTypePair);
	queryTypePair = make_pair("follows*", paraTypePair);
	tblQueryTypes.push_back(queryTypePair);

	//calls, calls*
	firstParaType.clear();
	secondParaType.clear();

	firstParaType.push_back("procedure");
	firstParaType.push_back("string");
	firstParaType.push_back("_");

	secondParaType.push_back("string");
	secondParaType.push_back("procedure");
	secondParaType.push_back("_");

	paraTypePair = make_pair(firstParaType, secondParaType);

	queryTypePair = make_pair("calls", paraTypePair);
	tblQueryTypes.push_back(queryTypePair);
	queryTypePair = make_pair("calls*", paraTypePair);
	tblQueryTypes.push_back(queryTypePair);


	//next, next*
	firstParaType.clear();
	secondParaType.clear();

	firstParaType.push_back("stmt");
	firstParaType.push_back("integer");
	firstParaType.push_back("call");
	firstParaType.push_back("while");
	firstParaType.push_back("if");
	firstParaType.push_back("assign");
	firstParaType.push_back("prog_line");
	firstParaType.push_back("_");

	secondParaType.push_back("stmt");
	secondParaType.push_back("integer");
	secondParaType.push_back("call");
	secondParaType.push_back("while");
	secondParaType.push_back("if");
	secondParaType.push_back("assign");
	secondParaType.push_back("prog_line");
	secondParaType.push_back("_");

	paraTypePair = make_pair(firstParaType, secondParaType);

	queryTypePair = make_pair("next", paraTypePair);
	tblQueryTypes.push_back(queryTypePair);
	queryTypePair = make_pair("next*", paraTypePair);
	tblQueryTypes.push_back(queryTypePair);

	//affects, affects*
	firstParaType.clear();
	secondParaType.clear();

	firstParaType.push_back("assign");
	firstParaType.push_back("integer");
	firstParaType.push_back("prog_line");
	firstParaType.push_back("stmt");
	firstParaType.push_back("_");

	secondParaType.push_back("integer");
	secondParaType.push_back("assign");
	secondParaType.push_back("prog_line");
	secondParaType.push_back("stmt");
	secondParaType.push_back("_");

	paraTypePair = make_pair(firstParaType, secondParaType);

	queryTypePair = make_pair("affects", paraTypePair);
	tblQueryTypes.push_back(queryTypePair);
	queryTypePair = make_pair("affects*", paraTypePair);
	tblQueryTypes.push_back(queryTypePair);
}

void QueryValidator::initCheckingTables(){
	initQueryClauseTable();
	initDesignEntityTable();
	initQueryTypeTable();
}

std::string QueryValidator::preprocessInput(string input){
	string processedInput = input;
	replaceSubstring(processedInput, " (", "(");
	replaceSubstring(processedInput, "( ", "(");
	replaceSubstring(processedInput, " )", ")");
	replaceSubstring(processedInput, "< ", "<");
	replaceSubstring(processedInput, " >", ">");
	replaceSubstring(processedInput, " ,", ",");
	replaceSubstring(processedInput, ", ", ",");
	replaceSubstring(processedInput, " =", "=");
	replaceSubstring(processedInput, "= ", "=");
	replaceSubstring(processedInput, " ;", ";");
	replaceSubstring(processedInput, "; ", ";");
	replaceSubstring(processedInput, "\n", "");
	replaceSubstring(processedInput, "  ", " ");

	return processedInput;
}

bool QueryValidator::processDeclarationStmt(string declarationStmt){
	pair<string, string> declarationPair;
	bool entityFound = false;

	replaceSubstring(declarationStmt, ",", " ");
	vector<string> tokens = split(declarationStmt, ' ');

	for (vector<string>::size_type counter = 0; counter < tblDesignEntities.size(); counter++){
		if (strcmpi(tokens[0].c_str(), tblDesignEntities[counter].c_str()) == 0){ //first token will definitely be entity type
			entityFound = true;
			break;
		}
	}

	if (!entityFound){
		cout << "entity not found: " << tokens[0] << endl;
		return false;
	}

	for (vector<string>::size_type counterVarNames = 1; counterVarNames < tokens.size(); counterVarNames++){
		declarationPair = make_pair(tokens[0], tokens[counterVarNames]);
		varList.push_back(declarationPair);

		queryManager -> addExpression(getVariableType(declarationPair.first), declarationPair.second);
	}

	return true;
}

string QueryValidator::getRawVariableType(string variableName){
	for (vector< pair<string, string> >::size_type counter = 0; counter < varList.size(); counter++){
		if (variableName == varList[counter].second){
			return varList[counter].first;
		}
	}

	if (variableName == "_")
		return "_";
	else if (is_number(variableName))
		return "integer";
	else if (variableName.compare(0, 1, "\"") == 0 && variableName.compare(variableName.length()-1, 1, "\"") == 0)
		return "string";
	else
		return "invalid";
}

pair<vector<string>, vector<string>> QueryValidator::getAllowableParaType(string entityType){
	for (vector< pair<string, pair<vector<string>, vector<string>>>>::size_type counter = 0; counter < tblQueryTypes.size(); counter++){
		if (strcmpi(tblQueryTypes[counter].first.c_str(), entityType.c_str()) == 0 ){
			return tblQueryTypes[counter].second;
		}
	}

	vector<string> nullA, nullB;
	nullA.push_back("not found");
	nullB.push_back("not found");
	pair<vector<string>, vector<string>> nullResult = make_pair(nullA, nullB);

	return nullResult;
}

bool QueryValidator::paraTypeAllowed(vector<string> allowedParameterTypes, string paraType){
	for (vector<string>::size_type counter = 0; counter < allowedParameterTypes.size(); counter++){
		if (strcmpi(allowedParameterTypes[counter].c_str(), paraType.c_str()) == 0)
			return true;
	}
	
	return false;
}

VARIABLETYPE QueryValidator::getVariableType(std::string rawVariableType){
	vector<std::string> varAttributes; 

	if (rawVariableType == "string")
		return VT_CONSTANTSTRING;

	if (rawVariableType == "integer")
		return VT_CONSTANTINTEGER;
		
	if (rawVariableType == "_"){
		return VT_UNDERSCORE;
	}else if (strcmpi(rawVariableType.c_str(), "assign") == 0){
		return VT_ASSIGNMENT;
	}else if (strcmpi(rawVariableType.c_str(), "while") == 0){
		return VT_WHILE;
	}else if (strcmpi(rawVariableType.c_str(), "if") == 0){
		return VT_IF;
	}else if (strcmpi(rawVariableType.c_str(), "procedure") == 0){
		return VT_PROCEDURE;
	}else if (strcmpi(rawVariableType.c_str(), "stmt") == 0){
		return VT_STATEMENTLIST;
	}else if (strcmpi(rawVariableType.c_str(), "stmtLst") == 0){
		return VT_STATEMENTLIST_EXTRA;
	}else if (strcmpi(rawVariableType.c_str(), "variable") == 0){
		return VT_VARIABLELIST;
	}else if (strcmpi(rawVariableType.c_str(), "call") == 0){
		return VT_CALL;
	}else if (strcmpi(rawVariableType.c_str(), "prog_line") == 0){
		return VT_PROG_LINE;
	}else if (strcmpi(rawVariableType.c_str(), "constant") == 0){
		return VT_CONSTANT;
	}else //if (unkVarType == "program"){
		return VT_CONSTANTSTRING;
	//}
}

bool QueryValidator::addToQueryManager(vector<pair<string, pair<string, string>>> clausesList){
	string entityType, firstPara, secondPara, firstParaRawType, secondParaRawType;

	for (vector<pair<string, pair<string, string>>>::size_type counter = 0; counter < clausesList.size(); counter++){
		entityType = clausesList[counter].first;
		firstPara = clausesList[counter].second.first;
		secondPara = clausesList[counter].second.second;

		if (strcmpi(entityType.c_str(), "queryAssignment") == 0){
			vector<string> splitResult;

			BinaryRelationEngine *BRE = new BinaryRelationEngine(queryManager, pkb);

			if (firstPara.find(".") != string::npos){
				splitResult = split(firstPara, '.');
				//cout << splitResult[0] << ": " << splitResult[1] << endl;
				string header = splitResult[0];
				string extension = splitResult[1];
				string headerRawType = getRawVariableType(header);
				if (headerRawType == "invalid"){
					cout << "first para header not declared" << endl;
					return false;
				}
				BRE -> addParam(header, getVariableType(headerRawType), extension);
			}else{
				firstParaRawType = getRawVariableType(firstPara);
				replaceSubstring(firstPara, "\"", "");
				BRE -> addParam(firstPara, getVariableType(firstParaRawType));
			}

			if (secondPara.find(".") != string::npos){
				splitResult = split(secondPara, '.');
				string header = splitResult[0];
				string extension = splitResult[1];
				string headerRawType = getRawVariableType(header);
				if (headerRawType == "invalid"){
					cout << "second para header not declared" << endl;
					return false;
				}
				BRE -> addParam(header, getVariableType(headerRawType), extension);
			}else{
				secondParaRawType = getRawVariableType(secondPara);
				replaceSubstring(secondPara, "\"", "");
				BRE -> addParam(secondPara, getVariableType(secondParaRawType));
			}

			queryManager -> addQueryClass(BRE);
		}else{//all non-extended clauses
			QueryClass *qc;

			if (strcmpi(entityType.c_str(), "Modifies") == 0){
				qc = new ModifiesEngine(queryManager, pkb);
			}else if (strcmpi(entityType.c_str(), "Uses") == 0){
				qc = new UsesEngine(queryManager, pkb);		
			}else if (strcmpi(entityType.c_str(), "Calls") == 0){
				qc = new CallEngine(queryManager, pkb);	
			}else if (strcmpi(entityType.c_str(), "Calls*") == 0){
				qc = new CallStarEngine(queryManager, pkb);					
			}else if (strcmpi(entityType.c_str(), "Parent") == 0){
				qc = new ParentEngine(queryManager, pkb);
			}else if (strcmpi(entityType.c_str(), "Parent*") == 0){
				qc = new ParentStarEngine(queryManager, pkb);	
			}else if (strcmpi(entityType.c_str(), "Follows") == 0){	
				qc = new FollowsEngine(queryManager, pkb);
			}else if (strcmpi(entityType.c_str(), "Follows*") == 0){
				qc = new FollowsStarEngine(queryManager, pkb);
			}else if (strcmpi(entityType.c_str(), "Next") == 0){	
				qc = new NextEngine(queryManager, pkb);
			}else if (strcmpi(entityType.c_str(), "Next*") == 0){
				qc = new NextStarEngine(queryManager, pkb);
			}else if (strcmpi(entityType.c_str(), "Affects") == 0){
				qc = new AffectEngine(queryManager, pkb);		
			}else{ //"Affects*"
				qc = new AffectStarEngine(queryManager, pkb);
			}

			firstParaRawType = getRawVariableType(firstPara);
			secondParaRawType = getRawVariableType(secondPara);
			replaceSubstring(firstPara, "\"", "");
			replaceSubstring(secondPara, "\"", "");
			qc -> addParam(firstPara, getVariableType(firstParaRawType));
			qc -> addParam(secondPara, getVariableType(secondParaRawType));

			queryManager -> addQueryClass(qc);
		}
	}

	return true;
}

bool QueryValidator::processPatternClauses(vector<string> patternClauses){
	string currentClause, variablePattern, parameters, patternType, firstPara, secondPara, thirdPara;
	vector<string> splitResults;

	for (vector<string>::size_type counter = 0; counter < patternClauses.size(); counter++){
		currentClause = patternClauses[counter];

		variablePattern = currentClause.substr(0, currentClause.find("("));
		parameters = currentClause.substr(currentClause.find("(")+1, currentClause.length() - currentClause.find("(")-2);

		patternType = getRawVariableType(variablePattern);

		if (patternType == "invalid"){
			cout << "processPatternClauses: parameters not declared" << endl;
			return false;
		}

		splitResults = split(parameters, ',');

		QueryClass *qc; //= new ExpressionPattern(queryManager, pkb);

		if (strcmpi(patternType.c_str(), "assign") == 0){
			if (splitResults.size() != 2){
				cout << "incorrect number of parameters" << endl;
				return false;
			}
			
			qc = new ExpressionPattern(queryManager, pkb);

			firstPara = splitResults[0];
			secondPara = splitResults[1];
			
			qc -> addParam(variablePattern, VT_ASSIGNMENT);

			if (firstPara == "_")
				qc -> addParam(splitResults[0], VT_UNDERSCORE);
			else if (firstPara.find("_") != string::npos){
				replaceSubstring(splitResults[0], "_\"", "");
				replaceSubstring(splitResults[0], "\"_", "");
				qc -> addParam(splitResults[0], VT_EXPRESSION_UNDERSCORE);
			}else if (firstPara.find("\"") != string::npos){
				replaceSubstring(splitResults[0], "\"", "");
				qc -> addParam(splitResults[0], VT_CONSTANTSTRING);
			}else{
				cout << "incorrect parameter type for pattern clauses" << endl;
				return false;
			}

			if (secondPara == "_")
				qc -> addParam(splitResults[1], VT_UNDERSCORE);
			else if (secondPara.compare(0, 1, "_") == 0 && secondPara.compare(secondPara.length()-1, 1, "_") == 0){
				replaceSubstring(splitResults[1], "_\"", "");
				replaceSubstring(splitResults[1], "\"_", "");
				qc -> addParam(splitResults[1], VT_EXPRESSION_UNDERSCORE);
			}else if (secondPara.find("\"") != string::npos && secondPara.find("_") == string::npos){
				replaceSubstring(splitResults[1], "\"", "");
				qc -> addParam(splitResults[1], VT_CONSTANTSTRING);
			}else{
				cout << "incorrect parameter type for ASSIGN pattern clauses" << endl;
				return false;
			}
		}else if (strcmpi(patternType.c_str(), "while") == 0){
			if (splitResults.size() != 2){
				cout << "incorrect number of parameters" << endl;
				return false;
			}

			qc = new WhilePattern(queryManager, pkb);

			firstPara = splitResults[0];
			secondPara = splitResults[1];

			qc -> addParam(variablePattern, VT_WHILE);

			if (firstPara == "_")
				qc -> addParam(splitResults[0], VT_UNDERSCORE);
			else if (firstPara.find("_") != string::npos){
				replaceSubstring(splitResults[0], "_\"", "");
				replaceSubstring(splitResults[0], "\"_", "");
				qc -> addParam(splitResults[0], VT_EXPRESSION_UNDERSCORE);
			}else if (firstPara.find("\"") != string::npos){
				replaceSubstring(splitResults[0], "\"", "");
				qc -> addParam(splitResults[0], VT_CONSTANTSTRING);
			}else{
				cout << "incorrect parameter type for WHILE pattern clauses" << endl;
				return false;
			}

			if (secondPara != "_"){
				cout << "second parameter is not a _ for WHILE pattern" << endl;
				return false;
			}
		}else if (strcmpi(patternType.c_str(), "if") == 0){
			if (splitResults.size() != 3){
				cout << "incorrect number of parameters" << endl;
				return false;
			}

			qc = new IfPattern(queryManager, pkb);

			firstPara = splitResults[0];
			secondPara = splitResults[1];
			thirdPara = splitResults[2];

			qc -> addParam(variablePattern, VT_IF);

			if (firstPara == "_")
				qc -> addParam(splitResults[0], VT_UNDERSCORE);
			else if (firstPara.find("_") != string::npos){
				replaceSubstring(splitResults[0], "_\"", "");
				replaceSubstring(splitResults[0], "\"_", "");
				qc -> addParam(splitResults[0], VT_EXPRESSION_UNDERSCORE);
			}else if (firstPara.find("\"") != string::npos){
				replaceSubstring(splitResults[0], "\"", "");
				qc -> addParam(splitResults[0], VT_CONSTANTSTRING);
			}else{
				cout << "incorrect parameter type for IF pattern clauses" << endl;
				return false;
			}

			if (secondPara != "_" || thirdPara != "_"){
				cout << "second/third parameter is not a _ for IF pattern" << endl;
				return false;
			}
		}else{
			cout << "invalid pattern type" << endl;
			return false;
		}

		queryManager -> addQueryClass(qc);
	}

	return true;
}

bool QueryValidator::processQueryClauses(vector<string> queryClauses){
	string currentClause, variableEntityType, parameters, firstParaType, secondParaType;
	pair<string, string> entityParaPair;
	pair<string, pair<string, string>> entityPair;
	pair<vector<string>, vector<string>> allowedParameterTypes;
	vector<string> splitResults;

	for (vector<string>::size_type counter = 0; counter < queryClauses.size(); counter++){
		currentClause = queryClauses[counter];
		if (currentClause.find("=") != string::npos){
			//clause: e.g. s=10, p.stmt = 11 etc
			splitResults = split(currentClause, '=');
			entityParaPair = make_pair(splitResults[0], splitResults[1]);
			entityPair = make_pair("queryAssignment", entityParaPair);
		}else if (currentClause.find("(") != string::npos && currentClause.find(")") != string::npos && currentClause.find(",") != string::npos){
			//clause: e.g. assign(a,b), next(a,b) etc
			variableEntityType = currentClause.substr(0, currentClause.find("("));
			allowedParameterTypes = getAllowableParaType(variableEntityType);

			if (allowedParameterTypes.first[0] == "not found"){ //entity type not found or invalid
				cout << "entity type not found or invalid" << endl;
				return false;
			}

			parameters = currentClause.substr(currentClause.find("(")+1, currentClause.length() - currentClause.find("(")-2); //return "a,b" for "next(a,b)"

			splitResults = split(parameters, ',');

			if (splitResults.size() != 2){
				cout << "processQueryClauses: incorrect number of parameters" << endl;
				return false;
			}

			entityParaPair = make_pair(splitResults[0], splitResults[1]);
			
			//check if the parameters in the NEXT relationship is the same variable
			if (strcmpi(variableEntityType.c_str(), "next") == 0){
				if (entityParaPair.first == entityParaPair.second && entityParaPair.first != "_"){
					return false;
				}
			}

			firstParaType = getRawVariableType(entityParaPair.first);
			secondParaType = getRawVariableType(entityParaPair.second);

			if (firstParaType == "invalid" || secondParaType == "invalid"){
				cout << "processQueryClauses: parameter not declared" << endl;
				return false;
			}

			if (!(paraTypeAllowed(allowedParameterTypes.first, firstParaType) && paraTypeAllowed(allowedParameterTypes.second, secondParaType))){
				cout << "parameters not allowed" << endl;
				return false;
			}

			entityPair = make_pair(variableEntityType, entityParaPair);
		}else{
			//neither of the above, invalid relationship
			cout << "invalid relationship: " << currentClause << endl;
			return false;
		}
		entityList.push_back(entityPair);
	}

	return addToQueryManager(entityList);
}

bool QueryValidator::getValidReturnResultType(string returnResultVariable){
	string rawType = getRawVariableType(returnResultVariable);
	for (vector<string>::size_type counter = 0; counter < tblDesignEntities.size(); counter++){
			if (strcmpi(tblDesignEntities[counter].c_str(), rawType.c_str()) == 0)
				return true;
		}
}

bool QueryValidator::processSelectStmt(string selectStmt){
	vector<string> tokens = split(selectStmt, ' ');
	vector<string> queryList, patternList;
	bool suchClauseDetected = false;
	bool connectClauseDetected = false;
	bool patternClauseDetected = false;

	string returnResult = tokens[1];
	string returnIndividualResult;
	string returnResultRawType;
	string returnResultExtension;

	replaceSubstring(returnResult, "<", "");
	replaceSubstring(returnResult, ">", "");

	vector<string> returnResults = split(returnResult, ',');
	
	for (vector<string>::size_type counter = 0; counter < returnResults.size(); counter++){
		returnIndividualResult = returnResults[counter];
		
		if (!getValidReturnResultType(returnIndividualResult)){
			cout << "return result not allowed: " << returnIndividualResult << endl;
			return false;
		}

		if (returnIndividualResult.find(".") != string::npos){
			string tempReturnResult = split(returnIndividualResult, '.')[0];
			returnResultRawType = getRawVariableType(tempReturnResult);
			returnResultExtension = split(returnIndividualResult, '.')[1];

			if (returnResultRawType == "invalid"){
				cout << "return result not declared" << endl;
				return false;
			}

			if (strcmpi(returnResultRawType.c_str(), "variable") == 0 && strcmpi(returnResultExtension.c_str(), "varName") != 0){
				return false;
			}else if (strcmpi(returnResultRawType.c_str(), "constant") == 0 && strcmpi(returnResultExtension.c_str(), "value") != 0){
				return false;
			}else if (strcmpi(returnResultRawType.c_str(), "prog_line") == 0 && strcmpi(returnResultExtension.c_str(), "prog_line#") != 0){
				return false;
			}else if (strcmpi(returnResultRawType.c_str(), "stmt") == 0 && strcmpi(returnResultExtension.c_str(), "stmt#") != 0){
				return false;
			}else if (strcmpi(returnResultRawType.c_str(), "procedure") == 0 && (strcmpi(returnResultExtension.c_str(), "procName") != 0)){
				return false;
			}else if (strcmpi(returnResultRawType.c_str(), "call") == 0 && (strcmpi(returnResultExtension.c_str(), "procName") != 0 && strcmpi(returnResultExtension.c_str(), "stmt#") != 0)){
				return false;
			}else if ((strcmpi(returnResultRawType.c_str(), "while") == 0 || strcmpi(returnResultRawType.c_str(), "if") == 0 || strcmpi(returnResultRawType.c_str(), "assign") == 0) && strcmpi(returnResultExtension.c_str(), "stmt#") != 0){
				return false;
			}else if (strcmpi(returnResultRawType.c_str(), "stmtLst") == 0 && strcmpi(returnResultExtension.c_str(), "stmt#") != 0){
				return false;
			}else{
				if (strcmpi(returnResultRawType.c_str(), "call") == 0 && strcmpi(returnResultExtension.c_str(), "procName") == 0){
					queryManager -> addResultExpression(returnIndividualResult);
				}else{
					queryManager -> addResultExpression(split(returnIndividualResult, '.')[0]);
				}
			}
		}else{
			queryManager -> addResultExpression(returnIndividualResult);
		}
	}

	for (vector<string>::size_type counter = 2; counter < tokens.size(); counter++){
		if (strcmpi(tokens[counter].c_str(), "such") == 0){
			if (connectClauseDetected){
				cout << "grammar error, continuous of connecting clauses: and, with, such that" << endl;
				return false;
			}else{
				suchClauseDetected = true;
				connectClauseDetected = false;
				patternClauseDetected = false;
			}
		}else if (suchClauseDetected){
			if (strcmpi(tokens[counter].c_str(), "that") == 0){
				connectClauseDetected = true;
				suchClauseDetected = false;
				patternClauseDetected = false;
			}else{
				cout << "incomplete such that clause" << endl;
				return false;
			}
		}else if (strcmpi(tokens[counter].c_str(), "and") == 0 || strcmpi(tokens[counter].c_str(), "with") == 0){
			if (connectClauseDetected){
				cout << "grammar error, continuous of connecting clauses: and, with, such that" << endl;
				return false;
			}else{
				connectClauseDetected = true;
				patternClauseDetected = false;
				suchClauseDetected = false;
			}
		}else if (strcmpi(tokens[counter].c_str(), "pattern") == 0){
			patternClauseDetected = true;
			suchClauseDetected = false;
			connectClauseDetected = false;
		}else if (patternClauseDetected){
			string actualPattern = tokens[counter];
			if (tokens[counter].compare(tokens[counter].length()-1, 1, ")") != 0){
				do{
					counter++;
					actualPattern = actualPattern + " " + tokens[counter];
				}while(counter <= tokens.size()-1 && tokens[counter].compare(tokens[counter].length()-1, 1, ")") != 0);
			}

			patternList.push_back(actualPattern);
			connectClauseDetected = false;
			patternClauseDetected = false;
			suchClauseDetected = false;
		}else{
			if (connectClauseDetected){
				queryList.push_back(tokens[counter]);
				connectClauseDetected = false;
				patternClauseDetected = false;
				suchClauseDetected = false;
			}else{
				cout << "grammar error, query not connected with connecting clauses: and, with, such that" << endl;
				return false;
			}
		}
	}

	return (processPatternClauses(patternList) && processQueryClauses(queryList));
}

bool QueryValidator::processQuery(string inputQuery){
	tblQueryClauses.clear();
	tblDesignEntities.clear();
	tblQueryTypes.clear();
	entityList.clear();
	varList.clear();
	
	initCheckingTables();

	string query = preprocessInput(inputQuery);
	vector<string> queryStmts = split(query, ';');

	//last statement must be Select statement since declarations should all be done before Select statement
	string selectStmt = queryStmts[queryStmts.size()-1]; 
	selectStmt = trim(selectStmt);

	if (strcmpi(selectStmt.substr(0, selectStmt.find(' ', 0)+1).c_str(), "select ") != 0){
		cout << "No Select statement found." << endl;
		return false;
	}

	for (vector<string>::size_type counter = 0; counter < queryStmts.size() -1; counter++){ //omit last statement, which should be the Select statement
		if (!processDeclarationStmt(trim(queryStmts[counter]))){
			cout << "process declaration stmt failed" << endl;
			return false;
		}
	}

	return processSelectStmt(selectStmt);
}	