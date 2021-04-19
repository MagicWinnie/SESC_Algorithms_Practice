#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>

using namespace std;

void printArr(int **arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << arr[i][j] << " "; 
        cout << endl;
    }
}

void printArr(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int* BFS(int **arr, int s, int f, int n, int *path_size)
{
    queue<int> q;
    int *dst = (int*)malloc(n*sizeof(int));
    int *pr = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
    {
        dst[i] = INT_MAX;
        pr[i] = -1;
    }
    q.push(s);
    arr[s][s] = 1;
    dst[s] = 0;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int i = 0; i < n; i++)
        {
            if (arr[v][i] != 0 && (!arr[i][i]))
            {
                arr[i][i] = 1;
                q.push(i);
                dst[i] = dst[v] + 1;
                pr[i] = v;
            }
        }
    }

    int *path = (int*)malloc(sizeof(int));
    int j = 0;
    if (arr[f][f])
    {
        for (int i = f; i != -1; i = pr[i])
        {
            path[j] = i;
            j++;
            path = (int*)realloc(path, (j+1)*sizeof(int));
        }
    }
    *path_size = j;
    return path;
}

int main(int argc, char **argv)
{
    if (argc < 3) return -1;

    ifstream inp(argv[1]);
    
    int n, s, f;
    
    inp >> n;
    inp >> s;
    inp >> f;

    int **arr = (int**)malloc(n*sizeof(int*));
    for(int i = 0; i < n; i++) arr[i] = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inp >> arr[i][j];
        }
    }
    inp.close();
    
    int path_size;
    int *path = BFS(arr, s, f, n, &path_size);

    ofstream out(argv[2], std::ios::out | std::ios::trunc);
    cerr << "[DEBUG] Error: " << strerror(errno) << endl;
    cout << "[DEBUG] File path: " << argv[2] << endl;

    out << path_size << endl;
    
    for(int i = path_size - 1; i >= 0; i--){
        out << path[i] << " ";
    }
    
    out.close();

    return 0;
}
