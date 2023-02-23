package algorithms.mazeGenerators;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Random;

public class SimpleMazeGenerator extends AMazeGenerator {

    /**
     * generate maze with more than 1 solution possible
     * @param row - The number of rows
     * @param column - The number of columns
     * @return - A new generate Simple maze that has a few solutions.
     */
    @Override
    public Maze generate(int row , int column){

        Random rnd = new Random();
        ArrayList<Position> walls = new ArrayList<>(); //all neighbors
        ArrayList<Position> neighbors = new ArrayList<>(); //all points that already visited

        Maze FullMaze = new Maze(row, column);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                FullMaze.grid[i][j] = 1;
            }
        }

        FullMaze.grid[FullMaze.getStartPosition().getRowIndex()][FullMaze.getStartPosition().getColumnIndex()] = 0 ;
        add_neighbors(FullMaze.start , walls , FullMaze , row , column,1);
        Position check =FullMaze.start;

        while (walls.size()>0) {

            int indexToCheck = rnd.nextInt(walls.size());
            check = walls.get(indexToCheck);
            neighbors.clear();
            add_neighbors(check , neighbors , FullMaze , row , column,0);
            if (neighbors.size() == 0)
                continue;
            int indexToNeighbors = rnd.nextInt(neighbors.size());
            Position Neighbor = neighbors.get(indexToNeighbors);
            paint_maze(FullMaze , check , Neighbor);
            add_neighbors(check , walls , FullMaze , row , column,1);
            walls.remove(check);
        }
        //For GUI color - FullMaze.grid[FullMaze.getStartPosition().getRowIndex()][FullMaze.getStartPosition().getColumnIndex()] = 2;
        FullMaze.grid[FullMaze.getGoalPosition().getRowIndex()][FullMaze.getGoalPosition().getColumnIndex()] = 0;
        return FullMaze;
    }
}
