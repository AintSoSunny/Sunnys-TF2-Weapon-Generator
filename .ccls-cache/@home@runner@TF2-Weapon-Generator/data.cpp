#include "data.hpp"
double version = 0.2;
int subVersion = 2; //0.2.2
string versionFull = to_string(version) + "." + to_string(subVersion);
string lineBreak(string ref, bool firstNL, bool secNL) {
	string lb;
	if (firstNL == true) {
		lb += "\n";
	}
	lb += ">";
	for (int i = 0; i < ref.length() - 2; i++) {
		lb += "=";
	}
	lb += "<";
	if (secNL == true) {
		lb += "\n";
	}
	return lb;
};
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
const string classWeapons[10][14] = { //note: placeholder is redundant because an unassigned element in an array will still be indexable / returnable and can be used as a reference. (This isn't storage effecient but the alternative method would be tedious)
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
		"Gunbai"
	},/*Soldier*/{
		"Rocket Launcher",
		"Battle Banner",
		"Boots", 
		"Parachute",
		"Shovel",
		"Pickaxe",
		"Katana",
		"Riding Crop"
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
		"RIFT Fire Axe"
	},/*Demoman*/{
		"Grenade Launcher",
		"Boots*",
		"Parachute*",
		"Stickybomb Launcher",
		"Shield",
		"Sword*",
		"Bottle",
		"Golf Club",
		"Caber Grenade"
	},/*Heavy*/{
		"Minigun",
		"*Shotgun" //heavy specific shotgun b/c why not
		"Lunchbox", //heavy specific lunchbox
		"Fists",
		"Boxing Gloves",
		"Mittens"
	},/*Engineer*/{
		"Shotgun*",
		"Pistol",
		"Laser Pointer",
		"Wrench",
		"Robot Arm",
		"Construction PDA",
		"Destruction PDA"
	},/*Sniper*/{
		"Sniper Rifle",
		"Bow",
		"Shield*",
		"SMG",
		"Jar-Based Karate",
		"Backpack",
		"Kukri"
	},/*Medic*/{
		"Syringe Gun",
		"Crossbow",
		"Medigun",
		"Bonesaw",
		"Statue Head"
	},/*Spy*/{
		"Revolver",
		"Sapper",
		"Knife",
		"Disguise Kit",
		"Invis Watch"
	},/*Multiclass*/{
		"Shotgun", //shotgun for soldier, pyro, heavy, & engie
		//"Shot*gun", // shotgun for soldier & pyro
		"Pistol"
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
	"Backpack"
};
const double wearBoost[6] = {
	35,
	45,
	50,
	10,
	75,
	25
};
const string alreadyBad[4] = {
	"*Shotgun",
	"Syringe Gun",
	"Gas Canister"
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
	"Flare Gun"
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
	"Medigun",
	"Invis Watch"
};
const string meterNames[14] = { //exsisting names for weapon types
	"Cleaver",
	"Drink",
	"Jar",
	"Rage",
	"Jetpack",
	"Gas",
	"charge",
	"charge",
	"Food",
	"charge",
	"Jar",
	"ÜberCharge",
	"cloak",
	"recharge"
}; 
const string classMeterNames[9][3] = { //meter names that aren't weapon-type specific (will be used for added meters)
	/*Scout*/{"Hype", "Boost"},
	/*Soldier*/{"Rage"},
	/*Pyro*/{"Mmph"},
	/*Demo*/{"Scrumpy"}, //custom, reason obvious.	
	/*Heavy*/{"Rage"}, //from mvm
	/*Engi*/{"God"}, //also custom; reference to god complex... maybe too obscure? Do ppl know about that?	
	/*Medic*/{"Herzinfall"}, /*or 'Herzinfarkt' german for heart attack.. I think? I looked it up, so it might be wrong...
I could also use Kardiotomie which means cardiomoty, or an incision in the heart, but I kinda think heart attack is clever... and it sounds cool so idk*/
	/*Sniper*/{"Focus", "Crikey"},
	/*Spy*/{"cloak"} //should not be accessable lol
}; 
const string altFireWeapons[14] = {
	"Flame Thrower",
	"Flame Launcher",
	"Minigun",
	"Sniper Rifle",
	"Bow",
	"Stickybomb Launcher",
	"Shield",
	"Lunchbox",
	"Laser Pointer",
	"Medigun",
	"Fists",
	"Boxing Gloves",
	"Mittens"
};
const string cliplessWeapons[9] = {
	"Flamethrower",
	"Minigun",
	"Sniper Rifle",
	"Cleaver",
	"Flare Gun",
	"Laser Pointer",
	"Medigun",
	"Sapper"
};
const string rapidFireWeapons[8] = {
	"Flame Thrower",
	"Minigun",
	"Syringe Gun",
	"Pistol",
	"SMG",
	"Medigun",
	"Sapper"
};
const string primaryLike[6] {
	"Stickybomb Launcher",
	"*Shotgun",
	"Medigun",
	"Wrench",
	"Knife"
};
const string secondaryLike[5] {
	"Shotgun",
	"Syringe Gun",
	"Crossbow",
	"Revolver"
};
const string throwableWeapons[7] { //first 3 are coatables; throwable also means consumable; basically something you don't always have;
	"Non-Milk Substance",
	"Gas Canister",
	"Jar-Based Karate",
	"Cleaver",
	"Lunchbox",
	"Lunchbox*"
};

const string ammoTypes[10] {
	"pellet",
	"rocket",
	"fire cloud",
	"grenade",
	"cannonball",
	"arrow",
	"syringe",
	"flare",
	"stickybomb",
	"bullet"
};
const string weaponAmmoGroups[9][5] {
	/*pellet*/{"Scattergun", "Peppergun", "Shotgun"},
	/*rocket*/{"Rocket Launcher"},
	/*fire cloud*/{"Flame Launcher"},
	/*grenade*/{"Grenade Launcher"},
	/*arrow*/{"Bow"},
	/*syringe*/{"Syringe Gun", "Crossbow"},
	/*flare*/{"Flare Gun"},
	/*stickybomb*/{"Stickybomb Launcher"} 
};