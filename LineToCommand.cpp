#include "LineToCommand.h"

LineToCommand::LineToCommand(std::shared_ptr<GridMap> gridMap, Point targetPoint)
: gridMap_(gridMap), targetPoint_(targetPoint)
{

}

void LineToCommand::execute()
{
    std::cout<<"LineToCommand::execute targetPoint "<<"("<<targetPoint_.x<<", "<<targetPoint_.y<<")"<<std::endl;
    if(gridMap_) gridMap_->lineToPoint(targetPoint_);
}
