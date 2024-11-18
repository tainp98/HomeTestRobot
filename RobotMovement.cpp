#include "RobotMovement.h"
#include <math.h>
RobotMovement::RobotMovement()
 : isCreatedSuccess_(false)
{

}

RobotMovement::RobotMovement(int dimension)
    : dimension_(dimension), isCreatedSuccess_(false)
{
    // asume that dimention should be greater than 0 and less than 200
    if(dimension_ <= 0 || dimension_ > 200) return;
    robotMap_ = std::vector<bool>(dimension_*dimension_, false);
    isCreatedSuccess_ = true;
}

void RobotMovement::create(int dimension)
{
    dimension_ = dimension;
    if(dimension_ <= 0 || dimension_ > 200) return;
    robotMap_ = std::vector<bool>(dimension_*dimension_, false);
    isCreatedSuccess_ = true;
}

void RobotMovement::doAction(CommandType commandType, const Point& p)
{
    switch (commandType) {
    case CommandType::MOVE:
        this->moveToPoint(p);
        break;
    case CommandType::LINE:
        this->lineToPoint(p);
        break;
    case CommandType::CIRCLE:
        this->circleToPoint(p);
        break;
    default:
        break;
    }
}

void RobotMovement::displayDataConsole()
{
    if(!isCreatedSuccess_) return;
    for (int i = 0; i < dimension_; i++) {
        for (int j = 0; j < dimension_; j++) {
            std::cout << "+---";
        }
        std::cout << "+" << std::endl;
        for (int j = 0; j < dimension_; j++) {
            if(robotMap_[i*dimension_ + j]) std::cout << "| + ";
            else std::cout << "|   ";
        }
        std::cout << "|" << std::endl;
    }

    for (int j = 0; j < dimension_; j++) {
        std::cout << "+---";
    }
    std::cout << "+" << std::endl;
}

void RobotMovement::displayDataBitmap()
{
    if(!isCreatedSuccess_) return;
    std::vector<RGB> bitmap(dimension_*dimension_, {255, 255, 255});
    RGB circleColor = {0, 0, 255};
    for(int i = 0; i < robotMap_.size(); i++){
        if(robotMap_[i]){
            bitmap[i] = circleColor;
        }
    }
    saveBitmap(bitmap, "output_bitmap.bmp");
}

void RobotMovement::moveToPoint(const Point& p)
{
    std::cout<<"GridMap::moveToPoint"<<std::endl;
    if(!checkPointValid(p) || !isCreatedSuccess_) return;
    // move to p
    robotPos_ = p;
    robotMap_[p.y * dimension_ + p.x] = true; // mark this point as visited
}

void RobotMovement::lineToPoint(const Point& p)
{
    std::cout<<"GridMap::lineToPoint"<<std::endl;
    if(!checkPointValid(p) || !isCreatedSuccess_) return;
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
        robotMap_[robotPos_.y * dimension_ + robotPos_.x] = true;
    }
}

void RobotMovement::circleToPoint(const Point& p)
{
    std::cout<<"GridMap::circleToPoint"<<std::endl;
    if(!checkPointValid(p) || !isCreatedSuccess_) return;
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

bool RobotMovement::checkPointValid(Point p)
{
    if(p.x < 0 || p.x >= dimension_ || p.y < 0 || p.y >= dimension_) return false;
    else return true;
}

int RobotMovement::squareDistanceOf2Point(Point p1, Point p2)
{
    return (p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y);
}

std::vector<Point> RobotMovement::findneighborPoints(Point p)
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

void RobotMovement::setPixel(int x, int y)
{
    if (x >= 0 && x < dimension_ && y >= 0 && y < dimension_) {
        robotMap_[y * dimension_ + x] = true;
    }
}

void RobotMovement::saveBitmap(const std::vector<RGB> &bitmap, const std::string &filename)
{
    std::ofstream file(filename, std::ios::binary);

    // Bitmap file header
    const int HEADER_SIZE = 54;
    const int PIXEL_ARRAY_OFFSET = 54;
    const int BITS_PER_PIXEL = 24;
    const unsigned char WIDTH = dimension_;
    const unsigned char HEIGHT = dimension_;
    unsigned char header[54] = {
        'B', 'M',                               // Signature
        0, 0, 0, 0,                             // Image file size in bytes
        0, 0, 0, 0,                             // Reserved
        PIXEL_ARRAY_OFFSET, 0, 0, 0,            // Pixel data offset
        40, 0, 0, 0,                            // Header size
        WIDTH, 0, 0, 0,                         // Image width
        HEIGHT, 0, 0, 0,                        // Image height
        1, 0,                                   // Planes
        BITS_PER_PIXEL, 0,                      // Bits per pixel
        0, 0, 0, 0,                             // Compression
        0, 0, 0, 0,                             // Image size (can be 0 for uncompressed)
        0, 0, 0, 0,                             // Horizontal resolution
        0, 0, 0, 0,                             // Vertical resolution
        0, 0, 0, 0,                             // Colors in color table
        0, 0, 0, 0                              // Important color count
    };

    // Set the file size
    int fileSize = HEADER_SIZE + WIDTH * HEIGHT * 3;
    header[2] = fileSize & 0xFF;
    header[3] = (fileSize >> 8) & 0xFF;
    header[4] = (fileSize >> 16) & 0xFF;
    header[5] = (fileSize >> 24) & 0xFF;

    // Write header
    file.write(reinterpret_cast<char*>(header), HEADER_SIZE);

    // Write pixel data
    for (int y = HEIGHT - 1; y >= 0; y--) {  // BMP format stores pixels bottom-to-top
        for (int x = 0; x < WIDTH; x++) {
            RGB color = bitmap[y * WIDTH + x];
            file.write(reinterpret_cast<char*>(&color), 3);
        }
    }

    file.close();
}
