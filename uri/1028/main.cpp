#include <iostream>

#include <sstream>
#include <cmath>
#include <iostream>

using namespace std;

/**
 * This is the solution for the URI online problem
 *
 * problem: https://www.urionlinejudge.com.br/judge/pt/problems/view/1028
 */

int main()
{
    int n; 
    string in; 
    
    std::getline(cin, in);
    std::istringstream is( in );

    is >> n;

    while ( n > 0 ) {
      

      std::getline(cin, in);
      std::istringstream is( in );
      
      int a, b;
      
      is >> a;
      is >> b; 
      
      do {  
        int rest = std::abs(a - b);
        
        a = b;
        b = rest;
      } 
      while( a != b );
      
      
      cout << a << endl;
      --n;
    }
    
	  return 0;
}
