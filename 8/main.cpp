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
#include <vector>

using namespace std;

struct edge
{
    int first, second, weight;
};

bool check_if_connected(vector<vector<pair<int, int>>> arr, int n)
{
    queue<int> q;
    q.push(0);

    vector<bool> visited(n);
    vector<int> d(n), p(n);

    visited[0] = true;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (size_t i = 0; i < arr[v].size(); ++i)
        {
            int to = arr[v][i].first;
            if (!visited[to])
            {
                visited[to] = true;
                q.push(to);
                d[to] = d[v] + 1;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
            return false;
    }
    return true;
}

int get_pred(int vertex, vector<int> pred)
{
    while (pred[vertex] != vertex)
        vertex = pred[vertex];
    return vertex;
}

int kruskal(vector<vector<pair<int, int>>> arr)
{
    vector<edge> edges; //, minimum_spanning_tree;
    vector<int> pred(arr.size());

    for (int i = 0; i < arr.size(); i++)
    {
        for (auto &e : arr[i])
            edges.push_back({i, e.first, e.second});
        pred[i] = i;
    }
    sort(edges.begin(), edges.end(), [](edge left, edge right) { return left.weight > right.weight; });

    int sum = 0;
    while (!edges.empty())
    {

        edge shortest = edges.back();
        edges.pop_back();

        int f_head, s_head;
        f_head = get_pred(shortest.first, pred);
        s_head = get_pred(shortest.second, pred);

        if (f_head != s_head)
        {
            sum += shortest.weight;
            //minimum_spanning_tree.push_back(shortest);
            if (f_head < s_head)
                pred[s_head] = f_head;
            else
                pred[f_head] = s_head;
        }
    }

    return sum;
    //return minimum_spanning_tree;
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

    vector<vector<int>> orig;
    vector<vector<pair<int, int>>> arr(n);

    orig.push_back({n, m, t});

    for (int l = 0; l < m; l++)
    {
        int i, j, k;
        inp >> i >> j;
        if (i == j)
            continue;
        i--;
        j--;
        if (t == 2 || t == 4)
        {
            inp >> k;
            orig.push_back({i + 1, j + 1, k});
        }
        else
        {
            orig.push_back({i + 1, j + 1});
        }
        if (t == 1)
        {
            arr[i].push_back(make_pair(j, 1));
        }
        else if (t == 2)
        {
            arr[i].push_back(make_pair(j, k));
        }
        else if (t == 3)
        {
            arr[i].push_back(make_pair(j, 1));
            arr[j].push_back(make_pair(i, 1));
        }
        else if (t == 4)
        {
            arr[i].push_back(make_pair(j, k));
            arr[j].push_back(make_pair(i, k));
        }
    }
    inp.close();

    if (!check_if_connected(arr, n))
    {
        ofstream out(output_filename, std::ios::out | std::ios::trunc);
        out << -1 << endl;

        for (int i = 0; i < orig.size(); i++)
        {
            for (int j = 0; j < orig[i].size(); j++)
                out << orig[i][j] << " ";
            out << endl;
        }
        out.close();

        return -1;
    }

    int num = kruskal(arr);

    ofstream out(output_filename, std::ios::out | std::ios::trunc);

    out << num << endl;
    for (int i = 0; i < orig.size(); i++)
    {
        for (int j = 0; j < orig[i].size(); j++)
            out << orig[i][j] << " ";
        out << endl;
    }
    out.close();
}
