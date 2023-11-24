DATAS SEGMENT
   SCORE DB 23,95,89,34,67,88,25,90
   		 DB 33,60,88,92,93,66,57,89
   		 DB 89,90,91,92,88,87,66,55
   MAX DB 20 DUP(?)
   MIN DB 20 DUP(?)
   CN DW 0    ;CN,SN -> SCORE[CN][SN] 
   SN DW 0 
   
DATAS ENDS

STACKS SEGMENT
	DW 10 DUP(0)
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    MOV AX,STACKS
    MOV SS,AX
    MOV SP,20
    
    MOV DI,0
    MOV BP,0
    
    MOV CX,3
    OUTS0:		;���ѭ��
  	MOV SN,0
  	PUSH CX		;�ݴ�CX
  	MOV CX,8 
  	
  	INS0:       ;�ڲ�ѭ��
  	;BX = CN * 8
  	;SI = SN
  	MOV AX,CN    ; = MOV AL,CN
  	MOV DL,8
  	MUL DL		 ;AX = CN * 8
  	MOV BX,AX
  	MOV SI,SN
  	
  	CMP SCORE[BX][SI],90   
  	JB FLUNK               ; С�� 90 �֣�
  	MOV AL,SCORE[BX][SI]
  	MOV MAX[DI],AL
  	INC DI
  	
  	FLUNK:
  	CMP SCORE[BX][SI],60
  	JAE INS1               ; ���� 60 �֣�  
  	MOV AL,SCORE[BX][SI]
  	MOV MIN[BP],AL
  	INC BP
  	
  	INS1:
  	INC SN
  	LOOP INS0		;�����ڲ�ѭ��
  	POP CX          ;�������ѭ����CX
  	
  	OUTS1:
  	INC CN          
  	LOOP OUTS0		;�������ѭ��
  	
  	; DI -> �������� BP -> ����������
  	DEC DI
  	DEC BP
  	;---- ð������ ������
  	MOV CX,DI         ;�� CX ��
  	OUT2:
  	PUSH CX			  
  	MOV SI,0		  
  	
  	OUT3:
  	MOV AL,MAX[SI]
  	CMP AL,MAX[SI+1]
  	JAE NEXT          ;��������
  	XCHG AL,MAX[SI+1] ;����˳��
  	MOV MAX[SI],AL
  	
  	NEXT:
  	INC SI           
  	LOOP OUT3
  	
  	POP CX
  	LOOP OUT2
  	;---- ð������ ��������
  	MOV CX,BP
  	OUT4:
  	PUSH CX			  ;�� CX ��
  	MOV SI,0		  
  	
  	OUT5:
  	MOV AL,MIN[SI]
  	CMP AL,MIN[SI+1]
  	JAE NEXT2          ;����
  	XCHG AL,MIN[SI+1]
  	MOV MIN[SI],AL
  	
  	NEXT2:
  	INC SI
  	LOOP OUT5
  	
  	POP CX
  	LOOP OUT4
  	
  	
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START








