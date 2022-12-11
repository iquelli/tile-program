#include <iostream>
#include <vector>
#include <map>

using namespace std;

int columns;
int lines;
map<vector<int>, long int> calculatedValues;

vector<int> create_copy(vector<int> vec)
{
    vector<int> v(vec);
    return v;
}

int findRightPosition(vector<int> numbers) {
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
    auto itr = calculatedValues.find(numbers);

    if(checkIfAllZero(numbers)){
        return 1;
    }

    else if(itr != calculatedValues.end()) {
        printf("entrou aqui\n");
        return itr -> second;
    }

    else{
        long int numberOfConfig = 0;
        int line = findRightPosition(numbers);
        for(int i = 1; i <= lines; i++) {

            if(squareFits(numbers, i, line)) {

                printf("valor de numeros: ");
                for(int j = 0; j<lines; j++) {
                    printf("%d  ", numbers[j]);
                }
                printf("\n");

                vector<int> numbers2 = create_copy(numbers);
                for(int j = line; j < line + i; j++) { // removes the square
                    numbers2[j] -= i;
                }
                printf("depois de tirar quadrado: ");
                for(int j = 0; j<lines; j++) {
                    printf("%d  ", numbers2[j]);
                }
                printf("\n");

                numberOfConfig += findNumberOfConfig(numbers2);
                printf("numero config: %d\n", numberOfConfig);
                printf("quadrado que vamor adicionar com aquela config: ");
                for(int j = 0; j<lines; j++) {
                    printf("%d  ", numbers[j]);
                }
                printf("\n\n");
                calculatedValues.insert({numbers, numberOfConfig});
            }

            else{
                break;
            }
        }
    }

    return itr->second; 
}

int main() {
    bool allZero = true;

    scanf("%d", &lines);
    scanf("%d", &columns);

    vector<int> numbers(lines); // initializes vector

    for(int i= 0; i < lines; i++){
        cin >> numbers[i];
        if(numbers[i] != 0) allZero = false;
    }

    if(lines == 0 || allZero) {
        cout << "0\n";
    }
    else {
        cout << findNumberOfConfig(numbers) << "\n";
        numbers.clear();
    }

    return 0;
}