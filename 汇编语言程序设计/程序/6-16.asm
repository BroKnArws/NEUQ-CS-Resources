DATAS SEGMENT
    CATT DB 'A','B','C','D','@','F'
    SIGN DB 0
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
   	MOV CX,SIGN-CATT
   	MOV BP,0
   	LET1:
   	CMP CATT[BP],'@'
   	JNE LET2
   	MOV SIGN,1
   	JMP LETE
   	
   	LET2:
   	INC BP
   	LOOP LET1
   	
   	LETE:
   	ADD SIGN,30H
   	MOV AH,2
   	MOV DL,SIGN
   	INT 21H
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START
