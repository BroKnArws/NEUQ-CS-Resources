DATAS SEGMENT
   X DW 0409H
   Y DW 0100H

DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
    
START:
	MOV AX,DATAS
    MOV DS,AX
    
    ;����
    MOV AX,X
    ADD AX,Y
    AAA
    MOV BX,AX
    
    ;ת�ַ�
    ADD BX,3030H
    
    ;�������
    MOV AH,2
    MOV DL,BH
    INT 21H
    MOV DL,BL
    INT 21H
    
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START












