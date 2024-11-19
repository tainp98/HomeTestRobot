### 1. Using pure C++, no external library. 
- We can design base functions for actions: Move_To (mark the point we move to as visited), Line_To function to find shortest path from current point to target point using A* algorithm, each point in the path we mark as visited.
- Designing base function for display result: Display console function and display bitmap function.

### 2. Design in OOP so we can easily add more commands (such as CIRCLE_TO), or how to express the result (such as output to a bitmap image)
- I define a base abstract class Action with pure virtual function execute.
- Each new action added, we can define new class type inherit from Action class and implementing execute method.
- to use in Robot Class, We create a map with key type of string as Action name and value type of unique pointer of type Action.
- When do action, we call execute of pointer corresponding to the Action name key from the map.

### 3. Handle input errors if possible
- Set limitation on dimension from input as 200. Because limitation of bitmap image size.
- We can handle some error coordinates from input like -1,-1 ....

### The input file will look like that
DIMENSION 200<br>
MOVE_TO 1,1<br>
LINE_TO 3,3<br>
LINE_TO 2,3<br>
MOVE_TO 90,90<br>
CIRCLE_TO 20,30<br>

### How to build and run program
- That cmake file is created with qt creator on windows 10.
- After building, we can check execute file in build/ folder.
- Creating input file
- Then Run ```HomeTestRobotic.exe input.txt```
