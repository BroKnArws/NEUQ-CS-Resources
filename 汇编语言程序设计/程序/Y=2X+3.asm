DATAS SEGMENT
    EXPRESSION DB 'Y=2X+3=','$'
DATAS ENDS

STACKS SEGMENT
    ;�˴������ջ�δ���
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    
    ;����X
    MOV AH,1
    INT 21H
    
    ;ȥ��ASCII
    SUB AL,30H
    
    ;2X+3
    MOV BL,2
    MUL BL
    AAM
    ADD AX,3
    AAA
    MOV BX,AX
    
	;����
    MOV AH,2
    MOV DL,0DH 
    INT 21H
    MOV AH,2
    MOV DL,0AH 
    INT 21H
    
    ;תΪASCII
    ADD BX,3030H
    
    MOV AX,SEG EXPRESSION
    MOV DS,AX
    LEA DX,EXPRESSION

    ;���
    MOV AH,9
    INT 21H
    
    MOV AH,2
    MOV DL,BH
    INT 21H
    MOV DL,BL
    INT 21H

    MOV AH,4CH
    INT 21H
CODES ENDS
    END START











