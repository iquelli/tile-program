#include <iostream>
#include <vector>

using namespace std;

int columns;
int lines;
int numberOfConfig = 0;

vector<int> create_copy(vector<int> vec)
{
    vector<int> v(vec);
    return v;
}

int findRightPosition(vector<int> numbers) {
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

bool checkIfAllZero(vector<int> numbers) {
    for(int i=0; i<lines; i++) {
        if(numbers[i] != 0){
            return false;
        }
    }

    return true;
}

bool squareFits(vector<int> numbers, int size, int line) {
    int line1 = numbers[line];
    for(int i = line; i< line + size; i++){
        if(!(i <= lines && numbers[i] - size >= 0 && numbers[i] == line1)) {
            return false;
        }
    }
    return true;
}

int findNumberOfConfig(vector<int> numbers) {

    if(checkIfAllZero(numbers)){
        numberOfConfig++;
        return 0;
    }

    else{

        for(int i = 1; i <= lines; i++) {
            int line = findRightPosition(numbers);

            if(squareFits(numbers, i, line)) {
                vector<int> numbers2 = create_copy(numbers);
                for(int j = line; j < line + i; j++) { // removes the square
                    numbers2[j] -= i;
                }

                findNumberOfConfig(numbers2);
            }

            else{
                break;
            }
        }
    }

    numbers.clear();

    return numberOfConfig; 
}

int main() {
    
    scanf("%d", &lines);
    scanf("%d", &columns);

    vector<int> numbers(lines);

    for(int i= 0; i < lines; i++){
        cin >> numbers[i];
    }

    if(lines == 0) {
        cout << "0\n";
    }
    else {
        cout << findNumberOfConfig(numbers) << "\n";
        numbers.clear();
    }

    return 0;
}