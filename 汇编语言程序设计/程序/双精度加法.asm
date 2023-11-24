;双精度的加法运算
DATAS SEGMENT
    X DW 5D68H,2012H
    Y DW 49A6H,1003H
    Z DW 2 DUP(?)
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
    
START:
    MOV AX,DATAS
    MOV DS,AX
    
    ;进位加
    MOV AX,X
    ADD AX,Y
    MOV Z,AX
    
    ;带进位加
    MOV BX,X+2
    ADC BX,Y+2
    MOV Z+2,BX  
    
    ;输出
    MOV AX,SEG Z
    MOV DS,AX
    MOV DX,OFFSET Z
    
    
    MOV AH,9
    INT 21H
    
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START






