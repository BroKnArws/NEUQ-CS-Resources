DATAS SEGMENT
    BUF DB 10 DUP(?)
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    MOV SI,0
    
    LET0:
    MOV AH,1
    INT 21H
    CMP AL,32    ;�ո�
    JE LETE
    MOV BUF[SI],AL
    INC SI
    JMP LET0
     
    LETE:
    MOV BUF[SI],'$'
    
    LEA DX,BUF
    MOV BX,SEG BUF
    MOV DS,BX
    MOV AH,9
    INT 21H
    
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START
