#ifndef GRIDMAP_H
#define GRIDMAP_H
#include <vector>
#include <iostream>

struct Point {
    int x{0};
    int y{0};
    Point(){}
    Point(int _x, int _y): x(_x), y(_y){}
    Point(const Point& p){
        this->x = p.x;
        this->y = p.y;
    }
    Point& operator = (const Point& p){
        this->x = p.x;
        this->y = p.y;
        return *this;
    }

    bool operator != (const Point& p){
        return (this->x != p.x || this->y != p.y);
    }
    bool operator == (const Point& p){
        return (this->x == p.x && this->y == p.y);
    }
};

class GridMap
{
public:
    GridMap(int dimension);
    void createMap(int dimension);
    void moveToPoint(Point p);
    void lineToPoint(Point p);
    void circleToPoint(Point p);
    void printGridMapToBitmap();
    std::vector<bool>& gridMap();
    int dimension() const;
    bool isGridMapCreatedSuccess() const;
private:
    bool checkPointValid(Point p);
    int squareDistanceOf2Point(Point p1, Point p2);
    std::vector<Point> findneighborPoints(Point p);
    void setPixel(int x, int y);
private:
    std::vector<bool> gridMap_;
    int dimension_;
    Point robotPos_;
    bool isGridMapCreatedSuccess_;
};

#endif // GRIDMAP_H
