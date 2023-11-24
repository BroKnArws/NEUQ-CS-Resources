package com.strutnut.lab3;

import java.util.*;

public class LRUStrategy implements Replacement {


    private int[][] instructions;

    private List<Block> memoryPagesList = new ArrayList<>();

    private HashSet<Integer> existedPages = new HashSet<>();

    private int discardCount = 0;

    public LRUStrategy(int[][] instructions) {
        this.instructions = Arrays.copyOf(instructions, instructions.length);
    }

    @Override
    public void run() {
        for (int i = 0; i < instructions.length; i++) {
            for (int j = 0; j < instructions[i].length; j++) {
                int pageNum = instructions[i][j] / 10;
                if (existedPages.contains(pageNum)) {
                    for (Block b : memoryPagesList) {
                        if (b.pageNum == pageNum) {
                            b.lastVisit = -1;
                        }
                        b.lastVisit++;
                    }
                    printBlockList(memoryPagesList, instructions[i][j], true);
                    //System.out.println(pageNum + " 页存在，指令的物理地址为 " + (getPositionOfPageInMemoryList(pageNum) * 10 + pages[i][j] % 10));
                } else {
                    if (memoryPagesList.size() >= MAX_PAGE_SIZE) {
                        int max = Integer.MIN_VALUE;
                        int index = -1;
                        for (int k = 0; k < memoryPagesList.size(); k++) {
                            Block b = memoryPagesList.get(k);
                            if (max < b.lastVisit) {
                                max = b.lastVisit;
                                index = k;
                            }
                        }
                        assert index != -1;
                        Block discard = memoryPagesList.get(index);
                        //System.out.println("内存已满，置换出页号为 " + discard.pageNum + " ,并换入页号 " + pageNum + " ,换入物理地址为 " + getPositionOfPageInMemoryList(discard.pageNum) * 10);
                        existedPages.remove(discard.pageNum);
                        discard.pageNum = pageNum;
                        discard.lastVisit = 0;
                        printBlockList(memoryPagesList, instructions[i][j], false);
                    } else {
                        memoryPagesList.add(new Block(pageNum, 0));
                        printBlockList(memoryPagesList, instructions[i][j], false);
                        //System.out.println("内存未满，调入页号为 " + pageNum);
                    }
                    existedPages.add(pageNum);
                    discardCount++;
                }
            }
        }
        System.out.println("====================================");
        System.out.println("LRU 缺页次数是 " + discardCount);
        System.out.println("LRU 缺页率是 " + (double) discardCount * 100 / (instructions.length * instructions[0].length) + " %");
        System.out.println("====================================");
    }


    private void printBlockList(List<Block> blockList, int inst, boolean hit) {
        System.out.print((hit ? "  " : "未") + "命中, ");
        System.out.print("当前指令： " + inst + " , 物理内存块： ");
        for (int i = 0; i < blockList.size(); i++) {
            Block block = blockList.get(i);
            if (i == blockList.size() - 1) {
                System.out.println(block.pageNum);
            } else {
                System.out.print(block.pageNum + "->");
            }
        }
    }
}
