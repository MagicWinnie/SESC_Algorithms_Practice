#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <vector>
#include <limits>
#include <cstring>
#include <algorithm>

using namespace std;

typedef numeric_limits<double> dbl;

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

int getIndex(vector<Point> v, Point k)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (abs(v[i].x - k.x) < 10e-8 && abs(v[i].y - k.y) < 10e-8)
            return i;
    }
    return -1;
}

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
    return vect_prod(a, b) > 0 || vect_prod(a, b) == 0 && (a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y);
}

vector<Point> convex_hull(vector<Point> points)
{
    Point p0 = points[0];
    for (Point p : points)
        if (p.x < p0.x || (p.x == p0.x && p.y < p0.y))
            p0 = p;

    // сдвинуть в начало координат
    for (Point &p : points)
    {
        p.x -= p0.x;
        p.y -= p0.y;
    }
    // отсортировать по углу
    sort(points.begin(), points.end(), &sort_func);

    vector<Point> hull;
    for (Point p : points)
    {
        // убираем последнюю точку минимальной выпуклой оболочки пока она выпуклая
        while (hull.size() >= 2 && (vect_prod((p - hull.back()), (hull[hull.size() - 2] - hull.back())) <= 0))
            hull.pop_back();
        hull.push_back(p);
    }
    // сдвигаем обратно точки
    for (Point &p : hull)
    {
        p.x += p0.x;
        p.y += p0.y;
    }
    return hull;
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

    auto start = chrono::steady_clock::now();
    vector<Point> ch = convex_hull(arr);
    auto end = chrono::steady_clock::now();
    auto diff = end - start;

    ofstream out(output_filename, std::ios::out | std::ios::trunc);
    out.precision(dbl::max_digits10);
    out << chrono::duration<double, nano>(diff).count() << endl;
    cout << "[DEBUG] Error: " << strerror(errno) << endl;
    cout << "[DEBUG] File path: " << argv[2] << endl;

    out << ch.size() << endl;
    for (int i = 0; i < ch.size(); i++)
        out << getIndex(arr, ch[i]) + 1 << endl;
    out.close();
}