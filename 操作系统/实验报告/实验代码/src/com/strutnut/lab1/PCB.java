package com.strutnut.lab1;

public class PCB {

    int id;
    int priority;
    int cpuTime;
    int allTime;
    int startBlock;
    int blockTime;
    State state;
    PCB next;

    public PCB(int id, int priority, int cpuTime, int allTime, int startBlock, int blockTime, State state, PCB next) {
        this.id = id;
        this.priority = priority;
        this.cpuTime = cpuTime;
        this.allTime = allTime;
        this.startBlock = startBlock;
        this.blockTime = blockTime;
        this.state = state;
        this.next = next;
    }
}
