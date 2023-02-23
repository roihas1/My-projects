package algorithms.search;

import java.util.ArrayList;
import java.util.Stack;

public class DepthFirstSearch extends ASearchingAlgorithm implements ISearchingAlgorithm {

    protected Stack<AState> SgoBack = new Stack<>();
    public DepthFirstSearch(){
        super("DFS");
    }


    /**
     * return the first neighbor who wasn't visited yet - by clockwise order
     * @param state
     * @return state which is neighbor of state
     */
    public AState NextNeighbor(AState state)
    {
        if(state == null)
            return null;
        for (int i =0 ; i< state.AllNeighborsAround.length;i+=2){
            if(state.AllNeighborsAround[i] != null && !state.AllNeighborsAround[i].HasVisited)
            {
                return state.AllNeighborsAround[i];
            }
        }
        return null;
    }

    /**
     * solving the maze according the DFS algorithm.
     * @param MazeToSolve - Maze to  solve
     * @return - solution to the maze - a list of state the produce the solution
     */
    @Override
    public Solution solve(ISearchable MazeToSolve) {
        Solution sol = new Solution();
        AState current = ((SearchableMaze)MazeToSolve).getStart();
        SgoBack.push(current);
        while(current!=((SearchableMaze)MazeToSolve).getGoal()) //run until find the goal
        {
            current.HasVisited=true;

            while(true){
                current = NextNeighbor(current);
                if (current != null){
                    current.HasVisited=true;
                    SgoBack.push(current);
                    numOfNodes++;
                    break;
                }
                else {
                    SgoBack.pop();
                    if(SgoBack.empty())
                        break;
                    current = SgoBack.peek();
                }
            }
        }

        //The stack will hold all states from the start to goal
        while(!SgoBack.empty()){
            sol.SolutionPath.add(0,SgoBack.pop());
        }
        setFalseToAllStates(MazeToSolve);
        return sol;
    }
}
