#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <cstring>
#include <iomanip>

using namespace std;

void sink(int *arr, int ind, int n)
{
    int big = ind;
    int l = 2 * ind + 1;
    int r = l + 1;

    if (l < n && arr[l] > arr[big])
        big = l;
    if (r < n && arr[r] > arr[big])
        big = r;
    if (big != ind)
    {
        swap(arr[ind], arr[big]);
        sink(arr, big, n);
    }
}

void build_heap(int *arr, int n)
{
    int ind = n / 2 - 1;
    
    while (ind >= 0)
    {
        sink(arr, ind, n);
        ind--;
    }
}

void heapSort(int *arr, int n)
{
    build_heap(arr, n);
    int i = n - 1;
    while (i >= 0)
    {
        swap(arr[0], arr[i]);
        sink(arr, 0, i);
        i--;
    }
}

void insertionSort(int *arr, int s, int f)  
{  
    int i, key, j;  
    for (i = s + 1; i < f; i++)
    {  
        key = arr[i];
        j = i - 1;
  
        while (j >= s && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            j--;
        }  
        arr[j + 1] = key;
    }  
    return;
}  

void introSort(int *arr, int n, int maxdepth)
{
    if(maxdepth > 0){
        heapSort(arr, n);
        return;
    }

    int ind = 0;
    int pivot = arr[n / 2];
    
    swap(arr[n / 2], arr[n-1]);

    for(int i = 0; i < n - 1; i++)
        if(arr[i] < pivot)
            swap(arr[i], arr[ind++]);
    
    swap(arr[n - 1], arr[ind]);
    
    if (0 < ind - 1 && ind > 16)
        introSort(arr, ind, maxdepth--);
    if (ind + 1 < n - 1 && n - ind - 1 > 16)
        introSort(arr + ind + 1, n - ind - 1, maxdepth--);
}

void introsort(int *arr, int n){
    introSort(arr, n, (int)floor(2*log(n)));
    insertionSort(arr, 0, n);
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
    introsort(arr, n);

    auto end = chrono::steady_clock::now();

    auto diff = end - start;
    ofstream out(argv[2], std::ios::out | std::ios::trunc);
    cerr << "[DEBUG] Error: " << strerror(errno) << endl;
    cout << "[DEBUG] File path: " << argv[2] << endl;

    out << chrono::duration <double, milli> (diff).count() << "\n";
    for(int i = 0; i < n; i++){
        out << arr[i] << " " ;
    }
    out.close();

    return 0;
}
