package com.strutnut.webcloader;

import com.strutnut.annotation.ObjectClass;
import com.strutnut.annotation.ObjectMethod;
import com.strutnut.bean.ObjectClazz;
import com.strutnut.utils.ByteUtil;
import com.strutnut.utils.RC4Util;

import java.io.*;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;


public class ClassPathDetector {

    private static final String GROUP_ID = "com.strutnut";

    public static ClassPathDetector classPathDetector = new ClassPathDetector();

    private ClassPathDetector() {
    }

    public static ClassPathDetector getInstance() {
        return classPathDetector;
    }

    /**
     * 获得全类名
     *
     * @return 全类名
     */
    private String searchClassPath() {

        if (this.classPath != null) {
            return this.classPath;
        }

        String replace = "/" + GROUP_ID.replace(".", "/");
        String projectPath = this.getClass().getResource(replace).getPath();
        searchClassPath(projectPath);
        if (this.classPath != null) {
            return this.classPath;
        } else {
            throw new RuntimeException("ERROR: Not Found.");
        }
    }

    /**
     * 密匙
     */
    private static final String KEY = "AllMyLife";


    /**
     * 构造实体类ObjectClazz
     *
     * @return ObjectClazz
     */
    public ObjectClazz buildClazz() {

        System.out.println("INFO: Clazz Building Starts ...");

        ObjectClazz objectClazz = null;

        String classPath = searchClassPath();

//        获得字节码路径
        String projectPath = this.getClass().getResource("/").getPath();

        String classFilePath = projectPath + classPath.replace(".", "/") + ".class";
//        读文件
        File file = new File(classFilePath);
        if (!file.exists()) {
            throw new RuntimeException("ERROR: File Doesn't Exist.");
        }
        byte[] classContent = null;
//        发送数据包
        try (BufferedInputStream bufferedFileInputStream = new BufferedInputStream(new FileInputStream(file))
        ) {
            byte[] bufferedBytes = new byte[1024];
            int len;
            while ((len = bufferedFileInputStream.read(bufferedBytes)) != -1) {
//                加密
                bufferedBytes = Arrays.copyOf(bufferedBytes, len);
                byte[] afterBytes = RC4Util.decry(bufferedBytes, KEY);
                classContent = ByteUtil.mergeBytes(classContent, afterBytes);
            }
//            生成实体类并填充
            objectClazz = new ObjectClazz();
            objectClazz.setClassContent(classContent);
            objectClazz.setMethodNames(this.methodNames);
            System.out.println("INFO: Successfully Build .");
            return objectClazz;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return objectClazz;
    }

    /**
     * 全类名路径
     */
    private String classPath;

    /**
     *  方法名数组
     */
    private List<String> methodNames = new ArrayList<>();


    /**
     * 扫描项目文件夹，获取含有 @ObjectClass 和 @ObjectMethod 注解的【单个】类及其方法之全类名
     *
     * @param path 项目所有文件夹
     */
    private void searchClassPath(String path) {

        File targetProjectDir = new File(path);
        File[] targetProjectPathFiles = targetProjectDir.listFiles();
        for (File file : targetProjectPathFiles) {
//            如果是文件夹则递归查找
            if (file.isDirectory()) {
                searchClassPath(file.getPath());
                continue;
            }
//            获取全类名
            String projectPathPrefix = this.getClass().getResource("/").getPath().replace("/", "\\");
            String tempCurrentFilePath = "\\" + file.getPath();
            String classPath = tempCurrentFilePath.replace(projectPathPrefix, "").replace("\\", ".").replace(".class", "");
            try {
                Class<?> clazz = Class.forName(classPath);
//                含有此注解否
                if (clazz.isAnnotationPresent(ObjectClass.class)) {
                    Method[] methods = clazz.getMethods();
                    for (Method method : methods) {
//                        它的方法含有此注解否
                        if (method.isAnnotationPresent(ObjectMethod.class)) {
                            this.classPath = clazz.getName();
                            this.methodNames.add(method.getName());
                        }
                    }
                    this.classPath = clazz.getName();
                }
            } catch (ClassNotFoundException e) {
                e.printStackTrace();

            }
        }
    }
}
