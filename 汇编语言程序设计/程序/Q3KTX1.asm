;---------- �� 3 ---------------

;3.	��д90H������жϳ���
;�ڵڣ�10����**���༶���к�Ϊ35��**�в�ɫ��ʾ�������
;(ע��Ҫ���ж�פ�����дӵ�0�п�ʼ���㣬�дӵ�0�п�ʼ����)��

;-----------------------------

DATAS SEGMENT
DATAS ENDS

STACKS SEGMENT
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    
    ;��90H���жϷ�����������
    LEA DX,OUTPUTSTART
    MOV AX,SEG OUTPUTSTART
    MOV DS,AX
    MOV AL,90H
    MOV AH,25H
    INT 21H
    
    ;�ж�פ��
    MOV AH,31H
    MOV AL,0
    MOV DX,OUTPUTEND-OUTPUTSTART+16
    
    ;����90H���ж�
    INT 90H
    
    MOV AH,4CH
    INT 21H
    
    ;�жϳ���
    OUTPUTSTART:
    
    JMP CODE
    ;����
    MYNAME DB 'KONGTIANXIN'
    ;��ɫ
    COLOR DB 1EH
    CODE:
    
    ;�ֳ�����
    PUSH DS
    PUSH DX
    PUSH AX
    PUSH CS
    POP DS
    
    ;�ƶ���굽10��35��
	MOV AH,2
	MOV DH,10
	MOV DL,35
	MOV BH,0
	INT 10H
    
    ;д�Դ�
	MOV BX,0B800H
	MOV ES,BX
	;�У�A0H * AH = 640H
	MOV BX,640H
	;�� 2H * 23H(35D) = 46H
	MOV DI,46H
	;���ֵĳ�����Ϊѭ��
	MOV CX,DWORD PTR COLOR-MYNAME
	MOV SI,0
	PAINT:
	;����ַ�
	MOV AH,2
	MOV DL,MYNAME[SI]
	INC SI
	INT 21H
	MOV AL,COLOR
	;��ɫ�����ַ�������
	ADD BYTE PTR ES:[BX+1+DI],AL
	;��һ���ַ�����ɫ
	ADD AL,3H		
	MOV COLOR,AL
	;��һ������λ��
	ADD BX,2
	LOOP PAINT
    
    ;�ֳ��ָ�
    POP AX
    POP DX
    POP DS
    IRET
    OUTPUTEND:NOP
CODES ENDS
    END START











