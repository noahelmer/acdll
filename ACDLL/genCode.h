#pragma once
#include "geom.h"

class Player {
public:
	void* vtable;
	Vector3 N00000053; //0x0004
	Vector3 velocity; //0x0010
	Vector3 N00000052; //0x001C
	Vector3 position; //0x0028
	float yaw; //0x0034
	float pitch; //0x0038
	float roll; //0x003C
	Vector3 recoil; //0x0040
	char pad_004C[160]; //0x004C
	int32_t health; //0x00EC
	char pad_00F0[60]; //0x00F0
	int32_t secondaryammo; //0x012C
	char pad_0130[12]; //0x0130
	uint32_t primaryammo; //0x013C
	char pad_0140[288]; //0x0140

}; //Size: 0x0260

class EntityList {
public:
	Player* players[64];
};