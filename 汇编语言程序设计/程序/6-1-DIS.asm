;-----�����Ϣ-----
PUBLIC DIS
INCLUDE PACK.mac

DATAS SEGMENT COMMON 'DATA'

   P EQU 5    ;ѧ����
   NL EQU 15  ;NAME ��������
   SL EQU 4   ;SCORE ��������
   NL1 EQU 13 ;NAME ʵ�ʳ���
   TEMP1 DB 0 ;���ʵʱѧ��
   TEMP2 DB 1

   NAMEA DB P DUP(NL1,?,NL1 DUP('$'))  ;����5�����������ֳ���С��11
   SCOREASC DB P DUP(SL DUP('$'))   ;����5���ɼ���ÿ���ɼ���3�ֽڣ���$��β
   RANK DW 0,1,2,3,4    ;�൱��NAMEA��SCOREASC�����±�
   SCOREN DW 5 DUP(0)   ;�����ֵ�Լ�������ɵĳɼ�
    
   X DB 3 DUP(?)   ; ���0-255������
DATAS ENDS

ASSUME CS:CODES,DS:DATAS

CODES SEGMENT PUBLIC 'CODE'
	DIS PROC
	
	 PUSH_STACK
	
	 MOV BX,0
	 MOV CX,P
	 MOV TEMP2,1
	
	 ;����RANK������������ͳɼ�
	 LOOPDIS:
	 ADD TEMP2,30H
	 PRINT_CHAR TEMP2
	 PRINT_CHAR ':'
	 ;����ƫ�Ƶ�ַ���������
	 MOV AX,RANK[BX]
	
	 MOV DL,NL
	 MUL DL
	 PRINT_STRING NAMEA,AX
	 LINE_BREAK
	 ENTER
	
	 ;����ƫ�Ƶ�ַ������ɼ�
	 MOV AX,RANK[BX]
	 MOV DL,SL
	 MUL DL
	 PRINT_STRING SCOREASC,AX
	 LINE_BREAK
	 ENTER
	
	 ADD BX,2
	 SUB TEMP2,30H
	 INC TEMP2
	
	 LINE_BREAK
	 ENTER
	 LOOP LOOPDIS
	
	 POP_STACK
	 RET
	
	DIS ENDP

CODES ENDS
END














