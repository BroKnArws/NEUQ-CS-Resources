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
    mov al,36h
    out dx,al
    mov dx,io82530
    mov ax,1000
    out dx,al
    mov al,ah
    out dx,al
    mov dx,io825c
    mov al,76h
    out dx,al
    mov dx,io82531
    mov ax,1000
    out dx,al
    mov al,ah
    out dx,al
    mov ah,4ch
    int 21h

code ends
end start
