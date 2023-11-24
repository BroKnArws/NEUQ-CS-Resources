package com.strutnut.webcloader;

import com.strutnut.utils.RC4Util;


public class WebClassLoader extends ClassLoader {

    /**
     * 生成类对象
     * @param classContent 字节码数组（加密后的）
     * @return 类对象
     */
    public Class<?> defineClass(byte[] classContent) {
        byte[] decryptedClassContent = decrypt(classContent);
        return this.defineClass(null, decryptedClassContent, 0, decryptedClassContent.length);

    }

    /**
     * 密匙
     */
    private static final String KEY = "AllMyLife";

    /**
     * 解密字节码
     * @param classContent 加密过的字节码数组
     * @return 解密后的字节码数组
     */
    private byte[] decrypt(byte[] classContent) {
        return RC4Util.decry(classContent, KEY);
    }

}
