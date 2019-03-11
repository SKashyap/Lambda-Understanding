#include <iostream>
#include <sstream>
using namespace std;


// Lambda is essentially a nameless function object/functor that can be created exactly at the place of useage and discared. 
// unlike the global function pointer def's which hang around till app exit and clutter the app

/*consider a lambda example which takes in a local "string s" , appends the value of an input argument "i" and returns resultant string

  auto lambdaExample = [s](int i){ 
    stringstream ss;
    ss << s << i;
    return ss.str();
  };
  
  Let us implement thsi using older c++ function objects
  
*/


/*Function Objects (Functors) - C++ allows the function call operator() to be overloaded, 
such that an object instantiated from a class can be "called" like a function.*/

class MyLambdaFuncObj
{
  private:
  string captureVariable;
  
  public:
  MyLambdaFuncObj(const string& input):captureVariable(input) {}
  string operator()(int i)
  {
    stringstream ss;
    ss << captureVariable << i;
    return ss.str();
  }
};
                             

int main()
{
  //functionObj obj;
  string s("Append Value to this log ");
  auto lambdaExample = [s](int i){ 
    stringstream ss;
    ss << s << i;
    //s = ss.str();
    return ss.str();
  };
  
  cout << "------lambda output-------" << endl;
  cout << lambdaExample(4) << endl ;
  
  cout << "------MyLambdaFuncObj output-------" << endl;
  MyLambdaFuncObj obj(s);
  cout << obj(4) << endl ;
}