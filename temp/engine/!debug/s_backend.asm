; Listing generated by Microsoft (R) Optimizing Compiler Version 19.37.32705.0 

	TITLE	D:\DevDragon\XashFE\dev\src\temp\engine\!debug\s_backend.obj
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRTD
INCLUDELIB OLDNAMES

PUBLIC	??_C@_0BC@GKIGDBEH@DirectSoundCreate@		; `string'
PUBLIC	_dsound_dll
PUBLIC	??_C@_0L@ELNNJJJ@dsound?4dll@			; `string'
_BSS	SEGMENT
_pDirectSoundCreate DD 01H DUP (?)
_BSS	ENDS
;	COMDAT ??_C@_0L@ELNNJJJ@dsound?4dll@
CONST	SEGMENT
??_C@_0L@ELNNJJJ@dsound?4dll@ DB 'dsound.dll', 00H	; `string'
CONST	ENDS
;	COMDAT ??_C@_0BC@GKIGDBEH@DirectSoundCreate@
CONST	SEGMENT
??_C@_0BC@GKIGDBEH@DirectSoundCreate@ DB 'DirectSoundCreate', 00H ; `string'
CONST	ENDS
_DATA	SEGMENT
_dsound_funcs DD FLAT:??_C@_0BC@GKIGDBEH@DirectSoundCreate@
	DD	FLAT:_pDirectSoundCreate
	DD	00H
	DD	00H
_dsound_dll DD	FLAT:??_C@_0L@ELNNJJJ@dsound?4dll@
	DD	FLAT:_dsound_funcs
	DD	00H
	ORG $+4
_DATA	ENDS
PUBLIC	_S_Activate
PUBLIC	_SNDDMA_Init
PUBLIC	_SNDDMA_GetSoundtime
PUBLIC	_SNDDMA_Shutdown
PUBLIC	_SNDDMA_BeginPainting
PUBLIC	_SNDDMA_Submit
PUBLIC	_SNDDMA_LockSound
PUBLIC	_SNDDMA_UnlockSound
PUBLIC	_SNDDMA_InitDirect
PUBLIC	_SNDDMA_FreeSound
PUBLIC	_SNDDMA_GetDMAPos
PUBLIC	??_C@_0P@KDAEJHKH@buffer?5is?5lost@		; `string'
PUBLIC	??_C@_0N@EIBHAONH@invalid?5call@		; `string'
PUBLIC	??_C@_0O@PFPAIGFJ@invalid?5param@		; `string'
PUBLIC	??_C@_0BH@OMFNMBKG@invalid?5priority?5level@	; `string'
PUBLIC	??_C@_0O@BFJCFAAK@unknown?5error@		; `string'
PUBLIC	??_C@_0DM@NNEFNPN@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@ ; `string'
PUBLIC	??_C@_0DM@KCOMJOCG@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@ ; `string'
PUBLIC	??_C@_0DL@PAIBECJB@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@ ; `string'
PUBLIC	??_C@_0DE@OIMKEAKI@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@ ; `string'
PUBLIC	??_C@_0DK@CCJBMFBL@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@ ; `string'
PUBLIC	??_C@_0DB@HIJBJALE@?$FO1Error?3?$FO7?5DirectSound?3?5hardwar@ ; `string'
PUBLIC	??_C@_0CO@PINFFA@?$FO1Error?3?$FO7?5DirectSound?3?5driver?5@ ; `string'
PUBLIC	??_C@_0DM@NLDNIIAO@?$FO1Error?3?$FO7?5BeginPainting?3?5could@ ; `string'
PUBLIC	??_C@_0BO@NCFLDAJJ@?$FO1Error?3?$FO7?5BeginPainting?3?5?$CFs?6@ ; `string'
EXTRN	_memset:PROC
EXTRN	_Sys_LoadLibrary:PROC
EXTRN	_Sys_FreeLibrary:PROC
EXTRN	_Con_DPrintf:PROC
EXTRN	_S_Shutdown:PROC
EXTRN	_S_StopAllSounds:PROC
EXTRN	@__security_check_cookie@4:PROC
EXTRN	_paintedtime:DWORD
EXTRN	_dma:BYTE
EXTRN	___security_cookie:DWORD
_BSS	SEGMENT
_primary_format_set DD 01H DUP (?)
_snd_hwnd DD	01H DUP (?)
_locksize DD	01H DUP (?)
_lpData	DD	01H DUP (?)
_gSndBufSize DD	01H DUP (?)
_mmstarttime DB	0cH DUP (?)
_pDSBuf	DD	01H DUP (?)
_pDSPBuf DD	01H DUP (?)
_pDS	DD	01H DUP (?)
?buffers@?1??SNDDMA_GetSoundtime@@9@9 DD 01H DUP (?)	; `SNDDMA_GetSoundtime'::`2'::buffers
?oldsamplepos@?1??SNDDMA_GetSoundtime@@9@9 DD 01H DUP (?) ; `SNDDMA_GetSoundtime'::`2'::oldsamplepos
_BSS	ENDS
;	COMDAT ??_C@_0BO@NCFLDAJJ@?$FO1Error?3?$FO7?5BeginPainting?3?5?$CFs?6@
CONST	SEGMENT
??_C@_0BO@NCFLDAJJ@?$FO1Error?3?$FO7?5BeginPainting?3?5?$CFs?6@ DB '^1Err'
	DB	'or:^7 BeginPainting: %s', 0aH, 00H		; `string'
CONST	ENDS
;	COMDAT ??_C@_0DM@NLDNIIAO@?$FO1Error?3?$FO7?5BeginPainting?3?5could@
CONST	SEGMENT
??_C@_0DM@NLDNIIAO@?$FO1Error?3?$FO7?5BeginPainting?3?5could@ DB '^1Error'
	DB	':^7 BeginPainting: couldn''t get sound buffer status', 0aH, 00H ; `string'
CONST	ENDS
;	COMDAT ??_C@_0CO@PINFFA@?$FO1Error?3?$FO7?5DirectSound?3?5driver?5@
CONST	SEGMENT
??_C@_0CO@PINFFA@?$FO1Error?3?$FO7?5DirectSound?3?5driver?5@ DB '^1Error:'
	DB	'^7 DirectSound: driver not installed', 0aH, 00H ; `string'
CONST	ENDS
;	COMDAT ??_C@_0DB@HIJBJALE@?$FO1Error?3?$FO7?5DirectSound?3?5hardwar@
CONST	SEGMENT
??_C@_0DB@HIJBJALE@?$FO1Error?3?$FO7?5DirectSound?3?5hardwar@ DB '^1Error'
	DB	':^7 DirectSound: hardware already in use', 0aH, 00H ; `string'
CONST	ENDS
;	COMDAT ??_C@_0DK@CCJBMFBL@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@
CONST	SEGMENT
??_C@_0DK@CCJBMFBL@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@ DB '^1Erro'
	DB	'r:^7 DirectSound: failed to create circular buffer', 0aH, 00H ; `string'
CONST	ENDS
;	COMDAT ??_C@_0DE@OIMKEAKI@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@
CONST	SEGMENT
??_C@_0DE@OIMKEAKI@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@ DB '^1Erro'
	DB	'r:^7 DirectSound: failed to get capabilities', 0aH, 00H ; `string'
