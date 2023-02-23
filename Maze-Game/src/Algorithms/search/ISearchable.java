package algorithms.search;

import algorithms.mazeGenerators.Maze;

import java.util.ArrayList;

public interface ISearchable {
   public void checkNeighbors(AState state , Maze maze);
   public ArrayList<AState> getAllPossibleStates(AState state);

}
