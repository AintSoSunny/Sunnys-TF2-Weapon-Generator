#ifndef STATS
#define STATS
#include "data.hpp" //also includes <array>, <string>, <vector>, & namespace:std
#include <algorithm>
#include <cmath>
enum statType{uncategorized, damage, defense, utility, projectile, exclusive, special = 8};
extern const string damTypes[7];
extern const double damTypeRatings[7];
extern const string critTypes[3];
extern const double critTypeRatings[3];
extern const string conditions[8];
extern const double conditionMods[8];
extern const string hitConditions[7];
extern const double hitConditionMods[7];
extern const string wearerConditions[7];
extern const double wearerConditionMods[7];
extern const string classSpWearerConditions[9][3];
extern const double classSpWearerConditionMods[9][3];
extern const string penalties[1];
extern const double penaltyRatings[1];
extern const string hitRewards[15];
extern const double hitRewardRatings[15];
extern const string posNegStringPair[10][2];
extern const int statCatNum[9];
extern const string posNegSign[3];
extern const string HPContainerTypes[4];
extern const double HPContainerTypeMods[4];
extern const string ammoContainerTypes[2];
extern const double ammoContainerTypeMods[2];
extern const string sizes[3];
extern const double sizeMods[3];
extern const double meterMods[14];
extern const string debuffs[8];
extern const double debuffMods[8];
extern const string altFire[5];
extern const double altFireRatings[5];
extern const string coatEffects[4];
extern const double coatRatings[4];
extern const string bannerBuffTypes[4];
extern const string meterBuildMethods[13];
extern const double meterBuildMethodRatings[13];
extern int tempInt, mod, statCat, subStat, bannerBuffTypeIndex;
class Stat {
	public:
		Stat(int mod, int statCat, int subStat, string wepType = "Shotgun", string wepSlot = "secondary", string realWepSlot = "secondary", string tfClass = "multi", string ammoType = "pellet", string meterName = "", bool whenActive = false, bool hasMeter = false, bool wearable = false, bool rapidFire = false, bool coatable = false, bool explosive = false, bool statFlagPass = false);
		statType type = uncategorized;
		string statString, statTemp, posNegString, tempString;
		int upside, numInterval = 5, damTypeIndex, critTypeIndex, posNegIndex, posNegSignIndex, HPContainerIndex, ammoContainerIndex;
		double rating, ratingBase = 1, ratingMod = 1,  ratingBonus = 0;
		bool tempBool, whiteText = false;
};

/*
class Attribute: public Stat {
	Attribute(int mod);
};
*/
#endif