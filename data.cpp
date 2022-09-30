#include "data.hpp"
double version = 0.2;
const string weaponList[68] = {
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
	"Bow",
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
	"*Shotgun",
	"Lunchbox*",
	"Laser Pointer",
	"SMG",
	"Jar-Based Karate",
	"Shield*",
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
	"Sword",
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
		"Cleaver",
		"Lunchbox*", //scout specific lunchbox (drink)
		"Non-Milk Substance",
		"Bat",
		"Fish",
		"Severed Arm",
		"Sword",
		"RIFT Fire Mace",
		"Gunbai",
		"Placeholder"
	},/*Soldier*/{
		"Rocket Launcher",
		"Battle Banner",
		"Boots", 
		"Parachute",
		"Shovel",
		"Pickaxe",
		"Katana",
		"Riding Crop",
		"Placeholder"
	},/*Pyro*/{
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
	},/*Demoman*/{
		"Grenade Launcher",
		"Boots*",
		"Parachute*",
		"Stickybomb Launcher",
		"Shield",
		"Sword*",
		"Bottle",
		"Golf Club",
		"Caber Grenade",
		"Placeholder"
	},/*Heavy*/{
		"Minigun",
		"*Shotgun" //heavy specific shotgun b/c why not
		"Lunchbox", //heavy specific lunchbox
		"Fists",
		"Boxing Gloves",
		"Mittens",
		"Placeholder"
	},/*Engineer*/{
		"Shotgun*",
		"Pistol",
		"Laser Pointer",
		"Wrench",
		"Robot Arm",
		"Construction PDA",
		"Destruction PDA"
		"Placeholder"
	},/*Sniper*/{
		"Sniper Rifle",
		"Bow",
		"Sheild*",
		"SMG",
		"Jar",
		"Backpack",
		"Kukri",
		"Placeholder"
	},/*Medic*/{
		"Syringe Gun",
		"Crossbow",
		"Medigun",
		"Bonesaw",
		"Statue Head",
		"Placeholder"
	},/*Spy*/{
		"Revolver",
		"Sapper",
		"Knife",
		"Disguise Kit",
		"Invis Watch"
		"Placeholder"
	},/*Multiclass*/{
		"Shotgun", //shotgun for soldier, pyro, heavy, & engie
		//"Shot*gun", // shotgun for soldier & pyro
		"Pistol",
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
const string wearables[7] = {
	"Boots",
	"Parachute",
	"Battle Banner",
	"Jetpack",
	"Shield",
	"Backpack",
	"Placeholder"
};
const double wearBoost[6] = {
	15,
	35,
	15,
	10,
	75,
	15
};
const string alreadyBad[4] = {
	"*Shotgun",
	"Syringe Gun",
	"Gas Canister",
	"Placeholder"
};
const double howBad[3] = {
	5,
	5.5,
	10
};
const string projectileBased[13] = {
	"Flame Thrower",
	"Flame Launcher",
	"Syringe Gun",
	"Crossbow",
	"Cleaver",
	"Non-Milk Substance",
	"Gas Canister",
	"Jar-Based Karate",
	"Rocket Launcher",
	"Grenade Launcher",
	"Stickybomb Launcher",
	"Flare Gun",
	"Placeholder"
};
const string meterWeapons[14] = {
	"Cleaver",
	"Lunchbox*",
	"Non-Milk Substance",
	"Battle Banner",
	"Jetpack",
	"Gas Canister",
	"Stickybomb Launcher",
	"Shield",
	"Lunchbox",
	"Sniper Rifle",
	"Jar-Based Karate",
	"Backpack",
	"Medigun",
	"Invis Watch"
};
const string meterNames[14] = {
	"Cleaver",
	"Drink",
	"Jar",
	"Rage",
	"Jetpack",
	"Gas",
	"charge",
	"Charge",
	"Food",
	"charge",
	"Jar",
	"recharge",
	"ÜberCharge",
	"cloak"
}; 
const string moreMeterNames[4] = { //exsisting names that arent exclusive to a weapon type (Soda Popper is a scattergun with hype; not all scatterguns have a meter though)
	"Hype",
	"Boost",
	"Jar",
	"Focus"
}; 
const string cliplessWeapons[9] = {
	"Flamethrower",
	"Minigun",
	"Sniper Rifle",
	"Cleaver",
	"Flare Gun",
	"Laser Pointer",
	"Medigun",
	"Sapper",
	"Placeholder"
};
const string rapidFireWeapons[8] = {
	"Flame Thrower",
	"Minigun",
	"Syringe Gun",
	"Pistol",
	"SMG",
	"Medigun",
	"Sapper",
	"Placeholder"
};
const string primaryLike[5] {
	"Stickybomb Launcher",
	"*Shotgun",
	"Medigun",
	"Wrench",
	"Knife"
};
const string secondaryLike[4] {
	"Shotgun*",
	"Syringe Gun",
	"Crossbow",
	"Revolver"
};