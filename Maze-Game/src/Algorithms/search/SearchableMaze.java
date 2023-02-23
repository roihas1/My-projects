package algorithms.search;

import algorithms.mazeGenerators.Maze;

import java.util.ArrayList;

public class SearchableMaze implements ISearchable {

    private final AState[][] newGrid;
    private AState start;
    private AState goal;

    public AState[][] getNewGrid() {
        return newGrid;
    }

    public AState getStart() {
        return start;
    }

    public AState getGoal() {
        return goal;
    }

    /**
     * creating new grid in same size, sets for each position his neighbors with checkNeighbors func
     * @param maze
     */
    public SearchableMaze(Maze maze) {

        newGrid = new AState[maze.getGrid().length][maze.getGrid()[0].length];
        //convert data to new grid
        for(int i = 0 ; i< maze.getGrid().length ; i++){
            for (int j = 0 ; j < maze.getGrid()[0].length ; j++){
                newGrid[i][j] = new MazeState(i,j,maze.getGrid()[i][j]);
            }
        }
        //edit the neighbors for each position/state in the grid
        for(int i = 0 ; i< maze.getGrid().length ; i++){
            for (int j = 0 ; j < maze.getGrid()[0].length ; j++){
                if (maze.getGrid()[i][j]==0)
                    checkNeighbors(newGrid[i][j],maze);
            }
        }
        start = newGrid[maze.getStartPosition().getRowIndex()][maze.getStartPosition().getColumnIndex()];
        goal = newGrid[maze.getGoalPosition().getRowIndex()][maze.getGoalPosition().getColumnIndex()];
    }

    /**
     * The function get the maze and a specific state
     * Check the existing neighbors
     * Add the neighbors with value 0 to the state array of possible neighbors
     * @param state - specific position in the maze
     * @param maze - the current maze to search in
     */
    public void checkNeighbors(AState state, Maze maze){

        //up
        if(state.getRow() -1 >= 0 && maze.getGrid()[state.getRow() -1][state.getColumn()] == 0) {
            state.AllNeighborsAround[0] = newGrid[state.getRow() - 1][state.getColumn()];
        }
        //right
        if(state.getColumn() +1 < maze.getGrid()[0].length && maze.getGrid()[state.getRow()][state.getColumn()+1] == 0) {
            state.AllNeighborsAround[2] = newGrid[state.getRow()][state.getColumn() + 1];
        }
        //down
        if(state.getRow() +1 < maze.getGrid().length && maze.getGrid()[state.getRow() +1][state.getColumn()] == 0) {
            state.AllNeighborsAround[4] = newGrid[state.getRow() + 1][state.getColumn()];
        }
        //left
        if(state.getColumn() -1 >= 0 && maze.getGrid()[state.getRow()][state.getColumn()-1] == 0) {
            state.AllNeighborsAround[6] = newGrid[state.getRow()][state.getColumn() - 1];
        }

        //up-right
        if (state.getRow() - 1 >= 0 && state.getColumn() + 1 < maze.getGrid()[0].length && maze.getGrid()[state.getRow() - 1][state.getColumn() + 1] == 0) {
            if(state.AllNeighborsAround[0]!=null||state.AllNeighborsAround[2]!=null) {
                state.AllNeighborsAround[1] = newGrid[state.getRow() - 1][state.getColumn() + 1];
            }

        }
        //down-right
        if (state.getRow() + 1 < maze.getGrid().length && state.getColumn() +1 < maze.getGrid()[0].length && maze.getGrid()[state.getRow() + 1][state.getColumn() + 1] == 0){
            if(state.AllNeighborsAround[2]!=null||state.AllNeighborsAround[4]!=null) {
                state.AllNeighborsAround[3] = newGrid[state.getRow() + 1][state.getColumn() + 1];
            }
        }
        //down-left
        if (state.getRow() + 1 < maze.getGrid().length && state.getColumn() - 1 >= 0 && maze.getGrid()[state.getRow() + 1][state.getColumn() - 1] == 0){
            if(state.AllNeighborsAround[4]!=null||state.AllNeighborsAround[6]!=null){
                state.AllNeighborsAround[5] = newGrid[state.getRow() + 1][state.getColumn() - 1];
            }
        }
        //up-left
        if (state.getRow() - 1 >= 0 && state.getColumn()-1 >= 0 && maze.getGrid()[state.getRow() - 1][state.getColumn() - 1] == 0){
            if(state.AllNeighborsAround[0]!=null||state.AllNeighborsAround[6]!=null){
                state.AllNeighborsAround[7] = newGrid[state.getRow() - 1][state.getColumn() - 1];
            }
        }
    }

    /**
     * Check who the existing neighbors of the State
     * @param state - position in the maze
     * @return - all the possible states that state can reach
     */
    public ArrayList<AState> getAllPossibleStates(AState state)
    {
        ArrayList<AState> AllPossibleStates = new ArrayList<>();
        for (int i = 0 ; i < state.AllNeighborsAround.length;i++){
            if (state.AllNeighborsAround[i] != null)
                AllPossibleStates.add(state.AllNeighborsAround[i]);
        }
        return AllPossibleStates;
    }
}
