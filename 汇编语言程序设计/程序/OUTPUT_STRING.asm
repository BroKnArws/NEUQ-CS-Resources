DATAS SEGMENT
    ;缓冲区
    BUFFER DB 14,?,14 DUP(?)  ;最大输入字节个数，实际输入个数（自动），13个空字节单元
  
    
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;DS:DX,DX是字节缓冲区偏移地址
    MOV AX,SEG BUFFER
    MOV DS,AX
    MOV DX,OFFSET BUFFER
    
    MOV AH,10
    INT 21H
    
    MOV AH,2
    MOV DL,0DH 
    INT 21H
    MOV AH,2
    MOV DL,0AH 
    INT 21H
    
    MOV BX,DS:[2]
    ADD BX,20H
    MOV DS:[2],BX
    
    MOV AH,9
    LEA DX,BUFFER
    INT 21H
    
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START




