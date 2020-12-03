#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;

void sink(vector<int> &arr, int ind, int m)
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

void build_heap(vector<int> &arr)
{
    int ind = arr.size()/2 - 1;
    
    while (ind >= 0)
    {
        sink(arr, ind, arr.size());
        ind--;
    }
}

void heapSort(vector<int> &arr)
{
    build_heap(arr);

    int end = arr.size() - 1;

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
    vector<int> vec;

    int current_number = 0;
    while (inp >> current_number){
        vec.push_back(current_number);
    }
    inp.close();

    auto start = chrono::steady_clock::now();
    heapSort(vec);
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