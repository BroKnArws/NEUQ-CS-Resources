DATAS SEGMENT
    SIGN DB '+' ;正负标志
    NUM DB 10110111B
    RESULT DB 0
    P DB 1  ;位乘数
DATAS ENDS

STACKS SEGMENT
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    CALL GETTRUEVALUE
    MOV AH,4CH
    INT 21H
    
    GETTRUEVALUE PROC
	    MOV AL,NUM
	    AND AL,AL
	    JNS LET1
	    MOV SIGN,'-' 
	    SUB AL,1
	    XOR AL,0FFH
	    MOV NUM,AL
	    LET1:
	    CMP NUM,0
	    JE LETE
	    MOV AH,0
	    MOV BL,10
	    MOV AL,NUM
	    IDIV BL      ;除10运算
	    MOV NUM,AL   ;商
	    MOV AL,AH    ;余数
	    MOV BL,P
	    IMUL BL
	    ADD RESULT,AL ;余数按位乘运算后并入RESULT
	    MOV AL,BL
	    MOV BH,10
	    IMUL BH
	    MOV P,AL     ;P = P * 10
	    JMP LET1
	    LETE:
	    RET
    GETTRUEVALUE ENDP
CODES ENDS
    END START
