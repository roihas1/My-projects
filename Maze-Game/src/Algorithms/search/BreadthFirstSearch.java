package algorithms.search;
import java.util.LinkedList;
import java.util.Queue;

public class BreadthFirstSearch extends ASearchingAlgorithm implements ISearchingAlgorithm {

    protected Queue<AState> PQueue;

    public BreadthFirstSearch(String name) {
        super(name);
        PQueue = new LinkedList<>();
    }

    public BreadthFirstSearch() {
        super("BFS");
        PQueue = new LinkedList<>();
    }


    /**
     * adding all neighbors from all sides to queue (default cost is 0)
     * @param state - the state to check his neighbors
     */
    public void addAllNeighbors(AState state) {
        for (int i = 0; i < state.AllNeighborsAround.length; i += 1) {
            if (state.AllNeighborsAround[i] != null && !state.AllNeighborsAround[i].HasVisited) {

                state.AllNeighborsAround[i].HasVisited = true;//added
                PQueue.add(state.AllNeighborsAround[i]);
                state.AllNeighborsAround[i].setParent(state);
            }
        }

    }

    /**
     *
     * @param MazeToSolve - Maze To Solve
     * @return - the solution - an arraylist with all the solution state.
     */
    @Override
    public Solution solve(ISearchable MazeToSolve) {

        AState current = ((SearchableMaze) MazeToSolve).getStart();
        current.setParent(null);
        PQueue.add(current);
        current.HasVisited = true;

        while (PQueue.peek() != ((SearchableMaze) MazeToSolve).getGoal()) {
            assert PQueue.peek() != null;
            addAllNeighbors(PQueue.poll());
            numOfNodes++;
        }
        current = PQueue.peek();
        Solution sol = new Solution();
        while (current != null) {
            sol.SolutionPath.add(0, current);
            current = current.getParent();
        }
        setFalseToAllStates(MazeToSolve);
        return sol;

    }

    
}