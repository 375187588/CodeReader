/*	$NetBSD: divsi3.S,v 1.2 1997/10/17 18:43:48 mark Exp $	*/

/*
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <machine/asm.h>

ENTRY(__umodsi3)
	stmfd	sp!, {lr}
	bl	L_udivide
	mov	r0, r1
	ldmfd	sp!, {pc}

ENTRY(__modsi3)
	stmfd	sp!, {lr}
	bl	L_divide
	mov	r0, r1
	ldmfd	sp!, {pc}

L_overflow:
	mov	r0, #8			/* SIGFPE */
	bl	_raise			/* raise it */
	mov	r0, #0
	mov	pc, lr

ENTRY(__udivsi3)
L_udivide:				/* r0 = r0 / r1; r1 = r0 % r1 */
	eor     r0, r1, r0 
	eor     r1, r0, r1 
	eor     r0, r1, r0 
					/* r0 = r1 / r0; r1 = r1 % r0 */
	cmp	r0, #1
	bcc	L_overflow
	beq	L_divide_l0
	mov	ip, #0
	movs	r1, r1
	bpl	L_divide_l1
	orr	ip, ip, #0x20000000	/* ip bit 0x20000000 = -ve r1 */
	movs	r1, r1, lsr #1
	orrcs	ip, ip, #0x10000000	/* ip bit 0x10000000 = bit 0 of r1 */
	b	L_divide_l1

L_divide_l0:				/* r0 == 1 */
	mov	r0, r1
	mov	r1, #0
	mov	pc, lr

ENTRY(__divsi3)
L_divide:				/* r0 = r0 / r1; r1 = r0 % r1 */
	eor     r0, r1, r0 
	eor     r1, r0, r1 
	eor     r0, r1, r0 
					/* r0 = r1 / r0; r1 = r1 % r0 */
	cmp	r0, #1
	bcc	L_overflow
	beq	L_divide_l0
	ands	ip, r0, #0x80000000
	rsbmi	r0, r0, #0
	ands	r2, r1, #0x80000000
	eor	ip, ip, r2
	rsbmi	r1, r1, #0
	orr	ip, r2, ip, lsr #1	/* ip bit 0x40000000 = -ve division */
					/* ip bit 0x80000000 = -ve remainder */

L_divide_l1:
	mov	r2, #1
	mov	r3, #0

	cmp	r1, r0
	bcc	L_divide_b0
	cmp	r1, r0, lsl #1
	bcc	L_divide_b1
	cmp	r1, r0, lsl #2
	bcc	L_divide_b2
	cmp	r1, r0, lsl #3
	bcc	L_divide_b3
	cmp	r1, r0, lsl #4
	bcc	L_divide_b4
	cmp	r1, r0, lsl #5
	bcc	L_divide_b5
	cmp	r1, r0, lsl #6
	bcc	L_divide_b6
	cmp	r1, r0, lsl #7
	bcc	L_divide_b7
	cmp	r1, r0, lsl #8
	bcc	L_divide_b8
	cmp	r1, r0, lsl #9
	bcc	L_divide_b9
	cmp	r1, r0, lsl #10
	bcc	L_divide_b10
	cmp	r1, r0, lsl #11
	bcc	L_divide_b11
	cmp	r1, r0, lsl #12
	bcc	L_divide_b12
	cmp	r1, r0, lsl #13
	bcc	L_divide_b13
	cmp	r1, r0, lsl #14
	bcc	L_divide_b14
	cmp	r1, r0, lsl #15
	bcc	L_divide_b15
	cmp	r1, r0, lsl #16
	bcc	L_divide_b16
	cmp	r1, r0, lsl #17
	bcc	L_divide_b17
	cmp	r1, r0, lsl #18
	bcc	L_divide_b18
	cmp	r1, r0, lsl #19
	bcc	L_divide_b19
	cmp	r1, r0, lsl #20
	bcc	L_divide_b20
	cmp	r1, r0, lsl #21
	bcc	L_divide_b21
	cmp	r1, r0, lsl #22
	bcc	L_divide_b22
	cmp	r1, r0, lsl #23
	bcc	L_divide_b23
	cmp	r1, r0, lsl #24
	bcc	L_divide_b24
	cmp	r1, r0, lsl #25
	bcc	L_divide_b25
	cmp	r1, r0, lsl #26
	bcc	L_divide_b26
	cmp	r1, r0, lsl #27
	bcc	L_divide_b27
	cmp	r1, r0, lsl #28
	bcc	L_divide_b28
	cmp	r1, r0, lsl #29
	bcc	L_divide_b29
	cmp	r1, r0, lsl #30
	bcc	L_divide_b30
	cmp	r1, r0, lsl #31
	subhs	r1, r1,r0, lsl #31
	addhs	r3, r3,r2, lsl #31
	cmp	r1, r0, lsl #30
	subhs	r1, r1,r0, lsl #30
	addhs	r3, r3,r2, lsl #30
L_divide_b30:
	cmp	r1, r0, lsl #29
	subhs	r1, r1,r0, lsl #29
	addhs	r3, r3,r2, lsl #29
L_divide_b29:
	cmp	r1, r0, lsl #28
	subhs	r1, r1,r0, lsl #28
	addhs	r3, r3,r2, lsl #28
