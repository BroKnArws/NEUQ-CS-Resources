package com.strutnut.lab2;

public class Block {

    int id;
    int startAddress;
    int size;
    boolean isFree;


    public Block(int id, int startAddress, int size, boolean isFree) {
        this.id = id;
        this.startAddress = startAddress;
        this.size = size;
        this.isFree = isFree;
    }

    @Override
    public String toString() {
        return "  " + (id == -1 ? " " : id) +
                "     " + startAddress +
                "          " + size +
                "        " + (isFree ? "√" : "×");
    }
}
