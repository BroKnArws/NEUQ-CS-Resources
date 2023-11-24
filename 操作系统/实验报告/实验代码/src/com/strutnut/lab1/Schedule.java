package com.strutnut.lab1;

import java.util.*;

public class Schedule {

    // 进程完成数
    private int countDone = 0;
    private int len;

    private PCB head;

    public Schedule(int len, PCB head) {
        this.len = len;
        this.head = head;
    }

    // 存放阻塞前的进程优先级
    Map<Integer, Integer> prePriority = new HashMap<>();

    Deque<Integer> blockedQueue = new LinkedList<>();

    public void start() {
        while (countDone < len) {
            PCB p = head;
            while (p != null) {
                if (p.state == State.READY && p.priority == getMax(head)) {

                    p.priority -= 3;
                    p.cpuTime += 1;
                    p.allTime -= 1;

                    // 未执行且就绪进程 优先级 +1
                    PCB q = head;
                    while (q != null) {
                        if (q != p) {
                            if (q.allTime > 0 && q.state == State.READY) {
                                q.priority += 1;
                            }
                        }
                        q = q.next;
                    }

                    // 进程执行完毕
                    if (p.allTime == 0) {
                        p.state = State.DONE;
                        p.priority = -1;
                        countDone++;
                    }

                    // 所有阻塞进程的阻塞时间片减少
                    q = head;
                    while (q != null) {
                        if (q.state == State.BLOCK && q.blockTime > 0) {
                            if (--q.blockTime == 0) {
                                q.state = State.READY;
                                q.priority = prePriority.get(q.id);
                            }
                        }
                        q = q.next;
                    }

                    // 快进入阻塞的进程 statblock倒计时时间片减少
                    if (p.startBlock > 0) {
                        if (--p.startBlock == 0) {
                            p.state = State.BLOCK;
                            prePriority.put(p.id, p.priority);
                            p.priority = -1;
                        }
                    }

                    output(p);
                }

                p = p.next;
            }
        }
    }


    private void output(PCB p) {
        System.out.println("RUNNING PROG：" + p.id);

        System.out.println("READY_QUEUE：");
        List<PCB> readyProcess = new ArrayList<>();
        PCB q = head;
        while (q != null) {
            if (q.state == State.READY) {
                readyProcess.add(q);
            }
            q = q.next;
        }
        readyProcess.sort((o1, o2) -> o2.priority - o1.priority);
        if (readyProcess.size() == 0) {
            System.out.print("EMPTY");
        } else {
            for (PCB process : readyProcess) {
                System.out.print("->" + process.id);
            }
        }
        System.out.print("\n");

        System.out.println("BLOCK_QUEUE：");
        List<PCB> blockProcess = new ArrayList<>();
        q = head;
        while (q != null) {
            if (q.state == State.BLOCK) {
                blockProcess.add(q);
            }
            q = q.next;
        }
        blockProcess.sort((o1, o2) -> o2.priority - o1.priority);
        if (blockProcess.size() == 0) {
            System.out.print("EMPTY");
        } else {
            for (PCB process : blockProcess) {
                System.out.print("->" + process.id);
            }
        }
        System.out.print("\n");

        System.out.print("ID：");
        q = head;
        while (q != null) {
            System.out.print(q.id + " ");
            q = q.next;
        }
        System.out.print("\n");
        System.out.print("CPUTIME：");
        q = head;
        while (q != null) {
            System.out.print(q.cpuTime + " ");
            q = q.next;
        }
        System.out.print("\n");
        System.out.print("ALLTIME：");
        q = head;
        while (q != null) {
            System.out.print(q.allTime + " ");
            q = q.next;
        }
        System.out.print("\n");
        System.out.print("STARTBLOCK：");
        q = head;
        while (q != null) {
            System.out.print(q.startBlock + " ");
            q = q.next;
        }
        System.out.print("\n");
        System.out.print("STATE：");
        q = head;
        while (q != null) {
            System.out.print(q.state + " ");
            q = q.next;
        }
        System.out.print("\n");
        System.out.print("PRIORITY：");
        q = head;
        while (q != null) {
            System.out.print(q.priority + " ");
            q = q.next;
        }
        System.out.print("\n");
        System.out.println("===================");

    }

    private int getMax(PCB head) {
        PCB p = head;
        int max = Integer.MIN_VALUE;
        while (p != null) {
            max = Math.max(p.priority, max);
            p = p.next;
        }
        return max;
    }


    public static void main(String[] args) {
        PCB pcb1 = new PCB(0, 9, 0, 3, 2, 3, State.READY, null);
        PCB pcb2 = new PCB(1, 38, 0, 3, -1, 0, State.READY, null);
        PCB pcb3 = new PCB(2, 30, 0, 6, -1, 0, State.READY, null);
        PCB pcb4 = new PCB(3, 29, 0, 3, -1, 0, State.READY, null);
        PCB pcb5 = new PCB(4, 0, 0, 4, -1, 0, State.READY, null);

        pcb4.next = pcb5;
        pcb3.next = pcb4;
        pcb2.next = pcb3;
        pcb1.next = pcb2;

        Schedule schedule = new Schedule(5, pcb1);
        schedule.start();

    }
}
