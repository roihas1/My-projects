package algorithms.search;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashSet;

public abstract class ASearchingAlgorithm {
    protected ArrayList<AState> AVisited = new ArrayList<>();
    protected String Name;
    protected int numOfNodes;
    public int getAVisitedLength(){
        return AVisited.size();
    }
    public ASearchingAlgorithm(String dfs) {
        Name = dfs;
    }

    public String getName() {
        return Name;
    }

    public int getNumberOfNodesEvaluated() {

        return numOfNodes;
    }

    /**
     * return the maze to the start state where all cell not visited and have cost of 0.
     * @param MazeToSolve - maze which finished to solve
     */
    public void setFalseToAllStates(ISearchable MazeToSolve)
    {
        int row = ((SearchableMaze)MazeToSolve).getNewGrid().length;
        int column = ((SearchableMaze)MazeToSolve).getNewGrid()[0].length;
        for (int i=0; i<row;i++)
        {
            for(int j=0;j<column;j++)
            {
                ((SearchableMaze)MazeToSolve).getNewGrid()[i][j].HasVisited=false;
                ((SearchableMaze)MazeToSolve).getNewGrid()[i][j].cost = 0;
            }
        }
    }
    public static class StateComparator implements Comparator<AState> {
        @Override
        public int compare(AState o1, AState o2) {
            if(o1.cost > o2.cost)
                return 1;
            else if (o1.cost < o2.cost)
                return -1;
            return 0;
        }
    }

}
