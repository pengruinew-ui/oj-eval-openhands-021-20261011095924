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

// Fenwick Tree (Binary Indexed Tree) for counting
class FenwickTree {
private:
    vector<int> tree;
    int n;

public:
    FenwickTree(int size) {
        n = size;
        tree.assign(n + 1, 0);
    }
    
    void update(int idx, int delta) {
        while (idx <= n) {
            tree[idx] += delta;
            idx += idx & (-idx);
        }
    }
    
    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & (-idx);
        }
        return sum;
    }
    
    int rangeQuery(int left, int right) {
        return query(right) - query(left - 1);
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
    
    // Coordinate compression for y-coordinates
    vector<int> y_coords;
    for (const auto& p : points) {
        y_coords.push_back(p.y);
    }
    sort(y_coords.begin(), y_coords.end());
    y_coords.erase(unique(y_coords.begin(), y_coords.end()), y_coords.end());
    
    // Map y-coordinate to compressed index
    auto get_y_index = [&](int y) -> int {
        return lower_bound(y_coords.begin(), y_coords.end(), y) - y_coords.begin() + 1;
    };
    
    long long count = 0;
    
    // For each point as the left boundary
    for (int i = 0; i < n; i++) {
        // Create a Fenwick tree for the current sweep
        FenwickTree fenw(y_coords.size());
        
        // Mark the current point's y-coordinate
        int y1_idx = get_y_index(points[i].y);
        fenw.update(y1_idx, 1);
        
        // Sweep through points to the right
        for (int j = i + 1; j < n; j++) {
            int y2_idx = get_y_index(points[j].y);
            
            // Check if points[i] can be bottom-left and points[j] can be top-right
            if (points[i].y < points[j].y) {
                // Check if there are no points between them in y-range
                if (fenw.rangeQuery(y1_idx + 1, y2_idx - 1) == 0) {
                    count++;
                }
            } 
            // Check if points[j] can be bottom-left and points[i] can be top-right
            else if (points[j].y < points[i].y) {
                // Check if there are no points between them in y-range
                if (fenw.rangeQuery(y2_idx + 1, y1_idx - 1) == 0) {
                    count++;
                }
            }
            
            // Add current point to the Fenwick tree
            fenw.update(y2_idx, 1);
        }
    }
    
    cout << count << endl;
    
    return 0;
}