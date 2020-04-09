#pragma once

#include "GClasses.h"
#include <math.h>
#include "mem.h"
#include <iostream>

typedef void(__fastcall* _talk)(int type, const char * buffer);
typedef void(__stdcall* _move)(int a1, int a2, int a3);

typedef void(__fastcall* _packet_edit_command_type)(DWORD packet_id);
typedef void(__fastcall* _packet_edit_one_byte)(BYTE arg);
typedef void(__fastcall* _packet_edit_two_bytes)(WORD arg);
typedef void(__fastcall* _packet_edit_four_bytes)(DWORD arg);
typedef void(__fastcall* _packet_edit_crypt_and_send)(BYTE ready);

typedef void(__fastcall* Command_F2)(int obj_ptr_or_counter);
typedef void(_fastcall* _ekrana_Yazdir)(const char * buffer);


class Character
{
private:
	FILE* debug_console;


	char * name;
	DWORD modulebase;
	BattleList * battle_list;
	Creature * Creature_list_ptr;
	Map map;


	_packet_edit_command_type edit_TYPE;
	_packet_edit_one_byte edit_BYTE;
	_packet_edit_two_bytes edit_WORD;
	_packet_edit_four_bytes edit_DWORD;
	_packet_edit_crypt_and_send crypt_and_send;
	 

public:
	Character(DWORD );
	~Character();


	void Talk(const char * , bool npc_chat, bool normal_chat );
	void Move(int );
	void Attack(DWORD );
	void Follow(DWORD );
	void Ekrana_Yaz(const char *);


	int get_mHP();
	int get_mMP();

	int get_cHP();
	int get_cMP();

	int get_exp();

	DWORD get_player_id();
	int get_x_coord();
	int get_y_coord();
	int get_z_coord();


	void look_coord(int x,int y, int z);
	void open_backpack();
	bool is_backpack_open();
	DWORD get_backpack_addr();
	void use_hp_pot_packet_send();
	void use_mp_pot_packet_send();

	void use_hp_pot();
	void use_mp_pot();
	void use_consumable_by_id(WORD item_id);

	void sell_item(BYTE amount,WORD item_id);

	bool mob_legit(DWORD);
	DWORD get_closest_Mob_ID();

	char * get_nickname();

	void debug_print_creatures();
	void debug_print_map();
	void debug_print_backpack();
};