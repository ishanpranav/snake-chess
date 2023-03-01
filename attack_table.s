	.file	"attack_table.c"
# GNU C17 (Ubuntu 11.3.0-1ubuntu1~22.04) version 11.3.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.3.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O2 -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.p2align 4
	.globl	attack_table
	.type	attack_table, @function
attack_table:
.LFB26:
	.cfi_startproc
	endbr64	
	pushq	%r15	#
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
# src/attack_table.c:423:     struct AttackTable *instance = malloc(sizeof *instance);
	movl	$3072, %edi	#,
# src/attack_table.c:422: {
	pushq	%r14	#
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13	#
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12	#
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp	#
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx	#
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$104, %rsp	#,
	.cfi_def_cfa_offset 160
# src/attack_table.c:423:     struct AttackTable *instance = malloc(sizeof *instance);
	call	malloc@PLT	#
	movq	%rax, 88(%rsp)	# <retval>, %sfp
# src/attack_table.c:425:     if (instance == NULL)
	testq	%rax, %rax	# <retval>
	je	.L1	#,
	leaq	1024(%rax), %r13	#, ivtmp.103
# src/attack_table.c:430:     for (enum Square square = 0; square < SQUARES; square++)
	xorl	%r14d, %r14d	# square
# src/attack_table.c:21:     unsigned long long value = 1ull << square;
	movl	$1, %ebp	#, tmp299
	movq	%rax, %r15	# ivtmp.105, ivtmp.105
	.p2align 4,,10
	.p2align 3
.L3:
# src/attack_table.c:30:         if (h8Direction & FILE_NOT_A_MASK)
	movabsq	$-72340172838076674, %rax	#, _32
# src/attack_table.c:21:     unsigned long long value = 1ull << square;
	movl	%r14d, %ecx	# square, tmp466
	movq	%rbp, %rdx	# tmp299, value
# src/attack_table.c:37:             result |= a8Direction;
	movabsq	$9187201950435737471, %rsi	#, _33
# src/attack_table.c:78:         result |= fivePiSixthsRadians;
	movabsq	$4557430888798830399, %r12	#, tmp491
# src/attack_table.c:21:     unsigned long long value = 1ull << square;
	salq	%cl, %rdx	# tmp466, value
# src/attack_table.c:22:     unsigned long long h8Direction = value >> 7;
	movq	%rdx, %rbx	# value, h8Direction
# src/attack_table.c:24:     unsigned long long a1Direction = value << 7;
	movq	%rdx, %rdi	# value, a1Direction
# src/attack_table.c:64:     unsigned long long piThirdsRadians = value >> 15;
	movq	%rdx, %r11	# value, piThirdsRadians
# src/attack_table.c:65:     unsigned long long twoPiThirdsRadians = value >> 17;
	movq	%rdx, %r10	# value, twoPiThirdsRadians
# src/attack_table.c:22:     unsigned long long h8Direction = value >> 7;
	shrq	$7, %rbx	#, h8Direction
# src/attack_table.c:24:     unsigned long long a1Direction = value << 7;
	salq	$7, %rdi	#, a1Direction
# src/attack_table.c:66:     unsigned long long sevenPiSixthsRadians = value << 6;
	movq	%rdx, %r9	# value, sevenPiSixthsRadians
# src/attack_table.c:67:     unsigned long long elevenPiSixthsRadians = value << 10;
	movq	%rdx, %r8	# value, elevenPiSixthsRadians
# src/attack_table.c:30:         if (h8Direction & FILE_NOT_A_MASK)
	andq	%rbx, %rax	# h8Direction, _32
# src/attack_table.c:22:     unsigned long long h8Direction = value >> 7;
	movq	%rbx, 72(%rsp)	# h8Direction, %sfp
# src/attack_table.c:30:         if (h8Direction & FILE_NOT_A_MASK)
	movq	%rax, 16(%rsp)	# _32, %sfp
	movl	$0, %eax	#, result
	cmovne	%rbx, %rax	# h8Direction,, result
