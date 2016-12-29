[org 0x07C0:0000]
[bits 16]

;------------------------------------------------
;startup
;------------------------------------------------
start:

;set up stack location
mov [temp], ax
mov ax, 0x2000
mov ss, ax
xor ax, ax
mov sp, ax
mov ax, temp

;set ds = ss
push ss
pop ds

call _kmain

;keep system stopped if control ever gets back here
stop_kernel:
cli
hlt
jmp stop_kernel

;------------------------------------------------

;------------------------------------------------
;int functions
;------------------------------------------------

int_entry:
;store all registers into c-accessible array
mov [_InRegs + 0], ax
mov [_InRegs + 2], bx
mov [_InRegs + 4], cx
mov [_InRegs + 6], dx
mov [_InRegs + 8], ss
mov [_InRegs + 10], ds
mov [_InRegs + 12], es
mov [_InRegs + 14], cs
mov [_InRegs + 16], sp
mov [_InRegs + 18], si
mov [_InRegs + 20], di
mov [_InRegs + 22], bp
pushf
pop word [_InRegs + 24]
ret

int_exit:
;load all registers from c-accessible array
mov ax, [_OutRegs + 0]
mov bx, [_OutRegs + 2]
mov cx, [_OutRegs + 4]
mov dx, [_OutRegs + 6]
mov ss, [_OutRegs + 8]
mov ds, [_OutRegs + 10]
mov es, [_OutRegs + 12]
mov si, [_OutRegs + 18]
mov di, [_OutRegs + 20]
mov bp, [_OutRegs + 22]
push word [_OutRegs + 24]
popf
ret

;------------------------------------------------

;------------------------------------------------
;int20 handler
;------------------------------------------------

call int_entry
;set return code to 0
push ax
mov al, 0x00
mov [_OutRegs + 1], al
pop ax
call _TerminateProgram
call int_exit

iret

;------------------------------------------------

;------------------------------------------------
;int21 handler
;------------------------------------------------

call int_entry
call _HandleAPICall
call int_exit

iret

;------------------------------------------------

temp dw 0
_InRegs times 32 dw 0
_OutRegs times 32 dw 0

_HandleAPICall:
_TerminateProgram:
_kmain:
ret
