package algorithms.search;

import java.util.Comparator;
import java.util.PriorityQueue;

public class BestFirstSearch extends BreadthFirstSearch implements ISearchingAlgorithm {

    public BestFirstSearch() {
        super("Best First Search");
        PQueue = new PriorityQueue<>(1,new StateComparator());
    }

/**
     * adding all neighbors by clockwise order to priority queue.
     * Set cost according to - corners =>15 , up,right,down,left => 10
     * Set state to be parented to his neighbors
     * @param state the state to check his neighbors
*/
    @Override
    public void addAllNeighbors(AState state)
    {
        for (int i = 0 ; i < state.AllNeighborsAround.length;i+=1)
        {
            if(state.AllNeighborsAround[i] != null && !state.AllNeighborsAround[i].HasVisited){
               if (i % 2 == 0)
                   state.AllNeighborsAround[i].setCost(10);
               else
                   state.AllNeighborsAround[i].setCost(15);

                state.AllNeighborsAround[i].HasVisited = true;//added
                PQueue.add(state.AllNeighborsAround[i]);
                state.AllNeighborsAround[i].setParent(state);
            }
        }
    }



}