# src/attack_table.c:23:     unsigned long long a8Direction = value >> 9;
	movq	%rdx, %rbx	# value, a8Direction
# src/attack_table.c:24:     unsigned long long a1Direction = value << 7;
	movq	%rdi, 64(%rsp)	# a1Direction, %sfp
# src/attack_table.c:23:     unsigned long long a8Direction = value >> 9;
	shrq	$9, %rbx	#, a8Direction
# src/attack_table.c:37:             result |= a8Direction;
	movq	%rbx, %rcx	# a8Direction, tmp304
# src/attack_table.c:23:     unsigned long long a8Direction = value >> 9;
	movq	%rbx, 56(%rsp)	# a8Direction, %sfp
# src/attack_table.c:37:             result |= a8Direction;
	orq	%rax, %rcx	# result, tmp304
	andq	%rbx, %rsi	# a8Direction, _33
# src/attack_table.c:25:     unsigned long long h1Direction = value << 9;
	movq	%rdx, %rbx	# value, h1Direction
# src/attack_table.c:37:             result |= a8Direction;
	cmovne	%rcx, %rax	# tmp304,, result
	movq	%rsi, 24(%rsp)	# _33, %sfp
# src/attack_table.c:69:     unsigned long long fivePiThirdsRadians = value << 17;
	movq	%rdx, %rsi	# value, fivePiThirdsRadians
# src/attack_table.c:434:             instance->pawns[square][color] = createPawnBitboard(square, color);
	movq	%rax, (%r15)	# result, MEM[(long long unsigned int *)_27]
# src/attack_table.c:43:         if (a1Direction & FILE_NOT_H_MASK)
	movabsq	$9187201950435737471, %rax	#, _36
	andq	%rdi, %rax	# a1Direction, _36
	movq	%rax, 32(%rsp)	# _36, %sfp
	movl	$0, %eax	#, result
	cmovne	%rdi, %rax	# a1Direction,, result
# src/attack_table.c:25:     unsigned long long h1Direction = value << 9;
	salq	$9, %rbx	#, h1Direction
# src/attack_table.c:50:             result |= h1Direction;
	movabsq	$-72340172838076674, %rdi	#, _37
	movq	%rbx, %rcx	# h1Direction, tmp306
# src/attack_table.c:25:     unsigned long long h1Direction = value << 9;
	movq	%rbx, 48(%rsp)	# h1Direction, %sfp
# src/attack_table.c:50:             result |= h1Direction;
	orq	%rax, %rcx	# result, tmp306
	andq	%rbx, %rdi	# h1Direction, _37
# src/attack_table.c:63:     unsigned long long fivePiSixthsRadians = value >> 10;
	movq	%rdx, %rbx	# value, fivePiSixthsRadians
# src/attack_table.c:50:             result |= h1Direction;
	cmovne	%rcx, %rax	# tmp306,, result
# src/attack_table.c:62:     unsigned long long piSixthsRadians = value >> 6;
	movq	%rdx, %rcx	# value, piSixthsRadians
# src/attack_table.c:50:             result |= h1Direction;
	movq	%rdi, 40(%rsp)	# _37, %sfp
# src/attack_table.c:68:     unsigned long long fourPiThirdsRadians = value << 15;
	movq	%rdx, %rdi	# value, fourPiThirdsRadians
# src/attack_table.c:62:     unsigned long long piSixthsRadians = value >> 6;
	shrq	$6, %rcx	#, piSixthsRadians
# src/attack_table.c:434:             instance->pawns[square][color] = createPawnBitboard(square, color);
	movq	%rax, 8(%r15)	# result, MEM[(long long unsigned int *)_27 + 8B]
# src/attack_table.c:63:     unsigned long long fivePiSixthsRadians = value >> 10;
	shrq	$10, %rbx	#, fivePiSixthsRadians
# src/attack_table.c:64:     unsigned long long piThirdsRadians = value >> 15;
	shrq	$15, %r11	#, piThirdsRadians
