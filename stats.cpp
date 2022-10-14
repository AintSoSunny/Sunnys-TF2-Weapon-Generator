#include "stats.hpp"
//this is messy but probably temporary >.>
int tempInt, mod, statCat, subStat, bannerBuffTypeIndex;
bool posNegSplit = false;
const int statCatNum[9] = {11,16,4,10,7,18,0,0,4};
const string damTypes[7] = {"bullet", "explosive", "fire", "critical", "ranged", "melee", "self"};
const double damTypeRatings[7] = {4, 3.25, 2.5, 1.25, 4.5, .75, 4};
const string critTypes[3] = {"critical hits", "mini-crits", "mini-crits and critical hits"};
const double critTypeRatings[3] = {190, 35, 200};
const string conditions[8] = {
	"players",
	"buildings",
	"burning players",
	"wet players",
	"targets launched airborne by explosions, grapple hooks or rocket packs",
	"slowed players",
	"bleeding players",
	"players who have also equipped this item"
};
const double conditionMods[8] = {.85, .15, .35, .25, .15, .05, .188, .125};
const string hitConditions[7] = {
	"Building",
	"Burning Player",
	"Wet Player",
	"Airborne Player",
	"Slowed Player",
	"Bleeding Player",
	"Teammate"
};
const double hitConditionMods[7] = {.15, .35, .25, .45, .05, .188, .125};
const string hitRewards[15] = {
	"gain a speed boost",
	"clip size increased (up to +$n*)",
	"heal $n% of base health",
	"$n health restored",
	"a $z health pack is dropped",
  "refills $n% of your $t meter",
	"$n* seconds of $r",
	"apply $e for $n* seconds",
	"one target at a time is Marked-For-Death, causing all damage taken to be mini-crits",
	"gain up to +$n* health",
	"target is engulfed in flames",
	"100% chance to slow target",
	"damage dealt is returned as ammo",
	"victim loses up to $n*% $t* charge",
	"next shot fires $n*% faster"
};
const double hitRewardRatings[15] = {2.5, 7.5, 3.75, 3.625, 145, 2.25, 0.75, 1.75, 1.75, 1.5, 5, 3.5, 35, 20, 2.5};
const string penalties[1] = {
	"Hit yourself. Idiot.",
};
const string altFire[5] = {
  "Launches a ball that $es opponents",
  "Launches a festive ornament that shatters causing bleed", //it'd be stupid if it didnt cause bleed
  "A charged shot that mini-crits players, sets them on fire and disables buildings for 4 sec",
  "Launches a projectile-consuming energy ball.",
	"Reach and shove someone!"
  //"Charge toward your enemies and remove debuffs. Gain a critical melee strike after impacting an enemy.", // idk if this should be for all weapons so...

};
const double altFireRatings[5] = {1, 35, 75, 100, 10};
const double penaltyRatings[1] = {50};
const string wearerConditions[7] = {
	"when fired at their back from close range",
	"while health >50% of max",
	"while health <50% of max"
};
const double wearerConditionMods[7] = {.75, .65, .35};
const string classSpWearerConditions[9][3] = {
	/*Scout*/{
	"while airborne"
	},/*Soldier*/{
	"while blast jumping"
	},/*Pyro*/{
	"while flare jumping"
	},/*Demoman*/{
	"while blast jumping"
	},/*Heavy*/{
	"while spun up & below 50% health"
	},/*Engineer*/{
	"to your sentry's target"
	},/*Medic*/{
	"while ÜberCharged"
	},/*Sniper*/{
	"while scoped",
	"while fully charged",
	"while not fully charged"
	},/*Spy*/{
	"while disguised",
	"while cloaked"}
};
const double classSpWearerConditionMods[9][3] = {
	/*Scout*/{1},
	/*Soldier*/{1},
	/*Pyro*/{1},
	/*Demoman*/{1},
	/*Heavy*/{1},
	/*Engineer*/{1},
	/*Medic*/{1},
	/*Sniper*/{1,1,1},
	/*Spy*/{1,1}
};
const string statTypes[10] = {
	"damage",
	"movement speed",
	"firing speed",
	"reload speed",
	"accuracy",
	"critical hit chance",
	"deploy speed",
	"holster speed",
	"health from healers & packs",
	"ammmo from boxes & dispensers"
};
const double statTypeRatings[10] = {4.75, 1.75, 4.25, 3.25, 1.875, 3, 1.125, .55, 12.5, 9.5};
const string posNegStringPair[10][2] = {
	{"",""},
	{"bonus", "penalty"},
	{"resistance", "vulnerability"},
	{"crits whenever it would normally mini-crit", "mini-crits whenever it would normally crit"},
	{"more", "less"},
	{"regenerated", "drained"},
	{"faster", "slower"},
	{"increase", "decrease"},
	{"increase", "reduction"},
	{"explode", "shatter"}
};
const string posNegSign[3] = {"+", "-", ""};
const string HPContainerTypes[4] = {"healers", "packs", "Medic sources", "dispensers"};
const double HPContainerTypeMods[4] = {.85, .15, .35, .40};
const string ammoContainerTypes[2]  = {"ammo boxes", "dispensers"};
const double ammoContainerTypeMods[2]  = {.85, .15};
const string sizes[3] = {"small", "medium", "large"};
const double sizeMods[3] = {.35, .5, 1};
const double meterMods[14] = {0.05, 0.125, 0.5, 0.75, 0.25, 0.063, 0.25, 0.5, 0.35, 0.25, 0.5, 0.85, 0.95, 0.8}; 
const string debuffs[8] = {
	"afterburn",
	"stun",
	"slow",
	"wet",
	"bleed",
	"incoming $r*",
  "mark"
};
const double debuffRatings[8] = {25, 150, 10, 1, 35, 0, 15};
const double debuffMods[8] = {0.85, 0.05, 0.35, 0.063, 0.5, 0.5};
const string coatEffects[4] = { //will make more soon? idk
	"Players heal 60% of the damage done to coated enemies",
	"Applies $e to coated enemies"
	"Coated enemies take $r",
	"Coated enemies take increased afterburn and afterburn ignores immunities"
};
const double coatRatings[4] = {50, 1, 1, 10};
const string bannerBuffTypes[4] = {" special", "n offensive", " defensive", " movement"};
const string meterBuildMethods[13] = {
	"with damage dealt",
	"with damage recieved",
	"with damage dealt and recieved",
	"with $d damage dealt",
	"on $l kills and asssts",
	//class specific (kinda self explanitory)
	"while moving",
	"while blast jumping",
	"with teammates extinguished",
	"while spun up",
	"on sentry kills and assists",
	"with teammates healed while below $n% health",
	"on headshot kills",
	"on buildings sapped"
};
const double meterBuildMethodRatings[13] = {25, 10, 40, 20, 20, 300, 50, 30, 50, 50, 4.825, 15, 35};
Stat::Stat(int mod, int statCat, int subStat, string wepType, string wepSlot, string realWepSlot, string tfClass, string ammoType, string meterName, bool whenActive, bool hasMeter, bool wearable, bool rapidFire, bool coatable, bool explosive, bool statFlagPass) {
	//var assigment
	posNegIndex = 0;
	posNegSignIndex = -1;
	numInterval = 5;
	tempBool = false;
	statTemp = "";
	//stat selection
	switch(statCat){
		case 0:
			//more & better attributes coming soon
			type = uncategorized;
			if (subStat + 1 <= 9) {
				posNegSplit = true;
			}
			switch (subStat) {
				case 0: //shouldn't be accessable but is thru 0,9... idk why
					if (mod > 0) {
						statTemp = "This weapon automatically reloads while not active";
						ratingBase = 15;
					} else {
						statTemp = "This weapon fires tracer rounds";
						ratingBase = 5;
					};
					break;
				case 1:
					if (mod > 0) {
						statTemp = "Increased Knockback on the target and shooter";
						ratingBase = 15;
					} else {
						statTemp = "Critical damage is affected by range";
						ratingBase = 25;
					};
					break;
				case 2:
					if (mod > 0) {
						if (realWepSlot == "melee" || wepType == "Cleaver") {
							statTemp = "All players connected via Medigun beams are hit";
							ratingBase = 3.25;
							if (tfClass == "Spy") {
								ratingBase = 40;
							}
						} else if (wearable == true) {
							if (mod > 5)
							statTemp = "Deals 3x falling damage to the player you land on";
							ratingBase = 6.5;
						} else {
							statTemp = "This weapon reloads its entire clip at once";
							ratingBase = 35;	
						}
					} else {
						statTemp = "Wearer cannot carry the intelligence briefcase or PASS Time JACK";
						ratingBase = 2.5;
					};
					break;
				case 3:
					if (mod > 0) {
						if (realWepSlot == "melee") {
							statTemp = "Damage removes Sappers";
							if (tfClass == "Engineer") {
								ratingBase = 0;
							} else {
								ratingBase = 15;
							}
						} else if (wearable == true) {
							statTemp = "Immune to the effects of $e*";
							ratingBase = 45;
						} else {}
					} else {
						if (realWepSlot == "melee" || wepType == "Cleaver") {
							statTemp = "Honorbound: Once drawn sheathing deals 50 damage to yourself unless it ";
							if (wepType == "Cleaver" || mod > 15) {
								statTemp += "hits";
							} else {
								statTemp += "kills";
							}
							ratingBase = 25;
						} else {}
					}
					break;
				case 4:
					if (mod > 0) {
						statTemp = "Increased knockback vs $c";
						ratingBase = 1.25;
					} else {
						statTemp = "You are marked for death while active, and for short period after switching weapons";
						ratingBase = 35;
					}
					break;
				case 5:
					if (mod > 0) {
						statTemp = "Primary Fire: Hits twice, its damage split between the two hits.";
						ratingBase = 1.5;
					} else {
						statTemp = "Maximum health is drained while item is active";
						tempInt = distance(weaponSlots, find(begin(weaponSlots), end(weaponSlots), wepSlot));
						switch(tempInt) {
							case 0:
								ratingBase = 150;
								cout << "primary\n";
								break;
							case 1:
								ratingBase = 75;
								cout << "secondary\n";
								break;
							case 2:
								ratingBase = 50;
								cout << "melee\n";
								break;
							default:
								ratingBase = 10;
								cout << "what\n";
								break;
							}	
					}
					break;
				case 6:
					if (mod > 0) {
						if (realWepSlot == "melee") {
							statTemp = "The first hit will cause an explosion";
						ratingBase = 35;
						} else if (wepType == "Scattergun" || wepType == "Peppergun" || wepType == "Shotgun") {
							statTemp = "Fires a wide, fixed shot pattern";
							ratingBase = 1.25;
						} else {
							statTemp = "$r on headshot";
							ratingMod *= .65;
						}
					} else {
						statTemp = "Successive shots become less accurate";
						ratingBase = 10;
					}
					break;
				case 7:
					if (mod > 0) {
						statTemp = "Critical hit forces victim to laugh";
						ratingBase = 15;
					} else {
						statTemp = "Critical hits do no damage";
						ratingBase = 45;
					}
					break;
				case 8:
					if (mod > 0) {
						if (realWepSlot == "melee") {
							statTemp = "Third successful hit in a row always crits.";
							ratingBase = 10;
						} else if (wearable == true) {
							statTemp = "Blocks a single backstab attempt";
							ratingBase = 35;				
						} else {
							statTemp = "No reload necessary";
							ratingBase = 50;
						}
					} else {}
					break;
				case 9:
					if (mod > 0) {
						if (realWepSlot == "melee" || wearable == true) {
							statTemp = "On Hit by Fire: Fireproof for 1 second and Afterburn immunity for 10 seconds";
							ratingBase = 25;
						} else {
							statTemp = "This weapon automatically reloads while not active";
						ratingBase = 15;
						}
					} else {
						if (realWepSlot == "melee" || wearable == true) {	
							statTemp = "";
							ratingBase = 0;
							if (realWepSlot == "melee") {
								statTemp = "Kill turns victim to ice\n";
								if (tfClass == "Spy") {
									ratingBase += 15;
								} else {
									ratingBase += 1.5;
								}
							}
							statTemp += "Melts in fire, regenerates in 15 seconds and by picking up ammo";
							ratingBase += 50;
						} else {
							statTemp = "This weapon fires tracer rounds";
						ratingBase = 5;
						}
					};
					break;
				case 10:
					if (mod > 0) {		
						statTemp = "Allows you to see enemy health";
						ratingBase = 15;
					} else {
						statTemp = "";
						ratingBase = 0;
					}
					break;
				case 11:
					if (mod > 0) {		
						if (realWepSlot == "melee") {
							statTemp = "This weapon has a large melee range and deploys and holsters slower";
							ratingBase = 0.125;
						} else if (wearable == true) {
							statTemp = "Push enemies back when you land (force and radius based on velocity)";
						ratingBase = 5;
						} else {
							statTemp = "Attacks pierce damage resistance effects and bonuses";
							ratingBase = 7.5;	
						}
					} else {
						statTemp = "";
						ratingBase = 0;
					}
					break;
			}
			break;
		case 1:
			type = damage;
			switch(subStat) {
				case 0:
					//damage bonus / penalty
					statTemp = "$n% damage $a";
					posNegIndex = 1;
					ratingBase = 5;
					break;
				case 1:
				//conditional damage bonus / penalty
					statTemp = "$n% damage $a vs $c";
					posNegIndex = 1;
					ratingBase = 3.5;
					break;
				case 2:
					/*minis to crits & visa versa
					lazy solution but shhh*/
					statTemp = "This weapon $a";
					ratingBase = 4.5;
					posNegIndex = 3;
					break;
				case 3:
					posNegSplit = true;
					if (mod < 0) {
						statTemp = "No random critcal hits";
						ratingBase = 15;
						if (realWepSlot == "melee") {
							ratingBase = 25;
						}
					} else {
						//conditional crit/minicrit
					//the specific wording of this stat is EXTREMELY INCONSISTANT from weapon to weapon so I just chose one
						statTemp = "100% $r vs $c";
					}
					break;
				case 4:
					//bullet spread
					statTemp = "$n% $a accurate";
					ratingBase = 1.875;
					posNegIndex = 4;
					break;
				case 5:
					//Firing speed
					statTemp = "$n% firing speed";
					ratingBase = 4.25;
					break;
				case 6:
					//Clip size
					statTemp = "$n% clip size";
					ratingBase = 2.5;
					break;
				case 7:
					//reserve ammo
					statTemp = "$n% max $l ammo $w";
					tempBool = true;
					if (mod > 0) {
						ratingBase = .875;	
					} else {
						ratingBase = 1.5;
					}
					break;
				case 8:
					statTemp = "$n% $ys per shot";
					ratingBase = 4.5;
					break;
				case 9:
					statTemp = "$n% $a reload time";
					posNegIndex = 6;
					posNegSignIndex = 2;
					ratingBase = 3.25;
					break;
				case 10:
					//wearer condition stat modifier (ex: +25% increase in move speed while health <50%)
					statTemp = "$n% $a in $s $b";
					posNegIndex = 7;
					ratingBase = 3.825;
					break;
				case 11:
					//no crits at all
					posNegSplit = true;
					if (mod < 0) {
						statTemp = "This weapon cannot crit";
						ratingBase = 35;
						if (tfClass == "Sniper" && wepSlot == "primary") {
							statTemp = "No headshots";
							ratingBase = 100;
						}
					} else {
						//wearer condition crit modifier
						statTemp = "$r targets $b";
					}
					break;
				case 12:
					//equalizer / esc plan incremental stat increase / decrease type thing
					statTemp = "$s $as as the user becomes injured";
  				ratingMod = .625;
          posNegIndex = 7;
				  break;
				case 13:
					posNegSplit = true;
					cout << "subStat = " << subStat << "; mod = " << mod << endl;
					if (mod > 0) {
						if (wearable == true) {
							statTemp = "On $l Hit$i: $o";
							} else if (coatable == true) {
  							statTemp = "On Hit Coated Player: $o";
							} else {
							statTemp = "On Hit$i: $o";
						}
					} else {
						statTemp = "On Miss: Hit yourself. Idiot";
						if (realWepSlot != "melee") {
							ratingBase = 150;
						} else {
							ratingBase = 50;	
						}
					}
					break;
				case 14:
          if (mod > 0) {
  					if (wearable == true) {
  							statTemp = "On $l Kill: $o";
  						} else if (coatable == true) {
  							statTemp = "On Kill Coated Player: $o";
							} else {
  							statTemp = "On Kill$i: $o";
  						}
            tempBool = true;
  					ratingMod *= .65;
          }
          break;
        case 15:
          if (mod > 0) {
            statTemp = "Alt Fire: $f";
          }
          break;
				case 16:
					if (mod > 0) {
						statTemp = "Hold Fire to load up to $n* $ys\nRelease Fire to fire all loaded $ys";
					} else if (statFlagPass == true) {
						statTemp = "Overloading the chamber will cause a misfire";
						ratingBase = 2.5;
					}
				break;
      }
      break;
		case 2:
			type = defense;
			switch(subStat){
				case 0:
					//damage resistance
					statTemp = "$n% damage $a $w";
					ratingBase = 5.125;
					posNegIndex = 2;
					posNegSignIndex = 2;
					break;
				case 1:
					//damage type resistance
					statTemp = "$n% $d damage $a $w";
					posNegIndex = 2;
					posNegSignIndex = 2;
					break;
				case 2:
					//max HP
					statTemp = "$n max health $w";
					tempInt = rand() % 9 + 2 * mod / abs(mod);
					if (tempInt < 8 && mod > 3) {
						mod = round(mod/2); //for less of a chance of insane health 
					}
					ratingBase = 7.75;
          if (mod < 0) {
            ratingBase = 12.5;
          }
					break;
				case 3:
					//max OVH
					statTemp = "$n% max overheal $w";
					ratingBase = .75;
					break;
				case 4:
					//HP regen (medic-like)
					statTemp = "Up to $n health $a per second $w";
					ratingBase = 7;
					posNegIndex = 5;
					tempInt = mod;
					mod %= 12 + mod / abs(mod); 
					numInterval = 1;
					if (mod == 0) {
						mod = tempInt / abs(tempInt);
					}
					if (mod < 0 || mod < -5 && tfClass != "Medic") {
						ratingBase = 15;
					}
					break;
			}
			break;
		case 3:
			type = utility;
			switch(subStat) {
				case 0:
					statTemp = "$n% movement speed $w";
					mod %= 9 + 2 * mod / abs(mod);
					ratingBase = 2.625;
					if (mod < 0) {
						ratingBase = 3.375;
					}
					break;
				case 1:
					statTemp = "This weapon deploys $n% $a";
					ratingBase = 1.125;
					posNegIndex = 6;
					posNegSignIndex = 2;
					break;
				case 2:
					statTemp = "This weapon holsters $n% $a";
					ratingBase = 0.5;
					posNegIndex = 6;
					posNegSignIndex = 2;
					break;
				case 3:
					statTemp = "$n% switch speed $w";
					ratingBase = 1.75;
					posNegIndex = 6;
					break;
				case 4: 
					//the greatest & most op stat
					statTemp = "$n% jump height $w";
					ratingBase = 0.35;
					break;
				case 5:
				//hp from things
					statTemp = "$n% health from $h $w";
					ratingBase = 12.5;
					break;
				case 6:
				//ammo from things
					statTemp = "$n% ammo from $j $w";
					ratingBase = 6.25;
					break;
				case 7:
					statTemp = "$n jumps while deployed";
					tempInt = mod;
					mod %= 4 + 2 * mod / abs(mod);
					if (mod < 0 and tfClass == "Scout") {
						mod = round(mod/10);
					} else if (mod < 0 && tfClass != "Scout"){
						statTemp = "Wearer cannot jump";
					} else if (mod > 0) {
						mod = round(mod/4);
					}
					if (mod == 0) {
						mod = tempInt / abs(tempInt);
					}
					if (mod == 1 || tfClass == "Scout" && mod == -1) {
						statTemp.erase(7,1);
					}
					numInterval = 1;
					ratingBase = 10;
					break;
				case 8:
					statTemp = "$n% $a in push force taken from damage and airblast $w";
					mod *= -1;
					posNegSignIndex = 2;
					ratingBase = -1;
					posNegIndex = 7;
					break;
				case 9:
					if (mod > 0) {
					statTemp = "+$n capture rate $w";
						posNegSignIndex = 2;
						ratingBase = 75;
						mod %= 3 + 2 * mod / abs(mod);
						numInterval = 1;
					} else {
						statTemp = "Wearer cannot capture control points or push the payload cart";
						ratingBase = 175;
					}
				break;
			}
			break;
		case 4:
			type = projectile; //and explosives
			switch(subStat) {
				case 0:
					statTemp = "$n% projectile speed";
					ratingBase = 2.188;
					break;
				case 1:
					posNegSplit = true;
					if (mod > 0) {
						statTemp = "Projectile penetrates enemy targets";
						if (explosive == true) {
							ratingBase = 1.5;
						} else {
							ratingBase = 25;
						}
					} else {
						tempString = "+$n degrees random projectile deviation";
						posNegSignIndex = 2;
						ratingBase =
						mod = round(mod/2.5);
						numInterval = 1;
					}
					break;
				case 2:
					posNegSplit = true;
					if (mod > 0) {
						statTemp = "Projectile cannot be deflected";
						if (explosive == true) {
							ratingBase = 50; 
						} else {	
							ratingBase = 15;
						} 
					} else {}
				case 4:
					statTemp = "$n% blast radius";
					ratingBase = 4.875;
					break;
				case 5:
					statTemp = "$n0% increased air control when blast jumping";
					ratingBase = 2;
					break;
				case 6:
					statTemp = "$n% blast radius $b";
					ratingBase = 4.5;
					break;
				case 7:
					statTemp = "$n% self damage force";
					if (tfClass == "Soldier" && wepType == "Rocket Launcher") {
						ratingBase = 7.5;
					} else if (tfClass == "Demoman" && wepType == "Stickybomb Launcher") {
						ratingBase = 5.5;
					} else if (tfClass == "Demoman" && wepType == "Grenade Launcher") {
						ratingBase = 3.5;
					} else {
						ratingBase = 1.5;
					}
				case 8:
					statTemp = "Launched bombs $a on surfaces";
					posNegIndex = 10;
					ratingBase = 85;
					if (mod > 0 && tfClass != "Demoman") {
						statTemp = "Able to destroy enemy stickybombs"; //there will be this stat repeated in demo specific stats since he cannot get this one in this context
						ratingBase = 45;
					}
				case 9:
					if (mod > 0) {
						statTemp = "$ys have a fuse time of 1 second; fuses can be primed to explode earlier by holding down the fire key.\n$ys push players back on impact\nDouble Donk! Explosions after a $ys impact will deal mini-crits to impact victims.";
						ratingBase = 50;
					} else if (statFlagPass == true) {
						statTemp = "$ys do not explode on impact";
						ratingBase = 7.5;
					}
			}
			break;
		case 5:
			type = exclusive;
			switch(subStat) {
				case 0:
					posNegSplit = true;
					if (mod > 0) {
						statTemp = "On Equip: Visit Pyroland";
					} else {
						statTemp = "Only visible in Pyroland";
					}
					break;
				case 1:
					posNegSplit = true;
					statTemp = "Extinguishing teammates restores $n health";
					posNegSignIndex = 2;
					numInterval = 1;
					if (mod > 0) {
						mod += 20;
						ratingBonus = -20;	
					}
					break;
				case 2:
					statTemp = "$n% airblast cost";
					mod *= -1;
					ratingBase = -1.875;
					if (mod > 0) {
						mod *= 2;
						ratingBase *= 2.125;
					}
					break;
				case 3:
					statTemp = "$n% afterburn damage $a";
					posNegIndex = 1;
					mod %= 4 + mod / abs(mod);
					numInterval = 25; //afterburn does 4 damage
					break;
				case 4:
					statTemp = "$n% $a in turning control while charging";
					if (mod > 15) {
						statTemp = "Full turning control while charging";
						ratingBase = 75;
					} else if (mod < 0) {
						statTemp = "No turning control while charging";
					} else {
						ratingBase = 1;
						posNegIndex = 5;
						mod %= 10;
						numInterval = 100;
					}
					break;
				case 5:
					statTemp = "$n max stickybombs out";
					if (mod > 0) {
						mod %= 10;
					} else {
						mod %= 6;
					}
					mod++;
					numInterval = 2;
					ratingBase = 10;
					break;
				case 6:
					if (mod < 0) {
						statTemp = "Detonates stickybombs near the crosshair and directly under your feet";
						ratingBase = 5;
					} else {}
					break;
				case 7:
					if (mod < 0) {
							statTemp = "Able to destroy enemy stickybombs";
							ratingBase = 7.5;
						} else {
							
						}
					break;
				case 8:
					statTemp = "0.$n sec $a bomb arm time";
					posNegIndex = 6;
					posNegSignIndex = 2;
					mod %= 10 + mod / abs(mod);
					if (abs(mod) == 10) {
						tempString = "1 sec $a bomb arm time";
					}
					break;
				case 9:
					statTemp = "Charge time $ad by $n%";
					posNegIndex = 7;
					posNegSignIndex = 2;
					ratingBase = 1.5;
					numInterval = 10;
					break;
				case 10:
					statTemp = "Up to $n% damage based on charge";
					ratingBase = 2;
					break;
				case 11:
					statTemp = "$n% $a in charge impact damage"; //the splendid screen's damage bonus is worded differently, understandably, plus damage bonus is blacklisted for wearables so...
					posNegIndex = 7;
					ratingBase = 2;
					break;
				case 12:
					if (mod > 0) {
						statTemp = "$n% increase in charge impact damage with each head taken while the eyelander is equipped"; //hidden splendid stat but...
						posNegIndex = 2;
						ratingBase = 2.5;
						mod %= 10 + 2 * mod / abs(mod);
					} else {
						statTemp = "Taking damage while shield charging reduces remaining charging time";
						ratingBase = 25;
					}
					break;
				case 13:
					statTemp = "$n% $a in $t recharge rate";
					tempBool = true;
					posNegIndex = 7;
					break;
				case 14:
					statTemp = "0.$n sec $a in charge duration";
					posNegIndex = 7;
					posNegSignIndex = 2;
					mod %= 10 + mod / abs(mod);
					if (abs(mod) == 10) {
						tempString = "1 sec $a in charge duration";
					}
					break;
				case 15:
					if (mod > 10) {
						statTemp = "Ammo boxes collected are converted to health"; //old persian pers stat
						ratingBase = 50;
					} else if (mod > 0) {
						statTemp = "Ammo boxes collected also refill your charge meter"; //new persian pers stat
						ratingBase = 30;
					} else {}
					break;
				case 16:
					statTemp = "$n% $a spin up time";
					ratingBase = 2.5;
					posNegIndex = 6;
					posNegSignIndex = 2;
				case 17:
					posNegSplit = true;
					if (mod > 0) {
						statTemp = "Creates a ring of flames while ";
            if (wepType == "Minigun") {
              statTemp += "spun up";
            } else {
              statTemp += "firing";
            }
						ratingBase = 5;
					} else {
						statTemp = "Consumes an additional $n ammo per second while spun up";
						ratingBase = 8.5;
						posNegSignIndex = 2;
						numInterval = 1;
					}
					break;
				case 18:
					if (mod > 0) {
						if (mod % 2 == 0) {
							statTemp = "Increased $s for each sentry kill and and assist";
						} else {
							statTemp = "Gain 2 revenge crits for each sentry kill and 1 for each sentry assist when your sentry is destroyed";
						}
					} else {
						statTemp = "Per Shot: -$n ammo\nUses metal for ammo";
						posNegSignIndex = 2;
						ratingBase = 12.5;
					}
					break;
				case 19:
					statTemp = "Sentry build speed $ad by n%";
					if (mod > 0) {
						numInterval = 10;
						ratingBase = 7.5;
					} else {
						ratingBase = 5;
					}
					break;
				case 20:
					if (mod > 0) {
						
					} else {
						statTemp = "Replaces the Sentry with a Mini-Sentry";
						ratingBase = 50;
					}
					break;
				case 21:
					statTemp = "Construction hit speed boost $a by $n%";
					posNegIndex = 6;
					numInterval = 10;
					ratingBase = 2.5;
					break;
				case 22:
					statTemp = "While active, movement speed $as based on ÜberCharge percentage (up to $n%)";
					posNegIndex = 6;
					ratingBase = 1;
					break;
				case 23:
					statTemp = "$n% ÜberCharge build rate";
					posNegIndex = 6;
					break;
				case 24:
					if (mod > 0) {
						statTemp = "+1 Organ on hit\nA percentage of your ÜberCharge level is retained on death, based on the number of organs harvested ($n% per). Total ÜberCharge retained on spawn caps at 80%";
						ratingBase = 3.5;
					} else {
						
					}
					break;
				case 25:
					statTemp = "$n% charge rate";
					ratingBase = 3.5;
					break;
				case 26:
					posNegSplit = true;
					if (mod > 0) {
						statTemp = "On Scoped Hit: Apply Jarate for 2 to 5 seconds based on charge level.";
						ratingBase = 3.5;
					} else {
						statTemp = "Nature's Call: Scoped headshots always mini-crit and reduce the remaining cooldown of Jarate by $n* seconds.\n No headshots";
						ratingBase = 35;
					}
					break;
				case 27:
					posNegSplit = true;
					if (mod > 0) {
						statTemp = "Charge and fire shots independent of zoom";
						posNegSignIndex = 2;
						ratingBase = 6.375;
					} else {
						statTemp = "Cannot fire unless zoomed";
						ratingBase = 5;
					}
					break;
				case 28:
					posNegSplit = true;
					if (mod > 0) {
						statTemp = "On Full Charge: +n% damage per shot";
						posNegSignIndex = 2;
						ratingBase = 2.375;
					} else {}
					break;
				case 29:
					posNegSplit = true;
					if (mod > 0) {
						statTemp = "No flinching $b*";
						posNegSignIndex = 2;
						ratingBase = 2.375;
					} else {}
					break;
				case 30:
					statTemp = "$n% cloak duration";
					ratingBase = 3.5;
					break;
				case 31:
					statTemp = "$n% cloak drain rate"; // is this the same thing idk who knows I think kinda but like drain rate is efficency and duration is like how much cloak you have? eh whateva
					mod *= -1;
					ratingBase = -3.5;
					break;
				case 32:
					statTemp = "$n% cloak regen rate";
					numInterval *= 2;
					ratingBase = 4.5;
				case 33:
					statTemp = "$n% cloak meter from ammo boxes";
					ratingBase = 2.5;
					break;
				case 34:
					posNegSplit = true;
					if (mod > 0) {
						statTemp = "On Backstab: $o";
						ratingMod *= 0.25;
            tempBool = true;
					} else {
						statTemp = "No cloak meter from ammo boxes when invisible";
						ratingBase = 4.5;
					}
					break;
				case 35:
					posNegSplit = true;
					if (mod > 0) {
						statTemp = "Upon a successful backstab against a human target, you rapidly disguise as your victim\nSilent Killer: No attack noise from backstabs";
						ratingBase = 8.75;
					} else {
						statTemp = "Disguises require (and consume) a full cloak meter";
						ratingBase = 12.5;
					}
					break;
				//past this point the stats arent sorted by class (If I did re-sort stats I'd have to recheck the blacklist and it'd be a pain) I might re-sort them when v.1.0 comes out with the UI and everything.
			}	
      break;
    case 8:
			cout << "\n\nCASE 8\n\n\n";
      type = special;
      switch (subStat) {
				case 0:	
				cout << "Lunchbox\n";
				//how much hp
		      mod *= 10;
		      mod %= 28; //0 is possible
		      if (mod > 3) {
		        mod -= 3;
		        if (mod > 20) { //20 is more likely
		          mod = 20;
		        }
		        statTemp = "Eat to regain up to" + to_string(mod * 15) + "health."; //no '%' and use of '$' flags is intentional
		      }
		    //effect
		      if (mod < 10) {
		        mod *= rand(); //attempt to re-randomize lol
		        mod %= 15 + 6; //min of 5
		        if (mod > 10) {
		           statTemp = "After consuming, increased $s for $n seconds"; 
		        } else {
		           statTemp = "After consuming, increased $s and $s for $n seconds"; 
		        }
		      }
					break;
				case 1: //shield
				cout << "Shield\n";
					mod *= 10;
					mod %= 77;
					posNegSignIndex = 2;
					if (mod < 40) { //rare bullet damage
						tempInt = mod % 10 * 5 + 1;
						tempInt = round(tempInt / 3);
						statTemp = to_string(tempInt) + "% bullet damage resistance $w\n";	
						ratingBase += 4;
					}
					tempInt = mod % 12 * 5 + 4;
					tempInt = round(tempInt / 1.5);
					statTemp = to_string(tempInt) + "% explosive damage resistance $w\n";
					ratingBase += 3.5;
					tempInt = mod * 5 + 4;
					statTemp = to_string(tempInt) + "% fire damage resistance $w";
					ratingBase += 2.5;
					break;
				case 2: //coatables
				cout << "coatable\n";
					tempInt = rand() % 2;
					statTemp = coatEffects[tempInt];
					ratingBonus = coatRatings[tempInt];
					if (tempInt == 2 || tempInt == 3) {
						ratingMod *= 0.35;
					}
					if (mod > 2 && tfClass != "Pyro") {
						statTemp += "\nCan be used to extinguish fires\nExtinguishing teammates reduces cooldown by -n%";
						posNegSignIndex = 2;
						ratingBase = 1.25;
					}	
					break;
				case 3: //banners
					statTemp = "Provides a" + bannerBuffTypes[bannerBuffTypeIndex] + " buff for nearby teammates\n";
					if (mod > 10) {
						statTemp += "Build Rage with damage done and / or taken";
					} else {
						statTemp += "Build Rage with damage done.";
					}
					statTemp += "\nWhile the buff is active, all nearby teammates recieve:";
					break;
				case 4: //meters
					tempBool = false;
					if (mod > 0) {
						statTemp = "Build $t ";
						tempInt = rand() % 6;
						if (tempInt == 6) {
							tempInt += distance(begin(classList), find(begin(classList), end(classList), tfClass));
							if (tfClass == "Demo") {
								tempInt -= 2;
							}
						}
						tempString = meterBuildMethods[tempInt];
						statTemp += tempString + " (Meter fills at ";
						tempInt = ratingBase * (21 - mod);
						ratingBase = meterBuildMethodRatings[tempInt];
						if (statTemp.substr(0,6).find("on") != string::npos) {
							tempInt = round(tempInt / 8);
							tempBool = true;
						}
						if (statTemp.substr(0,6).find("with") != string::npos || 
							tempBool == true) {
							statTemp += to_string(tempInt) + " " + tempString.substr(tempString.find(" "));
							if (statTemp.find("and") != string::npos) {
								statTemp.insert(statTemp.find("and"), to_string(round(tempInt / 1.75)));
							} else if (statTemp.find("while", 16) != string::npos) {
								statTemp.erase(statTemp.find("while", 16), string::npos);
							}
						} else if (statTemp.substr(0,6).find("while") != string::npos) {
							tempInt = round(tempInt / 2);
						} 
					} else if (statFlagPass == true) {
						statFlagPass = false;
					}
					break;
				case 5: //counter (heads, etc)
					break;
			}
		} 
	statString = statTemp; //copy template to main string 
	if (mod > 0) {
			upside = 0;
		} else {
			upside = 1;
		};
	if (posNegSignIndex < 0) {
		posNegSignIndex = upside;
	} //on hit rewards
	while (statString.find("$o") != string::npos) {
		tempInt = rand() % 15;
		do {	
			while (realWepSlot == "melee" && tempInt == 1) {
				tempInt += rand() % 15 - 1;
			}
	    while (hasMeter == false && tempInt == 5) {
					tempInt += rand() % 15 - 5;
			}
			while (hasMeter == false && tempInt == 6) {
				tempInt += rand() % 15 - 6;
			}
	    if (tempInt == 1) {
	      mod %= 10 + 3;
	    }
			tempInt = abs(tempInt);
			} while (tempBool == true && tempInt > 6);
		statString.replace(statString.find("$o"), 2, hitRewards[tempInt]);
		ratingBase *= hitRewardRatings[tempInt];
		if (rapidFire == true) {
			ratingBase *= 2;
		}
	}
	//pos/neg text & other stuff
	if (statString.find("$a") != string::npos) {
		statString.replace(statString.find("$a"), 2, posNegStringPair[posNegIndex][upside]);
	}
	while (statString.find("$b") != string::npos) {
		tempInt = rand() % 3;
		statString.replace(statString.find("$b"), 2, wearerConditions[tempInt]);
		ratingMod *= wearerConditionMods[tempInt];
		//will add more to switch statement soon :)
		switch (tempInt) {
			case 2: //burning
				if (tfClass == "Pyro") {
					ratingMod = 0.7;
				}
			case 4: //slowed
				if (tfClass == "Scout" && realWepSlot == "melee") {
					ratingMod = 0.55;
				}
			case 5: //bleeding
				if (tfClass == "Scout") {
					ratingMod = 0.55;
				}
		}
	}
	while (statString.find("$c") != string::npos) {
		tempInt = rand() % 9;
		statString.replace(statString.find("$c"), 2, conditions[tempInt]);
		ratingMod *= conditionMods[tempInt];
		//will add more to switch statement soon :)
		switch (tempInt) {
			case 2: //burning
				if (tfClass == "Pyro") {
					ratingMod = 0.7;
				}
				break;
			case 4: //slowed
				if (tfClass == "Scout" && realWepSlot == "melee") {
					ratingMod = 0.55;
				}
				break;
			case 5: //bleeding
				if (tfClass == "Scout") {
					ratingMod = 0.55;
				}
				break;
			case 8:
				if (mod > 0) {
					statString = "Instantly kills enemies who also have this weapon equipped";
					ratingBase = 5;
				} else {
					statString = "Does no damage to enemies who have also equipped this item";
					ratingBase = 7.5;
				}
				mod = 1;
				ratingMod = 1;
				break;
		}
	}
	while (statString.find("$d") != string::npos) {
		if (tfClass == "Soldier" && realWepSlot == "primary"|| tfClass == "Pyro" && wepType == "Flare Gun" || tfClass == "Demo" && realWepSlot != "melee") {
			tempInt = rand() % 7;
		} else if (wepType == "Shield") {			
			tempInt = rand() % 3 + 3;
		} else {
			tempInt = rand() % 6;
		} 
		statString.replace(statString.find("$d"), 2, damTypes[tempInt]);
		ratingBase *= damTypeRatings[tempInt];
	}
	while (statString.find("$e") != string::npos) {
		if (statString.substr(statString.find("$e"), 2).find("*") != string::npos) {
			statString.erase(statString.find("*"), 1);
			tempInt = rand() % 6;
		} else {
      tempInt = rand() % 5;
    }
		if (tempBool == true) {
      ratingBase = debuffRatings[tempInt];
			tempInt = rand() % 6;
      if (tempInt > 5) {
        tempInt++;
      }
		} else {
			ratingMod *= debuffMods[tempInt];
		}
		statString.replace(statString.find("$e"), 2, debuffs[tempInt]);
	}
  while (statString.find("$f") != string::npos) {
		tempInt = rand() % 5;
		statString.replace(statString.find("$f"), 2, altFire[tempInt]);
		ratingBase = altFireRatings[tempInt];
    if (realWepSlot != "melee" && tempInt < 4) {
      statString += "(consumes $n% of the clip)";
      mod %= 4 + mod / abs(mod);
      numInterval = 25;
      posNegSignIndex = 2;
      ratingMod *= 0.1;
    }
	}
	while (statString.find("$h") != string::npos) {
		tempInt = rand() % 4;
		statString.replace(statString.find("$h"), 2, HPContainerTypes[tempInt]);
		ratingMod *= HPContainerTypeMods[tempInt];
	}
	while (statString.find("$i") != string::npos) {
		tempInt = rand() % 35;
		if (tempInt <= 7) {
			tempString = " " + hitConditions[tempInt];
			ratingMod *= hitConditionMods[tempInt];
		} else {
			tempString = "";
		}
		cout <<  endl << hitConditions[0] << endl << tempInt << hitConditions[tempInt] << endl << tempString << endl;
		statString.replace(statString.find("$i"), 2, tempString);
	}
	while (statString.find("$j") != string::npos) {
		tempInt = rand() % 2;
		cout << endl << ammoContainerTypes[0] << endl << tempInt << ammoContainerTypes[tempInt] << endl;
		statString.replace(statString.find("$j"), 2, ammoContainerTypes[tempInt]);
		ratingMod *= ammoContainerTypeMods[tempInt]; 
	}
	while (statString.find("$l") != string::npos) {
		if (realWepSlot != "melee" && wearable == false) {
			statString.replace(statString.find("$l"), 2, realWepSlot);
		} else {
			tempInt = 3;
			if (tempBool == true) {
				tempInt--;
			}
			do {
				tempString = weaponSlots[rand() % tempInt];	
			}	while (tempString == realWepSlot && wearable == true); 
			statString.replace(statString.find("$l"), 2, tempString);
		} 
	}
	while (statString.find("$r") != string::npos) {
		if (statString.find("*") != string::npos) {
			statString.erase(statString.find("*"), 1);
			tempBool = true;
		}
		if (tempBool == true) {
			tempInt = rand() % 3;
		} else {
			tempInt = rand() % 2;
		}
		statString.replace(statString.find("$r"), 2, critTypes[tempInt]);
		ratingBase *= critTypeRatings[tempInt];
	}
	while (statString.find("$s") != string::npos) {
		if (wepType == "Lunchbox") {
      tempInt = rand() % 12;
    } else {      
      tempInt = rand() % 10;
    }
		if (wearable == true) {
			tempInt %= 3;
			switch (tempInt) {
				case 0:
					tempInt = 8;
					break;
				case 1:
					tempInt = 9;
					break;
				default:
					tempInt = 2;
					break;
			}
		}
    if (tempInt < 11) {
      tempString = statTypes[tempInt];
      ratingBase *= statTypeRatings[tempInt];
    } else if (tempInt == 11) {
      tempString = "+$n* max health";
      ratingBase *= 5;
    } else {
      tempString = "attacks $r";
    }
		statString.replace(statString.find("$s"), 2, tempString);
	}
	while (statString.find("$t") != string::npos) {
		if (statString.substr(statString.find("$t"),2).find("*") != string::npos) {
			statString.erase(statString.find("*"), 1);
			tempBool = true;
		}
		if (hasMeter == false || tempBool == true) {
			tempInt = rand() % 10;
			tempString = meterNames[tempInt];
		} else {
			tempString = meterName;
		}
		statString.replace(statString.find("$t"), 2, tempString);
		if (tempBool == true) {
			ratingMod *= meterMods[tempInt];
		}
	}
	while (statString.find("$w") != string::npos) {
    if (wepType == "Lunchbox") {
      if (mod > 0) {
        statString = "User has " + statString;
        tempString = "during this time"; 
      } else {
        tempString = "when the effect ends";
      }
    } else if (coatable == true && mod > 0) {
      statString = "Enemy has " + statString;
			tempString = posNegStringPair[posNegIndex][0];
			if (posNegIndex != 0 && statString.find(tempString) != string::npos) { //positive stat to negative (for enemy)
				statString.replace(statString.find(tempString), tempString.length(), posNegStringPair[posNegIndex][1]);
			}
			tempString = "while coated"; //hope this works lol
		} else if (wepType == "Battle Banner") {
			tempString = "";
		} else {
  		tempString = "on wearer";
  		if (whenActive == true) {
  			tempInt = distance(weaponSlots, find(begin(weaponSlots), end(weaponSlots), wepSlot));
  			switch(tempInt) {
  				case 0:
  					ratingMod *= .95;
  					break;
  				case 1:
  					ratingMod *= .65;
  					break;
  				case 2:
  					ratingMod *= .45;
  					break;
  				default:
  					ratingMod *= .25;
  					break;
  			}
  		}
    }
		statString.replace(statString.find("$w"), 2, tempString);
	}	
	while (statString.find("$y") != string::npos) {
		statString.replace(statString.find("$y"), 2, ammoType);
	}
	while (statString.find("$z") != string::npos) {
		tempInt = rand() % 2;
		statString.replace(statString.find("$z"), 2, sizes[tempInt]);
		ratingMod *= sizeMods[tempInt];
	}
	//number/percentage value
	if (statString.find("$n") != string::npos) {
		/*old code to remove leading zeros
		tempString = to_string(abs(mod*numInterval));
		tempString = tempString.substr(0, tempString.find(".")); 
		statString.replace(statString.find("$n"), 2, posNegSign[posNegSignIndex] + tempString);*/
		tempInt = 2;
		if (statString.find("*") != string::npos) {
			cout << "HOOOH WHEEE";
			if (statString.find("%") != string::npos) {
				numInterval = 5;
			} else {
				numInterval = 1;
			}
			cout << numInterval << endl;
			statString.erase(statString.find("*"), 1);
			posNegSignIndex = 2;
		}
  if (statString.find("%") != string::npos) {
			if (mod * numInterval == 35) {
        mod = 33;
        numInterval = 1;
        ratingMod *= 0.2;
      } else if (mod * numInterval == 65) {
        mod = 66;
        numInterval = 1;
        ratingMod *= 0.2;
      }
		}
		statString.replace(statString.find("$n"), 2, posNegSign[posNegSignIndex] + to_string(abs(mod*numInterval)));
	} else {
		mod /= abs(mod);
	}
  statString[0] = toupper(statString[0]);
	rating = (ratingBase * mod + ratingBonus) * ratingMod;
	cout << "/(mod = " << mod << "; ratingBase = " << ratingBase << "; ratingMod = " << ratingMod << "; ratingBonus = " << ratingBonus << ";\n rating = " << rating << ")\\...";
}
//1.35 hp on hit mult