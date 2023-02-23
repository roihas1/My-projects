package algorithms.mazeGenerators;

import javax.swing.*;
import java.awt.*;
import java.io.Serializable;
import java.util.Random;

public class Maze implements Serializable {
     protected int [][] grid;
     protected Position start;
     protected Position goal;


    /**
     * convert the Abyte array details and define the maze details
     * @param Abytes
     */
     public Maze(byte[] Abytes){

         int row = (Abytes[0]&0xff)*255 + (Abytes[1]&0xff);
         int column = (Abytes[2]&0xff)*255 + (Abytes[3]&0xff) ;

         grid = new int[row][column];

         row = (Abytes[4]&0xff)*255+(Abytes[5]&0xff);
         column = (Abytes[6]&0xff)*255 + (Abytes[7]&0xff);
         start = new Position(row,column);

         row = (Abytes[8]&0xff)*255 + (Abytes[9]&0xff);
         column = (Abytes[10]&0xff)*255 + (Abytes[11]&0xff);
         goal = new Position(row,column);

         int index = 12;
         for (int i = 0 ;i < grid.length;i++) {
             for (int j = 0; j < grid[0].length; j++) {
                 grid[i][j] = Abytes[index];
                 index++;
             }
         }

      }
    /**
     * maze constructor
     * @param row
     * @param column
     */
     public Maze(int row, int column) {

        if(row < 2 || column < 2 ){
            //default size for illegal size of grid;
          row = 10;
          column = 10;
        }
        this.grid = new int[row][column];

        start = buildStartAndGoal(row, column);// generate start position
        goal = buildStartAndGoal(row, column);//generate goal position

        while(!isLegit() || start.equals(goal))
        {
            start = buildStartAndGoal(row, column);// generate start position
            goal = buildStartAndGoal(row, column);//generate goal position
        }
    }


    /**
     * building the Position for start point and goal point
     * @param row
     * @param column
     * @return new position
     */
    private Position buildStartAndGoal(int row,int column)
    {
        Random rnd = new Random();
        int indexRow = rnd.nextInt(row);
        int indexColumn;
        if(indexRow == 0 || indexRow == row-1)
            indexColumn = rnd.nextInt(column);
        else{
            int [] arr = {0,column-1};
            int ranIndex =rnd.nextInt(arr.length);
            indexColumn = arr[ranIndex];
        }
        return new Position(indexRow , indexColumn);
    }

    /**
     * function detect when goal position is not reachable.
     * example: start -> (0,0) & goal -> (5,5) => not legit
     * because algorithm jump between 2 positions
     * @return true or false
     */
    private boolean isLegit(){
      /*  return !((start.row % 2 == 0 && start.column % 2 == 0 && goal.row % 2 == 1 && goal.column%2 == 1) ||
                (start.row % 2  == 1 && start.column % 2 == 1 && goal.row % 2 == 0 && goal.column % 2 == 0));*/
        return (start.row % 2 == goal.row % 2 && start.column % 2 == goal.column % 2);
    }

    public int[][] getGrid() {
        return grid;
    }

    public Position getStartPosition() {
        return start;
    }

    public Position getGoalPosition() {
        return goal;
    }
    public void setGrid(int [][] grid){
        this.grid = grid;

    }


    /**
     * printing the maze with 1,0 values and S-start,E-goal
     */
    public void print(){
        for(int i = 0 ; i< grid.length ; i++){
            System.out.println();
            for (int j = 0 ; j < grid[0].length ; j++){
                if (i == start.row && j == start.column)
                    System.out.print("S");
                else if (i == goal.row && j == goal.column)
                    System.out.print("E");
                else{System.out.print(grid[i][j]);}
            }
        }
        System.out.println();
        //initializeWindow(); //todo delete
    }

    /**
     * GUI for the maze
     */
    private void initializeWindow() {
        JFrame mainFrame = new JFrame("Maze Solver");
        mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        mainFrame.setLayout(new GridLayout(this.grid.length, this.grid[0].length));// avoid null layouts
        //mainFrame.setSize(1920, 1080); //use preferred size and let layout manager set the size
        mainFrame.setLocationRelativeTo(null);

        for (int[] ints : this.grid) {
            for (int col = 0; col < this.grid[0].length; col++) {
                JLabel label = makeLabel(ints[col]);
                mainFrame.add(label);
            }
        }
        mainFrame.pack();
        mainFrame.setVisible(true);
    }

    private JLabel makeLabel(int c) {

        JLabel label= new JLabel();
        label.setHorizontalAlignment(JLabel.CENTER);
        label.setPreferredSize(new Dimension(this.grid.length, this.grid[0].length));
        switch(c) {
            case 1:
                label.setBackground(Color.BLACK);
                break;
            case 2:
                label.setBackground(Color.GREEN);
                break;
            case 3:
                label.setBackground(Color.BLUE);
                break;
            default:
                label.setBackground(Color.white);
                break;

        }
        label.setOpaque(true);
        label.setBorder(BorderFactory.createLineBorder(Color.WHITE, 1));
        return label;
    }

    /**
     * The function convert each detail of the maze to a number in byte
     * the formula: (number = number/127 + number%127)
     * each number has 2 cells: first-number/127, second-number%127
     * after converting numbers, enters the grid cell by 1&0.
     * @return an array with byte numbers : array - (gridRow,gridColumn, StartRow,StartColumn,GoalRow,GoalColumn, grid cells))
     */
    public byte[] toByteArray(){

        byte[] ABytes = new byte[12+ grid.length*grid[0].length];

        //size of the maze
        ABytes[0] =(byte)(grid.length/255);//row
        ABytes[1] = (byte) (grid.length%255);// row reminder
        ABytes[2] = (byte)(grid[0].length/255);//column
        ABytes[3] = (byte)(grid[0].length%255);//column reminder
        //entry point
        ABytes[4] = (byte)(start.row/255);
        ABytes[5] = (byte)(start.row%255);
        ABytes[6] = (byte)(start.column/255);
        ABytes[7] = (byte)(start.column%255);
        //goal point
        ABytes[8] = (byte)(goal.row/255);
        ABytes[9] = (byte)(goal.row%255);
        ABytes[10] = (byte)(goal.column/255);
        ABytes[11] = (byte)(goal.column%255);
        // cells value
        int index = 12;
        for (int[] ints : grid) {
            for (int j = 0; j < grid[0].length; j++) {
                ABytes[index] = (byte) ints[j];
                index++;
            }
        }

        return ABytes;
    }


}
