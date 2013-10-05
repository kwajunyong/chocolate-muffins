#include <sstream>
#include "CommonUtility.h"
using namespace std;

  string NumberToString ( int Number )
  {
     ostringstream ss;
     ss << Number;
     return ss.str();
  }