# src/attack_table.c:71:     if (piSixthsRadians & FILE_NOT_A_NOR_B_MASK)
	movabsq	$-217020518514230020, %rax	#, result
# src/attack_table.c:65:     unsigned long long twoPiThirdsRadians = value >> 17;
	shrq	$17, %r10	#, twoPiThirdsRadians
# src/attack_table.c:66:     unsigned long long sevenPiSixthsRadians = value << 6;
	salq	$6, %r9	#, sevenPiSixthsRadians
# src/attack_table.c:68:     unsigned long long fourPiThirdsRadians = value << 15;
	salq	$15, %rdi	#, fourPiThirdsRadians
# src/attack_table.c:69:     unsigned long long fivePiThirdsRadians = value << 17;
	salq	$17, %rsi	#, fivePiThirdsRadians
# src/attack_table.c:67:     unsigned long long elevenPiSixthsRadians = value << 10;
	salq	$10, %r8	#, elevenPiSixthsRadians
# src/attack_table.c:71:     if (piSixthsRadians & FILE_NOT_A_NOR_B_MASK)
	andq	%rcx, %rax	# piSixthsRadians, result
	cmovne	%rcx, %rax	# result,, piSixthsRadians, result
# src/attack_table.c:78:         result |= fivePiSixthsRadians;
	movq	%rax, %rcx	# result, tmp308
	orq	%rbx, %rcx	# fivePiSixthsRadians, tmp308
	testq	%r12, %rbx	# tmp491, fivePiSixthsRadians
# src/attack_table.c:83:         result |= piThirdsRadians;
	movabsq	$-72340172838076674, %rbx	#, tmp493
# src/attack_table.c:78:         result |= fivePiSixthsRadians;
	cmovne	%rcx, %rax	# tmp308,, result
# src/attack_table.c:83:         result |= piThirdsRadians;
	movq	%rax, %rcx	# result, tmp334
	orq	%r11, %rcx	# piThirdsRadians, tmp334
	testq	%rbx, %r11	# tmp493, piThirdsRadians
# src/attack_table.c:88:         result |= twoPiThirdsRadians;
	movabsq	$9187201950435737471, %r11	#, tmp495
# src/attack_table.c:83:         result |= piThirdsRadians;
	cmovne	%rcx, %rax	# tmp334,, result
# src/attack_table.c:88:         result |= twoPiThirdsRadians;
	movq	%rax, %rcx	# result, tmp310
	orq	%r10, %rcx	# twoPiThirdsRadians, tmp310
	testq	%r11, %r10	# tmp495, twoPiThirdsRadians
# src/attack_table.c:116:     int destinationRank = square / 8;
	movl	%r14d, %r10d	# square, _109
# src/attack_table.c:88:         result |= twoPiThirdsRadians;
	cmovne	%rcx, %rax	# tmp310,, result
# src/attack_table.c:93:         result |= sevenPiSixthsRadians;
	movq	%rax, %rcx	# result, tmp323
	orq	%r9, %rcx	# sevenPiSixthsRadians, tmp323
	testq	%r12, %r9	# tmp497, sevenPiSixthsRadians
# src/attack_table.c:117:     int destinationFile = square % 8;
	movl	%r14d, %r12d	# square, destinationFile
# src/attack_table.c:98:         result |= elevenPiSixthsRadians;
	movabsq	$-217020518514230020, %r9	#, tmp499
# src/attack_table.c:93:         result |= sevenPiSixthsRadians;
	cmovne	%rcx, %rax	# tmp323,, result
# src/attack_table.c:98:         result |= elevenPiSixthsRadians;
	movq	%rax, %rcx	# result, tmp312
	orq	%r8, %rcx	# elevenPiSixthsRadians, tmp312
	testq	%r9, %r8	# tmp499, elevenPiSixthsRadians
	cmovne	%rcx, %rax	# tmp312,, result
