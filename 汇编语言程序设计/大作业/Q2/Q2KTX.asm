
;---------- 题 2 ---------------

;编写程序。从键盘输入一串字符，
;按照其ASCII码从大到小的顺序排列，
;并把排序后的结果显示出来。

;---------- 示 例 --------------

;输入：--==//..123044qwertyuiop
;输出：ywutrqpoie==443210//..--

;----------------------------
DATAS SEGMENT
    INPUTINFO DB 'Please Input The String:$'
    OUTPUTINFO DB 'After Sorted The Answer Is:$'
    ;输入的字符串
    STRING DB 64,?,64 DUP('$')
    ;NUM=STRING[1]，获取实际输入个数
    NUM DW 0
    TIPS_INFO DB 'Do You Want To Repeat Again ?[y/n] $'
DATAS ENDS

STACKS SEGMENT
    DW 32 DUP(?)
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:

;---------------------------------------MACRO

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

;------------------------------------------START
   STARTS:
    MOV AX,DATAS
    MOV DS,AX
    MOV AX,STACKS
    MOV SS,AX
    
    ;数据重置
    CALL RESET_BEGIN
    
    ;输入提示
    PRINTS INPUTINFO
    
    ;输入字符串
    MOV SI,1
    LEA DX,STRING
    MOV AH,10
    INT 21H
    ;取字节个数
    MOV AL,STRING[SI]
    MOV AH,0
    MOV NUM,AX
    
    ;调用冒泡排序
    CALL SORT
    
    ;回车换行
    NEXTLINE
    ;输出提示
    PRINTS OUTPUTINFO
    ;输出ASCII排序后的字符串
    PRINTS STRING[2]
    NEXTLINE
    
    DO_AGAIN

;------------------------------------------------PROC

;开始冒泡排序
SORT PROC

	 CMP NUM,1
	 JE DO_END
	 
	 ;现场保护
	 PROTECT_STACK
	
	 MOV CX,NUM
	 ;CX-1趟
	 DEC CX
	LOOP1:
	 PUSH CX
	 MOV SI,0
	LOOP2:
	 MOV AL,STRING[2+SI]
	 CMP AL,STRING[2+SI+1]
	 ;逆序排序
	 JGE NEXT
	 XCHG AL,STRING[2+SI+1]
	 MOV STRING[2+SI],AL
	NEXT:
	 ADD SI,1
	 LOOP LOOP2
	 POP CX
	 LOOP LOOP1
	 ;恢复现场
	 RECOVER_STACK
	DO_END:
	 RET
SORT ENDP

;数据重置
RESET_BEGIN PROC

    MOV CX,64
    MOV SI,0
   RESET:
    MOV STRING[SI],'$'
    INC SI
    LOOP RESET
    RET
    
RESET_BEGIN ENDP

CODES ENDS
    END START


















