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
		
	;输出提示语		    
    LEA DX,INFO
    MOV AH,9
	INT 21H
	
	;进行输入
    MOV AH,1
    INT 21H
    
	;去ASCII
    SUB AL,30H
				    
	;CL为最大长度
	MOV CL,12
   	MUL CL   	;AX = AL * CL = 12 * INPUT
   	MOV BX,AX
   	
   	;换行
   	MOV AH,2
    MOV DL,0DH 
    INT 21H
    MOV AH,2
    MOV DL,0AH 
    INT 21H
	
	;从NAMES的段地址开始偏移BX	   	
  	LEA DX,NAMES
   	ADD DX,BX
				   	
	;输出			   	
   	MOV AH,9
  	INT 21H
				    
	MOV AH,4CH
	INT 21H
CODES ENDS
END START





