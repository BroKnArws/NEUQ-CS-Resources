DATAS SEGMENT
DATAS ENDS

STACKS SEGMENT
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    ;保存原有的9号中断
    MOV AX,0
    MOV ES,AX  ;0段，中断向量表
    PUSH ES:[9*4]
    POP ES:[0200H]
    PUSH ES:[9*4+2]
    POP ES:[0202H]
    ;设置中断向量
    MOV AX,SEG INT9START
    MOV DS,AX
    LEA DX,INT9START
    MOV AL,9H
    MOV AH,25H
    INT 21H
    ;中断驻留
    MOV AH,31H
    MOV AL,0
    MOV DX,INT9END-INT9START+16
    INT 21H
    
    MOV AH,4CH
    INT 21H
    
	INT9START:
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH ES
	;接收键盘按键
	IN AL,60H
	PUSHF
	MOV BX,0
	MOV ES,BX
	;调用9号中断
	CALL DWORD PTR ES:[0200H]
	  
	CMP AL,3BH
	JNE INT9RET
	;写显存
	MOV BX,0B800H
	MOV ES,BX
	MOV BX,1
	MOV CX,2000 ;窗口屏幕 25 * 80 = 2000
	S:
	INC BYTE PTR ES:[BX]
	ADD BX,2
	LOOP S
	  
	INT9RET:
	POP ES
	POP CX
	POP BX
	POP AX
	IRET
	INT9END:NOP
CODES ENDS
END START














