;4.16
DATAS SEGMENT
    X DB 1
    Y DB 16
    Z DW ?
    W DB 1
    
DATAS ENDS

STACKS SEGMENT
    ;�˴������ջ�δ���
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;------------------------------�˷�
    
    ;MOV AL,16  ;8λ��AL�Ǳ�����
    ;ADD AL,X   
    
    ;MOV BL,5         
    ;IMUL BL   ;����BL��AX����Ϊ������
    
    ;-----------------------------����
    
    ;MOV AL,X     ;AL�Ǳ�����
    ;MOV BL,4     
    ;IDIV BL      ;����BL��AL����Ϊ��
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


