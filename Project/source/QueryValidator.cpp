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
	/*size_t startPosition = inputString.find(replaceTarget);
    if(startPosition == string::npos)
        return false;
	inputString.replace(startPosition, replaceTarget.length(), replaceValue);
	replaceSubstring(inputString, replaceTarget, replaceValue);
    return true;*/

	int loc = -1;
	int size = replaceTarget.size();

	while((loc = inputString.find(replaceTarget, loc+1)) != std::string::npos){
		inputString.replace(loc, size, replaceValue); //Single space in quotes
		loc = loc - size;
	}

	return true;
}

bool QueryValidator::is_number(const string& s)
{
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
	firstParaType.push_back("_");
	firstParaType.push_back("prog_line");

	//secondParaType.push_back("integer");
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
	//firstParaType.push_back("string");
	firstParaType.push_back("_");
	firstParaType.push_back("stmt");
	firstParaType.push_back("prog_line");

	secondParaType.push_back("integer");
	//secondParaType.push_back("string");
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
	//firstParaType.push_back("string");
	firstParaType.push_back("_");
	firstParaType.push_back("call");

	secondParaType.push_back("integer");
	//secondParaType.push_back("string");
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
	//firstParaType.push_back("integer");
	firstParaType.push_back("string");
	firstParaType.push_back("_");

	//secondParaType.push_back("integer");
	secondParaType.push_back("string");
	secondParaType.push_back("procedure");
	secondParaType.push_back("_");

	paraTypePair = make_pair(firstParaType, secondParaType);

	queryTypePair = make_pair("calls", paraTypePair);
	tblQueryTypes.push_back(queryTypePair);
	queryTypePair = make_pair("calls*", paraTypePair);
	tblQueryTypes.push_back(queryTypePair);

	//todo: confirm if can accept all kind of stmt type
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
	//firstParaType.push_back("string");
	firstParaType.push_back("prog_line");
	firstParaType.push_back("stmt");
	firstParaType.push_back("_");

	secondParaType.push_back("integer");
	//secondParaType.push_back("string");
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
	/*string processedInput = "";
	bool isEmpty = false;
	bool isFrontBracket = false;

	for(std::string::size_type i = 0; i < input.size(); ++i)  {
		if (input[i] == ' '){
			if (isEmpty)
				isFrontBracket = false;
			else{
				isEmpty = true;
				processedInput = processedInput + input[i];
				isFrontBracket = false;
			}
		}else if (input[i] == '('){
			isFrontBracket = true;
			if (!isEmpty){
				processedInput = processedInput + ' ' + input[i]; //add a space before ( if the previous character is not a space
			}else
				processedInput = processedInput + input[i]; 
			isEmpty = false;
		}else{
			processedInput = processedInput + input[i];
			isEmpty = false;
			isFrontBracket = false;
		}
	}*/

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
	//cout << "processed input: " << processedInput << endl;
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
	
	/*for (vector<pair<string, string>>::size_type i = 0; i < varList.size(); i++){
		cout << varList[i].first << ": " << varList[i].second << endl;
	}*/

	return true;
}

string QueryValidator::getRawVariableType(string variableName){
	for (vector< pair<string, string> >::size_type counter = 0; counter < varList.size(); counter++){
		if (variableName == varList[counter].second){
			return varList[counter].first;
		}
	}

	//if variable not declared, it will be either an integer or string input by user
	if (variableName == "_")
		return "_";
	else if (is_number(variableName))
		return "integer";
	else
		return "string";
}

