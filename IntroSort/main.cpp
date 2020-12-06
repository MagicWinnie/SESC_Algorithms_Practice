#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;

void sink(int *arr, int ind, int s, int e)
{
    int big, l, r, len = e-s;
    l = 2*ind + 1;
    r = l + 1;

    if (l < len && arr[s + l] > arr[s + ind])
        big = l;
    else
        big = ind;
    if (r < len && arr[s + r] > arr[s + big])
        big = r;
    if (big != ind)
    {
        swap(arr[s + big], arr[s + ind]);
        sink(arr, big, s, e);
    }
}

void build_heap(int *arr, int s, int e)
{
    int len = e - s;
    int ind = (len - 2)/2;
    
    while (ind >= 0)
    {
        sink(arr, ind, s, e);
        ind--;
    }
}

void heapSort(int *arr, int s, int e, int n)
{
    build_heap(arr, s, e);

    int end = n - 1;

    while (end >= 0)
    {
        swap(arr[0], arr[end]);
        sink(arr, 0, s, end);
        end--;
    }
}

void insertionSort(int *arr, int s, int f)  
{  
    int i, key, j;  
    for (i = s + 1; i <= f; i++)
    {  
        key = arr[i];
        j = i;
  
        while (j > s && arr[j - 1] > key) 
        {
            arr[j] = arr[j - 1];
            j--;
        }  
        arr[j] = key;
    }  
}  

int partition(int *arr, int s, int f)
{
    int pivotIndex = rand() % (f - s + 1) + s;
    swap(arr[pivotIndex], arr[f]);
    int pivot = arr[f];
    int pIndex = s;
    for (int i = s; i < f; i++)
    {
        if (arr[i] <= pivot)
        {
            swap(arr[i], arr[pIndex]);
            pIndex++;
        }
    }
    swap(arr[pIndex], arr[f]);
    return pIndex;
}

void introSort(int *arr, int s, int e, int maxdepth, int n)
{
    if (n <= 1) return;
    else if (n < 16) insertionSort(arr, s, e);
    else if (maxdepth == 0) heapSort(arr, s, e, n);
    else 
    {
        int p = partition(arr, s, e);
        introSort(arr, s, p + 1, maxdepth - 1, n);
        introSort(arr, p + 1, e, maxdepth - 1, n);
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
    introSort(arr, 0, n, log(n)*2, n);
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
