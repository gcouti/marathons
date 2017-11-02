#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>
#include <iterator>
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}
#include <iostream>

#include <sstream>
#include <cmath>
#include <iostream>
using namespace std;

#define INF 999999999;

bool DEBUG=false;

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


bool isIn(int *array, int arraySize, int element){
    for(int i=0;i<arraySize;i++){
        if(array[i] == element){
            return true;
        }
    }

    return false;
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

        if (in == "0 0"){
            break;
        }
        int sSize, bSize;
        is >> sSize;
        is >> bSize;

        int* s = readVector(sSize);
        int* b = readVector(bSize);
        int* sum = sumVector(s, sSize);

        if(DEBUG){
            test = "";
            for(int i=0; i<sSize; i++){
                test += patch::to_string(s[i]) + " ";
            }
            cout << "Roulette: " <<test << endl;

            test = "";
            for(int i=0; i<bSize; i++){
                test += patch::to_string(b[i]) + " ";
            }
            cout << "Balls: " <<test << endl;
            test = "";
            for(int i=0; i<sSize; i++){
                test += patch::to_string(sum[i]) + " ";
            }
            cout << "Sum: " <<test << endl;
        }

        int result = 99999999;
        int** matrix = new int*[bSize];
        int* choosed = new int[bSize];

        for (int i = 0; i < bSize; ++i){
            matrix[i] = new int[sSize];
            for(int j=0; j < sSize; j++){
                matrix[i][j] =0;
            }
        }

        for(int si=0;si<sSize;si++){
            int isFirst = true;
            int lowestRowValue = INF;
            int previousRowValue = INF;

            for(int j=0; j < (sSize - 2*(bSize -1)); j++){
                int newJ = (si + j) % sSize;
                matrix[0][j] = sum[newJ] * b[0];

                if (j!=0 && matrix[0][j-1] == matrix[0][j]){
                    isFirst = false;
                }

                if(j!=0 && matrix[0][j-1] < matrix[0][j]){
                    matrix[0][j] = matrix[0][j-1];
                }

                if(matrix[0][j] < lowestRowValue){
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
                        matrix[i][j] = value < matrix[i][j-1]? value:matrix[i][j-1] ;
                    }

                    if(matrix[i][j] < lowestRowValue){

                        if(j == sSize-1 && isFirst) continue;
                        lowestRowValue = matrix[i][j];
                    }
                }
            }

            if(DEBUG){
                cout << "Lowest: " << lowestRowValue << endl;
                test = "";
                for(int i=0; i<sSize; i++){
                    test += patch::to_string(sum[(si + i)%sSize]) + "\t";
                }
                cout << "S: \n" <<test << endl;

                test = "";
                for(int i=0; i<bSize;i++){
                    for(int j=0; j<sSize; j++){
                        test += patch::to_string(matrix[i][j]) + "\t";
                    }
                     test += "\n";
                }

                cout << "_ \n" << test << endl;
            }
            result = lowestRowValue < result? lowestRowValue: result;
        }

        delete[] s;
        delete[] b;

	    cout << (-1*result) << endl;
	}

	return 0;
}
