#include "QueryValidator.h"


#include <string>

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

bool QueryValidator::is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) 
		++it;
    return !s.empty() && it == s.end();
}

bool QueryValidator::replaceSubstring(std::string& inputString, const std::string& replaceTarget, const std::string& replaceValue){
	size_t startPosition = inputString.find(replaceTarget);
    if(startPosition == std::string::npos)
        return false;
    inputString.replace(startPosition, replaceTarget.length(), replaceValue);
	replaceSubstring(inputString, replaceTarget, replaceValue);
    return true;
}

pair<std::string, std::string> QueryValidator::processParameters(std::string firstParam, std::string secondParam){
	pair<std::string, std::string> returnPair;
	returnPair = std::make_pair("null", "null");

	if (std::string::npos == firstParam.find("(") && std::string::npos == secondParam.find(")")){
		cout << "not a pair of parameters";
		return returnPair;
	}

	replaceSubstring(firstParam, "(", "");
	replaceSubstring(firstParam, " ", "");
	replaceSubstring(secondParam, ")", "");
	replaceSubstring(secondParam, " ", "");

	returnPair = std::make_pair(firstParam, secondParam);

	return returnPair;
}

std::string QueryValidator::getRawVariableType(std::string varName){
	if (varName == "_")
		return "_";
	
	for (vector< pair<std::string, std::string> >::size_type varCount = 0; varCount < varList.size(); varCount++){
		if (varList[varCount].second == varName)
			return varList[varCount].first;
	}

	//if variable not declared, it is a variable in the the code
	//if (varName[0] == '"' && varName[varName.size()-1] == '"')

	if (is_number(varName))
		return "codingNumber";
	
	return "codingVariable";

	//cout << "variable: " << varName << " not found." << endl;
	//return "null";
}

VARIABLETYPE QueryValidator::identifyVariableType(std::string unkVarType){
	vector<std::string> varAttributes; 

	if (unkVarType == "codingVariable")
		return VT_CONSTANTSTRING;

	if (unkVarType == "codingNumber")
		return VT_CONSTANTINTEGER;

	if (std::string::npos != unkVarType.find(".")){
		varAttributes = split(unkVarType, '.');
		if (varAttributes.size() != 2){
			cout << "incorrect number of attributes" << endl;
		}else{
			if (varAttributes[1] == "procName" || varAttributes[1] == "varName"){
				return VT_CONSTANTSTRING;
			}else{
				return VT_CONSTANTINTEGER;
			}
		}
	}
	
	if (unkVarType == "_"){
		return VT_UNDERSCORE;
	}else if (unkVarType == "Assignment" || unkVarType == "assignment"){
		return VT_ASSIGNMENT;
	}else if (unkVarType == "While" || unkVarType == "while"){
		return VT_WHILE;
	}else if (unkVarType == "If" || unkVarType == "if"){
		return VT_IF;
	}else if (unkVarType == "Procedure" || unkVarType == "procedure"){
		return VT_PROCEDURE;
	}else if (unkVarType == "Stmt" || unkVarType == "stmt"){
		return VT_STATEMENTLIST;
	}else if (unkVarType == "StmtLst" || unkVarType == "stmtLst"){
		return VT_STATEMENTLIST;
	}else if (unkVarType == "Variable" || unkVarType == "variable"){
		return VT_VARIABLELIST;
	}else if (unkVarType == "Call" || unkVarType == "call"){
		return VT_CALL;
	}else //if (unkVarType == "program" || unkVarType == "constant" || unkVarType == "program"){
		return VT_CONSTANTSTRING;
	//}
}

