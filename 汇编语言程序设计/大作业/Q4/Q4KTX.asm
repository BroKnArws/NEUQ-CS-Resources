;---------- �� 4 ---------------

;��д���򡣴Ӽ�������������������
;��ͳ�Ƹ����ĸ�����
;�ڼ������и���֮�ͣ�����ʾ��ʮ���ƽ����

;---------- ʾ �� --------------


;���룺34 -2 -3 -4 43
;�����The Number Of Negative Numbers Is : 3
;      The Sum Of Negative Numbers Is : -9
		

;����:0 -200 -100 -50000 50000
;�����The Number Of Negative Numbers Is : 3
;      The Sum Of Negative Numbers Is : -50300

;����:0 200 100 50000 50000
;�����The Number Of Negative Numbers Is : 0
;      The Sum Of Negative Numbers Is : 0

;����: ab cd ef
;�����Please Input Correct Synatax

;----------------------------

DATAS SEGMENT
    ;��������ַ�������$�ָ�
	ARRAYSTR DB 128 DUP('$')
	;ARRAYSTR��ʵ������±�
	PTRNUM DW 0
    NUM_OF_NEGA DB 0
    ;��ʱ���֣������ݴ�ʮ������������������
    TEMP DW 0
    ;�Ƿ��Ǹ����ı�־
    SIGN DB 0
    ;�������ܺ�,����65535
    SUM DW 0
    INPUT_INFO DB 'Please Input The Number List: $'
    ;������Ϣ����������ȷ�ĸ�ʽ
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


;�꣬������ֵ�ʮ�����ַ���
PRINT_NUM MACRO NUM
   
   LOCAL DO_ING
   LOCAL DO_END
   
   ;�����ֳ�
   PROTECT_STACK
   
   MOV AX,WORD PTR NUM
   MOV DX,0
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

;-----------------------------START
   STARTS:
    MOV AX,DATAS
    MOV DS,AX
    
    ;��������
    CALL RESET_BEGIN
    
    PRINTS INPUT_INFO
    
    ;������һ�������������ո���Ϊ�ָ
    ;�ڴ洢��Ԫ����'$'����
    INPUT:
     MOV AH,1
     INT 21H
     
     ;�ǻس���
     CMP AL,0DH
     ;����ѭ��
     JE TONUM
     
     ;�ǿո�
     CMP AL,20H
     JNE ISNEGA
     ;�ָ���
     INC SI
     JMP INPUT
     
    ;�Ǹ��ţ�
    ISNEGA:
     CMP AL,'-'
     JNE NOTNEGA
     MOV ARRAYSTR[SI],'-'
     INC SI
     JMP INPUT
    ;���Ǹ��ŵ������
    NOTNEGA:
     ;��0~9�����֣�
     CMP AL,'0'
     ;���ǣ�����  
     JB ERROR
     CMP AL,'9'  
     JA ERROR
     MOV ARRAYSTR[SI],AL
     INC SI
     JMP INPUT
     
    ;���и�����ӣ���ͳ�Ƹ�������
    TONUM:
     MOV PTRNUM,SI
     ;�����±�
     MOV SI,0
     ;һ�����ֳ��������λ��
     MOV CX,0
     ;����
     MOV BX,1
    TONUMIN:
    
     ;��������±��Ѿ�����PTRNUM������
     CMP PTRNUM,SI
     JB PRINT_ALL
     
     MOV AL,ARRAYSTR[SI]
     CMP AL,'$'
     JE TOSUM
     CMP AL,'-'
     JE ADDNEGA
     ;�������ַ�����ջ
     MOV AH,0
     PUSH AX
     INC SI
     INC CX
     JMP TONUMIN
    ADDNEGA:
     ;�Ǹ���
     MOV SIGN,1
     INC NUM_OF_NEGA
     INC SI
     JMP TONUMIN
    TOSUM:
     ;�Ӹ�λ����ջ
     POP AX
     SUB AL,30H
     MUL BX
     ADD TEMP,AX
     MOV AX,BX
     MOV BX,10
     MUL BX
     MOV BX,AX
     LOOP TOSUM
     ;�Ǹ�����
     CMP SIGN,1
     JNE TOSUMIN
     ;�Ǹ�����SUM+=TEMP������
     MOV AX,TEMP
     ADD SUM,AX
     INC SI
     CALL RESET
     JMP TONUMIN
    ;���Ǹ���������
    TOSUMIN:
     INC SI
     CALL RESET
     JMP TONUMIN
     
    ;���������Ϣ
    PRINT_ALL:
    
     PRINTS NUM_INFO
     PRINT_NUM NUM_OF_NEGA
     NEXTLINE
     
     PRINTS SUM_INFO
     
     ;û�и���Ҳ��û��Ҫ��ӡ����
     CMP NUM_OF_NEGA,0
     JE DO_NOT_PRINTN
     PRINTC '-'
    DO_NOT_PRINTN:
     PRINT_NUM SUM
     NEXTLINE
     
     JMP LETE
    ;���������Ϣ
    ERROR:
     NEXTLINE
     PRINTS WRONG_INFO
     NEXTLINE
     JMP LETE
     
    LETE:
    
    DO_AGAIN
    
;--------------------------------PROC

;���������Ϣ
RESET PROC
	 MOV TEMP,0
     MOV BX,1
     MOV SIGN,0
     RET
RESET ENDP 

;��������
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






















