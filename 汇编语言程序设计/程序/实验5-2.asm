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
    OUTS0:		;外层循环
  	MOV SN,0
  	PUSH CX		;暂存CX
  	MOV CX,8 
  	
  	INS0:       ;内层循环
  	;BX = CN * 8
  	;SI = SN
  	MOV AX,CN    ; = MOV AL,CN
  	MOV DL,8
  	MUL DL		 ;AX = CN * 8
  	MOV BX,AX
  	MOV SI,SN
  	
  	CMP SCORE[BX][SI],90   
  	JB FLUNK               ; 小于 90 分？
  	MOV AL,SCORE[BX][SI]
  	MOV MAX[DI],AL
  	INC DI
  	
  	FLUNK:
  	CMP SCORE[BX][SI],60
  	JAE INS1               ; 大于 60 分？  
  	MOV AL,SCORE[BX][SI]
  	MOV MIN[BP],AL
  	INC BP
  	
  	INS1:
  	INC SN
  	LOOP INS0		;继续内层循环
  	POP CX          ;弹出外层循环的CX
  	
  	OUTS1:
  	INC CN          
  	LOOP OUTS0		;继续外层循环
  	
  	; DI -> 优秀人数 BP -> 不及格人数
  	DEC DI
  	DEC BP
  	;---- 冒泡排序 优秀组
  	MOV CX,DI         ;排 CX 趟
  	OUT2:
  	PUSH CX			  
  	MOV SI,0		  
  	
  	OUT3:
  	MOV AL,MAX[SI]
  	CMP AL,MAX[SI+1]
  	JAE NEXT          ;降序排序
  	XCHG AL,MAX[SI+1] ;交换顺序
  	MOV MAX[SI],AL
  	
  	NEXT:
  	INC SI           
  	LOOP OUT3
  	
  	POP CX
  	LOOP OUT2
  	;---- 冒泡排序 不及格组
  	MOV CX,BP
  	OUT4:
  	PUSH CX			  ;排 CX 趟
  	MOV SI,0		  
  	
  	OUT5:
  	MOV AL,MIN[SI]
  	CMP AL,MIN[SI+1]
  	JAE NEXT2          ;降序
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