# src/attack_table.c:103:         result |= fourPiThirdsRadians;
	movq	%rax, %rcx	# result, tmp330
	orq	%rdi, %rcx	# fourPiThirdsRadians, tmp330
	testq	%r11, %rdi	# tmp501, fourPiThirdsRadians
	cmovne	%rcx, %rax	# tmp330,, result
# src/attack_table.c:108:         result |= fivePiThirdsRadians;
	movq	%rax, %rcx	# result, tmp314
	orq	%rsi, %rcx	# fivePiThirdsRadians, tmp314
	testq	%rbx, %rsi	# tmp503, fivePiThirdsRadians
	cmovne	%rcx, %rax	# tmp314,, result
# src/attack_table.c:116:     int destinationRank = square / 8;
	shrl	$3, %r10d	#, _109
# src/attack_table.c:117:     int destinationFile = square % 8;
	andl	$7, %r12d	#, destinationFile
# src/attack_table.c:118:     int rank = destinationRank + 1;
	leal	1(%r10), %r9d	#, rank
# src/attack_table.c:119:     int file = destinationFile + 1;
	leal	1(%r12), %r11d	#, file
# src/attack_table.c:122:     while (rank < 7 && file < 7)
	cmpl	$6, %r9d	#, rank
# src/attack_table.c:437:         instance->knights[square] = createKnightBitboard(square);
	movq	%rax, 0(%r13)	# result, MEM[(long long unsigned int *)_5]
# src/attack_table.c:122:     while (rank < 7 && file < 7)
	setle	%sil	#, _273
# src/attack_table.c:122:     while (rank < 7 && file < 7)
	cmpl	$6, %r11d	#, file
# src/attack_table.c:122:     while (rank < 7 && file < 7)
	setle	%dil	#, _272
	jg	.L51	#,
	testb	%sil, %sil	# _273
	je	.L51	#,
	movq	%rdx, 8(%rsp)	# value, %sfp
	movl	%r12d, %ebx	# destinationFile, _81
	movl	%r9d, %r8d	# rank, rank
# src/attack_table.c:120:     unsigned long long result = 0ull;
	xorl	%eax, %eax	# result
	subl	%r10d, %ebx	# _109, _81
	.p2align 4,,10
	.p2align 3
.L15:
# src/attack_table.c:124:         result |= 1ull << (rank * 8 + file);
	leal	(%r8,%r8,8), %ecx	#, tmp243
	movq	%rbp, %rdx	# tmp299, tmp245
# src/attack_table.c:125:         rank++;
	addl	$1, %r8d	#, rank
# src/attack_table.c:124:         result |= 1ull << (rank * 8 + file);
	addl	%ebx, %ecx	# _81, tmp244
	salq	%cl, %rdx	# tmp244, tmp245
# src/attack_table.c:122:     while (rank < 7 && file < 7)
	leal	(%r8,%rbx), %ecx	#, file
# src/attack_table.c:124:         result |= 1ull << (rank * 8 + file);
	orq	%rdx, %rax	# tmp245, result
# src/attack_table.c:122:     while (rank < 7 && file < 7)
	cmpl	$6, %ecx	#, file
	jg	.L131	#,
	cmpl	$6, %r8d	#, rank
	jle	.L15	#,
.L131:
	movq	8(%rsp), %rdx	# %sfp, value
.L14:
# src/attack_table.c:129:     rank = destinationRank - 1;
	leal	-1(%r10), %r8d	#, rank
# src/attack_table.c:132:     while (rank > 0 && file < 7)
	testl	%r8d, %r8d	# rank
	setg	8(%rsp)	#, %sfp
	movzbl	8(%rsp), %ebx	# %sfp, _281
# src/attack_table.c:132:     while (rank > 0 && file < 7)
	testb	%dil, %dil	# _272
	je	.L17	#,
	testb	%bl, %bl	# _281
	je	.L17	#,
	leal	(%r11,%r8,8), %ecx	#, ivtmp.83
	movl	%r8d, %edi	# rank, rank
	.p2align 4,,10
	.p2align 3
.L18:
# src/attack_table.c:134:         result |= 1ull << (rank * 8 + file);
	movq	%rbp, %rbx	# tmp299, tmp254
