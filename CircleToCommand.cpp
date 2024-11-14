#include "CircleToCommand.h"

CircleToCommand::CircleToCommand(std::shared_ptr<GridMap> gridMap, Point targetPoint)
: gridMap_(gridMap), targetPoint_(targetPoint)
{

}

void CircleToCommand::execute()
{
    std::cout<<"CircleToCommand::execute targetPoint "<<"("<<targetPoint_.x<<", "<<targetPoint_.y<<")"<<std::endl;
    if(gridMap_) gridMap_->circleToPoint(targetPoint_);
}
