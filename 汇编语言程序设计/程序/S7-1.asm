DATAS SEGMENT
DATAS ENDS

STACKS SEGMENT
    DW 128 DUP(?)
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    MOV AX,5
    PUSH AX
    CALL FAC
    MOV AH,0
    
    MOV AH,4CH
    INT 21H
    
    FAC PROC
      MOV BP,SP      ;取地址
      MOV AX,[BP+2]  ;取栈顶值
      CMP AX,1      
      JZ RET1
      DEC AX
      PUSH AX        ;继续压栈
      CALL FAC
      MOV BP,SP      ;陆续出栈相乘
      MOV BX,[BP+2]
      MUL BX
      RET 2          ; = SP+4 (DW)
     RET1:
      MOV AX,1
      RET 2
    FAC ENDP
CODES ENDS
    END START



