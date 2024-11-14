#ifndef CONSOLEPRINTER_H
#define CONSOLEPRINTER_H
#include "MapPrinter.h"
#include <vector>
#include <memory>
#include "GridMap.h"

class ConsolePrinter : public MapPrinter
{
public:
    ConsolePrinter(std::shared_ptr<GridMap> gridMap);
    void print() override;
private:
    std::shared_ptr<GridMap> gridMap_;
};

#endif // CONSOLEPRINTER_H
