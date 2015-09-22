#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <iomanip>

using Point = std::pair<double, double>;

std::ostream& operator<<(std::ostream& ostr, Point p)
{
    ostr << "(" << p.first << ", " << p.second << ")";
    return ostr;
}

// Returns the (square of) distance between two points
double distance(const Point& p1, const Point& p2)
{
    double dx = p1.first - p2.first;
    double dy = p1.second - p2.second;
    return dx * dx + dy * dy;
}

int main(int argc, char* argv[])
{    
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " FILENAME\n";
        return 0; 
    }
    
    std::ifstream       infile(argv[1]);
    std::string         line;
    std::vector<Point>  points;
    
    // Read data to a vector of points
    if (infile.good()) {
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            double a, b;
            char c_;
            if (iss >> c_ >> a >> c_ >> b >> c_) {
                points.push_back(std::make_pair(a, b));
            }
        }
    }
    
    Point closest_point1    = points[0];
    Point closest_point2    = points[1];
    double closest_distance = distance(closest_point1, closest_point2);

    // Find the points with the closest distance
    for (auto p: points) {
        for (auto q: points) {
            if (p != q && distance(p, q) < closest_distance) {
                closest_distance = distance(p, q);
                closest_point1 = p;
                closest_point2 = q;
            }
        }
    }
    
    std::cout << std::setprecision(16) << "Closest points: \n" 
    << closest_point1 << "\n" << closest_point2 << std::endl;
}
