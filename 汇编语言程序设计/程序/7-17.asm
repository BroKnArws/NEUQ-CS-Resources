DATAS SEGMENT
    NUM DB 0
    NUMSTR DB 10 DUP(?)
    P DB 1  ;乘数
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    CALL INPUT  ;输入数字
    CALL TOD    ;十进制处理
    MOV AH,4CH
    INT 21H
    
    INPUT PROC
      PUSH AX
      MOV SI,0
     LET0:
     ;先以字符串保存
      MOV AH,1
      INT 21H
      CMP AL,0DH
      JE LET1
      MOV NUMSTR[SI],AL
      INC SI
      JMP LET0
     LET1:
      POP AX
      RET
    INPUT ENDP
    
    TOD PROC
      PUSH AX
      DEC SI
     LET2:
      CMP SI,-1
      JE LET3
      ;逐位乘法相加
      MOV AL,NUMSTR[SI]  
      SUB AL,30H
      MOV BL,P
      IMUL BL
      ADD NUM,AL
      MOV AL,P
      MOV BL,10
      MUL BL
      MOV P,AL
      DEC SI
      JMP LET2
     LET3:
      POP AX
      RET
    TOD ENDP
   
CODES ENDS
    END START




