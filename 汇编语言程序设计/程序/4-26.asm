DATAS SEGMENT
    TABLE DB '0.000$','1.000$','1.414$','1.732$',
    '2.000$','2.236$','2.449$','2.646$',
    '2.828$','3.000$'
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    
    ;����
    MOV AH,1
    INT 21H
    
    ;ȥASCII
    SUB AL,30H
    
    ;6�ֽ�һ����ƫ�Ƶ�ַ
    MOV BL,6
    IMUL BL
    
    MOV BX,AX
    
    ;����
   	MOV AH,2
    MOV DL,0DH 
    INT 21H
    MOV AH,2
    MOV DL,0AH 
    INT 21H
    
    ;���
	MOV AX,SEG TABLE
    MOV DS,AX
    LEA DX,TABLE
    ADD DX,BX
    
    MOV AH,9
    INT 21H
    
    
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START





