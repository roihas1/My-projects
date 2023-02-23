package Server;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class Configurations {

    int threadPoolSize;
    String mazeGeneratingAlgorithm;
    String mazeSearchingAlgorithm;
    private final String FilePath = "config.properties";

    public static Configurations instance;

   /* private Configurations(int threadPoolSize, String mazeGeneratingAlgorithm, String mazeSearchingAlgorithm) {
        this.threadPoolSize = threadPoolSize;
        this.mazeGeneratingAlgorithm = mazeGeneratingAlgorithm;
        this.mazeSearchingAlgorithm = mazeSearchingAlgorithm;
    }*/
    private Configurations() throws IOException {
        Properties properties = new Properties();
        InputStream inputStream = getClass().getClassLoader().getResourceAsStream(FilePath);
        if (inputStream != null)
            properties.load(inputStream);

        threadPoolSize = Integer.parseInt(properties.getProperty("threadPoolSize"));
        mazeGeneratingAlgorithm = properties.getProperty("mazeGeneratingAlgorithm");
        mazeSearchingAlgorithm = properties.getProperty("mazeSearchingAlgorithm");

    }


public static Configurations getInstance() throws IOException {
        if (instance == null)
            instance = new Configurations();
        return instance;
}



    public int getThreadPoolSize() {
        return threadPoolSize;
    }

    public String getMazeGeneratingAlgorithm() {
        return mazeGeneratingAlgorithm;
    }

    public String getMazeSearchingAlgorithm() {
        return mazeSearchingAlgorithm;
    }

    public void setThreadPoolSize(int threadPoolSize) {
        this.threadPoolSize = threadPoolSize;
    }

    public void setMazeGeneratingAlgorithm(String mazeGeneratingAlgorithm) {
        this.mazeGeneratingAlgorithm = mazeGeneratingAlgorithm;
    }

    public void setMazeSearchingAlgorithm(String mazeSearchingAlgorithm) {
        this.mazeSearchingAlgorithm = mazeSearchingAlgorithm;
    }
}
