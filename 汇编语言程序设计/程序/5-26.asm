DATAS SEGMENT

DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    
    MOV AH,1
    INT 21H
    
    SUB AL,30H
    AND AL,1
    CMP AL,0
    
    ;»»ÐÐ
    MOV AH,2
    MOV DL,0AH
    INT 21H
    MOV DL,0DH
    INT 21H
    
    JE LET1
  
    MOV DL,'N'
    INT 21H
    JMP LET2
    
    LET1:
    MOV DL,'Y'
    INT 21H
    
    LET2:
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START

