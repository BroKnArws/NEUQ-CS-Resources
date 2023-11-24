;---------- 题 1 ---------------

;编写程序。从键盘输入一个两位十进制数，
;输出其二进制结果。

;-----------------------------

;示例：

;输入：34
;输出：00100010

;输入:340
;输出:Only Two Digits Are Allowed

;输入:Q1
;输出：Not A Number

;----------------------------
DATAS SEGMENT
	;字符串形式的十进制数字
    NUMSTR DB 3 DUP(?)
    ;防止NUMSTR过度填充
    BUFF_USELESS DB 32 DUP(0)
    WRONG_INFO DB 'Not A Number!$'
    WRONG_INFO_OVER DB 'Only Two Digits Are Allowed!$'
    ;字符转数字的变量
    NUMBER DB 0
    INPUT_INFO DB 'Please enter 2 decimal digits: $'
    OUTPUT_INFO DB 'The Binary number is: $'
    TIPS_INFO DB 'Do You Want To Repeat Again ?[y/n] $'
DATAS ENDS

STACKS SEGMENT
	;存放二进制位数的堆栈
    DW 16 DUP(?)
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
;-----------------------------------MACRO

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

;宏，退出程序
RTSYS MACRO
	MOV AH,4CH
	INT 21H
	
ENDM

;宏，用于反复执行程序
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


;------------------------------------START
   STARTS:
    MOV AX,DATAS
    MOV DS,AX
    MOV AX,STACKS
    MOV SS,AX
    
    ;数据重置
    CALL RESET_BEGIN
    
    ;输出提示消息
    PRINTS INPUT_INFO
    
   ;输入2位以内十进制数字
   INPUT:
    MOV AH,1
    INT 21H
    MOV NUMSTR[SI],AL
    INC SI
    CMP AL,0DH
    JNE INPUT
    
    ;判断字符是否是数字,如果不是报错
    CALL JUDGE_IS_NUM
    
    ;转为十进制数字
    TOD:
     ;SI:1->2位
     MOV SI,1
     MOV BL,1
    TODIN:
     CMP SI,-1
     JE TOB
     ;是个位数？
     MOV AL,NUMSTR[SI]
     DEC SI
     CMP AL,0DH
     JE TODIN
     ;逐位相乘
     SUB AL,30H
     MUL BL
     ADD NUMBER,AL
     MOV AL,BL
     MOV BH,10
     MUL BH
     MOV BL,AL
     JMP TODIN
     
    ;转为二进制
    TOB:
     MOV AL,NUMBER
     MOV CX,0
    TOBIN:
     MOV BL,2
     CMP AL,0
     JE FILL
     MOV AH,0
     DIV BL
     MOV BL,AL
     MOV AL,0
     ;余数入栈，商进入下一次循环
     PUSH AX
     INC CX
     MOV AL,BL
     JMP TOBIN
    
    ;8位补足
    FILL:
     MOV BX,8
     SUB BX,CX
     MOV CX,BX
    FILLIN:
     MOV AX,0
     PUSH AX
     LOOP FILLIN
     
     ;输出提示信息
     PRINTS OUTPUT_INFO
     
     MOV CX,8
    ;弹出堆栈，输出各个余数
    SHOW:
     POP AX
     MOV DL,AH
     ADD DL,30H
     PRINTC DL
    LOOP SHOW
     NEXTLINE
     JMP LETEND
     
   ;非数字，输出错误信息
   ERROR:
    PRINTS WRONG_INFO
    NEXTLINE
    JMP LETEND
   ;字符串长度大于2，报错
   ERROR_OVER:
    PRINTS WRONG_INFO_OVER
    NEXTLINE
    
   ;重复程序
   LETEND: 
    DO_AGAIN
;---------------------------------------PROC

 ;判断字符是否是数字,如果不是报错
JUDGE_IS_NUM PROC

	PROTECT_STACK
	
	;只允许输入2位，否则直接报错
	CMP SI,3
	JA ERROR_OVER

	MOV SI,0
    MOV CX,2
   JUDGE:
    MOV AL,NUMSTR[SI]
    CMP SI,0
    JNE JUDGE_IN
    ;第一个字符是回车？
    CMP AL,0DH
    JE ERROR
   JUDGE_IN:
    INC SI
    ;是回车？
    CMP AL,0DH
    JE TOD
    ;是0~9的数字？
    CMP AL,'0'  
    JB ERROR
    CMP AL,'9'  
    JA ERROR
    LOOP JUDGE
    
    RECOVER_STACK
    
    RET
    
JUDGE_IS_NUM ENDP

;数据重置
RESET_BEGIN PROC
    MOV AX,0
    MOV SI,0
    MOV NUMBER,0
    RET
RESET_BEGIN ENDP

CODES ENDS
    END START

















