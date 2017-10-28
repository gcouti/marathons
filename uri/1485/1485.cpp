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

void merge(int list[], int lower, int upper, int pivot, bool abs)
{
    int* leftArray = NULL;
    int* rightArray = NULL;
    int i, j, k;
    int n1 = pivot - lower + 1;
    int n2 = upper - pivot;
    leftArray = new int[n2];
    rightArray = new int[n1];
    for (i = 0; i < n1; i++)
        rightArray[i] = list[lower + i];
    for (j = 0; j < n2; j++)
        leftArray[j] = list[pivot + 1 + j];

    i = 0;
    j = 0;
    k = lower;


    while (i < n1 && j < n2)
    {
        int leftValue = leftArray[i];
        int rightValue = rightArray[j];

        if (abs){
            leftValue = std::abs(leftValue);
            rightValue = std::abs(rightValue);
        }

        if (leftValue <= rightValue)
        {
            list[k] = rightArray[i];
            i++;
        }
        else
        {
            list[k] = leftArray[j];
            j++;
        }

        k++;
    }

    while (i < n1)
    {
        list[k] = rightArray[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        list[k] = leftArray[j];
        j++;
        k++;
    }

    delete [] leftArray;
    delete [] rightArray;
}

void mergeSort(int list[], int lower, int upper, bool abs)
{
    int pivot;

    if (upper > lower)
    {
        pivot = ( lower + upper) / 2;
        mergeSort(list, lower, pivot, abs);
        mergeSort(list, pivot + 1, upper, abs);
        merge(list, lower, upper, pivot, abs);
    }
}


bool isIn(int *array, int arraySize, int element){
    for(int i=0;i<arraySize;i++){
        if(array[i] == element){
            return true;
        }
    }

    return false;
}


int* removeElementsArray(int * array, int* remove, int removeSize, int &size){
    int index = -1;
    int newSize = size -removeSize;
    if (newSize <= 0){
        size =0;
        return array;
    }

    int *newArray = new int[newSize];
    for(int j=0;j<size;j++){
        if(isIn(remove,removeSize, j)){
            continue;
        }
        index += 1;
        newArray[index] = array[j];
    }
    size = newSize;
    return newArray;
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
//    int size = 7;
//    int a[size] = {0,1,-14,3,4,-5,6};
//
    string test = "";
//    for(int i=0; i<size; i++){
//        test += patch::to_string(a[i]) + " ";
//    }
//    cout << "Vb:  "<< test << endl;
//
//    mergeSort(a, 0, size -1, true);
//
//    test = "";
//    for(int i=0; i<size; i++){
//        test += patch::to_string(a[i]) + " ";
//    }
//
//    cout << "Va:  "<< test << endl;

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
        int** matrix = new int*[bSize +1];
        int* choosed = new int[sSize];

        for (int i = 0; i < bSize; ++i){
            matrix[i] = new int[sSize];
            for(int j=0; j < sSize; j++){
                matrix[i][j] =0;
            }
        }

        for(int si=0;si<sSize;si++){
            int* choosed = new int[sSize];
            int lowestRowValue = 99999999;
            for(int j=0; j < sSize; j++){
                int newJ = (si + j)%sSize;
                matrix[0][j] = sum[newJ] * b[0];
                if(j!=0 && matrix[0][j-1] < matrix[0][j]){
                    matrix[0][j] = matrix[0][j-1];
                }
                if(matrix[0][j] < lowestRowValue){
                    lowestRowValue = matrix[0][j];
//                    cout << j << endl;
                    choosed[0] = j;
                }
            }

            for (int i = 1; i < bSize; ++i){
                lowestRowValue = 99999999;
                for(int j=0; j < sSize; j++){
                    int index = (j < 2) ? sSize - 2 +j: j -2;
                    int value = (sum[(si + j)%sSize] * b[i]) + matrix[i-1][index];
//                     if(j == i*2){
//                        matrix[i][j] = value;
//                    }
//                    else {
                        matrix[i][j] = value; //< matrix[i][j-1]? value:matrix[i][j] ;
//                    }
                    int previousIndex = j==0? sSize-1: j -1;
                    int nextIndex = j==sSize-1?0:j+1;

//                    cout << "A: " << previousIndex << endl;
//                    cout << "N: " << nextIndex << endl;

                    if(matrix[i][j] < lowestRowValue && !isIn(choosed, sSize, j) && !isIn(choosed,sSize,previousIndex)){
                        lowestRowValue = matrix[i][j];
                        choosed[i-1] = previousIndex;
                        choosed[i] = j;
                    }
                }

                if(DEBUG){
                    test = "";
                    for(int i=0; i<bSize;i++){
                        for(int j=0; j<sSize; j++){
                            test += patch::to_string(matrix[i][j]) + "\t";
                        }
                        test += "\n";
                    }
                    cout << "Lowest: " << result << endl;
                    cout << "After Matrix: \n" << test << endl;
                }
            }


            result = lowestRowValue < result? lowestRowValue: result;
            delete[] choosed;
        }


        delete[] s;
        delete[] b;

	    cout << (-1*result) << endl;
	}

	return 0;
}
