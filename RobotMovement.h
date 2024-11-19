#ifndef ROBOTMOVEMENT_H
#define ROBOTMOVEMENT_H
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include <memory>
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

class Action{
public:
    virtual void execute(Point& currPos, std::vector<bool>& grid, int dim, const Point& targetPos) = 0;
};

class MoveToAction : public Action{
public:
    void execute(Point& currPos, std::vector<bool>& grid, int dim, const Point& targetPos) override;
};

class LineToAction : public Action{
public:
    void execute(Point& currPos, std::vector<bool>& grid, int dim, const Point& targetPos) override;
private:
    int squareDistanceOf2Point(const Point& p1, const Point& p2);
    std::vector<Point> findneighborPoints(const Point& p, int dim);
    bool checkPointValid(const Point& p, int dim);
};

class CircleToAction : public Action{
public:
    void execute(Point& currPos, std::vector<bool>& grid, int dim, const Point& targetPos) override;
private:
    void setPixel(int x, int y, int dim, std::vector<bool>& grid);
};

static std::unique_ptr<Action> createAction(const std::string& action){
    if(action == "MOVE_TO") return std::make_unique<MoveToAction>();
    else if(action == "LINE_TO") return std::make_unique<LineToAction>();
    else if(action == "CIRCLE_TO") return std::make_unique<CircleToAction>();
    else return nullptr;
}

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
    void doAction(const std::string& action, const Point& p);
    void displayDataConsole();
    void displayDataBitmap();
private:
    void saveBitmap(const std::vector<RGB>& bitmap, const std::string& filename);
private:
    std::vector<bool> robotMap_;
    int dimension_;
    Point robotPos_;
    std::map<std::string, std::unique_ptr<Action>> actions_;
};

#endif // ROBOTMOVEMENT_H
