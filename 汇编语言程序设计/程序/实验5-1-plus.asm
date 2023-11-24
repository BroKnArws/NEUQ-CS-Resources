DATAS SEGMENT
   SCORE DB 23,95,89,34,67,88,25,90
   		 DB 33,60,88,92,93,66,57,89
   		 DB 89,90,91,92,88,87,66,55
   MAX DB 3 DUP(0)
   MIN DB 3 DUP(0)
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
  	JB FLUNK           ; С�� 90 �֣�
  	MOV DI,CN
  	INC MAX[DI]
  	
  	FLUNK:
  	CMP SCORE[BX][SI],60
  	JAE INS1               ; ���� 60 �֣�  
  	MOV DI,CN
  	INC MIN[DI]     
  	
  	INS1:
  	INC SN
  	LOOP INS0		;�����ڲ�ѭ��
  	POP CX          ;�������ѭ����CX
  	
  	OUTS1:
  	INC CN             
  	LOOP OUTS0		;�������ѭ��
  	
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START



