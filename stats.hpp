#ifndef STATS
#define STATS
#include "grammar.hpp" //also includes <array>, <string>, <vector>, data.hpp, & namespace:std
#include <cmath>
enum statType{special, damage, defense, utility, projectile, exclusive, constructor = 8};
extern array<vector<int>,6> usedDynamicStatEntries; //first vector used for stored $b [0][0], $c [0][1], $i [0][2], $l [0][3], $u [0][4], and $z [0][5] values, the rest are for taken $d [1], $h [2], $j [3], $o [4], and $s [5]
extern array<string,6> singValStatFlagNames;
extern array<string,6> dynamicStatFlagNames;
extern const array<int,9> statCatNum;
extern const array<array<string,2>,11> posNegStringPair;
extern const array<string,3> posNegSign;
extern const array<string,7> damTypes;
extern const array<double,7> damTypeRatings;
extern const array<string,3> critTypes;
extern const array<double,3> critTypeRatings;
extern const array<string,8> conditions;
extern const array<double,8> conditionMods;
extern const array<string,7> hitConditions;
extern const array<double,7> hitConditionMods;
extern const array<string,3> wearerConditions;
extern const array<double,3> wearerConditionMods;
extern const array<array<string,3>,9> classSpWearerConditions;
extern const array<array<double,3>,9> classSpWearerConditionMods;
extern const array<string,16> rewards;
extern const array<double,16> rewardRatings;
extern const array<string,4> penalties;
extern const array<double,4> penaltyRatings;
extern const array<string,5> altFire;
extern const array<double,5> altFireRatings;
extern const array<string,7> debuffs;
extern const array<double,7> debuffMods;
extern const array<double,7> debuffRatings;
extern const array<string,5> coatEffects;
extern const array<double,5> coatBonus;
extern const array<string,10> statTypes;
extern const array<double,10> statTypeRatings;
extern const array<double,14> meterMods;
extern const array<string,13> meterBuildMethods;
extern const array<double,13> meterBuildMethodRatings;
extern const array<string,3> meterEffects;
extern const array<double,3> meterEffectRatings;
extern const array<array<string,3>,9> silentKiller;
extern const array<array<double,3>,9> silentKillerRatings;
extern const array<string,4> HPContainerTypes;
extern const array<double,4> HPContainerTypeMods;
extern const array<string,2> ammoContainerTypes;
extern const array<double,2> ammoContainerTypeMods;
extern const array<string,3> sizes;
extern const array<double,3> sizeMods;
extern const array<string,4> bannerBuffTypes;
extern const array<string,4> buildings;
extern const array<double,4> buildingRatings;
extern const array<string,4> uberEffects;
extern const array<double,4> uberEffectRatings;
extern const array<string,3> cloakTypes;
extern const array<double,3> cloakTypeRatings;
extern int tempInt, mod, statCat, subStat, bannerBuffTypeIndex, lunchboxDuration, invisWatchCloakTypeIndex, meterStatBoostNum; //use tempInt less... really dumb idea and horrendous coding practice
extern float invisWatchFeignDuration, meterRating;
class Stat {
	public:
		Stat(int mod, int statCat, int subStat, string wepType = "Shotgun", string wepSlot = "secondary", string realWepSlot = "secondary", string tfClass = "multi", string ammoType = "pellet", string meterName = "", bool whenActive = false, bool hasMeter = false, bool hasAltFire = false, bool wearable = false, bool rapidFire = false, bool coatable = false, bool explosive = false, bool clipless = false, bool critGimmick = false, bool miscAmmo = false, bool statFlagPass = false, bool lockedModValue = false); //c++ not supporting named paramaters makes me die inside... maybe I could just include a pointer to the weapon? that wouldnt work unless I defined stat and wep in one header or something. Maybe I can put all the weapon properties in a data structure and send that over? Can a struct be a paramater? Maybe I can forward declare both in data? Oh well this works fine for now, maybe I'll do this and then after I'll try pointing and reworking everything along with seeds & UI and stuff...
		statType type = special;
		array<int,2> coords = {0,0};
		//array<int,2> dynamicStatEntryCoords = {-1, -1};
		string statString, statTemp, posNegString, tempString; //use tempString less... same as tempInt
		int upside, numInterval = 5, damTypeIndex, critTypeIndex, posNegIndex, posNegSignIndex, HPContainerIndex, ammoContainerIndex, statFlagAmount, initialMod, dStatType = -1, tempInt;
		double rating, ratingBase = 1, ratingMod = 1,  ratingBonus = 0;
		bool tempBool, realUpside, whiteText = false; //use tempBool less... same as tempInt
};

/*
class Attribute: public Stat {
	Attribute(int mod);
};
*/
#endif