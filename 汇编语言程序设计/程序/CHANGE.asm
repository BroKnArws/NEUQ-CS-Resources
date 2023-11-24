DATAS SEGMENT

	X DB 3 DUP(?)   ; 存放0-255的数据
	INFO DB 0AH,0DH,'DEC = $' ; 提示信息
	INFO1 DB 0AH,0DH,'HEX = $'     
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    
    ; 输出提示信息
    LET:
    LEA DX,INFO
    MOV AH,9
    INT 21H
    
    ; 初始化
    MOV SI,0
    
   	; ---输入数字字符
   	
    LET0:
    MOV AH,1     ; 输入字符
    INT 21H

    CMP AL,1BH   ; 是 ESC?
    JE LET5
    
    CMP AL,0DH   ; 是 回车?
    JE LET1
    
    SUB AL,30H   ; 转数字
    MOV X[SI],AL
    INC SI 
    JMP LET0      
    
    LET1:
    
    ; 输出提示信息
    LEA DX,INFO1
    MOV AH,9
    INT 21H	 
    
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
    
    ; --- 转为16位
    
    MOV AX,BX
    MOV CL,16
    DIV CL
    MOV BX,AX    ;保存余数->BH，商->BL
    CMP BL,9     ;商≤ 9 ?
    JBE LET6
    ADD BL,7	 ;转16进制字母
    
    ;--- 输出字符
    
    LET6:
    
    ;先输出商
    ADD BL,30H
    MOV DL,BL
    MOV AH,2
    INT 21H
    CMP BH,9
    JBE LET7
    ADD BH,7
    
    LET7:
    ;再输出余数
    ADD BH,30H
    MOV DL,BH
    MOV AH,2
    INT 21H
    
    JMP LET      ; 返回重新输入

	; 结束
    LET5:
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START


