### 1 + 2. Using pure C++, no external library. Design in OOP so we can easily add more commands (such as CIRCLE_TO), or how to express the result (such as output to a bitmap image)

- I create a class RobotMovement represent map and actions on it. Firstly, we create funtions for MOVE_TO and LINE_TO command. I define a enum class for CommandType. If a new command need to be added, i add new CommandType on enum class and create new function to do it.
   - For LINE_TO commmand needs find shortest path from current position to target position, i use A* algorithm. To choose next node to go for from current node, we defind f = g + h. g is cost go from current node to it's neighbor nodes (equal 1), and h is heuristic distance from each neighbor node to target node, we choose node that has h is minimum. I use euclid distance to calculate h. We apply that strategy continuously until meet target point, then the algorithm finishs.

- To represent data of robot movement, i using a vector bool with size of dimesion*dimension to save state of each pixel robot visited. Then i can use this data to draw grid output to console or draw a bitmap image

### 3. Handle input errors if possible
- I set limitation on dimension from input as 200. Because limitation of bitmap image size.
- Handle some error coordinates from input like -1,-1 ....

### The input file will look like that
DIMENSION 200<br>
MOVE_TO 1,1<br>
LINE_TO 3,3<br>
LINE_TO 2,3<br>
MOVE_TO 90,90<br>
CIRCLE_TO 20,30<br>
