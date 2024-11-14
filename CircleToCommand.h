#ifndef CIRCLETOCOMMAND_H
#define CIRCLETOCOMMAND_H
#include "Command.h"
#include "GridMap.h"
#include <memory>
class CircleToCommand : public Command
{
public:
    CircleToCommand(std::shared_ptr<GridMap> gridMap, Point targetPoint);
    void execute() override;
private:
    std::shared_ptr<GridMap> gridMap_;
    Point targetPoint_;
};

#endif // CIRCLETOCOMMAND_H