# src/attack_table.c:135:         rank--;
	subl	$1, %edi	#, rank
# src/attack_table.c:134:         result |= 1ull << (rank * 8 + file);
	salq	%cl, %rbx	# ivtmp.83, tmp254
# src/attack_table.c:132:     while (rank > 0 && file < 7)
	subl	$7, %ecx	#, ivtmp.83
# src/attack_table.c:134:         result |= 1ull << (rank * 8 + file);
	orq	%rbx, %rax	# tmp254, result
# src/attack_table.c:132:     while (rank > 0 && file < 7)
	movl	%r10d, %ebx	# _109, tmp256
	subl	%edi, %ebx	# rank, tmp256
	addl	%r12d, %ebx	# destinationFile, file
# src/attack_table.c:132:     while (rank > 0 && file < 7)
	cmpl	$6, %ebx	#, file
	jg	.L17	#,
	testl	%edi, %edi	# rank
	jg	.L18	#,
.L17:
# src/attack_table.c:140:     file = destinationFile - 1;
	leal	-1(%r12), %ebx	#, file
# src/attack_table.c:142:     while (rank < 7 && file > 0)
	testl	%ebx, %ebx	# file
# src/attack_table.c:142:     while (rank < 7 && file > 0)
	setg	87(%rsp)	#, %sfp
	jle	.L24	#,
	testb	%sil, %sil	# _273
	je	.L20	#,
	leal	(%rbx,%r9,8), %ecx	#, ivtmp.72
	movl	%r9d, %esi	# rank, rank
	.p2align 4,,10
	.p2align 3
.L21:
# src/attack_table.c:144:         result |= 1ull << (rank * 8 + file);
	movq	%rbp, %rdi	# tmp299, tmp264
# src/attack_table.c:145:         rank++;
	addl	$1, %esi	#, rank
# src/attack_table.c:144:         result |= 1ull << (rank * 8 + file);
	salq	%cl, %rdi	# ivtmp.72, tmp264
# src/attack_table.c:142:     while (rank < 7 && file > 0)
	addl	$7, %ecx	#, ivtmp.72
# src/attack_table.c:144:         result |= 1ull << (rank * 8 + file);
	orq	%rdi, %rax	# tmp264, result
# src/attack_table.c:142:     while (rank < 7 && file > 0)
	movl	%r10d, %edi	# _109, tmp266
	subl	%esi, %edi	# rank, tmp266
	addl	%r12d, %edi	# destinationFile, file
# src/attack_table.c:142:     while (rank < 7 && file > 0)
	testl	%edi, %edi	# file
	jle	.L23	#,
	cmpl	$6, %esi	#, rank
	jle	.L21	#,
.L23:
# src/attack_table.c:152:     while (rank > 0 && file > 0)
	cmpb	$0, 87(%rsp)	#, %sfp
	je	.L49	#,
	cmpb	$0, 8(%rsp)	#, %sfp
	je	.L49	#,
.L47:
	movq	%rdx, 8(%rsp)	# value, %sfp
	movl	%r12d, %edi	# destinationFile, _222
# src/attack_table.c:142:     while (rank < 7 && file > 0)
	movl	%r8d, %esi	# rank, rank
	subl	%r10d, %edi	# _109, _222
	.p2align 4,,10
	.p2align 3
.L25:
# src/attack_table.c:154:         result |= 1ull << (rank * 8 + file);
	leal	(%rsi,%rsi,8), %ecx	#, tmp274
	movq	%rbp, %rdx	# tmp299, tmp276
# src/attack_table.c:155:         rank--;
	subl	$1, %esi	#, rank
# src/attack_table.c:154:         result |= 1ull << (rank * 8 + file);
	addl	%edi, %ecx	# _222, tmp275
	salq	%cl, %rdx	# tmp275, tmp276
# src/attack_table.c:152:     while (rank > 0 && file > 0)
	leal	(%rsi,%rdi), %ecx	#, file
