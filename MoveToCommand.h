#ifndef MOVETOCOMMAND_H
#define MOVETOCOMMAND_H
#include "Command.h"
#include "GridMap.h"
#include <memory>
class MoveToCommand : public Command
{
public:
    MoveToCommand(std::shared_ptr<GridMap> gridMap, Point targetPoint);
    void execute() override;
private:
    std::shared_ptr<GridMap> gridMap_;
    Point targetPoint_;
};

#endif // MOVETOCOMMAND_H
