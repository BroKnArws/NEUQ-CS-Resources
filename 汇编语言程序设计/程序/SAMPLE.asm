DATAS SEGMENT
    VAR1 DB 12,94,2 DUP(2,3),76H;此处输入数据段代码 
    VAR2 DW 3222,23,20H,$+77;地址计数器（当前地址+77）
    MSG1 DB 'HELLO WORLD'
    BUF1 EQU 'STUDENT'
    BUF2=34
     
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;此处输入代码段代码
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START

