#include "data.hpp"
double version = 0.2;
int subVersion = 9; 
string betaTag = "a1"; //0.2.9a1
string versionFull = to_string(version) + "." + to_string(subVersion) + betaTag;
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
int isInputSetInt(int c) {
	return (isdigit(c) || c == ',' || c == '-'); 
};
int isInputSingleInt(int c) {
	return (isdigit(c) || c == '-');
};
int isInputSetWords(int c) {
	return (isalpha(c) || ispunct(c) || c == ' '); //space only no tabs
};
const array<string,69> weaponList = {
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
	"Sword*",
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
	"Knife",
	"Invis Watch"
};
const array<string,10> classList = {
	"Scout", //0
	"Soldier", //1
	"Pyro", //2
	"Demoman", //3
	"Heavy", //4
	"Engineer", //5
	"Medic", //6
	"Sniper", //7
	"Spy", //8
	"Multi" //9
};
const array<array<string,14>,10> classWeapons = {{ //note: placeholder is redundant because an unassigned element in an array will still be indexable / returnable and can be used as a reference. (This isn't storage effecient but the alternative method would be tedious)
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
		"*Shotgun", //heavy specific shotgun b/c why not
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
	},/*Medic*/{
		"Syringe Gun",
		"Crossbow",
		"Medigun",
		"Bonesaw",
		"Statue Head"
	},/*Sniper*/{
		"Sniper Rifle",
		"Bow",
		"Shield*",
		"SMG",
		"Jar-Based Karate",
		"Backpack",
		"Kukri"
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
}};
const array<string,5> weaponSlots = {
	"primary",
	"secondary", 
	"melee",
	"PDA1"/*,
	"PDA2"
	PDA2 unused for now*/
};

const array<double,5> weaponSlotMods = {.95, .75, .45, .15};
const array<string,8> wearables = {
	"Boots",
	"Parachute",
	"Battle Banner",
	"Jetpack",
	"Shield",
	"Backpack",
	"Invis Watch"
};
const array<double,7> wearBoost = {
	25,
	20,
	20,
	2.5,
	46,
	20,
	100
};
const array<string,4> alreadyBad = {
	"*Shotgun",
	"Syringe Gun",
	"Gas Canister"
};
const array<double,3> howBad = {
	5,
	5.5,
	10
};
const array<string,14> projectileBased = {
	"Flame Thrower",
	"Flame Launcher",
	"Syringe Gun",
	"Crossbow",
	"Bow",
	"Rocket Launcher",
	"Grenade Launcher",
	"Stickybomb Launcher",
	"Flare Gun"
};
const array<string,14> meterWeapons = {
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
const array<string,14> meterNames = { //exsisting names for weapon types
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
const array<array<string,3>,9> classMeterNames = {{ //meter names that aren't weapon-type specific (will be used for added meters)
	/*Scout*/{"Hype", "Boost"},
	/*Soldier*/{"Rage"},
	/*Pyro*/{"Mmph"},
	/*Demo*/{"Scrumpy"}, //custom, reason obvious.	
	/*Heavy*/{"Rage"}, //from mvm
	/*Engi*/{"Omnipotence"}, //also custom; reference to god complex and stuff idk... maybe too obscure? Do ppl know about that?	
	/*Medic*/{"Herzinfall"}, /*or 'Herzinfarkt' german for heart attack.. I think? I looked it up, so it might be wrong...
I could also use Kardiotomie which means cardiomoty, or an incision in the heart, but I kinda think heart attack is clever... and it sounds cool so idk*/
	/*Sniper*/{"Focus", "Crikey"},
	/*Spy*/{"Baugette"} //the medic meter name took alot out of me fuck off
}}; 
const array<string,14> altFireWeapons = {
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
const array<string,10> cliplessWeapons = {
	"Flame Thrower",
	"Flame Launcher",
	"Minigun",
	"Sniper Rifle",
	"Bow",
	"Cleaver",
	"Flare Gun",
	"Lunchbox",
	"Laser Pointer",
	"Medigun"
};
const array<string,8> rapidFireWeapons = {
	"Flame Thrower",
	"Minigun",
	"Syringe Gun",
	"Pistol",
	"SMG",
	"Medigun",
	"Sapper"
};
const array<string,8> primaryLike {
	"Stickybomb Launcher",
	"*Shotgun",
	"Shotgun*",
	"Medigun",
	"Sword*",
	"Wrench",
	"Knife"
};
const array<string,6> secondaryLike {
	"Grenade Launcher",
	"Shotgun",
	"Syringe Gun",
	"Crossbow",
	"Revolver"
};
const array<string,5> throwableWeapons { //first 3 are coatables; Battle Banner & Lunchbox are no longer considered throwable
	"Non-Milk Substance",
	"Gas Canister",
	"Jar-Based Karate",
	"Cleaver"
};
const array<string,9> ammoTypes {
	"pellet",
	"rocket",
	"fire cloud",
	"grenade",
	"arrow",
	"syringe",
	"flare",
	"stickybomb",
	"bullet"
};
const array<array<string,5>,9> weaponAmmoGroups {{
	/*pellet*/{"Scattergun", "Peppergun", "Shotgun"},
	/*rocket*/{"Rocket Launcher"},
	/*fire cloud*/{"Flame Launcher"},
	/*grenade*/{"Grenade Launcher"},
	/*arrow*/{"Bow"},
	/*syringe*/{"Syringe Gun", "Crossbow"},
	/*flare*/{"Flare Gun"},
	/*stickybomb*/{"Stickybomb Launcher"} 
}};