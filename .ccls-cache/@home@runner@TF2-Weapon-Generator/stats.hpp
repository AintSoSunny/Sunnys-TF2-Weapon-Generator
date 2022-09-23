#ifndef STATS
#define STATS
#include "data.hpp" //also includes <array>, <string>, <vector>, & namespace:std
#include <algorithm>
#include <cmath>
enum statType{uncategorized, damage, defense, utility};
extern const string damTypes[4];
extern const double damTypeRatings[4];
extern const string critTypes[2];
extern const double critTypeRatings[2];
extern const string conditions[5];
extern const double conditionMods[5];
extern const string posNegStringPair[7][2];
extern const int statCatNum[4];
extern const string posNegSign[3];
extern int tempInt, mod, statCat, subStat;
class Stat {
	public:
		Stat(int mod, int statCat, int subStat, string wepType = "Shotgun", string wepSlot = "secondary", string tfClass = "multi", bool whenActive = false, bool hasMeter = false, bool wearable = false);
		statType type = uncategorized;
		string statString, statTemp, posNegString, tempString;
		int upside, damTypeIndex, critTypeIndex, posNegIndex, posNegSignIndex;
		double rating, ratingBase = 1, ratingMod = 1,  ratingBonus = 0, numInterval = 5;
		bool whiteText = false;
};

/*
class Attribute: public Stat {
	Attribute(int mod);
};
*/
#endif