CONST	ENDS
;	COMDAT ??_C@_0DL@PAIBECJB@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@
CONST	SEGMENT
??_C@_0DL@PAIBECJB@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@ DB '^1Erro'
	DB	'r:^7 DirectSound: failed to create secondary buffer', 0aH, 00H ; `string'
CONST	ENDS
;	COMDAT ??_C@_0DM@KCOMJOCG@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@
CONST	SEGMENT
??_C@_0DM@KCOMJOCG@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@ DB '^1Erro'
	DB	'r:^7 DirectSound: failed to set primary sound format', 0aH, 00H ; `string'
CONST	ENDS
;	COMDAT ??_C@_0DM@NNEFNPN@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@
CONST	SEGMENT
??_C@_0DM@NNEFNPN@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@ DB '^1Error'
	DB	':^7 DirectSound: failed to set EXCLUSIVE coop level', 0aH, 00H ; `string'
CONST	ENDS
;	COMDAT ??_C@_0O@BFJCFAAK@unknown?5error@
CONST	SEGMENT
??_C@_0O@BFJCFAAK@unknown?5error@ DB 'unknown error', 00H ; `string'
CONST	ENDS
;	COMDAT ??_C@_0BH@OMFNMBKG@invalid?5priority?5level@
CONST	SEGMENT
??_C@_0BH@OMFNMBKG@invalid?5priority?5level@ DB 'invalid priority level', 00H ; `string'
CONST	ENDS
;	COMDAT ??_C@_0O@PFPAIGFJ@invalid?5param@
CONST	SEGMENT
??_C@_0O@PFPAIGFJ@invalid?5param@ DB 'invalid param', 00H ; `string'
CONST	ENDS
;	COMDAT ??_C@_0N@EIBHAONH@invalid?5call@
CONST	SEGMENT
??_C@_0N@EIBHAONH@invalid?5call@ DB 'invalid call', 00H	; `string'
CONST	ENDS
;	COMDAT ??_C@_0P@KDAEJHKH@buffer?5is?5lost@
CONST	SEGMENT
??_C@_0P@KDAEJHKH@buffer?5is?5lost@ DB 'buffer is lost', 00H ; `string'
CONST	ENDS
_DATA	SEGMENT
_snd_firsttime DD 01H
_DATA	ENDS
;	COMDAT voltbl
voltbl	SEGMENT
_volmd	DB	0dH
	DB	06aH
voltbl	ENDS
;	COMDAT voltbl
voltbl	SEGMENT
_volmd	DW	010H
	DW	02f4H
voltbl	ENDS
;	COMDAT voltbl
voltbl	SEGMENT
_volmd	DB	010H
	DB	0e3H
voltbl	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_backend.c
;	COMDAT _SNDDMA_GetDMAPos
_TEXT	SEGMENT
_dwWrite$ = -24						; size = 4
_mmtime$ = -20						; size = 12
_s$ = -8						; size = 4
__$ArrayPad$ = -4					; size = 4
_SNDDMA_GetDMAPos PROC					; COMDAT

; 330  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 88					; 00000058H
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	mov	DWORD PTR __$ArrayPad$[ebp], eax
	push	ebx
	push	esi
	push	edi

; 331  : 	int	s;
; 332  : 	MMTIME	mmtime;
; 333  : 	DWORD	dwWrite;
; 334  : 
; 335  : 	if( !dma.initialized )

	cmp	DWORD PTR _dma+12, 0
	jne	SHORT $LN2@SNDDMA_Get

; 336  : 		return 0;

	xor	eax, eax
	jmp	SHORT $LN1@SNDDMA_Get
$LN2@SNDDMA_Get:

; 337  : 	
; 338  : 	mmtime.wType = TIME_SAMPLES;

	mov	DWORD PTR _mmtime$[ebp], 2

; 339  : 	pDSBuf->lpVtbl->GetCurrentPosition( pDSBuf, &mmtime.u.sample, &dwWrite );

	lea	eax, DWORD PTR _dwWrite$[ebp]
	push	eax
	lea	ecx, DWORD PTR _mmtime$[ebp+4]
	push	ecx
	mov	edx, DWORD PTR _pDSBuf
	push	edx
	mov	eax, DWORD PTR _pDSBuf
	mov	ecx, DWORD PTR [eax]
	mov	edx, DWORD PTR [ecx+16]
	call	edx

; 340  : 	s = mmtime.u.sample - mmstarttime.u.sample;

	mov	eax, DWORD PTR _mmtime$[ebp+4]
	sub	eax, DWORD PTR _mmstarttime+4
	mov	DWORD PTR _s$[ebp], eax

; 341  : 
; 342  : 	s >>= SAMPLE_16BIT_SHIFT;

	mov	eax, DWORD PTR _s$[ebp]
	sar	eax, 1
	mov	DWORD PTR _s$[ebp], eax

; 343  : 	s &= (dma.samples - 1);

	mov	eax, DWORD PTR _dma
	sub	eax, 1
	and	eax, DWORD PTR _s$[ebp]
	mov	DWORD PTR _s$[ebp], eax

; 344  : 
; 345  : 	return s;

	mov	eax, DWORD PTR _s$[ebp]
$LN1@SNDDMA_Get:

; 346  : }

	pop	edi
	pop	esi
	pop	ebx
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	0
_SNDDMA_GetDMAPos ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_backend.c
;	COMDAT _DS_DestroyBuffers
_TEXT	SEGMENT
_DS_DestroyBuffers PROC					; COMDAT

; 191  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi

; 192  : 	if( pDS ) pDS->lpVtbl->SetCooperativeLevel( pDS, snd_hwnd, DSSCL_NORMAL );

	cmp	DWORD PTR _pDS, 0
	je	SHORT $LN2@DS_Destroy
	push	1
	mov	eax, DWORD PTR _snd_hwnd
	push	eax
	mov	ecx, DWORD PTR _pDS
	push	ecx
	mov	edx, DWORD PTR _pDS
	mov	eax, DWORD PTR [edx]
	mov	ecx, DWORD PTR [eax+24]
	call	ecx
$LN2@DS_Destroy:

; 193  : 
; 194  : 	if( pDSBuf )

	cmp	DWORD PTR _pDSBuf, 0
	je	SHORT $LN3@DS_Destroy

; 195  : 	{
; 196  : 		pDSBuf->lpVtbl->Stop( pDSBuf );

	mov	eax, DWORD PTR _pDSBuf
	push	eax
	mov	ecx, DWORD PTR _pDSBuf
	mov	edx, DWORD PTR [ecx]
	mov	eax, DWORD PTR [edx+72]
	call	eax

; 197  : 		pDSBuf->lpVtbl->Release( pDSBuf );

	mov	eax, DWORD PTR _pDSBuf
	push	eax
	mov	ecx, DWORD PTR _pDSBuf
	mov	edx, DWORD PTR [ecx]
	mov	eax, DWORD PTR [edx+8]
	call	eax
$LN3@DS_Destroy:

; 198  : 	}
; 199  : 
; 200  : 	// only release primary buffer if it's not also the mixing buffer we just released
; 201  : 	if( pDSPBuf && ( pDSBuf != pDSPBuf ))

	cmp	DWORD PTR _pDSPBuf, 0
	je	SHORT $LN4@DS_Destroy
	mov	eax, DWORD PTR _pDSBuf
	cmp	eax, DWORD PTR _pDSPBuf
	je	SHORT $LN4@DS_Destroy

