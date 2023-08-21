#ifndef WEAPON
#define WEAPON
#include "stats.hpp" //also includes data.cpp, <algorithm>, <array>, <cmath>, <string>, <vector>, & namespace:std
#include <ctime> //for rand seed
extern const array<array<int,2>,20> statsToOutside;
extern const array<array<int,2>,2> statsToTop;
extern const array<array<int,2>,25> posNegSplitStats;
extern const array<array<int,2>,13> dynamicStats;
class Wep {
	public:
		string tempString, wepType, wepSlot, realWepSlot, tfClass, ammoType, meterName, fullSeed;
		bool hasMeter = false, hasAltFire = false, whenActive = false, statMade = false, multiClass = false, wearable = false, projectile = false, explosive = false, coatable = false, throwable = false, clipless = false, rapidFire = false, altFire = false, miscAmmo = false, statFlagPass = false, randomStat = false, preSeed = false, noDownsides = false, downsideBlacklistApplied = false, critGimmick = false, isSword = false, forceUpside = false, forceDownside = false, posNegSplit = false, dynamicStat = false, tempBool;
		array<int,1> upsideStatFlags; 
		array<vector<int>,9> statsUsed; //array of vectors
		//array<vector<int>,4> usedDynamicStatEntries;
		vector<array<int, 2>> statCoords; //vector of arrays
		vector<Stat> wepStats;
		vector<int> seed;
		vector<int> seedSegLengths; //for deconstructing user seeds
		vector<int> statFlags{-1}; //storage only
		//vector<string> tempVector; //for find function in multidimesional array because idk how else to do so lol
		int wepIndexFloor, wepIndexCeiling, statPhase, statNum, statAttempts, classIndex, wepIndex, meterIndex, statFlag, statFlagNum, forceDur = -1, upsideNum, downsideNum, bonusUpsideNum, seedCalls = 0, tempInt;
		double wepRating, newWepRating;
		bool seedAdded = false;
		Wep(int num, int preDefWepType = -1, int preDefWepSlot = -1, int preDefClass = -1, int modMax = 20, int modSplit = 10, int statNumMax = -1, vector<array<int,3>> preDefStatData = vector<array<int,3>>(), bool exactUpside = false, bool exactDownside = false, int preDefProperties[2] = nullptr, bool debug = false, bool bypassRating = false, bool bypassBlacklist = false, bool anyWepAnyClass = false, bool lockedModValue = false);
		int addSeed(int digits = 4); //adds seed to seed array
		// int reSeedRand(int digits = 6); //reseeds the rand() function using the seeds in the seed vector... probably not using 
		void addList(int arr[][2], int size, bool whitelist = false);
		void blacklist(int type);
		void printStats(bool debug = false);
};
#endif