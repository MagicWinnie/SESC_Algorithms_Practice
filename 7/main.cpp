#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
#include <queue>
#include <cmath>

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

    int path = BFS(arr, s, f, n);
    ofstream out(output_filename, std::ios::out | std::ios::trunc);
    cout << "[DEBUG] Error: " << strerror(errno) << endl;
    cout << "[DEBUG] File path: " << argv[2] << endl;

    out << path << endl;

    out.close();
}