; 202  : 		pDSPBuf->lpVtbl->Release( pDSPBuf );

	mov	eax, DWORD PTR _pDSPBuf
	push	eax
	mov	ecx, DWORD PTR _pDSPBuf
	mov	edx, DWORD PTR [ecx]
	mov	eax, DWORD PTR [edx+8]
	call	eax
$LN4@DS_Destroy:

; 203  : 
; 204  : 	dma.buffer = NULL;

	mov	DWORD PTR _dma+8, 0

; 205  : 	pDSPBuf = NULL;

	mov	DWORD PTR _pDSPBuf, 0

; 206  : 	pDSBuf = NULL;

	mov	DWORD PTR _pDSBuf, 0

; 207  : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_DS_DestroyBuffers ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_backend.c
;	COMDAT _DS_CreateBuffers
_TEXT	SEGMENT
_dsbuf$ = -100						; size = 36
_dsbcaps$ = -64						; size = 20
_format$ = -44						; size = 18
_pformat$ = -24						; size = 18
__$ArrayPad$ = -4					; size = 4
_hInst$ = 8						; size = 4
_DS_CreateBuffers PROC					; COMDAT

; 85   : {

	push	ebp
	mov	ebp, esp
	sub	esp, 164				; 000000a4H
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	mov	DWORD PTR __$ArrayPad$[ebp], eax
	push	ebx
	push	esi
	push	edi

; 86   : 	WAVEFORMATEX	pformat, format;
; 87   : 	DSBCAPS		dsbcaps;
; 88   : 	DSBUFFERDESC	dsbuf;
; 89   : 
; 90   : 	memset( &format, 0, sizeof( format ));

	push	18					; 00000012H
	push	0
	lea	eax, DWORD PTR _format$[ebp]
	push	eax
	call	_memset
	add	esp, 12					; 0000000cH

; 91   : 	format.wFormatTag = WAVE_FORMAT_PCM;

	mov	eax, 1
	mov	WORD PTR _format$[ebp], ax

; 92   : 	format.nChannels = 2;

	mov	eax, 2
	mov	WORD PTR _format$[ebp+2], ax

; 93   : 	format.wBitsPerSample = 16;

	mov	eax, 16					; 00000010H
	mov	WORD PTR _format$[ebp+14], ax

; 94   : 	format.nSamplesPerSec = SOUND_DMA_SPEED;

	mov	DWORD PTR _format$[ebp+4], 44100	; 0000ac44H

; 95   : 	format.nBlockAlign = format.nChannels * format.wBitsPerSample / 8;

	movzx	eax, WORD PTR _format$[ebp+2]
	movzx	ecx, WORD PTR _format$[ebp+14]
	imul	eax, ecx
	cdq
	and	edx, 7
	add	eax, edx
	sar	eax, 3
	mov	WORD PTR _format$[ebp+12], ax

; 96   : 	format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign; 

	movzx	eax, WORD PTR _format$[ebp+12]
	imul	eax, DWORD PTR _format$[ebp+4]
	mov	DWORD PTR _format$[ebp+8], eax

; 97   : 	format.cbSize = 0;

	xor	eax, eax
	mov	WORD PTR _format$[ebp+16], ax

; 98   : 
; 99   : 	if( pDS->lpVtbl->SetCooperativeLevel( pDS, hInst, DSSCL_EXCLUSIVE ) != DS_OK )

	push	3
	mov	eax, DWORD PTR _hInst$[ebp]
	push	eax
	mov	ecx, DWORD PTR _pDS
	push	ecx
	mov	edx, DWORD PTR _pDS
	mov	eax, DWORD PTR [edx]
	mov	ecx, DWORD PTR [eax+24]
	call	ecx
	test	eax, eax
	je	SHORT $LN2@DS_CreateB

; 100  : 	{
; 101  : 		Con_DPrintf( S_ERROR "DirectSound: failed to set EXCLUSIVE coop level\n" );

	push	OFFSET ??_C@_0DM@NNEFNPN@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@
	call	_Con_DPrintf
	add	esp, 4

; 102  : 		SNDDMA_FreeSound();

	call	_SNDDMA_FreeSound

; 103  : 		return false;

	xor	eax, eax
	jmp	$LN1@DS_CreateB
$LN2@DS_CreateB:

; 104  : 	}
; 105  : 
; 106  : 	// get access to the primary buffer, if possible, so we can set the sound hardware format
; 107  : 	memset( &dsbuf, 0, sizeof( dsbuf ));

	push	36					; 00000024H
	push	0
	lea	eax, DWORD PTR _dsbuf$[ebp]
	push	eax
	call	_memset
	add	esp, 12					; 0000000cH

; 108  : 	dsbuf.dwSize = sizeof( DSBUFFERDESC );

	mov	DWORD PTR _dsbuf$[ebp], 36		; 00000024H

; 109  : 	dsbuf.dwFlags = DSBCAPS_PRIMARYBUFFER;

	mov	DWORD PTR _dsbuf$[ebp+4], 1

; 110  : 	dsbuf.dwBufferBytes = 0;

	mov	DWORD PTR _dsbuf$[ebp+8], 0

; 111  : 	dsbuf.lpwfxFormat = NULL;

	mov	DWORD PTR _dsbuf$[ebp+16], 0

; 112  : 
; 113  : 	memset( &dsbcaps, 0, sizeof( dsbcaps ));

	push	20					; 00000014H
	push	0
	lea	eax, DWORD PTR _dsbcaps$[ebp]
	push	eax
	call	_memset
	add	esp, 12					; 0000000cH

; 114  : 	dsbcaps.dwSize = sizeof( dsbcaps );

	mov	DWORD PTR _dsbcaps$[ebp], 20		; 00000014H

; 115  : 	primary_format_set = false;

	mov	DWORD PTR _primary_format_set, 0

; 116  : 
; 117  : 	if( pDS->lpVtbl->CreateSoundBuffer( pDS, &dsbuf, &pDSPBuf, NULL ) == DS_OK )

	push	0
	push	OFFSET _pDSPBuf
	lea	eax, DWORD PTR _dsbuf$[ebp]
	push	eax
	mov	ecx, DWORD PTR _pDS
	push	ecx
	mov	edx, DWORD PTR _pDS
	mov	eax, DWORD PTR [edx]
	mov	ecx, DWORD PTR [eax+12]
	call	ecx
	test	eax, eax
	jne	SHORT $LN3@DS_CreateB

; 118  : 	{
; 119  : 		pformat = format;

	mov	eax, DWORD PTR _format$[ebp]
	mov	DWORD PTR _pformat$[ebp], eax
	mov	ecx, DWORD PTR _format$[ebp+4]
	mov	DWORD PTR _pformat$[ebp+4], ecx
	mov	edx, DWORD PTR _format$[ebp+8]
	mov	DWORD PTR _pformat$[ebp+8], edx
	mov	eax, DWORD PTR _format$[ebp+12]
	mov	DWORD PTR _pformat$[ebp+12], eax
	mov	cx, WORD PTR _format$[ebp+16]
	mov	WORD PTR _pformat$[ebp+16], cx

; 120  : 
; 121  : 		if( pDSPBuf->lpVtbl->SetFormat( pDSPBuf, &pformat ) != DS_OK )

	lea	eax, DWORD PTR _pformat$[ebp]
	push	eax
	mov	ecx, DWORD PTR _pDSPBuf
	push	ecx
	mov	edx, DWORD PTR _pDSPBuf
	mov	eax, DWORD PTR [edx]
	mov	ecx, DWORD PTR [eax+56]
	call	ecx
	test	eax, eax
	je	SHORT $LN4@DS_CreateB

; 122  : 		{
; 123  : 			if( snd_firsttime )

	cmp	DWORD PTR _snd_firsttime, 0
	je	SHORT $LN6@DS_CreateB

; 124  : 				Con_DPrintf( S_ERROR "DirectSound: failed to set primary sound format\n" );

	push	OFFSET ??_C@_0DM@KCOMJOCG@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@
	call	_Con_DPrintf
	add	esp, 4
$LN6@DS_CreateB:

; 125  : 		}

	jmp	SHORT $LN3@DS_CreateB
$LN4@DS_CreateB:

; 126  : 		else
; 127  : 		{
; 128  : 			primary_format_set = true;

	mov	DWORD PTR _primary_format_set, 1
$LN3@DS_CreateB:

; 129  : 		}
; 130  : 	}
; 131  : 
; 132  : 	// create the secondary buffer we'll actually work with
; 133  : 	memset( &dsbuf, 0, sizeof( dsbuf ));

	push	36					; 00000024H
	push	0
	lea	eax, DWORD PTR _dsbuf$[ebp]
	push	eax
	call	_memset
	add	esp, 12					; 0000000cH

; 134  : 	dsbuf.dwSize = sizeof( DSBUFFERDESC );

	mov	DWORD PTR _dsbuf$[ebp], 36		; 00000024H

; 135  : 	dsbuf.dwFlags = (DSBCAPS_CTRLFREQUENCY|DSBCAPS_LOCSOFTWARE);

	mov	DWORD PTR _dsbuf$[ebp+4], 40		; 00000028H

; 136  : 	dsbuf.dwBufferBytes = SECONDARY_BUFFER_SIZE;

	mov	DWORD PTR _dsbuf$[ebp+8], 65536		; 00010000H

; 137  : 	dsbuf.lpwfxFormat = &format;

	lea	eax, DWORD PTR _format$[ebp]
	mov	DWORD PTR _dsbuf$[ebp+16], eax

; 138  : 
; 139  : 	memset( &dsbcaps, 0, sizeof( dsbcaps ));

	push	20					; 00000014H
	push	0
	lea	eax, DWORD PTR _dsbcaps$[ebp]
	push	eax
	call	_memset
	add	esp, 12					; 0000000cH

; 140  : 	dsbcaps.dwSize = sizeof( dsbcaps );

	mov	DWORD PTR _dsbcaps$[ebp], 20		; 00000014H

; 141  : 
; 142  : 	if( pDS->lpVtbl->CreateSoundBuffer( pDS, &dsbuf, &pDSBuf, NULL ) != DS_OK )

	push	0
	push	OFFSET _pDSBuf
	lea	eax, DWORD PTR _dsbuf$[ebp]
	push	eax
	mov	ecx, DWORD PTR _pDS
	push	ecx
	mov	edx, DWORD PTR _pDS
	mov	eax, DWORD PTR [edx]
	mov	ecx, DWORD PTR [eax+12]
	call	ecx
	test	eax, eax
	je	SHORT $LN7@DS_CreateB

; 143  : 	{
; 144  : 		// couldn't get hardware, fallback to software.
; 145  : 		dsbuf.dwFlags = (DSBCAPS_LOCSOFTWARE|DSBCAPS_GETCURRENTPOSITION2);

	mov	DWORD PTR _dsbuf$[ebp+4], 65544		; 00010008H

; 146  : 
; 147  : 		if( pDS->lpVtbl->CreateSoundBuffer( pDS, &dsbuf, &pDSBuf, NULL ) != DS_OK )

	push	0
	push	OFFSET _pDSBuf
	lea	eax, DWORD PTR _dsbuf$[ebp]
	push	eax
	mov	ecx, DWORD PTR _pDS
	push	ecx
	mov	edx, DWORD PTR _pDS
	mov	eax, DWORD PTR [edx]
	mov	ecx, DWORD PTR [eax+12]
	call	ecx
	test	eax, eax
	je	SHORT $LN7@DS_CreateB

; 148  : 		{
; 149  : 			Con_DPrintf( S_ERROR "DirectSound: failed to create secondary buffer\n" );

	push	OFFSET ??_C@_0DL@PAIBECJB@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@
	call	_Con_DPrintf
	add	esp, 4

; 150  : 			SNDDMA_FreeSound ();

	call	_SNDDMA_FreeSound

; 151  : 			return false;

	xor	eax, eax
	jmp	$LN1@DS_CreateB
$LN7@DS_CreateB:

; 152  : 		}
; 153  : 	}
; 154  : 
; 155  : 	if( pDSBuf->lpVtbl->GetCaps( pDSBuf, &dsbcaps ) != DS_OK )

	lea	eax, DWORD PTR _dsbcaps$[ebp]
	push	eax
	mov	ecx, DWORD PTR _pDSBuf
	push	ecx
	mov	edx, DWORD PTR _pDSBuf
	mov	eax, DWORD PTR [edx]
	mov	ecx, DWORD PTR [eax+12]
	call	ecx
	test	eax, eax
	je	SHORT $LN9@DS_CreateB

; 156  : 	{
; 157  : 		Con_DPrintf( S_ERROR "DirectSound: failed to get capabilities\n" );

	push	OFFSET ??_C@_0DE@OIMKEAKI@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@
	call	_Con_DPrintf
	add	esp, 4

; 158  : 		SNDDMA_FreeSound ();

	call	_SNDDMA_FreeSound

; 159  : 		return false;

	xor	eax, eax
	jmp	$LN1@DS_CreateB
$LN9@DS_CreateB:

; 160  : 	}
; 161  : 
; 162  : 	// make sure mixer is active
; 163  : 	if( pDSBuf->lpVtbl->Play( pDSBuf, 0, 0, DSBPLAY_LOOPING ) != DS_OK )

	push	1
	push	0
	push	0
	mov	eax, DWORD PTR _pDSBuf
	push	eax
	mov	ecx, DWORD PTR _pDSBuf
	mov	edx, DWORD PTR [ecx]
	mov	eax, DWORD PTR [edx+48]
	call	eax
	test	eax, eax
	je	SHORT $LN10@DS_CreateB

; 164  : 	{
; 165  : 		Con_DPrintf( S_ERROR "DirectSound: failed to create circular buffer\n" );

	push	OFFSET ??_C@_0DK@CCJBMFBL@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@
	call	_Con_DPrintf
	add	esp, 4

; 166  : 		SNDDMA_FreeSound ();

	call	_SNDDMA_FreeSound

; 167  : 		return false;

	xor	eax, eax
	jmp	SHORT $LN1@DS_CreateB
$LN10@DS_CreateB:

; 168  : 	}
; 169  : 
; 170  : 	// we don't want anyone to access the buffer directly w/o locking it first
; 171  : 	lpData = NULL;

	mov	DWORD PTR _lpData, 0

; 172  : 	dma.samplepos = 0;

	mov	DWORD PTR _dma+4, 0

; 173  : 	snd_hwnd = (HWND)hInst;

	mov	eax, DWORD PTR _hInst$[ebp]
	mov	DWORD PTR _snd_hwnd, eax

; 174  : 	gSndBufSize = dsbcaps.dwBufferBytes;

	mov	eax, DWORD PTR _dsbcaps$[ebp+8]
	mov	DWORD PTR _gSndBufSize, eax

; 175  : 	dma.samples = gSndBufSize / 2;

	mov	eax, DWORD PTR _gSndBufSize
	shr	eax, 1
	mov	DWORD PTR _dma, eax

; 176  : 	dma.buffer = (byte *)lpData;

	mov	eax, DWORD PTR _lpData
	mov	DWORD PTR _dma+8, eax

; 177  : 
; 178  : 	SNDDMA_BeginPainting();

	call	_SNDDMA_BeginPainting

; 179  : 	if( dma.buffer ) memset( dma.buffer, 0, dma.samples * 2 );

	cmp	DWORD PTR _dma+8, 0
	je	SHORT $LN11@DS_CreateB
	mov	eax, DWORD PTR _dma
	shl	eax, 1
	push	eax
	push	0
	mov	ecx, DWORD PTR _dma+8
	push	ecx
	call	_memset
	add	esp, 12					; 0000000cH
$LN11@DS_CreateB:

; 180  : 	SNDDMA_Submit();

	call	_SNDDMA_Submit

; 181  : 
; 182  : 	return true;

	mov	eax, 1
$LN1@DS_CreateB:

; 183  : }

	pop	edi
	pop	esi
	pop	ebx
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	0
_DS_CreateBuffers ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_backend.c
;	COMDAT _DSoundError
_TEXT	SEGMENT
tv64 = -68						; size = 4
_error$ = 8						; size = 4
_DSoundError PROC					; COMDAT

