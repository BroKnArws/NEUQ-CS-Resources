package com.strutnut.lab2;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class FirstFitStrategy implements Strategy {

    /**
     * 进程 id 计数器
     */
    private int idCounter = 1;

    private List<Block> blockList = new ArrayList<>();

    public FirstFitStrategy() {
        Block initBlock = new Block(-1, 0, INITIAL_SIZE, true);
        blockList.add(initBlock);
        log();
    }


    @Override
    public Block alloc(int size) {
        Block block = null;
        if (!blockList.isEmpty()) {
            Iterator<Block> iterator = blockList.iterator();
            int i = 0;
            while (iterator.hasNext()) {
                Block b = iterator.next();
                if (b.size >= size && b.isFree) {
                    block = new Block(idCounter++, b.startAddress, size, false);
                    b.startAddress += size;
                    b.size -= size;
                    if (b.size == 0) {
                        iterator.remove();
                    }
                    blockList.add(i, block);
                    break;
                }
                i++;
            }
        }
        if (block != null) {
            System.out.println(">>> task" + (idCounter - 1) + " alloc " + size + "KB. ....OK");
            log();
        }
        return block;
    }

    private void log() {
        System.out.println("| id  startAddress  size  isFree |");
        for (Block b : blockList) {
            System.out.println(b.toString());
        }
        System.out.println("==============================\n");
    }

    @Override
    public void free(Block block) {
        int taskId = block.id;
        int blockSize = block.size;
        boolean flag = false;
        for (int i = 0; i < blockList.size(); i++) {
            Block b = blockList.get(i);
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
        }
    }

    @Override
    public void clearList() {
        this.blockList.clear();
    }
}
