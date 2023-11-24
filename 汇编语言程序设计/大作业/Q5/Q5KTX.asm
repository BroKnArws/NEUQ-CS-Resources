;---------- 题 5 ---------------

;读取系统时间的百分秒作为0—99之间的随机数，
;实现两个随机数的加、减、乘、除运算，
;并显示算式及计算结果。

;-----------------------------

DATAS SEGMENT
    ;MTIME：存放百分秒数值
    MTIME_1 DW 0
    MTIME_2 DW 0
    NUM_INFO_BEFORE DB 'The Frist Number Is : $'
    NUM_INFO_AFTER DB 'The Second Number Is : $'
    ADD_INFO DB 'NUM1 + NUM2 = $'
    SUB_INFO DB 'NUM1 - NUM2 = $'
    MUL_INFO DB 'NUM1 * NUM2 = $'
    DIV_INFO DB 'NUM1 / NUM2 = $'
    MOD_INFO DB ' ,MOD = $'
    TIPS_INFO DB 'Do You Want To Repeat Again ?[y/n] $'
    DELAY_TIME DB 14
DATAS ENDS

STACKS SEGMENT
    
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:

;-------------------------------------MACRO

;宏，输出字符
PRINTC MACRO STR
	 PROTECT_STACK
	 
	 MOV AH,2
	 MOV DL,STR
	 INT 21H
	 
	 RECOVER_STACK
ENDM

;宏，输出字符串
PRINTS MACRO STR
	 PROTECT_STACK
	 PUSH DS
	 
	 MOV AX,SEG STR
	 MOV DS,AX
	 LEA DX,STR
	 MOV AH,9
	 INT 21H
	 
	 POP DS
	 RECOVER_STACK
ENDM

PROTECT_STACK MACRO
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
ENDM

RECOVER_STACK MACRO
	POP DX
	POP CX
	POP BX
	POP AX

ENDM

;宏，换行
NEXTLINE MACRO
    PRINTC 0AH
    PRINTC 0DH
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

;宏，输出数字的十进制字符串
PRINT_NUMS MACRO NUM
   
   LOCAL DO_ING
   LOCAL DO_END
   
   ;保护现场
   PROTECT_STACK
   
   MOV AX,NUM
   MOV DX,0
   MOV CX,0
   MOV BX,10
   DO_ING:
    DIV BX
    ;余数入栈，商进入下一次循环
    PUSH DX
    MOV DX,0
    INC CX
    CMP AX,0
    JE DO_END
    JMP DO_ING
   ;按位输出
   DO_END:
    POP AX
    ADD AX,3030H
    PRINTC AL
    LOOP DO_END
    
    ;现场恢复
    RECOVER_STACK
ENDM

;宏，获取当前时间
GET_MTIME MACRO ARG,INFO

	MOV AH,2CH		;DL->millsecond
	INT 21H
	MOV DH,0
	MOV ARG,DX
	
	PRINTS INFO
	PRINT_NUMS ARG
	NEXTLINE
	
ENDM

;宏，退出程序
RTSYS MACRO
	MOV AH,4CH
	INT 21H
	
ENDM

;宏，反复执行程序
DO_AGAIN MACRO
    LOCAL RESTART
    
    PRINTS TIPS_INFO
	
	MOV AH,1H
	INT 21H
	
	CMP AL,0DH
	JE RESTART
	CMP AL,'y'
	JE RESTART
	CMP AL,'Y'
	JE RESTART
	RTSYS
	
   RESTART:
    CLEAR_SCREEN
    JMP STARTS
ENDM
;-------------------------------------------中断

;---除0(0号)的中断改写-----

;将00H号中断放入向量表中
    LEA DX,DIVIDE_START
    MOV AX,SEG DIVIDE_START
    MOV DS,AX
    MOV AL,00H
    MOV AH,25H
    INT 21H
    
    ;中断驻留
    MOV AH,31H
    MOV AL,0
    MOV DX,DIVIDE_END-DIVIDE_START+16
    
    JMP STARTS
    
    ;中断程序
   DIVIDE_START:
    JMP CODE
    DIVIDE_ERROR DB '0 Cannot Be Used As A Divisor.So Please *RESTART* The Program.$'
   CODE:
   
    ;现场保护
    PUSH DS
    PUSH DX
    PUSH AX
    PUSH CS
    POP DS
    
    PRINTS DIVIDE_ERROR  
    
    ;现场恢复
    POP AX
    POP DX
    POP DS
    
    ;回到界面
    MOV AX,4C00H
    INT 21H
    
    DIVIDE_END:NOP

;-------------------------------------------START
   STARTS:
    MOV AX,DATAS
    MOV DS,AX
	
	;MTIME_1 = 当前百分秒
	GET_MTIME MTIME_1,NUM_INFO_BEFORE
	
	;执行延时
	CALL DELAY
	
	;MTIME_1 = 延时后的百分秒
	GET_MTIME MTIME_2,NUM_INFO_AFTER
	
	;加
	CALL DO_ADD
	
	;减
	CALL DO_SUB
	
	;乘
	CALL DO_MUL
	
	;除
	CALL DO_DIV
	
	;反复执行程序
	DO_AGAIN
	
    
;----------------------------------------PROC
	
;加法
DO_ADD PROC

	MOV AX,MTIME_1
	MOV BX,MTIME_2
	ADD AX,BX
	;打印相加结果
	PRINTS ADD_INFO
	PRINT_NUMS AX
	NEXTLINE
	RET
	
DO_ADD ENDP


;减法
DO_SUB PROC

	MOV AX,MTIME_1
	MOV BX,MTIME_2
	CMP AX,BX
	JAE SUB_NN
	;如果是负数先打印‘-’
	XCHG AX,BX
	SUB AX,BX
	PRINTS SUB_INFO
	PRINTC '-'
	PRINT_NUMS AX
	NEXTLINE
	RET
	;是正数直接打印
   SUB_NN:
    SUB AX,BX
	PRINTS SUB_INFO
	PRINT_NUMS AX
	NEXTLINE
	RET
	
DO_SUB ENDP
	
;乘法
DO_MUL PROC
	MOV AX,MTIME_1
	MOV BX,MTIME_2
	MUL BX
	;打印相乘结果
	PRINTS MUL_INFO
	PRINT_NUMS AX
	NEXTLINE
	RET
DO_MUL ENDP

;除法
DO_DIV PROC

	MOV AX,MTIME_1
	MOV BX,MTIME_2
	DIV BX
	;打印商
	PRINTS DIV_INFO
	PRINT_NUMS AX
	;打印余数
	PRINTS MOD_INFO
	PRINT_NUMS DX
	NEXTLINE
	RET
	
DO_DIV ENDP

;延时
DELAY PROC

    ;读取时钟
	MOV AH,00H
	INT 1AH
	MOV BX,DX
	;反复查询时间差额是否满足
   REPTS:
    MOV AH,00H
    INT 1AH
    MOV AX,DX
    SUB AX,BX
    ;0s<AX<1s
    CMP AX,14
    JL REPTS
    CMP DELAY_TIME,30
    JBE DO_REPE_ADD
    JA DO_REPE_SUB
   ;延时时间反复游弋（8~32）
   DO_REPE_ADD:
    MOV BL,2
    ADD DELAY_TIME,BL
    RET
   DO_REPE_SUB:
    MOV BL,24
    SUB DELAY_TIME,BL
    RET
    
DELAY ENDP

CODES ENDS
    END START






























