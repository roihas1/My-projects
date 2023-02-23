package test;

import Client.Client;
import Client.IClientStrategy;
import IO.MyDecompressorInputStream;
import Server.Server;
import Server.ServerStrategyGenerateMaze;
import Server.ServerStrategySolveSearchProblem;
import algorithms.mazeGenerators.Maze;
import algorithms.mazeGenerators.MyMazeGenerator;
import algorithms.search.AState;
import algorithms.search.Solution;

import java.io.*;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.ArrayList;

public class RunCommunicateWithServers {

    public static void main(String[] args) throws IOException {
//Initializing servers
        Server mazeGeneratingServer = new Server(5400, 1000, new ServerStrategyGenerateMaze());
        Server solveSearchProblemServer = new Server(5401, 1000, new ServerStrategySolveSearchProblem());
        //Server stringReverserServer = new Server(5402, 1000, new ServerStrategyStringReverser());
        int x = -128;
        byte [] ne = new byte[1];
        ne[0] = (byte) (x);
       //System.out.println(ne[0]&fx00);
       // System.out.println(f.getName());

        //Starting servers
        //solveSearchProblemServer.start();
        mazeGeneratingServer.start();

        CommunicateWithServer_MazeGenerating();
        //CommunicateWithServer_SolveSearchProblem();

        mazeGeneratingServer.stop();
       // solveSearchProblemServer.stop();

    }

    private static void CommunicateWithServer_MazeGenerating() throws UnknownHostException {
        try {
            Client client1 = new Client(InetAddress.getLocalHost(), 5400, new IClientStrategy() {
                @Override
                public void clientStrategy(InputStream inFromServer, OutputStream outToServer) {

                    try {
                        ObjectOutputStream toServer = new ObjectOutputStream(outToServer);
                        ObjectInputStream fromServer = new ObjectInputStream(inFromServer);
                        toServer.flush();
                        int[] mazeDimensions = new int[]{1000, 100};
                        toServer.writeObject(mazeDimensions); //send maze dimensions to server
                        toServer.flush();
                        byte[] compressedMaze = (byte[]) fromServer.readObject(); //read generated maze (compressed with MyCompressor) from server
                        InputStream is = new MyDecompressorInputStream(new ByteArrayInputStream(compressedMaze));
                        byte[] decompressedMaze = new byte[100012/*CHANGE sIZE ACCORDING TO YOU MAZE SIZE*/];
                        //allocating byte[] for the decompressed
                        is.read(decompressedMaze); //Fill decompressedMaze

                        Maze maze = new Maze(decompressedMaze);


                        //maze.print();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            });

            Client client = new Client(InetAddress.getLocalHost(), 5400, new IClientStrategy() {
                @Override
                public void clientStrategy(InputStream inFromServer, OutputStream outToServer) {

                    try {
                        ObjectOutputStream toServer = new ObjectOutputStream(outToServer);
                        ObjectInputStream fromServer = new ObjectInputStream(inFromServer);
                        toServer.flush();
                        int[] mazeDimensions = new int[]{1000, 1000};
                        toServer.writeObject(mazeDimensions); //send maze dimensions to server
                        toServer.flush();
                        byte[] compressedMaze = (byte[]) fromServer.readObject(); //read generated maze (compressed with MyCompressor) from server
                        InputStream is = new MyDecompressorInputStream(new ByteArrayInputStream(compressedMaze));
                        byte[] decompressedMaze = new byte[1000012/*CHANGE sIZE ACCORDING TO YOU MAZE SIZE*/];
                        //allocating byte[] for the decompressed
                        is.read(decompressedMaze); //Fill decompressedMaze

                        Maze maze = new Maze(decompressedMaze);
                       // maze.print();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }

                }

            });
           // client.communicateWithServer();
            client1.communicateWithServer();
        } catch(UnknownHostException e){
                e.printStackTrace();
            }
        }
    private static void CommunicateWithServer_SolveSearchProblem() {
        try {
            Client client = new Client(InetAddress.getLocalHost(), 5401, new IClientStrategy() {
                        @Override
                        public void clientStrategy(InputStream inFromServer,
                                                   OutputStream outToServer) {
                            try {
                                ObjectOutputStream toServer = new ObjectOutputStream(outToServer);
                                ObjectInputStream fromServer = new ObjectInputStream(inFromServer);
                                toServer.flush();
                                MyMazeGenerator mg = new MyMazeGenerator();
                                Maze maze = mg.generate(300, 300);
                                //maze.print();
                                toServer.writeObject(maze); //send maze to server
                                toServer.flush();
                                Solution mazeSolution = (Solution)fromServer.readObject();
                                //read generated maze (compressed with MyCompressor) from server
                                //Print Maze Solution retrieved from the server
                                System.out.println(String.format("Solution steps: %s", mazeSolution));
                                ArrayList<AState> mazeSolutionSteps = mazeSolution.getSolutionPath();
                                /*for (int i = 0; i < mazeSolutionSteps.size(); i++) {
                                    System.out.println(String.format("%s. %s", i,mazeSolutionSteps.get(i).toString()));
                                }*/
                            } catch (Exception e) {
                                e.printStackTrace();
                            }
                        }
                    });
            client.communicateWithServer();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
    }




}

