package IO;

import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;


public class SimpleCompressorOutputStream extends OutputStream {
    protected OutputStream out;


    public SimpleCompressorOutputStream(OutputStream out) {
        this.out = out;
    }

    @Override
    public void write(byte[] b) throws IOException {
        //super.write(b);
        ArrayList<Byte> ACounter = new ArrayList<>();
        for (int i=0;i<12;i++){
            out.write(b[i]);

        }

        int index = 12;
        int zeroOrOne = 0;
        while(index < b.length) {

            int save = SequenceCounter(b, index,zeroOrOne);
            for (int i=0;i<save/255;i++)//change to 255
            {
                out.write(255);
                out.write(0);

            }
            out.write(save%255);

            if (zeroOrOne==0)
                zeroOrOne++;
            else
                zeroOrOne--;
            index += save;

        }




    }


    public int SequenceCounter (byte[] b, int index, int zeroOrOne)
    {
        int counter = 0;
        while (index < b.length && b[index] == zeroOrOne )
        {
            index++;
            counter++;
        }
        return counter;
    }



    @Override
    public void write(int b) throws IOException {

    }
}
