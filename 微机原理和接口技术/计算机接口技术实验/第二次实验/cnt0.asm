data segment
io82530 equ 280h
io82531 equ 281h
io82532 equ 282h
io8253c equ 283h
data ends

code segment
assume cs:code,ds:data
start:
    mov ax,data
    mov ds,ax
    mov dx,io8253c
    mov al,14h
    out dx,al
    mov dx,io82530
    mov al,0fh
    out dx,al
    cnt0:in al,dx
    call disp 
    mov ah,1
    int 16h
    jz cnt0
    mov ah,4ch
    int 21h
    
disp proc
    push ax
    push dx
    cmp al,9
    jle num
    add al,7
    num:
    add al,30h
    mov dl,al
    mov ah,2
    int 21h
    pop dx
    pop ax
    ret 
disp endp
code ends
end start
