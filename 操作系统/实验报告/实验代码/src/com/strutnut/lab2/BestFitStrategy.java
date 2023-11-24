package com.strutnut.lab2;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class BestFitStrategy implements Strategy {

    private int idCounter = 1;

    private List<Block> blockList = new LinkedList<>();

    public BestFitStrategy() {
        Block initBlock = new Block(-1, 0, INITIAL_SIZE, true);
        blockList.add(initBlock);
        log();
    }

    @Override
    public Block alloc(int size) {

        int maxSize = Integer.MIN_VALUE;
        Block maxBlock = null;
        int maxIndex = -1;
        for (int i = 0; i < blockList.size(); i++) {
            Block block = blockList.get(i);
            if (block.isFree && block.size >= size) {
                if (maxSize == Integer.MIN_VALUE || block.size <= maxSize) {
                    maxSize = block.size;
                    maxBlock = block;
                    maxIndex = i;
                }
            }
        }

        Block newBlock = null;
        if (maxIndex != -1) {
            newBlock = new Block(idCounter++, maxBlock.startAddress, size, false);
            maxBlock.startAddress += size;
            maxBlock.size -= size;
            if (maxBlock.size == 0) {
                blockList.remove(maxIndex);
            }
            blockList.add(maxIndex, newBlock);
        }

        System.out.println(">>> task" + (idCounter - 1) + " alloc " + size + "KB. ....OK");
        log();
        return newBlock;

    }


    private void log() {
        System.out.println("| id  startAddress  size  isFree |");
        for (Block b : blockList) {
            System.out.println(b.toString());
        }
        System.out.println("=========================\n");
    }

    @Override
    public void free(Block block) {
        int blockSize = block.size;
        int taskId = block.id;
        boolean flag = false;
        for (Block b : blockList) {
            if (b.id == block.id && !b.isFree) {
                b.isFree = true;
                b.id = -1;
                flag = true;
                Iterator<Block> it = blockList.iterator();
                while (it.hasNext()) {
                    Block bl = it.next();
                    if (bl.isFree && b.startAddress + b.size == bl.startAddress) {
                        b.size += bl.size;
                        it.remove();
                    } else if (bl.isFree && bl.startAddress + bl.size == b.startAddress) {
                        b.startAddress = bl.startAddress;
                        b.size += bl.size;
                        it.remove();
                    }
                }
                break;
            }
        }
        if (flag) {
            System.out.println(">>> task" + taskId + " free " + blockSize + "KB. ....OK");
            log();
        } else {
            throw new RuntimeException("FAILED");
        }
    }

    @Override
    public void clearList() {
        this.blockList.clear();
    }

}
