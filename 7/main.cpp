// Kosaraju's algorithm
// input:
// list of edges
// output:
// number of strongly connected components
// Written by Dmitriy Okoneshnikov, 2021
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <queue>
#include <cmath>
#include <vector>

using namespace std;

void DFS_1(vector<vector<int>> arr, int s, vector<bool> &visited, vector<int> &order)
{
    visited[s] = true;
    for (int r = 0; r < arr.size(); r++)
    {
        if (arr[s][r] != INT_MAX && !visited[r])
        {
            DFS_1(arr, r, visited, order);
        }
    }
    order.push_back(s);
}

void DFS_2(vector<vector<int>> arr, int s, vector<bool> &visited, vector<int> &components)
{
    visited[s] = true;
    components.push_back(s);

    for (int r = 0; r < arr.size(); r++)
    {
        if (arr[s][r] != INT_MAX && !visited[r])
        {
            DFS_2(arr, r, visited, components);
        }
    }
}

int kosaraju(vector<vector<int>> arr, vector<vector<int>> arr_inv, vector<int> &components)
{
    int n = arr.size();
    vector<int> order;
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            DFS_1(arr, i, visited, order);
        }
    }

    visited.assign(n, false);

    int component = 0;
    for (int i = 0; i < n; i++)
    {
        int v = order[n - i - 1];
        if (!visited[v])
        {
            component++;
            DFS_2(arr_inv, v, visited, components);
        }
    }

    return component;
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

    int n, m, t;

    inp >> n >> m >> t;

    vector<vector<int>> arr(n, vector<int>(n));
    vector<vector<int>> arr_inv(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i][j] = INT_MAX;
            arr_inv[i][j] = INT_MAX;
        }
    }
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
            arr_inv[j][i] = 1;
        }
        else if (t == 2)
        {
            arr[i][j] = k;
            arr_inv[j][i] = k;
        }
        else if (t == 3)
        {
            arr[i][j] = 1;
            arr[j][i] = 1;
            arr_inv[j][i] = 1;
            arr_inv[i][j] = 1;
        }
        else if (t == 4)
        {
            arr[i][j] = k;
            arr[j][i] = k;
            arr_inv[j][i] = k;
            arr_inv[i][j] = k;
        }
    }
    inp.close();

    vector<int> components;
    int num = kosaraju(arr, arr_inv, components);

    // for (int i = 0; i < n; i++ )
    //     cout << components[i] << " ";
    // cout << endl;

    ofstream out(output_filename, std::ios::out | std::ios::trunc);
    out << num << endl;
    out.close();
}
