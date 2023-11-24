package com.strutnut.webcloader;


import com.strutnut.bean.ObjectClazz;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * 1.设计一个基于socket或者RMI的服务器，可以将字节码文件（class文件）加密后发送出去。加密方法可采用教材例子3.1中的异或加密。
 * 2.设计一个接口displayable，包名任意，接口中定义方法display。
 * 3.设计一个类x去实现displayable接口，在display中任意输出一段话到控制台。将该类的字节码部署到服务器。
 * 4.设计一个可以通过网络获取字节码并解密的类加载器。
 * 5.设计一个客户端程序，使用网络类加载器，从服务器获取类x的字节码，通过接口回调，调用display方法。
 */


public class WebClassEncryptorServer {

    /**
     * 服务器端口
     */
    private static final int SERVER_PORT = 8080;


    /**
     * 处理客户端请求
     */
    public void doResponse() {

        while (true) {
            try (ServerSocket serverSocket = new ServerSocket(SERVER_PORT)) {
                serverSocket.setReuseAddress(true);
                System.out.println("INFO: Waiting ...");
                Socket clientSocket = serverSocket.accept();
                ExecutorService executorService = Executors.newCachedThreadPool();
                System.out.println("INFO: Sending ...");
                executorService.submit(() -> doSend(clientSocket));
                //doSend(clientSocket);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 发送数据包
     *
     * @param clientSocket socket
     */
    private void doSend(Socket clientSocket) {

        ObjectClazz objectClazz = ClassPathDetector.getInstance().buildClazz();
        try (ObjectOutputStream objectSocketOutputStream = new ObjectOutputStream(clientSocket.getOutputStream())) {
            objectSocketOutputStream.writeObject(objectClazz);
            objectSocketOutputStream.flush();
            System.out.println("INFO: Send OK.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


}

