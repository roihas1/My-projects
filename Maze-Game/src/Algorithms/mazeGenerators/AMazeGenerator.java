package algorithms.mazeGenerators;

import java.util.ArrayList;

public abstract class AMazeGenerator implements IMazeGenerator {

    @Override
    public abstract Maze generate(int row, int column);


    @Override
    public long measureAlgorithmTimeMillis(int row, int column) {
        long startTime = System.currentTimeMillis();
        generate(row,column);
        return System.currentTimeMillis() - startTime;
    }


    /**
     *
     * @param p - current position
     * @param w - list of neighbors of current position(adding new neighbors in the func)
     * @param FullMaze - current maze
     * @param row - num of rows in maze
     * @param column - num of columns in maze
     * @param index( index = 1 => who are my neighbors |||| index = 0 => who are the neighbors we can connect)
     */
    protected void add_neighbors(Position p, ArrayList<Position> w, Maze FullMaze , int row , int column, int index)
    {
        Position below = new Position(p.row + 2, p.column);
        if (p.row + 2 < row &&  FullMaze.grid[below.row][below.column] == index)
            w.add(below);

        Position up = new Position(p.row - 2, p.column);
        if (p.row - 2 >= 0 &&  FullMaze.grid[up.row][below.column] == index)
            w.add(up);

        Position right = new Position(p.row, p.column + 2);
        if (p.column + 2 < column && FullMaze.grid[right.row][right.column] == index)
            w.add(right);

        Position left = new Position(p.row, p.column - 2);
        if (p.column - 2 >= 0 &&  FullMaze.grid[left.row][left.column] == index)
            w.add(left);
    }

    /**
     * paint in the grid the neighbor of cell and the cell that sits between them
     * @param FullMaze the maze to p
     * @param check the current position
     * @param Neighbor the position that need to check if we can turn it to pass state
     */

    protected  void paint_maze(Maze FullMaze , Position check , Position Neighbor){

        if (check.getRowIndex()-2 == Neighbor.getRowIndex() && check.getColumnIndex() == Neighbor.getColumnIndex()) {
            FullMaze.grid[check.getRowIndex() - 1][check.getColumnIndex()] = 0;
        }

        else if (check.getRowIndex()+2 == Neighbor.getRowIndex() && check.getColumnIndex() == Neighbor.getColumnIndex()) {
            FullMaze.grid[check.getRowIndex() + 1][check.getColumnIndex()] = 0;
        }

        else if (check.getRowIndex() == Neighbor.getRowIndex() && check.getColumnIndex() -2  == Neighbor.getColumnIndex()) {
            FullMaze.grid[check.getRowIndex()][check.getColumnIndex() - 1] = 0;
        }

        else if (check.getRowIndex() == Neighbor.getRowIndex() && check.getColumnIndex()+2 == Neighbor.getColumnIndex()) {
            FullMaze.grid[check.getRowIndex()][check.getColumnIndex() + 1] = 0;
        }
        FullMaze.grid[check.getRowIndex()][check.getColumnIndex()] = 0;
    }
}
