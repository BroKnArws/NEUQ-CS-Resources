package com.strutnut.lab3;

public class Main {


    public static void main(String[] args) {

        int[][] instructions = InstructionBuilder.build(32, 10);
        //int[][] instructions = {{2, 3, 2, 1, 5, 2}, {4, 5, 3, 2, 5, 2}};
        //int[][] instructions = {{4, 3, 2, 1}, {4, 3, 5, 4}, {3, 2, 1, 5}};
        //int[][] instructions = {{70, 0, 10, 20, 0}, {30, 0, 40, 20, 30}, {0, 30, 20, 10, 20}, {0, 10, 70, 0, 10}};
        printInstructions(instructions);

        System.out.println("============== FIFO ==============");
        Replacement stg;
        stg = new FIFOStrategy(instructions);
        stg.run();
        System.out.println("============== LRU ==============");
        stg = new LRUStrategy(instructions);
        stg.run();
        System.out.println("============== OPT ==============");
        stg = new OPTStrategy(instructions);
        stg.run();


    }

    private static void printInstructions(int[][] instructions) {
        System.out.println("============指令============");
        int count = 0;
        for (int i = 0; i < instructions.length; i++) {
            for (int j = 0; j < instructions[i].length; j++) {
                System.out.print(instructions[i][j] + ",");
                count = (count + 1) % 10;
                if (count == 0) {
                    System.out.print("\n");
                }
            }
        }
    }


}