; 63   : {

	push	ebp
	mov	ebp, esp
	sub	esp, 68					; 00000044H
	push	ebx
	push	esi
	push	edi

; 64   : 	switch( error )

	mov	eax, DWORD PTR _error$[ebp]
	mov	DWORD PTR tv64[ebp], eax
	cmp	DWORD PTR tv64[ebp], -2005401530	; 88780046H
	jg	SHORT $LN9@DSoundErro
	cmp	DWORD PTR tv64[ebp], -2005401530	; 88780046H
	je	SHORT $LN7@DSoundErro
	cmp	DWORD PTR tv64[ebp], -2147024809	; 80070057H
	je	SHORT $LN6@DSoundErro
	cmp	DWORD PTR tv64[ebp], -2005401550	; 88780032H
	je	SHORT $LN5@DSoundErro
	jmp	SHORT $LN2@DSoundErro
$LN9@DSoundErro:
	cmp	DWORD PTR tv64[ebp], -2005401450	; 88780096H
	je	SHORT $LN4@DSoundErro
	jmp	SHORT $LN2@DSoundErro
$LN4@DSoundErro:

; 65   : 	{
; 66   : 	case DSERR_BUFFERLOST:
; 67   : 		return "buffer is lost";

	mov	eax, OFFSET ??_C@_0P@KDAEJHKH@buffer?5is?5lost@
	jmp	SHORT $LN1@DSoundErro
$LN5@DSoundErro:

; 68   : 	case DSERR_INVALIDCALL:
; 69   : 		return "invalid call";

	mov	eax, OFFSET ??_C@_0N@EIBHAONH@invalid?5call@
	jmp	SHORT $LN1@DSoundErro
$LN6@DSoundErro:

; 70   : 	case DSERR_INVALIDPARAM:
; 71   : 		return "invalid param";

	mov	eax, OFFSET ??_C@_0O@PFPAIGFJ@invalid?5param@
	jmp	SHORT $LN1@DSoundErro
$LN7@DSoundErro:

; 72   : 	case DSERR_PRIOLEVELNEEDED:
; 73   : 		return "invalid priority level";

	mov	eax, OFFSET ??_C@_0BH@OMFNMBKG@invalid?5priority?5level@
	jmp	SHORT $LN1@DSoundErro
$LN2@DSoundErro:

; 74   : 	}
; 75   : 
; 76   : 	return "unknown error";

	mov	eax, OFFSET ??_C@_0O@BFJCFAAK@unknown?5error@
$LN1@DSoundErro:

; 77   : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_DSoundError ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_backend.c
;	COMDAT _SNDDMA_FreeSound
_TEXT	SEGMENT
_SNDDMA_FreeSound PROC					; COMDAT

; 237  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi

; 238  : 	if( pDS )

	cmp	DWORD PTR _pDS, 0
	je	SHORT $LN2@SNDDMA_Fre

; 239  : 	{
; 240  : 		DS_DestroyBuffers();

	call	_DS_DestroyBuffers

; 241  : 		pDS->lpVtbl->Release( pDS );

	mov	eax, DWORD PTR _pDS
	push	eax
	mov	ecx, DWORD PTR _pDS
	mov	edx, DWORD PTR [ecx]
	mov	eax, DWORD PTR [edx+8]
	call	eax

; 242  : 		Sys_FreeLibrary( &dsound_dll );

	push	OFFSET _dsound_dll
	call	_Sys_FreeLibrary
	add	esp, 4
$LN2@SNDDMA_Fre:

; 243  : 	}
; 244  : 
; 245  : 	lpData = NULL;

	mov	DWORD PTR _lpData, 0

; 246  : 	pDSPBuf = NULL;

	mov	DWORD PTR _pDSPBuf, 0

; 247  : 	pDSBuf = NULL;

	mov	DWORD PTR _pDSBuf, 0

; 248  : 	pDS = NULL;

	mov	DWORD PTR _pDS, 0

; 249  : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_SNDDMA_FreeSound ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_backend.c
;	COMDAT _SNDDMA_InitDirect
_TEXT	SEGMENT
_hresult$ = -104					; size = 4
_dscaps$ = -100						; size = 96
__$ArrayPad$ = -4					; size = 4
_hInst$ = 8						; size = 4
_SNDDMA_InitDirect PROC					; COMDAT

; 259  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 168				; 000000a8H
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	mov	DWORD PTR __$ArrayPad$[ebp], eax
	push	ebx
	push	esi
	push	edi

; 260  : 	DSCAPS	dscaps;
; 261  : 	HRESULT	hresult;
; 262  : 
; 263  : 	if( !dsound_dll.link )

	cmp	DWORD PTR _dsound_dll+12, 0
	jne	SHORT $LN2@SNDDMA_Ini

; 264  : 	{
; 265  : 		if( !Sys_LoadLibrary( &dsound_dll ))

	push	OFFSET _dsound_dll
	call	_Sys_LoadLibrary
	add	esp, 4
	test	eax, eax
	jne	SHORT $LN2@SNDDMA_Ini

; 266  : 			return SIS_FAILURE;

	mov	eax, 1
	jmp	$LN1@SNDDMA_Ini
$LN2@SNDDMA_Ini:

; 267  : 	}
; 268  : 
; 269  : 	if(( hresult = iDirectSoundCreate( NULL, &pDS, NULL )) != DS_OK )

	push	0
	push	OFFSET _pDS
	push	0
	call	DWORD PTR _pDirectSoundCreate
	mov	DWORD PTR _hresult$[ebp], eax
	cmp	DWORD PTR _hresult$[ebp], 0
	je	SHORT $LN4@SNDDMA_Ini

; 270  : 	{
; 271  : 		if( hresult != DSERR_ALLOCATED )

	cmp	DWORD PTR _hresult$[ebp], -2005401590	; 8878000aH
	je	SHORT $LN5@SNDDMA_Ini

; 272  : 			return SIS_FAILURE;

	mov	eax, 1
	jmp	SHORT $LN1@SNDDMA_Ini
$LN5@SNDDMA_Ini:

; 273  : 
; 274  : 		Con_DPrintf( S_ERROR "DirectSound: hardware already in use\n" );

	push	OFFSET ??_C@_0DB@HIJBJALE@?$FO1Error?3?$FO7?5DirectSound?3?5hardwar@
	call	_Con_DPrintf
	add	esp, 4

; 275  : 		return SIS_NOTAVAIL;

	mov	eax, 2
	jmp	SHORT $LN1@SNDDMA_Ini
$LN4@SNDDMA_Ini:

; 276  : 	}
; 277  : 
; 278  : 	dscaps.dwSize = sizeof( dscaps );

	mov	DWORD PTR _dscaps$[ebp], 96		; 00000060H

; 279  : 
; 280  : 	if( pDS->lpVtbl->GetCaps( pDS, &dscaps ) != DS_OK )

	lea	eax, DWORD PTR _dscaps$[ebp]
	push	eax
	mov	ecx, DWORD PTR _pDS
	push	ecx
	mov	edx, DWORD PTR _pDS
	mov	eax, DWORD PTR [edx]
	mov	ecx, DWORD PTR [eax+16]
	call	ecx
	test	eax, eax
	je	SHORT $LN6@SNDDMA_Ini

; 281  : 		Con_DPrintf( S_ERROR "DirectSound: failed to get capabilities\n" );

	push	OFFSET ??_C@_0DE@OIMKEAKI@?$FO1Error?3?$FO7?5DirectSound?3?5failed?5@
	call	_Con_DPrintf
	add	esp, 4
$LN6@SNDDMA_Ini:

; 282  : 
; 283  : 	if( FBitSet( dscaps.dwFlags, DSCAPS_EMULDRIVER ))

	mov	eax, DWORD PTR _dscaps$[ebp+4]
	and	eax, 32					; 00000020H
	je	SHORT $LN7@SNDDMA_Ini

; 284  : 	{
; 285  : 		Con_DPrintf( S_ERROR "DirectSound: driver not installed\n" );

	push	OFFSET ??_C@_0CO@PINFFA@?$FO1Error?3?$FO7?5DirectSound?3?5driver?5@
	call	_Con_DPrintf
	add	esp, 4

; 286  : 		SNDDMA_FreeSound();

	call	_SNDDMA_FreeSound

; 287  : 		return SIS_FAILURE;

	mov	eax, 1
	jmp	SHORT $LN1@SNDDMA_Ini
$LN7@SNDDMA_Ini:

; 288  : 	}
; 289  : 
; 290  : 	if( !DS_CreateBuffers( hInst ))

	mov	eax, DWORD PTR _hInst$[ebp]
	push	eax
	call	_DS_CreateBuffers
	add	esp, 4
	test	eax, eax
	jne	SHORT $LN8@SNDDMA_Ini

; 291  : 		return SIS_FAILURE;

	mov	eax, 1
	jmp	SHORT $LN1@SNDDMA_Ini
$LN8@SNDDMA_Ini:

; 292  : 
; 293  : 	return SIS_SUCCESS;

	xor	eax, eax
$LN1@SNDDMA_Ini:

; 294  : }

	pop	edi
	pop	esi
	pop	ebx
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	0
_SNDDMA_InitDirect ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_backend.c
;	COMDAT _SNDDMA_UnlockSound
_TEXT	SEGMENT
_SNDDMA_UnlockSound PROC				; COMDAT

