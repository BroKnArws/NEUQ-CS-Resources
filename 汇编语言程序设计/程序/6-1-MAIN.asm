EXTRN SORT:NEAR
EXTRN INNAME:NEAR
EXTRN INSCORE:NEAR
EXTRN DIS:NEAR
INCLUDE PACK.mac

DATAS SEGMENT COMMON 'DATA'

   P EQU 5    ;ѧ����
   NL EQU 15  ;NAME ��������
   SL EQU 4   ;SCORE ��������
   NL1 EQU 13 ;NAME ʵ�ʳ���
   TEMP1 DB 0 ;���ʵʱѧ��
   TEMP2 DB 1

   NAMEA DB P DUP(NL1,?,NL1 DUP('$'))  ;����5�����������ֳ���С��11
   SCOREASC DB P DUP(SL DUP('$'))   ;����5���ɼ���ÿ���ɼ���3�ֽڣ���$��β
   RANK DW 0,1,2,3,4    ;�൱��NAMEA��SCOREASC�����±�
   SCOREN DW 5 DUP(0)   ;�����ֵ�Լ�������ɵĳɼ�
    
   X DB 3 DUP(?)   ; ���0-255������
DATAS ENDS

STACKS SEGMENT
STACKS ENDS

CODES SEGMENT PUBLIC 'CODE'
	ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    MOV CX,P   ;ѭ��������Ϣ
    LOOPM:
	CALL INNAME   ;��������
	CALL INSCORE  ;����ɼ�
    INC TEMP1
    LOOP LOOPM
    CALL SORT     ;����
    CALL DIS      ;��ʾ�ɼ�
    MOV AH,4CH
    INT 21H

CODES ENDS
    END START






















