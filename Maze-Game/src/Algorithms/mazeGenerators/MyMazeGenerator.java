package algorithms.mazeGenerators;

import java.util.ArrayList;
import java.util.Random;
import java.util.Stack;

public class MyMazeGenerator extends AMazeGenerator {


    /**
     * generate maze with 1 solution possible
     * @param row
     * @param column
     * @return
     */
    @Override
    public Maze generate(int row, int column) {

        Random rnd = new Random();
        Stack<Position> SRollBack = new Stack<>();
        ArrayList<Position> ANeighbors = new ArrayList<>(); //all neighbors of current position
        Maze FullMaze = new Maze(row, column);

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                FullMaze.grid[i][j] = 1;
            }
        }

        SRollBack.push(FullMaze.start);
        FullMaze.grid[FullMaze.start.getRowIndex()][FullMaze.start.getColumnIndex()] = 0;
        Position check = FullMaze.start;

        while (!SRollBack.empty())
        {
            ANeighbors.clear();
            add_neighbors(check,ANeighbors,FullMaze,row , column,1);

            while (ANeighbors.size()==0)
            {
                SRollBack.pop();
                if (SRollBack.empty()){break;}
                check = SRollBack.peek();
                add_neighbors(check,ANeighbors,FullMaze,row , column,1);
            }
            if (SRollBack.empty()){break;}
            Position neighbor = ANeighbors.get(rnd.nextInt(ANeighbors.size()));
            SRollBack.push(neighbor);
            paint_maze(FullMaze,neighbor,check);
            check = neighbor;
        }

       // For GUI - FullMaze.grid[FullMaze.getStartPosition().getRowIndex()][FullMaze.getStartPosition().getColumnIndex()] = 2;
        FullMaze.grid[FullMaze.getGoalPosition().getRowIndex()][FullMaze.getGoalPosition().getColumnIndex()] = 0;
        return FullMaze;

    }
}

