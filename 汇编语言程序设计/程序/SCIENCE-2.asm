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
    
    ;ֱ��Ѱַ
    MOV DX,DS:[0EH]   ;7 X 2 = 14 = 0EH
    
    ;�Ĵ������Ѱַ
    MOV BX,0EH
    MOV DX,DS:[BX]
    
    ;�Ĵ������Ѱַ
    MOV SI,0EH
    MOV DX,SCORE[SI]
    
    ;��ַ��ַѰַ
    LEA BX,SCORE
    MOV SI,0EH
    MOV DX,[BX][SI]  ; OR MOV DX,[BX+SI]
    
    ;��Ի�ַ��ַѰַ
    MOV BX,10       ; 5 X 2 = 10
    MOV SI,4		 ; 2 X 2 = 4
    MOV DX,SCORE[BX][SI]
    
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START


