	.file	"hw03.c"
	.text
	.section	.rodata
.LC0:
	.string	"block device"
.LC1:
	.string	"character device"
.LC2:
	.string	"directory"
.LC3:
	.string	"named pipe (FIFO)"
.LC4:
	.string	"symbolic link"
.LC5:
	.string	"regular file"
.LC6:
	.string	"UNIX domain socket"
.LC7:
	.string	"unknown file type"
.LC8:
	.string	"UNKNOWN"
	.text
	.globl	filetype
	.type	filetype, @function
filetype:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -20(%rbp)
	movzbl	-20(%rbp), %eax
	cmpl	$12, %eax
	ja	.L2
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L4(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L4(%rip), %rdx
	addq	%rdx, %rax
	notrack jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L4:
	.long	.L11-.L4
	.long	.L10-.L4
	.long	.L9-.L4
	.long	.L2-.L4
	.long	.L8-.L4
	.long	.L2-.L4
	.long	.L7-.L4
	.long	.L2-.L4
	.long	.L6-.L4
	.long	.L2-.L4
	.long	.L5-.L4
	.long	.L2-.L4
	.long	.L3-.L4
	.text
.L7:
	leaq	.LC0(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L9:
	leaq	.LC1(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L8:
	leaq	.LC2(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L10:
	leaq	.LC3(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L5:
	leaq	.LC4(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L6:
	leaq	.LC5(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L3:
	leaq	.LC6(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L11:
	leaq	.LC7(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L2:
	leaq	.LC8(%rip), %rax
	movq	%rax, -8(%rbp)
.L12:
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	filetype, .-filetype
	.globl	get_current_directory_name
	.type	get_current_directory_name, @function
get_current_directory_name:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	$2000, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -24(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	getcwd@PLT
	testq	%rax, %rax
	je	.L15
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	__xpg_basename@PLT
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	addq	$1, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy@PLT
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-8(%rbp), %rax
	jmp	.L16
.L15:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movl	$0, %eax
.L16:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	get_current_directory_name, .-get_current_directory_name
	.section	.rodata
.LC9:
	.string	" "
	.align 8
.LC10:
	.string	"%*s  File Permissions:         "
.LC11:
	.string	"d"
.LC12:
	.string	"-"
.LC13:
	.string	"r"
.LC14:
	.string	"w"
.LC15:
	.string	"x"
	.align 8
.LC16:
	.string	"%*s  File size:                %lld bytes\n"
	.align 8
.LC17:
	.string	"%*s  Last file access:         %s\n"
	.text
	.globl	printStat
	.type	printStat, @function
printStat:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	leaq	.LC9(%rip), %rdx
	movl	%eax, %esi
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	40(%rbp), %eax
	andl	$61440, %eax
	cmpl	$16384, %eax
	jne	.L18
	leaq	.LC11(%rip), %rax
	jmp	.L19
.L18:
	leaq	.LC12(%rip), %rax
.L19:
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	40(%rbp), %eax
	andl	$256, %eax
	testl	%eax, %eax
	je	.L20
	leaq	.LC13(%rip), %rax
	jmp	.L21
.L20:
	leaq	.LC12(%rip), %rax
.L21:
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	40(%rbp), %eax
	andl	$128, %eax
	testl	%eax, %eax
	je	.L22
	leaq	.LC14(%rip), %rax
	jmp	.L23
.L22:
	leaq	.LC12(%rip), %rax
.L23:
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	40(%rbp), %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L24
	leaq	.LC15(%rip), %rax
	jmp	.L25
.L24:
	leaq	.LC12(%rip), %rax
.L25:
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	40(%rbp), %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L26
	leaq	.LC13(%rip), %rax
	jmp	.L27
.L26:
	leaq	.LC12(%rip), %rax
.L27:
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	40(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L28
	leaq	.LC14(%rip), %rax
	jmp	.L29
.L28:
	leaq	.LC12(%rip), %rax
.L29:
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	40(%rbp), %eax
	andl	$8, %eax
	testl	%eax, %eax
	je	.L30
	leaq	.LC15(%rip), %rax
	jmp	.L31
.L30:
	leaq	.LC12(%rip), %rax
.L31:
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	40(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L32
	leaq	.LC13(%rip), %rax
	jmp	.L33
.L32:
	leaq	.LC12(%rip), %rax
.L33:
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	40(%rbp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L34
	leaq	.LC14(%rip), %rax
	jmp	.L35
.L34:
	leaq	.LC12(%rip), %rax
.L35:
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	40(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L36
	leaq	.LC15(%rip), %rax
	jmp	.L37
.L36:
	leaq	.LC12(%rip), %rax
.L37:
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$10, %edi
	call	putchar@PLT
	movl	40(%rbp), %eax
	andl	$61440, %eax
	cmpl	$16384, %eax
	jne	.L38
	movl	-4(%rbp), %eax
	movl	$0, %ecx
	leaq	.LC9(%rip), %rdx
	movl	%eax, %esi
	leaq	.LC16(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L39
.L38:
	movq	64(%rbp), %rdx
	movl	-4(%rbp), %eax
	movq	%rdx, %rcx
	leaq	.LC9(%rip), %rdx
	movl	%eax, %esi
	leaq	.LC16(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L39:
	leaq	88(%rbp), %rax
	movq	%rax, %rdi
	call	ctime@PLT
	movq	%rax, %rdx
	movl	-4(%rbp), %eax
	movq	%rdx, %rcx
	leaq	.LC9(%rip), %rdx
	movl	%eax, %esi
	leaq	.LC17(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	printStat, .-printStat
	.globl	checkSize
	.type	checkSize, @function
checkSize:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	$0, -4(%rbp)
	movq	64(%rbp), %rdx
	movl	-20(%rbp), %eax
	cltq
	cmpq	%rax, %rdx
	jg	.L41
	movl	$1, -4(%rbp)
.L41:
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	checkSize, .-checkSize
	.globl	checkSubstr
	.type	checkSubstr, @function
checkSubstr:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	%ecx, -40(%rbp)
	movl	$0, -4(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strstr@PLT
	testq	%rax, %rax
	je	.L44
	movl	-36(%rbp), %eax
	cmpl	-40(%rbp), %eax
	jg	.L44
	movl	$1, -4(%rbp)
.L44:
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	checkSubstr, .-checkSubstr
	.globl	splitStringOnSpace
	.type	splitStringOnSpace, @function
splitStringOnSpace:
.LFB11:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	-40(%rbp), %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	strchr@PLT
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L47
	movq	-48(%rbp), %rax
	movq	$0, (%rax)
	movq	-56(%rbp), %rax
	movq	$0, (%rax)
	jmp	.L46
.L47:
	movq	-24(%rbp), %rax
	subq	-40(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	-40(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strncpy@PLT
	movq	-24(%rbp), %rax
	leaq	1(%rax), %rcx
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strncpy@PLT
	movq	-48(%rbp), %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-56(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
.L46:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	splitStringOnSpace, .-splitStringOnSpace
	.section	.rodata
	.align 8
.LC18:
	.string	"%*s [%s] (symbolic link to %s)\n"
.LC19:
	.string	"%*s [%s] (%s)\n"
	.text
	.globl	displayForNoFlag
	.type	displayForNoFlag, @function
displayForNoFlag:
.LFB12:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	80(%rbp), %eax
	subl	$1, %eax
	movl	%eax, 80(%rbp)
	movl	80(%rbp), %eax
	testl	%eax, %eax
	jg	.L52
	movq	16(%rbp), %rax
	movzbl	18(%rax), %eax
	cmpb	$10, %al
	jne	.L51
	movq	24(%rbp), %rax
	movq	16(%rbp), %rdx
	leaq	19(%rdx), %rcx
	movl	$4095, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	readlink@PLT
	movq	%rax, 48(%rbp)
	movq	24(%rbp), %rcx
	movq	16(%rbp), %rax
	leaq	19(%rax), %rdx
	movl	32(%rbp), %eax
	sall	$2, %eax
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC9(%rip), %rdx
	movl	%eax, %esi
	leaq	.LC18(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L52
.L51:
	movq	16(%rbp), %rax
	movzbl	18(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	filetype
	movq	%rax, %rcx
	movq	16(%rbp), %rax
	leaq	19(%rax), %rdx
	movl	32(%rbp), %eax
	sall	$2, %eax
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC9(%rip), %rdx
	movl	%eax, %esi
	leaq	.LC19(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L52:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	displayForNoFlag, .-displayForNoFlag
	.globl	displayStatFlag
	.type	displayStatFlag, @function
displayStatFlag:
.LFB13:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	80(%rbp), %eax
	subl	$1, %eax
	movl	%eax, 80(%rbp)
	movq	$0, -8(%rbp)
	pushq	104(%rbp)
	pushq	96(%rbp)
	pushq	88(%rbp)
	pushq	80(%rbp)
	pushq	72(%rbp)
	pushq	64(%rbp)
	pushq	56(%rbp)
	pushq	48(%rbp)
	pushq	40(%rbp)
	pushq	32(%rbp)
	pushq	24(%rbp)
	pushq	16(%rbp)
	movl	$0, %edi
	call	printFile
	addq	$96, %rsp
	movl	$0, 56(%rbp)
	pushq	104(%rbp)
	pushq	96(%rbp)
	pushq	88(%rbp)
	pushq	80(%rbp)
	pushq	72(%rbp)
	pushq	64(%rbp)
	pushq	56(%rbp)
	pushq	48(%rbp)
	pushq	40(%rbp)
	pushq	32(%rbp)
	pushq	24(%rbp)
	pushq	16(%rbp)
	call	chooseNextFunc
	addq	$96, %rsp
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	displayStatFlag, .-displayStatFlag
	.globl	printFile
	.type	printFile, @function
printFile:
.LFB14:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	80(%rbp), %eax
	testl	%eax, %eax
	jg	.L58
	movq	16(%rbp), %rax
	movzbl	18(%rax), %eax
	cmpb	$10, %al
	jne	.L56
	movq	24(%rbp), %rax
	movq	16(%rbp), %rdx
	leaq	19(%rdx), %rcx
	movl	$4095, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	readlink@PLT
	movq	%rax, -8(%rbp)
	movq	24(%rbp), %rcx
	movq	16(%rbp), %rax
	leaq	19(%rax), %rdx
	movl	32(%rbp), %eax
	sall	$2, %eax
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC9(%rip), %rdx
	movl	%eax, %esi
	leaq	.LC18(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L57
.L56:
	movq	16(%rbp), %rax
	movzbl	18(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	filetype
	movq	%rax, %rcx
	movq	16(%rbp), %rax
	leaq	19(%rax), %rdx
	movl	32(%rbp), %eax
	sall	$2, %eax
	movq	%rcx, %r8
	movq	%rdx, %rcx
	leaq	.LC9(%rip), %rdx
	movl	%eax, %esi
	leaq	.LC19(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L57:
	movl	56(%rbp), %eax
	testl	%eax, %eax
	je	.L58
	movl	32(%rbp), %eax
	leal	0(,%rax,4), %edx
	movq	40(%rbp), %rax
	pushq	136(%rax)
	pushq	128(%rax)
	pushq	120(%rax)
	pushq	112(%rax)
	pushq	104(%rax)
	pushq	96(%rax)
	pushq	88(%rax)
	pushq	80(%rax)
	pushq	72(%rax)
	pushq	64(%rax)
	pushq	56(%rax)
	pushq	48(%rax)
	pushq	40(%rax)
	pushq	32(%rax)
	pushq	24(%rax)
	pushq	16(%rax)
	pushq	8(%rax)
	pushq	(%rax)
	movl	%edx, %edi
	call	printStat
	addq	$144, %rsp
.L58:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	printFile, .-printFile
	.globl	chooseNextFunc
	.type	chooseNextFunc, @function
chooseNextFunc:
.LFB15:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	64(%rbp), %rax
	testq	%rax, %rax
	je	.L60
	leaq	displayForStringFlag(%rip), %rax
	movq	%rax, 96(%rbp)
	jmp	.L61
.L60:
	movq	88(%rbp), %rax
	testq	%rax, %rax
	je	.L62
	leaq	displayFileTypeFlag(%rip), %rax
	movq	%rax, 96(%rbp)
	jmp	.L61
.L62:
	movl	72(%rbp), %eax
	testl	%eax, %eax
	je	.L63
	leaq	displayForSizeFlag(%rip), %rax
	movq	%rax, 96(%rbp)
	jmp	.L61
.L63:
	movl	56(%rbp), %eax
	cmpl	$1, %eax
	jne	.L61
	leaq	displayStatFlag(%rip), %rax
	movq	%rax, 96(%rbp)
.L61:
	movq	96(%rbp), %rax
	testq	%rax, %rax
	je	.L65
	movq	96(%rbp), %rax
	pushq	104(%rbp)
	pushq	96(%rbp)
	pushq	88(%rbp)
	pushq	80(%rbp)
	pushq	72(%rbp)
	pushq	64(%rbp)
	pushq	56(%rbp)
	pushq	48(%rbp)
	pushq	40(%rbp)
	pushq	32(%rbp)
	pushq	24(%rbp)
	pushq	16(%rbp)
	call	*%rax
	addq	$96, %rsp
.L65:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	chooseNextFunc, .-chooseNextFunc
	.section	.rodata
.LC20:
	.string	"f"
	.text
	.globl	displayFileTypeFlag
	.type	displayFileTypeFlag, @function
displayFileTypeFlag:
.LFB16:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	80(%rbp), %eax
	subl	$1, %eax
	movl	%eax, 80(%rbp)
	movq	$0, 96(%rbp)
	movq	88(%rbp), %rax
	leaq	.LC11(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L67
	movl	$4, -4(%rbp)
.L67:
	movq	88(%rbp), %rax
	leaq	.LC20(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L68
	movl	$8, -4(%rbp)
.L68:
	movq	16(%rbp), %rax
	movzbl	18(%rax), %eax
	cmpb	$8, %al
	jne	.L70
	pushq	104(%rbp)
	pushq	96(%rbp)
	pushq	88(%rbp)
	pushq	80(%rbp)
	pushq	72(%rbp)
	pushq	64(%rbp)
	pushq	56(%rbp)
	pushq	48(%rbp)
	pushq	40(%rbp)
	pushq	32(%rbp)
	pushq	24(%rbp)
	pushq	16(%rbp)
	movl	$0, %edi
	call	printFile
	addq	$96, %rsp
	movq	$0, 88(%rbp)
	pushq	104(%rbp)
	pushq	96(%rbp)
	pushq	88(%rbp)
	pushq	80(%rbp)
	pushq	72(%rbp)
	pushq	64(%rbp)
	pushq	56(%rbp)
	pushq	48(%rbp)
	pushq	40(%rbp)
	pushq	32(%rbp)
	pushq	24(%rbp)
	pushq	16(%rbp)
	call	chooseNextFunc
	addq	$96, %rsp
.L70:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	displayFileTypeFlag, .-displayFileTypeFlag
	.globl	displayForSizeFlag
	.type	displayForSizeFlag, @function
displayForSizeFlag:
.LFB17:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	80(%rbp), %eax
	subl	$1, %eax
	movl	%eax, 80(%rbp)
	movq	$0, 96(%rbp)
	movl	72(%rbp), %edx
	movq	40(%rbp), %rax
	pushq	136(%rax)
	pushq	128(%rax)
	pushq	120(%rax)
	pushq	112(%rax)
	pushq	104(%rax)
	pushq	96(%rax)
	pushq	88(%rax)
	pushq	80(%rax)
	pushq	72(%rax)
	pushq	64(%rax)
	pushq	56(%rax)
	pushq	48(%rax)
	pushq	40(%rax)
	pushq	32(%rax)
	pushq	24(%rax)
	pushq	16(%rax)
	pushq	8(%rax)
	pushq	(%rax)
	movl	%edx, %edi
	call	checkSize
	addq	$144, %rsp
	cmpl	$1, %eax
	jne	.L73
	pushq	104(%rbp)
	pushq	96(%rbp)
	pushq	88(%rbp)
	pushq	80(%rbp)
	pushq	72(%rbp)
	pushq	64(%rbp)
	pushq	56(%rbp)
	pushq	48(%rbp)
	pushq	40(%rbp)
	pushq	32(%rbp)
	pushq	24(%rbp)
	pushq	16(%rbp)
	movl	$0, %edi
	call	printFile
	addq	$96, %rsp
	movl	$0, 72(%rbp)
	pushq	104(%rbp)
	pushq	96(%rbp)
	pushq	88(%rbp)
	pushq	80(%rbp)
	pushq	72(%rbp)
	pushq	64(%rbp)
	pushq	56(%rbp)
	pushq	48(%rbp)
	pushq	40(%rbp)
	pushq	32(%rbp)
	pushq	24(%rbp)
	pushq	16(%rbp)
	call	chooseNextFunc
	addq	$96, %rsp
.L73:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	displayForSizeFlag, .-displayForSizeFlag
	.globl	displayForStringFlag
	.type	displayForStringFlag, @function
displayForStringFlag:
.LFB18:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	80(%rbp), %eax
	subl	$1, %eax
	movl	%eax, 80(%rbp)
	movq	$0, 96(%rbp)
	movq	16(%rbp), %rax
	movzbl	18(%rax), %eax
	cmpb	$4, %al
	je	.L79
	movq	64(%rbp), %rax
	leaq	-16(%rbp), %rdx
	leaq	-24(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	splitStringOnSpace
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %ecx
	movl	76(%rbp), %edx
	movq	-24(%rbp), %rax
	movq	16(%rbp), %rsi
	leaq	19(%rsi), %rdi
	movq	%rax, %rsi
	call	checkSubstr
	cmpl	$1, %eax
	jne	.L77
	pushq	104(%rbp)
	pushq	96(%rbp)
	pushq	88(%rbp)
	pushq	80(%rbp)
	pushq	72(%rbp)
	pushq	64(%rbp)
	pushq	56(%rbp)
	pushq	48(%rbp)
	pushq	40(%rbp)
	pushq	32(%rbp)
	pushq	24(%rbp)
	pushq	16(%rbp)
	movl	$0, %edi
	call	printFile
	addq	$96, %rsp
	movq	$0, 64(%rbp)
	pushq	104(%rbp)
	pushq	96(%rbp)
	pushq	88(%rbp)
	pushq	80(%rbp)
	pushq	72(%rbp)
	pushq	64(%rbp)
	pushq	56(%rbp)
	pushq	48(%rbp)
	pushq	40(%rbp)
	pushq	32(%rbp)
	pushq	24(%rbp)
	pushq	16(%rbp)
	call	chooseNextFunc
	addq	$96, %rsp
.L77:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	jmp	.L74
.L79:
	nop
.L74:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L78
	call	__stack_chk_fail@PLT
.L78:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	displayForStringFlag, .-displayForStringFlag
	.globl	displayeFlag
	.type	displayeFlag, @function
displayeFlag:
.LFB19:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	80(%rbp), %eax
	subl	$1, %eax
	movl	%eax, 80(%rbp)
	movq	104(%rbp), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	forkFunc
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	displayeFlag, .-displayeFlag
	.section	.rodata
.LC21:
	.string	"stat"
.LC22:
	.string	"/usr/bin/stat"
	.align 8
.LC23:
	.string	"If you see this statement then execl failed ;-("
.LC24:
	.string	"execv"
	.align 8
.LC25:
	.string	"Wait for the child process to terminate"
	.align 8
.LC26:
	.string	"Child process exited with status = %d\n"
	.align 8
.LC27:
	.string	"Child process did not terminate normally!"
.LC28:
	.string	"fork"
.LC29:
	.string	"[%ld]: Exiting program .....\n"
	.text
	.globl	forkFunc
	.type	forkFunc, @function
forkFunc:
.LFB20:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC21(%rip), %rax
	movq	%rax, -32(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	$0, -16(%rbp)
	call	fork@PLT
	movl	%eax, -36(%rbp)
	cmpl	$0, -36(%rbp)
	jne	.L82
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC22(%rip), %rax
	movq	%rax, %rdi
	call	execv@PLT
	leaq	.LC23(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC24(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$-1, %edi
	call	exit@PLT
.L82:
	cmpl	$0, -36(%rbp)
	jle	.L83
	leaq	.LC25(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	wait@PLT
	movl	-40(%rbp), %eax
	andl	$127, %eax
	testl	%eax, %eax
	jne	.L84
	movl	-40(%rbp), %eax
	sarl	$8, %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC26(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L85
.L84:
	leaq	.LC27(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L85
.L83:
	leaq	.LC28(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$1, %edi
	call	exit@PLT
.L85:
	call	getpid@PLT
	cltq
	movq	%rax, %rsi
	leaq	.LC29(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L86
	call	__stack_chk_fail@PLT
.L86:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	forkFunc, .-forkFunc
	.section	.rodata
.LC30:
	.string	"Error opening directory '%s'\n"
.LC31:
	.string	"."
.LC32:
	.string	".."
.LC33:
	.string	"lstat error for: %s\n"
	.text
	.globl	traverseDirectory
	.type	traverseDirectory, @function
traverseDirectory:
.LFB21:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$4096, %rsp
	orq	$0, (%rsp)
	subq	$464, %rsp
	movq	%rdi, -4520(%rbp)
	movl	%esi, -4524(%rbp)
	movl	%edx, -4528(%rbp)
	movl	%ecx, -4532(%rbp)
	movq	%r8, -4544(%rbp)
	movl	%r9d, -4536(%rbp)
	movq	24(%rbp), %rax
	movq	%rax, -4552(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-4520(%rbp), %rax
	movq	%rax, %rdi
	call	opendir@PLT
	movq	%rax, -4488(%rbp)
	cmpq	$0, -4488(%rbp)
	jne	.L88
	movq	-4520(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC30(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$-1, %edi
	call	exit@PLT
.L88:
	movl	$1, -4500(%rbp)
	movl	$2000, %edi
	call	malloc@PLT
	movq	%rax, -4480(%rbp)
	leaq	-4352(%rbp), %rdx
	movl	$0, %eax
	movl	$12, %ecx
	movq	%rdx, %rdi
	rep stosq
	jmp	.L89
.L99:
	movq	-4472(%rbp), %rax
	addq	$19, %rax
	leaq	.LC31(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L89
	movq	-4472(%rbp), %rax
	addq	$19, %rax
	leaq	.LC32(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L91
	jmp	.L89
.L91:
	movq	$-1, -4464(%rbp)
	movq	-4480(%rbp), %rax
	movl	$2000, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movq	-4520(%rbp), %rdx
	movq	-4480(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcat@PLT
	movq	-4480(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	movq	-4480(%rbp), %rax
	addq	%rdx, %rax
	movw	$47, (%rax)
	movq	-4472(%rbp), %rax
	leaq	19(%rax), %rdx
	movq	-4480(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcat@PLT
	movq	$0, -4496(%rbp)
	leaq	-4256(%rbp), %rdx
	movq	-4480(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	lstat@PLT
	testl	%eax, %eax
	jns	.L92
	movq	-4472(%rbp), %rax
	addq	$19, %rax
	movq	%rax, %rsi
	leaq	.LC33(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L92:
	movl	-4532(%rbp), %eax
	movl	%eax, -4384(%rbp)
	movq	-4496(%rbp), %rax
	movq	%rax, -4368(%rbp)
	movq	-4472(%rbp), %rax
	movq	%rax, -4448(%rbp)
	leaq	-4112(%rbp), %rax
	movq	%rax, -4440(%rbp)
	movq	-4480(%rbp), %rax
	movq	%rax, -4360(%rbp)
	movl	-4524(%rbp), %eax
	movl	%eax, -4432(%rbp)
	movl	-4500(%rbp), %eax
	movl	%eax, -4428(%rbp)
	leaq	-4256(%rbp), %rax
	movq	%rax, -4424(%rbp)
	movq	-4544(%rbp), %rax
	movq	%rax, -4400(%rbp)
	movq	-4552(%rbp), %rax
	movq	%rax, -4376(%rbp)
	movl	-4536(%rbp), %eax
	movl	%eax, -4392(%rbp)
	movq	-4464(%rbp), %rax
	movq	%rax, -4416(%rbp)
	movl	16(%rbp), %eax
	movl	%eax, -4408(%rbp)
	movl	-4528(%rbp), %eax
	movl	%eax, -4388(%rbp)
	cmpq	$0, -4544(%rbp)
	je	.L93
	leaq	displayForStringFlag(%rip), %rax
	movq	%rax, -4496(%rbp)
	jmp	.L94
.L93:
	cmpq	$0, -4552(%rbp)
	je	.L95
	leaq	displayFileTypeFlag(%rip), %rax
	movq	%rax, -4496(%rbp)
	jmp	.L94
.L95:
	cmpl	$0, -4536(%rbp)
	je	.L96
	leaq	displayForSizeFlag(%rip), %rax
	movq	%rax, -4496(%rbp)
	jmp	.L94
.L96:
	cmpl	$1, 16(%rbp)
	jne	.L97
	leaq	displayStatFlag(%rip), %rax
	movq	%rax, -4496(%rbp)
	jmp	.L94
.L97:
	leaq	displayForNoFlag(%rip), %rax
	movq	%rax, -4496(%rbp)
.L94:
	pushq	-4360(%rbp)
	pushq	-4368(%rbp)
	pushq	-4376(%rbp)
	pushq	-4384(%rbp)
	pushq	-4392(%rbp)
	pushq	-4400(%rbp)
	pushq	-4408(%rbp)
	pushq	-4416(%rbp)
	pushq	-4424(%rbp)
	pushq	-4432(%rbp)
	pushq	-4440(%rbp)
	pushq	-4448(%rbp)
	movq	-4496(%rbp), %rax
	call	*%rax
	addq	$96, %rsp
	movq	-4352(%rbp), %rax
	movq	-4344(%rbp), %rdx
	movq	%rax, -4448(%rbp)
	movq	%rdx, -4440(%rbp)
	movq	-4336(%rbp), %rax
	movq	-4328(%rbp), %rdx
	movq	%rax, -4432(%rbp)
	movq	%rdx, -4424(%rbp)
	movq	-4320(%rbp), %rax
	movq	-4312(%rbp), %rdx
	movq	%rax, -4416(%rbp)
	movq	%rdx, -4408(%rbp)
	movq	-4304(%rbp), %rax
	movq	-4296(%rbp), %rdx
	movq	%rax, -4400(%rbp)
	movq	%rdx, -4392(%rbp)
	movq	-4288(%rbp), %rax
	movq	-4280(%rbp), %rdx
	movq	%rax, -4384(%rbp)
	movq	%rdx, -4376(%rbp)
	movq	-4272(%rbp), %rax
	movq	-4264(%rbp), %rdx
	movq	%rax, -4368(%rbp)
	movq	%rdx, -4360(%rbp)
	addl	$1, -4500(%rbp)
	movq	-4472(%rbp), %rax
	movzbl	18(%rax), %eax
	cmpb	$4, %al
	jne	.L89
	movl	$2000, %edi
	call	malloc@PLT
	movq	%rax, -4456(%rbp)
	movq	-4520(%rbp), %rdx
	movq	-4456(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy@PLT
	movq	-4456(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	movq	-4456(%rbp), %rax
	addq	%rdx, %rax
	movw	$47, (%rax)
	movq	-4472(%rbp), %rax
	leaq	19(%rax), %rdx
	movq	-4456(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcat@PLT
	movl	-4528(%rbp), %eax
	leal	1(%rax), %edi
	movl	-4524(%rbp), %eax
	leal	1(%rax), %esi
	movl	-4536(%rbp), %r9d
	movq	-4544(%rbp), %r8
	movl	-4532(%rbp), %edx
	movq	-4456(%rbp), %rax
	pushq	-4552(%rbp)
	movl	16(%rbp), %ecx
	pushq	%rcx
	movl	%edx, %ecx
	movl	%edi, %edx
	movq	%rax, %rdi
	call	traverseDirectory
	addq	$16, %rsp
.L89:
	movq	-4488(%rbp), %rax
	movq	%rax, %rdi
	call	readdir@PLT
	movq	%rax, -4472(%rbp)
	cmpq	$0, -4472(%rbp)
	jne	.L99
	nop
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L100
	call	__stack_chk_fail@PLT
.L100:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	traverseDirectory, .-traverseDirectory
	.section	.rodata
.LC34:
	.string	"STARTING DIR\n[%s]\n"
.LC35:
	.string	"Invalid args"
.LC36:
	.string	"Ss:f:t:"
	.text
	.globl	main
	.type	main, @function
main:
.LFB22:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movl	%edi, -68(%rbp)
	movq	%rsi, -80(%rbp)
	movq	$0, -32(%rbp)
	movl	$0, -44(%rbp)
	movl	$0, -40(%rbp)
	movl	$0, -56(%rbp)
	movq	$0, -24(%rbp)
	movl	$0, -52(%rbp)
	movq	$0, -16(%rbp)
	movl	$0, -48(%rbp)
	movq	$0, -8(%rbp)
	movq	-80(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L102
	movq	-80(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movzbl	(%rax), %eax
	cmpb	$45, %al
	jne	.L103
.L102:
	leaq	.LC31(%rip), %rax
	movq	%rax, -16(%rbp)
	movl	$0, %eax
	call	get_current_directory_name
	movq	%rax, -32(%rbp)
	jmp	.L104
.L103:
	movq	-80(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-80(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -32(%rbp)
.L104:
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC34(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -44(%rbp)
	jmp	.L105
.L111:
	cmpl	$116, -36(%rbp)
	je	.L106
	cmpl	$116, -36(%rbp)
	jg	.L107
	cmpl	$115, -36(%rbp)
	je	.L108
	cmpl	$115, -36(%rbp)
	jg	.L107
	cmpl	$83, -36(%rbp)
	je	.L109
	cmpl	$102, -36(%rbp)
	je	.L110
	jmp	.L107
.L109:
	addl	$1, -56(%rbp)
	movl	$1, -48(%rbp)
	jmp	.L105
.L110:
	movq	optarg(%rip), %rax
	movq	%rax, -24(%rbp)
	addl	$1, -56(%rbp)
	jmp	.L105
.L108:
	addl	$1, -56(%rbp)
	movq	optarg(%rip), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	addl	%eax, -52(%rbp)
	jmp	.L105
.L106:
	addl	$1, -56(%rbp)
	movq	optarg(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L105
.L107:
	leaq	.LC35(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L105:
	movq	-80(%rbp), %rcx
	movl	-68(%rbp), %eax
	leaq	.LC36(%rip), %rdx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	getopt@PLT
	movl	%eax, -36(%rbp)
	cmpl	$-1, -36(%rbp)
	jne	.L111
	movl	-52(%rbp), %r9d
	movq	-24(%rbp), %r8
	movl	-56(%rbp), %ecx
	movl	-40(%rbp), %edx
	movl	-44(%rbp), %esi
	movq	-16(%rbp), %rax
	pushq	-8(%rbp)
	movl	-48(%rbp), %edi
	pushq	%rdi
	movq	%rax, %rdi
	call	traverseDirectory
	addq	$16, %rsp
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
