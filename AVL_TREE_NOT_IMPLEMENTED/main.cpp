// AVL-tree
// input:
// list of points
// output:
// sorted tree
// Written by Dmitriy Okoneshnikov, 2021
#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

class AVL_TREE
{
    public:
    int key, height;
    AVL_TREE *right;
    AVL_TREE *left;
    AVL_TREE() 
    {
        AVL_TREE *root = NULL;
        
    }  
    ~AVL_TREE()
    {

    }
    int height()
    {
        if (N == NULL)
    }
};

typedef numeric_limits<double> dbl;

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

    int n, temp;



    while (inp >> temp)
    {

    }

    inp >> n;

    vector<Point> arr;
    for (int i = 0; i < n; i++)
    {
        Point temp;
        inp >> temp.x;
        inp >> temp.y;
        arr.push_back(temp);
    }

    inp.close();

    auto start = chrono::steady_clock::now();
    // vector<Point> ch = convex_hull(arr);
    auto end = chrono::steady_clock::now();
    auto diff = end - start;

    ofstream out(output_filename, std::ios::out | std::ios::trunc);
    out.precision(dbl::max_digits10);
    out << chrono::duration<double, nano>(diff).count() << endl;

    // out << ch.size() << endl;
    // for (int i = 0; i < ch.size(); i++)
    //     out << getIndex(arr, ch[i]) + 1 << " ";
    out.close();
}