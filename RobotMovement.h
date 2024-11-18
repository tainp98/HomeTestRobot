#ifndef ROBOTMOVEMENT_H
#define ROBOTMOVEMENT_H
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
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

enum class CommandType: unsigned char{
    MOVE = 0,
    LINE,
    CIRCLE
};

class RobotMovement
{
private:
    struct RGB {
        unsigned char r, g, b;
    };
public:
    RobotMovement();
    RobotMovement(int dimension);
    void create(int dimension);
    void doAction(CommandType commandType, const Point& p);
    void displayDataConsole();
    void displayDataBitmap();
private:
    void moveToPoint(const Point& p);
    void lineToPoint(const Point& p);
    void circleToPoint(const Point& p);
    bool checkPointValid(Point p);
    int squareDistanceOf2Point(Point p1, Point p2);
    std::vector<Point> findneighborPoints(Point p);
    void setPixel(int x, int y);
    void saveBitmap(const std::vector<RGB>& bitmap, const std::string& filename);
private:
    std::vector<bool> robotMap_;
    int dimension_;
    Point robotPos_;
    bool isCreatedSuccess_;
};

#endif // ROBOTMOVEMENT_H
