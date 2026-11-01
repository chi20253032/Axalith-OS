/* GRUB enters in 32-bit protected mode. This stub builds identity mappings
 * for the first GiB, enables long mode, and calls the 64-bit C kernel.
 */
.section .multiboot, "a"
.align 8
mb2_header:
    .long 0xe85250d6
    .long 0
    .long mb2_header_end - mb2_header
    .long -(0xe85250d6 + (mb2_header_end - mb2_header))
    .align 8
    .short 5
    .short 0
    .long 20
    .long 1024
    .long 768
    .long 32
    .align 8
    .short 0
    .short 0
    .long 8
mb2_header_end:

.section .text.boot, "ax"
.code32
.global _start
.type _start, @function
.extern kmain
_start:
    cli
    movl %eax, boot_magic
    movl %ebx, boot_info_ptr

    movl $pdpt_table, %eax
    orl $0x3, %eax
    movl %eax, pml4_table
    movl $0, pml4_table + 4

    movl $pd_table, %eax
    orl $0x3, %eax
    movl %eax, pdpt_table
    movl $0, pdpt_table + 4

    xorl %ecx, %ecx
1:
    movl %ecx, %eax
    shll $21, %eax
    orl $0x83, %eax
    movl %eax, pd_table(,%ecx,8)
    movl $0, pd_table + 4(,%ecx,8)
    incl %ecx
    cmpl $512, %ecx
    jne 1b

    movl %cr4, %eax
    orl $0x20, %eax
    movl %eax, %cr4
    movl $pml4_table, %eax
    movl %eax, %cr3

    movl $0xC0000080, %ecx
    rdmsr
    orl $0x100, %eax
    wrmsr

    movl %cr0, %eax
    orl $0x80000001, %eax
    movl %eax, %cr0

    lgdt gdt64_pointer
    ljmp $0x08, $long_mode_entry

.code64
long_mode_entry:
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    xorw %ax, %ax
    movw %ax, %fs
    movw %ax, %gs
    leaq boot_stack_top(%rip), %rsp
    andq $-16, %rsp
    movl boot_info_ptr(%rip), %edi
    movl boot_magic(%rip), %esi
    call kmain
2:
    cli
    hlt
    jmp 2b

.align 8
gdt64:
    .quad 0x0000000000000000
    .quad 0x00AF9A000000FFFF
    .quad 0x00CF92000000FFFF
gdt64_end:
gdt64_pointer:
    .word gdt64_end - gdt64 - 1
    .long gdt64

.section .bss, "aw", @nobits
.align 4096
pml4_table: .skip 4096
.align 4096
pdpt_table: .skip 4096
.align 4096
pd_table: .skip 4096
.align 16
boot_magic: .skip 4
boot_info_ptr: .skip 4
.align 16
boot_stack_bottom: .skip 16384
boot_stack_top:
