package algorithms.mazeGenerators;

public class EmptyMazeGenerator extends AMazeGenerator{
    /**
     * building grid with num of rows,columns.
     * afterwards set each position with value 0.
     * @param row
     * @param column
     * @return a maze with all position with value 0.
     */
    @Override
    public Maze generate(int row, int column) {
        Maze emptyMaze = new Maze(row, column);
        for (int i=0; i<row;i++)
        {
            for(int j=0;j<column;j++)
            {
                emptyMaze.grid[i][j]=0;
            }
        }
        return emptyMaze;
    }
}
