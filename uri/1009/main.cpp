#include <iostream>
using namespace std;

/**
 * This is the solution for the URI online problem
 *
 * problem: https://www.urionlinejudge.com.br/judge/pt/problems/view/1009
 */

int main()
{
  char a[256];
  float b, c;

  std::cin >> a;
  std::cin >> b;
  std::cin >> c;
  printf("TOTAL = R$ %.2f\n",(b + c*.15));
	
  return 0;
}
