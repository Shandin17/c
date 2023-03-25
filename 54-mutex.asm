
section         .data
mutex           dd 1 ; from beginning mutex is open

section         .text

mutex_lock:     mov eax, 0
.again:         xchg eax, [mutex] ; xcgh swaps contains of operands in one atomic action
                cmp eax, 0
                je .again
                ret

mutex_unlock:   mov dword [mutex], 1
                ret