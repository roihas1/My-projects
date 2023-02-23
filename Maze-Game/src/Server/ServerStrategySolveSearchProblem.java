package Server;

import algorithms.mazeGenerators.Maze;
import algorithms.search.*;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.util.Arrays;
import java.util.Objects;

public class ServerStrategySolveSearchProblem implements IServerStrategy{
    /**
     * The function gets a maze, checks if there have been a check for this maze in the past.
     * if we didn't find a solution from the past - make a new solution - by type of solution chosen in configuration
     * if we founded a solution from the past, return it.
     * @param mazeFromClient - get the current maze to solve
     * @param outToClient - solution for the current maze we check.
     */
    @Override
    public void applyStrategy(InputStream mazeFromClient, OutputStream outToClient) {

        try {
            ObjectInputStream fromClient = new ObjectInputStream(mazeFromClient);
            ObjectOutputStream toClient = new ObjectOutputStream(outToClient);

            Maze maze = (Maze) fromClient.readObject();
            byte [] mazeByteArray = maze.toByteArray();
            int sizeOfMaze = maze.getGrid().length*maze.getGrid()[0].length+12;

            String tempDirectoryPath = System.getProperty("java.io.tmpdir");
            File directory = new File(tempDirectoryPath);
            String fileName;
            boolean flag = false;
            byte [] FileBytes;

            // go over the files in the temporary file. if its a maze - compare to see if already solved
            for (File file : Objects.requireNonNull(directory.listFiles())) {
                fileName = file.getName();
               if(fileName.startsWith("Maze"))
               {
                   FileBytes = Files.readAllBytes(Path.of(file.getPath()));
                    if (CompareBytes(mazeByteArray,FileBytes,sizeOfMaze)){
                        flag = true;
                        byte[] SolutionBytesArr = Arrays.copyOfRange(FileBytes, sizeOfMaze, FileBytes.length);
                        Solution solutionMaze = new Solution(SolutionBytesArr);
                        toClient.writeObject(solutionMaze);

                        break;
                    }
               }
            }

            if (!flag) {
                SearchableMaze searchableMaze = new SearchableMaze(maze);
                ISearchingAlgorithm searchingAlgorithm = checkTypeSolution(Configurations.getInstance().getMazeSearchingAlgorithm());
                Solution solutionMaze = searchingAlgorithm.solve(searchableMaze);
                toClient.writeObject(solutionMaze);
                File newFile = File.createTempFile("Maze", null, new File(tempDirectoryPath));
                Files.write(Path.of(newFile.getPath()), mazeByteArray);
                Files.write(Path.of(newFile.getPath()), solutionMaze.toByteArray(), StandardOpenOption.APPEND);

            }
        toClient.flush();

        }catch (IOException e){
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * compare the maze to a maze that was solved in the past
     * @param maze - current maze to solve
     * @param file - previous maze that have been already solved
     * @param sizeOfMaze - the size of the maze (including his details - start,goal,num of row&col)
     * @return true- if the previous maze is similar to current. false - if not.
     */
    private boolean CompareBytes(byte [] maze,byte [] file,int sizeOfMaze)
    {
        for (int i=0;i<sizeOfMaze;i++)
        {
            if (maze[i]!=file[i])
                return false;
        }
        return true;
    }

    /**
     * choose which object type solution will be given
     * @param name - get the type of Solution for the maze - by configuration file
     * @return an object of the solution type
     */
    private ISearchingAlgorithm checkTypeSolution (String name)
    {
        if (name.equals("Best First Search")) {
            return new BestFirstSearch();}
        if (name.equals("Depth First Search")) {
            return new DepthFirstSearch();
        } else
            return new BreadthFirstSearch();
    }
}
