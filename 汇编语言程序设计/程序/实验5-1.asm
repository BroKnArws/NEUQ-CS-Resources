DATAS SEGMENT
   SCORE DB 23,95,89,34,67,88,25,90
   		 DB 33,60,88,92,93,66,57,89
   		 DB 89,90,91,92,88,87,66,55
   MAX DB 3 DUP(0)
   MIN DB 3 DUP(0)
   CN DW 0
   SN DW 0
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    
    OUTS0:
    CMP CN,3		;外层循环
  	JAE EXIT
  	MOV SN,0
  	INS0:
  	CMP SN,8        ;内层循环
  	JAE OUTS1
  	;BX = CN * 8
  	;SI = SN
  	MOV AX,CN    ;MOV AL,CN
  	MOV DL,8
  	MUL DL		 ;AX = CN * 8
  	MOV BX,AX
  	MOV SI,SN
  	
  	CMP SCORE[BX][SI],90   
  	JB FLUNK           ; 小于 90 分？
  	MOV DI,CN
  	INC MAX[DI]
  	
  	FLUNK:
  	CMP SCORE[BX][SI],60
  	JAE INS1               ; 大于 60 分？  
  	MOV DI,CN
  	INC MAX[DI]     
  	
  	INS1:
  	INC SN
  	JMP INS0
  	
  	OUTS1:
  	INC CN
  	JMP OUTS0
  	
  	EXIT:
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START


