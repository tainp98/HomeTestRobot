#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <vector>

class GridMap;
class Command;
class MapPrinter;
class Application
{
public:
    Application();
    void exec();
    void createMap(int dimention);
    void readCommands(const std::vector<std::string>& commandList);
private:
    std::shared_ptr<GridMap> robotMap_;
    std::vector<std::shared_ptr<Command>> commands;
    std::vector<std::string> printCommands;
    std::shared_ptr<MapPrinter> mapPrinter_;
};

#endif // APPLICATION_H
