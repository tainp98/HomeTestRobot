#include <iostream>
#include <fstream>
#include "Application.h"

int main(int argc, char * argv[]) {
    Application app;
    std::ifstream file("input.txt");  // Open file

    std::string line;
    std::vector<std::string> commandList;
    while (std::getline(file, line)) {  // Read file line-by-line
        std::cout << line << std::endl;  // Output each line
        if(int index = line.find("DIMENSION"); index != std::string::npos){
            app.createMap(std::stoi(line.substr(index + 9)));
        }
        else{
            commandList.push_back(line);
        }
    }
    file.close();
    app.readCommands(commandList);
    app.exec();

    return 0;
}
