; Listing generated by Microsoft (R) Optimizing Compiler Version 19.37.32705.0 

	TITLE	D:\DevDragon\XashFE\dev\src\temp\engine\!debug\pm_debug.obj
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRTD
INCLUDELIB OLDNAMES

PUBLIC	_PM_ParticleLine
PUBLIC	_PM_DrawBBox
PUBLIC	__real@40000000
EXTRN	_CL_Particle:PROC
EXTRN	_VectorNormalizeLength2:PROC
EXTRN	@__security_check_cookie@4:PROC
EXTRN	_boxpnt:BYTE
EXTRN	___security_cookie:DWORD
EXTRN	__fltused:DWORD
;	COMDAT __real@40000000
CONST	SEGMENT
__real@40000000 DD 040000000r			; 2
CONST	ENDS
;	COMDAT voltbl
voltbl	SEGMENT
_volmd	DW	010H
	DW	02dcH
voltbl	ENDS
;	COMDAT voltbl
voltbl	SEGMENT
_volmd	DW	0dH
	DW	01a9H
voltbl	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\common\pm_debug.c
;	COMDAT _PM_DrawRectangle
_TEXT	SEGMENT
_tl$ = 8						; size = 4
_bl$ = 12						; size = 4
_tr$ = 16						; size = 4
_br$ = 20						; size = 4
_pcolor$ = 24						; size = 4
_life$ = 28						; size = 4
_PM_DrawRectangle PROC					; COMDAT

