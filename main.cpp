#include "RobotMovement.h"
#define SIZE_MOVE_TO 7
#define SIZE_LINE_TO 7
#define SIZE_CIRCLE_TO 9


int main(int argc, char * argv[]) {

    if(argc < 2){
        std::cout<<"Please add input path file\n";
        return 1;
    }
    std::string fileName(argv[1]);
    std::cout<<"fileName: "<<fileName;
    std::ifstream file(fileName);  // Open file
    std::string line;
    RobotMovement robotMovement;
    while (std::getline(file, line)) {  // Read file line-by-line
        std::cout << line << std::endl;  // Output each line
        if(int index = line.find("DIMENSION"); index != std::string::npos){
            // create grid
            robotMovement.create(std::stoi(line.substr(index + 9)));
        }
        else{
            if(int index = line.find("MOVE_TO"); index != std::string::npos){
                if(int commaIndex = line.find(","); commaIndex != std::string::npos){
                    Point p(std::stoi(line.substr(commaIndex+1)), std::stoi(line.substr(index+SIZE_MOVE_TO+1, commaIndex - (index+SIZE_MOVE_TO+1))));
                    // move action
                    robotMovement.doAction("MOVE_TO", p);
                }
            }
            else if(int index = line.find("LINE_TO"); index != std::string::npos){
                if(int commaIndex = line.find(","); commaIndex != std::string::npos){
                    Point p(std::stoi(line.substr(commaIndex+1)), std::stoi(line.substr(index+SIZE_LINE_TO+1, commaIndex - (index+SIZE_LINE_TO+1))));
                    // line action
                    robotMovement.doAction("LINE_TO", p);
                }
            }
            else if(int index = line.find("CIRCLE_TO"); index != std::string::npos){
                if(int commaIndex = line.find(","); commaIndex != std::string::npos){
                    Point p(std::stoi(line.substr(commaIndex+1)), std::stoi(line.substr(index+SIZE_CIRCLE_TO+1, commaIndex - (index+SIZE_CIRCLE_TO+1))));
                    // circle action
                    robotMovement.doAction("CIRCLE_TO", p);
                }
            }
        }
    }
    file.close();
    robotMovement.displayDataConsole();
    robotMovement.displayDataBitmap();

    return 0;
}
