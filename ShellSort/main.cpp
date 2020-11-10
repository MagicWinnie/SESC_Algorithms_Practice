#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

void shellSort(vector<int> &arr)
{
    int i = 0, d = 1, n = arr.size();
    
    while (d*3 < n){
        if (i % 2 == 0) d = 9 * pow(2, i) - 9 * pow(2, i / 2) + 1;
        else d = 8 * pow(2, i) - 6 * pow(2, (i + 1) / 2) + 1;

        for (int j = d; j < n; j++) {
            int k = j;
            int temp = arr[j];

            while (k >= d && arr[k - d] > temp) {
                arr[k] = arr[k - d];
                k -= d;
            }

            arr[k] = temp;
        }
        i++;
    }
}


int main(int argc, char **argv)
{
    if (argc < 2) return -1;

    ifstream inp(argv[1]);
    vector<int> vec;

    int current_number = 0;
    while (inp >> current_number){
        vec.push_back(current_number);
    }
    inp.close();

    shellSort(vec);

    ofstream out ("output.txt");
    for(int i = 0; i < vec.size(); i++){
        out << vec[i] << " " ;
    }
    out.close();

    return 0;
}