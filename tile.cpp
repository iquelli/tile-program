#include <iostream>
#include <cstdio>

using namespace std;

int columns;
int lines;
int numberOfConfig = 0;

int findRightPosition(int numbers[]) {
    int biggest = numbers[0];
    int index = 0;

    for(int i=0; i<lines; i++) {
        if(numbers[i] > biggest) {
            biggest = numbers[i];
            index = i;
        }
    }

    return index;
}

bool checkIfAllZero(int numbers[]) {
    for(int i=0; i<lines; i++) {
        if(numbers[i] != 0){
            return false;
        }
    }

    return true;
}

int findNumberOfConfig(int numbers[]) {
    if(checkIfAllZero(numbers)){
        return 1;
    }
    else{
        int line = findRightPosition(numbers);

        for(int i = 1; i <= line + 1; i++) {

            if(line + 1 - i >= 0 && numbers[line] - i >= 0) {
                numbers[line] -= i;
                numberOfConfig += findNumberOfConfig(numbers);
                numbers[line] += i;
                printf("%d\n",numberOfConfig);
            }

            else {
                break;
            }
        }
    }

    return numberOfConfig; 
}

int main() {
    
    scanf("%d", &lines);
    scanf("%d", &columns);

    int numbers[lines];

    for(int i= 0; i < lines; i++){
        scanf("%d", &numbers[i]);
    }

    if(lines == 0) {
        cout << "0\n";
    }
    else {
        cout << findNumberOfConfig(numbers) << "\n";
    }

    return 0;
}