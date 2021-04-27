#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

void printArr(vector<vector<int>> arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
}

void printArr(vector<int> arr, int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void DFS(vector<vector<int>> arr, int s, vector<bool> &visited, vector<int> &path)
{
    visited[s] = true;
    // cout << s << " " << visited[s] << endl;
    path.push_back(s);
    for (int r = 0; r < arr.size(); r++)
        if (arr[s][r] == 1 && !visited[r])
        {
            DFS(arr, r, visited, path);
        }
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
    inp >> n >> m >> t;

    vector<vector<int>> arr(n, vector<int>(n));
    for (int l = 0; l < m; l++)
    {
        int i, j, k;
        inp >> i >> j;
        if (t == 2 || t == 4)
        {
            inp >> k;
        }
        if (t == 1)
        {
            arr[i][j] = 1;
        } else if (t == 2)
        {
            arr[i][j] = k;
        } else if (t == 3)
        {
            arr[i][j] = 1;
            arr[j][i] = 1;
        } else if (t == 4)
        {
            arr[i][j] = k;
            arr[j][i] = k;
        }
    }
    inp.close();
    vector<bool> visited(n);
    fill(visited.begin(), visited.end(), false);
    vector<int> path;

    DFS(arr, s, visited, path);

    ofstream out(output_filename, std::ios::out | std::ios::trunc);
    cout << "[DEBUG] Error: " << strerror(errno) << endl;
    cout << "[DEBUG] File path: " << argv[2] << endl;

    out << visited[f] << endl;
    out.close();

    return 0;
}
