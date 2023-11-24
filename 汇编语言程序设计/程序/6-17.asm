DATAS SEGMENT
	VALUE DW 1,-1,2,-3,2,3,3,-1
    N DB ?
    NUM DB 0
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    
    ;计算数组长度
    MOV AL,N-VALUE
    MOV BL,2
    MOV AH,0
    IDIV BL
    MOV AH,0
    MOV CX,AX
    
    MOV BP,0
    
    ;遍历判断是否为负
    LET0:
    CMP VALUE[BP],0
    JGE LET1
    INC NUM
    
    LET1:
    ADD BP,2
    LOOP LET0
    
    ;保存到AX中
    MOV AL,NUM
   	MOV AH,0
	
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START