# src/attack_table.c:154:         result |= 1ull << (rank * 8 + file);
	orq	%rdx, %rax	# tmp276, result
# src/attack_table.c:152:     while (rank > 0 && file > 0)
	testl	%ecx, %ecx	# file
	jle	.L134	#,
	testl	%esi, %esi	# rank
	jg	.L25	#,
.L134:
# src/attack_table.c:438:         instance->bishops[square] = createBishopBitboard(square);
	movq	%rax, 512(%r13)	# result, MEM[(long long unsigned int *)_5 + 512B]
	movq	8(%rsp), %rdx	# %sfp, value
# src/attack_table.c:246:     unsigned long long result = 0ull;
	xorl	%eax, %eax	# result
# src/attack_table.c:248:     for (int rank = destinationRank + 1; rank < 7; rank++)
	cmpl	$6, %r9d	#, rank
	jg	.L45	#,
.L44:
	leal	(%r12,%r9,8), %ecx	#, ivtmp.51
# src/attack_table.c:246:     unsigned long long result = 0ull;
	xorl	%eax, %eax	# result
	.p2align 4,,10
	.p2align 3
.L29:
# src/attack_table.c:250:         result |= 1ull << (rank * 8 + destinationFile);
	movq	%rbp, %rsi	# tmp299, tmp284
# src/attack_table.c:248:     for (int rank = destinationRank + 1; rank < 7; rank++)
	addl	$1, %r9d	#, rank
# src/attack_table.c:250:         result |= 1ull << (rank * 8 + destinationFile);
	salq	%cl, %rsi	# ivtmp.51, tmp284
# src/attack_table.c:248:     for (int rank = destinationRank + 1; rank < 7; rank++)
	addl	$8, %ecx	#, ivtmp.51
# src/attack_table.c:250:         result |= 1ull << (rank * 8 + destinationFile);
	orq	%rsi, %rax	# tmp284, result
# src/attack_table.c:248:     for (int rank = destinationRank + 1; rank < 7; rank++)
	cmpl	$7, %r9d	#, rank
	jne	.L29	#,
.L28:
# src/attack_table.c:253:     for (int rank = destinationRank - 1; rank > 0; rank--)
	testl	%r8d, %r8d	# rank
	jle	.L30	#,
.L45:
	leal	(%r12,%r8,8), %ecx	#, ivtmp.44
	.p2align 4,,10
	.p2align 3
.L31:
# src/attack_table.c:255:         result |= 1ull << (rank * 8 + destinationFile);
	movq	%rbp, %rsi	# tmp299, tmp287
	salq	%cl, %rsi	# ivtmp.44, tmp287
# src/attack_table.c:253:     for (int rank = destinationRank - 1; rank > 0; rank--)
	subl	$8, %ecx	#, ivtmp.44
# src/attack_table.c:255:         result |= 1ull << (rank * 8 + destinationFile);
	orq	%rsi, %rax	# tmp287, result
# src/attack_table.c:253:     for (int rank = destinationRank - 1; rank > 0; rank--)
	subl	$1, %r8d	#, rank
	jne	.L31	#,
.L30:
# src/attack_table.c:258:     for (int file = destinationFile + 1; file < 7; file++)
	cmpl	$6, %r11d	#, file
	jg	.L32	#,
# src/attack_table.c:260:         result |= 1ull << (destinationRank * 8 + file);
	leal	0(,%r10,8), %esi	#, _90
	leal	(%rsi,%r11), %ecx	#, ivtmp.36
	addl	$7, %esi	#, _259
	.p2align 4,,10
	.p2align 3
.L33:
# src/attack_table.c:260:         result |= 1ull << (destinationRank * 8 + file);
	movq	%rbp, %rdi	# tmp299, tmp289
	salq	%cl, %rdi	# ivtmp.36, tmp289
# src/attack_table.c:258:     for (int file = destinationFile + 1; file < 7; file++)
	addl	$1, %ecx	#, ivtmp.36
