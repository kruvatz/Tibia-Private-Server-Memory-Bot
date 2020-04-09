#include "stdafx.h"
#include "Character.h"

using namespace std;

namespace class_offsets {

	DWORD CMainGui = 0x7B00D4;
	std::vector<unsigned int> BattleList_offsets{ 0x1C, 0x0 };
	DWORD Creature_List_StaticAddr = 0x76A0B0;
	DWORD Map_ptr_StaticAddr = 0x7B02D8;
	DWORD Backpack = 0x7B63DC;
	std::vector<unsigned int> Backpack_offsets{ 0x28, 0x14, 0x4C, 0x4 };
	std::vector<unsigned int> Backpack__check_offsets{ 0x28, 0x14, 0x0 };
}

namespace Offsets
{
	namespace cLocalPlayer   // xd
	{
		DWORD xor_key_offs = 0x570458;
		DWORD cur_MP_offs = 0x57048C;
		DWORD max_MP_offs = 0x57045C;
		DWORD exp_offs = 0x570460;
		DWORD level_offs = 0x570470;
		DWORD target_mob_offs = 0x570488;

		DWORD cur_HP_offs = 0x70E000;
		DWORD max_HP_offs = 0x70E048;

		DWORD player_id = 0x70E050;
		DWORD x_coord_offs = 0x70E054;
		DWORD y_coord_offs = 0x70E058;
		DWORD z_coord_offs = 0x70E05C;

	}

	DWORD
		Talk_Offset = 0x206C0,
		Move_Offset = 0x181140,

		packet_edit_command_type = 0x1B5C10,
		packet_edit_one_byte = 0x1B5FD0,
		packet_edit_two_bytes = 0x1B6180,
		packet_edit_four_bytes = 0x1B6330, 
		packet_edit_crypt_and_send = 0x1B6B10,

		Ekrana_yazdir_Offset = 0x214540;



}


Character::Character(DWORD modulebase)
{
	this->modulebase = modulebase;
	this->name = (char *)(modulebase + 0x76A500);
	this->battle_list = (BattleList*) mem::FindDMAAddy(modulebase + class_offsets::CMainGui, class_offsets::BattleList_offsets);

	this->Creature_list_ptr = (Creature * )(modulebase + class_offsets::Creature_List_StaticAddr);
	this->map = (Map)(*(DWORD *)(modulebase + class_offsets::Map_ptr_StaticAddr));

	// packet edit and send functions************************************************************************
	this->edit_TYPE = (_packet_edit_command_type)(this->modulebase + Offsets::packet_edit_command_type);
	this->edit_BYTE = (_packet_edit_one_byte)(this->modulebase + Offsets::packet_edit_one_byte);
	this->edit_WORD = (_packet_edit_two_bytes)(this->modulebase + Offsets::packet_edit_two_bytes);
	this->edit_DWORD = (_packet_edit_four_bytes)(this->modulebase + Offsets::packet_edit_four_bytes);
	this->crypt_and_send = (_packet_edit_crypt_and_send)(this->modulebase + Offsets::packet_edit_crypt_and_send);
	//*******************************************************************************************************

	AllocConsole();
	this->debug_console = new FILE;
	freopen_s(&debug_console, "CONOUT$", "w", stdout);

}

Character::~Character()
{
	fclose(this->debug_console);
	FreeConsole();
}

void Character::Talk(const char * buffer,bool npc_chat,bool normal_chat)
{
	_talk Chat = (_talk)(this->modulebase + Offsets::Talk_Offset);
	if (normal_chat) Chat(1, buffer);
	else if (npc_chat) Chat(4, buffer);
}

void Character::Ekrana_Yaz(const char * buffer)
{
	_ekrana_Yazdir yaz = (_ekrana_Yazdir)(this->modulebase + Offsets::Ekrana_yazdir_Offset);

	yaz(buffer);
}

