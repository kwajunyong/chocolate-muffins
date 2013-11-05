#include "QueryTree.h"

QueryTree::QueryTree() {
}

void QueryTree::addQueryClass(QueryClass *qc) {
	// Mode 1
	//queryList.push_back(qc);

	// Mode 2
	QueryNode *qn = new QueryNode(qc);
	VariableDict::iterator iterFound;
	QueryNodeList::iterator iterQueryNode;
	vector<ASTParameter*> paramList = qc->getParameterList();
	vector<ASTParameter*>::iterator iterParam;
	// Here is what happened
	// Step :
	// 1. Find the QueryNode who is having the same variable name 1 and name 2
	// 2. Add those found QueryNode List into its own arm
	// 3. Do the reverse : Iterate thru the query node list and add the new one to them as well. 

	// the query node now supports 2 arm, not overengineered since no features can be added further. But can be extended fairly easy. 
	bool rightArm = false;
	for (iterParam = paramList.begin(); iterParam != paramList.end(); iterParam++) {
		if ((*iterParam)->updateAble()) {
			iterFound =variableDictionary.find((*iterParam)->getVariableName());

			if (iterFound != variableDictionary.end()) {
				
				for (iterQueryNode = iterFound->second.begin(); iterQueryNode != iterFound->second.end(); iterQueryNode++) {
					
					//step 2
					if (!rightArm) {
						qn->addLeftArm(*iterQueryNode);						
					} else 
						qn->addRightArm(*iterQueryNode);						

				
					// step 3
					if ((*iterQueryNode)->getVariable1Name().compare((*iterParam)->getVariableName()) == 0) 
						(*iterQueryNode)->addLeftArm(qn);
					else 
						(*iterQueryNode)->addRightArm(qn);										
				}

				// updated to the list
				iterFound->second.push_back(qn);

			} else {  // if the variable don't exists then create new one 
				QueryNodeList newQueryNodeList;
				variableDictionary[(*iterParam)->getVariableName()] = newQueryNodeList;

			}			
		} // updateable
		rightArm = true;
	}

	


}

QueryClass *QueryTree::pop() { // pop one now, will pop more than one if they are the same generation. 
	QueryClass *qc = queryList[0];

	queryList.erase(queryList.begin());
	
	return qc;


}

bool QueryTree::isEmpty() {
	return queryList.empty();
}

void QueryTree::clear() {

	vector<QueryClass*>::iterator iter;

	for (iter = queryList.begin(); iter != queryList.end(); iter++) {
	    delete (*iter);

	}

	queryList.clear();
}