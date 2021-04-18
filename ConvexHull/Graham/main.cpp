#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Point
{
    double x;
    double y;

    bool operator<(const Point &p) const
    {
        if (x < p.x)
            return true;
        else if (x == p.x)
            return (y > p.y) ? true : false;
        else
            return false;
    }

    bool operator==(const Point &p) const
    {
        return (p.x == x) && (p.y == y) ? true : false;
    }
} point;

ostream &operator<<(ostream &stream, const point &p)
{
    stream << p.x << " " << p.y;
    return stream;
}

point vect(const point &p, const point &q)
{
    Point res = {q.x - p.x, q.y - p.y};
    return res;
}

double cosine(const point &p, const point &q)
{
    int dot_prod = p.x * q.x + p.y * q.y;
    double norm_2_p = sqrt(pow(p.x, 2) + pow(p.y, 2));
    double norm_2_q = sqrt(pow(q.x, 2) + pow(q.y, 2));
    return dot_prod / (norm_2_p * norm_2_q);
}

void convex_hull(vector<point> in_points, vector<point> &out_points, double err = 10e-9)
{
    if (in_points.size() <= 2)
        return;

    point f_point = in_points.front();
    for (point p : in_points)
    {
        if (p < f_point)
            f_point = p;
    }
    out_points.push_back(f_point);

    point ref_p = {f_point.x, f_point.y + 1};
    point ref_q = f_point;
    point next_point = ref_p;

    while (true)
    {
        point next_point = ref_p;

        for (point p : in_points)
        {
            if (p == ref_q)
                continue;

            double cos_ang_1 = cosine(vect(ref_p, ref_q), vect(ref_q, p));
            double cos_ang_2 = cosine(vect(ref_p, ref_q), vect(ref_q, next_point));

            if (abs(cos_ang_1 - cos_ang_2) < err)
                next_point = (p < next_point) ? p : next_point;
            else if (cos_ang_1 > cos_ang_2)
                next_point = p;
        }

        out_points.push_back(next_point);
        ref_p = ref_q;
        ref_q = next_point;

        if (next_point == f_point)
            break;
    }
}

int main(int argc, char **argv)
{
    if (argc < 3)
        return -1;

    ifstream inp(argv[1]);

    int n;

    inp >> n;

    vector<point> arr;
    for (int i = 0; i < n; i++)
    {
        point temp;
        inp >> temp.x;
        inp >> temp.y;
        arr.push_back(temp);
    }

    inp.close();

    vector<point> ch;

    convex_hull(arr, ch);

    ofstream out(string("output\\") + argv[2] + ".txt");
    out << ch.size() << endl;
    for (int i = 0; i < ch.size(); i++)
        out << ch[i] << endl;
    out.close();
}