;-----�ɼ�����-----
PUBLIC INSCORE
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
	INSCORE PROC
	 PUSH AX
	 PUSH BX
	 PUSH CX
	 PUSH DX
	 PUSH SI
	 PUSH DI
	 PUSH BP 
	 
     MOV AH,2
     MOV DL,0AH
     INT 21H
     MOV DL,0DH
     INT 21H
     
     MOV AL,TEMP1
	 MOV CL,SL
	 MUL CL
	 LEA BP,SCOREASC
	 ADD BP,AX      ;SCOREASC[N] -> RANK * SL + SCOREASC
    
	 ; ��ʼ��
	 MOV SI,0
	 
	 ; ---���������ַ�
	 
	 LET0:
	 MOV AH,1     ; �����ַ�
	 INT 21H
	 CMP AL,0DH
	 JE LET1
	 MOV DS:[BP],AL ;����SCOREASC
	 SUB AL,30H 
	 MOV X[SI],AL
	 INC SI 
	 INC BP
	 JMP LET0      
	 
	 LET1:
	
	 ; ��ʼ��
	 MOV DI,0
	 MOV BX,0
	 ;--- ���ִ���
	
	 CMP SI,1     ;�� һλ��?
	 JE LET2
	
	 CMP SI,2     ;�� ��λ��?
	 JE LET3
	
	 MOV AL,X[DI] ;����λ����
	 MOV CL,100
	 MUL CL
	
	 ADD BX,AX
	 INC DI
	
	 ;�ڶ�λ����
	 LET3:
	 MOV AL,X[DI]
	 MOV CL,10
	 MUL CL
	
	 ADD BX,AX
	 INC DI
	
	 ;��һλ����
	 LET2:
	 MOV AL,X[DI]
	 MOV AH,0
	 ADD BX,AX
	
	 ; SCOREN + TEMP1 * 2
	 MOV AL,TEMP1
	 MOV CL,2
	 MUL CL
	 MOV AH,0
	 MOV BP,AX
	 MOV SCOREN[BP],BX ;����SCOREN
	
	 POP BP
	 POP DI
	 POP SI
	 POP DX
	 POP CX
	 POP BX
	 POP AX
	 RET
	 
	INSCORE ENDP
CODES ENDS
END











