#include "Application.h"

#include "GridMap.h"
#include "Command.h"
#include "MoveToCommand.h"
#include "LineToCommand.h"
#include "CircleToCommand.h"
#include "ConsolePrinter.h"
#include "BitmapPrinter.h"

Application::Application() {}

void Application::exec()
{
    for(int i = 0; i < commands.size(); i++){
        commands[i]->execute();
    }
    for(auto& printCommand : printCommands){
        if(printCommand.find("CONSOLE") != std::string::npos){
            std::cout<<"print console\n";
            mapPrinter_ = std::make_shared<ConsolePrinter>(this->robotMap_);
            mapPrinter_->print();
        }
        if(printCommand.find("BITMAP") != std::string::npos){
            std::cout<<"print bitmap\n";
            mapPrinter_ = std::make_shared<BitmapPrinter>(this->robotMap_);
            mapPrinter_->print();
        }
    }
}

void Application::createMap(int dimention)
{
    if(!robotMap_){
        robotMap_ = std::make_shared<GridMap>(dimention);
    }
    else{
        robotMap_->createMap(dimention);
    }
}

void Application::readCommands(const std::vector<std::string> &commandList)
{
    const int SIZE_OF_MOVE_TO = 7;
    const int SIZE_OF_LINE_TO = 7;
    const int SIZE_OF_CIRCLE_TO = 9;
    commands.reserve(commandList.size());
    for(int i = 0; i < commandList.size(); i++){
        if(int index = commandList[i].find("MOVE_TO"); index != std::string::npos){
            if(int commaIndex = commandList[i].find(","); commaIndex != std::string::npos){
                Point target(std::stoi(commandList[i].substr(commaIndex+1)), std::stoi(commandList[i].substr(index+SIZE_OF_MOVE_TO+1, commaIndex - (index+SIZE_OF_MOVE_TO+1))));
                commands.push_back(std::make_shared<MoveToCommand>(this->robotMap_,target));
            }
        }
        else if(int index = commandList[i].find("LINE_TO"); index != std::string::npos){
            if(int commaIndex = commandList[i].find(","); commaIndex != std::string::npos){
                Point target(std::stoi(commandList[i].substr(commaIndex+1)), std::stoi(commandList[i].substr(index+SIZE_OF_LINE_TO+1, commaIndex - (index+SIZE_OF_LINE_TO+1))));
                commands.push_back(std::make_shared<LineToCommand>(this->robotMap_,target));
            }
        }
        else if(int index = commandList[i].find("CIRCLE_TO"); index != std::string::npos){
            if(int commaIndex = commandList[i].find(","); commaIndex != std::string::npos){
                Point target(std::stoi(commandList[i].substr(commaIndex+1)), std::stoi(commandList[i].substr(index+SIZE_OF_CIRCLE_TO+1, commaIndex - (index+SIZE_OF_CIRCLE_TO+1))));
                commands.push_back(std::make_shared<CircleToCommand>(this->robotMap_,target));
            }
        }
        else if(commandList[i].find("PRINT") != std::string::npos){
            printCommands.push_back(commandList[i]);
        }
    }

}
