package Server;

import IO.MyCompressorOutputStream;
import algorithms.mazeGenerators.*;

import java.io.*;

public class ServerStrategyGenerateMaze implements IServerStrategy{

    /**
     * getting int[] from client which represent the size of th maze to generate.
     * return to client a compressed maze.
     * @param inFromClient - the input stream from the client
     * @param outToClient - the output stream from server in this case a compressed maze
     */
    @Override
    public void applyStrategy(InputStream inFromClient, OutputStream outToClient) {
        try {
            ObjectInputStream fromClient = new ObjectInputStream(inFromClient);
            ObjectOutputStream toClient = new ObjectOutputStream(outToClient);

            int[] mazeSize =(int[]) fromClient.readObject();
            AMazeGenerator mazeGenerator = checkTypeGenerator (Configurations.getInstance().getMazeGeneratingAlgorithm());
            Maze maze = mazeGenerator.generate(mazeSize[0], mazeSize[1]);


            ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
            OutputStream out = new MyCompressorOutputStream(byteArrayOutputStream); //call constructor - set the output

            byte [] MazeToByteArray = maze.toByteArray();
            out.write(MazeToByteArray);

            toClient.writeObject(byteArrayOutputStream.toByteArray());
            toClient.flush();

        } catch (IOException e){
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * check the type of maze the client want to generate.
     * @param name - The type of  generator - simple\empty\My - by configuration file
     * @return - an object of Amaze generator
     */
    private AMazeGenerator checkTypeGenerator(String name)
    {
        if (name.equals("My Maze Generator")){
            return new MyMazeGenerator();}
        else if (name.equals("Simple Maze Generator")){
            return new SimpleMazeGenerator();}
        else{
            return new EmptyMazeGenerator();}
    }
}
