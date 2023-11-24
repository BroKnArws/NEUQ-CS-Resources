;4.16
DATAS SEGMENT
    X DB 1
    Y DB 16
    Z DW ?
    W DB 1
    
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;------------------------------乘法
    
    ;MOV AL,16  ;8位，AL是被乘数
    ;ADD AL,X   
    
    ;MOV BL,5         
    ;IMUL BL   ;乘以BL，AX重置为运算结果
    
    ;-----------------------------除法
    
    ;MOV AL,X     ;AL是被除数
    ;MOV BL,4     
    ;IDIV BL      ;除以BL，AL重置为商
    ;MOV BL,Y   
    ;SUB AL,BL   
    ;MOV Z,AX
    
    ;-------------------------
    ;MOV AL,X
    ;MOV BL,8
    ;IMUL BL
    ;MOV Z,AX
    
    ;MOV AH,0
    ;MOV AL,Y 
    ;MOV BL,16
    ;IDIV BL
    ;ADD Z,AX
    
    ;MOV AL,W
    ;MOV BL,W
    ;IMUL BL
    ;SUB Z,AX
    ;------------------------------
    MOV AL,X
    ADD AL,Y
    
    MOV BL,X
    SUB BL,Y
    
    IMUL BL
    
    MOV Z,AX
    MOV AH,0
    
    MOV AL,X
    MOV BL,Y
    IDIV BL
    
    SUB Z,AX
    
    
    

    
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START


