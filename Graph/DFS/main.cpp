#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <queue>
#include <cmath>
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

void DFS(vector<vector<int>> arr, int s, vector<int> visited, vector<int> path)
{
    visited[s] = 1;
    path.push_back(s);
    for (int r = 0; r <= arr.size(); r++)
        if (!visited[r])
            DFS(arr, r, visited, path);
}

int main(int argc, char **argv)
{
    if (argc < 3)
        return -1;

    ifstream inp(argv[1]);

    int n, s;

    inp >> n;
    inp >> s;

    vector<vector<int>> arr(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inp >> arr[i][j];
    inp.close();
    vector<int> visited(n);
    fill(visited.begin(), visited.end(), 0);
    vector<int> path;

    for (int i = 0; i < n; i++)
        if (visited[i] == 0)
            DFS(arr, s, visited, path);

    ofstream out(string("output\\") + argv[2] + ".txt");

    out << path.size() << endl;

    for (int i = 0; i < path.size(); i--)
        out << path[i] << " ";

    out.close();

    return 0;
}
