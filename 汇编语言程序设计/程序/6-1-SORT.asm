;-----ð����������-----
PUBLIC SORT
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
	SORT PROC
	 PUSH AX
	 PUSH BX
	 PUSH CX
	 PUSH DX
	
	 MOV CX,P
	 DEC CX
	 LOOPS1:
	 PUSH CX
	 MOV BX,0
	 LOOPS2:
	 MOV AX,SCOREN[BX]
	 MOV DX,RANK[BX]
	 CMP AX,SCOREN[BX+2]
	 JGE NEXTS
	 ;ͨ���Ƚ�SCORE���ı�RANK�Ĵ����������
	 XCHG AX,SCOREN[BX+2]
	 MOV SCOREN[BX],AX
	 XCHG DX,RANK[BX+2]
	 MOV RANK[BX],DX
	 NEXTS:
	 ADD BX,2
	 LOOP LOOPS2
	 POP CX
	 LOOP LOOPS1
	 POP DX
	 POP CX
	 POP BX
	 POP AX
	 RET
	SORT ENDP
CODES ENDS
END








