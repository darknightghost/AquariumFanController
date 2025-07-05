                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ISO C Compiler
                                      3 ; Version 4.5.0 #15242 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module platform
                                      6 	
                                      7 	.optsdcc -mmcs51 --model-small
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _EA
                                     12 	.globl _ELVD
                                     13 	.globl _EADC
                                     14 	.globl _ES
                                     15 	.globl _ET1
                                     16 	.globl _EX1
                                     17 	.globl _ET0
                                     18 	.globl _EX0
                                     19 	.globl _P7_7
                                     20 	.globl _P7_6
                                     21 	.globl _P7_5
                                     22 	.globl _P7_4
                                     23 	.globl _P7_3
                                     24 	.globl _P7_2
                                     25 	.globl _P7_1
                                     26 	.globl _P7_0
                                     27 	.globl _P6_7
                                     28 	.globl _P6_6
                                     29 	.globl _P6_5
                                     30 	.globl _P6_4
                                     31 	.globl _P6_3
                                     32 	.globl _P6_2
                                     33 	.globl _P6_1
                                     34 	.globl _P6_0
                                     35 	.globl _P5_5
                                     36 	.globl _P5_4
                                     37 	.globl _P5_3
                                     38 	.globl _P5_2
                                     39 	.globl _P5_1
                                     40 	.globl _P5_0
                                     41 	.globl _P4_7
                                     42 	.globl _P4_6
                                     43 	.globl _P4_5
                                     44 	.globl _P4_4
                                     45 	.globl _P4_3
                                     46 	.globl _P4_2
                                     47 	.globl _P4_1
                                     48 	.globl _P4_0
                                     49 	.globl _P3_7
                                     50 	.globl _P3_6
                                     51 	.globl _P3_5
                                     52 	.globl _P3_4
                                     53 	.globl _P3_3
                                     54 	.globl _P3_2
                                     55 	.globl _P3_1
                                     56 	.globl _P3_0
                                     57 	.globl _P2_7
                                     58 	.globl _P2_6
                                     59 	.globl _P2_5
                                     60 	.globl _P2_4
                                     61 	.globl _P2_3
                                     62 	.globl _P2_2
                                     63 	.globl _P2_1
                                     64 	.globl _P2_0
                                     65 	.globl _P1_7
                                     66 	.globl _P1_6
                                     67 	.globl _P1_5
                                     68 	.globl _P1_4
                                     69 	.globl _P1_3
                                     70 	.globl _P1_2
                                     71 	.globl _P1_1
                                     72 	.globl _P1_0
                                     73 	.globl _P0_7
                                     74 	.globl _P0_6
                                     75 	.globl _P0_5
                                     76 	.globl _P0_4
                                     77 	.globl _P0_3
                                     78 	.globl _P0_2
                                     79 	.globl _P0_1
                                     80 	.globl _P0_0
                                     81 	.globl _IAP_TPS
                                     82 	.globl _IAP_CONTR
                                     83 	.globl _IAP_TRIG
                                     84 	.globl _IAP_CMD
                                     85 	.globl _IAP_ADDRL
                                     86 	.globl _IAP_ADDRH
                                     87 	.globl _IAP_DATA
                                     88 	.globl _IP3H
                                     89 	.globl _IP3
                                     90 	.globl _IP2H
                                     91 	.globl _IP2
                                     92 	.globl _IPH
                                     93 	.globl _IP
                                     94 	.globl _INTCLKO
                                     95 	.globl _IE2
                                     96 	.globl _IE
                                     97 	.globl _AUXR
                                     98 	.globl _TH1
                                     99 	.globl _TH0
                                    100 	.globl _TL1
                                    101 	.globl _TL0
                                    102 	.globl _TMOD
                                    103 	.globl _TCON
                                    104 	.globl _PCON
                                    105 	.globl _SBUF
                                    106 	.globl _SCON
                                    107 	.globl _P7M0
                                    108 	.globl _P7M1
                                    109 	.globl _P7
                                    110 	.globl _P6M0
                                    111 	.globl _P6M1
                                    112 	.globl _P6
                                    113 	.globl _P5M0
                                    114 	.globl _P5M1
                                    115 	.globl _P5
                                    116 	.globl _P4M0
                                    117 	.globl _P4M1
                                    118 	.globl _P4
                                    119 	.globl _P3M0
                                    120 	.globl _P3M1
                                    121 	.globl _P3
                                    122 	.globl _P2M0
                                    123 	.globl _P2M1
                                    124 	.globl _P2
                                    125 	.globl _P1M0
                                    126 	.globl _P1M1
                                    127 	.globl _P1
                                    128 	.globl _P0M0
                                    129 	.globl _P0M1
                                    130 	.globl _P0
                                    131 	.globl _platform_init
                                    132 ;--------------------------------------------------------
                                    133 ; special function registers
                                    134 ;--------------------------------------------------------
                                    135 	.area RSEG    (ABS,DATA)
      000000                        136 	.org 0x0000
                           000080   137 _P0	=	0x0080
                           000093   138 _P0M1	=	0x0093
                           000094   139 _P0M0	=	0x0094
                           000090   140 _P1	=	0x0090
                           000091   141 _P1M1	=	0x0091
                           000092   142 _P1M0	=	0x0092
                           0000A0   143 _P2	=	0x00a0
                           000095   144 _P2M1	=	0x0095
                           000096   145 _P2M0	=	0x0096
                           0000B0   146 _P3	=	0x00b0
                           0000B1   147 _P3M1	=	0x00b1
                           0000B2   148 _P3M0	=	0x00b2
                           0000C0   149 _P4	=	0x00c0
                           0000B3   150 _P4M1	=	0x00b3
                           0000B4   151 _P4M0	=	0x00b4
                           0000C8   152 _P5	=	0x00c8
                           0000C9   153 _P5M1	=	0x00c9
                           0000CA   154 _P5M0	=	0x00ca
                           0000E8   155 _P6	=	0x00e8
                           0000CB   156 _P6M1	=	0x00cb
                           0000CC   157 _P6M0	=	0x00cc
                           0000F8   158 _P7	=	0x00f8
                           0000E1   159 _P7M1	=	0x00e1
                           0000E2   160 _P7M0	=	0x00e2
                           000098   161 _SCON	=	0x0098
                           000099   162 _SBUF	=	0x0099
                           000087   163 _PCON	=	0x0087
                           000088   164 _TCON	=	0x0088
                           000089   165 _TMOD	=	0x0089
                           00008A   166 _TL0	=	0x008a
                           00008B   167 _TL1	=	0x008b
                           00008C   168 _TH0	=	0x008c
                           00008D   169 _TH1	=	0x008d
                           00008E   170 _AUXR	=	0x008e
                           0000A8   171 _IE	=	0x00a8
                           0000AF   172 _IE2	=	0x00af
                           00008F   173 _INTCLKO	=	0x008f
                           0000B8   174 _IP	=	0x00b8
                           0000B7   175 _IPH	=	0x00b7
                           0000B5   176 _IP2	=	0x00b5
                           0000B6   177 _IP2H	=	0x00b6
                           0000DF   178 _IP3	=	0x00df
                           0000EE   179 _IP3H	=	0x00ee
                           0000C2   180 _IAP_DATA	=	0x00c2
                           0000C3   181 _IAP_ADDRH	=	0x00c3
                           0000C4   182 _IAP_ADDRL	=	0x00c4
                           0000C5   183 _IAP_CMD	=	0x00c5
                           0000C6   184 _IAP_TRIG	=	0x00c6
                           0000C7   185 _IAP_CONTR	=	0x00c7
                           0000F5   186 _IAP_TPS	=	0x00f5
                                    187 ;--------------------------------------------------------
                                    188 ; special function bits
                                    189 ;--------------------------------------------------------
                                    190 	.area RSEG    (ABS,DATA)
      000000                        191 	.org 0x0000
                           000080   192 _P0_0	=	0x0080
                           000081   193 _P0_1	=	0x0081
                           000082   194 _P0_2	=	0x0082
                           000083   195 _P0_3	=	0x0083
                           000084   196 _P0_4	=	0x0084
                           000085   197 _P0_5	=	0x0085
                           000086   198 _P0_6	=	0x0086
                           000087   199 _P0_7	=	0x0087
                           000090   200 _P1_0	=	0x0090
                           000091   201 _P1_1	=	0x0091
                           000092   202 _P1_2	=	0x0092
                           000093   203 _P1_3	=	0x0093
                           000094   204 _P1_4	=	0x0094
                           000095   205 _P1_5	=	0x0095
                           000096   206 _P1_6	=	0x0096
                           000097   207 _P1_7	=	0x0097
                           0000A0   208 _P2_0	=	0x00a0
                           0000A1   209 _P2_1	=	0x00a1
                           0000A2   210 _P2_2	=	0x00a2
                           0000A3   211 _P2_3	=	0x00a3
                           0000A4   212 _P2_4	=	0x00a4
                           0000A5   213 _P2_5	=	0x00a5
                           0000A6   214 _P2_6	=	0x00a6
                           0000A7   215 _P2_7	=	0x00a7
                           0000B0   216 _P3_0	=	0x00b0
                           0000B1   217 _P3_1	=	0x00b1
                           0000B2   218 _P3_2	=	0x00b2
                           0000B3   219 _P3_3	=	0x00b3
                           0000B4   220 _P3_4	=	0x00b4
                           0000B5   221 _P3_5	=	0x00b5
                           0000B6   222 _P3_6	=	0x00b6
                           0000B7   223 _P3_7	=	0x00b7
                           0000C0   224 _P4_0	=	0x00c0
                           0000C1   225 _P4_1	=	0x00c1
                           0000C2   226 _P4_2	=	0x00c2
                           0000C3   227 _P4_3	=	0x00c3
                           0000C4   228 _P4_4	=	0x00c4
                           0000C5   229 _P4_5	=	0x00c5
                           0000C6   230 _P4_6	=	0x00c6
                           0000C7   231 _P4_7	=	0x00c7
                           0000C8   232 _P5_0	=	0x00c8
                           0000C9   233 _P5_1	=	0x00c9
                           0000CA   234 _P5_2	=	0x00ca
                           0000CB   235 _P5_3	=	0x00cb
                           0000CC   236 _P5_4	=	0x00cc
                           0000CD   237 _P5_5	=	0x00cd
                           0000E8   238 _P6_0	=	0x00e8
                           0000E9   239 _P6_1	=	0x00e9
                           0000EA   240 _P6_2	=	0x00ea
                           0000EB   241 _P6_3	=	0x00eb
                           0000EC   242 _P6_4	=	0x00ec
                           0000ED   243 _P6_5	=	0x00ed
                           0000EE   244 _P6_6	=	0x00ee
                           0000EF   245 _P6_7	=	0x00ef
                           0000F8   246 _P7_0	=	0x00f8
                           0000F9   247 _P7_1	=	0x00f9
                           0000FA   248 _P7_2	=	0x00fa
                           0000FB   249 _P7_3	=	0x00fb
                           0000FC   250 _P7_4	=	0x00fc
                           0000FD   251 _P7_5	=	0x00fd
                           0000FE   252 _P7_6	=	0x00fe
                           0000FF   253 _P7_7	=	0x00ff
                           0000A8   254 _EX0	=	0x00a8
                           0000A9   255 _ET0	=	0x00a9
                           0000AA   256 _EX1	=	0x00aa
                           0000AB   257 _ET1	=	0x00ab
                           0000AC   258 _ES	=	0x00ac
                           0000AD   259 _EADC	=	0x00ad
                           0000AE   260 _ELVD	=	0x00ae
                           0000AF   261 _EA	=	0x00af
                                    262 ;--------------------------------------------------------
                                    263 ; overlayable register banks
                                    264 ;--------------------------------------------------------
                                    265 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                        266 	.ds 8
                                    267 ;--------------------------------------------------------
                                    268 ; internal ram data
                                    269 ;--------------------------------------------------------
                                    270 	.area DSEG    (DATA)
                                    271 ;--------------------------------------------------------
                                    272 ; overlayable items in internal ram
                                    273 ;--------------------------------------------------------
                                    274 ;--------------------------------------------------------
                                    275 ; indirectly addressable internal ram data
                                    276 ;--------------------------------------------------------
                                    277 	.area ISEG    (DATA)
                                    278 ;--------------------------------------------------------
                                    279 ; absolute internal ram data
                                    280 ;--------------------------------------------------------
                                    281 	.area IABS    (ABS,DATA)
                                    282 	.area IABS    (ABS,DATA)
                                    283 ;--------------------------------------------------------
                                    284 ; bit data
                                    285 ;--------------------------------------------------------
                                    286 	.area BSEG    (BIT)
                                    287 ;--------------------------------------------------------
                                    288 ; paged external ram data
                                    289 ;--------------------------------------------------------
                                    290 	.area PSEG    (PAG,XDATA)
                                    291 ;--------------------------------------------------------
                                    292 ; uninitialized external ram data
                                    293 ;--------------------------------------------------------
                                    294 	.area XSEG    (XDATA)
                                    295 ;--------------------------------------------------------
                                    296 ; absolute external ram data
                                    297 ;--------------------------------------------------------
                                    298 	.area XABS    (ABS,XDATA)
                                    299 ;--------------------------------------------------------
                                    300 ; initialized external ram data
                                    301 ;--------------------------------------------------------
                                    302 	.area XISEG   (XDATA)
                                    303 	.area HOME    (CODE)
                                    304 	.area GSINIT0 (CODE)
                                    305 	.area GSINIT1 (CODE)
                                    306 	.area GSINIT2 (CODE)
                                    307 	.area GSINIT3 (CODE)
                                    308 	.area GSINIT4 (CODE)
                                    309 	.area GSINIT5 (CODE)
                                    310 	.area GSINIT  (CODE)
                                    311 	.area GSFINAL (CODE)
                                    312 	.area CSEG    (CODE)
                                    313 ;--------------------------------------------------------
                                    314 ; global & static initialisations
                                    315 ;--------------------------------------------------------
                                    316 	.area HOME    (CODE)
                                    317 	.area GSINIT  (CODE)
                                    318 	.area GSFINAL (CODE)
                                    319 	.area GSINIT  (CODE)
                                    320 ;--------------------------------------------------------
                                    321 ; Home
                                    322 ;--------------------------------------------------------
                                    323 	.area HOME    (CODE)
                                    324 	.area HOME    (CODE)
                                    325 ;--------------------------------------------------------
                                    326 ; code
                                    327 ;--------------------------------------------------------
                                    328 	.area CSEG    (CODE)
                                    329 ;------------------------------------------------------------
                                    330 ;Allocation info for local variables in function 'platform_init'
                                    331 ;------------------------------------------------------------
                                    332 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:6: void platform_init()
                                    333 ;	-----------------------------------------
                                    334 ;	 function platform_init
                                    335 ;	-----------------------------------------
      0000AD                        336 _platform_init:
                           000007   337 	ar7 = 0x07
                           000006   338 	ar6 = 0x06
                           000005   339 	ar5 = 0x05
                           000004   340 	ar4 = 0x04
                           000003   341 	ar3 = 0x03
                           000002   342 	ar2 = 0x02
                           000001   343 	ar1 = 0x01
                           000000   344 	ar0 = 0x00
                                    345 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:9: EA = 0;
                                    346 ;	assignBit
      0000AD C2 AF            [12]  347 	clr	_EA
                                    348 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:12: P0M0 = 0;
      0000AF 75 94 00         [24]  349 	mov	_P0M0,#0x00
                                    350 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:13: P0M1 = 0xFF;
      0000B2 75 93 FF         [24]  351 	mov	_P0M1,#0xff
                                    352 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:14: P1M0 = 0;
      0000B5 75 92 00         [24]  353 	mov	_P1M0,#0x00
                                    354 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:15: P1M1 = 0xFF;
      0000B8 75 91 FF         [24]  355 	mov	_P1M1,#0xff
                                    356 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:16: P2M0 = 0;
      0000BB 75 96 00         [24]  357 	mov	_P2M0,#0x00
                                    358 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:17: P2M1 = 0xFF;
      0000BE 75 95 FF         [24]  359 	mov	_P2M1,#0xff
                                    360 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:18: P3M0 = 0;
      0000C1 75 B2 00         [24]  361 	mov	_P3M0,#0x00
                                    362 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:19: P3M1 = 0xFF;
      0000C4 75 B1 FF         [24]  363 	mov	_P3M1,#0xff
                                    364 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:20: P4M0 = 0;
      0000C7 75 B4 00         [24]  365 	mov	_P4M0,#0x00
                                    366 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:21: P4M1 = 0xFF;
      0000CA 75 B3 FF         [24]  367 	mov	_P4M1,#0xff
                                    368 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:22: P5M0 = 0;
      0000CD 75 CA 00         [24]  369 	mov	_P5M0,#0x00
                                    370 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:23: P5M1 = 0xFF;
      0000D0 75 C9 FF         [24]  371 	mov	_P5M1,#0xff
                                    372 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:24: P6M0 = 0;
      0000D3 75 CC 00         [24]  373 	mov	_P6M0,#0x00
                                    374 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:25: P6M1 = 0xFF;
      0000D6 75 CB FF         [24]  375 	mov	_P6M1,#0xff
                                    376 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:26: P7M0 = 0;
      0000D9 75 E2 00         [24]  377 	mov	_P7M0,#0x00
                                    378 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:27: P7M1 = 0xFF;
      0000DC 75 E1 FF         [24]  379 	mov	_P7M1,#0xff
                                    380 ;	/home/darknightghost/projects/AquariumFanController/firmware/source/platform.c:30: }
      0000DF 22               [24]  381 	ret
                                    382 	.area CSEG    (CODE)
                                    383 	.area CONST   (CODE)
                                    384 	.area XINIT   (CODE)
                                    385 	.area CABS    (ABS,CODE)