bool QueryValidator::identifyRelationship(std::string unkRelationship, std::string firstParam, std::string secondParam){
	cout << "relationship: " << unkRelationship << ", first Para: " << firstParam << ", second Para: " << secondParam << endl;
	
	pair<std::string, std::string> parameters = processParameters(firstParam, secondParam);
	cout << "processed para: " << parameters.first << " & " << parameters.second << endl;

	//temporary set to modifies
	QueryClass *qc;

	if (unkRelationship == "Modifies"){
		qc = new ModifiesEngine(queryManager, pkb);
	}else if (unkRelationship == "Uses"){
		qc = new UsesEngine(queryManager, pkb);		
	}else if (unkRelationship == "Calls"){
		//QueryClass qc(QT_CALLS, queryManager, pkb);		
	}else if (unkRelationship == "Calls*"){
				
	}else if (unkRelationship == "Parent"){
		qc = new ParentEngine(queryManager, pkb);
	}else if (unkRelationship == "Parent*"){
		qc = new ParentStarEngine(queryManager, pkb);	
	}else if (unkRelationship == "Follows"){	
		qc = new FollowsEngine(queryManager, pkb);
	}else if (unkRelationship == "Follows*"){
		qc = new FollowsStarEngine(queryManager, pkb);
	}else if (unkRelationship == "Next"){	
		qc = new NextEngine(queryManager, pkb);
	}else if (unkRelationship == "Next*"){
				
	}else if (unkRelationship == "Affects"){
		//QueryClass qc(QT_AFFECT, queryManager, pkb);		
	}else{ //"Affects*"
				
	}

	if (parameters.first == "null")
		return false;
	else{
		std::string firstRawVarType = getRawVariableType(parameters.first);
		std::string secondRawVarType = getRawVariableType(parameters.second);
		replaceSubstring(parameters.first, "\"", "");
		replaceSubstring(parameters.second, "\"", "");
		qc -> addParam(parameters.first, identifyVariableType(firstRawVarType));
		qc -> addParam(parameters.second, identifyVariableType(secondRawVarType));
		//qcRelationships.push_back(qc);
		queryManager -> addQueryClass(qc);
		return true;
	}
}

void QueryValidator::initCheckingVectors(){
	//queryClauses.push_back("select");
	//queryClauses.push_back("Select");
	queryClauses.push_back("such that");
	queryClauses.push_back("with");
	queryClauses.push_back("and");
	queryClauses.push_back("pattern");
	queryClauses.push_back("BOOLEAN");
	queryClauses.push_back("Such That");
	queryClauses.push_back("With");
	queryClauses.push_back("And");
	queryClauses.push_back("Pattern");
	queryClauses.push_back("boolean");

	designEntities.push_back("Program");
	designEntities.push_back("Procedure");
	designEntities.push_back("StmtLst");
	designEntities.push_back("Stmt");
	designEntities.push_back("Assign");
	designEntities.push_back("Call");
	designEntities.push_back("While");
	designEntities.push_back("If");
	designEntities.push_back("Variable");
	designEntities.push_back("Constant");
	designEntities.push_back("Prog_line");
	designEntities.push_back("program");
	designEntities.push_back("procedure");
	designEntities.push_back("stmtLst");
	designEntities.push_back("stmt");
	designEntities.push_back("assign");
	designEntities.push_back("call");
	designEntities.push_back("while");
	designEntities.push_back("if");
	designEntities.push_back("variable");
	designEntities.push_back("constant");
	designEntities.push_back("prog_line");

	queryTypes.push_back("Modifies");
	queryTypes.push_back("modifies");
	queryTypes.push_back("Uses");
	queryTypes.push_back("uses");
	queryTypes.push_back("Calls");
	queryTypes.push_back("calls");
	queryTypes.push_back("Calls*");
	queryTypes.push_back("calls*");
	queryTypes.push_back("Parent");
	queryTypes.push_back("parent");
	queryTypes.push_back("Parent*");
	queryTypes.push_back("parent*");
	queryTypes.push_back("Follows");
	queryTypes.push_back("follows");
	queryTypes.push_back("Follows*");
	queryTypes.push_back("follows*");
	queryTypes.push_back("Next");
	queryTypes.push_back("next");
	queryTypes.push_back("Next*");
	queryTypes.push_back("next*");
	queryTypes.push_back("Affects");
	queryTypes.push_back("affects");
	queryTypes.push_back("Affects*");
	queryTypes.push_back("affects*");
}

