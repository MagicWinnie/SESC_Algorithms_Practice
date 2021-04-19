#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <cstring>
#include <iomanip>

using namespace std;

void swap_m(int *r, int *s)
{
    int temp = *r;
    *r = *s;
    *s = temp;
} 

int part(int *arr, int l, int h)
{
    int opor = arr[(l + h)/2];
    int i = l - 1;
    int j = h + 1;
    while (1)
    {
        i++;
        while (arr[i] < opor)
            i++;
        
        j--;
        while (arr[j] > opor)
            j--;

        if (i >= j) return j;
        swap_m(&arr[i], &arr[j]);
    }
}

void quickSort(int *arr, int l, int h)
{
    if (l < h)
    {
        int ind = part(arr, l, h);
        quickSort(arr, l, ind);
        quickSort(arr, ind + 1, h);
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
    quickSort(arr, 0, n - 1);
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