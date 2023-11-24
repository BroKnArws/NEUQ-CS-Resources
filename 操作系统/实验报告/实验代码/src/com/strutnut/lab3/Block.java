package com.strutnut.lab3;

public class Block {


    int pageNum;
    int lastVisit;

    public Block(int pageNum) {
        this.pageNum = pageNum;
    }

    public Block(int pageNum, int lastVisit) {
        this.pageNum = pageNum;
        this.lastVisit = lastVisit;
    }
}