; 226  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi

; 227  : 	if( pDSBuf != NULL )

	cmp	DWORD PTR _pDSBuf, 0
	je	SHORT $LN1@SNDDMA_Unl

; 228  : 		pDSBuf->lpVtbl->Play( pDSBuf, 0, 0, DSBPLAY_LOOPING );

	push	1
	push	0
	push	0
	mov	eax, DWORD PTR _pDSBuf
	push	eax
	mov	ecx, DWORD PTR _pDSBuf
	mov	edx, DWORD PTR [ecx]
	mov	eax, DWORD PTR [edx+48]
	call	eax
$LN1@SNDDMA_Unl:

; 229  : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_SNDDMA_UnlockSound ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_backend.c
;	COMDAT _SNDDMA_LockSound
_TEXT	SEGMENT
_SNDDMA_LockSound PROC					; COMDAT

; 215  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi

; 216  : 	if( pDSBuf != NULL )

	cmp	DWORD PTR _pDSBuf, 0
	je	SHORT $LN1@SNDDMA_Loc

; 217  : 		pDSBuf->lpVtbl->Stop( pDSBuf );

	mov	eax, DWORD PTR _pDSBuf
	push	eax
	mov	ecx, DWORD PTR _pDSBuf
	mov	edx, DWORD PTR [ecx]
	mov	eax, DWORD PTR [edx+72]
	call	eax
