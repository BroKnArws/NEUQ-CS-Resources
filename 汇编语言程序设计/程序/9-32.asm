DATAS SEGMENT
    MSG DB 'HELLO!$'
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;清屏
    MOV AH,6
	MOV AL,0
	MOV BH,07H
	MOV CH,0	;左上(0,0)
	MOV CL,0
	MOV DH,24
	MOV DL,79	;右下(24,79)->25 * 80
	INT 10H
	MOV AH,2
	MOV DH,0
	MOV DL,0
	MOV BH,0
	INT 10H

	
	LEA DX,MSG
	MOV AH,9
	INT 21H
	;移动输入光标
	MOV AH,2
	MOV DH,1
	MOV DL,0
	MOV BH,0
	INT 10H
	MOV AH,10
	INT 21H


    MOV AH,4CH
    INT 21H
CODES ENDS
    END START
