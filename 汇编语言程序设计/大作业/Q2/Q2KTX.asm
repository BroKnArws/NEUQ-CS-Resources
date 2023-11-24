
;---------- �� 2 ---------------

;��д���򡣴Ӽ�������һ���ַ���
;������ASCII��Ӵ�С��˳�����У�
;���������Ľ����ʾ������

;---------- ʾ �� --------------

;���룺--==//..123044qwertyuiop
;�����ywutrqpoie==443210//..--

;----------------------------
DATAS SEGMENT
    INPUTINFO DB 'Please Input The String:$'
    OUTPUTINFO DB 'After Sorted The Answer Is:$'
    ;������ַ���
    STRING DB 64,?,64 DUP('$')
    ;NUM=STRING[1]����ȡʵ���������
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

;�꣬�����ֳ�
PROTECT_STACK MACRO
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
ENDM

;�꣬�ֳ��ָ�
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

;�꣬�˳�����
RTSYS MACRO
	MOV AH,4CH
	INT 21H
	
ENDM

;�꣬���ڷ���ִ�г���
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
    
    ;��������
    CALL RESET_BEGIN
    
    ;������ʾ
    PRINTS INPUTINFO
    
    ;�����ַ���
    MOV SI,1
    LEA DX,STRING
    MOV AH,10
    INT 21H
    ;ȡ�ֽڸ���
    MOV AL,STRING[SI]
    MOV AH,0
    MOV NUM,AX
    
    ;����ð������
    CALL SORT
    
    ;�س�����
    NEXTLINE
    ;�����ʾ
    PRINTS OUTPUTINFO
    ;���ASCII�������ַ���
    PRINTS STRING[2]
    NEXTLINE
    
    DO_AGAIN

;------------------------------------------------PROC

;��ʼð������
SORT PROC

	 CMP NUM,1
	 JE DO_END
	 
	 ;�ֳ�����
	 PROTECT_STACK
	
	 MOV CX,NUM
	 ;CX-1��
	 DEC CX
	LOOP1:
	 PUSH CX
	 MOV SI,0
	LOOP2:
	 MOV AL,STRING[2+SI]
	 CMP AL,STRING[2+SI+1]
	 ;��������
	 JGE NEXT
	 XCHG AL,STRING[2+SI+1]
	 MOV STRING[2+SI],AL
	NEXT:
	 ADD SI,1
	 LOOP LOOP2
	 POP CX
	 LOOP LOOP1
	 ;�ָ��ֳ�
	 RECOVER_STACK
	DO_END:
	 RET
SORT ENDP

;��������
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


















