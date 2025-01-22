    .text
    .align 8
    .globl getFP
    .globl getSP
getFP:
    movq %rbp, %rax
    ret
getSP:
    movq %rsp, %rax
    ret
