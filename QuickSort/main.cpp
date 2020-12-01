#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;

void swap_m(int *r, int *s)
{
    int temp = *r;
    *r = *s;
    *s = temp;
} 

int part(vector <int> &arr, int l, int h)
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

void quickSort(vector <int> &arr, int l, int h)
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
    vector<int> vec;

    int current_number = 0;
    while (inp >> current_number){
        vec.push_back(current_number);
    }
    inp.close();

    auto start = chrono::steady_clock::now();
    quickSort(vec, 0, vec.size() - 1);
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