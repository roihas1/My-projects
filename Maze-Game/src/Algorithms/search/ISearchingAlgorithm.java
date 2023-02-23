package algorithms.search;

public interface ISearchingAlgorithm {
    public Solution solve(ISearchable MazeToSolve);
    public String getName();
    public int  getNumberOfNodesEvaluated();

}