$LN1@SNDDMA_Loc:

; 218  : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_SNDDMA_LockSound ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_backend.c
;	COMDAT _SNDDMA_Submit
_TEXT	SEGMENT
_SNDDMA_Submit PROC					; COMDAT

; 440  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi

; 441  : 	if( !dma.buffer ) return;

	cmp	DWORD PTR _dma+8, 0
	jne	SHORT $LN2@SNDDMA_Sub
	jmp	SHORT $LN1@SNDDMA_Sub
$LN2@SNDDMA_Sub:

; 442  : 	// unlock the dsound buffer
; 443  : 	if( pDSBuf ) pDSBuf->lpVtbl->Unlock( pDSBuf, dma.buffer, locksize, NULL, 0 );

	cmp	DWORD PTR _pDSBuf, 0
	je	SHORT $LN1@SNDDMA_Sub
	push	0
	push	0
	mov	eax, DWORD PTR _locksize
	push	eax
	mov	ecx, DWORD PTR _dma+8
	push	ecx
	mov	edx, DWORD PTR _pDSBuf
	push	edx
	mov	eax, DWORD PTR _pDSBuf
	mov	ecx, DWORD PTR [eax]
	mov	edx, DWORD PTR [ecx+76]
	call	edx
$LN1@SNDDMA_Sub:

