assume cs:code
code segment
start: mov ax,cs
mov ds,ax
mov si,offset do0;����ds:siָ��Դ��ַ
mov ax,0
mov es,ax
mov di,200h;����es:diָ��Ŀ�ĵ�ַ
mov cx,offset do0end-offset do0;����cx���䳤��
cld;���ô��䷽��Ϊ��
rep movsb
mov ax,0;�����ж�������
mov es,ax
mov word ptr es:[0*4],200h;Ϊʲô��es�����ж���������?
mov word ptr es:[0*4+2],0
mov ax,4c00h
int 21h

do0:jmp short do0start
db"overflow!"
do0start:mov ax,cs
mov ds,ax
mov si,202h
mov ax,0b800h
mov es,ax
mov di,12*160+36*2;����es:diָ���Դ�ռ���м�λ��,�����ַ��ô�������?
mov cx,9;����cxΪ�ַ�������
s:mov al,[si]
mov es:[di],al
inc si
add di,2
loop s
mov ax,4c00h
int 21h
do0end :nop;Ϊʲô��nop?
code ends
end start
