package algorithms.mazeGenerators;

import java.io.Serializable;

public class Position implements Serializable {
    protected int column;
    protected int row;

    public Position(int row,int column) {
        this.column = column;
        this.row = row;
    }

    @Override
    public String toString() {
        return "{" + row + "," + column + '}';
    }
    public int getColumnIndex() {
        return column;
    }
    public int getRowIndex() {
        return row;
    }

    public void setColumn(int column) {
        this.column = column;
    }

    public void setRow(int row) {
        this.row = row;
    }

    /**
     * create equal function between 2 positions
     * checking by row&column
     * @param o
     * @return true or false
     */
    @Override
    public boolean equals(Object o ){
        if ( o == this)
            return true;
        if(!(o instanceof Position))
            return false;

        Position p = (Position) o;
        return (p.row==row && p.column==column);
    }


}
