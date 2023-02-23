package test;

import algorithms.mazeGenerators.IMazeGenerator;
import algorithms.mazeGenerators.Maze;
import algorithms.mazeGenerators.MyMazeGenerator;
import algorithms.mazeGenerators.SimpleMazeGenerator;
import algorithms.search.*;
import jdk.jfr.Unsigned;

import java.util.ArrayList;

public class RunSearchOnMaze {
        public static void main(String[] args) {
            byte[]b = new byte[10];
            int row = 300;
            byte b1 = (byte)(row/127);
            byte b2 = (byte) (row%127);
            System.out.println(b1);
            System.out.println(b2);
            b[0] = (byte) 700;
            System.out.println(Byte.toUnsignedLong(b[0]));
            IMazeGenerator mg = new MyMazeGenerator();
            Maze maze = mg.generate(-1000,-1000);
            IMazeGenerator m  = new SimpleMazeGenerator();
            Maze ma = m.generate(10,10);
            //maze.print();
            //ma.print();
            SearchableMaze searchableMaze1 = new SearchableMaze(ma);
            SearchableMaze searchableMaze = new SearchableMaze(maze);
            //solveProblem(searchableMaze1 , new BestFirstSearch());
            //solveProblem(searchableMaze1 ,  new BreadthFirstSearch());
            int count = 0;
            int count2 = 0;
            /*for (int i = 0; i < 10 ; i ++) {
                maze = mg.generate(-1000,-1000);
                searchableMaze = new SearchableMaze(maze);
                ISearchingAlgorithm bfs = new BreadthFirstSearch();
                ISearchingAlgorithm dfs = new DepthFirstSearch();
                ISearchingAlgorithm best = new BestFirstSearch();
                solveProblem(searchableMaze, bfs);
                solveProblem(searchableMaze, dfs);
                solveProblem(searchableMaze, best);

                if (bfs.getNumberOfNodesEvaluated() > best.getNumberOfNodesEvaluated())
                    count+=1;
                else if (bfs.getNumberOfNodesEvaluated() < best.getNumberOfNodesEvaluated()) {
                    count2+=1;
                }
                System.out.println("__________________________");

            }
            System.out.printf("bfs bigger %s times.\n",count);
            System.out.printf("best bigger %s times.\n", count2);
*/
/*
                for (int i = 0; i < 10 ; i ++) {
                maze = m.generate(1000,1000);
                searchableMaze = new SearchableMaze(maze);
                //System.out.println(searchableMaze.getAllPossibleStates(searchableMaze.getStart()));
                int t1 = (int) System.currentTimeMillis();
                solveProblem(searchableMaze, new BreadthFirstSearch());
                int t2 = (int) System.currentTimeMillis();
                System.out.println("BFS time : " + (t2 - t1));
                solveProblem(searchableMaze, new DepthFirstSearch());
                t1 = (int) System.currentTimeMillis();
                solveProblem(searchableMaze, new BestFirstSearch());
                t2 = (int) System.currentTimeMillis();
                System.out.println("Best time : " + (t2 - t1));
                System.out.println("__________________________");
            }
*/
        }
        private static void solveProblem(ISearchable domain, ISearchingAlgorithm searcher) {
//Solve a searching problem with a searcher
            Solution solution = searcher.solve(domain);
            System.out.printf("'%s' algorithm - nodes evaluated:%d%n", searcher.getName(), searcher.getNumberOfNodesEvaluated());
//Printing Solution Path
            System.out.println("Solution path:" + solution.getSolutionPath().size());
            int sum =1;
            ArrayList<AState> solutionPath = solution.getSolutionPath();
            /*for (AState aState : solutionPath) {
                 System.out.printf("%d.%s%n",sum,aState);
                sum += 1;
            }*/
            //System.out.printf("%s total cost : %d%n",searcher.getName(),sum);
        }
    }


