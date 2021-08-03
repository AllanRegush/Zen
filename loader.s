.set MAGIC, 0x1BADB002
.set FLAGS, (1 << 0 | 1 << 1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

#.section .bss
#.align 16
#kstack_bottom:
#.skip 16384 # 16 KiB
#kstack_top:

.section .text
.extern k_main
.global loader

loader:
    mov $k_stack, %esp
    push %eax
    push %ebx
    call k_main
    jmp _quit


_quit:
    cli
    hlt
    jmp _quit

.section .bss
# Create space for the kernel stack -> offset memory 2MB
.space 2*1024*1024
k_stack:

