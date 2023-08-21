#include "stats.hpp"
// this is messy but probably temporary >.>
int metertempInt, mod, statCat, subStat, bannerBuffTypeIndex = -1, lunchboxDuration, invisWatchCloakTypeIndex = -1, meterStatBoostNum = -1;
float invisWatchFeignDuration = -1;
double meterMod = 0;
array<vector<int>, 6> usedDynamicStatEntries;
array<string, 6> singValStatFlagNames = {"$b", "$c", "$i", "$l", "$u", "$z"};
array<string, 6> dynamicStatFlagNames = {"Single-Value Storage Flags", "$d", "$h", "$j", "$o", "$s"};
const array<int, 9> statCatNum = {11, 17, 5, 11, 8, 45, 0, 0, 8};
const array<array<string, 2>, 11> posNegStringPair = {{
	{"", ""}, // 0
	{"bonus", "penalty"}, // 1
	{"resistance", "vulnerability"}, // 2
	{"crits whenever it would normally mini-crit", "mini-crits whenever it would normally crit"}, // 3
	{"more", "less"}, // 4
	{"regenerated", "drained"}, // 5
	{"faster", "slower"}, // 6
	{"increase", "decrease"}, // 7
	{"increase", "reduction"}, // 8
	{"explode", "shatter"}, // 9
	{"larger", "smaller"} // 10
}};
const array<string, 3> posNegSign = {"+", "-", ""};
const array<string, 7> damTypes = {"bullet", "explosive", "fire", "critical", "ranged", "melee", "self"};
const array<double, 7> damTypeRatings = {4.25, 3.5, 2.5, 1.063, 5, .75, 4};
const array<string, 3> critTypes = {"critical hits", "mini-crits", "mini-crits and critical hits"};
const array<double, 3> critTypeRatings = {190, 30, 200};
const array<string, 8> conditions = {
	"players", // 0
	"buildings", // 1
	"burning players", // 2
	"wet players", // 3
	"targets launched airborne by explosions, grapple hooks or rocket packs", // 4
	"slowed players", // 5
	"bleeding players", // 6
	"players who have also equipped this item" // 7
};
const array<double, 8> conditionMods = {.85, .15, .35, .25, .15, .05, .188, .031};
const array<string, 7> hitConditions = {"Building", "Burning Player", "Wet Player", "Airborne Player", "Slowed Player", "Bleeding Player", "Teammate"};
const array<double, 7> hitConditionMods = {.15, .35, .25, .45, .05, .188, .5};
const array<string, 3> wearerConditions = {"when fired at their back from close range", "while health >50% of max", "while health <50% of max"};
const array<double, 3> wearerConditionMods = {.75, .65, .35};
const array<array<string, 3>, 9> classSpWearerConditions = {{
/*Scout*/ {"while airborne"}, 
/*Soldier*/ {"while blast jumping"},
/*Pyro*/ {"while flare jumping"}, 
/*Demoman*/ {"while blast jumping"},
/*Heavy*/ {"while spun up & below 50% health"},
/*Engineer*/ {"to your sentry's target"}, 
/*Medic*/ {"while ÜberCharged"},
/*Sniper*/{"while scoped", "while fully charged", "while not fully charged"},
/*Spy*/ {"while disguised", "while cloaked"}
}};
const array<array<double, 3>, 9> classSpWearerConditionMods = {{
/*Scout*/ {0.85},
/*Soldier*/ {0.45},
/*Pyro*/ {0.125},
/*Demoman*/ {0.375},
/*Heavy*/ {0.75},
/*Engineer*/ {0.5},
/*Medic*/ {0.1},
/*Sniper*/ {0.625, 0.125, 0.5},
/*Spy*/ {0.75, 0.5}
}};
const array<string, 16> rewards = {
	// on hit & on kill rewards
	"gain a speed boost", // 0
	"clip size increased (up to +$n*)", // 1
	"heal $n% of base health", // 2
	"$n health restored", // 3
	"a $z health pack is dropped", // 4
	"refills $n% of your $t meter", // 5
	"$n* seconds of $r", // 6
	"$n* seconds of increased $s", // 7
	// on hit rewards only
	"applies $e* for $n* seconds", // 8
	"one target at a time is Marked-For-Death, causing all damage taken to be mini-crits", // 9
	"target is engulfed in flames", // 10
	"100% chance to slow target", // 11
	"gain up to +$n* health", // 12
	"damage dealt is returned as ammo", // 13
	"victim loses up to $n*% $t* charge", // 14
	"next shot fires $n*% faster" // 15
};
const array<double, 16> rewardRatings = {2.5, 7.5, 3.75, 5.875, 145, 6.5, 0.25, 0.375, 1.75, 1.75, 1.5, 5, 2.75, 35, 20, 2.375};
const array<string, 4> penalties = {
// miss and shot penalties
	"$n* seconds of decreased $s", // 0
	"-$n health", // 1
// on miss penalties only
	"Hit Yourself. Idiot", // 2
	"next shot fires $n*% slower" // 3
};
const array<double, 4> penaltyRatings = {0.563, 1.25, 50, 2.375};
const array<string, 5> altFire = {
	"Launches a ball that $e*s opponents", // 0
	"Launches a festive ornament that shatters causing bleed", // 1; it'd be stupid if it didnt cause bleed
	"A charged shot that mini-crits players, sets them on fire and disables buildings for 4 sec", // 2
	"Launches a projectile-consuming energy ball.", // 3
	"Reach and shove someone!" // 4
};
const array<double, 5> altFireRatings = {1, 35, 75, 100, 10};
const array<string, 7> debuffs = {"afterburn", "stun", "slow", "bleed", "mad milk", "incoming $r*", "mark"};
const array<double, 7> debuffRatings = {25, 150, 10, 3.5, 25, 1, 15};
const array<double, 7> debuffMods = {0.85, 0.15, 0.375, 0.5, 0.438, 0.5, 0.5};
const array<string, 5> coatEffects = {
// will make more soon? idk
	"Players heal $n% of the damage done to coated enemies", // 0
	"Applies $e* to coated enemies", // 1
	"Coated enemies take $r", // 2
	"Coated enemies take increased afterburn and afterburn ignores immunities\nOn Hit Coated Enemy: target is engulfed in flames", // 3
    "Coated enemies have -$n% slower movement & switch speed" // 4
};
const array<double, 5> coatBonus = {4.875, 0, 0, 10, 3.125};
const array<string, 10> statTypes = {
    // generic
    "damage", // 0
    "movement speed", // 1
    "firing speed", // 2
    "reload speed", // 3
    "switch speed", // 4
    "health from healers & packs", // 5
    // hitscan specific
    "accuracy", // 6
    // projectile specific
    "projectile speed", // 7
    // explosive specific
    "blast radius", // 8
    "self damage force" // 9
};
const array<double, 10> statTypeRatings = {4.75, 2.75,  4.625, 5.5, 1, 3.25, 1.875, 2.188, 4.875, 2.5};
const array<double, 14> meterMods = {0.05, 0.125, 0.5,  0.75, 0.25, 0.063, 0.25, 0.5,  0.35,  0.25, 0.5,  0.85, 0.95,  0.8};
const array<string, 13> meterBuildMethods = {
  "with damage dealt", "with damage recieved",
  "with damage dealt and recieved", "with $d damage dealt",
  "on $l kills and asssts",
  // class specific (kinda self explanitory)
  "while moving", "while blast jumping", "on teammate extinguishes",
  "while spun up", "on sentry kills and assists",
  "with teammates healed while below $n% health", "on headshot kills",
  "on buildings sapped"
};
const array<double, 13> meterBuildMethodRatings = {
    25, 10, 40, 20, 20, 300, 50, 30, 50, 50, 4.825, 15, 35};
const array<string, 12> meterLossMethods = {
    "when hit", "on miss", "over time",
    // class specific (kinda self explanitory)
    "on air jump", "n/a", "n/a", "n/a", "n/a",
    "when one of your buildings are destroyed",
    "while not healing for more than $n* seconds", "on non-leathal hit",
    "on sapper destroyed"};
