#include <iostream>
using namespace std;

/**
 * This is the solution for the URI online problem
 *
 * problem: https://www.urionlinejudge.com.br/judge/pt/problems/view/1001
 */

int main()
{
  int a, b, c, d;
  std::cin >> a;
  std::cin >> b;
  std::cin >> c;
  std::cin >> d;
  printf("DIFERENCA = %d\n",(a*b - c*d));
	return 0;
}
