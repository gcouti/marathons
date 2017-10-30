#include <iostream>
using namespace std;

void playTurn(int *permutation, int size) {
    int change = 0;

    for (int i = 0; i < size; i++) {
        while(permutation[i] != i + 1) {
            int value = permutation[i];
            permutation[i] = permutation[value - 1];
            permutation[value - 1] = value;
            change++;
        }
    }

    if (change % 2 == 1) {
        cout << "Marcelo" << endl;
    }
    else {
        cout << "Carlos" << endl;
    }
}

int main(void) {
    while (true) {
        int size;
        cin >> size;

        if (size == 0) break;
        else {
            int* permutation = new int[size];

            for (int i = 0; i < size; i++) {
                int x;
                cin >> x;
                permutation[i] = x;
            }

            playTurn(permutation, size);
        }
    }

    return 0;
}