# src/attack_table.c:260:         result |= 1ull << (destinationRank * 8 + file);
	orq	%rdi, %rax	# tmp289, result
# src/attack_table.c:258:     for (int file = destinationFile + 1; file < 7; file++)
	cmpl	%ecx, %esi	# ivtmp.36, _259
	jne	.L33	#,
.L32:
# src/attack_table.c:263:     for (int file = destinationFile - 1; file > 0; file--)
	testl	%ebx, %ebx	# file
	jle	.L34	#,
# src/attack_table.c:265:         result |= 1ull << (destinationRank * 8 + file);
	sall	$3, %r10d	#, _98
	leal	(%r10,%rbx), %ecx	#, ivtmp.28
	.p2align 4,,10
	.p2align 3
.L35:
# src/attack_table.c:265:         result |= 1ull << (destinationRank * 8 + file);
	movq	%rbp, %rsi	# tmp299, tmp291
	salq	%cl, %rsi	# ivtmp.28, tmp291
# src/attack_table.c:263:     for (int file = destinationFile - 1; file > 0; file--)
	subl	$1, %ecx	#, ivtmp.28
# src/attack_table.c:265:         result |= 1ull << (destinationRank * 8 + file);
	orq	%rsi, %rax	# tmp291, result
# src/attack_table.c:263:     for (int file = destinationFile - 1; file > 0; file--)
	cmpl	%ecx, %r10d	# ivtmp.28, _98
	jne	.L35	#,
.L34:
# src/attack_table.c:333:     unsigned long long rank8 = value >> 8;
	movq	%rdx, %rsi	# value, rank8
# src/attack_table.c:331:     unsigned long long fileA = value >> 1;
	movq	%rdx, %rcx	# value, fileA
# src/attack_table.c:439:         instance->rooks[square] = createRookBitboard(square);
	movq	%rax, 1024(%r13)	# result, MEM[(long long unsigned int *)_5 + 1024B]
# src/attack_table.c:335:     unsigned long long fileH = value << 1;
	leaq	(%rdx,%rdx), %rax	#, fileH
# src/attack_table.c:333:     unsigned long long rank8 = value >> 8;
	shrq	$8, %rsi	#, rank8
# src/attack_table.c:337:     unsigned long long rank1 = value << 8;
	salq	$8, %rdx	#, rank1
# src/attack_table.c:343:         result |= fileA;
	movabsq	$9187201950435737471, %rbx	#, tmp454
# src/attack_table.c:339:     unsigned long long result = rank1 | rank8;
	orq	%rsi, %rdx	# rank8, result
# src/attack_table.c:331:     unsigned long long fileA = value >> 1;
	shrq	%rcx	# fileA
# src/attack_table.c:343:         result |= fileA;
	movq	%rdx, %rsi	# result, tmp316
	orq	%rcx, %rsi	# fileA, tmp316
	testq	%rbx, %rcx	# tmp454, fileA
# src/attack_table.c:348:         result |= h8;
	movq	72(%rsp), %rcx	# %sfp, h8Direction
# src/attack_table.c:358:         result |= fileH;
	movabsq	$-72340172838076674, %rbx	#, tmp460
# src/attack_table.c:343:         result |= fileA;
	cmovne	%rsi, %rdx	# tmp316,, result
# src/attack_table.c:348:         result |= h8;
	orq	%rdx, %rcx	# result, h8Direction
	cmpq	$0, 16(%rsp)	#, %sfp
	cmovne	%rcx, %rdx	# tmp325,, result
# src/attack_table.c:353:         result |= a8;
	movq	56(%rsp), %rcx	# %sfp, a8Direction
	orq	%rdx, %rcx	# result, a8Direction
	cmpq	$0, 24(%rsp)	#, %sfp
	cmovne	%rcx, %rdx	# tmp318,, result
# src/attack_table.c:358:         result |= fileH;
	movq	%rdx, %rcx	# result, tmp332
	orq	%rax, %rcx	# fileH, tmp332
	testq	%rbx, %rax	# tmp460, fileH
