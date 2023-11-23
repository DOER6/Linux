#include <iostream>
#include <cmath>

struct Point {
    double x, y;
};

bool onSegment(Point p, Point q, Point r) {
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
        return true;
    return false;
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    double o1 = (q1.y - p1.y) * (p2.x - p1.x) - (q1.x - p1.x) * (p2.y - p1.y);
    double o2 = (q1.y - p1.y) * (q2.x - p1.x) - (q1.x - p1.x) * (q2.y - p1.y);
    double o3 = (q2.y - p2.y) * (p1.x - p2.x) - (q2.x - p2.x) * (p1.y - p2.y);
    double o4 = (q2.y - p2.y) * (q1.x - p2.x) - (q2.x - p2.x) * (q1.y - p2.y);

    if (o1 * o2 < 0 && o3 * o4 < 0) {
        return true;
    }

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

int main(int argc, char* argv[]) {
    if (argc != 9) {
        std::cerr << "ERROR: Invalid number of arguments." << std::endl;
        return 1;
    }

    Point L1P1 = {std::stod(argv[1]), std::stod(argv[2])};
    Point L1P2 = {std::stod(argv[3]), std::stod(argv[4])};
    Point L2P1 = {std::stod(argv[5]), std::stod(argv[6])};
    Point L2P2 = {std::stod(argv[7]), std::stod(argv[8])};

    if (doIntersect(L1P1, L1P2, L2P1, L2P2)) {
        std::cout << "TRUE" << std::endl;
    } else {
        std::cout << "FALSE" << std::endl;
    }

    return 0;
}

