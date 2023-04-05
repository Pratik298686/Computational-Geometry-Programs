#include <iostream>
using namespace std;
#define Point pair<double, double>

class Line
{
public:
    Point lineLineIntersection(Point A, Point B, Point C, Point D);
    void displayPoint(Point P);
};

void Line::displayPoint(Point P)
{
    cout << "(" << P.first << ", " << P.second
        << ")" << endl;
}

Point Line::lineLineIntersection(Point A, Point B, Point C, Point D)
{
    // Line AB represented as a1x + b1y = c1
    double a1 = B.second - A.second;
    double b1 = A.first - B.first;
    double c1 = a1 * (A.first) + b1 * (A.second);

    // Line CD represented as a2x + b2y = c2
    double a2 = D.second - C.second;
    double b2 = C.first - D.first;
    double c2 = a2 * (C.first) + b2 * (C.second);

    double determinant = a1 * b2 - a2 * b1;

    if (determinant == 0)
    {
        // The lines are parallel. 
        return make_pair(FLT_MAX, FLT_MAX);
    }
    else
    {
        double x = (b2 * c1 - b1 * c2) / determinant;
        double y = (a1 * c2 - a2 * c1) / determinant;
        return make_pair(x, y);
    }
}
int main()
{

    Line l1;
    Point A = make_pair(1, 1);
    Point B = make_pair(4, 4);
    Point C = make_pair(1, 8);
    Point D = make_pair(2, 4);

    Point intersection = l1.lineLineIntersection(A, B, C, D);

    if (intersection.first == FLT_MAX &&
        intersection.second == FLT_MAX)
    {
        cout << "The given lines AB and CD are parallel.\n";
    }

    else
    {
        cout << "The intersection of the given lines AB "
            "and CD is: ";
        l1.displayPoint(intersection);
    }
    return 0;
}