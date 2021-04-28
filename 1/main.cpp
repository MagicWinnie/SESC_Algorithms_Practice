// Breath-First Search
// input:
// list of edges
// output:
// length of the shortest path 
// Written by Dmitriy Okoneshnikov, 2020
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int BFS(vector<vector<int>> arr, int s, int f, int n)
{
    queue<int> q;
    vector<int> dst(n);
    vector<int> pr(n);
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

    vector<int> path;
    if (arr[f][f])
    {
        for (int i = f; i != -1; i = pr[i])
            path.push_back(i);
    }
    // return path;
    return (dst[f] == INT_MAX) ? -1 : dst[f];
}

int main(int argc, char **argv)
{
    string input_filename = "input.txt";
    string output_filename = "output.txt";
    if (argc == 2)
    {
        input_filename = argv[1];
    }
    else if (argc >= 3)
    {
        input_filename = argv[1];
        output_filename = argv[2];
    }

    ifstream inp(input_filename);

    int n, m, t, s, f;

    inp >> s >> f;
    s--;
    f--;
    inp >> n >> m >> t;
    vector<vector<int>> arr(n, vector<int>(n));

    for (int l = 0; l < m; l++)
    {
        int i, j, k;
        inp >> i >> j;
        i--;
        j--;
        if (t == 2 || t == 4)
        {
            inp >> k;
        }
        if (t == 1)
        {
            arr[i][j] = 1;
        }
        else if (t == 2)
        {
            arr[i][j] = k;
        }
        else if (t == 3)
        {
            arr[i][j] = 1;
            arr[j][i] = 1;
        }
        else if (t == 4)
        {
            arr[i][j] = k;
            arr[j][i] = k;
        }
    }
    inp.close();

    int path = BFS(arr, s, f, n);
    ofstream out(output_filename, std::ios::out | std::ios::trunc);

    out << path << endl;

    out.close();
}
