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
    
    // For each point as the left boundary
    for (int i = 0; i < n; i++) {
        // Set to maintain y-coordinates of points seen so far
        set<int> y_coords;
        y_coords.insert(points[i].y);
        
        // Sweep through points to the right (higher x-coordinate)
        for (int j = i + 1; j < n; j++) {
            // Check if points[i] can be bottom-left and points[j] can be top-right
            if (points[i].y < points[j].y) {
                // Find the smallest y-coordinate greater than points[i].y
                auto it = y_coords.upper_bound(points[i].y);
                // If there is no such point or the smallest one is >= points[j].y,
                // then there are no points in the y-interval (points[i].y, points[j].y)
                if (it == y_coords.end() || *it >= points[j].y) {
                    count++;
                }
            }
            // Check if points[j] can be bottom-left and points[i] can be top-right
            else if (points[j].y < points[i].y) {
                // Find the largest y-coordinate smaller than points[i].y
                auto it = y_coords.lower_bound(points[i].y);
                if (it != y_coords.begin()) {
                    --it;
                    // If the largest one is <= points[j].y,
                    // then there are no points in the y-interval (points[j].y, points[i].y)
                    if (*it <= points[j].y) {
                        count++;
                    }
                } else {
                    // No points smaller than points[i].y
                    count++;
                }
            }
            
            // Add current point's y-coordinate to the set
            y_coords.insert(points[j].y);
        }
    }
    
    cout << count << endl;
    
    return 0;
}