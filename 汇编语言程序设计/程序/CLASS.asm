DATAS SEGMENT
    BUF DB 20,?,20 DUP(0)
DATAS ENDS

STACKS SEGMENT
    ;�˴������ջ�δ���
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    
    LEA DX,BUF
    
    MOV AH,10
    INT 21H
    
    ;��ȡ������ַ�����
    MOV BL,BUF[1]
    ;BH����Ϊ0
    MOV BH,0
    ;��ΪBUF[0][1]�������֣������Ҫ�ƶ���ĩβ
    ADD BX,2
    ;ĩβ�����ֹ��
    MOV BUF[BX],'$'
    MOV BUF[0],0AH
    MOV BUF[1],0DH
    ;�ٴ����������
    LEA DX,BUF
    MOV AH,9
    INT 21H
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START

