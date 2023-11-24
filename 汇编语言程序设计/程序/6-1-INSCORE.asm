;-----成绩处理-----
PUBLIC INSCORE
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
    
	 ; 初始化
	 MOV SI,0
	 
	 ; ---输入数字字符
	 
	 LET0:
	 MOV AH,1     ; 输入字符
	 INT 21H
	 CMP AL,0DH
	 JE LET1
	 MOV DS:[BP],AL ;存入SCOREASC
	 SUB AL,30H 
	 MOV X[SI],AL
	 INC SI 
	 INC BP
	 JMP LET0      
	 
	 LET1:
	
	 ; 初始化
	 MOV DI,0
	 MOV BX,0
	 ;--- 数字处理
	
	 CMP SI,1     ;是 一位数?
	 JE LET2
	
	 CMP SI,2     ;是 二位数?
	 JE LET3
	
	 MOV AL,X[DI] ;第三位处理
	 MOV CL,100
	 MUL CL
	
	 ADD BX,AX
	 INC DI
	
	 ;第二位处理
	 LET3:
	 MOV AL,X[DI]
	 MOV CL,10
	 MUL CL
	
	 ADD BX,AX
	 INC DI
	
	 ;第一位处理
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
	 MOV SCOREN[BP],BX ;存入SCOREN
	
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











