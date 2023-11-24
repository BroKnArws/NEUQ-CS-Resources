package com.strutnut.utils;

/**
 * RC4 加/解密算法
 */
public class RC4Util {

    public static byte[] decry(byte[] data, String key) {
        if (data == null || key == null) {
            return null;
        }
        return RC4(data, key);
    }

    /**
     * 对字节数组进行加密
     * @param data
     * @param keyWithoutInited
     * @return
     */
    private static byte[] RC4(byte[] data, String keyWithoutInited) {
        int x = 0;
        int y = 0;
        byte[] initedKey = initKey(keyWithoutInited);
        int xorIndex;
        byte[] result = new byte[data.length];

        for (int i = 0; i < data.length; i++) {
            x = (x + 1) & 0xff;
            assert initedKey != null;
            y = ((initedKey[x] & 0xff) + y) & 0xff;
            byte tmp = initedKey[x];
            initedKey[x] = initedKey[y];
            initedKey[y] = tmp;
            xorIndex = ((initedKey[x] & 0xff) + (initedKey[y] & 0xff)) & 0xff;
            result[i] = (byte) (data[i] ^ initedKey[xorIndex]);
        }
        return result;
    }

    private static final int LENGTH = 256;

    /**
     * 根据key创建向量并交换元素
     * @param stringKey
     * @return
     */
    private static byte[] initKey(String stringKey) {
        byte[] bytesKey = stringKey.getBytes();
        byte[] state = new byte[LENGTH];

        for (int i = 0; i < LENGTH; i++) {
            state[i] = (byte) i;
        }
        int firstIndex = 0;
        int secondIndex = 0;
        if (bytesKey.length == 0) {
            return null;
        }
        for (int i = 0; i < LENGTH; i++) {
            secondIndex = ((bytesKey[firstIndex] & 0xff) + (state[i] & 0xff) + secondIndex) & 0xff;
            byte temp = state[i];
            state[i] = state[secondIndex];
            state[secondIndex] = temp;
            firstIndex = (firstIndex + 1) % bytesKey.length;
        }
        return state;
    }
}