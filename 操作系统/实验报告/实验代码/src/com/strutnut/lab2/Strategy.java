package com.strutnut.lab2;

public interface Strategy {

    int INITIAL_SIZE = 640;

    Block alloc(int size);

    void free(Block block);

    void clearList();

}
