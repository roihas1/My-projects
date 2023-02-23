package Client;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;

public class Client implements IClientStrategy  {
    private InetAddress serverIP;
    private int port;
    private IClientStrategy clientStrategy;

    public Client(InetAddress serverIP, int port, IClientStrategy clientStrategy) {
        this.serverIP = serverIP;
        this.port = port;
        this.clientStrategy = clientStrategy;
    }
    public void communicateWithServer(){
        try(Socket serverSocket = new Socket(serverIP, port)){
            clientStrategy.clientStrategy(serverSocket.getInputStream(), serverSocket.getOutputStream());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    @Override
    public void clientStrategy(InputStream inFromServer,OutputStream outToServer) {
    }
}
