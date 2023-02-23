package test;
import algorithms.mazeGenerators.*;
public class RunMazeGenerator {
    public static void main(String[] args) {
       // testMazeGenerator(new EmptyMazeGenerator());
       // testMazeGenerator(new SimpleMazeGenerator());
        testMazeGenerator(new MyMazeGenerator());
    }
    private static void testMazeGenerator(IMazeGenerator mazeGenerator) {
// prints the time it takes the algorithm to run
        System.out.printf("Maze generation time(ms): %s%n", mazeGenerator.measureAlgorithmTimeMillis(1000/*rows*/, 1000/*columns*/));
// generate another maze
        Maze maze = mazeGenerator.generate(50/*rows*/, 50/*columns*/);

// prints the maze
        maze.print();
// get the maze entrance
        Position startPosition = maze.getStartPosition();
// print the start position
        System.out.printf("Start Position: %s%n", startPosition); // format "{row,column}"
// prints the maze exit position
        System.out.printf("Goal Position: %s%n", maze.getGoalPosition());

    }
}
