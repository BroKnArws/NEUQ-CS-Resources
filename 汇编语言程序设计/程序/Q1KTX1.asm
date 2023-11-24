;---------- �� 1 ---------------

;��д���򡣴Ӽ�������һ����λʮ��������
;���������ƽ����

;-----------------------------
INCLUDE QPACK.MAC
DATAS SEGMENT
	;�ַ�����ʽ��ʮ��������
    NUMSTR DB 3 DUP(?)
    ;��ֹNUMSTR�������
    BUFF_USELESS DB 32 DUP(0)
    WRONG_INFO DB 'Not A Number!$'
    WRONG_INFO_OVER DB 'Only Two Digits Are Allowed!$'
    ;�ַ�ת���ֵı���
    NUMBER DB 0
    INPUT_INFO DB 'Please enter 2 decimal digits: $'
    OUTPUT_INFO DB 'The Binary number is: $'
    TIPS_INFO DB 'Do You Want To Repeat Again ?[y/n] $'
DATAS ENDS

STACKS SEGMENT
	;��Ŷ�����λ���Ķ�ջ
    DW 16 DUP(?)
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:

;------------------------------------START
   STARTS:
    MOV AX,DATAS
    MOV DS,AX
    MOV AX,STACKS
    MOV SS,AX
    
    ;��������
    CALL RESET_BEGIN
    
    ;�����ʾ��Ϣ
    PRINTS INPUT_INFO
    
   ;����2λ����ʮ��������
   INPUT:
    MOV AH,1
    INT 21H
    MOV NUMSTR[SI],AL
    INC SI
    CMP AL,0DH
    JNE INPUT
    
    ;�ж��ַ��Ƿ�������,������Ǳ���
    CALL JUDGE_IS_NUM
    
    ;תΪʮ��������
    TOD:
     ;SI:1->2λ
     MOV SI,1
     MOV BL,1
    TODIN:
     CMP SI,-1
     JE TOB
     ;�Ǹ�λ����
     MOV AL,NUMSTR[SI]
     DEC SI
     CMP AL,0DH
     JE TODIN
     ;��λ���
     SUB AL,30H
     MUL BL
     ADD NUMBER,AL
     MOV AL,BL
     MOV BH,10
     MUL BH
     MOV BL,AL
     JMP TODIN
     
    ;תΪ������
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
     ;������ջ���̽�����һ��ѭ��
     PUSH AX
     INC CX
     MOV AL,BL
     JMP TOBIN
    
    ;8λ����
    FILL:
     MOV BX,8
     SUB BX,CX
     MOV CX,BX
    FILLIN:
     MOV AX,0
     PUSH AX
     LOOP FILLIN
     
     ;�����ʾ��Ϣ
     PRINTS OUTPUT_INFO
     
     MOV CX,8
    ;������ջ�������������
    SHOW:
     POP AX
     MOV DL,AH
     ADD DL,30H
     PRINTC DL
    LOOP SHOW
     NEXTLINE
     JMP LETEND
     
   ;�����֣����������Ϣ
   ERROR:
    PRINTS WRONG_INFO
    NEXTLINE
    JMP LETEND
   ;�ַ������ȴ���2������
   ERROR_OVER:
    PRINTS WRONG_INFO_OVER
    NEXTLINE
    
   ;�ظ�����
   LETEND: 
    DO_AGAIN
;---------------------------------------PROC

 ;�ж��ַ��Ƿ�������,������Ǳ���
JUDGE_IS_NUM PROC

	PROTECT_STACK
	
	;ֻ��������2λ������ֱ�ӱ���
	CMP SI,3
	JA ERROR_OVER

	MOV SI,0
    MOV CX,2
   JUDGE:
    MOV AL,NUMSTR[SI]
    CMP SI,0
    JNE JUDGE_IN
    ;��һ���ַ��ǻس���
    CMP AL,0DH
    JE ERROR
   JUDGE_IN:
    INC SI
    ;�ǻس���
    CMP AL,0DH
    JE TOD
    ;��0~9�����֣�
    CMP AL,'0'  
    JB ERROR
    CMP AL,'9'  
    JA ERROR
    LOOP JUDGE
    
    RECOVER_STACK
    
    RET
    
JUDGE_IS_NUM ENDP

;��������
RESET_BEGIN PROC
    MOV AX,0
    MOV SI,0
    MOV NUMBER,0
    RET
RESET_BEGIN ENDP

CODES ENDS
    END START













