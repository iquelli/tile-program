#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int columns;
int lines;
unordered_map<string, long int> calculatedValues;

string turnToString(vector<int> &vec) {
    string str(vec.begin(), vec.end());
    return str;
}

vector<int> create_copy(vector<int> &vec) {
    vector<int> v(vec);
    return v;
}


int findRightPosition(vector<int> &numbers) {
    int biggest = numbers[0];
    int index = 0;

    for(int i=1; i<lines; i++) {
        if(numbers[i] > biggest) {
            biggest = numbers[i];
            index = i;
        }
        if(biggest == columns) {
            return index;
        }
    }

    return index;
}


bool checkIfAllZero(vector<int> &numbers) {
    for(int i=0; i<lines; i++) {
        if(numbers[i] != 0){
            return false;
        }
    }

    return true;
}


bool squareFits(vector<int> &numbers, int &size, int &line) {
    int column = numbers[line];
    for(int i = line; i< line + size; i++){
        if(!(i <= lines && numbers[i] - size >= 0 && numbers[i] == column)) {
            return false;
        }
    }
    return true;
}


long int findNumberOfConfig(vector<int> &numbers) {
    long int numberOfConfig = 0;
    auto itr = calculatedValues.find(turnToString(numbers));

    if (checkIfAllZero(numbers)) return 1;

    else if(itr != calculatedValues.end()) {
        return itr -> second;
    }

    else{
        int line = findRightPosition(numbers);
        for(int i = 1; i <= lines; i++) {
            if(squareFits(numbers, i, line)) {
                for(int j = line; j < line + i; j++) { // removes the square
                    numbers.at(j) -= i;
                }

                numberOfConfig += findNumberOfConfig(numbers);

                for(int j = line; j < line + i; j++) { // adds back the square
                    numbers.at(j) += i;
                }
            }

            else{
                break;
            }
        }

        calculatedValues.insert({turnToString(numbers), numberOfConfig});
    }

    return numberOfConfig; 
}


int main() {


    scanf("%d", &lines);
    scanf("%d", &columns);

    vector<int> numbers(lines); // initializes the  vector

    for(int i= 0; i < lines; i++){
        cin >> numbers[i];
    }

    if(lines == 0 || numbers[lines - 1] == 0) cout << "0\n";
    else {
        cout << findNumberOfConfig(numbers) << "\n";
        numbers.clear();
        calculatedValues.clear();
    }

    return 0;
}