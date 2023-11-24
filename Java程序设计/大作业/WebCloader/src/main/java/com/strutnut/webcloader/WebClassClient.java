package com.strutnut.webcloader;

import com.strutnut.bean.ObjectClazz;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.Socket;
import java.util.Scanner;


/**
 * 客户端
 */
public class WebClassClient {

    /**
     * 请求端口
     */
    public static final int OBJECT_PORT = 8080;

    /**
     * IP地址
     */
    public static final String IP_ADDRESS = "127.0.0.1";

    /**
     * 客户端做请求
     */
    public void doRequest() {

        System.out.println("INFO: Request Started...");
        do {
            try (Socket clientSocket = new Socket(IP_ADDRESS, OBJECT_PORT)) {

                System.out.println("INFO: GET Response.");
                ObjectInputStream objectSocketInputStream = new ObjectInputStream(clientSocket.getInputStream());
                System.out.println("INFO: Analysing The Class File..");
//                通过socket流获取服务端传来的objectClazz
                ObjectClazz objectClazz = (ObjectClazz) objectSocketInputStream.readObject();
                System.out.println("INFO: Analysis OK.");
                this.invokeMethod(objectClazz);
                System.out.println("Try again?[y/n]");
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
//            可重新体验~
        } while ("y".equals(new Scanner(System.in).next()));

    }

    private void invokeMethod(ObjectClazz objectClazz) {
        try {
            //                类加载器将字节码数组转化为类对象
            WebClassLoader webClassLoader = new WebClassLoader();
            Class<?> objectClass = webClassLoader.defineClass(objectClazz.getClassContent());
            System.out.println("INFO: Invoking Methods.");
//                调用该类含有@ObjectMethod注解的所有方法
            Method[] methods = objectClass.getMethods();
            for (String methodName : objectClazz.getMethodNames()) {
                for (Method method : methods) {
                    if (methodName.equals(method.getName())) {
                        method.invoke(objectClass.getConstructor().newInstance());
                    }
                }
            }
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        }
    }

}
