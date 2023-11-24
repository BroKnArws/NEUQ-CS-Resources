DATAS SEGMENT
    MSG1 DB 'DATE : $'
    MSG2 DB ' TIME : $'
    Y DW ?
    M DB ?
    D DB ?
    H DB ?
    MIN DB ?
    S DB ?
    P DB ?
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    
     ;清屏
    MOV AH,6
	MOV AL,0
	MOV BH,07H  ;黑底白字
	MOV CH,0	;左上(0,0)
	MOV CL,0
	MOV DH,24
	MOV DL,79	;右下(24,79)->25 * 80
	INT 10H
	
	;打开窗口
	MOV AH,6
	MOV AL,0
	MOV BH,70H
	MOV CH,5
	MOV CL,10
	MOV DH,14
	MOV DL,50
	INT 10H
	
	;移动光标到5行10列
	MOV AH,2
	MOV DH,5
	MOV DL,10
	MOV BH,0
	INT 10H
	
    MOV AH,9
    LEA DX,MSG1
    INT 21H
    ;显示日期
    MOV AH,2AH    ;CX->year,DH->month,DL->day,AL->week
    INT 21H
    MOV Y,CX
    MOV M,DH
    MOV D,DL
    MOV BX,Y
    CALL DIS
    CALL SPLIT
    MOV BL,M
    CALL DIS
    CALL SPLIT
    MOV BL,D
    CALL DIS
    
    MOV AH,9
    LEA DX,MSG2
    INT 21H
    
    MOV AH,2CH		;CH->hour,CL->minute,DH->second,DL->millsecond
	INT 21H
	MOV H,CH
	MOV MIN,CL
	MOV S,AH
	MOV P,AL
	;显示时间
	MOV BH,0
	MOV BL,H
    CALL DIS
    CALL DOT
	MOV BL,MIN
    CALL DIS
    CALL DOT
    MOV BL,S
    CALL DIS
    CALL DOT
    MOV BL,P
    CALL DIS

    
    MOV AH,2CH
    INT 21H
    
    MOV AH,4CH
    INT 21H
    
   DIS PROC
     PUSH AX
     PUSH BX
     PUSH CX
     PUSH DX
     
     MOV AX,BX
	 MOV CX,0
	 MOV BX,10
	 LET1:		;十进制表示
	 MOV DX,0
	 INC CX		
	 IDIV BX	;÷10
	 PUSH DX	;DX是余数，入栈
	 CMP AX,0
	 JNZ LET1
	 LET2:		;弹出栈显示余数
	 POP AX
	 ADD AX,30H
	 MOV DL,AL
	 MOV AH,2
	 INT 21H
	 LOOP LET2
	 
	 POP DX
	 POP CX
	 POP BX
	 POP AX
	 MOV BX,0
	 RET
   DIS ENDP
   
   SPLIT PROC
   	 PUSH AX
   	 PUSH DX
   	 
     MOV DL,'/'
   	 MOV AH,2
   	 INT 21H
   	 
   	 POP DX
   	 POP AX
   	 RET
   SPLIT ENDP
   
   DOT PROC
   	PUSH AX
   	 PUSH DX
   	 
     MOV DL,':'
   	 MOV AH,2
   	 INT 21H
   	 
   	 POP DX
   	 POP AX
   	 RET
   DOT ENDP
CODES ENDS
    END START




