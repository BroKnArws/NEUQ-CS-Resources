DATAS SEGMENT

	X DB 3 DUP(?)   ; ���0-255������
	INFO DB 0AH,0DH,'DEC = $' ; ��ʾ��Ϣ
	INFO1 DB 0AH,0DH,'HEX = $'     
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    
    ; �����ʾ��Ϣ
    LET:
    LEA DX,INFO
    MOV AH,9
    INT 21H
    
    ; ��ʼ��
    MOV SI,0
    
   	; ---���������ַ�
   	
    LET0:
    MOV AH,1     ; �����ַ�
    INT 21H

    CMP AL,1BH   ; �� ESC?
    JE LET5
    
    CMP AL,0DH   ; �� �س�?
    JE LET1
    
    SUB AL,30H   ; ת����
    MOV X[SI],AL
    INC SI 
    JMP LET0      
    
    LET1:
    
    ; �����ʾ��Ϣ
    LEA DX,INFO1
    MOV AH,9
    INT 21H	 
    
    ; ��ʼ��
    MOV DI,0
    MOV BX,0
    
    ;--- ���ִ���
    
    CMP SI,1     ;�� һλ��?
    JE LET2
    
    CMP SI,2     ;�� ��λ��?
    JE LET3
    
    MOV AL,X[DI] ;����λ����
    MOV CL,100
    MUL CL
    
    ADD BX,AX
    INC DI
    
    ;�ڶ�λ����
    LET3:
    MOV AL,X[DI]
    MOV CL,10
    MUL CL
    
    ADD BX,AX
    INC DI
    
    ;��һλ����
    LET2:
    MOV AL,X[DI]
    MOV AH,0
    ADD BX,AX
    
    ; --- תΪ16λ
    
    MOV AX,BX
    MOV CL,16
    DIV CL
    MOV BX,AX    ;��������->BH����->BL
    CMP BL,9     ;�̡� 9 ?
    JBE LET6
    ADD BL,7	 ;ת16������ĸ
    
    ;--- ����ַ�
    
    LET6:
    
    ;�������
    ADD BL,30H
    MOV DL,BL
    MOV AH,2
    INT 21H
    CMP BH,9
    JBE LET7
    ADD BH,7
    
    LET7:
    ;���������
    ADD BH,30H
    MOV DL,BH
    MOV AH,2
    INT 21H
    
    JMP LET      ; ������������

	; ����
    LET5:
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START


