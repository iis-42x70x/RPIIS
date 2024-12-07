#include <iostream>
#include <vector>

using namespace std;

int countChords(vector<vector<int>> incidenceMatrix) {
    int n = incidenceMatrix.size();
    int chords = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (incidenceMatrix[i][j] == 0) {
                int k = -1;
                for (int l = 0; l < n; l++) {
                    if (incidenceMatrix[i][l] == 1 && incidenceMatrix[j][l] == 1) {
                        k = l;
                        break;
                    }
                }

                if (k != -1) {
                    bool isChord = true;
                    for (int m = 0; m < n; m++) {
                        if (m != i && m != j && incidenceMatrix[i][m] == 1 && incidenceMatrix[j][m] == 1 && incidenceMatrix[k][m] == 1) {
                            isChord = false;
                            break;
                        }
                    }

                    if (isChord) {
                        chords++;
                    }
                }
            }
        }
    }
    return chords;
}

int main() {
    setlocale(LC_ALL, "RU");
    vector<vector<int>> incidenceMatrix = {
        {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0}
    };

    int result = countChords(incidenceMatrix);
    cout << "Число хорд в неориентированном графе: " << result << endl;
    return 0;
}
