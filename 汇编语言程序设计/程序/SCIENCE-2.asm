DATAS SEGMENT
    SCORE DW 100,98,96,97,95
    	  DW 100,98,96,95,94
DATAS ENDS

;[OEH] -> 96

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    
    ;直接寻址
    MOV DX,DS:[0EH]   ;7 X 2 = 14 = 0EH
    
    ;寄存器间接寻址
    MOV BX,0EH
    MOV DX,DS:[BX]
    
    ;寄存器相对寻址
    MOV SI,0EH
    MOV DX,SCORE[SI]
    
    ;基址变址寻址
    LEA BX,SCORE
    MOV SI,0EH
    MOV DX,[BX][SI]  ; OR MOV DX,[BX+SI]
    
    ;相对基址变址寻址
    MOV BX,10       ; 5 X 2 = 10
    MOV SI,4		 ; 2 X 2 = 4
    MOV DX,SCORE[BX][SI]
    
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START


