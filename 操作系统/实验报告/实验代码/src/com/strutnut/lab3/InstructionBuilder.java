package com.strutnut.lab3;

import java.util.Random;

public class InstructionBuilder {

    private static int rightBound;

    public static int[][] build(int pageNum, int size) {
        rightBound = pageNum * size;
        int[][] pages = new int[pageNum][size];
        randomBulid(pages);
        //mapPages(pages);
        return pages;
    }

    private static void randomBulid(int[][] instructions) {
        Random random = new Random();
        int status = 0;
        int m, m1, m2;
        m = m1 = m2 = -1;
        boolean next = false;
        for (int i = 0; i < instructions.length; i++) {
            for (int j = 0; j < instructions[i].length; j = j + 2) {
                if (status == 0 || status == 3) {
                    if (!next) {
                        m = random.nextInt(rightBound);
                    } else {
                        status = 1;
                    }
                    m1 = random.nextInt(m);
                    m2 = m1 + 2 + random.nextInt(rightBound - 1 - m1 - 1);
                }
                assert m != -1 && m1 != -1 && m2 != -1;
                instructions[i][j] = status == 0 ? m : status == 1 ? m1 : m2;
                instructions[i][j + 1] = status == 0 ? m + 1 : status == 1 ? m1 + 1 : m2 + 1;
                status++;
                next = true;
            }
        }
    }


}
