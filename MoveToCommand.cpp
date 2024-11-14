#include "MoveToCommand.h"
#include "GridMap.h"

MoveToCommand::MoveToCommand(std::shared_ptr<GridMap> gridMap, Point targetPoint)
    : gridMap_(gridMap), targetPoint_(targetPoint)
{

}

void MoveToCommand::execute()
{
    std::cout<<"MoveToCommand::execute targetPoint "<<"("<<targetPoint_.x<<", "<<targetPoint_.y<<")"<<std::endl;
    if(gridMap_) gridMap_->moveToPoint(targetPoint_);
}
