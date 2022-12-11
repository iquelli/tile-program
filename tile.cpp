#include <iostream>
#include <vector>

using namespace std;

int columns;
int lines;
long int numberOfConfig = 0;
int mod = (int) (1e9 + 9);

long int calculateTotalPaths(int n, int m, vector< vector< int> > &mat) {
    for(int i = 0; i < n; i++) {
        for(int j =0; j<m; j++) {
            cout << mat[i][j] << "  ";
        }
        cout << "\n";
    }

    vector<int> prev(m,0);
    for(int i=0; i<n; i++) {
        vector<int> cur(m,0);
        for(int j = 0; j<m; j++) {
            if(mat[i][j] == -1) cur[j] = 0;
            else if(i == 0 && j == 0) cur[j] = 1;
            else {
                int up = 0, left = 0;
                if(i>0) up = prev[j];
                if(j>0) left = cur[j-1];
                cur[j] = (up+left) %mod; 
            }  
        }

        prev = cur;
    }
    return prev[m-1];
}

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
        if(biggest == lines) {
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

    if(checkIfAllZero(numbers)){
        numberOfConfig++;
        return 0;
    }

    else{
        int line = findRightPosition(numbers);
        for(int i = 1; i <= lines; i++) {

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
    //initializes vector
    vector<vector<int>> grid(lines, vector<int>(columns, 0));

    for(int i= 0; i < lines; i++){
        cin >> numbers[i];
        for(int j=numbers[i]; j < columns; j++) {
            grid[i][j] = -1;
        }
    }

    if(lines == 0) {
        cout << "0\n";
    }
    else {
        int paths = calculateTotalPaths(lines, columns, grid);
        grid.clear();
        cout << paths <<"\n";
        cout << findNumberOfConfig(numbers) << "\n";
        numbers.clear();
    }

    return 0;
}