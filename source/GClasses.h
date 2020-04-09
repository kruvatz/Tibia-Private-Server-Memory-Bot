#pragma once
#include <stdint.h>
#define Map MapCell *

class Layer
{
public:
	int32_t sprite_id; //0x0000
	char pad_0004[28]; //0x0004
}; //Size: 0x0020


class MapCell
{
public:
	int32_t layer_size; //0x0000
	int32_t unk0; //0x0004
	int32_t unk1; //0x0008
	int32_t unk2; //0x000C
	int32_t unk3; //0x0010
	int32_t unk4; //0x0014
	char pad_0018[28]; //0x0018
	class Layer Layer_array[9]; //0x0034
	char pad_0154[24]; //0x0154
	int32_t some_flag; //0x016C
}; //Size: 0x0170





class Creature
{
public:
	int32_t Creature_id; //0x0000
	char name[32]; 
	int32_t z_coord; //0x0024
	int32_t y_coord; //0x0028
	int32_t x_coord; //0x002C
	int32_t y_axis_sprite_state; //0x0030
	int32_t x_axis_sprite_state; //0x0034
	int32_t direction; //0x0038
	int32_t unk_increase_when_move; //0x003C
	int32_t unk2_increase_when_move; //0x0040
	int32_t is_looking_updownward; //0x0044
	int32_t is_looking_rightleft; //0x0048
	int32_t unk3_seems_constant; //0x004C
	int32_t is_moving; //0x0050
	int32_t direction_2nd; //0x0054
	int32_t minus_one; //0x0058
	int32_t positive_MAX; //0x005C
	char pad_0060[68]; //0x0060
	int32_t is_Alive; //0x00A4
	char pad_00A8[52]; //0x00A8

}; //Size: 0x00DC


class Mob_Instance
{
public:
	uint32_t Mob_ID; //0x0000
	int32_t x; //0x0004
	int32_t y; //0x0008
}; //Size: 0x000C


class BattleList
{
public:
	uint32_t unk0; //0x0000
	int32_t unk1; //0x0004
	int32_t unk2; //0x0008
	uint32_t ptr_derived_from; //0x000C
	uint32_t unk3; //0x0010
	uint32_t unk4; //0x0014
	uint32_t unk5; //0x0018
	uint32_t unk6; //0x001C
	uint32_t unk7; //0x0020
	uint32_t unk8; //0x0024
	uint32_t unk9; //0x0028
	uint32_t Size_of_Mob_Array; //0x002C
	Mob_Instance Mob_Instance_Array[32]; 
};


class Backpack_Item_Struct
{
public:
	int32_t amount; //0x0000
	int32_t item_id; //0x0004
	char pad_0008[12]; //0x0008
	int32_t not_allocated; //0x0014
	char pad_0018[8]; //0x0018
}; //Size: 0x0020



