#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;

void sink(int *arr, int ind, int m)
{
    int big, l, r;

    while(ind < m)
    {
        big = ind;
        l = 2*ind + 1;
        r = l + 1;

        if (l < m && arr[l] > arr[big])
            big = l;
        if (r < m && arr[r] > arr[big])
            big = r;
        if (big == ind) return;
        swap(arr[ind], arr[big]);
        ind = big;
    }
}

void build_heap(int *arr, int n)
{
    int ind = n/2 - 1;
    
    while (ind >= 0)
    {
        sink(arr, ind, n);
        ind--;
    }
}

void heapSort(int *arr, int n)
{
    build_heap(arr, n);

    int end = n - 1;

    while (end >= 0)
    {
        swap(arr[0], arr[end]);
        sink(arr, 0, end);
        end--;
    }
}

int main(int argc, char **argv)
{
    if (argc < 3) return -1;

    ifstream inp(argv[1]);

    int current_number = 0, n, i = 0;
    inp >> n;
    int *arr = (int*)malloc(n*sizeof(int));
    while (inp >> current_number){
        arr[i] = current_number;
        i++;
    }
    inp.close();
    
    auto start = chrono::steady_clock::now();
    heapSort(arr, n);
    auto end = chrono::steady_clock::now();

    auto diff = end - start;

    ofstream out (string("output\\") + argv[2] + ".txt");

    out << chrono::duration <double, milli> (diff).count() << "\n";
    for(int i = 0; i < n; i++){
        out << arr[i] << " " ;
    }
    out.close();

    return 0;
}