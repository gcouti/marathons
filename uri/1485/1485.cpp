#include <iostream>

#include <sstream>
#include <cmath>
#include <iostream>
using namespace std;

#define INF 999999999;

/**
 * This is the solution for the URI online problem
 *
 * problem: https://www.urionlinejudge.com.br/judge/pt/problems/view/1485
 */

int *readVector(int size) {
    string in;
    int* v = new int[size];

    std::getline(cin, in);
    std::istringstream is( in );

    for(int i = 0; i< size; i++){
        is >> v[i];
    }

    return v;
}

int* sumVector(int s[], int size){
    int* sum = new int[size];
    sum[0] = s[size-1] + s[0];
    for(int i=1; i<size; i++){
        sum[i] = s[i-1] + s[i];
    }

    return sum;
}

int main()
{
    string test = "";
    string in;

	while(true){

	    std::getline(cin, in);
	    std::istringstream is( in );

        if (in == "0 0") break;

        int sSize, bSize;
        is >> sSize;
        is >> bSize;

        int* s = readVector(sSize);
        int* b = readVector(bSize);
        int* sum = sumVector(s, sSize);

        int result = INF;
        int** matrix = new int*[bSize];
        int* choosed = new int[bSize];

        for (int i = 0; i < bSize; ++i) matrix[i] = new int[sSize];

        for(int si=0;si<sSize;si++){
            int firstSelected = true;
            int offset = 0;
            int lowestRowValue = INF;

            for(int j=0; j < (sSize - 2*(bSize -1)); j++){

                int newJ = (si + j) % sSize;
                matrix[0][j] = sum[newJ] * b[0];

                if (j!=0 && matrix[0][0] == matrix[0][j]){
                    firstSelected = false;
                    offset = j;
                }

                if(j!=0 && matrix[0][j-1] < matrix[0][j]){
                    matrix[0][j] = matrix[0][j-1];
                }

                if(matrix[0][j] < lowestRowValue){
                    if(j>0) firstSelected = false;
                    choosed[0] = j;
                    lowestRowValue = matrix[0][j];
                }
            }

            for (int i = 1; i < bSize; ++i){
                lowestRowValue = INF;

                for(int j=i*2; j < (sSize - 2*(bSize -i -1)); j++){
                    int index = (j < 2) ? sSize - 2 +j: j -2;
                    int value = (sum[(si + j)%sSize] * b[i]) + matrix[i-1][index];

                    if(j == i*2){
                        matrix[i][j] = value;
                    }
                    else {
                        if(value < matrix[i][j-1]){
                            matrix[i][j] = value;
                        }
                        else{
                            matrix[i][j] = matrix[i][j-1];
                            offset = j;
                        }
                    }

                    if(matrix[i][j] < lowestRowValue){
                        if( firstSelected && j == sSize-1) continue;

                        choosed[i] = j;
                        lowestRowValue = matrix[i][j];
                    }
                }

                if(choosed[i] >= (i*2) && choosed[i] <= (i*2) + offset) firstSelected = true;

            }

            result = lowestRowValue < result? lowestRowValue: result;
        }

//        delete[] s;
//        delete[] b;
//        delete[] choosed;

	    cout << (-1*result) << endl;
	}

	return 0;
}
