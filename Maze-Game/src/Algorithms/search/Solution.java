package algorithms.search;

import java.io.Serializable;
import java.util.ArrayList;

public class Solution implements Serializable {
    ArrayList<AState> SolutionPath = new ArrayList<>(); //path of States/position of the solution

    public ArrayList<AState> getSolutionPath() {
        return SolutionPath;
    }

    /**
     * get byte array from the file, and convert it to a readable solution
     * @param bytes - byte array from the file
     */
    public Solution(byte[]bytes) {

        for (int i = 0; i < bytes.length;i += 4) {
            int row = (bytes[i] & 0xff) * 255 + (bytes[i + 1] & 0xff);
            int column = (bytes[i + 2] & 0xff) * 255 + (bytes[i + 3] & 0xff);
            SolutionPath.add(new MazeState(row, column, 0));
        }
    }

    public Solution() {

    }


    /**
     * transfer the Solution to byte array
     * each State in the solution gets 4 bytes.
     * 2 bytes present the row, and 2 bytes present the column
     * @return the solution in byte array
     */
    public byte[] toByteArray(){

        int index =0;
        byte[] ABytes = new byte[SolutionPath.size()*4];
        for (AState aState : SolutionPath) {
            int row = aState.getRow();
            int column = aState.getColumn();
            ABytes[index] = (byte) (row / 255);
            ABytes[index + 1] = (byte) (row % 255);
            ABytes[index + 2] = (byte) (column / 255);
            ABytes[index + 3] = (byte) (column % 255);
            index += 4;
        }
        return ABytes;
    }


}
