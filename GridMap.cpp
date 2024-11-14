#include "GridMap.h"
#include <math.h>
GridMap::GridMap(int dimension)
    : dimension_(dimension), isGridMapCreatedSuccess_(false)
{
    // asume that dimention should be greater than 0 and less than 200
    if(dimension_ <= 0 || dimension_ > 200) return;
    gridMap_ = std::vector<bool>(dimension_*dimension_, false);
    isGridMapCreatedSuccess_ = true;
}

void GridMap::createMap(int dimension)
{
    if(dimension_ <= 0 || dimension_ > 200) {
        isGridMapCreatedSuccess_ = false;
        return;
    }
    gridMap_ = std::vector<bool>(dimension_*dimension_, false);
    isGridMapCreatedSuccess_ = true;
}

void GridMap::moveToPoint(Point p)
{
    std::cout<<"GridMap::moveToPoint"<<std::endl;
    if(!checkPointValid(p) || !isGridMapCreatedSuccess_) return;
    // move to p
    robotPos_ = p;
    gridMap_[p.y * dimension_ + p.x] = true; // mark this point as visited
}

void GridMap::lineToPoint(Point p)
{
    std::cout<<"GridMap::lineToPoint"<<std::endl;
    if(!checkPointValid(p) || !isGridMapCreatedSuccess_) return;
    // using A* algorithm to find path from robotPos to point P

    // choose the next point to step in is the point that
    // distance euclid from it to target is smallest
    while (robotPos_ != p) {
        auto neighborPoint = findneighborPoints(robotPos_);
        if(neighborPoint.size() == 0){
            std::cout<<"neighborPoint empty"<<std::endl;
            return;
        }
        Point choosedPoint = neighborPoint[0];
        for(int i = 1; i < neighborPoint.size(); i++){
            if(squareDistanceOf2Point(choosedPoint, p) > squareDistanceOf2Point(neighborPoint[i], p)){
                choosedPoint = neighborPoint[i];
            }
        }
        robotPos_ = choosedPoint;
        gridMap_[robotPos_.y * dimension_ + robotPos_.x] = true;
    }
}

void GridMap::circleToPoint(Point p)
{
    std::cout<<"GridMap::circleToPoint"<<std::endl;
    if(!checkPointValid(p) || !isGridMapCreatedSuccess_) return;
    int radius = std::sqrt(((p.x-robotPos_.x)*(p.x - robotPos_.x) + (p.y-robotPos_.y)*(p.y - robotPos_.y)));
    std::cout<<"radius: "<<radius<<std::endl;
    int x = radius, y = 0;
    int decisionOver2 = 1 - x;
    while (x >= y) {
        // Plot the circle points in each octant
        setPixel(robotPos_.x + x, robotPos_.y + y);
        setPixel(robotPos_.x + y, robotPos_.y + x);
        setPixel(robotPos_.x - y, robotPos_.y + x);
        setPixel(robotPos_.x - x, robotPos_.y + y);
        setPixel(robotPos_.x - x, robotPos_.y - y);
        setPixel(robotPos_.x - y, robotPos_.y - x);
        setPixel(robotPos_.x + y, robotPos_.y - x);
        setPixel(robotPos_.x + x, robotPos_.y - y);
        y++;

        if (decisionOver2 <= 0) {
            decisionOver2 += 2 * y + 1;
        } else {
            x--;
            decisionOver2 += 2 * (y - x) + 1;
        }
    }
}

void GridMap::printGridMapToBitmap()
{

}

std::vector<bool> &GridMap::gridMap()
{
    return gridMap_;
}

int GridMap::dimension() const
{
    return dimension_;
}

bool GridMap::isGridMapCreatedSuccess() const
{
    return isGridMapCreatedSuccess_;
}

bool GridMap::checkPointValid(Point p)
{
    bool res{false};
    if(p.x < 0 || p.x >= dimension_ || p.y < 0 || p.y >= dimension_) res = false;
    else res = true;
    if(res) std::cout<<"("<<p.x<<", "<<p.y<<") is valid "<<std::endl;
    else std::cout<<"("<<p.x<<", "<<p.y<<") is not valid "<<std::endl;
    return res;
}

int GridMap::squareDistanceOf2Point(Point p1, Point p2)
{
    return (p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y);
}

std::vector<Point> GridMap::findneighborPoints(Point p)
{
    std::vector<Point> res;
    if(checkPointValid(Point(p.x-1, p.y-1))) res.push_back(Point(p.x-1, p.y-1));
    if(checkPointValid(Point(p.x, p.y-1))) res.push_back(Point(p.x, p.y-1));
    if(checkPointValid(Point(p.x+1, p.y-1))) res.push_back(Point(p.x+1, p.y-1));
    if(checkPointValid(Point(p.x-1, p.y))) res.push_back(Point(p.x-1, p.y));
    if(checkPointValid(Point(p.x+1, p.y))) res.push_back(Point(p.x+1, p.y));
    if(checkPointValid(Point(p.x-1, p.y+1))) res.push_back(Point(p.x-1, p.y+1));
    if(checkPointValid(Point(p.x, p.y+1))) res.push_back(Point(p.x, p.y+1));
    if(checkPointValid(Point(p.x+1, p.y+1))) res.push_back(Point(p.x+1, p.y+1));
    return res;
}

void GridMap::setPixel(int x, int y)
{
    if (x >= 0 && x < dimension_ && y >= 0 && y < dimension_) {
        gridMap_[y * dimension_ + x] = true;
    }
}
