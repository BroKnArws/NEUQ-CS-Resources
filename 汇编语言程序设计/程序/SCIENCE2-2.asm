DATAS SEGMENT
	INFO        DB 'PLEASE INPUT NUMBER NO MORE THAN 5: $'
	STU0        DB 'NOTHING    $'
	STU1		DB 'ChengZiRui $'
	STU2		DB 'LiSiMeng   $'
	STU3		DB 'LiZiShi    $'
	STU4		DB 'XiaoJianHui$'
	STU5		DB 'HuangSiHan $'
	;�����ÿ����Ԫ��ƫ�Ƶ�ַ
	TABLE       DW STU0,STU1,STU2,STU3,STU4,STU5
			
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
	
	;����
    MOV AH,1
    INT 21H
    
	;ȥASCII����ֵ
    SUB AL,30H
				    
	MOV CL,2 	;��ΪDW
   	MUL CL   	;AX = AL * CL = 2 * INPUT
   	MOV BX,AX
   	
   	;����
   	MOV AH,2
    MOV DL,0DH 
    INT 21H
    MOV AH,2
    MOV DL,0AH 
    INT 21H
   	

   	;����Ƶ���Ӧ�ε�ַ
   	MOV DX,TABLE[BX]
   	
   	;���
   	MOV AH,9
  	INT 21H
				    
	MOV AH,4CH
	INT 21H
CODES ENDS
END START








