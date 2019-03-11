#include <iostream>
#include <sstream>
#include <tuple>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Now, we will write a more generic function object , that can take any number of arguments in it's capture list
In the older example , we made explicit String captureValue. But lambda allows use to capture multiple values of multiple types 
So, we will make the capture list a "Variadic template struct" which is easily implement using "tuple". It provides the exact same 
functionality as std::pair , except it's more than two values. 

this example class simulates something like : 
auto lambdaExample = [s, endingString, limit](int i){ 
	stringstream ss;
    ss << s << ((i < limit) ? i : limit) << endingString;
    return ss.str();
  };
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename ... Next>
class MyGenericLambdaFuncObj
{
  private:
  std::tuple<Next...> captureList;
  
  public:
  void setCaptureList(std::tuple<Next...>& values) // setting the variable capture values ; can be done in constructor also
  {
    captureList = values;
  }
  
  string operator()(int i) //return value of this function is still hard coded 
  {
    stringstream ss;
    string end(std::get<1>(captureList)); //unpacking from capture list using indexes
    string start(std::get<0>(captureList));
    int limit(std::get<2>(captureList));
    ss << start << ((i < limit) ? i : limit) << end ;
    return ss.str();
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Now, we will give a capabiity of passing multiple arguments as parameters to the function operator , like this :
		auto lambdaExample = [s, endingString, limit](int i, int j, int x, int y){ 
				stringstream ss;
				ss << s << i << j << x << y << endingString;
				return ss.str();
		}; 
  
  This can be achieved using initializer_list . 
  
  Also, we will remove hard coded return type, and add "auto" to type deduce the return type. 
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename ... Next>
class MyGenericLambdaFuncObjWithMultipleArguements
{
  private:
  std::tuple<Next...> captureList;
  
  public:
  void setCaptureList(std::tuple<Next...>& values)
  {
    captureList = values;
  }
  
  auto operator()(initializer_list<int> initList) //changing return value to "auto" specifier 
  {
    stringstream ss;
    string end(std::get<1>(captureList));
    string start(std::get<0>(captureList));
    int limit(std::get<2>(captureList));
    
    for (int i : initList)
    {
      ss << ((i < limit) ? i : limit) << " ";
    }
    ss << start << ss.str() << end ;
    return ss.str();
  }
};

int main()
{

  string endingString("\n end of log");
  string s("Append Value to this log ");
  int limit(10);
  
   /////////// Testing with lambda //////////////////////////////////////////////
  auto lambdaExample = [=](int i){ 
    stringstream ss;
    ss << s << ((i < limit) ? i : limit) << endingString;
    return ss.str();
  };
  
  cout << "------lambda output-------" << endl;
  cout << lambdaExample(4) << endl ;
  
  
   /////////// Testing with MyGenericLambdaFuncObj ///////////////////////////////
  std::tuple<string,string,int> captureListAsTuple(make_tuple(s,endingString,10));
  
  MyGenericLambdaFuncObj<string,string,int> obj;
  obj.setCaptureList(captureListAsTuple);
  cout << "------MyGenericLambdaFuncObj output-------" << endl;
  cout << obj(4) << endl ;
  
  
 
  /////////// Testing with MyGenericLambdaFuncObjWithMultipleArguements ///////////////////////////////
  MyGenericLambdaFuncObjWithMultipleArguements<string,string,int> obj2;  
  obj2.setCaptureList(captureListAsTuple);
  cout << "------MyGenericLambdaFuncObjWithMultipleArguements output-------" << endl;
  cout << obj2({2,3}) << endl;
  
}



