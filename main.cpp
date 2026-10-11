#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

int main() {
    int n;
    cin >> n;
    
    vector<Point> points;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }
    
    // Sort points by x-coordinate
    sort(points.begin(), points.end());
    
    long long count = 0;
    
    // For each pair of points as potential bottom-left and top-right corners
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Check if points[i] can be bottom-left and points[j] can be top-right
            if (points[i].x < points[j].x && points[i].y < points[j].y) {
                // Check if the rectangle is empty (no other points inside or on boundary)
                bool empty = true;
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j) continue;
                    
                    // Check if point k is inside or on the boundary of the rectangle
                    if (points[k].x >= points[i].x && points[k].x <= points[j].x && 
                        points[k].y >= points[i].y && points[k].y <= points[j].y) {
                        empty = false;
                        break;
                    }
                }
                
                if (empty) {
                    count++;
                }
            }
        }
    }
    
    cout << count << endl;
    
    return 0;
}