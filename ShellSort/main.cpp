#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>

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
    if (argc < 3) return -1;

    ifstream inp(argv[1]);
    vector<int> vec;

    int current_number = 0;
    while (inp >> current_number){
        vec.push_back(current_number);
    }
    inp.close();

    auto start = chrono::steady_clock::now();
    shellSort(vec);
    auto end = chrono::steady_clock::now();

    auto diff = end - start;

    ofstream out (string("output\\") + argv[2] + ".txt");

    out << chrono::duration <double, milli> (diff).count() << "\n";
    for(int i = 0; i < vec.size(); i++){
        out << vec[i] << " " ;
    }
    out.close();

    return 0;
}