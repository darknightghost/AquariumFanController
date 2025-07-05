                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ISO C Compiler
                                      3 ; Version 4.5.0 #15242 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module CMakeCCompilerId
                                      6 	
                                      7 	.optsdcc -mmcs51 --model-small
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main_PARM_2
                                     12 	.globl _info_version
                                     13 	.globl _main
                                     14 	.globl _info_language_extensions_default
                                     15 	.globl _info_language_standard_default
                                     16 	.globl _info_arch
                                     17 	.globl _info_platform
                                     18 	.globl _info_compiler
                                     19 ;--------------------------------------------------------
                                     20 ; special function registers
                                     21 ;--------------------------------------------------------
                                     22 	.area RSEG    (ABS,DATA)
      000000                         23 	.org 0x0000
                                     24 ;--------------------------------------------------------
                                     25 ; special function bits
                                     26 ;--------------------------------------------------------
                                     27 	.area RSEG    (ABS,DATA)
      000000                         28 	.org 0x0000
                                     29 ;--------------------------------------------------------
                                     30 ; overlayable register banks
                                     31 ;--------------------------------------------------------
                                     32 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                         33 	.ds 8
                                     34 ;--------------------------------------------------------
                                     35 ; internal ram data
                                     36 ;--------------------------------------------------------
                                     37 	.area DSEG    (DATA)
      000008                         38 _info_compiler::
      000008                         39 	.ds 3
      00000B                         40 _info_platform::
      00000B                         41 	.ds 3
      00000E                         42 _info_arch::
      00000E                         43 	.ds 3
      000011                         44 _info_language_standard_default::
      000011                         45 	.ds 3
      000014                         46 _info_language_extensions_default::
      000014                         47 	.ds 3
                                     48 ;--------------------------------------------------------
                                     49 ; overlayable items in internal ram
                                     50 ;--------------------------------------------------------
                                     51 	.area	OSEG    (OVR,DATA)
      000017                         52 _main_PARM_2:
      000017                         53 	.ds 3
                                     54 ;--------------------------------------------------------
                                     55 ; Stack segment in internal ram
                                     56 ;--------------------------------------------------------
                                     57 	.area SSEG
      00001A                         58 __start__stack:
      00001A                         59 	.ds	1
                                     60 
                                     61 ;--------------------------------------------------------
                                     62 ; indirectly addressable internal ram data
                                     63 ;--------------------------------------------------------
                                     64 	.area ISEG    (DATA)
                                     65 ;--------------------------------------------------------
                                     66 ; absolute internal ram data
                                     67 ;--------------------------------------------------------
                                     68 	.area IABS    (ABS,DATA)
                                     69 	.area IABS    (ABS,DATA)
                                     70 ;--------------------------------------------------------
                                     71 ; bit data
                                     72 ;--------------------------------------------------------
                                     73 	.area BSEG    (BIT)
                                     74 ;--------------------------------------------------------
                                     75 ; paged external ram data
                                     76 ;--------------------------------------------------------
                                     77 	.area PSEG    (PAG,XDATA)
                                     78 ;--------------------------------------------------------
                                     79 ; uninitialized external ram data
                                     80 ;--------------------------------------------------------
                                     81 	.area XSEG    (XDATA)
                                     82 ;--------------------------------------------------------
                                     83 ; absolute external ram data
                                     84 ;--------------------------------------------------------
                                     85 	.area XABS    (ABS,XDATA)
                                     86 ;--------------------------------------------------------
                                     87 ; initialized external ram data
                                     88 ;--------------------------------------------------------
                                     89 	.area XISEG   (XDATA)
                                     90 	.area HOME    (CODE)
                                     91 	.area GSINIT0 (CODE)
                                     92 	.area GSINIT1 (CODE)
                                     93 	.area GSINIT2 (CODE)
                                     94 	.area GSINIT3 (CODE)
                                     95 	.area GSINIT4 (CODE)
                                     96 	.area GSINIT5 (CODE)
                                     97 	.area GSINIT  (CODE)
                                     98 	.area GSFINAL (CODE)
                                     99 	.area CSEG    (CODE)
                                    100 ;--------------------------------------------------------
                                    101 ; interrupt vector
                                    102 ;--------------------------------------------------------
                                    103 	.area HOME    (CODE)
      000000                        104 __interrupt_vect:
      000000 02 00 4C         [24]  105 	ljmp	__sdcc_gsinit_startup
                                    106 ; restartable atomic support routines
      000003                        107 	.ds	5
      000008                        108 sdcc_atomic_exchange_rollback_start::
      000008 00               [12]  109 	nop
      000009 00               [12]  110 	nop
      00000A                        111 sdcc_atomic_exchange_pdata_impl:
      00000A E2               [24]  112 	movx	a, @r0
      00000B FB               [12]  113 	mov	r3, a
      00000C EA               [12]  114 	mov	a, r2
      00000D F2               [24]  115 	movx	@r0, a
      00000E 80 2C            [24]  116 	sjmp	sdcc_atomic_exchange_exit
      000010 00               [12]  117 	nop
      000011 00               [12]  118 	nop
      000012                        119 sdcc_atomic_exchange_xdata_impl:
      000012 E0               [24]  120 	movx	a, @dptr
      000013 FB               [12]  121 	mov	r3, a
      000014 EA               [12]  122 	mov	a, r2
      000015 F0               [24]  123 	movx	@dptr, a
      000016 80 24            [24]  124 	sjmp	sdcc_atomic_exchange_exit
      000018                        125 sdcc_atomic_compare_exchange_idata_impl:
      000018 E6               [12]  126 	mov	a, @r0
      000019 B5 02 02         [24]  127 	cjne	a, ar2, .+#5
      00001C EB               [12]  128 	mov	a, r3
      00001D F6               [12]  129 	mov	@r0, a
      00001E 22               [24]  130 	ret
      00001F 00               [12]  131 	nop
      000020                        132 sdcc_atomic_compare_exchange_pdata_impl:
      000020 E2               [24]  133 	movx	a, @r0
      000021 B5 02 02         [24]  134 	cjne	a, ar2, .+#5
      000024 EB               [12]  135 	mov	a, r3
      000025 F2               [24]  136 	movx	@r0, a
      000026 22               [24]  137 	ret
      000027 00               [12]  138 	nop
      000028                        139 sdcc_atomic_compare_exchange_xdata_impl:
      000028 E0               [24]  140 	movx	a, @dptr
      000029 B5 02 02         [24]  141 	cjne	a, ar2, .+#5
      00002C EB               [12]  142 	mov	a, r3
      00002D F0               [24]  143 	movx	@dptr, a
      00002E 22               [24]  144 	ret
      00002F                        145 sdcc_atomic_exchange_rollback_end::
                                    146 
      00002F                        147 sdcc_atomic_exchange_gptr_impl::
      00002F 30 F6 E0         [24]  148 	jnb	b.6, sdcc_atomic_exchange_xdata_impl
      000032 A8 82            [24]  149 	mov	r0, dpl
      000034 20 F5 D3         [24]  150 	jb	b.5, sdcc_atomic_exchange_pdata_impl
      000037                        151 sdcc_atomic_exchange_idata_impl:
      000037 EA               [12]  152 	mov	a, r2
      000038 C6               [12]  153 	xch	a, @r0
      000039 F5 82            [12]  154 	mov	dpl, a
      00003B 22               [24]  155 	ret
      00003C                        156 sdcc_atomic_exchange_exit:
      00003C 8B 82            [24]  157 	mov	dpl, r3
      00003E 22               [24]  158 	ret
      00003F                        159 sdcc_atomic_compare_exchange_gptr_impl::
      00003F 30 F6 E6         [24]  160 	jnb	b.6, sdcc_atomic_compare_exchange_xdata_impl
      000042 A8 82            [24]  161 	mov	r0, dpl
      000044 20 F5 D9         [24]  162 	jb	b.5, sdcc_atomic_compare_exchange_pdata_impl
      000047 80 CF            [24]  163 	sjmp	sdcc_atomic_compare_exchange_idata_impl
                                    164 ;--------------------------------------------------------
                                    165 ; global & static initialisations
                                    166 ;--------------------------------------------------------
                                    167 	.area HOME    (CODE)
                                    168 	.area GSINIT  (CODE)
                                    169 	.area GSFINAL (CODE)
                                    170 	.area GSINIT  (CODE)
                                    171 	.globl __sdcc_gsinit_startup
                                    172 	.globl __sdcc_program_startup
                                    173 	.globl __start__stack
                                    174 	.globl __mcs51_genXINIT
                                    175 	.globl __mcs51_genXRAMCLEAR
                                    176 	.globl __mcs51_genRAMCLEAR
                                    177 ;	CMakeCCompilerId.c:456: char const* info_compiler = "INFO" ":" "compiler[" COMPILER_ID "]";
      0000A5 75 08 BF         [24]  178 	mov	_info_compiler,#___str_0
      0000A8 75 09 01         [24]  179 	mov	(_info_compiler + 1),#(___str_0 >> 8)
      0000AB 75 0A 80         [24]  180 	mov	(_info_compiler + 2),#0x80
                                    181 ;	CMakeCCompilerId.c:826: char const* info_platform = "INFO" ":" "platform[" PLATFORM_ID "]";
      0000AE 75 0B D3         [24]  182 	mov	_info_platform,#___str_1
      0000B1 75 0C 01         [24]  183 	mov	(_info_platform + 1),#(___str_1 >> 8)
      0000B4 75 0D 80         [24]  184 	mov	(_info_platform + 2),#0x80
                                    185 ;	CMakeCCompilerId.c:827: char const* info_arch = "INFO" ":" "arch[" ARCHITECTURE_ID "]";
      0000B7 75 0E E3         [24]  186 	mov	_info_arch,#___str_2
      0000BA 75 0F 01         [24]  187 	mov	(_info_arch + 1),#(___str_2 >> 8)
      0000BD 75 10 80         [24]  188 	mov	(_info_arch + 2),#0x80
                                    189 ;	CMakeCCompilerId.c:857: const char* info_language_standard_default =
      0000C0 75 11 EF         [24]  190 	mov	_info_language_standard_default,#___str_3
      0000C3 75 12 01         [24]  191 	mov	(_info_language_standard_default + 1),#(___str_3 >> 8)
      0000C6 75 13 80         [24]  192 	mov	(_info_language_standard_default + 2),#0x80
                                    193 ;	CMakeCCompilerId.c:860: const char* info_language_extensions_default = "INFO" ":" "extensions_default["
      0000C9 75 14 09         [24]  194 	mov	_info_language_extensions_default,#___str_4
      0000CC 75 15 02         [24]  195 	mov	(_info_language_extensions_default + 1),#(___str_4 >> 8)
      0000CF 75 16 80         [24]  196 	mov	(_info_language_extensions_default + 2),#0x80
                                    197 	.area GSFINAL (CODE)
      0000D2 02 00 49         [24]  198 	ljmp	__sdcc_program_startup
                                    199 ;--------------------------------------------------------
                                    200 ; Home
                                    201 ;--------------------------------------------------------
                                    202 	.area HOME    (CODE)
                                    203 	.area HOME    (CODE)
      000049                        204 __sdcc_program_startup:
      000049 02 00 D5         [24]  205 	ljmp	_main
                                    206 ;	return from main will return to caller
                                    207 ;--------------------------------------------------------
                                    208 ; code
                                    209 ;--------------------------------------------------------
                                    210 	.area CSEG    (CODE)
                                    211 ;------------------------------------------------------------
                                    212 ;Allocation info for local variables in function 'main'
                                    213 ;------------------------------------------------------------
                                    214 ;argv          Allocated with name '_main_PARM_2'
                                    215 ;argc          Allocated to registers r6 r7 
                                    216 ;require       Allocated to registers r4 r3 
                                    217 ;------------------------------------------------------------
                                    218 ;	CMakeCCompilerId.c:878: int main(int argc, char* argv[])
                                    219 ;	-----------------------------------------
                                    220 ;	 function main
                                    221 ;	-----------------------------------------
      0000D5                        222 _main:
                           000007   223 	ar7 = 0x07
                           000006   224 	ar6 = 0x06
                           000005   225 	ar5 = 0x05
                           000004   226 	ar4 = 0x04
                           000003   227 	ar3 = 0x03
                           000002   228 	ar2 = 0x02
                           000001   229 	ar1 = 0x01
                           000000   230 	ar0 = 0x00
      0000D5 AE 82            [24]  231 	mov	r6, dpl
      0000D7 AF 83            [24]  232 	mov	r7, dph
                                    233 ;	CMakeCCompilerId.c:882: require += info_compiler[argc];
      0000D9 EE               [12]  234 	mov	a,r6
      0000DA 25 08            [12]  235 	add	a, _info_compiler
      0000DC FB               [12]  236 	mov	r3,a
      0000DD EF               [12]  237 	mov	a,r7
      0000DE 35 09            [12]  238 	addc	a, (_info_compiler + 1)
      0000E0 FC               [12]  239 	mov	r4,a
      0000E1 AD 0A            [24]  240 	mov	r5,(_info_compiler + 2)
      0000E3 8B 82            [24]  241 	mov	dpl,r3
      0000E5 8C 83            [24]  242 	mov	dph,r4
      0000E7 8D F0            [24]  243 	mov	b,r5
      0000E9 12 01 6D         [24]  244 	lcall	__gptrget
      0000EC FB               [12]  245 	mov	r3,a
      0000ED 7D 00            [12]  246 	mov	r5,#0x00
                                    247 ;	CMakeCCompilerId.c:883: require += info_platform[argc];
      0000EF EE               [12]  248 	mov	a,r6
      0000F0 25 0B            [12]  249 	add	a, _info_platform
      0000F2 F9               [12]  250 	mov	r1,a
      0000F3 EF               [12]  251 	mov	a,r7
      0000F4 35 0C            [12]  252 	addc	a, (_info_platform + 1)
      0000F6 FA               [12]  253 	mov	r2,a
      0000F7 AC 0D            [24]  254 	mov	r4,(_info_platform + 2)
      0000F9 89 82            [24]  255 	mov	dpl,r1
      0000FB 8A 83            [24]  256 	mov	dph,r2
      0000FD 8C F0            [24]  257 	mov	b,r4
      0000FF 12 01 6D         [24]  258 	lcall	__gptrget
      000102 7C 00            [12]  259 	mov	r4,#0x00
      000104 2B               [12]  260 	add	a, r3
      000105 F9               [12]  261 	mov	r1,a
      000106 EC               [12]  262 	mov	a,r4
      000107 3D               [12]  263 	addc	a, r5
      000108 FC               [12]  264 	mov	r4,a
                                    265 ;	CMakeCCompilerId.c:884: require += info_arch[argc];
      000109 EE               [12]  266 	mov	a,r6
      00010A 25 0E            [12]  267 	add	a, _info_arch
      00010C FA               [12]  268 	mov	r2,a
      00010D EF               [12]  269 	mov	a,r7
      00010E 35 0F            [12]  270 	addc	a, (_info_arch + 1)
      000110 FB               [12]  271 	mov	r3,a
      000111 AD 10            [24]  272 	mov	r5,(_info_arch + 2)
      000113 8A 82            [24]  273 	mov	dpl,r2
      000115 8B 83            [24]  274 	mov	dph,r3
      000117 8D F0            [24]  275 	mov	b,r5
      000119 12 01 6D         [24]  276 	lcall	__gptrget
      00011C 7D 00            [12]  277 	mov	r5,#0x00
      00011E 29               [12]  278 	add	a, r1
      00011F FA               [12]  279 	mov	r2,a
      000120 ED               [12]  280 	mov	a,r5
      000121 3C               [12]  281 	addc	a, r4
      000122 FD               [12]  282 	mov	r5,a
                                    283 ;	CMakeCCompilerId.c:886: require += info_version[argc];
      000123 EE               [12]  284 	mov	a,r6
      000124 24 8D            [12]  285 	add	a, #_info_version
      000126 F5 82            [12]  286 	mov	dpl,a
      000128 EF               [12]  287 	mov	a,r7
      000129 34 01            [12]  288 	addc	a, #(_info_version >> 8)
      00012B F5 83            [12]  289 	mov	dph,a
      00012D E4               [12]  290 	clr	a
      00012E 93               [24]  291 	movc	a,@a+dptr
      00012F 7B 00            [12]  292 	mov	r3,#0x00
      000131 2A               [12]  293 	add	a, r2
      000132 FC               [12]  294 	mov	r4,a
      000133 EB               [12]  295 	mov	a,r3
      000134 3D               [12]  296 	addc	a, r5
      000135 FB               [12]  297 	mov	r3,a
                                    298 ;	CMakeCCompilerId.c:900: require += info_language_standard_default[argc];
      000136 EE               [12]  299 	mov	a,r6
      000137 25 11            [12]  300 	add	a, _info_language_standard_default
      000139 F9               [12]  301 	mov	r1,a
      00013A EF               [12]  302 	mov	a,r7
      00013B 35 12            [12]  303 	addc	a, (_info_language_standard_default + 1)
      00013D FA               [12]  304 	mov	r2,a
      00013E AD 13            [24]  305 	mov	r5,(_info_language_standard_default + 2)
      000140 89 82            [24]  306 	mov	dpl,r1
      000142 8A 83            [24]  307 	mov	dph,r2
      000144 8D F0            [24]  308 	mov	b,r5
      000146 12 01 6D         [24]  309 	lcall	__gptrget
      000149 7D 00            [12]  310 	mov	r5,#0x00
      00014B 2C               [12]  311 	add	a, r4
      00014C FC               [12]  312 	mov	r4,a
      00014D ED               [12]  313 	mov	a,r5
      00014E 3B               [12]  314 	addc	a, r3
      00014F FB               [12]  315 	mov	r3,a
                                    316 ;	CMakeCCompilerId.c:901: require += info_language_extensions_default[argc];
      000150 EE               [12]  317 	mov	a,r6
      000151 25 14            [12]  318 	add	a, _info_language_extensions_default
      000153 FE               [12]  319 	mov	r6,a
      000154 EF               [12]  320 	mov	a,r7
      000155 35 15            [12]  321 	addc	a, (_info_language_extensions_default + 1)
      000157 FF               [12]  322 	mov	r7,a
      000158 AD 16            [24]  323 	mov	r5,(_info_language_extensions_default + 2)
      00015A 8E 82            [24]  324 	mov	dpl,r6
      00015C 8F 83            [24]  325 	mov	dph,r7
      00015E 8D F0            [24]  326 	mov	b,r5
      000160 12 01 6D         [24]  327 	lcall	__gptrget
      000163 7F 00            [12]  328 	mov	r7,#0x00
      000165 2C               [12]  329 	add	a, r4
      000166 F5 82            [12]  330 	mov	dpl,a
      000168 EF               [12]  331 	mov	a,r7
      000169 3B               [12]  332 	addc	a, r3
      00016A F5 83            [12]  333 	mov	dph,a
                                    334 ;	CMakeCCompilerId.c:903: return require;
                                    335 ;	CMakeCCompilerId.c:904: }
      00016C 22               [24]  336 	ret
                                    337 	.area CSEG    (CODE)
                                    338 	.area CONST   (CODE)
                                    339 	.area CONST   (CODE)
      00018D                        340 _info_version:
      00018D 49                     341 	.db #0x49	; 73	'I'
      00018E 4E                     342 	.db #0x4e	; 78	'N'
      00018F 46                     343 	.db #0x46	; 70	'F'
      000190 4F                     344 	.db #0x4f	; 79	'O'
      000191 3A                     345 	.db #0x3a	; 58
      000192 63                     346 	.db #0x63	; 99	'c'
      000193 6F                     347 	.db #0x6f	; 111	'o'
      000194 6D                     348 	.db #0x6d	; 109	'm'
      000195 70                     349 	.db #0x70	; 112	'p'
      000196 69                     350 	.db #0x69	; 105	'i'
      000197 6C                     351 	.db #0x6c	; 108	'l'
      000198 65                     352 	.db #0x65	; 101	'e'
      000199 72                     353 	.db #0x72	; 114	'r'
      00019A 5F                     354 	.db #0x5f	; 95
      00019B 76                     355 	.db #0x76	; 118	'v'
      00019C 65                     356 	.db #0x65	; 101	'e'
      00019D 72                     357 	.db #0x72	; 114	'r'
      00019E 73                     358 	.db #0x73	; 115	's'
      00019F 69                     359 	.db #0x69	; 105	'i'
      0001A0 6F                     360 	.db #0x6f	; 111	'o'
      0001A1 6E                     361 	.db #0x6e	; 110	'n'
      0001A2 5B                     362 	.db #0x5b	; 91
      0001A3 30                     363 	.db #0x30	; 48	'0'
      0001A4 30                     364 	.db #0x30	; 48	'0'
      0001A5 30                     365 	.db #0x30	; 48	'0'
      0001A6 30                     366 	.db #0x30	; 48	'0'
      0001A7 30                     367 	.db #0x30	; 48	'0'
      0001A8 30                     368 	.db #0x30	; 48	'0'
      0001A9 30                     369 	.db #0x30	; 48	'0'
      0001AA 34                     370 	.db #0x34	; 52	'4'
      0001AB 2E                     371 	.db #0x2e	; 46
      0001AC 30                     372 	.db #0x30	; 48	'0'
      0001AD 30                     373 	.db #0x30	; 48	'0'
      0001AE 30                     374 	.db #0x30	; 48	'0'
      0001AF 30                     375 	.db #0x30	; 48	'0'
      0001B0 30                     376 	.db #0x30	; 48	'0'
      0001B1 30                     377 	.db #0x30	; 48	'0'
      0001B2 30                     378 	.db #0x30	; 48	'0'
      0001B3 35                     379 	.db #0x35	; 53	'5'
      0001B4 2E                     380 	.db #0x2e	; 46
      0001B5 30                     381 	.db #0x30	; 48	'0'
      0001B6 30                     382 	.db #0x30	; 48	'0'
      0001B7 30                     383 	.db #0x30	; 48	'0'
      0001B8 30                     384 	.db #0x30	; 48	'0'
      0001B9 30                     385 	.db #0x30	; 48	'0'
      0001BA 30                     386 	.db #0x30	; 48	'0'
      0001BB 30                     387 	.db #0x30	; 48	'0'
      0001BC 30                     388 	.db #0x30	; 48	'0'
      0001BD 5D                     389 	.db #0x5d	; 93
      0001BE 00                     390 	.db #0x00	; 0
                                    391 	.area CSEG    (CODE)
                                    392 	.area CONST   (CODE)
      0001BF                        393 ___str_0:
      0001BF 49 4E 46 4F 3A 63 6F   394 	.ascii "INFO:compiler[SDCC]"
             6D 70 69 6C 65 72 5B
             53 44 43 43 5D
      0001D2 00                     395 	.db 0x00
                                    396 	.area CSEG    (CODE)
                                    397 	.area CONST   (CODE)
      0001D3                        398 ___str_1:
      0001D3 49 4E 46 4F 3A 70 6C   399 	.ascii "INFO:platform[]"
             61 74 66 6F 72 6D 5B
             5D
      0001E2 00                     400 	.db 0x00
                                    401 	.area CSEG    (CODE)
                                    402 	.area CONST   (CODE)
      0001E3                        403 ___str_2:
      0001E3 49 4E 46 4F 3A 61 72   404 	.ascii "INFO:arch[]"
             63 68 5B 5D
      0001EE 00                     405 	.db 0x00
                                    406 	.area CSEG    (CODE)
                                    407 	.area CONST   (CODE)
      0001EF                        408 ___str_3:
      0001EF 49 4E 46 4F 3A 73 74   409 	.ascii "INFO:standard_default[11]"
             61 6E 64 61 72 64 5F
             64 65 66 61 75 6C 74
             5B 31 31 5D
      000208 00                     410 	.db 0x00
                                    411 	.area CSEG    (CODE)
                                    412 	.area CONST   (CODE)
      000209                        413 ___str_4:
      000209 49 4E 46 4F 3A 65 78   414 	.ascii "INFO:extensions_default[OFF]"
             74 65 6E 73 69 6F 6E
             73 5F 64 65 66 61 75
             6C 74 5B 4F 46 46 5D
      000225 00                     415 	.db 0x00
                                    416 	.area CSEG    (CODE)
                                    417 	.area XINIT   (CODE)
                                    418 	.area CABS    (ABS,CODE)
