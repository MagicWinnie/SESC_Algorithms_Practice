#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <cstring>
#include <iomanip>

using namespace std;

void shellSort(int arr[], int n)
{
    int i = 0, d = 1;
    
    while (d*3 < n){
        if (i % 2 == 0) d = 9 * pow(2, i) - 9 * pow(2, i / 2) + 1;
        else d = 8 * pow(2, i) - 6 * pow(2, (i + 1) / 2) + 1;

        for (int j = d; j < n; j++)
        {
            int k = j;
            int temp = arr[j];

            while (k >= d && arr[k - d] > temp)
            {
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

    // vector<int> arr;
    

    int current_number = 0, n, i = 0;
    inp >> n;
    int *arr = (int*)malloc(n*sizeof(int));
    while (inp >> current_number){
        arr[i] = current_number;
        i++;
    }
    inp.close();

    auto start = chrono::steady_clock::now();
    shellSort(arr, n);
    auto end = chrono::steady_clock::now();

    auto diff = end - start;

    ofstream out(argv[2], std::ios::out | std::ios::trunc);
    cout << "[DEBUG] Error: " << strerror(errno) << endl;
    cout << "[DEBUG] File path: " << argv[2] << endl;

    out << chrono::duration <double, milli> (diff).count() << "\n";
    for(int i = 0; i < n; i++){
        out << arr[i] << " " ;
    }
    out.close();

    return 0;
}
