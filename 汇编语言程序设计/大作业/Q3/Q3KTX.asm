;---------- 题 3 ---------------

;3.	编写90H号软件中断程序，
;在第（10）行**（班级序列号为35）**列彩色显示你的姓名
;(注：要求中断驻留，行从第0行开始计算，列从第0列开始计算)。

;-----------------------------

DATAS SEGMENT
DATAS ENDS

STACKS SEGMENT
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:

;-------------------------------------MACRO

;宏，保护现场
PROTECT_STACK MACRO
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
ENDM

;宏，现场恢复
RECOVER_STACK MACRO
	POP DX
	POP CX
	POP BX
	POP AX

ENDM

;宏 清屏
CLEAR_SCREEN MACRO

	PROTECT_STACK
	
    MOV AH,6
	MOV AL,0
	MOV BH,07H  ;黑底白字
	MOV CH,0	;左上(0,0)
	MOV CL,0
	MOV DH,24
	MOV DL,79	;右下(24,79)->25 * 80
	INT 10H
	;移动光标到开头
	MOV AH,2
	MOV DH,0
	MOV DL,0
	MOV BH,0
	INT 10H
	
	RECOVER_STACK
	
ENDM
;---------------------------------------START
    
    ;将90H号中断放入向量表中
    LEA DX,OUTPUTSTART
    MOV AX,SEG OUTPUTSTART
    MOV DS,AX
    MOV AL,90H
    MOV AH,25H
    INT 21H
    
    ;中断驻留
    MOV AH,31H
    MOV AL,0
    MOV DX,OUTPUTEND-OUTPUTSTART+16
    
    ;触发90H号中断
    INT 90H
    
    MOV AH,4CH
    INT 21H
    
    ;中断程序
    OUTPUTSTART:
    
    JMP CODE
    ;姓名
    MYNAME DB 'KONGTIANXIN'
    ;颜色
    COLOR DB 1EH
    CODE:
    
    ;现场保护
    PUSH DS
    PROTECT_STACK
    PUSH CS
    POP DS
    
    CLEAR_SCREEN
    
    ;移动光标到10行35列
	MOV AH,2
	MOV DH,10
	MOV DL,35
	MOV BH,0
	INT 10H
    
    ;写显存
	MOV BX,0B800H
	MOV ES,BX
	;行：A0H * AH = 640H
	MOV BX,640H
	;列 2H * 23H(35D) = 46H
	MOV DI,46H
	;名字的长度作为循环
	MOV CX,DWORD PTR COLOR-MYNAME
	MOV SI,0
	PAINT:
	;输出字符
	MOV AH,2
	MOV DL,MYNAME[SI]
	INC SI
	INT 21H
	MOV AL,COLOR
	;填色，奇地址存放属性
	ADD BYTE PTR ES:[BX+1+DI],AL
	;下一个字符换颜色
	ADD AL,3H		
	MOV COLOR,AL
	;下一个相邻位置
	ADD BX,2
	LOOP PAINT
    
    ;现场恢复
    RECOVER_STACK
    POP DS
    IRET
    OUTPUTEND:NOP
CODES ENDS
    END START














