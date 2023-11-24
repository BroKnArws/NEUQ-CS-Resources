package com.webcloader;


import com.strutnut.bean.ObjectClazz;
import com.strutnut.webcloader.ClassPathDetector;
import com.strutnut.utils.RC4Util;
import com.strutnut.webcloader.tar.DisplayableImpl;
import org.junit.Test;


import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Arrays;


public class ClientTest {

    public static final int OBJECT_PORT = 8080;
    public static final String IP_ADDRESS = "127.0.0.1";

    @Test
    public void getClazzPath() {
        String clazzName = "DisplayableImpl";
        String absolutePath = new File("./src").getAbsolutePath();
        System.out.println(absolutePath);
        File[] files = new File(absolutePath).listFiles();
        System.out.println(Arrays.toString(files));
    }


    @Test
    public void makeClazzFile() {
        File file = new File("./temp.class");
        try (Socket clientSocket = new Socket(IP_ADDRESS, OBJECT_PORT)) {
            BufferedInputStream bufferedInputStream = new BufferedInputStream(clientSocket.getInputStream());
            BufferedOutputStream bufferedOutputStream = new BufferedOutputStream(new FileOutputStream(file));
            byte[] bytes = new byte[1024];
            int len;
            while ((len = bufferedInputStream.read(bytes)) != -1) {
                byte[] bytes1 = RC4Util.decry(bytes, "AllMyLife");
                bufferedOutputStream.write(bytes1, 0, len);
            }
            bufferedOutputStream.flush();
            bufferedOutputStream.close();
            bufferedInputStream.close();


        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private static final String CLASSPATH = "com.strutnut.webcloader.tar.DisplayableImpl";

    @Test
    public void test01() throws IOException {
        String canonicalPath = new File("").getCanonicalPath();
        System.out.println(canonicalPath);
        String absolutePath = new File("").getAbsolutePath();
        System.out.println(absolutePath);
        System.out.println(this.getClass().getResource("/").getPath());
        String path = DisplayableImpl.class.getResource("/").getPath();
        System.out.println(path);
        System.out.println(CLASSPATH.replace(".", "/") + ".class");
    }

    private static final String path = "com.strutnut";

    @Test
    public void test02() throws IOException {
        ObjectClazz objectClazz = ClassPathDetector.getInstance().buildClazz();
        System.out.println(objectClazz.getMethodNames());

    }


}