void Character::Move(int Yon)
{
	_move Move_direction = (_move)(this->modulebase + Offsets::Move_Offset);

	switch(Yon)
	{
	case 4:
		Move_direction(1, 1, 1); // sag alt
		break;

	case 0:
		Move_direction(0xFFFFFFFF, 0xFFFFFFFF, 1); // sol-ust
		break;

	case 2:

		Move_direction(1, 0xFFFFFFFF, 1); // sag-ust
		break;

	case 6:

		Move_direction(0xFFFFFFFF, 1, 1); // sol-alt
		break;

	case 5:

		Move_direction(0, 1, 0);// aþaðý
		break;

	case 3:

		Move_direction(1, 0, 0);// saða
		break;

	case 1:

		Move_direction(0, 0xFFFFFFFF, 0);// yukarý
		break;

	case 7:

		Move_direction(0xFFFFFFFF, 0, 0);// sola
		break;
	default:
		break;
		

	}


}

void Character::Attack(DWORD enemy_ptr) {

	if (!mob_legit(enemy_ptr)) return; // NULLdan kaçýn kaçýn

	edit_TYPE(0xA1);//Attack Packet
	edit_DWORD(enemy_ptr);  // Target
	edit_DWORD(0x23);  // Mystery, maybe # of attacks so far. Server doesn't check it.
	crypt_and_send(1);  // 1 for ready




}


char * Character::get_nickname() {
	return this->name;
}




void Character::Follow(DWORD obj_ptr) {

	if (!mob_legit(obj_ptr)) return; // NULLdan kaçýn kaçýn

	edit_TYPE(0xA2);//Attack Packet
	edit_DWORD(obj_ptr);  // Target
	edit_DWORD(0x23);  // Mystery, maybe # of attacks so far. Server doesn't check it.
	crypt_and_send(1);  // 1 for ready




}

int Character::get_cMP() {
	DWORD md = this->modulebase;
	return *(DWORD *)(md + Offsets::cLocalPlayer::xor_key_offs) ^ *(DWORD *)(md + Offsets::cLocalPlayer::cur_MP_offs);
}

int Character::get_mMP() {
	DWORD md = this->modulebase;
	return *(DWORD *)(md + Offsets::cLocalPlayer::xor_key_offs) ^ *(DWORD *)(md + Offsets::cLocalPlayer::max_MP_offs);
}

int Character::get_cHP() {
	DWORD md = this->modulebase;
	return *(DWORD *)(md + Offsets::cLocalPlayer::xor_key_offs) ^ *(DWORD *)(md + Offsets::cLocalPlayer::cur_HP_offs);
}

int Character::get_mHP() {
	DWORD md = this->modulebase;
	return *(DWORD *)(md + Offsets::cLocalPlayer::xor_key_offs) ^ *(DWORD *)(md + Offsets::cLocalPlayer::max_HP_offs);
}

int Character::get_exp() {
	return  *(DWORD *)(this->modulebase + Offsets::cLocalPlayer::exp_offs);
}

DWORD Character::get_player_id() {

	return *(DWORD *)(this->modulebase + Offsets::cLocalPlayer::player_id);
}

int Character::get_x_coord() {
	return  *(DWORD *)(this->modulebase + Offsets::cLocalPlayer::x_coord_offs);
}

int Character::get_y_coord() {
	return  *(DWORD *)(this->modulebase + Offsets::cLocalPlayer::y_coord_offs);
}

int Character::get_z_coord() {
	return  *(DWORD *)(this->modulebase + Offsets::cLocalPlayer::z_coord_offs);
}


bool Character::mob_legit(DWORD c_id) {

	return c_id > 0x1000FFFF && c_id < 0x4FFFFFFF;

}