const array<double, 12> meterLossMethodRatings = {25, 15, 60, 35, 0, 0, 0, 0, 25, 2.5, 15, 20};
const array<array<string, 3>, 9> silentKiller = {{
	{"N/A", "N/A", "N/A"}, // idk anything for scout
	{"N/A", "N/A", "N/A"}, // idk anything for soldier either
	{"N/A", "No sound made when firing", "No sound made on kill"}, // pyro
	{"N/A", "No charge noise from sheild charges", "No charge noise from sheild charges"}, // Demoman
	{"No barrel spin sound", "Chew with your mouth closed", "No sounds made when punching"}, // Heavy (these are dumb I know)
	{"N/A", "N/A", "Your sentry does not beep when locking onto a target"}, // Engie
	{"N/A", "Medigun beam is not visible to enimies", "N/A"}, // Medic
  {"Your rifle is equipped with a silencer, making shots quiet", "Your SMG is equipped with a silencer, making shots quiet", "N/A"}, // sniper
  {"Your revolver is equipped with a silencer, making shots quiet", "Sapping does not make a noise nor does it make sparks appear on the building", "No attack noise from backstabs\nOn Backstab: victim's corpse dissapears"}, // Spy
}};
const array<array<double, 3>, 9> silentKillerRatings = {{
    {0, 0, 0},         // Scout (shouldn't be accessable)
    {0, 0, 0},         // Soldier (shouldn't be accessable)
    {0, 1, 0.5},       // Pyro
    {0, 0.75, 0.75},   // Demoman
    {2.5, 0.25, 0.25}, // Heavy
    {0, 0, 3.5},       // Engineer
    {0, 0.5, 0},       // Medic
    {1.25, 0.25, 0},   // Sniper
    {4.25, 1.25, 6.5}, // Spy
}};
const array<string, 4> HPContainerTypes = {"healers", "packs", "Medic sources", "dispensers"};
const array<double, 4> HPContainerTypeMods = {.85, .15, .35, .40};
const array<string, 2> ammoContainerTypes = {"ammo boxes", "dispensers"};
const array<double, 2> ammoContainerTypeMods = {.65, .25};
const array<string, 3> sizes = {"small", "medium", "large"};
const array<double, 3> sizeMods = {.35, .5, 1};
const array<string, 4> bannerBuffTypes = {" special", "n offensive", " defensive", " movement"};
const array<string, 4> buildings = {"sentry", "dispenser", "teleporters", "buildings"}; // buildings = all
const array<double, 4> buildingRatings = {100, 95, 70, 215};
const array<string, 4> uberEffects = {
	"full damage invulnurability", // 0
	"100% $r", // 1
	"an increase in healing by $n0% and immunity to movement-impairing "
	"effects", // 2
	"a resistance bubble that blocks $n% base damage and 100% crit damage of the selected type" // 3
};
const array<double, 4> uberEffectRatings = {50, 1, 12, 4.25};
const array<string, 3> cloakTypes = {"Timed", /*stock*/ "Motion Sensitive", "Feign Death"};
const array<double, 3> cloakTypeRatings = {100, 115, 75};
Stat::Stat(int mod, int statCat, int subStat, string wepType, string wepSlot, string realWepSlot, string tfClass, string ammoType, string meterName, bool whenActive, bool hasMeter, bool hasAltFire, bool wearable, bool rapidFire, bool coatable, bool explosive, bool clipless, bool critGimmick, bool miscAmmo, bool statFlagPass, bool lockedModValue) {
  // var assigment
  initialMod = mod;
  posNegIndex = 0;
  posNegSignIndex = -1;
  numInterval = 5;
  tempBool = false;
  statTemp = "";
  ratingBase = 0;
  ratingMod = 1;
  ratingBonus = 0;
  dStatType = -1;
  if (mod > 0) {
    realUpside = true;
  } else {
    realUpside = false;
  }
  if (meterName == "" && meterStatBoostNum > 0) {
    meterName = "charge";
  }
  usedDynamicStatEntries[0].reserve(6); // so shit 100% wont go wrong maybe
  // stat selection
  switch (statCat) {
  case 0:
    type = special; // aka just gimmicks
    switch (subStat) {
    case 0: // shouldn't be accessable
      cout << "\nUh Oh...\n\n";
      ratingMod = 0;
      break;
    case 1:
      if (mod > 0) {
        statTemp = "Increased knockback on the target and shooter";
        ratingBase = 15;
      } else {
        statTemp = "Critical damage is affected by range";
        if (wepType == "Flamethrower") {
          ratingBase = 2.5;
        } else {
          ratingBase = 6.5;
        }
        if (critGimmick) {
          ratingMod *= 1.875;
        }
        if (realWepSlot == "melee") {
          ratingMod *= 1.25;
        }
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
        } else if (wearable) {
          if (mod > 5)
            statTemp = "Deals 3x falling damage to the player you land on";
          if (tfClass == "Soldier" || tfClass == "Demoman" ||
              wepType == "Jetpack") {
            ratingBase = 8.875;
          } else {
            ratingBase = 4.25;
          }
        } else {
          statTemp = "This weapon reloads its entire clip at once";
          if (explosive) {
            ratingBase = 40;
          } else {
            ratingBase = 25;
          }
        }
      } else {
        statTemp =
            "Wearer cannot carry the intelligence briefcase or PASS Time JACK";
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
        } else if (wearable || wepType == "Lunchbox" || wepType == "Medigun") {
          statTemp = "Immune to the effects of $e";
          tempBool = true;
          ratingBase = 35;
          if (wepType == "Medigun") {
            statTemp = "Immune to debuff effects during ÜberCharge";
          }
        } else {
        }
      } else {
        if (realWepSlot == "melee" || wepType == "Cleaver") {
          statTemp = "Honorbound: Once drawn sheathing deals 50 damage to "
                     "yourself unless it ";
          if (wepType == "Cleaver" || mod > 15) {
            statTemp += "hits";
          } else {
            statTemp += "kills";
          }
          ratingBase = 25;
        } else {
        }
      }
      break;
    case 4:
      statTemp = "$ad knockback vs $c";
      if (mod > 0) {
        ratingBase = 1.25;
      } else {
        ratingBase = 0.25;
      }
      if (explosive) {
        ratingMod *= 1.125;
      }
      posNegIndex = 7;
      if (coatable) {
        statTemp = statTemp.substr(0, statTemp.find("vs"));
      } else if (wepType == "Shield" || realWepSlot == "melee") {
        mod *= -1;
        ratingBase *= -1;
        if (wepType == "Shield" || wepType == "Sword") {
          ratingBase *= 5;
        }
        if (mod < 0) {
          ratingBase *= 2;
        }
      }
      break;
    case 5:
      if (mod > 0 && wepSlot == "melee") {
        statTemp =
            "Primary Fire: Hits twice, its damage split between the two hits.";
        ratingBase = 0.875;
      } else {
        statTemp = "$w*Maximum health is drained while item is active";
        if (tfClass == "Heavy") {
          ratingMod *= 0.5;
        } else if (tfClass == "Soldier") {
          ratingMod *= 0.875;
        } else if (tfClass == "Pyro") {
          ratingMod *= 1.25;
        }
        ratingBase = 200;
      }
      break;
    case 6:
      if (mod > 0) {
        if (realWepSlot == "melee" || coatable) {
          statTemp = "The first hit will cause an explosion";
          ratingBase = 30;
        } else if (wepType == "Scattergun" || wepType == "Peppergun" ||
                   wepType == "Shotgun") {
          statTemp = "Fires a wide, fixed shot pattern";
          ratingBase = 0.875;
        } else {
          statTemp = "$r on headshot";
          if (projectile) {
            ratingMod *= .15;
          } else {
            ratingMod *= .65;
          }
        }
      } else if (!(realWepSlot == "melee" || projectile)) {
        statTemp = "Successive shots become less accurate";
        ratingBase = 10;
      }
      break;
    case 7:
      if (mod > 0) {
        statTemp = "Critical hit forces victim to laugh";
        ratingBase = 15;
      } else if (statFlagPass) {
        statFlagPass = false;
        statTemp = "Critical hits do no damage";
        ratingBase = 25;
      }
      break;
    case 8:
      if (mod > 0) {
        if (realWepSlot == "melee") {
          statTemp = "Third successful hit in a row always $r.";
          if (tfClass == "Scout") {
            ratingMod *= 0.039;
          } else {
            ratingMod *= 0.026;
          }
        } else if (wearable) {
          statTemp = "Blocks a single backstab attempt";
          ratingBase = 35;
        } else {
          statTemp = "No reload necessary";
          ratingBase = 50;
        }
      } else if (!wearable) {
        statTemp = "User is marked for death while active, and for short "
                   "period after switching weapons";
        if (wepSlot == "primary") {
          ratingBase = 55;
        } else {
          ratingBase = 25;
        }
      }
      break;
    case 9:
      if (mod > 0) {
        if (realWepSlot == "melee" || wearable) {
          statTemp = "On Hit by Fire: Fireproof for 1 second and Afterburn "
                     "immunity for 10 seconds";
          ratingBase = 25;
        } else if (!whenActive) {
          statTemp = "This weapon automatically reloads while not active";
          if (explosive) {
            ratingBase = 20;
          } else {
            ratingBase = 15;
          }
          if (wepSlot == "primary") {
            ratingBase = round(ratingBase / 2.5);
          }
        }
      } else {
        if (realWepSlot == "melee" || wearable) {
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
          statTemp +=
              "Melts in fire, regenerates in 15 seconds and by picking up ammo";
          ratingBase += 50;
          if (wearable) {
            ratingBase += 25;
          }
          if (wepType == "Invis Watch") {
            ratingBase += 75;
          }
        } else {
          statTemp = "This weapon fires tracer rounds";
          ratingBase = 5;
        }
      };
      break;
    case 10:
      if (mod > 0) {
        statTemp = "Allows you to see enemy health";
        if (coatable) {
          statTemp = "Allows you to see coated enemies' health";
          ratingMod *= 0.25;
        }
        if (tfClass == "Sniper") {
          ratingBase = 15;
        } else if (tfClass == "Scout" || tfClass == "Pyro") {
          ratingBase = 10;
        } else {
          ratingBase = 7.5;
        }
        ratingBase = 10;
      } else if (wepType == "Lunchbox") {
        statTemp = "Cannot be shared with teammates";
        ratingBase = 35;
      }
      break;
    case 11:
      if (mod > 0) {
        if (realWepSlot == "melee") {
          statTemp = "This weapon has a large melee range and deploys and "
                     "holsters slower";
          ratingBase = 0.125;
        } else if (wearable) {
          statTemp = "Push enemies back when you land (force and radius based "
                     "on velocity)";
          ratingBase = 5;
        } else {
          statTemp = "Attacks pierce damage resistance effects and bonuses";
          ratingBase = 3.75;
        }
      } else if (wepType == "Lunchbox") {
        statTemp = "User can only use melee weapons";
        ratingBase = -75;
        mod *= -1;
      }
      break;
    }
    if ((wepType == "Lunchbox" || meterStatBoostNum > 0) && statTemp != "") {
      statTemp += " $w";
    }
    break;
  case 1:
    type = damage;
    switch (subStat) {
    case 0:
      // damage bonus / penalty
      statTemp = "$n% damage $a";
      if (wepType == "Crossbow") {
        statTemp = "$n% healing / damage $a";
        ratingBase = 6.5;
      }
      if (wepSlot == "melee" && mod < 0) {
        ratingMod *= 0.75;
      }
      posNegIndex = 1;
      ratingBase = 5;
      break;
    case 1:
      // conditional damage bonus / penalty
      statTemp = "$n% damage $a vs $c";
      if (wepType == "Crossbow") {
        statTemp = "$n% healing & damage $a vs $c";
        ratingBase = 5;
      } else if (mod > 10 && (rand() % 3) == 0 && tfClass == "Pyro" &&
                 wepSlot != "primary") {
        statTemp = "Damage increases based on remaining duration of afterburn";
      }
      posNegIndex = 1;
      ratingBase = 3.5;
      if (mod < -19) {
        mod = -19;
      }
      break;
    case 2:
      /*minis to crits & visa versa
      lazy solution but shhh*/
      statTemp = "This weapon $a";
      if (mod > 0) {
        if (wepType == "Sword") {
          ratingBase = 5;
        } else {
          ratingBase = 2.5;
        }
      } else {
        ratingBase = 25;
      }
      posNegIndex = 3;
      if (mod < 0) {
        if (tfClass == "Sniper") {
          if (mod > 0) {
            ratingBase = 10;
          } else if (wepSlot == "primary") {
            statTemp = "Headshots mini-crit instead of crit";
            ratingBase = 150;
          }
        } else if (wepType == "Flare Gun") {
          statTemp = "Flares mini-crit burning players";
          ratingBase = 125;
        }
      }
      break;
    case 3:
      if (mod > 0) {
        // conditional crit/minicrit
        // the specific wording of this stat is EXTREMELY INCONSISTANT from
        // weapon to weapon so I just chose one
        statTemp = "100% $r vs $c";
        if (wepType == "Cleaver") {
          statTemp = "Long distance hits $r players";
          ratingMod *= 0.4;
        }
        if (miscAmmo) { // tickle mittens stats hehe dont ask why its stored in
                        // miscAmmo
          statTemp.replace(statTemp.find("$r"), 2, "crits");
          ratingBase = 35;
        }
      } else {
        statTemp = "No random critcal hits";
        ratingBase = 7.5;
        if (realWepSlot == "melee") {
          ratingBase = 15;
        }
      }
      break;
    case 4:
      // bullet spread
      if (mod > 0 && wepType != "Sniper Rifle") {
        statTemp = "$n% $a accurate";
        ratingBase = 1.875;
        posNegIndex = 4;
        if (wepType == "Sniper Rifle") {
          ratingMod *= 25;
        }
      }
      break;
    case 5:
      // Firing speed
      statTemp = "$n% firing speed";
      ratingBase = 4.625;
      if (wepSlot == "melee" && tfClass == "Engineer") {
        ratingBase = 5.063;
      }
      if (wepType == "Lunchbox") {
        statTemp = "$n% consumption speed";
        ratingBase /= 2.5;
      } else if (wepType == "Flame Thrower") {
        statTemp = "$n% airblast fire rate";
        ratingBase = 2.375;
      } else if (wepType == "Flame Launcher") {
        statTemp = "$n% re-pressurization rate on Alt-fire";
        ratingBase = 2.625;
      } else if (wepType == "Bow") {
        statTemp = "$n% $a draw speed";
        posNegIndex = 6;
        posNegSignIndex = 2;
        ratingBase = 4.875;
      }
      if (mod < -19) {
        mod = -19;
      }
      break;
    case 6:
      // Clip size
      statTemp = "$n% clip size";
      if (explosive || wepType == "Peppergun") {
        mod = mod % 4 + mod / abs(mod);
        ratingBase = 4.25;
        numInterval = 25;
      } else if (wepType == "Shotgun" || wepType == "Scattergun") {
        mod = mod % 6 + mod / abs(mod);
        numInterval = 16;
        if (mod > 0) {
          ratingBase = 2;
        } else {
          ratingBase = 5;
        };
        numInterval = 10;
      } else {
        ratingBase = 2.5;
      }
      break;
    case 7:
      // reserve ammo
      statTemp = "$n% max $l* ammo $w";
      if (mod > 0) {
        ratingBase = .875;
      } else {
        ratingBase = 1.75;
      }
      if (mod < -19) {
        mod = -19;
      }
      if (tfClass == "Medic") {
        ratingMod *= 0.5;
      } else if (wepSlot == "secondary") {
        ratingMod *= 0.875;
      }
      if (tfClass == "Heavy" || tfClass == "Pyro") {
        ratingMod *= 1.25;
      }
      break;
    case 8:
      if (wepType == "Scattergun" || wepType == "Peppergun" ||
          wepType == "Shotgun") {
        statTemp = "$n% $ys per shot";
        ratingBase = 4.5;
      } else if (mod > 0 && !wearable && !coatable &&
                 wepSlot.substr(0, 3) != "PDA" && tfClass != "Scout" &&
                 tfClass != "Soldier" && wepType != "Shotgun") {
        statTemp = "Silent Killer: ";
        tempString =
            silentKiller[distance(
                classList.begin(),
                find(classList.begin(), classList.end() - 1, tfClass))]
                        [distance(weaponSlots.begin(),
                                  find(weaponSlots.begin(),
                                       weaponSlots.end() - 1, wepSlot))];
        if (tempString == "N/A") {
          statTemp = "";
          ratingMod = 0;
        } else {
          statTemp += tempString;
          ratingBase = silentKillerRatings[distance(
              classList.begin(),
              find(classList.begin(), classList.end() - 1,
                   tfClass))][distance(weaponSlots.begin(),
                                       find(weaponSlots.begin(),
                                            weaponSlots.end() - 1, wepSlot))];
        }
      }
      break;
    case 9:
      if (wepSlot != "melee") {
        statTemp = "$n% $a reload time";
        posNegIndex = 6;
        posNegSignIndex = 2;
        ratingBase = 3.25;
      } else {
        statTemp = "$n% $a melee range";
        posNegIndex = 10;
        posNegSignIndex = 2;
        ratingBase = 2.5;
      }
      break;
    case 10:
      // wearer condition stat modifier (ex: +25% increase in move speed while
      // health <50%)
      statTemp = "$n% $a in $s $b";
      posNegSignIndex = 2;
      posNegIndex = 7;
      break;
    case 11:
      // no crits at all
      if (mod < 0) {
        statTemp = "This weapon cannot crit";
        ratingBase = 15;
        if (tfClass == "Sniper" && wepSlot == "primary") {
          statTemp = "No headshots";
          ratingBase = 150;
        }
      } else {
        // wearer condition crit modifier
        statTemp = "$r targets $b";
        ratingMod *= 0.75;
        if (tempBool) {
          statTemp = "Crits targets $b";
          ratingBase = 45;
        }
      }
      break;
    case 12:
      // equalizer / esc plan incremental stat increase / decrease type thing
      // combined with BFB like meter stat
      if (meterStatBoostNum == -2 && mod > 0) {
        statTemp = "$s increases with $t";
      } else {
        statTemp = "$s $as as the user becomes injured";
      }
      ratingMod *= 2;
      posNegIndex = 7;
      break;
    case 13:
      cout << "subStat = " << subStat << "; mod = " << mod << endl;
      if (mod > 0) {
        if (wearable) {
          statTemp = "On $l Hit$i: ";
        } else if (coatable) {
          statTemp = "On Hit Coated Player: ";
        } else if (hasMeter && wepType != "Cleaver") {
          statTemp = "On Hit While $t Is Active: ";
        } else if (wepType == "Lunchbox" || wepType == "Battle Banner") {
          statTemp = "On Hit While Effect Is Active: ";
        } else if (rand() % 2 == 0 && tfClass == "Sniper" &&
                   wepSlot == "primary") {
          statTemp = "On Headshot: ";
          ratingMod *= 0.85;

        } else {
          statTemp = "On Hit$i: ";
        }
        if (wepType == "Sniper Rifle") {
          ratingMod *= 1.25;
        } else if (wepSlot == "melee") {
          ratingMod *= 0.85;
        }
      } else {
        statTemp = "On Miss: ";
        if (wepSlot == "melee") {
          ratingMod *= 0.938;
        }
      }
      statTemp += "$o";
      // cout << "ratingMod = " << ratingMod;
      break;
    case 14:
      if (mod > 0) {
        if (wepType == "Lunchbox" || wepType == "Battle Banner") {
          statTemp = "$wOn Kill While Effect Is Active: ";
        } else if (wepType == "Sapper") {
          statTemp = "On Building Sapped: ";
          ratingMod *= 0.35;
        } else if (wearable) {
          statTemp = "On $l Kill: ";
        } else if (rand() % 3 == 0 && tfClass == "Sniper" &&
                   wepSlot == "primary") {
          statTemp = "On Headshot Kill: ";
          ratingMod *= 0.85;
        } else if (coatable) {
          statTemp = "$wOn Kill Coated Player: ";
        } else if (hasMeter && wepType != "Cleaver") {
          statTemp = "$wOn Kill While $t Is Active: ";
        } else {
          statTemp = "On Kill$i: ";
        }
        if (wepType == "Sniper Rifle") {
          ratingMod *= 1.125;
        } else if (wepSlot == "melee") {
          ratingMod *= 0.5;
        } else {
          ratingMod *= .65;
        }
      } else {
        if (wepSlot == "melee") {
          statTemp = "Per Swing: ";
          ratingMod *= 1.438;
        } else if (wepType == "Sapper") {
          statTemp = "On Sapper Destroyed: ";
          ratingMod *= 1.125;
        } else {
          statTemp = "Per Shot: ";
          ratingMod *= 1.5;
          posNegSignIndex = 2;
        }
      }
      tempBool = true;
      statTemp += "$o";
      break;
    case 15:
      if (mod > 0) {
        if (!hasMeter & !hasAltFire) {
          statTemp = "Alt-Fire: ";
        } else if (hasMeter && !hasAltFire) {
          statTemp = "Pressing your RELOAD key ";
        }
        statTemp += "$f";
      }
      break;
    case 16:
      if (mod > 0) {
        statTemp = "Hold Fire to load up to $n $ys\nRelease Fire to fire all "
                   "loaded $ys";
        numInterval = 1;
        posNegSignIndex = 2;
        ratingBonus -= 25;
        ratingBase = 3.25;
        if (explosive) {
          ratingBase *= 2.5;
        }
        if (rapidFire) {
          numInterval = 4;
        }
      } else if (statFlagPass && explosive) {
        statFlagPass = false;
        statTemp = "Overloading the chamber will cause a misfire";
        ratingBase = -1.5;
      }
      break;
    }
    break;
  case 2:
    type = defense;
    switch (subStat) {
    case 0:
      // damage resistance
      statTemp = "$n% damage $a $w";
      ratingBase = 5.75;
      posNegIndex = 2;
      posNegSignIndex = 2;
      if (mod > 19) {
        mod = 19;
      }
      if (tfClass == "Medic" && mod > 5) {
        mod = 5;
      }
      // cout << "ratingMod = " << ratingMod << "; Press ENTER to continue";
      // cin.ignore();
      break;
    case 1:
      // damage type resistance
      statTemp = "$n% $d damage $a $w";
      posNegIndex = 2;
      posNegSignIndex = 2;
      if (mod > 19) {
        mod = 19;
      }
      break;
    case 2:
      // max HP
      statTemp = "$n max health $w";
      tempInt = rand() % 9 + (2 * mod / abs(mod));
      if (tempInt < 8 && mod > 3) {
        mod = round(mod / 2); // for less of a chance of insane health
      }
      if (tfClass == "Heavy") {
        if (mod > 0) {
          ratingBase = 6.5;
        } else {
          ratingBase = 5.5;
        }
      } else if (tfClass == "Soldier") {
        if (mod > 0) {
          ratingBase = 5.5;
        } else {
          ratingBase = 7;
        }
      } else if (tfClass == "Scout" || tfClass == "Medic" ||
                 tfClass == "Sniper" || tfClass == "Spy") {
        if (mod > 0) {
          ratingBase = 10;
        } else {
          ratingBase = 8.5;
        }
      } else {
        if (mod > 0) {
          ratingBase = 7.5;
        } else {
          ratingBase = 7;
        }
      }
      break;
    case 3:
      // max OVH
      statTemp = "$n% maximum overheal $w";
      if (mod < -20) {
        mod = -20;
      }
      ratingBase = .75;
      // cout << "ratingMod = " << ratingMod << "; Press ENTER to continue";
      // cin.ignore();
      break;
    case 4:
      // HP regen (medic-like)
      statTemp = "Up to $n health $a per second $w";
      ratingBonus += 7.125 * mod / abs(mod);
      ratingBase = 4.125;
      posNegIndex = 5;
      tempInt = mod;
      mod = mod % 12 + mod / abs(mod);
      numInterval = 1;
      if (mod == 0) {
        mod = tempInt / abs(tempInt);
      }
      if (mod < 0 || mod < -5 && tfClass != "Medic") {
        ratingBase = 6.5;
        ratingBonus -= 3.375;
      }
      break;
    }
    break;
  case 3:
    type = utility;
    switch (subStat) {
    case 0:
      statTemp = "$n% movement speed $w";
      mod = mod % 9 + (2 * mod / abs(mod));
      ratingBase = 2.875;
      if (mod < 0) {
        ratingBase = 3.375;
      }
      if (tfClass == "Heavy") { // movement change matters for heavy
        ratingBase *= 1.5;
      } else if (tfClass == "Medic" || tfClass == "Scout" ||
                 tfClass == "Spy") { // movement reliant
        ratingBase *= 1.25;
      } else if (tfClass == "Sniper" ||
                 (tfClass == "Pyro" &&
                  mod > 0)) { // sniper barely moves; pyro just deserves it
        ratingBase *= 0.625;
      }
      if (mod < -19) {
        mod = -19;
      }
      break;
    case 1:
      statTemp = "This weapon deploys $n% $a";
      if (wepSlot == "primary") {
        ratingBase = 0.5;
      } else if (mod < 0) {
        ratingBase = 1.375;
      } else {
        ratingBase = 1.125;
      }
      if (mod < -19) {
        mod = -19;
      }
      posNegIndex = 6;
      posNegSignIndex = 2;
      break;
    case 2:
      statTemp = "This weapon holsters $n% $a";
      if (mod < 0) {
        ratingBase = 0.938;
      } else if (wepSlot == "primary") {
        ratingBase = 1.063;
      } else if (wepSlot == "secondary" && !coatable && wepType != "Cleaver") {
        ratingBase = 0.75;
      } else {
        ratingBase = 0.5;
      }
      if (mod < -19) {
        mod = -19;
      }
      posNegIndex = 6;
      posNegSignIndex = 2;
      break;
    case 3:
      statTemp = "$n% switch speed $w";
      ratingBase = 1.625;
      if (mod < -19) {
        mod = -19;
      }
      // cout << "ratingMod = " << ratingMod << "; Press ENTER to continue";
      // cin.ignore();
      break;
    case 4:
      // the greatest & most op stat
      statTemp = "$n% jump height $w";
      ratingBase = 0.25;
      if (mod < -19) {
        mod = -19;
      }
      // cout << "ratingMod = " << ratingMod << "; Press ENTER to continue";
      // cin.ignore();
      break;
    case 5:
      // hp from things
      statTemp = "$n% health from $h $w";
      ratingBase = 5.5;
      if (whenActive) {
        if (mod > 0) {
          ratingMod *= 1.2; // offset penalty
        } else {
          ratingMod *= 0.5;
        }
      }
      if (mod < -19) {
        statTemp = "No health from $h $w";
        ratingBonus -= 5;
      }
      // cout << "ratingMod = " << ratingMod;
      break;
    case 6:
      // ammo from things
      statTemp = "$n% ammo from $j $w";
      ratingBase = 3.5;
      if (mod > 5) {
        ratingBase = 0.625;
        ratingBonus += 15;
      }

      if (tfClass == "Medic") {
        ratingMod *= 0.5;
      } else if (whenActive) {
        if (mod > 0) {
          ratingMod *= 1.1;
        } else {
          ratingMod *= 0.375;
        }
      }
      if (mod < -19) {
        mod = -20;
        statTemp = "No ammo from $j $w";
      }
      break;
    case 7:
      statTemp = "$n jumps ";
      if (wearable) {
        statTemp += "$w";
      } else {
        statTemp = "$w" + statTemp + "while deployed";
      }
      tempInt = mod % 4 + 1;
      // limits amount of extra jumps
      if (mod < 0 and tfClass == "Scout") {
        mod = round(mod / 10);
        ratingMod *= 1.25;
      } else if (mod > 0) {
        mod = round(mod / 6);
      }
      if (mod == 0) {
        mod = tempInt / abs(tempInt);
      }
      if ((mod < 0 && tfClass != "Scout")) {
        statTemp = "Wearer cannot jump";
        ratingMod *= 3.5;
        if (tfClass == "Heavy") {
          ratingMod *= 1.5;
        } else if (tfClass == "Scout") {
          ratingMod *= 2.25;
        }
        mod = -1;
      } else if (abs(mod) == 1 && tfClass == "Scout") {
        statTemp.erase(statTemp.find("jumps") + 4, 1);
      }
      numInterval = 1;
      ratingBase = 3.25;
      if (tfClass == "Scout") {
        ratingBase += 0.75;
      }
      break;
    case 8:
      statTemp = "$n% $a in push force taken from damage and airblast $w";
      mod *= -1;
      posNegSignIndex = 2;
      ratingBase = -0.75;
      posNegIndex = 7;
      if (tfClass == "Heavy") {
        ratingBase = -0.375;
      }
      // cout << "ratingMod = " << ratingMod << "; Press ENTER to continue";
      // cin.ignore();
      break;
    case 9:
      if (mod > 0) {
        statTemp = "+$n capture rate $w";
        posNegSignIndex = 2;
        ratingBase = 6.75;
        mod %= 3;
        mod += 1;
        if (tfClass == "Scout") {
          ratingMod = 2.25;
          if (mod == 3) {
            mod--;
          }
        } else if (tfClass == "Medic" &&
                   (wepSlot == "secondary" || !whenActive)) {
          ratingMod *= 2;
        } else if (tfClass == "Heavy") {
          ratingMod *= 1.375;
        }
        numInterval = 1;
        if (mod == 0) {
          mod = 1;
        }
      } else {
        if (mod < 10 && tfClass == "Scout") {
          statTemp = "-1 capture rate $w";
          ratingBase = 25;
        } else {
          statTemp =
              "$wWearer cannot capture control points or push the payload cart";
          ratingBase = 75;
        }
      }
      break;
    }
    break;
  case 4:
    type = projectile; // and explosives
    switch (subStat) {
    case 0:
      statTemp = "$n% projectile speed";
      ratingBase = 2.188;
      if (mod < -19) {
        mod = -19;
      }
      if (wepType.substr(0, 5) == "Flame") {
        ratingBase *= 0.25;
      }
      if (mod < 0) {
        ratingBase *= 1.25;
      }
      break;
    case 1:
      if (mod > 0) {
        statTemp = "$y penetrates enemy targets";
        if (explosive) {
          ratingBonus -= 10;
          ratingBase = 4.5;
          statTemp += "\nDirect hits do $n% damage\n$y explosions can deal "
                      "additional damage";
          posNegSignIndex = 2;
          mod %= 3;
          mod += 2; // 2-4
          numInterval = 25;
        } else if (coatable) {
          ratingBase = -1;
        } else if (wepType == "Crossbow") {
          ratingBase = 8;
          statTemp = "Syringe penetrates targets";
        } else {
          ratingBase = 7.5;
        }
      } else {
        tempString = "+$n degrees random projectile deviation";
        posNegSignIndex = 2;
        ratingBase = 10;
        mod = round(mod / 2.5);
        numInterval = 1;
      }
      break;
    case 2:
      if (mod > 0) {
        statTemp = "Projectile cannot be reflected";
        if (explosive) {
          ratingBase = 50;
        } else if (wepType.substr(0, 5) == "Flame") {
          statTemp = "On Successful Projectile Reflect: $o";
          tempBool = true;
          ratingMod *= 0.85;
          ratingBase = 1;
        } else if (coatable) {
          ratingBase = 25;
        } else {
          ratingBase = 15;
        }
      } else {
      }
      break;
    case 4:
      statTemp = "$n% blast radius";
      if (coatable || wepType == "Battle Banner") {
        statTemp = "$n% area of effect radius";
        ratingMod *= 0.875;
      }
      ratingBase = 4.375;
      break;
    case 5:
      // statTemp = "$n% blast radius $b";
      // ratingBase = 4.5;
      break;
    case 6:
      statTemp = "$n0% $ad air control when blast jumping";
      if (mod > 0) {
        ratingBase = 1.875;
      } else if (tfClass == "Soldier") {
        ratingBase = 4.375;
      } else if (tfClass == "Pyro") {
        ratingBase = 0.875;
      } else if (wepType == "Grenade Launcher") {
        ratingBase = 2.125;
      } else {
        ratingBase = 3.75;
      }
      posNegIndex = 7;
      posNegSignIndex = 2;
      break;
    case 7:
      statTemp = "$n% self damage force";
      if (tfClass == "Soldier" && wepType == "Rocket Launcher") {
        ratingBase = 6.5;
      } else if (tfClass == "Demoman" && wepType == "Stickybomb Launcher") {
        ratingBase = 3.5;
      } else if (tfClass == "Demoman" && wepType == "Grenade Launcher") {
        ratingBase = 1.5;
      } else {
        ratingBase = 0.5;
      }
    case 8:
      statTemp = "Launched $ys $a on surfaces";
      posNegIndex = 9;
      ratingBase = 85;
      if (mod > 0 && tfClass != "Demoman") {
        statTemp =
            "Able to destroy enemy stickybombs"; // there will be this stat
                                                 // repeated in demo specific
                                                 // stats since he cannot get
                                                 // this one in this context
        ratingBase = 45;
      } else if (wepType == "Stickybomb Launcher") {
        statTemp = "Stickybombs $a on surfaces after $n seconds";
        posNegSignIndex = 2;
        mod %= 10;
        mod++;
        if (mod == 1) {
          statTemp.pop_back();
        }
        ratingMod *= -1;
        numInterval = 1;
        ratingBonus -= 250;
        ratingBase = 20;
        if (mod < 0) {
          ratingBonus -= 150;
        }
      }
    case 9:
      if (mod > 0 && wepType != "Stickybomb Launcher") {
        statTemp = "$ys have a fuse time of 1 second; fuses can be primed to "
                   "explode earlier by holding down the fire key.\n$ys push "
                   "players back on impact\nDouble Donk! Explosions after a "
                   "$y's impact will deal $r to impact victims.";
        if (wepType == "Rocket Launcher") {
          ratingMod *= 0.375;
        } else if (wepType == "Flare Gun") {
          ratingMod *= 0.75;
        } else {
          ratingMod *= 0.875;
        }
      } else if (statFlagPass) {
        statFlagPass = false;
        statTemp = "$ys do not explode on impact";
        ratingBase = 10;
      }
    }
    if (coatable) {
      ratingMod *= 0.75;
    }
    break;
  case 5:
    type = exclusive;
    switch (subStat) {
    case 0:
      if (mod > 0) {
        statTemp = "On Equip: Visit Pyroland";
      } else if (statFlagPass) {
        statFlagPass = false;
        statTemp = "Only visible in Pyroland";
      }
      ratingMod = 0;
      break;
    case 1:
      statTemp = "Extinguishing teammates restores $n health";
      posNegSignIndex = 2;
      numInterval = 1;
      ratingBase = 0.5;
      if (wepSlot == "primary" && mod > 0) {
        mod += 20;
        ratingBonus -= 10;
      } else if (wepSlot == "primary" && mod < 0) {
        mod *= -1;
        ratingBonus -= 10;
        statTemp.insert(statTemp.find("$n"), "only ");
      } else if (wepSlot != "primary") {
        if (mod > 10) {
          statTemp = "Alt-Fire: Extinguish teammates to gain gauranteed $r";
          ratingMod *= 0.05;
        } else if (mod > 0) {
          statTemp = "Alt-Fire: Extinguishes teammates\n" + statTemp;
          ratingMod *= 0.25;
        } else if (!coatable) {
          statTemp = "On Hit Burning Player: Extinguishes target";
        }
      }
      break;
    case 2:
      statTemp = "$n% airblast cost";
      if (mod > 0) {
        mod = round(mod / -2);
        numInterval = 10; // 10-100
        ratingBase = -1.875;
      } else {
        mod = round(mod / -1.666);
        numInterval = 25; // 25-300
        ratingBase = -2.25;
      }
      break;
    case 3:
      statTemp = "$n% afterburn damage $a";
      posNegIndex = 1;
      mod = (mod % 4 + 1) * mod / abs(mod);
      numInterval = 25; // afterburn does 4 damage
      break;
    case 4:
      statTemp = "$n% $a in turning control while charging";
      if (mod > 10) {
        statTemp = "Full turning control while charging";
        ratingBase = 75;
      } else if (mod < -10) {
        statTemp = "No turning control while charging";
        ratingBase = 35;
      } else {
        ratingBase = 1;
        posNegIndex = 7;
        mod = (mod % 10 + 2) * mod / abs(mod);
        numInterval = 100;
      }
      break;
    case 5:
      statTemp = "$n max stickybombs out";
      if (mod > 0) {
        mod %= 10;
      } else {
        mod %= -6;
      }
      mod += mod / abs(mod);
      numInterval = 2;
      ratingBase = 10;
      break;
    case 6:
      if (mod < 0) {
        statTemp = "Detonates stickybombs near the crosshair and directly "
                   "under your feet";
        ratingBase = 5;
      } else {
      }
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
      mod = (mod % 10 + 1) * mod / abs(mod);
      if (abs(mod) == 10) {
        tempString =
            "1 " + tempString.substr(tempString.find("sec"), string::npos);
      }
      break;
    case 9:
      statTemp = "Charge time $ad by $n%";
      posNegIndex = 7;
      posNegSignIndex = 2;
      mod *= -1;
      ratingBase = -1.5;
      numInterval = 10;
      break;
    case 10:
      if (mod > 0) {
        statTemp = "Up to $n% damage based on charge";
        ratingBase = 2;
      }
      break;
    case 11:
      statTemp =
          "$n% $a in charge impact damage"; // the splendid screen's damage
                                            // bonus is worded differently,
                                            // understandably, plus damage bonus
                                            // is blacklisted for wearables so...
      posNegIndex = 7;
      ratingBase = 2;
      break;
    case 12:
      if (mod > 0 && wepType == "Shield") {
        statTemp =
            "$n% increase in charge impact damage with each head taken while "
            "the eyelander is equipped"; // hidden splendid stat but...
        posNegIndex = 2;
        ratingBase = 2.5;
        mod = (mod % 10 + 2) * mod / abs(mod);
      } else {
        if (wepType == "Shield") {
          statTemp = "Taking damage while shield charging reduces remaining "
                     "charging time";
          ratingBase = 25;
        } else {
          statTemp = "Taking damage during $t reduces remaining $t time";
          ratingBase = 50;
          if (meterMod != 0) {
            ratingMod = meterMod;
          }
          if (tfClass == "Sniper" || tfClass == "Spy") {
            ratingMod *= 0.85;
          } else if (tfClass == "Scout" || tfClass == "Engineer") {
            ratingMod *= 0.938;
          } else if (tfClass == "Pyro" || tfClass == "Heavy") {
            ratingMod *= 1.5;
          }
        }
      }
      break;
    case 13:
      statTemp = "$n% $a in $t recharge rate";
      posNegIndex = 7;
      ratingBase = 4.938;
      break;
    case 14:
      statTemp = "0.$n sec $a in charge duration";
      posNegIndex = 7;
      posNegSignIndex = 2;
      mod = (mod % 10 + (mod / abs(mod)));
      if (abs(mod) == 10) {
        tempString = "1 sec $a in charge duration";
      }
      break;
    case 15:
      if (mod > 10 && wepType == "Shield" ||
          (tfClass == "Demoman" && wepSlot == "melee")) {
        statTemp =
            "Ammo boxes collected are converted to health"; // old persian pers
                                                            // stat
        ratingBase = 50;
      } else if (mod > 0) {
        statTemp =
            "Ammo boxes collected also refill your $t meter"; // new persian
                                                              // pers stat
        ratingBase = 30;
      } else {
      }
      break;
    case 16:
      statTemp = "$n% $a spin up time";
      ratingBase = 2.5;
      posNegIndex = 6;
      posNegSignIndex = 2;
    case 17:
      if (mod > 0) {
        statTemp = "Creates a ring of flames ";
        if (wepType == "Minigun") {
          statTemp += "while spun up";
          ratingBase = 5;
        } else if (wepType == "Battle Banner") {
          statTemp += "while banner is deployed";
          ratingBase = 7.5;
        } else if (wepType == "Shield" && tfClass == "Demoman") {
          statTemp.insert(9, "trail of flames while charging and a ");
          statTemp += "on charge impact";
          ratingBase = 25;
        } else if (wearable) {
          statTemp += "while moving";
          ratingBase = 25;
        } else if (wepType == "Flare Gun") {
          statTemp = "On Hit: c" + statTemp.substr(1, string::npos) +
                     "around the target that can ignite enemies";
          ratingBase = 15;
        } else if (wepType == "Gas Canister") {
          statTemp = "On Impact: All enimies in area of effect radius are "
                     "engulfed in flames";
          ratingBase = 7.5;
        } else {
          statTemp += "when firing";
          ratingBase = 15;
          if (tfClass == "Pyro") {
            ratingBase = 2.5;
          }
        }
      } else if (wepType == "Minigun") {
        statTemp = "Consumes an additional $n ammo per second while spun up";
        ratingBase = 8.5;
        posNegSignIndex = 2;
        numInterval = 1;
        ratingBonus -= 6.5;
      }
      break;
    case 18:
      if (mod > 0) {
        if (mod % 2 == 0) {
          statTemp = "Increased $s for each sentry kill and and assist";
        } else {
          statTemp = "Gain 2 revenge crits for each sentry kill and 1 for each "
                     "sentry assist when your sentry is destroyed";
        }
      } else {
        statTemp = "Per Shot: -$n ammo";
        posNegSignIndex = 2;
        if (tfClass == "Engineer") {
          statTemp += "\nUses metal for ammo";
          numInterval = 3;
          ratingBase = 8.5;
        } else {
          mod = ceil(mod / 5) - 1;
          numInterval = 1;
          ratingBase = 2.5;
        }
      }
      break;
    case 19:
      statTemp = "$u build speed $ad by $n%";
      tempBool = true;
      if (mod > 0) {
        numInterval = 20;
        ratingMod = .15;
      } else {
        ratingMod = .25;
      }
      if (mod < -19) {
        mod = -19;
      }
      break;
    case 20:
      if (mod > 0 && coatable) {
        statTemp += "$ys do $n damage on ";
        if (statFlagPass) {
          statFlagPass = false;
          statTemp += "player contact";
          ratingBonus += 0.5;
        } else {
          statTemp += "direct impact";
        }
        ratingBase = 0.875;
        numInterval = 3;
        posNegSignIndex = 2;
      } else {
        statTemp = "Replaces the Sentry with a Mini-Sentry";
        ratingBase = 50;
      }
      break;
    case 21:
      statTemp = "Construction hit speed boost $ad by $n%";
      posNegIndex = 7;
      numInterval = 10;
      ratingBase = 2.5;
      break;
    case 22:
      statTemp = "While active, movement speed $as based on ÜberCharge "
                 "percentage (up to $n%)";
      posNegIndex = 6;
      ratingBase = 1;
      mod = mod % 9 + 2;
      break;
    case 23:
      statTemp = "$n% ÜberCharge build rate";
      ratingBase = 5;
      break;
    case 24:
      if (mod > 0) {
        statTemp = "+1 Organ on hit\nA percentage of your ÜberCharge level is "
                   "retained on death, based on the number of organs harvested "
                   "($n% per). Total ÜberCharge retained on spawn caps at 80%";
        ratingBase = 3.5;
      } else {
      }
      break;
    case 25:
      statTemp = "$n% charge rate";
      ratingBase = 3.5;
      break;
    case 26:
      if (mod > 0) {
        statTemp = "Nature's Call: Scoped headshots always mini-crit and "
                   "reduce the remaining cooldown of Jarate by $n* "
                   "seconds.\nScoped shots can extinguish players";
        ratingBase = 45;
      } else {
      }
      break;
    case 27:
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
      if (mod > 10) {
        statTemp = "On Scoped Hit: $o";
        ratingMod *= 1.5;
      } else if (mod > 0) {
        statTemp = "On Full Charge: $o";
      } else {
      }
      break;
    case 29:
      if (mod > 0) {
        statTemp = "No flinching $b*";
        posNegSignIndex = 2;
        ratingBase = 2.375;
      } else {
      }
      break;
    case 30:
      statTemp = "$n% cloak duration";
      ratingBase = 3.375;
      break;
    case 31:
      statTemp = "$n% cloak drain rate"; // is this the same thing idk who knows
                                         // I think kinda but like drain rate is
                                         // efficency and duration is like how
                                         // much cloak you have? eh whateva
      mod *= -1;
      ratingBase = -3.5;
      if (wepType == "Invis Watch") {
        ratingBonus += invisWatchFeignDuration;
        invisWatchFeignDuration *= (1 - mod / 20);
        ratingBonus -= invisWatchFeignDuration; // no clue if this will work how
                                                // I intend it to lmao
        cout << "invisWatchFeignDuration = " << invisWatchFeignDuration << endl;
      }
      break;
    case 32:
      statTemp = "$n% cloak regen rate";
      numInterval *= 2;
      ratingBase = 4.5;
    case 33:
      if (tfClass == "Engineer") {
        statTemp = "$n% metal from ammo boxes & dispensers";
      } else {
        statTemp = "$n% cloak meter from ammo boxes";
      }
      ratingBase = 3.5;
      break;
    case 34:
      if (mod > 0) {
        if (wepType == "Invis Watch") {
          statTemp = "On Backstab: refills $n% of your cloak meter";
          ratingBase = 3.938;
        } /* else {
                 statTemp = "On Backstab: $o";
                 ratingMod *= 0.25;
tempBool = true;
         }*/
      } else {
        statTemp = "No cloak meter from ammo boxes when invisible";
        ratingBase = 4.5;
      }
      break;
    case 35:
      if (mod > 0) {
        statTemp = "Upon a successful backstab against a human target, you "
                   "rapidly disguise as your victim";
        ratingBase = 8.75;
      } else {
        statTemp = "Disguises require (and consume) a full cloak meter";
        ratingBase = 12.5;
      }
      break;
    // past this point the stats arent sorted by class (If I did re-sort stats
    // I'd have to recheck the blacklist and it'd be a pain) I might re-sort them
    // when v.1.0 comes out with the UI and everything.
    case 36:
      if (mod > 10) {
        statTemp = "$t meter builds with damage done and / or time";
        ratingBase = 15;
      } else if (mod > 0) {
        statTemp = "$t meter builds with damage done";
        ratingBase = 15;
      } else {
        statTemp = "Spawning and resupply do not affect the $t meter\n$t meter "
                   "starts empty";
        ratingBase = 50;
      }
      break;
    case 37:
      if (mod > 0) {
        statTemp = "Press your reload key to choose to teleport to spawn or "
                   "your exit teleporter";
        ratingBase = 50;
      } else {
        statTemp = "Wearer cannot carry buildings";
        ratingBase = 125;
      }
      break;
    case 38:
      statTemp = "$n% $a repair rate";
      break;
    case 39:
      statTemp = "$n% metal cost when constructing or upgrading $us";
      mod *= -1;
      ratingMod *= -0.25;
      break;
    case 40:
      if (mod > 0) {
        statTemp = "Long distance hits reduce recharge time";
        ratingBase = 15;
      } else {
        statTemp = "Bleed is only applied on long distance hits";
        ratingBase = 50;
      }
    case 41:
      statTemp = "$n% ÜberCharge rate on Overhealed patients";
      ratingBase = 3.5;
      break;
    case 42:
      statTemp = "$n% Overheal build rate";
      ratingBase = 4.5;
      break;
    case 43:
      if (mod > 0) {
        statTemp = "Mirror the blast jumps and shield charges of patients.";
        ratingBase = 2.5;
      } else {
        statTemp = "ÜberCharge rate decreases by $n% while healing a patient "
                   "for more than 5 seconds";
        mod %= 7;
        mod += 2;
        ratingBase = 3.5;
        posNegSignIndex = 2;
      }
      break;
    case 44:
      statTemp = "$n% $a spooky";
      ratingMod = 0;
      posNegIndex = 4;
      break;
    }
    break;
  case 8:
    type = constructor;
    switch (subStat) {
    case 0:
      cout << "Lunchbox\n";
      tempInt = mod;
      // how much hp
      mod *= rand() % 12;
      mod %= 28; // 0 is possible
      if (mod > 7 && tfClass == "Heavy") {
        mod -= 7;
        statTemp = "Eat to regain up to " + to_string(mod * 15) +
                   " health."; // no '%' and use of '$' flags is intentional
        ratingBonus += mod * 5;
      }
      // effect
      if (tempInt < 10 || tfClass == "Scout") {
        mod *= rand() % 25; // attempt to re-randomize lol
        mod %= 30;
        mod += 11; // min of 10, max of 40
        if (statTemp != "") {
          statTemp += "\n";
        }
        if (mod > 10) {
          statTemp += "After consuming, $n% $s for ";
        } else {
          statTemp += "After consuming, $n% $s and $s for ";
          mod *= 0.5;
          ratingBonus += 15;
        }
        statTemp += to_string(mod) + " seconds";
        lunchboxDuration = mod;
        ratingMod *= mod * 0.15;
        ratingBonus += mod * 0.25;
      } else {
        lunchboxDuration = 0;
      }
      mod = tempInt;
      break;
    case 1: // shield
      cout << "Shield\nmod = " << mod << endl;
      tempInt = mod * 10;
      tempInt %= 77;
      posNegSignIndex = 2;
      if (tempInt > 40) { // rare bullet damage
        tempInt = mod % 13 + 2;
        tempInt = round(tempInt / 3) * 5;
        if (tempInt == 35) {
          tempInt = 33;
        } else if (tempInt == 65) {
          tempInt = 66;
        }
        if (tempInt > 5) {
          statTemp += to_string(tempInt) + "% bullet damage resistance $w\n";
          ratingBonus += 4.25 * (tempInt / 5);
        }
      }
      tempInt = mod % 16 + 3;
      tempInt = round(tempInt / 1.5) * 5;
      if (tempInt == 35) {
        tempInt = 33;
      } else if (tempInt == 65) {
        tempInt = 66;
      }
      if (tempInt != 0) {
        statTemp += to_string(tempInt) + "% explosive damage resistance $w\n";
        ratingBonus += 3.5 * (tempInt / 5);
      }
      mod = mod % 13 + 6;
      statTemp += "$n% fire damage resistance $w";
      ratingBase = 2.5;
      cout << "mod = " << mod << endl;
      break;
    case 2: // coatables
      posNegSignIndex = 2;
      tempInt = rand() % 5;
      statTemp = coatEffects[tempInt];
      if (tempInt == 0 || tempInt == 4) {
        ratingBonus += coatBonus[tempInt] * mod;
        tempBool = true;
      } else {
        ratingBonus += coatBonus[tempInt];
      }
      if (tempInt == 1 || tempInt == 2) {
        ratingMod *= 0.688;
      } else if (tempInt == 3 && tfClass != "Pyro") {
        ratingBonus += 7.5;
      }
      if (mod > 3 && tfClass != "Pyro" && tempInt != 3) {
        statTemp += "\nCan be used to extinguish fires\nExtinguishing "
                    "teammates reduces cooldown by ";
        posNegSignIndex = 2;
        statTemp += to_string(mod * numInterval) + "%";
        ratingBonus += mod * 0.375;
        if (!tempBool) {
          mod = 1;
          numInterval = 10;
        }
      }
      cout << ".\n";
      break;
    case 3: // banners
      statTemp = "Provides a" + bannerBuffTypes[bannerBuffTypeIndex] +
                 " buff for nearby teammates\n";
      if (mod > 10) {
        statTemp += "Build Rage with damage done and / or taken";
      } else {
        statTemp += "Build Rage with damage done.";
      }
      statTemp += "\nWhile the buff is active, all nearby teammates recieve:";
      break;
    case 4: // meters
      cout << "mod = " << mod << endl;
      if (mod > 0) {
        statTemp = "Build $t ";
        tempInt = rand() % 6;
        if (tempInt == 5) {
          tempInt += distance(begin(classList),
                              find(begin(classList), end(classList), tfClass));
          if (tfClass == "Demoman") {
            tempInt -= 2;
          }
        }
        tempString = meterBuildMethods[tempInt];
        ratingBase = meterBuildMethodRatings[tempInt];
        meterMod = meterBuildMethodRatings[tempInt] * mod * 0.15;
        statTemp += tempString + " (Meter fills at ";
        tempInt = round(ratingBase * (25 - mod) / 25);
        if (statTemp.substr(0, 6).find("while") != string::npos) {
          tempInt = round(tempInt * 2.5);
        } else if (tempString.substr(0, 3).find("on") == string::npos) {
          // no 'on'
          cout << "grumbe the goo\n";
          tempInt *= 25;
        }
        statTemp += to_string(tempInt);
        if (statTemp.substr(0, 6).find("while") != string::npos) {
          statTemp += "seconds of";
        }
        statTemp += tempString.substr(tempString.find(" "));
        if (statTemp.find("and", statTemp.find("and") + 3) != string::npos) {
          statTemp.insert(statTemp.find("and", statTemp.find("and") + 3) + 4,
                          to_string(int(round(tempInt / 8.5) * 10)));
        } else if (statTemp.find("while", 16) != string::npos) {
          statTemp.erase(statTemp.find("while", 16), string::npos);
        }
        statTemp += ")";
        if (rand() % 100 < 33) { // active or passive
          statTemp += "\n";
          if (mod <= 10) {
            statTemp += "When $t is full, ";
          }
          if (hasAltFire) {
            statTemp += "press 'Reload' ";
          } else {
            statTemp += "Alt-Fire ";
          }
          tempInt = (rand() % mod + 1);
          statTemp += "to activate $t for " + to_string(tempInt) + " seconds";
          meterStatBoostNum = mod % 4 + 1;
          meterMod *= tempInt * 0.35;
          ratingMod = 0;
        } else {
          meterStatBoostNum = -2;
          statTemp += "\n$s increases with $t ";
          tempInt = round(mod / 3.333) + 2; // 2-8
          statTemp += "(up to +%" + to_string(tempInt * 5) + ")";
          meterMod *= tempInt / 5;
          // mod = meterMod / 1.875;
        }
        cout << "(meter) mod = " << mod << "; tempInt = " << tempInt
             << "; meterMod = " << meterMod
             << "; meterStatBoostNum = " << meterStatBoostNum
             << "\nstatTemp = " << statTemp << endl;
        if (meterMod > 1) {
          meterMod = 1;
        }
      } else if (statFlagPass) { // error here?
        statFlagPass = false;
        cout << "ratingMod = " << ratingMod << endl;
        statTemp = "$t reduced ";
        tempInt = rand() % 4;
        if (tempInt == 3) {
          if (tfClass == "Soldier" || tfClass == "Pyro" ||
              tfClass == "Demoman") {
            tempInt = 0;
          } else {
            tempInt +=
                distance(begin(classList),
                         find(begin(classList), end(classList), tfClass));
          }
        }
        tempString = meterLossMethods[tempInt];
        if (tempString == "" || tempString == "n/a" ||
            (tempString == "on miss" && rapidFire)) {
          tempString = "when hit";
        }
        cout << "SF#14 - debug flag - 1";
        ratingBase = meterLossMethodRatings[tempInt];
        statTemp += tempString + " (Full meter empties at ";
        tempInt = round(ratingBase * (22 + mod) / 7.5);
        ratingMod = tempInt / 10;
        tempBool = false;
        cout << "SF#14 - debug flag - 2";
        if (tempString.substr(0, 3).find("on") == string::npos) {
          tempInt *= 5;
        } else {
          tempBool = true;
        }
        if (tempString.find("build") != string::npos) {
          tempInt = round(tempInt / 10);
        }
        if (tempString.find("$n") != string::npos) {
          tempString.replace(tempString.find("$n"), 2,
                             to_string(abs(mod % -20 + 25)));
          ratingBase += mod / 5;
        }
        cout << "SF#14 - debug flag - 3";
        if (tempString.find("time") != string::npos) {
          ratingBonus += 5 * (mod / abs(mod));
          tempInt *= 2;
        }
        if (tempString.substr(0, 6).find("while") != string::npos) {
          tempInt = round(tempInt / 3);
        }
        statTemp += to_string(tempInt) + " ";
        cout << "SF#14 - debug flag - 4";
        if (tempString.find("time") != string::npos) {
          statTemp += "seconds";
        } else if (statTemp.find("while") != string::npos) {
          tempInt = tempString.find(" ");
          if (tempInt > tempString.size()) {
            tempInt = 0;
          }
          statTemp += "seconds of" + tempString.substr(tempInt);

        } else if (tempString.find("building") != string::npos) {
          statTemp += "buildings";
        } else if (tempString.find("when hit") != string::npos) {
          statTemp += "damage";
        } else {
          statTemp +=
              toPlural(tempString.substr(tempString.find(" ") + 1), tempBool);
        }
        statTemp += ")";
        cout << "(meter) mod = " << mod << "; tempInt = " << tempInt
             << "; meterMod = " << meterMod
             << "; meterStatBoostNum = " << meterStatBoostNum
             << "\nstatTemp = " << statTemp << endl;
      }
      tempBool = false;
      if (ratingMod == 0) {
        ratingBonus +=
            0.001 *
            (mod / abs(mod)); // to prevent bugs (I think this fixes it lol)
      }
      break;
    case 5: // counter (heads, etc)
      meterStatBoostNum = mod % 4 + 1;
      meterMod = mod * 0.088;
      cout << "(counter) mod = " << mod << "; tempInt = " << tempInt << endl;
      break;
    case 6: // medigun
      statTemp = "ÜberCharge provides ";
      tempInt = rand() % 4;
      if (tempInt == 1) {
        ratingMod *= 0.188;
      } else if (tempInt == 2) {
        ratingBonus += 2.5;
        if (mod > 10) {
          mod = 10;
        }
      } else if (tempInt == 3) {
        mod += 10;
        if (mod > 19) {
          mod = 19;
        }
        ratingBonus += 5 + ((mod % 5 + 2) * 5);
        statTemp =
            "While healing, provides you and your target with a constant " +
            to_string((mod % 5 + 2) * 5) +
            "% resistance to the selected damage type.\nPress your reload key "
            "to cycle through resist types.\n" +
            statTemp;
      }
      statTemp += uberEffects[tempInt] + " to the Medic and Patient";
      break;
    case 7: // invis watch
      ratingBonus -= 1;
      cout << "mod = " << mod << endl;
      if (mod > 0) {
        invisWatchCloakTypeIndex = rand() % 3;
        statTemp = "Cloak Type: ";
        statTemp += cloakTypes[invisWatchCloakTypeIndex];
        if (invisWatchCloakTypeIndex == 2) {
          ratingBonus += 25;
          invisWatchFeignDuration = (mod + 15) / 4 + 2;
          if (invisWatchFeignDuration > 10) {
            invisWatchFeignDuration = 10;
          } // 6.25s - 10s base duration, some stats affect this though
          tempString =
              to_string(round(((invisWatchFeignDuration / 4) - 1) * 20) * 5);
          while (tempString.back() == '0' || tempString.back() == '.') {
            cout << "wl0.";
            tempString.pop_back();
          }
          if (stoi(tempString) >= 10) {
            statTemp += "\n+" + tempString + "% cloak duration";
          }
          ratingBonus += 9.375 * invisWatchFeignDuration;
          cout << "invisWatchFeignDuration = " << invisWatchFeignDuration
               << endl;
        } else {
          ratingBonus += cloakTypeRatings[invisWatchCloakTypeIndex];
        }
        cout << "statTemp = \"" << statTemp << "\"\n";
      } else if (statFlagPass && invisWatchCloakTypeIndex == 2) {
        statFlagPass = false;
        if (abs(mod) > 10) {
          invisWatchFeignDuration += invisWatchFeignDuration / 2;
          ratingBonus += 2.5 + 9.375 * invisWatchFeignDuration;
          statTemp = "-25% cloak meter when Feign Death is activated";
        } else if (abs(mod) < 4) {
          invisWatchFeignDuration /= 2;
          ratingBonus -= 2.5 + 9.375 * invisWatchFeignDuration;
          statTemp = "-75% cloak meter when Feign Death is activated";
        } else {
          statTemp = "-50% cloak meter when Feign Death is activated";
        }
        ratingBonus -= 5;
        cout << "invisWatchFeignDuration = " << invisWatchFeignDuration << endl;
      }
      break;
    }
  }
  // cout << "statTemp = " << statTemp << endl;
  statString = statTemp; // copy template to main string
  if (mod > 0) {
    upside = 0;
  } else {
    upside = 1;
  };
  if (posNegSignIndex < 0) {
    posNegSignIndex = upside;
  }
  // pre-wordflag stat wording checks
  if ((wepType == "Lunchbox" || meterStatBoostNum > 0) && statCat != 8 &&
      !(statCat == 1 && subStat == 15)) {
    tempString.clear();
    transform(statString.begin(), statString.end(), tempString.begin(),
              ::tolower);
    tempInt = tempString.find("while");
    if (tempInt != string::npos) {
      cout << "'while' condition detected on '" << wepType
           << "!' statString = " << statString;
      statString = statString.substr(0, tempInt) + "$w";
      cout << "; new statString = " << statString << "...";
    }
  }
  // on hit conditions, rewards & stat / alt-fire inserts
  while (statString.find("$i") != string::npos) {
    if (usedDynamicStatEntries[0][3] < 0) {
      tempInt = rand() % 30;
    } else {
      tempInt = usedDynamicStatEntries[0][3];
    }
    if (tempInt < 7) {
      tempString = " " + hitConditions[tempInt];
      ratingMod *= hitConditionMods[tempInt];
      if (tempInt == 1 && wepSlot == "melee") {
      }
    } else {
      tempString = "";
    }
    cout << endl
         << hitConditions[0] << endl
         << tempInt << hitConditions[tempInt] << endl
         << tempString << endl;
    statString.replace(statString.find("$i"), 2, tempString);
  }
  while (statString.find("$o") != string::npos) {
    bool onKill = false;
    tempInt = rand();
    int stringIndex = -1;
    bool invalid;
    if (mod > 0) {
      tempInt %= 16;
      if (tempBool) { // on kill only stats
        onKill = true;
        tempInt -= 8;
        if (tempInt < -7) {
          tempInt = 0;
        }
      }
      unsigned int wlohk = 0;
      do { // DStat Check + other stat checks
        invalid = true;
        cout << "wlohk." << wlohk << ".tempInt." << tempInt << ">";
        if (abs(tempInt) == 1 && (clipless || realWepSlot == "melee")) {
          tempInt += rand() % 9 - 2;
        } else if (abs(tempInt) == 5 && !hasMeter) {
          cout << "!";
          tempInt += rand() % 9 - 6;
        } else if (abs(tempInt) > 7 && abs(tempInt) < 12 &&
                   statString.find("uilding") != string::npos) {
          tempInt += rand() % 17 - (tempInt + 1);
        } else if (abs(tempInt) == 15 && (wepType == "Cleaver" || rapidFire)) {
          tempInt -= rand() % 15 + 1;
        } else if (count(usedDynamicStatEntries[4].begin(),
                         usedDynamicStatEntries[4].end(), abs(tempInt))) {
          tempInt++;
          if ((tempInt > 7 && onKill) || tempInt > 15) {
            tempInt = 0;
          }
        } else {
          invalid = false;
        }
        wlohk++;
        if (wlohk > 150) {
          cout << "ERROR: Dectected infinite loop at loop \"wlohk\", breaking "
                  "loop & aborting current stat creation. Press ENTER to "
                  "continue";
          cin.ignore();
          invalid = true;
          break;
        }
      } while (invalid && wlohk <= 150);
      if (invalid) {
        statTemp.clear();
        statString.clear();
        ratingBase = 0;
        ratingMod = 0;
        break;
      } else {
        tempInt = abs(tempInt);
        tempString = rewards[tempInt];
        usedDynamicStatEntries[4].push_back(tempInt);
        dStatType = 4;
        stringIndex = tempInt;
        if (tempInt == 1) {
          mod %= 10;
          mod += 3;
          if (clipless || realWepSlot == "melee") {
            mod = 0;
          }
        }
        if (tfClass == "Sniper" && wepSlot == "primary" &&
            (tempInt == 0 || tempInt == 6 || tempInt == 8 || tempInt == 13 ||
             tempInt == 14)) {
          if ((statString.find("Full Charge") != string::npos ||
               statString.find("On Kill") != string::npos) &&
              tempInt != 8) {
            tempString = "+$n% damage per shot";
          } else {
            mod = round(mod / 4);
            tempString = "applys $e* for $n* to " +
                         to_string(round(mod / 2.5)) +
                         " seconds based on charge level";
          }
        }
        if (tempInt == 3 && (wepType == "Shotgun" && wepType == "Scattergun" &&
                             wepType == "Peppergun")) {
          if (wepType == "Peppergun") { // 4 pellets
            mod = round(mod / 2);
            ratingMod *= 2;
          } else { // 10 pellets
            mod *= 2;
            ratingMod *= 0.85;
            numInterval = 1;
          }
          tempString += " per pellet";
        }
        tempInt = rewardRatings[tempInt];
      }
    } else { // negative stats
      tempInt %= 4;
      bool onMiss = false;
      if (tempBool) { // on miss stats
        onMiss = true;
        tempInt -= 2;
        if (tempInt < -1) {
          tempInt = 0;
        }
      }
      unsigned int wloms = 0;
      do { // DStat Check + other stat checks
        invalid = true;
        cout << "wloms." << wloms << ">";
        if (count(usedDynamicStatEntries[4].begin(),
                  usedDynamicStatEntries[4].end(),
                  abs(tempInt) +
                      100)) { // downside modifier is + 100 (ex. rewards values
                              // are 0-15; penalties' values are 100-103)
          tempInt++;
          if ((tempInt > 1 && onMiss) || tempInt > 3) {
            tempInt = 0;
          }
        } else {
          invalid = false;
        }
        wloms++;
        if (wloms > 150) {
          cout << "ERROR: Dectected infinite loop at loop \"wloms\", breaking "
                  "loop & aborting current stat creation.";
          invalid = true;
          break;
        }
      } while (invalid && wloms <= 150);
      if (invalid) {
        statTemp.clear();
        statString.clear();
        ratingBase = 0;
        ratingMod = 0;
        break;
      } else {
        tempInt = abs(tempInt);
        if (wepType == "Cleaver") {
          tempInt = 1;
        }
        if (tempInt == 0) {
          mod %= 5;
          mod++;
        } else if (tempInt == 1) {
          posNegSignIndex = 2;
          if (rapidFire) {
            numInterval = 2;
            ratingMod *= 1.063;
          }
        }
        tempString = penalties[tempInt];
        usedDynamicStatEntries[4].push_back(tempInt +
                                            100); // downside modifier is + 100
        dStatType = 4;
        stringIndex = tempInt;
        tempInt = penaltyRatings[tempInt];
        if (tempString.find("seconds") == string::npos) {
          if (mod > 0) {
            mod %= 9;
          } else {
            mod %= 4;
          }
          mod += 2;
        }
        if (tempInt) {
          ratingMod *= tempInt;
        }
      } //<- bracket from commented code above (not commented anymore)
    }
    statString.replace(statString.find("$o"), 2, tempString);
    if (rapidFire) {
      ratingMod *= 2.5;
    }
    if (usedDynamicStatEntries[4].size() > 2) {
      cout << "\n\nstatString: \"" << statString
           << "\"; stringIndex: " << stringIndex
           << "; press ENTER to continue\n\n";
      cin.ignore();
    }
  }
  while (statString.find("$s") != string::npos) {
    bool skipNormStatCheck = false;
    if (wepType == "Lunchbox" || wepType == "Cleaver") {
      tempInt = rand() % 10; // 0-9
      skipNormStatCheck = true;
    } else if (explosive) {
      tempInt = rand() % 9; // 0-9 (no 5)
    } else {
      tempInt = rand() % 7; // 0-6 (if projectile: 0-7 & no 5)
    }
    cout << "(pre-adj) tempInt == " << tempInt << endl;
    bool invalid;
    unsigned int wlst = 0;
    do { // DStat Check + other stat checks
      invalid = false;
      cout << "wlst." << wlst << ">";
      wlst++;
      if (wearable) {
        // cout << "WEARABLE";
        tempInt %= 3;
        switch (tempInt) {
        case 0:
          tempInt = 1;
          break;
        case 1:
          tempInt = 4;
          break;
        case 2:
          tempInt = 5;
          break;
        }
      } else if (!skipNormStatCheck) {
        invalid = true;
        if (tempInt > 5 && projectile) {
          tempInt++;
        }
        if (tempInt == 3 && (wearable || clipless || realWepSlot == "melee")) {
          tempInt += rand() % 8 - 4;
        } else if (tempInt == 8 && (realWepSlot == "melee" ||
                                    projectile && wepType != "Syringe Gun")) {
          tempInt += rand() % 8 - 9;
        } else if (tempInt > 7 && !projectile) {
          tempInt = 0;
        } else {
          invalid = false;
        }
      }
      if (!invalid && count(usedDynamicStatEntries[5].begin(),
                            usedDynamicStatEntries[5].end(), abs(tempInt))) {
        tempInt++;
        if ((tempInt > 6 && !(explosive || wepType == "Lunchbox")) ||
            tempInt > 10) {
          tempInt = 0;
        } else if (projectile && tempInt == 5) {
          tempInt++;
        }
        invalid = true;
      }
      if (wlst > 150) {
        cout << "ERROR: Dectected infinite loop at loop \"wlst\", breaking "
                "loop & aborting current stat creation";
        invalid = true;
        break;
      }
    } while (invalid && wlst <= 150);
    if (invalid) {
      statTemp.clear();
      statString.clear();
      ratingBase = 0;
      ratingMod = 0;
      break;
    }
    tempInt = abs(tempInt);
    if (wepType == "Cleaver" && tempInt != 7) {
      tempString = "damage";
    } else if (wepType == "Lunchbox" && tempInt >= 7) {
      if (tempInt == 7) {
        if (tfClass == "Heavy") {
          tempString = "faster spin up time";
          ratingBase += 2.625;
        } else {
          tempString = "jump height";
          ratingBase += 0.125;
        }
      } else if (tempInt == 8) {
        tempString = "max health";
        if (tfClass == "Heavy") {
          ratingBase += 5.5;
        } else {
          ratingBase += 9.5;
        }
      } else if (tempInt == 9) {
        tempString = "attacks deal $r";
        ratingMod *= 0.65;
      }
    } else {
      tempInt = abs(tempInt);
      tempString = statTypes[tempInt];
      ratingBase += statTypeRatings[tempInt];
      usedDynamicStatEntries[5].push_back(tempInt);
      dStatType = 5;
    }
    if (tempString == "") {
      tempString = "movement speed";
    }
    cout << "(post-adj) tempInt == " << tempInt
         << "; tempString = " << tempString << endl;
    statString.replace(statString.find("$s"), 2, tempString);
  }
  while (statString.find("$f") != string::npos) {
    tempInt = rand() % 5;
    tempString = altFire[tempInt];
    if (statString.find(":") == string::npos) {
      tempString[0] = tolower(tempString[0]);
      if (tempInt == 0) {
        tempString.insert(0, "lets you ");
      }
    }
    statString.replace(statString.find("$f"), 2, tempString);
    ratingBase = altFireRatings[tempInt];
    if (tempInt < 4) {
      if (realWepSlot != "melee") {
        mod %= 4;
        tempInt = 4 - mod;
        statString += " (consumes " + to_string(tempInt * 25) + " of the clip)";
        ratingMod *= mod * 0.563;
      } else {
        tempInt = 22 - mod;
        statString += " (recharges in " + to_string(tempInt * 3) + " seconds)";
        ratingMod *= mod * 0.063;
      }
      posNegSignIndex = 2;
    }
  }
  // pos/neg text & other stuff
  while (statString.find("$a") != string::npos) {
    statString.replace(statString.find("$a"), 2,
                       posNegStringPair[posNegIndex][upside]);
  }
  while (statString.find("$b") != string::npos) {
    tempInt = distance(classList.begin(),
                       find(classList.begin(), classList.end(), tfClass));
    vector<string> tempVector(classSpWearerConditions[tempInt].begin(),
                              classSpWearerConditions[tempInt].end());
    while (tempVector.back() == "") {
      tempVector.pop_back();
    }
    vector<double> tempVectorMods(classSpWearerConditionMods[tempInt].begin(),
                                  classSpWearerConditionMods[tempInt].end());
    if (usedDynamicStatEntries[0][0] < 0) {
      tempInt = rand();
    } else {
      tempInt = usedDynamicStatEntries[0][0];
    }
    tempInt %= (3 + tempVector.size());
    if ((tfClass == "Heavy" && wepType != "Minigun") ||
        (tfClass == "Sniper" && wepType != "Sniper Rifle")) {
      tempInt %= 3;
    }
    if (tempInt == 0) {
      if (!explosive && !wearable &&
              (statString.find("reload speed") != string::npos) ||
          (statString.find("deploy & holster speed") != string::npos) ||
          (statString.find("health from healers & packs") != string::npos)) {
        cout << "Detected illogical stat boost in combination with wearer "
                "condition; statString = "
             << statString.substr(0, statString.find("$w")) +
                    "when fired at their back from close range\n";
        if (mod % 2 == 0) {
          tempString = "damage";
          ratingBase *= 1.45;
        } else {
          tempString = "firing speed";
        }
        statString.replace(statString.find("in ") + 3, string::npos,
                           tempString + " $b");
      } else if (explosive || wearable ||
                 (statString.find("No flinching") != string::npos)) {
        tempInt = 3;
      }
    } else if (tempInt == 3 && tfClass == "Heavy") {
      tempInt = 2;
    } else if (tempInt == 3 && tfClass == "Engineer") {
      statTemp = "Deals " + statTemp;
      if (statTemp.find("targets") != string::npos) {
        statTemp.erase(statTemp.find("targets"), 8);
      }
    }
    if (wepType == "Invis Watch") {
      if (invisWatchCloakTypeIndex < 2) {
        tempString = "while cloaked";
        ratingMod *= 0.85;
      } else {
        if (mod > 8) {
          tempInt = 20 - mod;
          if (tempInt > invisWatchFeignDuration) {
            tempInt = invisWatchFeignDuration;
          }
          tempString = "for " + to_string(tempInt) +
                       " seconds when Feign Death is activated";
          ratingMod *= 0.063 * tempInt;
        } else {
          tempString = "while Feign Death is active";
          ratingMod *= 0.063 * invisWatchFeignDuration;
        }
      }
    } else if (wepType == "Battle Banner") {
      tempString = "while buff is active";
      ratingMod *= 0.333;
    } else if (wepType == "Jetpack" && tempInt > 2) {
      tempString =
          "while launched airborne by explosions, grapple hooks or rocket "
          "packs"; // thanks tf team for being so long winded with ur stats <3
    } else if (meterStatBoostNum > 0 && statCat != 8) {
      tempString = "while $t is active";
      ratingMod *= meterMod;
    } else if (tempInt < 3) {
      tempString = wearerConditions[tempInt];
      ratingMod *= wearerConditionMods[tempInt];
    } else {
      cout << "!!";
      tempString = tempVector[tempInt - 3];
      ratingMod *= tempVectorMods[tempInt - 3];
    }
    cout << "tempInt = " << tempInt << "; tempString = " << tempString << endl;
    statString.replace(statString.find("$b"), 2, tempString);
  }
  while (statString.find("$c") != string::npos) {
    bool revCondition = false;
    if (usedDynamicStatEntries[0][1] < 1) { // special exception for vs players
      tempInt = rand() % 10; // 0-9; makes vs players & buildings 2x as likely
    } else {
      tempInt = usedDynamicStatEntries[0][1];
      if (mod < 0) {
        revCondition = true;
      }
    }
    tempInt %= 8;
    if (usedDynamicStatEntries[0][1] == tempInt) {
      tempInt++;
    }
    if (wepType == "Battle Banner" || wepType == "Lunchbox" ||
        meterStatBoostNum > 0) {
      tempInt = 0;
    }
    if ((tempInt == 1 && (statString.find("knockback") != string::npos || statString.find("$r") != string::npos || statString.find("crit") != string::npos)) ||
      	(tempInt == 4 && wepSlot == "melee") ||
        (critGimmick && (statString.find("$r") != string::npos || statString.find("crit") != string::npos))) {
      cout << "!!!.";
      /*if (usedDynamicStatEntries[0][1] > -1) {
        tempInt -= 2;
      }*/
      tempInt %= 6;
      tempInt += 2;
    }
    tempString = conditions[tempInt];
    if (revCondition) {
      tempString = "non-" + tempString;
    }
    statString.replace(statString.find("$c"), 2, tempString);
    float modVal = conditionMods
        [tempInt]; // store modifier value in variable while it goes through
                   // switch statement to potentially change value before being
                   // mutiplied to the ratingMod variable. Before the local var,
                   // the switch ststement changed the ratingMod directly. It
                   // didn't cause any problems but this setup should prevent
                   // anything from going wrong.
    usedDynamicStatEntries[0][1] = tempInt;
    // will add more to switch statement soon :)
    switch (tempInt) {
    case 1: // building
      if (wepSlot != "melee" && explosive) {
        modVal += 0.4;
      } else if (tfClass == "Pyro") {
        modVal = 0.25;
      }
    case 2: // burning
      if (tfClass == "Pyro") {
        modVal = 0.7;
        if (wepType == "Flame Thrower") {
          modVal = 0.95;
        }
      }
      break;
    case 4: // slowed
      if (tfClass == "Scout" && realWepSlot != "melee") {
        modVal = 0.45;
      }
      break;
    case 5: // bleeding
      if (tfClass == "Scout") {
        modVal = 0.5;
      }
      break;
    case 8: // ppl who also have this weapon
      if (mod > 0) {
        statString =
            "Instantly kills enemies who also have this weapon equipped";
        ratingBase = 1.25;
      } else {
        statString =
            "Does no damage to enemies who have also equipped this item";
        ratingBase = 2.5;
      }
      mod = 1;
      ratingMod = 1;
      modVal = 1;
      break;
    }
    if (revCondition) {
      modVal = 1 - modVal;
    }
    ratingMod *= modVal;
  }
  while (statString.find("$d") != string::npos) {
    bool dStatCheck = false;
    bool skipDStat = false;
    bool debugTempIntCout = false;
    unsigned int wld = 0;
    do {
      cout << "wl$d.";
      if (statCat == 8 && subStat == 4) {
        skipDStat = true;
        if (wepSlot == "melee" && whenActive) {
          tempInt = 5;
        } else if (tfClass == "Pyro") {
          tempInt = 2;
        } else if (tfClass == "Soldier" || tfClass == "Demoman") {
          tempInt = 1;
        } else {
          tempInt = 0;
        }
      } else if (!skipDStat && !dStatCheck) {
        tempInt = rand();
      } else {
        tempInt++;
        debugTempIntCout = true;
        dStatCheck = false;
      }
      if (explosive) {
        tempInt %= 7;
      } else if (wepType == "Shield") {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!.";
        tempInt %= 3;
        tempInt += 3;
      } else {
        tempInt %= 6;
      }
      if (debugTempIntCout) {
        cout << "tempInt = " << to_string(tempInt);
      }
      if (tempInt == 3 && tfClass == "Sniper" && wepSlot == "primary" &&
          !tempBool) {
        ratingMod *= 1.5;
      }
      if (count(usedDynamicStatEntries[1].begin(), usedDynamicStatEntries[1].end(), tempInt) && !skipDStat) {
        dStatCheck = true;
        cout << "!";
      } else if (!skipDStat) {
        usedDynamicStatEntries[1].push_back(tempInt);
				//cout << "YOOO WE ADDED A DSTAT1 YOOO";
        dStatType = 1;
        dStatCheck = false;
      }
      wld++;
      if (wld > 150) {
        cout << "ERROR: Dectected infinite loop at loop \"wl$d\", breaking loop & aborting current stat creation.";
        dStatCheck = true;
        break;
      }
    } while (dStatCheck && wld < 150);
    if (tempInt == 1 && tfClass == "Pyro") {
      ratingMod *= 0.75;
    }
    if (tempInt == 3 && tfClass == "Sniper") {
      ratingMod *= 1.375;
    }
    if (!dStatCheck) {
      statString.replace(statString.find("$d"), 2, damTypes[tempInt]);
      ratingBase += damTypeRatings[tempInt];
    } else {
      statTemp.clear();
      statString.clear();
      ratingBase = 0;
      ratingMod = 0;
      break;
    }
  }
  while (statString.find("$e") != string::npos) {
    if (tempBool) {
      tempInt = rand() % 7;
    } else {
      tempInt = rand() % 6;
    }
    if (statString.substr(statString.find("$e"), 4).find("*") != string::npos) {
      statString.erase(statString.find("*"), 1);
      ratingBase = debuffRatings[tempInt];
      tempInt %= 6;
      if (tempInt == 3 && !coatable) {
        statString += "for $n* seconds";
        numInterval = 1;
        posNegSignIndex = 2;
        mod %= 11;
        mod += 2;
      } else if (tempInt == 5) {
        tempInt++;
      }
    } else {
      ratingMod *= debuffMods[tempInt];
    }
    tempString = debuffs[tempInt];
    if (statString.substr(statString.find("$e"), 4).find("s") != string::npos) {
      if (tempInt == 0) {
        tempString = "burn";
      }
    } else if (tfClass == "Spy") {
      if (tempInt == 0 || tempInt == 3) {
        ratingMod *= 2.5;
      }
      if (mod < 12) {
        if (invisWatchCloakTypeIndex < 2) {
          statString += " while cloaked";
          ratingMod *= 0.85;
        } else {
          if (mod > 8) {
            tempInt = 20 - mod;
            if (tempInt > invisWatchFeignDuration) {
              tempInt = invisWatchFeignDuration;
            }
            statString += " for " + to_string(tempInt) +
                          " seconds when Feign Death is activated";
            ratingMod *= 0.063 * tempInt;
          } else {
            statString += " while Feign Death is active";
            ratingMod *= 0.063 * invisWatchFeignDuration;
          }
        }
      }
    } else if (statTemp.substr(0, statTemp.find("$e")).find("appl") != string::npos) {
      if (tfClass == "Sniper") {
        tempString = "Jarate";
      } else {
        tempString += "s";
        statTemp.erase(statTemp.begin() + statTemp.find("appl"), statTemp.begin() + statTemp.find("$e") + 2);
        if (statTemp.find("to") != string::npos) {
          statTemp.erase(statTemp.find("to"), 2);
        }
        if (statTemp.find("for") != string::npos) {
          statTemp.insert(statTemp.find("for"), "for death ");
        } else {
          statTemp += " for death";
        }
      }
    }
    statString.replace(statString.find("$e"), 2, tempString);
  }
  while (statString.find("$h") != string::npos) {
    bool dStatCheck = false;
    bool skipDStat = false;
    if (wepType == "Invis Watch") {
      skipDStat = true;
    } else if (dStatCheck) {
      tempInt++;
    } else {
      tempInt = rand();
    }
    tempInt %= 4;
    if (wepType == "Invis Watch") {
      tempInt = 1;
    }
    cout << "tempInt = " << tempInt << endl;
    if (tempInt == 1 && mod > 10) {
      if (tfClass == "Heavy") {
        statString += "\nHealth from packs and Lunchboxes can give overheal";
        ratingBonus += 8.5;
      } else {
        statString += "\nHealth from packs can give overheal";
        ratingBonus += 6.25;
      }
    }
    if (count(usedDynamicStatEntries[2].begin(),
              usedDynamicStatEntries[2].end(), tempInt) &&
        !skipDStat) {
      dStatCheck = true;
    } else {
      if (!skipDStat) {
        usedDynamicStatEntries[2].push_back(tempInt);
        dStatType = 2;
      }
      statString.replace(statString.find("$h"), 2, HPContainerTypes[tempInt]);
      ratingMod *= HPContainerTypeMods[tempInt];
      dStatCheck = false;
    }
  }
  while (statString.find("$j") != string::npos) {
    bool dStatCheck = false;
    if (dStatCheck) {
      tempInt++;
      dStatCheck = false;
    } else {
      tempInt = rand();
    }
    tempInt %= 2;
    if (count(usedDynamicStatEntries[3].begin(), usedDynamicStatEntries[3].end(), tempInt)) {
      dStatCheck = true;
    } else {
      usedDynamicStatEntries[3].push_back(tempInt);
      dStatType = 3;
      statString.replace(statString.find("$j"), 2, ammoContainerTypes[tempInt]);
      ratingMod *= ammoContainerTypeMods[tempInt];
      dStatCheck = false;
    }
  }
  while (statString.find("$l") != string::npos) {
    int slotIndex = 0;
    string slotName;
    bool isAmmo = false;
    if (statString.substr(statString.find("$l"), 2).find("*")) {
      statString.erase(statString.find("*"), 1);
      isAmmo = true;
    }
    if (!(realWepSlot.substr(0, 3) == "PDA" || wepType == "Lunchbox" ||
          wepType == "Medigun" || wepType == "Sapper" || wearable || coatable ||
          (realWepSlot == "melee" && !miscAmmo))) {
      if (realWepSlot == "melee" && miscAmmo) {
        slotName = "misc";
      } else {
        slotName = realWepSlot;
      };
    } else {
      // for weapons without ammo
      if (usedDynamicStatEntries[0][3] > -1) {
        slotIndex = usedDynamicStatEntries[0][3];
      } else {
        slotIndex = rand();
      }
      int wl1 = 0;
      do {
        cout << "wl1.";
        if (wl1 > 0) {
          slotIndex++;
        }
        if (isAmmo) {
          slotIndex %= 2;
        } else {
          slotIndex %= 3;
        }
        slotName = weaponSlots[slotIndex];
        wl1++;
        if (wl1 > 50) {
          cout << "\nERROR: infinite loop detected after running loop \"wl1\" "
                  "50 times, breaking from loop & abandoning stat creation. "
                  "Press ENTER to continue: \n";
          cin.ignore();
          ratingBase = 0;
          ratingMod = 0;
          slotName.clear();
          statTemp.clear();
          statString.clear();
          break;
        }
      } while (slotName == realWepSlot && !(wl1 > 50));
    }
    if (slotName.empty()) {
      break;
    } else {
      statString.replace(statString.find("$l"), 2, slotName);
    }
  }
  while (statString.find("$r") != string::npos) {
    if (statString.find("*") != string::npos) {
      statString.erase(statString.find("*"), 1);
      tempInt = rand() % 3;
    } else {
      tempInt = rand() % 2;
    }
    statString.replace(statString.find("$r"), 2, critTypes[tempInt]);
    ratingBase += critTypeRatings[tempInt];
  }
  while (statString.find("$t") != string::npos) {
    if (statString.substr(statString.find("$t"), 4).find("*") != string::npos) {
      statString.erase(statString.find("*"), 1);
      tempBool = true;
    }
    if (tempBool) {
      tempInt = rand() % 10;
      tempString = meterNames[tempInt];
    } else {
      tempString = meterName;
    }
    if (tempString == "" || (tfClass == "Demoman" && wepSlot == "melee")) {
      tempString = "charge";
    }
    cout << "tempString = \"" << tempString << "\"\n";
    statString.replace(statString.find("$t"), 2, tempString);
    if (tempBool) {
      ratingMod *= meterMods[tempInt];
    }
  }
  while (statString.find("$u") != string::npos) {
    if (usedDynamicStatEntries[0][4] < 0) {
      tempInt = rand();
    } else {
      tempInt = usedDynamicStatEntries[0][4];
    }
    tempInt %= 4;
    tempString = buildings[tempInt];
    if (statString.substr(statString.find("$u"), 4).find("s") != string::npos ||
        tempBool) {
      if (tempString == "sentry" && !tempBool) {
        tempString = "sentries";
      } else if (tempString == "buildings" || tempString == "teleporters") {
        tempString = tempString.substr(0, tempString.length() - 1);
      }
    }
    statString.replace(statString.find("$u"), 2, tempString);
    ratingBase += buildingRatings[tempInt];
  }

  while (statString.find("$w") != string::npos) {
    bool forceWepSlotMod = false;
    if (statString.find("$w") == 0 ||
        statString.substr(statString.find("$w"), 4).find("*") != string::npos) {
      forceWepSlotMod = true;
      if (statString.substr(statString.find("$w"), 4).find("*") !=
          string::npos) {
        statString.erase(statString.substr(statString.find("$w"), 4).find("*") + statString.find("$w"), 1);
      }
    }
    if (statString.find("$w") == 0 ||
        statString.substr(statString.find("$w"), 4).find("*") != string::npos ||
        (wepType == "Medigun" && statString.find("overheal") != string::npos)) {
      tempString = "";
    } else if (statString.find("max") != string::npos) {
      tempString = "on wearer";
    } else if (wepType == "Lunchbox") {
      if (mod > 0 || (rand() % 4 != 0 && (statCat == 2 || statCat == 0))) {
        statString[0] = tolower(statString[0]);
        if (statString.find("User") == string::npos || statCat == 0) {
          statString = "User has " + statString;
        }
        tempString = "during this time";
        ratingMod *= 0.15 * lunchboxDuration;
      } else {
        tempString = "when the effect ends";
        ratingMod *= 0.375;
      }
      if (statCat == 0 && subStat == 11) {
        tempString = "";
      }
    } else if (wepType == "Battle Banner" && bannerBuffTypeIndex > 0) {
      tempString = "while buff is active";
      ratingMod = 0.333;
    } else if (wepType == "Medigun") {
      tempString = "";
    } else if (coatable && mod > 0) {
      statString = "Enemy has " + statString;
      tempString = posNegStringPair[posNegIndex][0];
      if (posNegIndex != 0 &&
          statString.find(tempString) !=
              string::npos) { // positive stat to negative (for enemy)
        statString.replace(statString.find(tempString), tempString.length(),
                           posNegStringPair[posNegIndex][1]);
      }
      tempString = "while coated"; // hope this works lol
    } else if (wepType == "Invis Watch" &&
               (statString.find("heal") == string::npos ||
                !(statCat == 2 || mod > 0))) {
      if (invisWatchCloakTypeIndex < 2) {
        tempString = "while cloaked";
        ratingMod *= 0.85;
      } else {
        if (mod > 10) {
          tempInt = 20 - mod;
          if (tempInt > invisWatchFeignDuration) {
            tempInt = invisWatchFeignDuration;
          }
          tempString = "for " + to_string(tempInt) +
                       " seconds when Feign Death is activated";
          ratingMod *= 0.063 * tempInt;
        } else {
          tempString = "while Feign Death is active";
          ratingMod *= 0.063 * invisWatchFeignDuration;
        }
      }
    } else if (meterStatBoostNum > 0) {
      tempString = "while " + meterName + " is active";
      ratingMod *= meterMod;
    } else {
      tempString = "on wearer";
    }
    if (whenActive && (tempString == "on wearer" || forceWepSlotMod)) {
      ratingMod *= weaponSlotMods[distance(
          weaponSlots.begin(),
          find(weaponSlots.begin(), weaponSlots.end(), wepSlot))];
      if (mod > 0) {
        ratingMod *= 1.1;
      }
    }
    statString.replace(statString.find("$w"), 2, tempString);
  }
  while (statString.find("$y") != string::npos) {
    statString.replace(statString.find("$y"), 2, ammoType);
  }
  while (statString.find("$z") != string::npos) {
    if (usedDynamicStatEntries[0][5] < 0) {
      tempInt = rand();
    } else {
      tempInt = usedDynamicStatEntries[0][5];
    }
    tempInt %= 2;
    statString.replace(statString.find("$z"), 2, sizes[tempInt]);
    ratingMod *= sizeMods[tempInt];
  }
  // final checks for stat legibility or changes so it makes sense
  if (wepType == "Lunchbox") {
    tempInt = statString.find("Wearer");
    if (tempInt != string::npos) {
      cout << "'Wearer' condition detected on 'Lunchbox!' statString = "
           << statString;
      statString = "User" + statString.substr(tempInt + 6, string::npos) +
                   "during this time";
      cout << "; new statString = " << statString << "...";
      ratingMod *= 1.063;
    }
  } else if (wepType.substr(0, 5) == "Flame") {
    tempInt = statString.find("projectile speed");
    if (tempInt != string::npos) {
      if (wepType == "Flame Thrower") {
        statString.replace(
            tempInt, string::npos,
            "flame range"); // how tf do I word this... flame reach distance?
                            // flame range? just 'range'?
      } else {
        statString.replace(tempInt, string::npos,
                           "projectile range"); // also weird... idc
      }
    }
  } else if (coatable) {
    if (statString.find("oated") == string::npos && statCat < 3 &&
        statString != "") { // oated to avoid capitals
      cout << "No 'coated' condition detected on 'coatable'! statString = "
           << statString;
      statString += " vs coated players";
      ratingMod *= 0.85;
    }
  } else if (meterStatBoostNum > 0) {
    if (statString.find("max") == string::npos &&
        statString.find("active") == string::npos && statCat < 3 &&
        statString != "") {
      cout << "No 'meter' condition detected on 'meter weapon'! statString = "
           << statString;
      statString += " while " + meterName + " is active";
      ratingMod *= meterMod;
    }
  }
  if (wepType == "Medigun") {
    if (statCat < 3 && statString != "" &&
        statString.find("ÜberCharge") == string::npos &&
        statString.find("max") == string::npos) {
      cout << "ooo\n";
      statString = statString.substr(0, statString.find("while"));
      cout << "statString = " << statString << endl;
      /*if (!isalpha(statString[0]) || statString[0] == '+' || statString[0] ==
      '-') { statString.insert(0,"a ");
      }*/
      statString.insert(0, "Provides you and your target with ");
      if ((mod > 6 || ratingBase * mod > 25) && statCat != 3) {
        statString += "during ÜberCharge";
        ratingMod *= 0.375;
      } else {
        statString[0] = tolower(statString[0]);
        statString.insert(0, "While healing, ");
        ratingMod *= 1.25;
      }
    }
  }
  // number/percentage value
  if (statString.find("$n") != string::npos) {
    /*old code to remove leading zeros when mod wasn't an int value:
    tempString = to_string(abs(mod*numInterval));
    tempString = tempString.substr(0, tempString.find("."));
    statString.replace(statString.find("$n"), 2, posNegSign[posNegSignIndex] +
    tempString);*/
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
      tempInt = abs(mod * numInterval);
      if (tempInt > 30 && tempInt < 36) {
        mod = 33 * mod / abs(mod);
        // cout << "numInterval = "<< numInterval << "; ratingMod/numInterval =
        // " << to_string(ratingMod/numInterval) << endl;
        ratingMod /= numInterval;
        numInterval = 1;
      } else if (tempInt > 62 && tempInt < 70) {
        mod = 66 * mod / abs(mod);
        // cout << "numInterval = "<< numInterval << "; ratingMod/numInterval =
        // " << to_string(ratingMod/numInterval) << endl;
        ratingMod /= numInterval;
        numInterval = 1;
      } else if (tempInt > 95 && tempInt < 105) {
        mod = 100 * mod / abs(mod);
        // cout << "numInterval = "<< numInterval << "; ratingMod/numInterval =
        // " << to_string(ratingMod/numInterval) << endl;
        ratingMod /= numInterval;
        numInterval = 1;
      }
      // cout << "ratingMod = " << ratingMod << "; Press ENTER to continue";
      // cin.ignore();
      if (tempInt % 5 != 0 && tempInt % 33 != 0) {
        mod = (mod % 19 + 2) * mod / abs(mod);
        numInterval = 5;
        ratingMod *= (5 / numInterval);
      }
      while (abs(mod * numInterval) < 10) {
        mod += mod / abs(mod);
      }
    } else if (mod == 0) {
      if (realUpside) {
        mod = 1;
      } else {
        mod = -1;
      }
    }
    statString.replace(statString.find("$n"), 2,
                       posNegSign[posNegSignIndex] +
                           to_string(abs(mod * numInterval)));
  } else {
    mod /= abs(mod);
  }
  if (ratingBase == 0 && statString != "") {
    ratingBase = 1;
  }
  tempInt = 0;
  while (true) {
    tempInt = statString.find('\n', tempInt);
    if (tempInt != string::npos && tempInt < statString.length()) {
      tempInt++;
      cout << "statString.substr(" << tempInt << ", string::npos) = \""
           << statString.substr(tempInt, string::npos) << "\"\n";
      statString[tempInt] = toupper(statString[tempInt]);
    } else {
      statString[0] = toupper(statString[0]);
      break;
    }
  }
  if (lockedModValue) {
    mod = initialMod;
    numInterval = 5;
  }
  rating = (ratingBase * mod + ratingBonus) * ratingMod;
  coords = array<int, 2>({statCat, subStat});
  cout << "mod = " << mod << "; ratingBase = " << ratingBase
       << "; ratingMod = " << ratingMod << "; ratingBonus = " << ratingBonus
       << "; rating = " << rating << "; coordinates: (" << coords[0] << ", "
       << coords[1] << ")";
  // if (ratingMod == 0) {
  // cout << "...Press ENTER to continue\n";
  // cin.ignore();
  // }
}