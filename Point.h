#ifndef POINT_H
#define POINT_H

struct Point {
    int x, y;
    bool sosanhbang(Point a) {
        return x == a.x && y == a.y;
    }
};

#endif 