DWORD Character::get_closest_Mob_ID() {

	int player_x = get_x_coord();
	int player_y = get_y_coord();
	int player_z = get_z_coord();

	DWORD tmp_id = NULL;
	int tmp_x = 9999;
	int tmp_y = 9999;
	char * name = NULL;
	DWORD dbg_addr = NULL;

	Creature * list = this->Creature_list_ptr;

	for (int i = 0; list[i].Creature_id; i++) {  // öklid uzaklýk, listeden en kýsa uzaklýðý olaný çekiyoruz, lineer algo 

		//std::cout << std::hex << list[i].Creature_id   << "  creature address baslangic: " << list + i << std::endl;

		// if (list[i].Creature_id == 0xBAADF00D) break;  //// heap degil

		if (!mob_legit(list[i].Creature_id)) continue;
		if (!list[i].is_Alive) continue;
		if (player_z != list[i].z_coord) continue; // z koordinatlarý eþit mi

		if ((pow(tmp_x, 2) + pow(tmp_y, 2)) > (pow(list[i].x_coord, 2) + pow(list[i].y_coord, 2))) {

			tmp_x = list[i].x_coord;
			tmp_y = list[i].y_coord;
			tmp_id = list[i].Creature_id;
			name = list[i].name;
			dbg_addr = (DWORD)(list + i);
		}


	}

//
//	if (!tmp_id) std::cout << "Saldirilacak mob bulunamadi " << std::endl;
//	else {
//		std::cout << "Saldiriliyor: " << name << "  " << std::hex << tmp_id << endl << "creature address baslangic: " << dbg_addr << std::endl;
//
//		cout << "player x: " << std::dec << player_x << endl << "player y: "<<std::dec << player_y << endl;
//}


	return tmp_id;

}

void Character::look_coord(int x, int y , int z) {

	DWORD f1 = this->modulebase + 0xB23C0;
	DWORD f2 = this->modulebase + Offsets::packet_edit_command_type;
	DWORD f3 = this->modulebase + Offsets::packet_edit_two_bytes;
	DWORD f4 = this->modulebase + Offsets::packet_edit_one_byte;
	DWORD f5 = this->modulebase + Offsets::packet_edit_crypt_and_send;

	_asm {

		call f1
		mov ecx, 0x82     // look packet
		call f2
		mov ecx, x  // x coord
		call f3 
		mov ecx, y   // y coord
		call f3
		mov ecx, z   //  z coord 
		call f4 
		mov ecx,  0xF93   // sprite id , her look için sprite id vermektense sabit verelim, server nasýl tepki veriyor bakalým
		call f3 
		mov ecx, 0x2   // layer index gibime geldi :)  buradan hata gelebilir
		call f4 
		mov ecx, 0 // envanter açýk mý? is inventory open
		call f4 
		mov cl, 1			// ready flag
		call f5


	}


}

void Character::open_backpack() {


	DWORD f1 = this->modulebase + 0xB23C0;
	DWORD f2 = this->modulebase + Offsets::packet_edit_command_type;
	DWORD f3 = this->modulebase + Offsets::packet_edit_two_bytes;
	DWORD f4 = this->modulebase + Offsets::packet_edit_one_byte;
	DWORD f5 = this->modulebase + Offsets::packet_edit_crypt_and_send;

	_asm {

		mov ecx, 0x82     // look packet
		call f2
		mov ecx, 0xFFFF
		call f3
		mov ecx, 0
		call f3
		mov ecx, 0
		call f4
		mov ecx, 0xB26   // item, sprite ... id , her backpack farklýdýr. dikkat 
		call f3
		mov ecx, 0   // layer index?
		call f4
		mov ecx, 0
		call f4
		mov cl, 1			// ready flag
		call f5


	}


}

DWORD Character::get_backpack_addr() { // deprecated
	open_backpack();
	return mem::FindDMAAddy(this->modulebase + class_offsets::Backpack, class_offsets::Backpack_offsets);


}

bool Character::is_backpack_open() { // deprecated

	DWORD addr = mem::FindDMAAddy(this->modulebase + class_offsets::Backpack, class_offsets::Backpack__check_offsets);

	return (  addr < 0x50000000  &&  addr > 0x700000);  // shitty way to check...

}

