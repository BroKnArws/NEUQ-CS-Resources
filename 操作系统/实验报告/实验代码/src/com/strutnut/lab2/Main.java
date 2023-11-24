package com.strutnut.lab2;


public class Main {

    public void work(Strategy strategy) {
        Block block1 = strategy.alloc(130);
        Block block2 = strategy.alloc(60);
        Block block3 = strategy.alloc(100);
        strategy.free(block2);
        Block block4 = strategy.alloc(200);
        strategy.free(block3);
        strategy.free(block1);
        Block block5 = strategy.alloc(140);
        Block block6 = strategy.alloc(60);
        Block block7 = strategy.alloc(50);
        strategy.free(block6);
        strategy.clearList();
    }

    public static void main(String[] args) {

        Main main = new Main();

        System.out.println("************** 最佳适应算法 **************");
        main.work(new BestFitStrategy());

        System.out.println("\n************** 首次适应算法 **************");
        main.work(new FirstFitStrategy());

    }

}
