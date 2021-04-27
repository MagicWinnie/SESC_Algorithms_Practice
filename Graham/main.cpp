#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <limits>
#include <cstring>
#include <algorithm>

using namespace std;

typedef numeric_limits< double > dbl;

struct Point
{
    double x;
    double y;

    Point(double x = 0.0, double y = 0.0)
        : x(x), y(y)
    {
    }

    Point operator-(Point pnt) { return Point(x - pnt.x, y - pnt.y); }
};

ostream &operator<<(ostream &stream, const Point &p)
{
    stream << p.x << " " << p.y;
    return stream;
}

double vect_prod(Point A, Point B)
{
    return A.x * B.y - A.y * B.x;
}

bool sort_func(Point a, Point b)
{
    return vect_prod(a, b) > 0 || vect_prod(a, b) == 0 && (a.x*a.x + a.y*a.y < b.x*b.x + b.y*b.y);
}

vector<Point> convex_hull(vector<Point> points)
{
    Point p0 = points[0];
    for (Point p : points)
        if (p.x < p0.x || (p.x == p0.x && p.y < p0.y))
            p0 = p;

    // p0 : start of coordinates
    for (Point &p : points)
    {
        p.x -= p0.x; p.y -= p0.y;
    }
    // sort polar
    sort(points.begin(), points.end(), &sort_func);

    vector<Point> hull;
    for (Point p : points)
    {
        // remove the last point of the minimal convex hull while it forms a convexity
        while (hull.size() >= 2 && (vect_prod((p - hull.back()), (hull[hull.size() - 2] - hull.back())) <= 0))
            hull.pop_back();
        hull.push_back(p);
    }
    // get points back
    for (Point &p : hull)
    {
        p.x += p0.x; p.y += p0.y;
    }
    return hull;
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

    vector<Point> ch = convex_hull(arr);

    ofstream out(argv[2], std::ios::out | std::ios::trunc);
    out.precision(dbl::max_digits10);
    cout << "[DEBUG] Error: " << strerror(errno) << endl;
    cout << "[DEBUG] File path: " << argv[2] << endl;
    out << ch.size() << endl;
    for (int i = 0; i < ch.size(); i++)
        out << ch[i] << endl;
    out.close();
}