pair<vector<string>, vector<string>> QueryValidator::getAllowableParaType(string entityType){
	for (vector< pair<string, pair<vector<string>, vector<string>>>>::size_type counter = 0; counter < tblQueryTypes.size(); counter++){
		//if (tblQueryTypes[counter].first == entityType){ // shouldn't use ==

		//cout << "getAllowaleParaType:: " << tblQueryTypes[counter].first << " comparing with (parsed in) " << entityType << endl;
		//cout << "comapare result: " << strcmpi(tblQueryTypes[counter].first.c_str(), entityType.c_str()) << endl;

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
	/*cout << "parsed in para type: " << paraType << endl;
	for (vector<string>::size_type counter = 0; counter < allowedParameterTypes.size(); counter++){
		cout << "allowed parameters are: " << allowedParameterTypes[counter] << endl;
	}*/


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

	/*if (rawVariableType.find(".") != std::string::npos){
		varAttributes = split(rawVariableType, '.');
		if (varAttributes.size() != 2){
			cout << "incorrect number of attributes" << endl;
		}else{
			if (strcmpi(varAttributes[1].c_str(), "procName") == 0){
				return VT_PROCEDURE;
			}else if (strcmpi(varAttributes[1].c_str(), "varName") == 0){
				return VT_VARIABLELIST;
			}else if (strcmpi(varAttributes[1].c_str(), "stmt#") == 0){
				return VT_STATEMENTLIST;
			}
		}
	}*/
		
	if (rawVariableType == "_"){
		//cout << "var type is: _" << endl;
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
		return VT_STATEMENTLIST;
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
		firstParaRawType = getRawVariableType(firstPara);
		secondParaRawType = getRawVariableType(secondPara);

		//remove double quote from string that user input
		replaceSubstring(firstPara, "\"", "");
		replaceSubstring(secondPara, "\"", "");


		if (strcmpi(entityType.c_str(), "queryAssignment") == 0){
			vector<string> splitResult;

			BinaryRelationEngine *BRE = new BinaryRelationEngine(queryManager, pkb);

			if (firstPara.find(".") != string::npos){
				splitResult = split(firstPara, '.');
				//cout << splitResult[0] << ": " << splitResult[1] << endl;
				string header = splitResult[0];
				string extension = splitResult[1];
				BRE -> addParam(header, getVariableType(getRawVariableType(header)), extension);
			}else{
				//cout << "without . : " << firstPara << " - " << firstParaRawType << endl;
				BRE -> addParam(firstPara, getVariableType(firstParaRawType));
			}

			if (secondPara.find(".") != string::npos){
				splitResult = split(secondPara, '.');
				//cout << splitResult[0] << ": " << splitResult[1] << endl;
				string header = splitResult[0];
				string extension = splitResult[1];
				BRE -> addParam(header, getVariableType(getRawVariableType(header)), extension);
			}else{
				//cout << "without . : " << secondPara << " - " << secondParaRawType << endl;
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
				//QueryClass qc(QT_CALLS, queryManager, pkb);
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

			/*cout << "first para: " << firstPara << endl;
			cout << "second para: " << secondPara << endl;
			cout << "first para raw type: " << getRawVariableType(firstPara) << endl;
			cout << "second para raw type: " << getRawVariableType(secondPara) << endl;
			cout << "first para official type: " << getVariableType(getRawVariableType(firstPara)) << endl;
			cout << "second para official type: " << getVariableType(getRawVariableType(secondPara)) << endl;*/

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

		//cout << "current clause: " << currentClause << endl;

		variablePattern = currentClause.substr(0, currentClause.find("("));
		parameters = currentClause.substr(currentClause.find("(")+1, currentClause.length() - currentClause.find("(")-2);

		patternType = getRawVariableType(variablePattern);
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

			//cout << "first para: " << firstPara << endl;
			//cout << "second para: " << secondPara << endl;
			
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
			//else if (secondPara.find("_") != string::npos){
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
		//cout << "processQueryClauses:: current query clause is -> " << queryClauses[counter] << endl;
		currentClause = queryClauses[counter];
		if (currentClause.find("=") != string::npos){
			//clause: e.g. s=10, p.stmt = 11 etc
			splitResults = split(currentClause, '=');
			entityParaPair = make_pair(splitResults[0], splitResults[1]);
			//cout << "processed parameters: " << entityParaPair.first << ": " << entityParaPair.second << endl;
			entityPair = make_pair("queryAssignment", entityParaPair);
		}else if (currentClause.find("(") != string::npos && currentClause.find(")") != string::npos && currentClause.find(",") != string::npos){
			//clause: e.g. assign(a,b), next(a,b) etc
			variableEntityType = currentClause.substr(0, currentClause.find("("));
			//cout << "variable entity type: " << variableEntityType << endl;
			allowedParameterTypes = getAllowableParaType(variableEntityType);

			if (allowedParameterTypes.first[0] == "not found"){ //entity type not found or invalid
				cout << "entity type not found or invalid" << endl;
				return false;
			}

			parameters = currentClause.substr(currentClause.find("(")+1, currentClause.length() - currentClause.find("(")-2); //return "a,b" for "next(a,b)"
			//cout << "raw parameters: " << parameters << endl;

			splitResults = split(parameters, ',');
			//entityParaPair = make_pair(split(parameters, ',')[0], split(parameters, ',')[1]);
			if (splitResults.size() != 2){
				cout << "incorrect number of parameters" << endl;
				return false;
			}

			entityParaPair = make_pair(splitResults[0], splitResults[1]);
			//cout << "processed parameters: " << entityParaPair.first << ": " << entityParaPair.second << endl;
			
			//check if the parameters in the NEXT relationship is the same variable
			if (strcmpi(variableEntityType.c_str(), "next") == 0){
				if (entityParaPair.first == entityParaPair.second){
					return false;
				}
			}

			firstParaType = getRawVariableType(entityParaPair.first);
			secondParaType = getRawVariableType(entityParaPair.second);

			//cout << "processQueryClauses:: firstParaRawType -> " << firstParaType << endl;
			//cout << "processQueryClauses:: secondParaRawType -> " << secondParaType << endl;

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

	/*for (vector < pair<string, pair<string, string>>>::size_type i = 0; i < entityList.size(); i++){
		cout << entityList[i].first << ": " << entityList[i].second.first << " - " << entityList[i].second.second << endl;
	}*/

	return addToQueryManager(entityList);
	//return true;
}

bool QueryValidator::processSelectStmt(string selectStmt){
	vector<string> tokens = split(selectStmt, ' ');
	vector<string> queryList, patternList;
	bool suchClauseDetected = false;
	bool connectClauseDetected = false;
	bool patternClauseDetected = false;

	string returnResult = tokens[1];

	//cout << "processSelectStmt:: " << selectStmt << endl;
	//cout << "processSelectStmt:: before return results -> " << returnResult << endl;

	replaceSubstring(returnResult, "<", "");
	replaceSubstring(returnResult, ">", "");
	//cout << "processSelectStmt:: after return results -> " << returnResult << endl;
	vector<string> returnResults = split(returnResult, ',');
	
	for (vector<string>::size_type counter = 0; counter < returnResults.size(); counter++){
		//cout << "processSelectStmt:: return results #" << counter << " -> " << returnResults[counter] << endl;
		queryManager -> addResultExpression(returnResults[counter]);
	}

	for (vector<string>::size_type counter = 2; counter < tokens.size(); counter++){
		//cout << "current token: " << tokens[counter] << endl;

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
				//cout << "such that clause detected" << endl;
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
				//cout << tokens[counter] << " clause detected" << endl;
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
					//cout << "pattern token: " << tokens[counter] << endl;
					actualPattern = actualPattern + " " + tokens[counter];
				}while(counter <= tokens.size()-1 && tokens[counter].compare(tokens[counter].length()-1, 1, ")") != 0);
			}
			//cout << "actual pattern: " << actualPattern << endl;
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

	/*for (vector<string>::size_type counter = 0; counter < patternList.size(); counter++){
		cout << "processsSelectStmt:: pattern no. " << counter << " -> " << patternList[counter] << endl;
	}*/

	return (processPatternClauses(patternList) && processQueryClauses(queryList));
}

bool QueryValidator::processQuery(string inputQuery){
	//cout << "Processing Query..." << endl;
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
	
	//cout << "processQuery:: select statement is -> " << selectStmt << endl;

	if (strcmpi(selectStmt.substr(0, selectStmt.find(' ', 0)+1).c_str(), "select ") != 0){
		cout << "No Select statement found." << endl;
		return false;
	}

	for (vector<string>::size_type counter = 0; counter < queryStmts.size() -1; counter++){ //omit last statement, which should be the Select statement
		//cout << "processQuery:: declaration statement is -> " << queryStmts[counter] << endl;
		if (!processDeclarationStmt(trim(queryStmts[counter]))){
			cout << "process declaration stmt failed" << endl;
			return false;
		}
	}

	return processSelectStmt(selectStmt);

	/*cout << query << endl;
	cout << inputQuery.find("select", 0) << endl;
	cout << queryStmts.size() << endl;
	return true;*/
}

int main(){
	Parser parser;
	DesignExtractor extractor;
	PKB* pkb;

	try {
		//pkb = parser.parse("ComboTest2.txt");
		pkb = parser.parse("Test.txt");
		extractor.extract(pkb);
	} catch (ParseException pe) {
		cout << pe.what();
		getchar();
		return 0;
	}

	QueryManager* qm = new QueryManager(pkb);

	QueryClass* qc = new UsesEngine(qm, pkb);

	QueryValidator qv(qm, pkb);

	string input;
	//input = "stmt s; \n Select s such that Parent(s, 3) ";
	//input = "assign a, a1;Select a such that Follows(a, a1)";
	//input = "assign a;Select a pattern a(\"z\",_)";
	//input = "stmt s, s1; prog_line n; Select s such that Parent(s, s1) with s1.stmt# = n with n = 3";
	//input = "Select BOOLEAN such that Calls*(\"eight\", \"Six\")";
	input = "procedure p, q; Select <q, p> such that Calls(p, q)";
	
	cout << qv.processQuery(input) << endl;
	getline(cin, input);
	//cout << "input: " << input << endl;
	while (cin != "0"){
		if (qv.processQuery(input) == true)
			cout << "result is: TRUE" << endl;
		else
			cout << "result is: FALSE" << endl;
		
		getline(cin, input);
	}
	//qv.processQuery("assign a, b; variable v; select a such that modifies (a , v)");
	//qv.processQuery("assign a, b; variable v; while w; select a such that pattern w (\"x\", _)");
	//qv.processQuery("assign a, b; variable v; select a such that Modifies (a , v) and v.VarName = \"a\"");
	//qv.processQuery("assign a, b; variable v; select v such that modifies (2 , v)");
	//qv.processQuery("assign a, b; variable v; select v such that Modifies (3 , v) and Next(1,2)");
	//qv.processQuery("assign a, b; variable v; while w; select v such that Modifies (w , v)");
	cout << "end";
}	