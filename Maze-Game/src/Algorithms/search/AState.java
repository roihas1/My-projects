package algorithms.search;

import java.io.Serializable;
import java.util.ArrayList;

public abstract class AState implements Serializable {
     protected int row;
     protected int column;
     protected int value;
     int cost;

    protected boolean HasVisited;
     protected AState parent;

     AState[] AllNeighborsAround;
    public int getRow() {
        return row;
    }

    public int getColumn() {
        return column;
    }

    public AState getParent() {
        return parent;
    }

    public void setParent(AState parent) {
        this.parent = parent;
    }

    public void setCost(int cost) {
        this.cost = cost;
    }
    public int getCost() {
        return cost;
    }

    public AState(int row, int column, int value) {
        this.row = row;
        this.column = column;
        AllNeighborsAround = new AState[8];
        for (AState state : AllNeighborsAround){state = null;}
        this.value = value;
        HasVisited=false;
        this.cost = 0;
    }
    @Override
    public boolean equals(Object state){
        if (state == this)
            return true;
        if(!(state instanceof AState))
                return false;

        return (((AState) state).getRow()==row && ((AState) state).getColumn()==column);
    }

    @Override
    public String toString() {
        return "{row=" + row +
                ", column=" + column +
                '}';
    }
}