; 444  : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_SNDDMA_Submit ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_backend.c
;	COMDAT _SNDDMA_BeginPainting
_TEXT	SEGMENT
_dwStatus$ = -24					; size = 4
_hr$ = -20						; size = 4
_pbuf2$ = -16						; size = 4
_pbuf$ = -12						; size = 4
_dwSize2$ = -8						; size = 4
_reps$ = -4						; size = 4
_SNDDMA_BeginPainting PROC				; COMDAT

; 393  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 88					; 00000058H
	push	ebx
	push	esi
	push	edi

; 394  : 	int	reps;
; 395  : 	DWORD	dwSize2;
; 396  : 	DWORD	*pbuf, *pbuf2;
; 397  : 	HRESULT	hr;
; 398  : 	DWORD	dwStatus;
; 399  : 
; 400  : 	if( !pDSBuf ) return;

	cmp	DWORD PTR _pDSBuf, 0
	jne	SHORT $LN4@SNDDMA_Beg
	jmp	$LN1@SNDDMA_Beg
$LN4@SNDDMA_Beg:

; 401  : 
; 402  : 	// if the buffer was lost or stopped, restore it and/or restart it
; 403  : 	if( pDSBuf->lpVtbl->GetStatus( pDSBuf, &dwStatus ) != DS_OK )

	lea	eax, DWORD PTR _dwStatus$[ebp]
	push	eax
	mov	ecx, DWORD PTR _pDSBuf
	push	ecx
	mov	edx, DWORD PTR _pDSBuf
	mov	eax, DWORD PTR [edx]
	mov	ecx, DWORD PTR [eax+36]
	call	ecx
	test	eax, eax
	je	SHORT $LN5@SNDDMA_Beg

; 404  : 		Con_DPrintf( S_ERROR "BeginPainting: couldn't get sound buffer status\n" );

	push	OFFSET ??_C@_0DM@NLDNIIAO@?$FO1Error?3?$FO7?5BeginPainting?3?5could@
	call	_Con_DPrintf
	add	esp, 4
$LN5@SNDDMA_Beg:

; 405  : 	
; 406  : 	if( dwStatus & DSBSTATUS_BUFFERLOST )

	mov	eax, DWORD PTR _dwStatus$[ebp]
	and	eax, 2
	je	SHORT $LN6@SNDDMA_Beg

; 407  : 		pDSBuf->lpVtbl->Restore( pDSBuf );

	mov	eax, DWORD PTR _pDSBuf
	push	eax
	mov	ecx, DWORD PTR _pDSBuf
	mov	edx, DWORD PTR [ecx]
	mov	eax, DWORD PTR [edx+80]
	call	eax
$LN6@SNDDMA_Beg:

; 408  : 	
; 409  : 	if( !FBitSet( dwStatus, DSBSTATUS_PLAYING ))

	mov	eax, DWORD PTR _dwStatus$[ebp]
	and	eax, 1
	jne	SHORT $LN7@SNDDMA_Beg

; 410  : 		pDSBuf->lpVtbl->Play( pDSBuf, 0, 0, DSBPLAY_LOOPING );

	push	1
	push	0
	push	0
	mov	eax, DWORD PTR _pDSBuf
	push	eax
	mov	ecx, DWORD PTR _pDSBuf
	mov	edx, DWORD PTR [ecx]
	mov	eax, DWORD PTR [edx+48]
	call	eax
$LN7@SNDDMA_Beg:

; 411  : 
; 412  : 	// lock the dsound buffer
; 413  : 	dma.buffer = NULL;

	mov	DWORD PTR _dma+8, 0

; 414  : 	reps = 0;

	mov	DWORD PTR _reps$[ebp], 0
$LN2@SNDDMA_Beg:

; 415  : 
; 416  : 	while(( hr = pDSBuf->lpVtbl->Lock( pDSBuf, 0, gSndBufSize, &pbuf, &locksize, &pbuf2, &dwSize2, 0 )) != DS_OK )

	push	0
	lea	eax, DWORD PTR _dwSize2$[ebp]
	push	eax
	lea	ecx, DWORD PTR _pbuf2$[ebp]
	push	ecx
	push	OFFSET _locksize
	lea	edx, DWORD PTR _pbuf$[ebp]
	push	edx
	mov	eax, DWORD PTR _gSndBufSize
	push	eax
	push	0
	mov	ecx, DWORD PTR _pDSBuf
	push	ecx
	mov	edx, DWORD PTR _pDSBuf
	mov	eax, DWORD PTR [edx]
	mov	ecx, DWORD PTR [eax+44]
	call	ecx
	mov	DWORD PTR _hr$[ebp], eax
	cmp	DWORD PTR _hr$[ebp], 0
	je	SHORT $LN3@SNDDMA_Beg

; 417  : 	{
; 418  : 		if( hr != DSERR_BUFFERLOST )

	cmp	DWORD PTR _hr$[ebp], -2005401450	; 88780096H
	je	SHORT $LN8@SNDDMA_Beg

; 419  : 		{
; 420  : 			Con_DPrintf( S_ERROR "BeginPainting: %s\n", DSoundError( hr ));

	mov	eax, DWORD PTR _hr$[ebp]
	push	eax
	call	_DSoundError
	add	esp, 4
	push	eax
	push	OFFSET ??_C@_0BO@NCFLDAJJ@?$FO1Error?3?$FO7?5BeginPainting?3?5?$CFs?6@
	call	_Con_DPrintf
	add	esp, 8

; 421  : 			S_Shutdown ();

	call	_S_Shutdown

; 422  : 			return;

	jmp	SHORT $LN1@SNDDMA_Beg

; 423  : 		}

	jmp	SHORT $LN9@SNDDMA_Beg
$LN8@SNDDMA_Beg:

; 424  : 		else pDSBuf->lpVtbl->Restore( pDSBuf );

	mov	eax, DWORD PTR _pDSBuf
	push	eax
	mov	ecx, DWORD PTR _pDSBuf
	mov	edx, DWORD PTR [ecx]
	mov	eax, DWORD PTR [edx+80]
	call	eax
$LN9@SNDDMA_Beg:

; 425  : 		if( ++reps > 2 ) return;

	mov	eax, DWORD PTR _reps$[ebp]
	add	eax, 1
	mov	DWORD PTR _reps$[ebp], eax
	cmp	DWORD PTR _reps$[ebp], 2
	jle	SHORT $LN10@SNDDMA_Beg
	jmp	SHORT $LN1@SNDDMA_Beg
$LN10@SNDDMA_Beg:

; 426  : 	}

	jmp	$LN2@SNDDMA_Beg
$LN3@SNDDMA_Beg:

; 427  : 
; 428  : 	dma.buffer = (byte *)pbuf;

	mov	eax, DWORD PTR _pbuf$[ebp]
	mov	DWORD PTR _dma+8, eax
$LN1@SNDDMA_Beg:

; 429  : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_SNDDMA_BeginPainting ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_backend.c
;	COMDAT _SNDDMA_Shutdown
_TEXT	SEGMENT
_SNDDMA_Shutdown PROC					; COMDAT

; 454  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi

