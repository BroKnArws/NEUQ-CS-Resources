;-----��������-----
PUBLIC INNAME
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
	INNAME PROC

	 PUSH AX
	 PUSH BX
	 PUSH CX
	 PUSH DX
	 
	 MOV AL,TEMP1 ; TEMP1 ���ڱ�ע��ǰ����ͬѧ���
	 
	 ;NAMEA[N] -> RANK * NL + NAMEA 
	 MOV CL,NL     
	 MUL CL
	 LEA DX,NAMEA
	 ADD DX,AX
	 
	 ;����
	 MOV AH,10
	 INT 21H
	 
	 MOV BX,DX
	 MOV BYTE PTR [BX],0AH
	 INC BX
	 MOV BYTE PTR [BX],0DH
	 
	 POP DX
	 POP CX
	 POP BX
	 POP AX
	 RET
	 
	INNAME ENDP
CODES ENDS
END