# src/attack_table.c:363:         result |= a1;
	movq	64(%rsp), %rax	# %sfp, a1Direction
# src/attack_table.c:358:         result |= fileH;
	cmovne	%rcx, %rdx	# tmp332,, result
# src/attack_table.c:363:         result |= a1;
	orq	%rdx, %rax	# result, a1Direction
	cmpq	$0, 32(%rsp)	#, %sfp
	cmovne	%rax, %rdx	# tmp320,, result
# src/attack_table.c:368:         result |= h1;
	movq	48(%rsp), %rax	# %sfp, h1Direction
	orq	%rdx, %rax	# result, h1Direction
	cmpq	$0, 40(%rsp)	#, %sfp
	cmovne	%rax, %rdx	# tmp327,, result
# src/attack_table.c:430:     for (enum Square square = 0; square < SQUARES; square++)
	addl	$1, %r14d	#, square
# src/attack_table.c:430:     for (enum Square square = 0; square < SQUARES; square++)
	addq	$8, %r13	#, ivtmp.103
	addq	$16, %r15	#, ivtmp.105
# src/attack_table.c:440:         instance->kings[square] = createKingBitboard(square);
	movq	%rdx, 1528(%r13)	# result, MEM[(long long unsigned int *)_5 + 1536B]
# src/attack_table.c:430:     for (enum Square square = 0; square < SQUARES; square++)
	cmpl	$64, %r14d	#, square
	jne	.L3	#,
# src/attack_table.c:444:     unsigned long long occupancy = setOccupancy(4095, popcountll(mask), mask);
	movabsq	$9079539427579068672, %rdi	#, tmp301
	xorl	%eax, %eax	#
	call	popcountll@PLT	#
# src/attack_table.c:446:     bitboard_print(occupancy);
	xorl	%edi, %edi	#
	call	bitboard_print@PLT	#
.L1:
# src/attack_table.c:449: }
	movq	88(%rsp), %rax	# %sfp,
	addq	$104, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx	#
	.cfi_def_cfa_offset 48
	popq	%rbp	#
	.cfi_def_cfa_offset 40
	popq	%r12	#
	.cfi_def_cfa_offset 32
	popq	%r13	#
	.cfi_def_cfa_offset 24
	popq	%r14	#
	.cfi_def_cfa_offset 16
	popq	%r15	#
	.cfi_def_cfa_offset 8
	ret	
	.p2align 4,,10
	.p2align 3
.L51:
	.cfi_restore_state
# src/attack_table.c:120:     unsigned long long result = 0ull;
	xorl	%eax, %eax	# result
	jmp	.L14	#
	.p2align 4,,10
	.p2align 3
.L49:
# src/attack_table.c:438:         instance->bishops[square] = createBishopBitboard(square);
	movq	%rax, 512(%r13)	# result, MEM[(long long unsigned int *)_5 + 512B]
	jmp	.L44	#
.L20:
# src/attack_table.c:152:     while (rank > 0 && file > 0)
	cmpb	$0, 8(%rsp)	#, %sfp
	jne	.L47	#,
.L24:
# src/attack_table.c:438:         instance->bishops[square] = createBishopBitboard(square);
	movq	%rax, 512(%r13)	# result, MEM[(long long unsigned int *)_5 + 512B]
# src/attack_table.c:248:     for (int rank = destinationRank + 1; rank < 7; rank++)
	cmpl	$6, %r9d	#, rank
	jle	.L44	#,
# src/attack_table.c:246:     unsigned long long result = 0ull;
	xorl	%eax, %eax	# result
	jmp	.L28	#
	.cfi_endproc
.LFE26:
	.size	attack_table, .-attack_table
	.p2align 4
	.globl	finalize_attack_table
	.type	finalize_attack_table, @function
finalize_attack_table:
.LFB27:
	.cfi_startproc
	endbr64	
# src/attack_table.c:453:     free(this);
	jmp	free@PLT	#
	.cfi_endproc
.LFE27:
	.size	finalize_attack_table, .-finalize_attack_table
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
