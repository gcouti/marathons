#include <iostream>

#include <sstream>
#include <cmath>
#include <iostream>
using namespace std;

const int SIZE=1e+3+35;

int data[SIZE][SIZE];
int sum[SIZE][SIZE];
int dp[SIZE][SIZE][2];

int main()
{
    int n;
    int k;
    string in;

	while(true)
	{
	    std::getline(cin, in);
        std::istringstream is( in );

	    is >> n;

        if(n == 0) break;
		for(int i=1; i<=n; i++) {
		    std::getline(cin, in);
		    std::istringstream is( in );
			for(int j=1; j<=i; j++) {
				is >> data[i][j];
				sum[i][j]=(sum[i-1][j]+sum[i-1][j-1]-(i-2>=0?sum[i-2][j-1]:0))+data[i][j];
				dp[i][j][0]=dp[i][j][1]=0;
            }
        }

		int ans=0;
		for(int j=1; j<=n; j++) {
			for(int i=j; i<=n; i++) {
				dp[i][j][0]=sum[i][j];
				dp[i][j][0]=max(dp[i][j][0], dp[i-1][j-1][1]+(sum[i][j]-sum[i-1][j-1]));
				ans=std::max(ans, dp[i][j][0]);
			}
			dp[n][j][1]=dp[n][j][0];
			for(int i=n-1; i>=j; i--)
				dp[i][j][1]=max(dp[i+1][j][1], dp[i][j][0]);
		}
		cout << ans << endl;
	}

	return 0;
}