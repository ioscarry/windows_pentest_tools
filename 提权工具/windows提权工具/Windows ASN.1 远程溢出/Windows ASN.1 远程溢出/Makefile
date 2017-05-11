build: stage0 win32_bind

stage0: stage0.asm
	nasm -O2 -f bin -o stage0 stage0.asm

win32_bind: win32_bind.asm
	nasm -f bin -o win32_bind win32_bind.asm

disasm: stage0.elf
	objdump -d stage0.elf
	
stage0.elf: stage0.asm
	nasm -O2 -f elf -o stage0.elf stage0.asm

clean:
	rm -rf stage0 win32_bind stage0.elf

.PHONY: build disasm clean
