#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

struct Point
{
    double x;
    double y;

    Point() : x(0.0), y(0.0){};
    Point(double x, double y) : x(x), y(y){};

    Point operator=(Point pnt) { (*this).x = pnt.x; (*this).y = pnt.y; return (*this); }

    Point operator+(Point pnt) { return Point((*this).x + pnt.x, (*this).y + pnt.y); }
    Point operator-(Point pnt) { return Point((*this).x - pnt.x, (*this).y - pnt.y); }
    Point operator*(Point pnt) { return Point((*this).x * pnt.x, (*this).y * pnt.y); }
    Point operator/(Point pnt) { return Point((*this).x / pnt.x, (*this).y / pnt.y); }
    
};

bool operator==(Point a, Point b) { return a.x==b.x && a.y==b.y; }
ostream &operator<<(ostream &stream, const Point &p)
{
    stream << p.x << " " << p.y;
    return stream;
}
ostream &operator<<(ostream &stream, vector<int> &p)
{
    for (int i = 0; i < p.size(); i++)
        stream << p[i] << " ";
    return stream;
}


float rotate(Point A, Point B, Point C)
{
    return (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x);
}

vector<int> convex_hull(vector<Point> in_points)
{
    int n = in_points.size();

    vector<int> P;
    for (int i = 0; i < n; i++)
        P.push_back(i);

    for (int i = 1; i < n; i++)
    {
        if (in_points[P[i]].x < in_points[P[i]].x)
            swap(P[i], P[0]);
    }

    for (int i = 2; i < n; i++)
    {
        int j = i;
        while (j > 1 && (rotate(in_points[P[0]], in_points[P[j - 1]], in_points[P[j]]) < 0))
        {
            swap(P[j], P[j - 1]);
            j--;
        }
    }
    vector<int> out{P[0], P[1]};
    for (int i = 2; i < n; i++)
    {
        while (rotate(in_points[out[out.size() - 2]], in_points[out[out.size() - 1]], in_points[P[i]]) < 0)
        {
            out.pop_back();
        }
        out.push_back(P[i]);
    }
    // cout << out << endl;
    return out;
}

int main(int argc, char **argv)
{
    if (argc < 3)
        return -1;

    ifstream inp(argv[1]);

    int n;

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

    vector<int> ch = convex_hull(arr);
    cout << ch << endl;

    ofstream out(argv[2], std::ios::out | std::ios::trunc);
    cerr << "[DEBUG] Error: " << strerror(errno) << endl;
    cout << "[DEBUG] File path: " << argv[2] << endl;
    out << ch.size() << endl;
    for (int i = 0; i < ch.size(); i++)
        out << ch[i] << endl;
    out.close();
}