; 55   : {

	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi

; 56   : 	PM_ParticleLine( tl, bl, pcolor, life, 0 );

	push	ecx
	xorps	xmm0, xmm0
	movss	DWORD PTR [esp], xmm0
	push	ecx
	movss	xmm0, DWORD PTR _life$[ebp]
	movss	DWORD PTR [esp], xmm0
	mov	eax, DWORD PTR _pcolor$[ebp]
	push	eax
	mov	ecx, DWORD PTR _bl$[ebp]
	push	ecx
	mov	edx, DWORD PTR _tl$[ebp]
	push	edx
	call	_PM_ParticleLine
	add	esp, 20					; 00000014H

; 57   : 	PM_ParticleLine( bl, br, pcolor, life, 0 );

	push	ecx
	xorps	xmm0, xmm0
	movss	DWORD PTR [esp], xmm0
	push	ecx
	movss	xmm0, DWORD PTR _life$[ebp]
	movss	DWORD PTR [esp], xmm0
	mov	eax, DWORD PTR _pcolor$[ebp]
	push	eax
	mov	ecx, DWORD PTR _br$[ebp]
	push	ecx
	mov	edx, DWORD PTR _bl$[ebp]
	push	edx
	call	_PM_ParticleLine
	add	esp, 20					; 00000014H

; 58   : 	PM_ParticleLine( br, tr, pcolor, life, 0 );

	push	ecx
	xorps	xmm0, xmm0
	movss	DWORD PTR [esp], xmm0
	push	ecx
	movss	xmm0, DWORD PTR _life$[ebp]
	movss	DWORD PTR [esp], xmm0
	mov	eax, DWORD PTR _pcolor$[ebp]
	push	eax
	mov	ecx, DWORD PTR _tr$[ebp]
	push	ecx
	mov	edx, DWORD PTR _br$[ebp]
	push	edx
	call	_PM_ParticleLine
	add	esp, 20					; 00000014H

; 59   : 	PM_ParticleLine( tr, tl, pcolor, life, 0 );

	push	ecx
	xorps	xmm0, xmm0
	movss	DWORD PTR [esp], xmm0
	push	ecx
	movss	xmm0, DWORD PTR _life$[ebp]
	movss	DWORD PTR [esp], xmm0
	mov	eax, DWORD PTR _pcolor$[ebp]
	push	eax
	mov	ecx, DWORD PTR _tl$[ebp]
	push	ecx
	mov	edx, DWORD PTR _tr$[ebp]
	push	edx
	call	_PM_ParticleLine
	add	esp, 20					; 00000014H

; 60   : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_PM_DrawRectangle ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\common\pm_debug.c
;	COMDAT _PM_DrawBBox
_TEXT	SEGMENT
tv151 = -188						; size = 4
tv130 = -188						; size = 4
tv87 = -188						; size = 4
tv76 = -188						; size = 4
_i$ = -120						; size = 4
_gap$ = -116						; size = 4
_tmp$ = -112						; size = 12
_p$ = -100						; size = 96
__$ArrayPad$ = -4					; size = 4
_mins$ = 8						; size = 4
_maxs$ = 12						; size = 4
_origin$ = 16						; size = 4
_pcolor$ = 20						; size = 4
_life$ = 24						; size = 4
_PM_DrawBBox PROC					; COMDAT

; 69   : {

	push	ebp
	mov	ebp, esp
	sub	esp, 188				; 000000bcH
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	mov	DWORD PTR __$ArrayPad$[ebp], eax
	push	ebx
	push	esi
	push	edi

; 70   : 	vec3_t	p[8], tmp;
; 71   : 	float	gap = BOX_GAP;

	xorps	xmm0, xmm0
	movss	DWORD PTR _gap$[ebp], xmm0

; 72   : 	int	i;
; 73   : 
; 74   : 	for( i = 0; i < 8; i++ )

	mov	DWORD PTR _i$[ebp], 0
	jmp	SHORT $LN4@PM_DrawBBo
$LN2@PM_DrawBBo:
	mov	eax, DWORD PTR _i$[ebp]
	add	eax, 1
	mov	DWORD PTR _i$[ebp], eax
$LN4@PM_DrawBBo:
	cmp	DWORD PTR _i$[ebp], 8
	jge	$LN3@PM_DrawBBo

; 75   : 	{
; 76   : 		tmp[0] = (i & 1) ? mins[0] - gap : maxs[0] + gap;

	mov	eax, DWORD PTR _i$[ebp]
	and	eax, 1
	je	SHORT $LN9@PM_DrawBBo
	mov	ecx, 4
	imul	edx, ecx, 0
	mov	eax, DWORD PTR _mins$[ebp]
	movss	xmm0, DWORD PTR [eax+edx]
	subss	xmm0, DWORD PTR _gap$[ebp]
	movss	DWORD PTR tv76[ebp], xmm0
	jmp	SHORT $LN10@PM_DrawBBo
$LN9@PM_DrawBBo:
	mov	ecx, 4
	imul	edx, ecx, 0
	mov	eax, DWORD PTR _maxs$[ebp]
	movss	xmm0, DWORD PTR [eax+edx]
	addss	xmm0, DWORD PTR _gap$[ebp]
	movss	DWORD PTR tv76[ebp], xmm0
$LN10@PM_DrawBBo:
	mov	ecx, 4
	imul	edx, ecx, 0
	movss	xmm0, DWORD PTR tv76[ebp]
	movss	DWORD PTR _tmp$[ebp+edx], xmm0

; 77   : 		tmp[1] = (i & 2) ? mins[1] - gap : maxs[1] + gap ;

	mov	eax, DWORD PTR _i$[ebp]
	and	eax, 2
	je	SHORT $LN11@PM_DrawBBo
	mov	ecx, 4
	shl	ecx, 0
	mov	edx, DWORD PTR _mins$[ebp]
	movss	xmm0, DWORD PTR [edx+ecx]
	subss	xmm0, DWORD PTR _gap$[ebp]
	movss	DWORD PTR tv87[ebp], xmm0
	jmp	SHORT $LN12@PM_DrawBBo
$LN11@PM_DrawBBo:
	mov	eax, 4
	shl	eax, 0
	mov	ecx, DWORD PTR _maxs$[ebp]
	movss	xmm0, DWORD PTR [ecx+eax]
	addss	xmm0, DWORD PTR _gap$[ebp]
	movss	DWORD PTR tv87[ebp], xmm0
$LN12@PM_DrawBBo:
	mov	edx, 4
	shl	edx, 0
	movss	xmm0, DWORD PTR tv87[ebp]
	movss	DWORD PTR _tmp$[ebp+edx], xmm0

; 78   : 		tmp[2] = (i & 4) ? mins[2] - gap : maxs[2] + gap ;

	mov	eax, DWORD PTR _i$[ebp]
	and	eax, 4
	je	SHORT $LN13@PM_DrawBBo
	mov	ecx, 4
	shl	ecx, 1
	mov	edx, DWORD PTR _mins$[ebp]
	movss	xmm0, DWORD PTR [edx+ecx]
	subss	xmm0, DWORD PTR _gap$[ebp]
	movss	DWORD PTR tv130[ebp], xmm0
	jmp	SHORT $LN14@PM_DrawBBo
$LN13@PM_DrawBBo:
	mov	eax, 4
	shl	eax, 1
	mov	ecx, DWORD PTR _maxs$[ebp]
	movss	xmm0, DWORD PTR [ecx+eax]
	addss	xmm0, DWORD PTR _gap$[ebp]
	movss	DWORD PTR tv130[ebp], xmm0
$LN14@PM_DrawBBo:
	mov	edx, 4
	shl	edx, 1
	movss	xmm0, DWORD PTR tv130[ebp]
	movss	DWORD PTR _tmp$[ebp+edx], xmm0

; 79   : 
; 80   : 		VectorAdd( tmp, origin, tmp );

	mov	eax, 4
	imul	ecx, eax, 0
	mov	edx, 4
	imul	eax, edx, 0
	mov	edx, DWORD PTR _origin$[ebp]
	movss	xmm0, DWORD PTR _tmp$[ebp+ecx]
	addss	xmm0, DWORD PTR [edx+eax]
	mov	eax, 4
	imul	ecx, eax, 0
	movss	DWORD PTR _tmp$[ebp+ecx], xmm0
	mov	edx, 4
	shl	edx, 0
	mov	eax, 4
	shl	eax, 0
	mov	ecx, DWORD PTR _origin$[ebp]
	movss	xmm0, DWORD PTR _tmp$[ebp+edx]
	addss	xmm0, DWORD PTR [ecx+eax]
	mov	edx, 4
	shl	edx, 0
	movss	DWORD PTR _tmp$[ebp+edx], xmm0
	mov	eax, 4
	shl	eax, 1
	mov	ecx, 4
	shl	ecx, 1
	mov	edx, DWORD PTR _origin$[ebp]
	movss	xmm0, DWORD PTR _tmp$[ebp+eax]
	addss	xmm0, DWORD PTR [edx+ecx]
	movss	DWORD PTR tv151[ebp], xmm0
	mov	eax, 4
	shl	eax, 1
	movss	xmm0, DWORD PTR tv151[ebp]
	movss	DWORD PTR _tmp$[ebp+eax], xmm0

; 81   : 		VectorCopy( tmp, p[i] );

	mov	eax, 4
	imul	ecx, eax, 0
	imul	edx, DWORD PTR _i$[ebp], 12
	lea	eax, DWORD PTR _p$[ebp+edx]
	mov	edx, 4
	imul	edx, edx, 0
	mov	ecx, DWORD PTR _tmp$[ebp+ecx]
	mov	DWORD PTR [eax+edx], ecx
	mov	edx, 4
	shl	edx, 0
	imul	eax, DWORD PTR _i$[ebp], 12
	lea	ecx, DWORD PTR _p$[ebp+eax]
	mov	eax, 4
	shl	eax, 0
	mov	edx, DWORD PTR _tmp$[ebp+edx]
	mov	DWORD PTR [ecx+eax], edx
	mov	eax, 4
	shl	eax, 1
	imul	ecx, DWORD PTR _i$[ebp], 12
	lea	edx, DWORD PTR _p$[ebp+ecx]
	mov	ecx, 4
	shl	ecx, 1
	mov	eax, DWORD PTR _tmp$[ebp+eax]
	mov	DWORD PTR [edx+ecx], eax

; 82   : 	}

	jmp	$LN2@PM_DrawBBo
$LN3@PM_DrawBBo:

; 83   : 
; 84   : 	for( i = 0; i < 6; i++ )

	mov	DWORD PTR _i$[ebp], 0
	jmp	SHORT $LN7@PM_DrawBBo
$LN5@PM_DrawBBo:
	mov	eax, DWORD PTR _i$[ebp]
	add	eax, 1
	mov	DWORD PTR _i$[ebp], eax
$LN7@PM_DrawBBo:
	cmp	DWORD PTR _i$[ebp], 6
	jge	$LN6@PM_DrawBBo

; 85   : 	{
; 86   : 		PM_DrawRectangle( p[boxpnt[i][1]], p[boxpnt[i][0]], p[boxpnt[i][2]], p[boxpnt[i][3]], pcolor, life );

	push	ecx
	movss	xmm0, DWORD PTR _life$[ebp]
	movss	DWORD PTR [esp], xmm0
	mov	eax, DWORD PTR _pcolor$[ebp]
	push	eax
	mov	ecx, DWORD PTR _i$[ebp]
	shl	ecx, 4
	mov	edx, 4
	imul	eax, edx, 3
	imul	ecx, DWORD PTR _boxpnt[ecx+eax], 12
	lea	edx, DWORD PTR _p$[ebp+ecx]
	push	edx
	mov	eax, DWORD PTR _i$[ebp]
	shl	eax, 4
	mov	ecx, 4
	shl	ecx, 1
	imul	edx, DWORD PTR _boxpnt[eax+ecx], 12
	lea	eax, DWORD PTR _p$[ebp+edx]
	push	eax
	mov	ecx, DWORD PTR _i$[ebp]
	shl	ecx, 4
	mov	edx, 4
	imul	eax, edx, 0
	imul	ecx, DWORD PTR _boxpnt[ecx+eax], 12
	lea	edx, DWORD PTR _p$[ebp+ecx]
	push	edx
	mov	eax, DWORD PTR _i$[ebp]
	shl	eax, 4
	mov	ecx, 4
	shl	ecx, 0
	imul	edx, DWORD PTR _boxpnt[eax+ecx], 12
	lea	eax, DWORD PTR _p$[ebp+edx]
	push	eax
	call	_PM_DrawRectangle
	add	esp, 24					; 00000018H

; 87   : 	}

	jmp	$LN5@PM_DrawBBo
$LN6@PM_DrawBBo:

; 88   : }

	pop	edi
	pop	esi
	pop	ebx
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	0
_PM_DrawBBox ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\common\pm_debug.c
;	COMDAT _PM_ParticleLine
_TEXT	SEGMENT
tv144 = -104						; size = 4
tv84 = -104						; size = 4
_pos$ = -36						; size = 12
_diff$ = -24						; size = 12
_curdist$ = -12						; size = 4
_len$ = -8						; size = 4
__$ArrayPad$ = -4					; size = 4
_start$ = 8						; size = 4
_end$ = 12						; size = 4
_pcolor$ = 16						; size = 4
_life$ = 20						; size = 4
_zvel$ = 24						; size = 4
_PM_ParticleLine PROC					; COMDAT

; 31   : {

	push	ebp
	mov	ebp, esp
	sub	esp, 104				; 00000068H
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	mov	DWORD PTR __$ArrayPad$[ebp], eax
	push	ebx
	push	esi
	push	edi

; 32   : 	float	len, curdist;
; 33   : 	vec3_t	diff, pos;
; 34   : 
; 35   : 	// determine distance
; 36   : 	VectorSubtract( end, start, diff );

	mov	eax, 4
	imul	ecx, eax, 0
	mov	edx, 4
	imul	eax, edx, 0
	mov	edx, DWORD PTR _end$[ebp]
	mov	esi, DWORD PTR _start$[ebp]
	movss	xmm0, DWORD PTR [edx+ecx]
	subss	xmm0, DWORD PTR [esi+eax]
	mov	eax, 4
	imul	ecx, eax, 0
	movss	DWORD PTR _diff$[ebp+ecx], xmm0
	mov	edx, 4
	shl	edx, 0
	mov	eax, 4
	shl	eax, 0
	mov	ecx, DWORD PTR _end$[ebp]
	mov	esi, DWORD PTR _start$[ebp]
	movss	xmm0, DWORD PTR [ecx+edx]
	subss	xmm0, DWORD PTR [esi+eax]
	mov	edx, 4
	shl	edx, 0
	movss	DWORD PTR _diff$[ebp+edx], xmm0
	mov	eax, 4
	shl	eax, 1
	mov	ecx, 4
	shl	ecx, 1
	mov	edx, DWORD PTR _end$[ebp]
	mov	esi, DWORD PTR _start$[ebp]
	movss	xmm0, DWORD PTR [edx+eax]
	subss	xmm0, DWORD PTR [esi+ecx]
	movss	DWORD PTR tv84[ebp], xmm0
	mov	eax, 4
	shl	eax, 1
	movss	xmm0, DWORD PTR tv84[ebp]
	movss	DWORD PTR _diff$[ebp+eax], xmm0

; 37   : 	len = VectorNormalizeLength( diff );

	lea	eax, DWORD PTR _diff$[ebp]
	push	eax
	lea	ecx, DWORD PTR _diff$[ebp]
	push	ecx
	call	_VectorNormalizeLength2
	add	esp, 8
	fstp	DWORD PTR _len$[ebp]

; 38   : 	curdist = 0;

	xorps	xmm0, xmm0
	movss	DWORD PTR _curdist$[ebp], xmm0
$LN2@PM_Particl:

; 39   : 
; 40   : 	while( curdist <= len )

	movss	xmm0, DWORD PTR _len$[ebp]
	comiss	xmm0, DWORD PTR _curdist$[ebp]
	jb	$LN3@PM_Particl

; 41   : 	{
; 42   : 		VectorMA( start, curdist, diff, pos );

	mov	eax, 4
	imul	ecx, eax, 0
	mov	edx, 4
	imul	eax, edx, 0
	movss	xmm0, DWORD PTR _curdist$[ebp]
	mulss	xmm0, DWORD PTR _diff$[ebp+eax]
	mov	edx, DWORD PTR _start$[ebp]
	addss	xmm0, DWORD PTR [edx+ecx]
	mov	eax, 4
	imul	ecx, eax, 0
	movss	DWORD PTR _pos$[ebp+ecx], xmm0
	mov	edx, 4
	shl	edx, 0
	mov	eax, 4
	shl	eax, 0
	movss	xmm0, DWORD PTR _curdist$[ebp]
	mulss	xmm0, DWORD PTR _diff$[ebp+eax]
	mov	ecx, DWORD PTR _start$[ebp]
	addss	xmm0, DWORD PTR [ecx+edx]
	mov	edx, 4
	shl	edx, 0
	movss	DWORD PTR _pos$[ebp+edx], xmm0
	mov	eax, 4
	shl	eax, 1
	mov	ecx, 4
	shl	ecx, 1
	movss	xmm0, DWORD PTR _curdist$[ebp]
	mulss	xmm0, DWORD PTR _diff$[ebp+ecx]
	mov	edx, DWORD PTR _start$[ebp]
	movss	xmm1, DWORD PTR [edx+eax]
	addss	xmm1, xmm0
	movss	DWORD PTR tv144[ebp], xmm1
	mov	eax, 4
	shl	eax, 1
	movss	xmm0, DWORD PTR tv144[ebp]
	movss	DWORD PTR _pos$[ebp+eax], xmm0

; 43   : 		CL_Particle( pos, pcolor, life, 0, zvel );

	cvttss2si eax, DWORD PTR _zvel$[ebp]
	push	eax
	push	0
	push	ecx
	movss	xmm0, DWORD PTR _life$[ebp]
	movss	DWORD PTR [esp], xmm0
	mov	ecx, DWORD PTR _pcolor$[ebp]
	push	ecx
	lea	edx, DWORD PTR _pos$[ebp]
	push	edx
	call	_CL_Particle
	add	esp, 20					; 00000014H

; 44   : 		curdist += 2.0f;

	movss	xmm0, DWORD PTR _curdist$[ebp]
	addss	xmm0, DWORD PTR __real@40000000
	movss	DWORD PTR _curdist$[ebp], xmm0

; 45   : 	}

	jmp	$LN2@PM_Particl
$LN3@PM_Particl:

; 46   : }

	pop	edi
	pop	esi
	pop	ebx
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	0
_PM_ParticleLine ENDP
_TEXT	ENDS
END
