package com.strutnut.lab3;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;

public class OPTStrategy implements Replacement {

    private int[][] instructions;

    private List<Block> memoryPagesList = new ArrayList<>();

    private HashSet<Integer> existedPages = new HashSet<>();

    private int discardCount = 0;

    public OPTStrategy(int[][] instructions) {
        this.instructions = Arrays.copyOf(instructions, instructions.length);
    }

    @Override
    public void run() {
        for (int i = 0; i < instructions.length; i++) {
            for (int j = 0; j < instructions[i].length; j++) {
                int pageNum = instructions[i][j] / 10;
                if (existedPages.contains(pageNum)) {
                    printBlockList(memoryPagesList, instructions[i][j], true);
                    //System.out.println(pageNum + " 页存在，指令的物理地址为 " + (getPositionOfPageInMemoryList(pageNum) * 10 + pages[i][j] % 10));
                } else {
                    int discardPageNum = -1;
                    if (memoryPagesList.size() >= MAX_PAGE_SIZE) {
                        int fari = -1;
                        int farj = -1;

                        for (Block block : memoryPagesList) {
                            int currentPageNum = block.pageNum;
                            boolean findit = false;
                            for (int m = i; m < instructions.length; m++) {
                                if (findit) {
                                    break;
                                }
                                for (int n = m == i ? j + 1 : 0; n < instructions[m].length; n++) {
                                    if (currentPageNum == instructions[m][n] / 10) {
                                        findit = true;
                                        if (m * 10 + n > fari * 10 + farj) {
                                            fari = m;
                                            farj = n;
                                        }
                                        break;
                                    }
                                }
                            }
                            discardPageNum = findit ? instructions[fari][farj] / 10 : currentPageNum;
                            if (!findit) {
                                break;
                            }
                        }
                        assert fari != -1 && farj != -1 && discardPageNum != -1;
                        for (Block b : memoryPagesList) {
                            if (b.pageNum == discardPageNum) {
                                b.pageNum = pageNum;
                            }
                        }
                        printBlockList(memoryPagesList, instructions[i][j], false);
                        //System.out.println("内存已满，置换出页号为 " + discardPageNum + " ,并换入页号 " + pageNum + " ,换入物理地址为 " + getPositionOfPageInMemoryList(pageNum) * 10);
                        existedPages.remove(discardPageNum);
                    } else {
                        memoryPagesList.add(new Block(pageNum));
                        printBlockList(memoryPagesList, instructions[i][j], false);
                        //System.out.println("内存未满，调入页号为 " + pageNum);
                    }
                    existedPages.add(pageNum);
                    discardCount++;
                }
            }
        }
        System.out.println("====================================");
        System.out.println("OPT 缺页次数是 " + discardCount);
        System.out.println("OPT 缺页率是 " + (double) discardCount * 100 / (instructions.length * instructions[0].length) + " %");
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
