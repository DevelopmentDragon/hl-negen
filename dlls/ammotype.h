#pragma once

#include <vector>

// Weapon Info stuff
typedef std::vector<const char*> ammoType; // array of strings
typedef struct wi_e {
	int numClips;
	ammoType ammoTypes;
} ammoWeaponInfo;

typedef std::vector<ammoWeaponInfo> weaponInfo;

typedef std::vector<ammoType> ammoTypes; // array of arrays of strings


typedef std::vector<int> legalAmmoType; // array of ints
typedef std::vector<legalAmmoType> legalAmmoTypes; // array of arrays of ints

// This is the ammo register, all ammo types are declared and stored here
static ammoType ammoRegistery = {
	"9mm",
	"9mmI",
	"9mmE",
	"9mmIE",
	"9mmAP",
	"9mmAPI",
	"9mmAPE",
	"9amAPEI",
	"9mmHP",
	"9mmHPI",
	"9mmHPE",
	"9amHPIE",
	"40mm",
	"40mmHE",
	"40mmF",
	"40mmI",
	"40mmB",
	"40mmS",
	"40mmG",
	"40mm+",

	"ecells",
	"ocecells",
	"opecells",
	"pcells",
	"ocpcells",
	"oppcells"
};

int GetAmmoRegisterySize(void);

legalAmmoTypes GenerateLegalAmmoIndicies(weaponInfo wiInput);
int GetAmmoIndex(const char* psz);
int ValidAmmoIndex(int iAmmoIndex);