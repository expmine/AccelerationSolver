section .data
conv dq 0.27777778

section .text
bits 64
default rel

global accelsolve
extern printf

accelsolve:
    SUBSD XMM1, XMM0
    MULSD XMM1, [conv]
    DIVSD XMM1, XMM2

    CVTSD2SI RAX, XMM1
 ret