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

#pragma once

const int MAX_WEAPON_SLOTS = 5;		// hud item selection slots
const int MAX_ITEM_TYPES   = 6;		// hud item selection slots
const int MAX_WEAPONS      = 32;
const int MAX_AMMO_TYPES   = 32;	// ???
const int MAX_AMMO_SLOTS   = 32;	// not really slots
const int MAX_ITEMS        = 4;		// hard coded item types
const int DEFAULT_FOV      = 90;	// the default field of view

#define	DEFAULT_VIEWHEIGHT          17
#define DEFAULT_VIEWHEIGHT_DEAD     -8
#define DEFAULT_DUCKHEIGHT          12

#define HIDEHUD_WEAPONS             BIT(0)
#define HIDEHUD_FLASHLIGHT          BIT(1)
#define HIDEHUD_ALL                 BIT(2)
#define HIDEHUD_HEALTH              BIT(3)
#define HIDEHUD_TIMER               BIT(4)
#define HIDEHUD_MONEY               BIT(5)
#define HIDEHUD_CROSSHAIR           BIT(6)
#define HIDEHUD_OBSERVER_CROSSHAIR  BIT(7)

#define STATUSICON_HIDE  0
#define STATUSICON_SHOW  1
#define STATUSICON_FLASH 2

#define HUD_PRINTNOTIFY  1
#define HUD_PRINTCONSOLE 2
#define HUD_PRINTTALK    3
#define HUD_PRINTCENTER  4
#define HUD_PRINTRADIO   5

#define TEAM_UNASSIGNED  0
#define TEAM_TERRORIST   1
#define TEAM_CT          2
#define TEAM_SPECTATOR   3

#define STATUS_NIGHTVISION_ON  1
#define STATUS_NIGHTVISION_OFF 0

#define ITEM_STATUS_NIGHTVISION BIT(0)
#define ITEM_STATUS_DEFUSER     BIT(1)

#define SCORE_STATUS_DEAD       BIT(0)
#define SCORE_STATUS_BOMB       BIT(1)
#define SCORE_STATUS_VIP        BIT(2)
#define SCORE_STATUS_DEFKIT     BIT(3)

// player data iuser3
#define PLAYER_CAN_SHOOT        BIT(0)
#define PLAYER_FREEZE_TIME_OVER BIT(1)
#define PLAYER_IN_BOMB_ZONE     BIT(2)
#define PLAYER_HOLDING_SHIELD   BIT(3)
#define PLAYER_PREVENT_DUCK     BIT(4)
#define PLAYER_PREVENT_CLIMB    BIT(5) // The player can't climb ladder
#define PLAYER_PREVENT_JUMP     BIT(6)

#define MENU_KEY_1 BIT(0)
#define MENU_KEY_2 BIT(1)
#define MENU_KEY_3 BIT(2)
#define MENU_KEY_4 BIT(3)
#define MENU_KEY_5 BIT(4)
#define MENU_KEY_6 BIT(5)
#define MENU_KEY_7 BIT(6)
#define MENU_KEY_8 BIT(7)
#define MENU_KEY_9 BIT(8)
#define MENU_KEY_0 BIT(9)

#define CS_NUM_SKIN				   4
#define CZ_NUM_SKIN				   5

#define FIELD_ORIGIN0			   0
#define FIELD_ORIGIN1			   1
#define FIELD_ORIGIN2			   2

#define FIELD_ANGLES0			   3
#define FIELD_ANGLES1			   4
#define FIELD_ANGLES2			   5

#define CUSTOMFIELD_ORIGIN0		   0
#define CUSTOMFIELD_ORIGIN1		   1
#define CUSTOMFIELD_ORIGIN2		   2

#define CUSTOMFIELD_ANGLES0		   3
#define CUSTOMFIELD_ANGLES1		   4
#define CUSTOMFIELD_ANGLES2		   5

#define CUSTOMFIELD_SKIN		   6
#define CUSTOMFIELD_SEQUENCE	   7
#define CUSTOMFIELD_ANIMTIME	   8

#define HUD_PRINTNOTIFY            1
#define HUD_PRINTCONSOLE           2
#define HUD_PRINTTALK              3
#define HUD_PRINTCENTER            4

#define WEAPON_SUIT                31
#define WEAPON_ALLWEAPONS          (~(1<<WEAPON_SUIT))

#define ARMOR_NONE                 0 // No armor
#define ARMOR_VESTHELM             1 // Suit and helmet

// custom enum
enum ChooseTeamMenuSlot
{
	MENU_SLOT_TEAM_UNDEFINED = -1,

	MENU_SLOT_TEAM_TERRORIST = 1,
	MENU_SLOT_TEAM_CT,
	MENU_SLOT_TEAM_VIP,

	MENU_SLOT_TEAM_RANDOM = 5,
	MENU_SLOT_TEAM_SPECT
};

// custom enum
enum BuyItemMenuSlot
{
	MENU_SLOT_ITEM_VEST = 1,
	MENU_SLOT_ITEM_VESTHELM,
	MENU_SLOT_ITEM_FLASHGREN,
	MENU_SLOT_ITEM_HEGREN,
	MENU_SLOT_ITEM_SMOKEGREN,
	MENU_SLOT_ITEM_NVG,
	MENU_SLOT_ITEM_DEFUSEKIT,
	MENU_SLOT_ITEM_SHIELD,
};

// custom enum
enum VGUIMenu
{
	VGUI_Menu_Team = 2,
	VGUI_Menu_TFC_Class = 3,
	VGUI_Menu_MapBriefing = 4,
	VGUI_Menu_ServerInfo = 5,
	VGUI_Menu_TFC_ClassDesc = 6,
	VGUI_Menu_SpecHelp = 9,

	VGUI_Menu_Class_T = 26,
	VGUI_Menu_Class_CT,
	VGUI_Menu_Buy,
	VGUI_Menu_Buy_Pistol,
	VGUI_Menu_Buy_ShotGun,
	VGUI_Menu_Buy_Rifle,
	VGUI_Menu_Buy_SubMachineGun,
	VGUI_Menu_Buy_MachineGun,
	VGUI_Menu_Buy_Item,

	VGUI_Menu_CareerRoundEnd,
	VGUI_Menu_CareerMatchEnd,
	VGUI_Menu_Credits,
	VGUI_Menu_BuyPresetMain,
	VGUI_Menu_BuyPresetEdit,
};

// custom enum
enum VGUIMenuSlot
{
	VGUI_MenuSlot_Buy_Pistol = 1,
	VGUI_MenuSlot_Buy_ShotGun,
	VGUI_MenuSlot_Buy_SubMachineGun,
	VGUI_MenuSlot_Buy_Rifle,
	VGUI_MenuSlot_Buy_MachineGun,
	VGUI_MenuSlot_Buy_PrimAmmo,
	VGUI_MenuSlot_Buy_SecAmmo,
	VGUI_MenuSlot_Buy_Item,
};

enum TeamName
{
	UNASSIGNED,
	TERRORIST,
	CT,
	SPECTATOR,
};

typedef struct
{
	float m_fTimeEnteredPVS;

} ENTITYPVSSTATUS;

const int MAX_ENTITIES = 1380;
struct PLAYERPVSSTATUS
{
	ENTITYPVSSTATUS m_Status[MAX_ENTITIES];
	int headnode;
	int num_leafs;
	short int leafnums[MAX_ENT_LEAFS];
};

struct entity_field_alias_t
{
	char name[32];
	int field;
};
