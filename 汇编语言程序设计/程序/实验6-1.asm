DATAS SEGMENT

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

STACKS SEGMENT
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    MOV CX,P   ;ѭ��������Ϣ
    LOOPM:
	CALL INNAME   ;��������
	CALL INSCORE  ;����ɼ�
    INC TEMP1
    LOOP LOOPM
    CALL SORT     ;����
    CALL DIS      ;��ʾ�ɼ�
    
    MOV AH,4CH
    INT 21H
    
    ;-----��������-----
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
	    
	;-----�ɼ�����-----
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
	
	;-----ð����������-----
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
	
	;-----�����Ϣ-----
	DIS PROC
	
	 PUSH AX
	 PUSH BX
	 PUSH CX
	 PUSH DX
	
	 MOV BX,0
	 MOV CX,P
	 MOV TEMP2,1
	
	 ;����RANK������������ͳɼ�
	 LOOPDIS:
	 ADD TEMP2,30H
	 MOV DL,TEMP2
	 MOV AH,2
	 INT 21H
	 MOV DL,':'
	 MOV AH,2
	 INT 21H
	 ;����ƫ�Ƶ�ַ���������
	 MOV AX,RANK[BX]
	
	 MOV DL,NL
	 MUL DL
	 LEA DX,NAMEA
	 ADD DX,AX
	 MOV AH,9
	 INT 21H
	 MOV DL,0AH
	 MOV AH,2
	 INT 21H
	 MOV DL,0DH
	 MOV AH,2
	 INT 21H
	
	 ;����ƫ�Ƶ�ַ������ɼ�
	 MOV AX,RANK[BX]
	 MOV DL,SL
	 MUL DL
	 LEA DX,SCOREASC
	 ADD DX,AX
	 MOV AH,9
	 INT 21H
	 MOV DL,0AH
	 MOV AH,2
	 INT 21H
	 MOV DL,0DH
	 MOV AH,2
	 INT 21H
	
	 ADD BX,2
	 SUB TEMP2,30H
	 INC TEMP2
	
	 MOV DL,0AH
	 MOV AH,2
	 INT 21H
	 MOV DL,0DH
	 INT 21H
	 LOOP LOOPDIS
	
	 POP DX
	 POP CX
	 POP BX
	 POP AX
	 RET
	
	DIS ENDP
CODES ENDS
    END START







