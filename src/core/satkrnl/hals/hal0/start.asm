bits 32

section .text
global HALInstallLocalGDT
global _start
global HALInstallLocalIDT
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15
extern HALHandleFault
extern idtp
extern BspMgrEntrypoint
extern gp

_start:
    mov esp, SystemStack
    push eax
    push ebx
    call BspMgrEntrypoint
    jmp $
HALInstallLocalGDT:
    lgdt [gp]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2
flush2:
    ret
    
HALInstallLocalIDT:
    lidt [idtp]
    ret

;  0: Divide By Zero Exception
isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common_stub

;  1: Debug Exception
isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub

;  2: Non Maskable Interrupt Exception
isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_stub

;  3: Int 3 Exception
isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_stub

;  4: INTO Exception
isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_stub

;  5: Out of Bounds Exception
isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_stub

;  6: Invalid Opcode Exception
isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common_stub

;  7: Coprocessor Not Available Exception
isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_stub

;  8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push byte 8
    jmp isr_common_stub

;  9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_stub

; 10: Bad TSS Exception (With Error Code!)
isr10:
    cli
    push byte 10
    jmp isr_common_stub

; 11: Segment Not Present Exception (With Error Code!)
isr11:
    cli
    push byte 11
    jmp isr_common_stub

; 12: Stack Fault Exception (With Error Code!)
isr12:
    cli
    push byte 12
    jmp isr_common_stub

; 13: General Protection Fault Exception (With Error Code!)
isr13:
    cli
    push byte 13
    jmp isr_common_stub

; 14: Page Fault Exception (With Error Code!)
isr14:
    cli
    push byte 14
    jmp isr_common_stub

; 15: Reserved Exception
isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common_stub

; 16: Floating Point Exception
isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common_stub

; 17: Alignment Check Exception
isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common_stub

; 18: Machine Check Exception
isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common_stub

; 19: Reserved
isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common_stub

; 20: Reserved
isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common_stub

; 21: Reserved
isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common_stub

; 22: Reserved
isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common_stub

; 23: Reserved
isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common_stub

; 24: Reserved
isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common_stub

; 25: Reserved
isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common_stub

; 26: Reserved
isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common_stub

; 27: Reserved
isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common_stub

; 28: Reserved
isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common_stub

; 29: Reserved
isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common_stub

; 30: Reserved
isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common_stub

; 31: Reserved
isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_stub

extern ExHandleSyscall
    
; 128: Syscall
isr128:
    cli
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, ExHandleSyscall
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    iret

global isr128 

isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, HALHandleFault
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

extern HALSwitchThread

; 32: IRQ0
irq0:
    cli
    push byte 0
    push byte 32
    jmp IRQCommonStub

; 33: IRQ1
irq1:
    cli
    push byte 0
    push byte 33
    jmp IRQCommonStub

; 34: IRQ2
irq2:
    cli
    push byte 0
    push byte 34
    jmp IRQCommonStub

; 35: IRQ3
irq3:
    cli
    push byte 0
    push byte 35
    jmp IRQCommonStub

; 36: IRQ4
irq4:
    cli
    push byte 0
    push byte 36
    jmp IRQCommonStub

; 37: IRQ5
irq5:
    cli
    push byte 0
    push byte 37
    jmp IRQCommonStub

; 38: IRQ6
irq6:
    cli
    push byte 0
    push byte 38
    jmp IRQCommonStub

; 39: IRQ7
irq7:
    cli
    push byte 0
    push byte 39
    jmp IRQCommonStub

; 40: IRQ8
irq8:
    cli
    push byte 0
    push byte 40
    jmp IRQCommonStub

; 41: IRQ9
irq9:
    cli
    push byte 0
    push byte 41
    jmp IRQCommonStub

; 42: IRQ10
irq10:
    cli
    push byte 0
    push byte 42
    jmp IRQCommonStub

; 43: IRQ11
irq11:
    cli
    push byte 0
    push byte 43
    jmp IRQCommonStub

; 44: IRQ12
irq12:
    cli
    push byte 0
    push byte 44
    jmp IRQCommonStub

; 45: IRQ13
irq13:
    cli
    push byte 0
    push byte 45
    jmp IRQCommonStub

; 46: IRQ14
irq14:
    cli
    push byte 0
    push byte 46
    jmp IRQCommonStub

; 47: IRQ15
irq15:
    cli
    push byte 0
    push byte 47
    jmp IRQCommonStub

HALLoadCR3:
    push ebp
    mov ebp, esp
    mov eax, [esp + 8]
    mov cr3, eax
    mov esp, ebp
    pop ebp
    ret
    
HALStartupPaging:
    push ebp
    mov ebp, esp
    mov eax, cr0
    or eax, 80000000h
    mov cr0, eax 
    mov esp, ebp 
    pop ebp
    ret

global HALLoadCR3
global HALStartupPaging
    
extern HALCommonIRQHandler

IRQCommonStub:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp

    push eax
    mov eax, HALCommonIRQHandler
    call eax
    pop eax

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

HALGetCPUFlags:
    pushf
    pop eax
    ret

global HALGetCPUFlags

section .multiboot
align 8
    ; Multiboot macros to make a few lines later more readable
    MULTIBOOT_HEADER_MAGIC	equ 0xE85250D6
    MULTIBOOT_HEADER_ARCHI	equ 0
    MULTIBOOT_HEADER_LENGT	equ 32
    MULTIBOOT_CHECKSUM	    equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_ARCHI + MULTIBOOT_HEADER_LENGT)
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_ARCHI
    dd MULTIBOOT_HEADER_LENGT
    dd MULTIBOOT_CHECKSUM

    ; multiboot2 request
    dw 1  ; 2 bytes
    dw 0  ; 2 bytes
    dd 16  ; 4 bytes
    dd 2  ; 4 bytes
    dd 6  ; 4 bytes


; Here is the definition of our BSS section. Right now, we'll use
; it just to store the stack. Remember that a stack actually grows
; downwards, so we declare the size of the data before declaring
; the identifier 'SystemStack'
SECTION .bss
    resb 16384               ; This reserves 16 KBs of memory here
SystemStack:
    resb 512
SchedulerStack:

