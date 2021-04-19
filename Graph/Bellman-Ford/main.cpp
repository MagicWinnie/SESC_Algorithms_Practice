#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <queue>
#include <cstring>
#include <cmath>
#include <vector>
const int INF = 100000;

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

int BellmanFord(vector<vector<int>> arr, int n, int start, int finish, vector<int> &path)
{
    vector<int> dist(n, INF);

    dist[start] = 0;

    vector<int> pred(n, -1);
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (arr[i][j] != INF)
                {
                    if (dist[j] > (dist[i] + arr[i][j]))
                    {
                        dist[j] = dist[i] + arr[i][j];
                        pred[j] = i;
                    }
                }
            }
        }
    }
    if (dist[finish] != INF)
    {
        for (int curr = finish; curr != -1; curr = pred[curr])
            path.push_back(curr);

        reverse(path.begin(), path.end());
    }
    return dist[finish];
}

int main(int argc, char **argv)
{
    if (argc < 3)
        return -1;

    ifstream inp(argv[1]);

    int n, s, f;

    inp >> n;
    inp >> s;
    inp >> f;

    vector<vector<int>> arr(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inp >> arr[i][j];
    inp.close();

    vector<int> path;
    int cost = BellmanFord(arr, n, s, f, path);

    ofstream out(argv[2], std::ios::out | std::ios::trunc);
    cerr << "[DEBUG] Error: " << strerror(errno) << endl;
    cout << "[DEBUG] File path: " << argv[2] << endl;
    
    out << cost << endl;
    out << path.size() << endl;
    for (int i = 0; i < path.size(); i++)
        out << path[i] << " ";
    out.close();

    return 0;
}
