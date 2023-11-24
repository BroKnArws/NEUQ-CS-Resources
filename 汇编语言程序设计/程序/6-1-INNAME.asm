;-----姓名处理-----
PUBLIC INNAME
INCLUDE PACK.mac

DATAS SEGMENT COMMON 'DATA'

   P EQU 5    ;学生数
   NL EQU 15  ;NAME 完整长度
   SL EQU 4   ;SCORE 完整长度
   NL1 EQU 13 ;NAME 实际长度
   TEMP1 DB 0 ;存放实时学号
   TEMP2 DB 1

   NAMEA DB P DUP(NL1,?,NL1 DUP('$'))  ;存入5个名字且名字长度小于11
   SCOREASC DB P DUP(SL DUP('$'))   ;存入5个成绩，每个成绩（3字节）以$结尾
   RANK DW 0,1,2,3,4    ;相当于NAMEA和SCOREASC数组下标
   SCOREN DW 5 DUP(0)   ;存放数值以及排序完成的成绩
    
   X DB 3 DUP(?)   ; 存放0-255的数据
DATAS ENDS

ASSUME CS:CODES,DS:DATAS

CODES SEGMENT PUBLIC 'CODE'
	INNAME PROC

	 PUSH AX
	 PUSH BX
	 PUSH CX
	 PUSH DX
	 
	 MOV AL,TEMP1 ; TEMP1 用于标注当前输入同学序号
	 
	 ;NAMEA[N] -> RANK * NL + NAMEA 
	 MOV CL,NL     
	 MUL CL
	 LEA DX,NAMEA
	 ADD DX,AX
	 
	 ;输入
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




