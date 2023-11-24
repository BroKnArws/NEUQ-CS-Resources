DATAS SEGMENT
	INFO        DB 'PLEASE INPUT NUMBER NO MORE THAN 5: $'
	STU0        DB 'NOTHING    $'
	STU1		DB 'ChengZiRui $'
	STU2		DB 'LiSiMeng   $'
	STU3		DB 'LiZiShi    $'
	STU4		DB 'XiaoJianHui$'
	STU5		DB 'HuangSiHan $'
	;存的是每个单元的偏移地址
	TABLE       DW STU0,STU1,STU2,STU3,STU4,STU5
			
DATAS ENDS

CODES SEGMENT
  ASSUME CS:CODES,DS:DATAS
	START:
	
	MOV AX,DATAS
    MOV DS,AX
			
	;输出提示语			    
    LEA DX,INFO
    MOV AH,9
	INT 21H
	
	;输入
    MOV AH,1
    INT 21H
    
	;去ASCII变数值
    SUB AL,30H
				    
	MOV CL,2 	;因为DW
   	MUL CL   	;AX = AL * CL = 2 * INPUT
   	MOV BX,AX
   	
   	;换行
   	MOV AH,2
    MOV DL,0DH 
    INT 21H
    MOV AH,2
    MOV DL,0AH 
    INT 21H
   	

   	;查表，移到对应段地址
   	MOV DX,TABLE[BX]
   	
   	;输出
   	MOV AH,9
  	INT 21H
				    
	MOV AH,4CH
	INT 21H
CODES ENDS
END START








