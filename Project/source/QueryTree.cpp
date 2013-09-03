#include "QueryTree.h"

QueryTree::QueryTree() {
}

void QueryTree::addQueryClass(QueryClass *qc) {
	queryList.push_back(qc);
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