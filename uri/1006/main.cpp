#include <iostream>
using namespace std;

/**
 * This is the solution for the URI online problem
 *
 * problem: https://www.urionlinejudge.com.br/judge/pt/problems/view/1001
 */

int main()
{
  double a, b, c;
  std::cin >> a;
  std::cin >> b;
  std::cin >> c;
  printf("MEDIA = %.1f\n",(((2*a)+(3*b)+(5*c))/10));
	return 0;
}