bool QueryValidator::processSelectQuery(string inputQuery){
	initCheckingVectors();
	std::vector<std::string> queryTokens;
	bool afterConnectionWords = false;

	cout << inputQuery << endl;

	/*
	//check for select clause in all the tokens to ensure there is a valid select clause
	if (std::string::npos == inputQuery.find("select")){
		cout << "no select statement found";
		return false;
	}*/

	//replace "," and ", " with space for splitting into correct tokens
	cout << "before replace: " << inputQuery << endl;
	replaceSubstring(inputQuery, ", ", " ");
	replaceSubstring(inputQuery, ",", " ");
	cout << "after replace: " << inputQuery << endl;

	queryTokens = split (inputQuery, ' ');

	cout << queryClauses.size() <<endl;

	for (std::vector<std::string>::size_type i = 0; i < queryTokens.size(); i++){
		cout << "current token is: " << queryTokens[i] << endl;
		if (queryTokens[i] == "such"){
			cout << "detected such" << endl;
			if (queryTokens[++i] == "that"){
				//detect "such that"
				if (afterConnectionWords){
					cout << "invalid query" << endl;
					return false;
				}else{
					afterConnectionWords = true;
					cout << "detected that" << endl;
				}
			}else{
				cout << "incomplete such that clause" << endl;
				return false;
			}
		}else if (std::find(queryClauses.begin(), queryClauses.end(), queryTokens[i]) != queryClauses.end()){
			//query connection words
			cout << queryTokens[i] << " is found." << endl;
			if (afterConnectionWords){
				cout << "invalid query" << endl;
				return false;
			}else{
				if (queryTokens[i] == "BOOLEAN" || queryTokens[i] == "boolean"){
					afterConnectionWords = false;
					//queryManager -> addResultExpression("BOOLEAN");
				}else
					afterConnectionWords = true;
			}
		}else if (std::find(queryTypes.begin(), queryTypes.end(), queryTokens[i]) != queryTypes.end()){
			//relationships
			cout << "RELATIONSHIPS" << endl;
			if (afterConnectionWords){
				cout << queryTokens[i+1] << ": " << queryTokens[i+2] << endl;
				if (!identifyRelationship(queryTokens[i], queryTokens[i+1], queryTokens[i+2])){
					cout << "invalid query, incorrect number of parameters for one of the relationships" << endl;
					return false;
				}
				afterConnectionWords = false;
			}else{
				cout << "invalid query, conditions not connected by AND, SUCH THAT, WITH, PATTERN etc" << endl;
				return false;
			}
			i += 3;
		}else{
			bool isVar = false;

			if (queryTokens[i] == "select" || queryTokens[i] == "Select"){
				isVar = true;
			}else{
				for (vector< pair<std::string, std::string> >::size_type varCount = 0; varCount < varList.size(); varCount++){
					if (varList[varCount].second == queryTokens[i]){
						isVar = true;
						queryManager -> addResultExpression(queryTokens[i]);
					}
				}
			}

			if (!isVar){
				cout << "invalid phrase in query sentence: " << queryTokens[i] << endl;
				return false;
			}
		}
	}

	return true;
}


std::string QueryValidator::preprocessInput(string input){
	string processedInput = "";
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
				processedInput = processedInput + ' ' + input[i];
			}else
				processedInput = processedInput + input[i];
			isEmpty = false;
		}else{
			processedInput = processedInput + input[i];
			isEmpty = false;
			isFrontBracket = false;
		}
	}

	replaceSubstring(processedInput, "( ", "(");
	replaceSubstring(processedInput, " )", ")");

	return processedInput;
}


bool QueryValidator::processInputQuery(string inputQuery){
	std::vector<std::string> inputTokens, inputVar, variableNames;

	replaceSubstring(inputQuery, "/n", "");
	replaceSubstring(inputQuery, "; ", ";");
	inputQuery = preprocessInput(inputQuery);

	cout << inputQuery << endl;

	inputTokens = split(inputQuery, ';');

	for (std::vector<std::string>::size_type i = 0; i < inputTokens.size(); i++){
		//cout << inputTokens[i] << endl;
		
		if (std::string::npos != inputTokens[i].find(" ") && std::string::npos == inputTokens[i].find("select") && std::string::npos == inputTokens[i].find("Select")){
			replaceSubstring(inputTokens[i], ", ", ",");
			inputVar = split(inputTokens[i], ' ');

			//cout << inputVar.size() << endl;
			if (inputVar.size() != 2){
				cout << "initialization of variables failed." << endl;
				return false;
			}else{
				replaceSubstring(inputVar[0], " ", "");
				
				if (std::string::npos == inputVar[1].find(",")){
					variableNames = split(inputVar[1], ',');
					for (std::vector<std::string>::size_type t = 0; t < variableNames.size(); t++){
						replaceSubstring(variableNames[t], " ", "");
						cout << inputVar[0] << ": " << variableNames[t] << endl;
						pair<std::string, std::string> varPair = std::make_pair(inputVar[0], variableNames[t]);
						queryManager -> addExpression(identifyVariableType(inputVar[0]), variableNames[t]);
						varList.push_back(varPair);
					}
				}else{
					replaceSubstring(inputVar[1], " ", "");
					cout << inputVar[0] << ": " << inputVar[1] << endl;
					pair<std::string, std::string> varPair = std::make_pair(inputVar[0], inputVar[1]);
					queryManager -> addExpression(identifyVariableType(inputVar[0]), inputVar[1]);
					varList.push_back(varPair);
				}
			}
		}else{
			if (std::string::npos == inputTokens[i].find("select") || std::string::npos == inputTokens[i].find("Select")){
				return processSelectQuery(inputTokens[i]);
			}
		}
	}
	return true;
}





