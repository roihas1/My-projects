package test;

import IO.*;
import algorithms.mazeGenerators.AMazeGenerator;
import algorithms.mazeGenerators.Maze;
import algorithms.mazeGenerators.MyMazeGenerator;

import java.io.*;
import java.util.Arrays;

public class RunCompressDecompressMaze {
    public static void main(String[] args) {


        int countFalse = 0;
        int countTrue = 0;
        for (int i = 0; i < 10; i++) {

            String mazeFileName = "savedMaze.maze";
            AMazeGenerator mazeGenerator = new MyMazeGenerator();
            Maze maze = mazeGenerator.generate(1200, 1000); //Generate new maze


            //

            byte savedMazeBytes[] = new byte[0];
            byte []savedMazeBytes2;
            try {
// save maze to a file
                OutputStream out = new SimpleCompressorOutputStream(new FileOutputStream(mazeFileName));

                //System.out.println(Arrays.toString(maze.toByteArray()));

                savedMazeBytes = new byte[maze.toByteArray().length];
                savedMazeBytes = maze.toByteArray();
                out.write(savedMazeBytes);


                out.flush();
                out.close();

            } catch (IOException e) {
                e.printStackTrace();
            }

            try {
//read maze from file
                InputStream in = new SimpleDecompressorInputStream(new FileInputStream(mazeFileName));
                savedMazeBytes2 = new byte[maze.toByteArray().length];
                in.read(savedMazeBytes2);
                //System.out.println(Arrays.toString(savedMazeBytes));
                System.out.println(Arrays.equals(savedMazeBytes,maze.toByteArray()));
                in.close();

            } catch (IOException e) {
                e.printStackTrace();
            }
            Maze loadedMaze = new Maze(savedMazeBytes);
            //System.out.println(Arrays.toString(maze.toByteArray()));
            //System.out.println(Arrays.toString(loadedMaze.toByteArray()));
            boolean areMazesEquals = Arrays.equals(loadedMaze.toByteArray(), maze.toByteArray());
            byte[] loaded = loadedMaze.toByteArray();
            byte[] mazetest = maze.toByteArray();
            if (areMazesEquals)
                countTrue++;
            else {
                countFalse++;
                for (int k = 0 ; k< 12;k++){
                    System.out.println(loaded[k]);
                }
                for (int j = 0; j < loadedMaze.toByteArray().length; j++) {

                    if (loaded[j] != mazetest[j]) {
                        System.out.println(j);
                        System.out.println("the real:" + mazetest[j] + " the decompress: " + loaded[j]);

                    }

                    //System.out.println(String.format("Mazes equal: %s",areMazesEquals));
//maze should be equal to loadedMaze
                }
            }


            System.out.println("True:" + countTrue + " False : " + countFalse);
        }


    }
}