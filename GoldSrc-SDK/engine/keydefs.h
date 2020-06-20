/*
*
*    Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*    This product contains software technology licensed from Id
*    Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*    All Rights Reserved.
*
*    Use, distribution, and modification of this source code and/or resulting
*    object code is restricted to non-commercial enhancements to products from
*    Valve LLC.  All other use, distribution, or modification is prohibited
*    without written permission from Valve LLC.
*
*/

#ifndef KEYDEFS_H
#define KEYDEFS_H
#ifdef _WIN32
#ifndef __MINGW32__
#pragma once
#endif // #ifndef __MINGW32__
#endif

#define K_UNKNOWN			0

//
// these are the key numbers that should be passed to Key_Event
//
#define K_TAB				9
#define K_ENTER				13
#define K_ESCAPE			27
#define K_SPACE				32

#define K_QUOTE				39
#define K_COMMA				44
#define K_MINUS				45
#define K_PERIOD			46
#define K_SLASH				47
#define K_0					48
#define K_1					49
#define K_2					50
#define K_3					51
#define K_4					52
#define K_5					53
#define K_6					54
#define K_7					55
#define K_8					56
#define K_9					57
#define K_SEMICOLON			59
#define K_EQUALS			61
#define K_A					65
#define K_B					66
#define K_C					67
#define K_D					68
#define K_E					69
#define K_F					70
#define K_G					71
#define K_H					72
#define K_I					73
#define K_J					74
#define K_K					75
#define K_L					76
#define K_M					77
#define K_N					78
#define K_O					79
#define K_P					80
#define K_Q					81
#define K_R					82
#define K_S					83
#define K_T					84
#define K_U					85
#define K_V					86
#define K_W					87
#define K_X					88
#define K_Y					89
#define K_Z					90
#define K_LEFTBRACKET		91
#define K_BACKSLASH			92
#define K_RIGHTBRACKET		93
#define K_BACKQUOTE			96
#define K_a					97
#define K_b					98
#define K_c					99
#define K_d					100
#define K_e					101
#define K_f					102
#define K_g					103
#define K_h					104
#define K_i					105
#define K_j					106
#define K_k					107
#define K_l					108
#define K_m					109
#define K_n					110
#define K_o					111
#define K_p					112
#define K_q					113
#define K_r					114
#define K_s					115
#define K_t					116
#define K_u					117
#define K_v					118
#define K_w					119
#define K_x					120
#define K_y					121
#define K_z					122

// normal keys should be passed as lowercased ascii

#define K_TILDE				126
#define K_BACKSPACE			127
#define K_UPARROW			128
#define K_DOWNARROW			129
#define K_LEFTARROW			130
#define K_RIGHTARROW		131

#define K_ALT				132
#define K_CTRL				133
#define K_SHIFT				134
#define K_F1				135
#define K_F2				136
#define K_F3				137
#define K_F4				138
#define K_F5				139
#define K_F6				140
#define K_F7				141
#define K_F8				142
#define K_F9				143
#define K_F10				144
#define K_F11				145
#define K_F12				146
#define K_INS				147
#define K_DEL				148
#define K_PGDN				149
#define K_PGUP				150
#define K_HOME				151
#define K_END				152

#define K_KP_HOME			160
#define K_KP_UPARROW		161
#define K_KP_PGUP			162
#define K_KP_LEFTARROW		163
#define K_KP_5				164
#define K_KP_RIGHTARROW		165
#define K_KP_END			166
#define K_KP_DOWNARROW		167
#define K_KP_PGDN			168
#define K_KP_ENTER			169
#define K_KP_INS   			170
#define K_KP_DEL			171
#define K_KP_SLASH			172
#define K_KP_MINUS			173
#define K_KP_PLUS			174
#define K_CAPSLOCK			175
#define K_KP_MULTIPLY		176
#define K_WIN				177

//
// joystick buttons
//
#define K_JOY1				203
#define K_JOY2				204
#define K_JOY3				205
#define K_JOY4				206

//
// aux keys are for multi-buttoned joysticks to generate so they can use
// the normal binding process
//
#define K_AUX1				207
#define K_AUX2				208
#define K_AUX3				209
#define K_AUX4				210
#define K_AUX5				211
#define K_AUX6				212
#define K_AUX7				213
#define K_AUX8				214
#define K_AUX9				215
#define K_AUX10				216
#define K_AUX11				217
#define K_AUX12				218
#define K_AUX13				219
#define K_AUX14				220
#define K_AUX15				221
#define K_AUX16				222
#define K_AUX17				223
#define K_AUX18				224
#define K_AUX19				225
#define K_AUX20				226
#define K_AUX21				227
#define K_AUX22				228
#define K_AUX23				229
#define K_AUX24				230
#define K_AUX25				231
#define K_AUX26				232
#define K_AUX27				233
#define K_AUX28				234
#define K_AUX29				235
#define K_AUX30				236
#define K_AUX31				237
#define K_AUX32				238
#define K_MWHEELDOWN		239
#define K_MWHEELUP			240

#define K_PAUSE				255

//
// mouse buttons generate virtual keys
//
#define K_MOUSE1			241
#define K_MOUSE2			242
#define K_MOUSE3			243
#define K_MOUSE4			244
#define K_MOUSE5			245

#define MAX_BINDING_KEYS	256

#endif // #ifndef KEYDEFS_H
