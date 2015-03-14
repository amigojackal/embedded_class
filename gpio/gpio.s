	.arch armv6
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"gpio.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"echo 27 > /sys/class/gpio/export\000"
	.align	2
.LC1:
	.ascii	"echo \"out\" > /sys/class/gpio/gpio27/direction\000"
	.align	2
.LC2:
	.ascii	"cat /sys/class/gpio/gpio27/value\000"
	.align	2
.LC3:
	.ascii	"Enter 1 to turn on GPIO27(D1 LED), enter 0 to turn "
	.ascii	"off GPIO27(D1 LED), anything else to quit: \000"
	.align	2
.LC4:
	.ascii	"%s\000"
	.align	2
.LC5:
	.ascii	"1\000"
	.align	2
.LC6:
	.ascii	"echo 1 > /sys/class/gpio/gpio27/value\000"
	.align	2
.LC7:
	.ascii	"0\000"
	.align	2
.LC8:
	.ascii	"echo 0 > /sys/class/gpio/gpio27/value\000"
	.align	2
.LC9:
	.ascii	"echo 27 > /sys/class/gpio/unexport\000"
	.align	2
.LC10:
	.ascii	"END OF TEST \000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	.fnstart
.LFB0:
	@ args = 0, pretend = 0, frame = 256
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.setfp fp, sp, #4
	add	fp, sp, #4
	.pad #256
	sub	sp, sp, #256
	ldr	r0, .L8
	bl	system
	ldr	r0, .L8+4
	bl	system
	ldr	r0, .L8+8
	bl	system
.L6:
	ldr	r0, .L8+12
	bl	printf
	sub	r3, fp, #260
	ldr	r0, .L8+16
	mov	r1, r3
	bl	scanf
	sub	r3, fp, #260
	mov	r0, r3
	ldr	r1, .L8+20
	bl	strcmp
	mov	r3, r0
	cmp	r3, #0
	bne	.L2
	ldr	r0, .L8+24
	bl	system
	b	.L6
.L2:
	sub	r3, fp, #260
	mov	r0, r3
	ldr	r1, .L8+28
	bl	strcmp
	mov	r3, r0
	cmp	r3, #0
	bne	.L7
	ldr	r0, .L8+32
	bl	system
	b	.L6
.L7:
	mov	r0, r0	@ nop
.L5:
	ldr	r0, .L8+36
	bl	system
	ldr	r0, .L8+40
	bl	puts
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L9:
	.align	2
.L8:
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.word	.LC10
	.fnend
	.size	main, .-main
	.ident	"GCC: (Debian 4.6.3-14+rpi1) 4.6.3"
	.section	.note.GNU-stack,"",%progbits
