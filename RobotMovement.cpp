#include "RobotMovement.h"
#include <math.h>
RobotMovement::RobotMovement() {}

RobotMovement::RobotMovement(int dimension)
    : dimension_(dimension)
{
    if(dimension_ <= 0 || dimension_ > 200) return;
    robotMap_ = std::vector<bool>(dimension_*dimension_, false);
}

void RobotMovement::create(int dimension)
{
    dimension_ = dimension;
    if(dimension_ <= 0 || dimension_ > 200) return;
    robotMap_ = std::vector<bool>(dimension_*dimension_, false);
}

void RobotMovement::doAction(const std::string& action, const Point& p)
{
    if(actions_.find(action) != actions_.end() && actions_[action] != nullptr){
        actions_[action]->execute(robotPos_, robotMap_, dimension_, p);
    }
    else{
        actions_[action] = createAction(action);
        if(actions_[action]) actions_[action]->execute(robotPos_, robotMap_, dimension_, p);
    }
}

void RobotMovement::displayDataConsole()
{
    if(robotMap_.size() == 0) return;
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
    if(robotMap_.size() == 0) return;
    std::vector<RGB> bitmap(dimension_*dimension_, {255, 255, 255});
    RGB circleColor = {0, 0, 255};
    for(int i = 0; i < robotMap_.size(); i++){
        if(robotMap_[i]){
            bitmap[i] = circleColor;
        }
    }
    saveBitmap(bitmap, "output_bitmap.bmp");
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

void MoveToAction::execute(Point &currPos, std::vector<bool> &grid, int dim, const Point &targetPos)
{
    std::cout<<"MoveToAction::execute"<<std::endl;
    if(grid.size() == 0) return;
    if(targetPos.x < 0 || targetPos.y < 0 || ((targetPos.y*dim + targetPos.x) >= grid.size())) return;
    // move to p
    currPos = targetPos;
    grid[targetPos.y * dim + targetPos.x] = true; // mark this point as visited
}

void LineToAction::execute(Point &currPos, std::vector<bool> &grid, int dim, const Point &targetPos)
{
    std::cout<<"LineToAction::execute"<<std::endl;
    if(grid.size() == 0) return;
    if(targetPos.x < 0 || targetPos.y < 0 || ((targetPos.y*dim + targetPos.x) >= grid.size())) return;
    // using A* algorithm to find path from robotPos to point P

    // choose the next point to step in is the point that
    // distance euclid from it to target is smallest
    while (currPos != targetPos) {
        auto neighborPoint = findneighborPoints(currPos, dim);
        if(neighborPoint.size() == 0){
            std::cout<<"neighborPoint empty"<<std::endl;
            return;
        }
        Point choosedPoint = neighborPoint[0];
        for(int i = 1; i < neighborPoint.size(); i++){
            if(squareDistanceOf2Point(choosedPoint, targetPos) > squareDistanceOf2Point(neighborPoint[i], targetPos)){
                choosedPoint = neighborPoint[i];
            }
        }
        currPos = choosedPoint;
        grid[currPos.y * dim + currPos.x] = true;
    }
}

int LineToAction::squareDistanceOf2Point(const Point& p1, const Point& p2)
{
    return (p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y);
}

std::vector<Point> LineToAction::findneighborPoints(const Point& p, int dim)
{
    std::vector<Point> res;
    if(checkPointValid(Point(p.x-1, p.y-1),dim)) res.push_back(Point(p.x-1, p.y-1));
    if(checkPointValid(Point(p.x, p.y-1),dim)) res.push_back(Point(p.x, p.y-1));
    if(checkPointValid(Point(p.x+1, p.y-1),dim)) res.push_back(Point(p.x+1, p.y-1));
    if(checkPointValid(Point(p.x-1, p.y),dim)) res.push_back(Point(p.x-1, p.y));
    if(checkPointValid(Point(p.x+1, p.y),dim)) res.push_back(Point(p.x+1, p.y));
    if(checkPointValid(Point(p.x-1, p.y+1),dim)) res.push_back(Point(p.x-1, p.y+1));
    if(checkPointValid(Point(p.x, p.y+1),dim)) res.push_back(Point(p.x, p.y+1));
    if(checkPointValid(Point(p.x+1, p.y+1),dim)) res.push_back(Point(p.x+1, p.y+1));
    return res;
}

bool LineToAction::checkPointValid(const Point &p, int dim)
{
    if(p.x < 0 || p.x >= dim || p.y < 0 || p.y >= dim) return false;
    else return true;
}

void CircleToAction::execute(Point &currPos, std::vector<bool> &grid, int dim, const Point &targetPos)
{
    std::cout<<"CircleToAction::execute"<<std::endl;
    if(grid.size() == 0) return;
    if(targetPos.x < 0 || targetPos.y < 0 || ((targetPos.y*dim + targetPos.x) >= grid.size())) return;
    int radius = std::sqrt(((targetPos.x-currPos.x)*(targetPos.x - currPos.x) + (targetPos.y-currPos.y)*(targetPos.y - currPos.y)));
    std::cout<<"radius: "<<radius<<std::endl;
    int x = radius, y = 0;
    int decisionOver2 = 1 - x;
    while (x >= y) {
        // Plot the circle points in each octant
        setPixel(currPos.x + x, currPos.y + y, dim, grid);
        setPixel(currPos.x + y, currPos.y + x, dim, grid);
        setPixel(currPos.x - y, currPos.y + x, dim, grid);
        setPixel(currPos.x - x, currPos.y + y, dim, grid);
        setPixel(currPos.x - x, currPos.y - y, dim, grid);
        setPixel(currPos.x - y, currPos.y - x, dim, grid);
        setPixel(currPos.x + y, currPos.y - x, dim, grid);
        setPixel(currPos.x + x, currPos.y - y, dim, grid);
        y++;
        if (decisionOver2 <= 0) {
            decisionOver2 += 2 * y + 1;
        } else {
            x--;
            decisionOver2 += 2 * (y - x) + 1;
        }
    }
}

void CircleToAction::setPixel(int x, int y, int dim, std::vector<bool>& grid)
{
    if (x >= 0 && x < dim && y >= 0 && y < dim) {
        grid[y * dim + x] = true;
    }
}
