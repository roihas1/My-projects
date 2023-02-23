package IO;

import java.io.IOException;
import java.io.InputStream;

public class SimpleDecompressorInputStream extends InputStream {
 InputStream in;

    public SimpleDecompressorInputStream(InputStream in) {
        this.in = in;
    }


    @Override
    public int read() throws IOException {
        return 0;
    }

    @Override
    public int read(byte[] bytes) throws IOException {

        for (int i=0;i<12;i++){
            bytes[i] = (byte) in.read();
        }
        int index = 12;
        int zeroOrOne=0;
        int numOfCells = ((bytes[0]&0xff)*255 + (bytes[1]&0xff))  *  ((bytes[2]&0xff)*255 + (bytes[3]&0xff));

        for (int j = 12; index < numOfCells+12;j++){
            int sequenceCount = in.read()&0xff ;
            for (int i = 0; i < sequenceCount; i++){  //convert the negative to INTEGER
                bytes[index] = (byte) zeroOrOne;
                index++;
            }
            if (zeroOrOne == 0)
                zeroOrOne++;
            else
                zeroOrOne--;
        }


        return 0;
    }
}