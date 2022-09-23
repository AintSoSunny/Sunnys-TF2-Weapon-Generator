#include "data.hpp"
double version = 0.1;
const string weaponList[63] = {
	"Scattergun",
	"Peppergun",
	"Rocket Launcher",
	"Flame Thrower",
	"Flame Launcher",
	"Grenade Launcher",
	"Boots*",
	"Parachute*",
	"Minigun",
	"Shotgun*",
	"Sniper Rifle",
	"Syringe Gun",
	"Crossbow",
	"Revolver",
	"Pistol",
	"Cleaver",
	"Lunchbox",
	"Non-Milk Substance",
	"Shotgun",
	"Battle Banner",
	"Boots", 
	"Parachute",
	"Flare Gun",
	"Jetpack",
	"Gas Canister",
	"Stickybomb Launcher",
	"Shield",
	"Laser Pointer",
	"SMG",
	"Jar-Based Karate",
	"Backpack",
	"Medigun",
	"Sapper",
	"Bat",
	"Fish",
	"Severed Arm",
	"Sword",
	"RIFT Fire Mace",
	"Gunbai",
	"Shovel",
	"Pickaxe",
	"Katana",
	"Riding Crop",
	"Fire Axe",
	"Mailbox",
	"Sledgehammer",
	"Car Battery",
	"Neon Sign",
	"Rubber Glove",
	"Rake",
	"RIFT Fire Axe",
	"Bottle",
	"Golf Club",
	"Caber Grenade",
	"Fists",
	"Boxing Gloves",
	"Mittens",
	"Wrench",
	"Robot Arm",
	"Kukri",
	"Bonesaw",
	"Statue Head",
	"Knife"
};
const string classList[10] = {
	"Scout",
	"Soldier",
	"Pyro",
	"Demoman",
	"Heavy",
	"Engineer",
	"Sniper",
	"Medic",
	"Spy",
	"Multi"
};
const string classWeapons[10][15] = {
	/*Scout*/{
		"Scattergun",
		"Peppergun",
		"Pistol",
		"Cleaver",
		"Lunchbox",
		"Non-Milk Substance",
		"Bat",
		"Fish",
		"Severed Arm",
		"Sword",
		"RIFT Fire Mace",
		"Gunbai",
		"Placeholder"
	},
	/*Soldier*/{
		"Rocket Launcher",
		"Battle Banner",
		"Boots", 
		"Parachute",
		"Shovel",
		"Pickaxe",
		"Katana",
		"Riding Crop",
		"Placeholder"
	},
	/*Pyro*/{
		"Flame Thrower",
		"Flame Launcher",
		"Flare Gun",
		"Jetpack",
		"Gas Canister",
		"Fire Axe",
		"Mailbox",
		"Sledgehammer",
		"Car Battery",
		"Neon Sign",
		"Rubber Glove",
		"Rake",
		"RIFT Fire Axe",
		"Placeholder"
	},
	/*Demoman*/{
		"Grenade Launcher",
		"Boots*",
		"Parachute*",
		"Stickybomb Launcher",
		"Shield",
		"Sword",
		"Bottle",
		"Golf Club",
		"Caber Grenade",
		"Placeholder"
	},
	/*Heavy*/{
		"Minigun",
		"*Shotgun" //heavy specific shotgun b/c why not
		"Lunchbox",
		"Fists",
		"Boxing Gloves",
		"Mittens",
		"Placeholder"
	},
	/*Engineer*/{
		"Shotgun*",
		"Pistol",
		"Laser Pointer",
		"Wrench",
		"Robot Arm",
		"Placeholder"
	},
	/*Sniper*/{
		"Sniper Rifle",
		"Sheild",
		"SMG",
		"Jar",
		"Backpack",
		"Kukri",
		"Placeholder"
	},
	/*Medic*/{
		"Syringe Gun",
		"Crossbow",
		"Medigun",
		"Bonesaw",
		"Statue Head",
		"Placeholder"
	},
	/*Spy*/{
		"Revolver",
		"Sapper",
		"Knife",
		"Placeholder"
	}
	/*Multiclass*/{
		"Shotgun", //shotgun for soldier, pyro, heavy, & engie
		//"Shot*gun", // shotgun for soldier & pyro
		"Placeholder"
	}
}; //need placeholder b/c of find
const string weaponSlots[5] = {
	"primary",
	"secondary", 
	"melee"/*,
	"PDA1",
	"PDA2"
	PDAs unused for now*/
};

const string wearables[4] = {
	"Boots",
	"Parachute",
	"Shield",
	"Backpack"
};
const double wearBoost[4] = {
	12.5,
	15,
	15,
	5
};
const string alreadyBad[3] = {
	"*Shotgun",
	"Syringe Gun",
	"Gas Canister"
};
const double howBad[3] = {
	5,
	5.5,
	10
};