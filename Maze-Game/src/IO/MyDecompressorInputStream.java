package IO;

import java.io.IOException;
import java.io.InputStream;

public class MyDecompressorInputStream extends InputStream {
    InputStream in;

    public MyDecompressorInputStream(InputStream in) {
        this.in = in;
    }

/**
     * get an Integer, calculate the binary number by 15 bits
     * @param num - an Integer number
     * @return - an array with 15 cells that present the Integer's phrase in binary number.
     */

    public byte[] IntToBinary(int num)
    {

        int testNum = num;
        byte[] BinaryNum = new byte[15];
        int index = 14;
        try {
            while (num > 0) {
                if (num % 2 == 1)
                    BinaryNum[index] = 1;
                else
                    BinaryNum[index] = 0;
                num = num / 2;
                index--;
            }
        }catch (Exception e){
            System.out.println(testNum);
        }
        while (index>=0)
        {
            BinaryNum[index]=0;
            index--;
        }
        return BinaryNum;
    }

/**
     * From the 12 spot in the array, each pair of cells present an Int number of 13 bits by Bytes.
     * using IntToBinary function we enter each Int by his Binary presentation to the bytes array that the function gets.
     * @param bytes   the buffer into which the data is read.
     * @return
     * @throws IOException
  */

    @Override
    public int read(byte[] bytes) throws IOException {
        int number = 0;
        int index = 12;
        byte[] BinaryNum = new byte[15];
        byte[] temp = new byte[bytes.length];
        for (int i=0;i<12;i++)
        {
            temp[i] = (byte) in.read();
        }

        int numOfCells = (((temp[0]&0xff)*255+(temp[1]&0xff)) * ((temp[2]&0xff)*255+(temp[3]&0xff)));
        int lengthOfCompress = ((numOfCells/15)+1)*2+12;
        for (int k = 12;k < lengthOfCompress;k++) {
            temp[k] = (byte) in.read();
        }

        System.arraycopy(temp, 0, bytes, 0, 12);


        int j;
        lengthOfCompress = ((numOfCells/15))*2+12;
        for ( j =12;j < lengthOfCompress;j+=2){
            number = ((temp[j]&0xff)*255) + (temp[j+1]&0xff);
            BinaryNum = IntToBinary(number);
            for (int i=0;i<15;i++){
                bytes[index] = BinaryNum[i];
                index++;
            }
        }
        // enter the last part of the maze - because not sure if num of cell is divided by 13.
        int lastOfMaze = numOfCells-(numOfCells/15)*15;
        int BinaryNumber = (temp[lengthOfCompress]&0xff)*255 + (temp[lengthOfCompress+1]&0xff);
        BinaryNum = IntToBinary(BinaryNumber);
        for (int i=15-lastOfMaze;i<15;i++)
        {
            bytes[index]=BinaryNum[i];
            index++;
        }

        return 0;
    }

    @Override
    public int read() throws IOException {
        return 0;
    }
}
