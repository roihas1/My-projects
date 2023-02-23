package IO;

import java.io.IOException;
import java.io.OutputStream;

public class MyCompressorOutputStream extends OutputStream {
    OutputStream out;

    public MyCompressorOutputStream(OutputStream out) {

        this.out = out;
    }

    /**
     * Taking every 15 digits from the maze that represent a binary number and convert it to a pair of numbers that equals to
     * the decimal number.The first number is how many times the number divide in 255 and the second is reminder.
     * @param b   the data.
     * @throws IOException
     */
    @Override
    public void write(byte[] b) throws IOException {
        //super.write(b);
        int numOfCells = (((b[0]&0xff)*255+(b[1]&0xff)) * ((b[2]&0xff)*255+(b[3]&0xff)));
        int lengthOfCompress = ((numOfCells/15)+1)*2+12;
        byte[] compressByte = new byte[lengthOfCompress];

        System.arraycopy(b, 0, compressByte, 0, 12);
      /*  for (int i = 0 ; i < 12 ; i++){
            compressByte[i] = b[i];
        }*/

        int index =12;
        int startMazeindex = 12;
        while(startMazeindex < b.length) {
            int power = 0; // the power for 2 in calculation
            int sum = 0; // 15 digits by binary in INT the max number we can represent with byte
            int delta = 15;
            if (startMazeindex + 14 > b.length-1) {
                delta = b.length - startMazeindex;
            }

            for (int i = startMazeindex+delta-1;i >=startMazeindex; i--){
                if (b[i]==1)
                    sum += Math.pow(2,power);
                power++;
            }
            startMazeindex += delta;
            // to convert INT to byte representation
            compressByte[index] =(byte)(sum/255);
            index++;
            compressByte[index] = (byte)(sum%255);
            index ++;
        }



        out.write(compressByte);

    }


    @Override
    public void write(int b) throws IOException {

    }
}
