
.data
    text db "Text", 0
    caption db "Caption", 0

.code
NtCreateThreadEx PROC
    mov r10, rcx
    mov eax, 0C2h
    syscall
    ret 0
NtCreateThreadEx ENDP



end