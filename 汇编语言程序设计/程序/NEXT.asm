DATAS SEGMENT
    ;�˴��������ݶδ���  
DATAS ENDS

STACKS SEGMENT
    ;�˴������ջ�δ���
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    MOV AH,1
    INT 21H
    
    MOV BL,AL
    MOV AH,2
    MOV DL,0DH ;�س�������Ƶ���ͷ
    INT 21H
    MOV AH,2
    MOV DL,0AH ;����,��ʱAL���0AH����Ϊ�﷨Լ��
    INT 21H
    
    ADD BL,20H
    MOV DL,BL
    MOV AH,2
    INT 21H
    
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START
