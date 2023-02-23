package Server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;

public class Server {
    private int port;
    private int listeningIntervalMS;
    private IServerStrategy strategy;
    private volatile boolean stop;


    private ThreadPoolExecutor executor;


    public Server(int port, int listeningIntervalMS, IServerStrategy strategy) throws IOException {
        this.port = port;
        this.listeningIntervalMS = listeningIntervalMS;
        this.strategy = strategy;
        stop = false;

    }

    public void start(){

        new Thread(this::startNow).start();
    }

    public void startNow() {
        try {
            Configurations config = Configurations.getInstance();
            ServerSocket serverSocket = new ServerSocket(port);
            serverSocket.setSoTimeout(listeningIntervalMS);

            executor = (ThreadPoolExecutor) Executors.newFixedThreadPool(Configurations.getInstance().getThreadPoolSize());
            while (!stop){
                try {
                    Socket clientSocket = serverSocket.accept();
                    executor.execute(()-> {
                        try {
                            handleClient(clientSocket);
                        } catch (IOException e) {
                            throw new RuntimeException(e);
                        }
                    });
                }catch (SocketTimeoutException e){
                    //e.printStackTrace();
                    //System.out.println("no client request..");
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    private Runnable handleClient(Socket clientSocket) throws IOException {
        try {

            strategy.applyStrategy(clientSocket.getInputStream(),clientSocket.getOutputStream());
            clientSocket.close();
        }catch (IOException e){
            e.printStackTrace();
        }

        return null;
    }
    public void stop(){
        stop = true;
        executor.shutdown();
    }
}
