DATAS SEGMENT
   NUM DW 1110011011011101B
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    MOV BX,NUM
    MOV CX,4        ;16λȡ4��
    BEG:
    CALL TOHEX      ;ת16�����ַ�
    CALL DIS        ;���
    LOOP BEG
    MOV AH,4CH
    INT 21H
   	
   	TOHEX PROC
      PUSH CX
      
   	  MOV CL,4
   	  ROL BX,CL     ;�����λ�Ƶ��ײ�
   	  MOV AX,BX
   	  AND AL,0FH    ;ȡ����λ
   	  ADD AL,30H
   	  CMP AL,3AH    ;16�����ַ�
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