void Character::use_hp_pot() {  // not directly sends packet

	DWORD player_id = *(DWORD *)(this->modulebase + Offsets::cLocalPlayer::player_id);
	DWORD f1 = this->modulebase + 0x1F660;
	DWORD restore_edx;

	_asm {
		push player_id
		push 0
		push 0x10A
		push 0
		mov restore_edx, edx
		xor edx, edx
		mov ecx, 0xFFFF
		call f1
		mov edx, restore_edx


	}


}

void Character::use_consumable_by_id(WORD item_id) {

		edit_TYPE(0x82);
		edit_WORD(0xFFFF);
		edit_WORD(0);
		edit_BYTE(0);
		edit_WORD(item_id);
		edit_BYTE(0);
		edit_BYTE(0);
		crypt_and_send(1);


	

}
void Character::use_mp_pot() {

	DWORD player_id = get_player_id();
	DWORD f1 = this->modulebase + 0x1F660;
	DWORD restore_edx;

	_asm {
		push dword ptr ds : [player_id]
		push 0
		push 0x10C
		push 0
		mov restore_edx, edx
		xor edx, edx
		mov ecx, 0xFFFF
		call f1
		mov edx, restore_edx


	}


}

void Character::use_hp_pot_packet_send() {  // server won't allow

	DWORD f1 = this->modulebase + 0xB23C0;
	std::cout << hex << get_player_id();
	_asm {
		call f1
	}

	edit_TYPE(0x84);
	edit_WORD(0);
	edit_WORD(0xFFFF);
	edit_BYTE(0);
	edit_WORD(0x10A);  // pot id
	edit_BYTE(0);
	edit_DWORD(get_player_id());
	crypt_and_send(1);



}

void Character::use_mp_pot_packet_send() {



	DWORD f1 = this->modulebase + 0xB23C0;

	_asm {
		call f1
	}

	edit_TYPE(0x84);
	edit_WORD(0);
	edit_WORD(0xFFFF);
	edit_BYTE(0);
	edit_WORD(0x10C);  // pot id
	edit_BYTE(0);
	edit_DWORD(get_player_id());
	crypt_and_send(1);




}

void Character::sell_item(BYTE amount, WORD item_id) {

	edit_TYPE(0x7B);  // Command Type
	edit_WORD(item_id);  // Item Id
	edit_BYTE(0);  // ???
	edit_BYTE(amount);  // amount to sell
	edit_BYTE(1);  // checks if npc is focused us (?)
	crypt_and_send(1);  /* read flag 1*/

}


void Character::debug_print_creatures() {


	Creature * list = this->Creature_list_ptr;

	std::cout <<"sizeof class: " << sizeof(Creature) << std::endl;

	for (int i = 0; list[i].Creature_id ; i++) {


		cout <<"_________________\n" <<"name: " << list[i].name <<endl << "Address: "<< list + i  << endl;
		cout << "is alive: " << list[i].is_Alive << endl;



	}


}


void Character::debug_print_map() {


	MapCell * list = this->map;

	std::cout << "\n\nsizeof class: " << sizeof(MapCell) << std::endl;

	for (int y = 0; y < 24; y++) {

		cout << endl;

		for (int x = 0; x < 32; x++) {



			std::cout << hex <<list[x + y*24].Layer_array[0].sprite_id<< " " ;


		}



	}


}


void Character::debug_print_backpack() {     // deprecated

	open_backpack();
	Backpack_Item_Struct * list = (Backpack_Item_Struct *)get_backpack_addr();
	
	int i = 0;
	do {
		cout << "item id: " << hex << list[i].item_id << "miktar: " << dec << list[i].amount << endl;


		i++;
	} while (list[i].item_id != 0xBAADF00D || list[i].item_id != NULL);
}