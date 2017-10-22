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

bool DEBUG=true;

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
    leftArray = new int[n1];
    rightArray = new int[n2];
    for (i = 0; i < n1; i++)
        leftArray[i] = list[lower + i];
    for (j = 0; j < n2; j++)
        rightArray[j] = list[pivot + 1 + j];

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

        int** matrix = new int*[bSize +1];
        for (int i = 0; i <= bSize; ++i){
            matrix[i] = new int[sSize];
            for(int j=0; j < sSize; j++){
                matrix[i][j] = 0;
            }
        }

        mergeSort(b,0,bSize-1, true);

        int *result = new int[bSize+1];
        for(int i=0; i<bSize;i++ ){
            result[i] = 0;
        }

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
        }

        for(int i=1;i<=bSize;i++){
            int lowestRowResult = 9999999;
            int bestIndex = -1;
            int bestSupportIndex = -1;
            for(int j=0;j<sSize;j++){
                int supportIndex =  (j > 0)? j-1 : sSize-1;
//                if(matrix[0][j] != 1 && matrix[0][supportIndex] != 1){
                int rowValue = result[i-1] + (sum[j] * b[i-1]);
                matrix[i][j] = rowValue;

                if(rowValue < lowestRowResult && matrix[0][j] != 1 &&  matrix[0][supportIndex] != 1 ){
                    lowestRowResult = rowValue;
                    bestIndex = j;
                    bestSupportIndex = supportIndex;
                }
            }

            int total = 0;
            bool hasIndex = false;
            for(int j=0;j<sSize;j++){
                int supportIndex =  (j > 0)? j-1 : sSize-1;
                if(matrix[i][j] == lowestRowResult && matrix[0][j] == 0){
                    hasIndex = true;
                    matrix[0][j] = -1*i;
                    total ++;
                    matrix[0][supportIndex] = -1*i;
                    total ++;
                }
            }
            result[i] = lowestRowResult;

            if(!hasIndex || total == 2){
                matrix[0][bestIndex] = 1;
                matrix[0][bestSupportIndex] = 1;
            }

            if(DEBUG){
                        cout << "Total: " << total << endl;
                        cout << "L: " << lowestRowResult << endl;
                        test = "";
                        for(int i=0; i<=bSize;i++){
                            for(int j=0; j<sSize; j++){
                                test += patch::to_string(matrix[i][j]) + "\t";
                            }
                            test += "\n";
                        }
                        cout << "After Matrix: \n" << test << endl;
                    }



//            for(int j=0;j<sSize;j++){
//                if(){
//                    matrix[0][j] =
//                }
//            }


        }


//        int indexesSize = sSize;
//        int* indexes = new int[sSize];
//        for(int i=0;i<sSize;i++){
//            indexes[i] = i;
//        }
//
//        int chosen = 0;
//        int chosenPrevious = indexesSize-1;
//        for(int i=bSize-1; i>=0; i--){
//            if(rouletteLoop){
//                chosen = indexes[0];
//                chosenPrevious = indexes[indexesSize-1];
//            }
//            else {
//            if(DEBUG){
//                            test = "";
//                            for(int i=0; i<indexesSize; i++){
//                                test += patch::to_string(indexes[i]) + " ";
//                            }
//                             cout << "Index List: " << test << endl;
//                        }
//
//                int j = 1;
//                do{
//                    chosen = indexes[j];
//                    chosenPrevious = indexes[j-1];
//                    j++;
//                }
//                while(indexes[j] -1 != indexes[j-1]);
//            }
//
//            int minValue = (s[chosen] + s[chosenPrevious]) * b[i];
//
//            if(DEBUG){
//                cout << "indexes: " << chosenPrevious << " and " << chosen << endl;
//                cout << "(" << s[chosen] << " + " << s[chosenPrevious] << ") * " << b[i] << " = "<< minValue<< endl;
//            }
//
//            for(int j=chosen+1; j<indexesSize; j++){
//                if(indexes[j] -1 > indexes[j-1]){
//                    continue;
//                }
//                int newValue = (s[indexes[j-1]] + s[indexes[j]]) * b[i];
//                if(minValue >= newValue){
//                    minValue = newValue;
//                    chosen = indexes[j];
//                    chosenPrevious = chosen-1;
//                }
//            }
//
//            if(DEBUG){
//               cout << "final indexes: " << chosenPrevious << " and " << chosen << endl;
//               cout << "final value: " << minValue << " for: " << b[i] << endl;
//            }
//
//            if(chosenPrevious == sSize -1 || chosenPrevious == 0){
//                if(DEBUG){
//                    cout << "Use de last loop" <<  endl;
//                }
//                rouletteLoop = false;
//            }
//
//            result += -1*minValue;
//            int removeArray[] = {chosenPrevious, chosen};
//            indexes = removeElementsArray(indexes, removeArray,2, indexesSize);
//
//
//            if(DEBUG){
//                test = "";
//                for(int i=0; i<indexesSize; i++){
//                    test += patch::to_string(s[indexes[i]]) + " ";
//                }
//                 cout << "Index List: " << test << endl;
//            }
//        }
//
//
        delete[] s;
        delete[] b;

	    cout << (result[bSize]*-1) << endl;
	}

	return 0;
}
