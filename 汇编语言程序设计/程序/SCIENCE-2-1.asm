DATAS SEGMENT
	INFO    DB 'PLEASE INPUT NUMBER NO MORE THAN 5 : $'
	NAMES   DB 'NOTHING    $'
			DB 'ChengZiRui $'
			DB 'LiSiMeng   $'
			DB 'LiZiShi    $'
			DB 'XiaoJianHui$'
			DB 'HuangSiHan $'
DATAS ENDS

CODES SEGMENT
  ASSUME CS:CODES,DS:DATAS
	START:
	
	MOV AX,DATAS
    MOV DS,AX
		
	;�����ʾ��		    
    LEA DX,INFO
    MOV AH,9
	INT 21H
	
	;��������
    MOV AH,1
    INT 21H
    
	;ȥASCII
    SUB AL,30H
				    
	;CLΪ��󳤶�
	MOV CL,12
   	MUL CL   	;AX = AL * CL = 12 * INPUT
   	MOV BX,AX
   	
   	;����
   	MOV AH,2
    MOV DL,0DH 
    INT 21H
    MOV AH,2
    MOV DL,0AH 
    INT 21H
	
	;��NAMES�Ķε�ַ��ʼƫ��BX	   	
  	LEA DX,NAMES
   	ADD DX,BX
				   	
	;���			   	
   	MOV AH,9
  	INT 21H
				    
	MOV AH,4CH
	INT 21H
CODES ENDS
END START





