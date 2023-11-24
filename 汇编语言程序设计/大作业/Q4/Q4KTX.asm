;---------- 题 4 ---------------

;编写程序。从键盘输入多个带符号数：
;①统计负数的个数；
;②计算所有负数之和，并显示出十进制结果。

;---------- 示 例 --------------


;输入：34 -2 -3 -4 43
;输出：The Number Of Negative Numbers Is : 3
;      The Sum Of Negative Numbers Is : -9
		

;输入:0 -200 -100 -50000 50000
;输出：The Number Of Negative Numbers Is : 3
;      The Sum Of Negative Numbers Is : -50300

;输入:0 200 100 50000 50000
;输出：The Number Of Negative Numbers Is : 0
;      The Sum Of Negative Numbers Is : 0

;输入: ab cd ef
;输出：Please Input Correct Synatax

;----------------------------

DATAS SEGMENT
    ;存放数字字符串，以$分割
	ARRAYSTR DB 128 DUP('$')
	;ARRAYSTR的实际最大下标
	PTRNUM DW 0
    NUM_OF_NEGA DB 0
    ;临时数字，用于暂存十进制数（无论正负）
    TEMP DW 0
    ;是否是负数的标志
    SIGN DB 0
    ;负数的总和,上限65535
    SUM DW 0
    INPUT_INFO DB 'Please Input The Number List: $'
    ;错误信息：请输入正确的格式
    WRONG_INFO DB 'Please Input Correct Synatax!$'
    NUM_INFO DB 'The Number Of Negative Numbers Is : $'
    SUM_INFO DB 'The Sum Of Negative Numbers Is : $'
    OVER_INFO DB 'Overflow! $'
    TIPS_INFO DB 'Do You Want To Repeat Again ?[y/n] $'
DATAS ENDS

STACKS SEGMENT
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:

;--------------------------------MACRO

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


;宏，输出数字的十进制字符串
PRINT_NUM MACRO NUM
   
   LOCAL DO_ING
   LOCAL DO_END
   
   ;保护现场
   PROTECT_STACK
   
   MOV AX,WORD PTR NUM
   MOV DX,0
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

;-----------------------------START
   STARTS:
    MOV AX,DATAS
    MOV DS,AX
    
    ;重置数据
    CALL RESET_BEGIN
    
    PRINTS INPUT_INFO
    
    ;先输入一串带符号数，空格作为分割，
    ;在存储单元中以'$'代替
    INPUT:
     MOV AH,1
     INT 21H
     
     ;是回车？
     CMP AL,0DH
     ;跳出循环
     JE TONUM
     
     ;是空格？
     CMP AL,20H
     JNE ISNEGA
     ;分隔符
     INC SI
     JMP INPUT
     
    ;是负号？
    ISNEGA:
     CMP AL,'-'
     JNE NOTNEGA
     MOV ARRAYSTR[SI],'-'
     INC SI
     JMP INPUT
    ;不是负号的情况下
    NOTNEGA:
     ;是0~9的数字？
     CMP AL,'0'
     ;不是，报错  
     JB ERROR
     CMP AL,'9'  
     JA ERROR
     MOV ARRAYSTR[SI],AL
     INC SI
     JMP INPUT
     
    ;所有负数相加，并统计负数个数
    TONUM:
     MOV PTRNUM,SI
     ;数组下标
     MOV SI,0
     ;一个数字除符号外的位数
     MOV CX,0
     ;乘数
     MOV BX,1
    TONUMIN:
    
     ;如果数组下标已经大于PTRNUM，跳出
     CMP PTRNUM,SI
     JB PRINT_ALL
     
     MOV AL,ARRAYSTR[SI]
     CMP AL,'$'
     JE TOSUM
     CMP AL,'-'
     JE ADDNEGA
     ;是数字字符，入栈
     MOV AH,0
     PUSH AX
     INC SI
     INC CX
     JMP TONUMIN
    ADDNEGA:
     ;是负数
     MOV SIGN,1
     INC NUM_OF_NEGA
     INC SI
     JMP TONUMIN
    TOSUM:
     ;从个位数出栈
     POP AX
     SUB AL,30H
     MUL BX
     ADD TEMP,AX
     MOV AX,BX
     MOV BX,10
     MUL BX
     MOV BX,AX
     LOOP TOSUM
     ;是负数吗？
     CMP SIGN,1
     JNE TOSUMIN
     ;是负数，SUM+=TEMP，重置
     MOV AX,TEMP
     ADD SUM,AX
     INC SI
     CALL RESET
     JMP TONUMIN
    ;不是负数，重置
    TOSUMIN:
     INC SI
     CALL RESET
     JMP TONUMIN
     
    ;输出所有消息
    PRINT_ALL:
    
     PRINTS NUM_INFO
     PRINT_NUM NUM_OF_NEGA
     NEXTLINE
     
     PRINTS SUM_INFO
     
     ;没有负数也就没必要打印符号
     CMP NUM_OF_NEGA,0
     JE DO_NOT_PRINTN
     PRINTC '-'
    DO_NOT_PRINTN:
     PRINT_NUM SUM
     NEXTLINE
     
     JMP LETE
    ;输出错误消息
    ERROR:
     NEXTLINE
     PRINTS WRONG_INFO
     NEXTLINE
     JMP LETE
     
    LETE:
    
    DO_AGAIN
    
;--------------------------------PROC

;重置相关信息
RESET PROC
	 MOV TEMP,0
     MOV BX,1
     MOV SIGN,0
     RET
RESET ENDP 

;数据重置
RESET_BEGIN PROC

	MOV SI,0
    MOV TEMP,0
    MOV SUM,0
    MOV NUM_OF_NEGA,0
    MOV CX,128
   RESET_CLEAR:
    MOV ARRAYSTR[SI],'$'
    INC SI
    LOOP RESET_CLEAR
    MOV SI,0
    RET
    
RESET_BEGIN ENDP

CODES ENDS
    END START






















