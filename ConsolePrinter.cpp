#include "ConsolePrinter.h"

ConsolePrinter::ConsolePrinter(std::shared_ptr<GridMap> gridMap)
    : gridMap_(gridMap)
{

}

void ConsolePrinter::print()
{
    if(!gridMap_->isGridMapCreatedSuccess()) return;
    const std::vector<bool>& gridMap = gridMap_->gridMap();
    for (int i = 0; i < gridMap_->dimension(); i++) {
        for (int j = 0; j < gridMap_->dimension(); j++) {
            std::cout << "+---";
        }
        std::cout << "+" << std::endl;
        for (int j = 0; j < gridMap_->dimension(); j++) {
            if(gridMap[i*gridMap_->dimension() + j]) std::cout << "| + ";
            else std::cout << "|   ";
        }
        std::cout << "|" << std::endl;
    }

    for (int j = 0; j < gridMap_->dimension(); j++) {
        std::cout << "+---";
    }
    std::cout << "+" << std::endl;
}
