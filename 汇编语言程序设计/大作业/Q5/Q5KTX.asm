;---------- �� 5 ---------------

;��ȡϵͳʱ��İٷ�����Ϊ0��99֮����������
;ʵ������������ļӡ������ˡ������㣬
;����ʾ��ʽ����������

;-----------------------------

DATAS SEGMENT
    ;MTIME����Űٷ�����ֵ
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

;�꣬����ַ�
PRINTC MACRO STR
	 PROTECT_STACK
	 
	 MOV AH,2
	 MOV DL,STR
	 INT 21H
	 
	 RECOVER_STACK
ENDM

;�꣬����ַ���
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

;�꣬����
NEXTLINE MACRO
    PRINTC 0AH
    PRINTC 0DH
ENDM

;�� ����
CLEAR_SCREEN MACRO

	PROTECT_STACK
	
    MOV AH,6
	MOV AL,0
	MOV BH,07H  ;�ڵװ���
	MOV CH,0	;����(0,0)
	MOV CL,0
	MOV DH,24
	MOV DL,79	;����(24,79)->25 * 80
	INT 10H
	;�ƶ���굽��ͷ
	MOV AH,2
	MOV DH,0
	MOV DL,0
	MOV BH,0
	INT 10H
	
	RECOVER_STACK
	
ENDM

;�꣬������ֵ�ʮ�����ַ���
PRINT_NUMS MACRO NUM
   
   LOCAL DO_ING
   LOCAL DO_END
   
   ;�����ֳ�
   PROTECT_STACK
   
   MOV AX,NUM
   MOV DX,0
   MOV CX,0
   MOV BX,10
   DO_ING:
    DIV BX
    ;������ջ���̽�����һ��ѭ��
    PUSH DX
    MOV DX,0
    INC CX
    CMP AX,0
    JE DO_END
    JMP DO_ING
   ;��λ���
   DO_END:
    POP AX
    ADD AX,3030H
    PRINTC AL
    LOOP DO_END
    
    ;�ֳ��ָ�
    RECOVER_STACK
ENDM

;�꣬��ȡ��ǰʱ��
GET_MTIME MACRO ARG,INFO

	MOV AH,2CH		;DL->millsecond
	INT 21H
	MOV DH,0
	MOV ARG,DX
	
	PRINTS INFO
	PRINT_NUMS ARG
	NEXTLINE
	
ENDM

;�꣬�˳�����
RTSYS MACRO
	MOV AH,4CH
	INT 21H
	
ENDM

;�꣬����ִ�г���
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
;-------------------------------------------�ж�

;---��0(0��)���жϸ�д-----

;��00H���жϷ�����������
    LEA DX,DIVIDE_START
    MOV AX,SEG DIVIDE_START
    MOV DS,AX
    MOV AL,00H
    MOV AH,25H
    INT 21H
    
    ;�ж�פ��
    MOV AH,31H
    MOV AL,0
    MOV DX,DIVIDE_END-DIVIDE_START+16
    
    JMP STARTS
    
    ;�жϳ���
   DIVIDE_START:
    JMP CODE
    DIVIDE_ERROR DB '0 Cannot Be Used As A Divisor.So Please *RESTART* The Program.$'
   CODE:
   
    ;�ֳ�����
    PUSH DS
    PUSH DX
    PUSH AX
    PUSH CS
    POP DS
    
    PRINTS DIVIDE_ERROR  
    
    ;�ֳ��ָ�
    POP AX
    POP DX
    POP DS
    
    ;�ص�����
    MOV AX,4C00H
    INT 21H
    
    DIVIDE_END:NOP

;-------------------------------------------START
   STARTS:
    MOV AX,DATAS
    MOV DS,AX
	
	;MTIME_1 = ��ǰ�ٷ���
	GET_MTIME MTIME_1,NUM_INFO_BEFORE
	
	;ִ����ʱ
	CALL DELAY
	
	;MTIME_1 = ��ʱ��İٷ���
	GET_MTIME MTIME_2,NUM_INFO_AFTER
	
	;��
	CALL DO_ADD
	
	;��
	CALL DO_SUB
	
	;��
	CALL DO_MUL
	
	;��
	CALL DO_DIV
	
	;����ִ�г���
	DO_AGAIN
	
    
;----------------------------------------PROC
	
;�ӷ�
DO_ADD PROC

	MOV AX,MTIME_1
	MOV BX,MTIME_2
	ADD AX,BX
	;��ӡ��ӽ��
	PRINTS ADD_INFO
	PRINT_NUMS AX
	NEXTLINE
	RET
	
DO_ADD ENDP


;����
DO_SUB PROC

	MOV AX,MTIME_1
	MOV BX,MTIME_2
	CMP AX,BX
	JAE SUB_NN
	;����Ǹ����ȴ�ӡ��-��
	XCHG AX,BX
	SUB AX,BX
	PRINTS SUB_INFO
	PRINTC '-'
	PRINT_NUMS AX
	NEXTLINE
	RET
	;������ֱ�Ӵ�ӡ
   SUB_NN:
    SUB AX,BX
	PRINTS SUB_INFO
	PRINT_NUMS AX
	NEXTLINE
	RET
	
DO_SUB ENDP
	
;�˷�
DO_MUL PROC
	MOV AX,MTIME_1
	MOV BX,MTIME_2
	MUL BX
	;��ӡ��˽��
	PRINTS MUL_INFO
	PRINT_NUMS AX
	NEXTLINE
	RET
DO_MUL ENDP

;����
DO_DIV PROC

	MOV AX,MTIME_1
	MOV BX,MTIME_2
	DIV BX
	;��ӡ��
	PRINTS DIV_INFO
	PRINT_NUMS AX
	;��ӡ����
	PRINTS MOD_INFO
	PRINT_NUMS DX
	NEXTLINE
	RET
	
DO_DIV ENDP

;��ʱ
DELAY PROC

    ;��ȡʱ��
	MOV AH,00H
	INT 1AH
	MOV BX,DX
	;������ѯʱ�����Ƿ�����
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
   ;��ʱʱ�䷴����߮��8~32��
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






























