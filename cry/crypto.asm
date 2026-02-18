section .text
    global crypto

; Function: crypto
; Parameters:
;   - rdi: pointer to data buffer
;   - rsi: length of data buffer
;   - dl: XOR key (single byte)
crypto:
    test rsi, rsi             ; Check if length is zero
    jz .done

.loop:
    cmp rsi, 8                ; Check if at least 8 bytes remain
    jl .small_loop            ; If less, handle remaining bytes

    mov rax, [rdi]            ; Load 8 bytes from the buffer
    xor rax, rdx              ; XOR with the key (key is extended to 64 bits)
    mov [rdi], rax            ; Store result back in the buffer

    add rdi, 8                ; Move pointer forward by 8 bytes
    sub rsi, 8                ; Decrease remaining length
    jmp .loop                 ; Repeat for the next 8 bytes

.small_loop:
    test rsi, rsi             ; Check if any bytes are left
    jz .done

    mov al, byte [rdi]        ; Load 1 byte
    xor al, dl                ; XOR with key
    mov byte [rdi], al        ; Store result back

    inc rdi                   ; Move to next byte
    dec rsi                   ; Decrement length
    jmp .small_loop           ; Continue for remaining bytes

.done:
    ret
