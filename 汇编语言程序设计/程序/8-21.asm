MULT MACRO X,Y,Z
	MOV AL,X
	MOV BL,Y
	MUL BL
	MOV Z,AL
ENDM

INPUT MACRO
	MOV AH,1
	INT 21H
ENDM

OUTPUT_STRING MACRO DISP
	MOV AX,SEG DISP
	MOV DS,AX
	LEA DX,DISP
	MOV AH,9
	INT 21H
ENDM

OUTPUT_CHAR MACRO DISP
    PUSH AX   ;��ջ����
	MOV DL,DISP
	MOV AH,2
	INT 21H
	POP AX
ENDM

KEY_STR MACRO
	MOV AH,10
	INT 21H
ENDM

DATAS SEGMENT
    TIME DB '2333$'
    X DB 20
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    INPUT
    SUB AL,30H
    MOV BH,AL
    INPUT
    SUB AL,30H
    MOV AH,0
    ADD AL,BH
    AAA
    ADD AX,3030H
    OUTPUT_CHAR AH
    OUTPUT_CHAR AL
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START
