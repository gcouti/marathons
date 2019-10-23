#include <iostream>
using namespace std;

/**
 * This is the solution for the URI online problem
 *
 * problem: https://www.urionlinejudge.com.br/judge/pt/problems/view/1001
 */

int main()
{
  double a, b;
  std::cin >> a;
  std::cin >> b;
  printf("MEDIA = %.5f\n",(((3.5*a)+(b*7.5))/11));
	return 0;
}
