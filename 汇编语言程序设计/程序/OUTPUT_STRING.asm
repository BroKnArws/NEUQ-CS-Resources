DATAS SEGMENT
    ;������
    BUFFER DB 14,?,14 DUP(?)  ;��������ֽڸ�����ʵ������������Զ�����13�����ֽڵ�Ԫ
  
    
DATAS ENDS

STACKS SEGMENT
    ;�˴������ջ�δ���
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;DS:DX,DX���ֽڻ�����ƫ�Ƶ�ַ
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




