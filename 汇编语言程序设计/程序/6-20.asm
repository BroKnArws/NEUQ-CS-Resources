DATAS SEGMENT
	FOUND DW 3,5,62,80,2,65,99,21
    N DB ?
    MIN DW 10000
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    
    ;�������鳤��
    MOV AL,N-FOUND
    MOV BL,2
    MOV AH,0
    IDIV BL
    MOV AH,0
    MOV CX,AX
    
    MOV BP,0
    
    ;�����ж��Ƿ���С
    LET0:
    MOV AX,FOUND[BP]
    CMP AX,MIN
    JGE LET1
    MOV MIN,AX
    
    LET1:
    ADD BP,2
    LOOP LET0
    
    ;���
    MOV BX,MIN
    ADD BL,30H
    MOV AH,2
    MOV DL,BL
    INT 21H
	
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START

