; Listing generated by Microsoft (R) Optimizing Compiler Version 19.37.32705.0 

	TITLE	D:\DevDragon\XashFE\dev\src\temp\engine\!debug\s_mouth.obj
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRTD
INCLUDELIB OLDNAMES

PUBLIC	_SND_InitMouth
PUBLIC	_SND_MoveMouth8
PUBLIC	_SND_MoveMouth16
PUBLIC	_SND_CloseMouth
EXTRN	_abs:PROC
EXTRN	_CL_GetEntityByIndex:PROC
EXTRN	_S_GetOutputData:PROC
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_mouth.c
;	COMDAT _SND_CloseMouth
_TEXT	SEGMENT
_clientEntity$1 = -4					; size = 4
_ch$ = 8						; size = 4
_SND_CloseMouth PROC					; COMDAT

; 42   : {

	push	ebp
	mov	ebp, esp
	sub	esp, 68					; 00000044H
	push	ebx
	push	esi
	push	edi

; 43   : 	if( ch->entchannel == CHAN_VOICE || ch->entchannel == CHAN_STREAM )

	mov	eax, DWORD PTR _ch$[ebp]
	cmp	DWORD PTR [eax+32], 2
	je	SHORT $LN3@SND_CloseM
	mov	eax, DWORD PTR _ch$[ebp]
	cmp	DWORD PTR [eax+32], 6
	jne	SHORT $LN1@SND_CloseM
$LN3@SND_CloseM:

; 44   : 	{
; 45   : 		cl_entity_t	*clientEntity;
; 46   : 
; 47   : 		clientEntity = CL_GetEntityByIndex( ch->entnum );

	mov	eax, DWORD PTR _ch$[ebp]
	mov	ecx, DWORD PTR [eax+28]
	push	ecx
	call	_CL_GetEntityByIndex
	add	esp, 4
	mov	DWORD PTR _clientEntity$1[ebp], eax

; 48   : 
; 49   : 		if( clientEntity )

	cmp	DWORD PTR _clientEntity$1[ebp], 0
	je	SHORT $LN1@SND_CloseM

; 50   : 		{
; 51   : 			// shut mouth
; 52   : 			clientEntity->mouth.mouthopen = 0;

	mov	eax, DWORD PTR _clientEntity$1[ebp]
	mov	BYTE PTR [eax+3160], 0
$LN1@SND_CloseM:

; 53   : 		}
; 54   : 	}
; 55   : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_SND_CloseMouth ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_mouth.c
;	COMDAT _SND_MoveMouth16
_TEXT	SEGMENT
tv128 = -104						; size = 4
tv95 = -100						; size = 4
_i$ = -32						; size = 4
_pos$ = -28						; size = 4
_scount$ = -24						; size = 4
_data$ = -20						; size = 4
_savg$ = -16						; size = 4
_pMouth$ = -12						; size = 4
_pdata$ = -8						; size = 4
_clientEntity$ = -4					; size = 4
_ch$ = 8						; size = 4
_pSource$ = 12						; size = 4
_count$ = 16						; size = 4
_SND_MoveMouth16 PROC					; COMDAT

; 106  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 104				; 00000068H
	push	ebx
	push	esi
	push	edi

; 107  : 	cl_entity_t	*clientEntity;
; 108  : 	short		*pdata = NULL;

	mov	DWORD PTR _pdata$[ebp], 0

; 109  : 	mouth_t		*pMouth = NULL;

	mov	DWORD PTR _pMouth$[ebp], 0

; 110  : 	int		savg, data;
; 111  : 	int		scount, pos = 0;

	mov	DWORD PTR _pos$[ebp], 0

; 112  : 	uint 		i;
; 113  : 
; 114  : 	clientEntity = CL_GetEntityByIndex( ch->entnum );

	mov	eax, DWORD PTR _ch$[ebp]
	mov	ecx, DWORD PTR [eax+28]
	push	ecx
	call	_CL_GetEntityByIndex
	add	esp, 4
	mov	DWORD PTR _clientEntity$[ebp], eax

; 115  : 	if( !clientEntity ) return;

	cmp	DWORD PTR _clientEntity$[ebp], 0
	jne	SHORT $LN4@SND_MoveMo
	jmp	$LN9@SND_MoveMo
$LN4@SND_MoveMo:

; 116  : 
; 117  : 	pMouth = &clientEntity->mouth;

	mov	eax, DWORD PTR _clientEntity$[ebp]
	add	eax, 3160				; 00000c58H
	mov	DWORD PTR _pMouth$[ebp], eax

; 118  : 
; 119  : 	if( ch->isSentence )

	mov	eax, DWORD PTR _ch$[ebp]
	cmp	DWORD PTR [eax+56], 0
	je	SHORT $LN5@SND_MoveMo

; 120  : 	{
; 121  : 		if( ch->currentWord )

	mov	eax, DWORD PTR _ch$[ebp]
	cmp	DWORD PTR [eax+168], 0
	je	SHORT $LN7@SND_MoveMo

; 122  : 			pos = ch->currentWord->sample;

	mov	eax, DWORD PTR _ch$[ebp]
	mov	ecx, DWORD PTR [eax+168]
	cvttsd2si edx, QWORD PTR [ecx]
	mov	DWORD PTR _pos$[ebp], edx
$LN7@SND_MoveMo:

; 123  : 	}

	jmp	SHORT $LN6@SND_MoveMo
$LN5@SND_MoveMo:

; 124  : 	else pos = ch->pMixer.sample;

	mov	eax, DWORD PTR _ch$[ebp]
	cvttsd2si ecx, QWORD PTR [eax+80]
	mov	DWORD PTR _pos$[ebp], ecx
$LN6@SND_MoveMo:

; 125  : 
; 126  : 	count = S_GetOutputData( pSource, &pdata, pos, count, ch->use_loop );

	mov	eax, DWORD PTR _ch$[ebp]
	mov	ecx, DWORD PTR [eax+68]
	push	ecx
	mov	edx, DWORD PTR _count$[ebp]
	push	edx
	mov	eax, DWORD PTR _pos$[ebp]
	push	eax
	lea	ecx, DWORD PTR _pdata$[ebp]
	push	ecx
	mov	edx, DWORD PTR _pSource$[ebp]
	push	edx
	call	_S_GetOutputData
	add	esp, 20					; 00000014H
	mov	DWORD PTR _count$[ebp], eax

; 127  : 	if( pdata == NULL ) return;

	cmp	DWORD PTR _pdata$[ebp], 0
	jne	SHORT $LN8@SND_MoveMo
	jmp	$LN9@SND_MoveMo
$LN8@SND_MoveMo:

; 128  : 	
; 129  : 	i = 0;

	mov	DWORD PTR _i$[ebp], 0

; 130  : 	scount = pMouth->sndcount;

	mov	eax, DWORD PTR _pMouth$[ebp]
	movzx	ecx, BYTE PTR [eax+1]
	mov	DWORD PTR _scount$[ebp], ecx

; 131  : 	savg = 0;

	mov	DWORD PTR _savg$[ebp], 0
$LN2@SND_MoveMo:

; 132  : 
; 133  : 	while( i < count && scount < CAVGSAMPLES )

	mov	eax, DWORD PTR _i$[ebp]
	cmp	eax, DWORD PTR _count$[ebp]
	jae	SHORT $LN3@SND_MoveMo
	cmp	DWORD PTR _scount$[ebp], 10		; 0000000aH
	jge	SHORT $LN3@SND_MoveMo

; 134  : 	{
; 135  : 		data = pdata[i];

	mov	eax, DWORD PTR _i$[ebp]
	mov	ecx, DWORD PTR _pdata$[ebp]
	movsx	edx, WORD PTR [ecx+eax*2]
	mov	DWORD PTR _data$[ebp], edx

; 136  : 		data = (bound( -32767, data, 0x7ffe ) >> 8);

	cmp	DWORD PTR _data$[ebp], -32767		; ffff8001H
	jl	SHORT $LN13@SND_MoveMo
	cmp	DWORD PTR _data$[ebp], 32766		; 00007ffeH
	jge	SHORT $LN11@SND_MoveMo
	mov	eax, DWORD PTR _data$[ebp]
	mov	DWORD PTR tv95[ebp], eax
	jmp	SHORT $LN12@SND_MoveMo
$LN11@SND_MoveMo:
	mov	DWORD PTR tv95[ebp], 32766		; 00007ffeH
$LN12@SND_MoveMo:
	mov	ecx, DWORD PTR tv95[ebp]
	mov	DWORD PTR tv128[ebp], ecx
	jmp	SHORT $LN14@SND_MoveMo
$LN13@SND_MoveMo:
	mov	DWORD PTR tv128[ebp], -32767		; ffff8001H
$LN14@SND_MoveMo:
	mov	edx, DWORD PTR tv128[ebp]
	sar	edx, 8
	mov	DWORD PTR _data$[ebp], edx

; 137  : 		savg += abs( data );	

	mov	eax, DWORD PTR _data$[ebp]
	push	eax
	call	_abs
	add	esp, 4
	add	eax, DWORD PTR _savg$[ebp]
	mov	DWORD PTR _savg$[ebp], eax

; 138  : 
; 139  : 		i += 80 + ((byte)data & 0x1F);

	movzx	eax, BYTE PTR _data$[ebp]
	and	eax, 31					; 0000001fH
	mov	ecx, DWORD PTR _i$[ebp]
	lea	edx, DWORD PTR [ecx+eax+80]
	mov	DWORD PTR _i$[ebp], edx

; 140  : 		scount++;

	mov	eax, DWORD PTR _scount$[ebp]
	add	eax, 1
	mov	DWORD PTR _scount$[ebp], eax

; 141  : 	}

	jmp	$LN2@SND_MoveMo
$LN3@SND_MoveMo:

; 142  : 
; 143  : 	pMouth->sndavg += savg;

	mov	eax, DWORD PTR _pMouth$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	add	ecx, DWORD PTR _savg$[ebp]
	mov	edx, DWORD PTR _pMouth$[ebp]
	mov	DWORD PTR [edx+4], ecx

; 144  : 	pMouth->sndcount = (byte)scount;

	mov	eax, DWORD PTR _pMouth$[ebp]
	mov	cl, BYTE PTR _scount$[ebp]
	mov	BYTE PTR [eax+1], cl

; 145  : 
; 146  : 	if( pMouth->sndcount >= CAVGSAMPLES ) 

	mov	eax, DWORD PTR _pMouth$[ebp]
	movzx	ecx, BYTE PTR [eax+1]
	cmp	ecx, 10					; 0000000aH
	jl	SHORT $LN9@SND_MoveMo

; 147  : 	{
; 148  : 		pMouth->mouthopen = pMouth->sndavg / CAVGSAMPLES;

	mov	eax, DWORD PTR _pMouth$[ebp]
	mov	eax, DWORD PTR [eax+4]
	cdq
	mov	ecx, 10					; 0000000aH
	idiv	ecx
	mov	edx, DWORD PTR _pMouth$[ebp]
	mov	BYTE PTR [edx], al

; 149  : 		pMouth->sndavg = 0;

	mov	eax, DWORD PTR _pMouth$[ebp]
	mov	DWORD PTR [eax+4], 0

; 150  : 		pMouth->sndcount = 0;

	mov	eax, DWORD PTR _pMouth$[ebp]
	mov	BYTE PTR [eax+1], 0
$LN9@SND_MoveMo:

; 151  : 	}
; 152  : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_SND_MoveMouth16 ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_mouth.c
;	COMDAT _SND_MoveMouth8
_TEXT	SEGMENT
_i$ = -32						; size = 4
_data$ = -28						; size = 4
_savg$ = -24						; size = 4
_pos$ = -20						; size = 4
_scount$ = -16						; size = 4
_pMouth$ = -12						; size = 4
_pdata$ = -8						; size = 4
_clientEntity$ = -4					; size = 4
_ch$ = 8						; size = 4
_pSource$ = 12						; size = 4
_count$ = 16						; size = 4
_SND_MoveMouth8 PROC					; COMDAT

; 58   : {

	push	ebp
	mov	ebp, esp
	sub	esp, 96					; 00000060H
	push	ebx
	push	esi
	push	edi

; 59   : 	cl_entity_t	*clientEntity;
; 60   : 	char		*pdata = NULL;

	mov	DWORD PTR _pdata$[ebp], 0

; 61   : 	mouth_t		*pMouth = NULL;

	mov	DWORD PTR _pMouth$[ebp], 0

; 62   : 	int		scount, pos = 0;

	mov	DWORD PTR _pos$[ebp], 0

; 63   : 	int		savg, data;
; 64   : 	uint 		i;
; 65   : 
; 66   : 	clientEntity = CL_GetEntityByIndex( ch->entnum );

	mov	eax, DWORD PTR _ch$[ebp]
	mov	ecx, DWORD PTR [eax+28]
	push	ecx
	call	_CL_GetEntityByIndex
	add	esp, 4
	mov	DWORD PTR _clientEntity$[ebp], eax

; 67   : 	if( !clientEntity ) return;

	cmp	DWORD PTR _clientEntity$[ebp], 0
	jne	SHORT $LN4@SND_MoveMo
	jmp	$LN9@SND_MoveMo
$LN4@SND_MoveMo:

; 68   : 
; 69   : 	pMouth = &clientEntity->mouth;

	mov	eax, DWORD PTR _clientEntity$[ebp]
	add	eax, 3160				; 00000c58H
	mov	DWORD PTR _pMouth$[ebp], eax

; 70   : 
; 71   : 	if( ch->isSentence )

	mov	eax, DWORD PTR _ch$[ebp]
	cmp	DWORD PTR [eax+56], 0
	je	SHORT $LN5@SND_MoveMo

; 72   : 	{
; 73   : 		if( ch->currentWord )

	mov	eax, DWORD PTR _ch$[ebp]
	cmp	DWORD PTR [eax+168], 0
	je	SHORT $LN7@SND_MoveMo

; 74   : 			pos = ch->currentWord->sample;

	mov	eax, DWORD PTR _ch$[ebp]
	mov	ecx, DWORD PTR [eax+168]
	cvttsd2si edx, QWORD PTR [ecx]
	mov	DWORD PTR _pos$[ebp], edx
$LN7@SND_MoveMo:

; 75   : 	}

	jmp	SHORT $LN6@SND_MoveMo
$LN5@SND_MoveMo:

; 76   : 	else pos = ch->pMixer.sample;

	mov	eax, DWORD PTR _ch$[ebp]
	cvttsd2si ecx, QWORD PTR [eax+80]
	mov	DWORD PTR _pos$[ebp], ecx
$LN6@SND_MoveMo:

; 77   : 
; 78   : 	count = S_GetOutputData( pSource, &pdata, pos, count, ch->use_loop );

	mov	eax, DWORD PTR _ch$[ebp]
	mov	ecx, DWORD PTR [eax+68]
	push	ecx
	mov	edx, DWORD PTR _count$[ebp]
	push	edx
	mov	eax, DWORD PTR _pos$[ebp]
	push	eax
	lea	ecx, DWORD PTR _pdata$[ebp]
	push	ecx
	mov	edx, DWORD PTR _pSource$[ebp]
	push	edx
	call	_S_GetOutputData
	add	esp, 20					; 00000014H
	mov	DWORD PTR _count$[ebp], eax

; 79   : 	if( pdata == NULL ) return;

	cmp	DWORD PTR _pdata$[ebp], 0
	jne	SHORT $LN8@SND_MoveMo
	jmp	$LN9@SND_MoveMo
$LN8@SND_MoveMo:

; 80   : 	
; 81   : 	i = 0;

	mov	DWORD PTR _i$[ebp], 0

; 82   : 	scount = pMouth->sndcount;

	mov	eax, DWORD PTR _pMouth$[ebp]
	movzx	ecx, BYTE PTR [eax+1]
	mov	DWORD PTR _scount$[ebp], ecx

; 83   : 	savg = 0;

	mov	DWORD PTR _savg$[ebp], 0
$LN2@SND_MoveMo:

; 84   : 
; 85   : 	while( i < count && scount < CAVGSAMPLES )

	mov	eax, DWORD PTR _i$[ebp]
	cmp	eax, DWORD PTR _count$[ebp]
	jae	SHORT $LN3@SND_MoveMo
	cmp	DWORD PTR _scount$[ebp], 10		; 0000000aH
	jge	SHORT $LN3@SND_MoveMo

; 86   : 	{
; 87   : 		data = pdata[i];

	mov	eax, DWORD PTR _pdata$[ebp]
	add	eax, DWORD PTR _i$[ebp]
	movsx	ecx, BYTE PTR [eax]
	mov	DWORD PTR _data$[ebp], ecx

; 88   : 		savg += abs( data );	

	mov	eax, DWORD PTR _data$[ebp]
	push	eax
	call	_abs
	add	esp, 4
	add	eax, DWORD PTR _savg$[ebp]
	mov	DWORD PTR _savg$[ebp], eax

; 89   : 
; 90   : 		i += 80 + ((byte)data & 0x1F);

	movzx	eax, BYTE PTR _data$[ebp]
	and	eax, 31					; 0000001fH
	mov	ecx, DWORD PTR _i$[ebp]
	lea	edx, DWORD PTR [ecx+eax+80]
	mov	DWORD PTR _i$[ebp], edx

; 91   : 		scount++;

	mov	eax, DWORD PTR _scount$[ebp]
	add	eax, 1
	mov	DWORD PTR _scount$[ebp], eax

; 92   : 	}

	jmp	SHORT $LN2@SND_MoveMo
$LN3@SND_MoveMo:

; 93   : 
; 94   : 	pMouth->sndavg += savg;

	mov	eax, DWORD PTR _pMouth$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	add	ecx, DWORD PTR _savg$[ebp]
	mov	edx, DWORD PTR _pMouth$[ebp]
	mov	DWORD PTR [edx+4], ecx

; 95   : 	pMouth->sndcount = (byte)scount;

	mov	eax, DWORD PTR _pMouth$[ebp]
	mov	cl, BYTE PTR _scount$[ebp]
	mov	BYTE PTR [eax+1], cl

; 96   : 
; 97   : 	if( pMouth->sndcount >= CAVGSAMPLES ) 

	mov	eax, DWORD PTR _pMouth$[ebp]
	movzx	ecx, BYTE PTR [eax+1]
	cmp	ecx, 10					; 0000000aH
	jl	SHORT $LN9@SND_MoveMo

; 98   : 	{
; 99   : 		pMouth->mouthopen = pMouth->sndavg / CAVGSAMPLES;

	mov	eax, DWORD PTR _pMouth$[ebp]
	mov	eax, DWORD PTR [eax+4]
	cdq
	mov	ecx, 10					; 0000000aH
	idiv	ecx
	mov	edx, DWORD PTR _pMouth$[ebp]
	mov	BYTE PTR [edx], al

; 100  : 		pMouth->sndavg = 0;

	mov	eax, DWORD PTR _pMouth$[ebp]
	mov	DWORD PTR [eax+4], 0

; 101  : 		pMouth->sndcount = 0;

	mov	eax, DWORD PTR _pMouth$[ebp]
	mov	BYTE PTR [eax+1], 0
$LN9@SND_MoveMo:

; 102  : 	}
; 103  : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_SND_MoveMouth8 ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_mouth.c
;	COMDAT _SND_InitMouth
_TEXT	SEGMENT
_clientEntity$1 = -4					; size = 4
_entnum$ = 8						; size = 4
_entchannel$ = 12					; size = 4
_SND_InitMouth PROC					; COMDAT

; 24   : {

	push	ebp
	mov	ebp, esp
	sub	esp, 68					; 00000044H
	push	ebx
	push	esi
	push	edi

; 25   : 	if(( entchannel == CHAN_VOICE || entchannel == CHAN_STREAM ) && entnum > 0 )

	cmp	DWORD PTR _entchannel$[ebp], 2
	je	SHORT $LN3@SND_InitMo
	cmp	DWORD PTR _entchannel$[ebp], 6
	jne	SHORT $LN1@SND_InitMo
$LN3@SND_InitMo:
	cmp	DWORD PTR _entnum$[ebp], 0
	jle	SHORT $LN1@SND_InitMo

; 26   : 	{
; 27   : 		cl_entity_t	*clientEntity;
; 28   : 
; 29   : 		// init mouth movement vars
; 30   : 		clientEntity = CL_GetEntityByIndex( entnum );

	mov	eax, DWORD PTR _entnum$[ebp]
	push	eax
	call	_CL_GetEntityByIndex
	add	esp, 4
	mov	DWORD PTR _clientEntity$1[ebp], eax

; 31   : 
; 32   : 		if( clientEntity )

	cmp	DWORD PTR _clientEntity$1[ebp], 0
	je	SHORT $LN1@SND_InitMo

; 33   : 		{
; 34   : 			clientEntity->mouth.mouthopen = 0;

	mov	eax, DWORD PTR _clientEntity$1[ebp]
	mov	BYTE PTR [eax+3160], 0

; 35   : 			clientEntity->mouth.sndcount = 0;

	mov	eax, DWORD PTR _clientEntity$1[ebp]
	mov	BYTE PTR [eax+3161], 0

; 36   : 			clientEntity->mouth.sndavg = 0;

	mov	eax, DWORD PTR _clientEntity$1[ebp]
	mov	DWORD PTR [eax+3164], 0
$LN1@SND_InitMo:

; 37   : 		}
; 38   : 	}
; 39   : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_SND_InitMouth ENDP
_TEXT	ENDS
END
