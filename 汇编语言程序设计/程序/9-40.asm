CODES SEGMENT
    ASSUME CS:CODES
START:
    
    ;��80H���жϷ�����������
    LEA DX,OUTPUTSTART
    MOV AX,SEG OUTPUTSTART
    MOV DS,AX
    MOV AL,80H
    MOV AH,25H
    INT 21H
    
    INT 80H
    
    ;�ж�פ��
    MOV AH,31H
    MOV AL,0
    MOV DX,OUTPUTEND-OUTPUTSTART+16
    
    MOV AH,4CH
    INT 21H
    
    ;�жϳ���
    OUTPUTSTART:
    JMP CODE
    NUMBERS DB ' ',9,8,7,6,5,4,3,2,1
    COLOR DB 3DH
    CODE:
    
    ;�ֳ�����
    PUSH DS
    PUSH DX
    PUSH AX
    PUSH CS
    POP DS
    
    ;д�Դ�
	MOV BX,0B800H
	MOV ES,BX
	MOV BX,1
	MOV CX,9  ;9�����ָı���ɫ
	S:
	MOV AH,2
	MOV SI,CX
	MOV DL,NUMBERS[SI]
	ADD DL,30H
	INT 21H
	MOV AL,COLOR
	ADD BYTE PTR ES:[BX],AL
	ADD AL,3DH		;��һ���ַ���ɫ
	MOV COLOR,AL
	ADD BX,2
	LOOP S
    
    ;�ֳ��ָ�
    POP AX
    POP DX
    POP DS
    IRET
    OUTPUTEND:NOP
CODES ENDS
    END START

