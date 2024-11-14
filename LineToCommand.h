#ifndef LINETOCOMMAND_H
#define LINETOCOMMAND_H
#include "Command.h"
#include "GridMap.h"
#include <memory>
class LineToCommand : public Command
{
public:
    LineToCommand(std::shared_ptr<GridMap> gridMap, Point targetPoint);
    void execute() override;
private:
    std::shared_ptr<GridMap> gridMap_;
    Point targetPoint_;
};

#endif // LINETOCOMMAND_H
