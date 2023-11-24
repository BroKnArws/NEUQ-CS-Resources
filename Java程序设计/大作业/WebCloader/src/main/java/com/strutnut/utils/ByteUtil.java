package com.strutnut.utils;

public class ByteUtil {


    /**
     * 合并字节数组
     *
     * @param firstBytes  数组A
     * @param secondBytes 数组B
     * @return 合并后的数组
     */
    public static byte[] mergeBytes(byte[] firstBytes, byte[] secondBytes) {
        if (secondBytes == null) {
            return firstBytes;
        }
        if (firstBytes != null) {
            byte[] tempBytes = new byte[firstBytes.length + secondBytes.length];
            System.arraycopy(firstBytes, 0, tempBytes, 0, firstBytes.length);
            System.arraycopy(secondBytes, 0, tempBytes, firstBytes.length, secondBytes.length);
            return tempBytes;
        }
        byte[] tempBytes = new byte[secondBytes.length];
        System.arraycopy(secondBytes, 0, tempBytes, 0, secondBytes.length);
        return tempBytes;

    }
}
