DATAS SEGMENT
   NUM DW 1110011011011101B
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    MOV BX,NUM
    MOV CX,4        ;16位取4次
    BEG:
    CALL TOHEX      ;转16进制字符
    CALL DIS        ;输出
    LOOP BEG
    MOV AH,4CH
    INT 21H
   	
   	TOHEX PROC
      PUSH CX
      
   	  MOV CL,4
   	  ROL BX,CL     ;最高四位移到底部
   	  MOV AX,BX
   	  AND AL,0FH    ;取低四位
   	  ADD AL,30H
   	  CMP AL,3AH    ;16进制字符
   	  JL LET0
   	  ADD AL,7H
   	 LET0:
   	  POP CX
   	  RET
   	TOHEX ENDP
   	
   	DIS PROC
   	  PUSH CX
   	  PUSH AX
   	  
   	  MOV DL,AL
   	  MOV AH,2
   	  INT 21H
   	  
   	  POP AX
   	  POP CX
   	  RET
   	DIS ENDP
CODES ENDS
    END START

