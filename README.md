### 1 + 2. Using pure C++, no external library. Design in OOP so we can easily add more commands (such as CIRCLE_TO), or how to express the result (such as output to a bitmap image)

- I use Command pattern (Bebavioral Pattern) to implement Command requesting/doing in this case. Each command from file treated as a Command Object.
When Command Object executes, it call real object to take action.
   - Real Object that called from Command Object is GridMap object that represent matrix map and define actions on it like MOVE_TO, LINE_TO, CIRCLE_TO...
   - Easy for extent if need add new Command Type.
   - For LINE_TO commmand needs find shortest path from current position to target position, i use A* algorithm. To choose next node to go for from current node, we defind f = g + h. g is cost go from current node to it's neighbor nodes (equal 1), and h is heuristic distance from each neighbor node to target node, we choose node that has h is minimum. I use euclid distance to calculate h. We apply that strategy continuously until meet target point, then the algorithm finishs.
- I create an Application class that initializes Objects and read input for our app.

- To print output to console or bitmap. I create MapPrint abstract class that has interface "print"
   - That i can extent output print type.
   - I put PRINT TYPE in input file too for testing.

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
PRINT CONSOLE<br>
PRINT BITMAP<br>
