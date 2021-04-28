// Kruskal's algorithm
// input:
// list of edges
// output:
// sum of weights of a minimum spanning forest
// Written by Dmitriy Okoneshnikov, 2021
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;



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
    cout << "[DEBUG] Error: " << strerror(errno) << endl;
    cout << "[DEBUG] File path: " << argv[2] << endl;

    out << num << endl;
    out.close();
}
