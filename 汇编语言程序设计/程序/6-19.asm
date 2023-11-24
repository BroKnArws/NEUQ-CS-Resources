DATAS SEGMENT
    STR1 DB 'HELLo!'
    STR2 DB 'hELLO!word'
    SAME DB 0
    NSAME DB 0
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,ES:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    MOV ES,AX
    
   
    MOV AL,STR2-STR1
    MOV BL,SAME-STR2
    
    MOV AH,0
    MOV BH,0
    
    MOV BP,0
    
    ;CX取最小长度,DL取长度差
    MOV DH,AL
    MOV CX,BX
    SUB AL,BL
    MOV DL,AL
    MOV AL,DH
    CMP AL,BL
    
    JBE LET0
    JMP LET1
    LET0:
    MOV CX,AX
    SUB BL,AL
    MOV DL,BL
    
    ;逐个字符比较
    LET1:
    MOV AL,STR1[BP]
    CMP AL,STR2[BP]
    JE LET2
    INC NSAME
    JMP LET3
  
    LET2:
    INC SAME
    
    LET3:
  	INC BP
  	LOOP LET1
    
    LETE:
    ADD NSAME,DL   ;长度差必定相异
    ADD SAME,30H
    ADD NSAME,30H
    ;输出
    MOV AH,2
    MOV DL,SAME
    INT 21H
    MOV DL,' '
    INT 21H
    MOV DL,NSAME
    INT 21H
    
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START


