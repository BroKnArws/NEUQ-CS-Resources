DATAS SEGMENT
    BUF DB 20,?,20 DUP(0)
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    
    LEA DX,BUF
    
    MOV AH,10
    INT 21H
    
    ;获取填入的字符个数
    MOV BL,BUF[1]
    ;BH重置为0
    MOV BH,0
    ;因为BUF[0][1]都有填字，因此需要移动到末尾
    ADD BX,2
    ;末尾添加终止符
    MOV BUF[BX],'$'
    MOV BUF[0],0AH
    MOV BUF[1],0DH
    ;再次输出缓冲区
    LEA DX,BUF
    MOV AH,9
    INT 21H
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START