; 455  : 	if( !dma.initialized ) return;

	cmp	DWORD PTR _dma+12, 0
	jne	SHORT $LN2@SNDDMA_Shu
	jmp	SHORT $LN1@SNDDMA_Shu
$LN2@SNDDMA_Shu:

; 456  : 	dma.initialized = false;

	mov	DWORD PTR _dma+12, 0

; 457  : 	SNDDMA_FreeSound();

	call	_SNDDMA_FreeSound
$LN1@SNDDMA_Shu:

; 458  : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_SNDDMA_Shutdown ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_backend.c
;	COMDAT _SNDDMA_GetSoundtime
_TEXT	SEGMENT
_fullsamples$ = -8					; size = 4
_samplepos$ = -4					; size = 4
_SNDDMA_GetSoundtime PROC				; COMDAT

; 356  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 72					; 00000048H
	push	ebx
	push	esi
	push	edi

; 357  : 	static int	buffers, oldsamplepos;
; 358  : 	int		samplepos, fullsamples;
; 359  : 	
; 360  : 	fullsamples = dma.samples / 2;

	mov	eax, DWORD PTR _dma
	cdq
	sub	eax, edx
	sar	eax, 1
	mov	DWORD PTR _fullsamples$[ebp], eax

; 361  : 
; 362  : 	// it is possible to miscount buffers
; 363  : 	// if it has wrapped twice between
; 364  : 	// calls to S_Update.  Oh well.
; 365  : 	samplepos = SNDDMA_GetDMAPos();

	call	_SNDDMA_GetDMAPos
	mov	DWORD PTR _samplepos$[ebp], eax

; 366  : 
; 367  : 	if( samplepos < oldsamplepos )

	mov	eax, DWORD PTR _samplepos$[ebp]
	cmp	eax, DWORD PTR ?oldsamplepos@?1??SNDDMA_GetSoundtime@@9@9
	jge	SHORT $LN2@SNDDMA_Get

; 368  : 	{
; 369  : 		buffers++; // buffer wrapped

	mov	eax, DWORD PTR ?buffers@?1??SNDDMA_GetSoundtime@@9@9
	add	eax, 1
	mov	DWORD PTR ?buffers@?1??SNDDMA_GetSoundtime@@9@9, eax

; 370  : 
; 371  : 		if( paintedtime > 0x40000000 )

	cmp	DWORD PTR _paintedtime, 1073741824	; 40000000H
	jle	SHORT $LN2@SNDDMA_Get

; 372  : 		{	
; 373  : 			// time to chop things off to avoid 32 bit limits
; 374  : 			buffers = 0;

	mov	DWORD PTR ?buffers@?1??SNDDMA_GetSoundtime@@9@9, 0

; 375  : 			paintedtime = fullsamples;

	mov	eax, DWORD PTR _fullsamples$[ebp]
	mov	DWORD PTR _paintedtime, eax

; 376  : 			S_StopAllSounds( true );

	push	1
	call	_S_StopAllSounds
	add	esp, 4
$LN2@SNDDMA_Get:

; 377  : 		}
; 378  : 	}
; 379  : 
; 380  : 	oldsamplepos = samplepos;

	mov	eax, DWORD PTR _samplepos$[ebp]
	mov	DWORD PTR ?oldsamplepos@?1??SNDDMA_GetSoundtime@@9@9, eax

; 381  : 
; 382  : 	return (buffers * fullsamples + samplepos / 2);

	mov	ecx, DWORD PTR ?buffers@?1??SNDDMA_GetSoundtime@@9@9
	imul	ecx, DWORD PTR _fullsamples$[ebp]
	mov	eax, DWORD PTR _samplepos$[ebp]
	cdq
	sub	eax, edx
	sar	eax, 1
	add	eax, ecx

; 383  : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_SNDDMA_GetSoundtime ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_backend.c
;	COMDAT _SNDDMA_Init
_TEXT	SEGMENT
_hInst$ = 8						; size = 4
_SNDDMA_Init PROC					; COMDAT

; 305  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi

; 306  : 	// already initialized
; 307  : 	if( dma.initialized ) return true;

	cmp	DWORD PTR _dma+12, 0
	je	SHORT $LN2@SNDDMA_Ini
	mov	eax, 1
	jmp	SHORT $LN1@SNDDMA_Ini
$LN2@SNDDMA_Ini:

; 308  : 
; 309  : 	memset( &dma, 0, sizeof( dma ));

	push	16					; 00000010H
	push	0
	push	OFFSET _dma
	call	_memset
	add	esp, 12					; 0000000cH

; 310  : 
; 311  : 	// init DirectSound
; 312  : 	if( SNDDMA_InitDirect( hInst ) != SIS_SUCCESS )

	mov	eax, DWORD PTR _hInst$[ebp]
	push	eax
	call	_SNDDMA_InitDirect
	add	esp, 4
	test	eax, eax
	je	SHORT $LN3@SNDDMA_Ini

; 313  : 		return false;

	xor	eax, eax
	jmp	SHORT $LN1@SNDDMA_Ini
$LN3@SNDDMA_Ini:

; 314  : 	dma.initialized = true;

	mov	DWORD PTR _dma+12, 1

; 315  : 	snd_firsttime = false;

	mov	DWORD PTR _snd_firsttime, 0

; 316  : 
; 317  : 	return true;

	mov	eax, 1
$LN1@SNDDMA_Ini:

; 318  : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_SNDDMA_Init ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /ZI
; File D:\DevDragon\XashFE\dev\src\engine\client\s_backend.c
;	COMDAT _S_Activate
_TEXT	SEGMENT
_active$ = 8						; size = 4
_hInst$ = 12						; size = 4
_S_Activate PROC					; COMDAT

; 470  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 64					; 00000040H
	push	ebx
	push	esi
	push	edi

; 471  : 	if( !dma.initialized ) return;

	cmp	DWORD PTR _dma+12, 0
	jne	SHORT $LN2@S_Activate
	jmp	SHORT $LN1@S_Activate
$LN2@S_Activate:

; 472  : 	snd_hwnd = (HWND)hInst;

	mov	eax, DWORD PTR _hInst$[ebp]
	mov	DWORD PTR _snd_hwnd, eax

; 473  : 
; 474  : 	if( !pDS || !snd_hwnd )

	cmp	DWORD PTR _pDS, 0
	je	SHORT $LN4@S_Activate
	cmp	DWORD PTR _snd_hwnd, 0
	jne	SHORT $LN3@S_Activate
$LN4@S_Activate:

; 475  : 		return;

	jmp	SHORT $LN1@S_Activate
$LN3@S_Activate:

; 476  : 
; 477  : 	if( active )

	cmp	DWORD PTR _active$[ebp], 0
	je	SHORT $LN5@S_Activate

; 478  : 		DS_CreateBuffers( snd_hwnd );

	mov	eax, DWORD PTR _snd_hwnd
	push	eax
	call	_DS_CreateBuffers
	add	esp, 4
	jmp	SHORT $LN1@S_Activate
$LN5@S_Activate:

; 479  : 	else DS_DestroyBuffers();

	call	_DS_DestroyBuffers
$LN1@S_Activate:

; 480  : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_S_Activate ENDP
_TEXT	ENDS
END