L_divide_b28:
	cmp	r1, r0, lsl #27
	subhs	r1, r1,r0, lsl #27
	addhs	r3, r3,r2, lsl #27
L_divide_b27:
	cmp	r1, r0, lsl #26
	subhs	r1, r1,r0, lsl #26
	addhs	r3, r3,r2, lsl #26
L_divide_b26:
	cmp	r1, r0, lsl #25
	subhs	r1, r1,r0, lsl #25
	addhs	r3, r3,r2, lsl #25
L_divide_b25:
	cmp	r1, r0, lsl #24
	subhs	r1, r1,r0, lsl #24
	addhs	r3, r3,r2, lsl #24
L_divide_b24:
	cmp	r1, r0, lsl #23
	subhs	r1, r1,r0, lsl #23
	addhs	r3, r3,r2, lsl #23
L_divide_b23:
	cmp	r1, r0, lsl #22
	subhs	r1, r1,r0, lsl #22
	addhs	r3, r3,r2, lsl #22
L_divide_b22:
	cmp	r1, r0, lsl #21
	subhs	r1, r1,r0, lsl #21
	addhs	r3, r3,r2, lsl #21
L_divide_b21:
	cmp	r1, r0, lsl #20
	subhs	r1, r1,r0, lsl #20
	addhs	r3, r3,r2, lsl #20
L_divide_b20:
	cmp	r1, r0, lsl #19
	subhs	r1, r1,r0, lsl #19
	addhs	r3, r3,r2, lsl #19
L_divide_b19:
	cmp	r1, r0, lsl #18
	subhs	r1, r1,r0, lsl #18
	addhs	r3, r3,r2, lsl #18
L_divide_b18:
	cmp	r1, r0, lsl #17
	subhs	r1, r1,r0, lsl #17
	addhs	r3, r3,r2, lsl #17
L_divide_b17:
	cmp	r1, r0, lsl #16
	subhs	r1, r1,r0, lsl #16
	addhs	r3, r3,r2, lsl #16
L_divide_b16:
	cmp	r1, r0, lsl #15
	subhs	r1, r1,r0, lsl #15
	addhs	r3, r3,r2, lsl #15
L_divide_b15:
	cmp	r1, r0, lsl #14
	subhs	r1, r1,r0, lsl #14
	addhs	r3, r3,r2, lsl #14
L_divide_b14:
	cmp	r1, r0, lsl #13
	subhs	r1, r1,r0, lsl #13
	addhs	r3, r3,r2, lsl #13
L_divide_b13:
	cmp	r1, r0, lsl #12
	subhs	r1, r1,r0, lsl #12
	addhs	r3, r3,r2, lsl #12
L_divide_b12:
	cmp	r1, r0, lsl #11
	subhs	r1, r1,r0, lsl #11
	addhs	r3, r3,r2, lsl #11
L_divide_b11:
	cmp	r1, r0, lsl #10
	subhs	r1, r1,r0, lsl #10
	addhs	r3, r3,r2, lsl #10
L_divide_b10:
	cmp	r1, r0, lsl #9
	subhs	r1, r1,r0, lsl #9
	addhs	r3, r3,r2, lsl #9
L_divide_b9:
	cmp	r1, r0, lsl #8
	subhs	r1, r1,r0, lsl #8
	addhs	r3, r3,r2, lsl #8
L_divide_b8:
	cmp	r1, r0, lsl #7
	subhs	r1, r1,r0, lsl #7
	addhs	r3, r3,r2, lsl #7
L_divide_b7:
	cmp	r1, r0, lsl #6
	subhs	r1, r1,r0, lsl #6
	addhs	r3, r3,r2, lsl #6
L_divide_b6:
	cmp	r1, r0, lsl #5
	subhs	r1, r1,r0, lsl #5
	addhs	r3, r3,r2, lsl #5
L_divide_b5:
	cmp	r1, r0, lsl #4
	subhs	r1, r1,r0, lsl #4
	addhs	r3, r3,r2, lsl #4
L_divide_b4:
	cmp	r1, r0, lsl #3
	subhs	r1, r1,r0, lsl #3
	addhs	r3, r3,r2, lsl #3
L_divide_b3:
	cmp	r1, r0, lsl #2
	subhs	r1, r1,r0, lsl #2
	addhs	r3, r3,r2, lsl #2
L_divide_b2:
	cmp	r1, r0, lsl #1
	subhs	r1, r1,r0, lsl #1
	addhs	r3, r3,r2, lsl #1
L_divide_b1:
	cmp	r1, r0
	subhs	r1, r1, r0
	addhs	r3, r3, r2
L_divide_b0:

	tst	ip, #0x20000000
	bne	L_udivide_l1
	mov	r0, r3
	cmp	ip, #0
	rsbmi	r1, r1, #0
	movs	ip, ip, lsl #1
	bicmi	r0, r0, #0x80000000	/* Fix incase we divided 0x80000000 */
	rsbmi	r0, r0, #0
	mov	pc, lr

L_udivide_l1:
	tst	ip, #0x10000000
	mov	r1, r1, lsl #1
	orrne	r1, r1, #1
	mov	r3, r3, lsl #1
	cmp	r1, r0
	subhs	r1, r1, r0
	addhs	r3, r3, r2
	mov	r0, r3
	mov	pc, lr
