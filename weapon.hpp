#ifndef WEAPON
#define WEAPON
#include "stats.hpp" //also includes data.cpp, <algorithm>, <array>, <cmath>, <string>, <vector>, & namespace:std
#include <ctime> //for rand seed
class Wep {
	public:
		string tempString, wepType, wepSlot, realWepSlot, tfClass, ammoType, meterName, fullSeed;
		bool hasMeter = false, hasAltFire = false, whenActive = false, statMade = false, multiClass = false, wearable = false, projectile = false, explosive = false, coatable = false, throwable = false, clipless = false, rapidFire = false, altFire = false, miscAmmo = false, statFlagPass = false, randomStat = false, preSeed = false, tempBool;
		vector<int> statsUsed[6]; //array of vectors
		vector<array<int, 2>> statCoords; //vector of arrays
		vector<Stat> wepStats;
		vector<int> seed;
		vector<int> seedSegLengths; //for deconstructing user seeds
		//vector<string> tempVector; //for find function in multidimesional array because idk how else to do so lol
		int wepIndexFloor, wepIndexCeiling, statPhase, statNum, statAttempts, classIndex, wepIndex, meterIndex, statFlag, statFlagNum;
		double wepRating, newWepRating;
		Wep(int num, string preDefWepSlot = "", string preDefWepType = "", int preDefCoords[][2] = nullptr, int preDefProperties[] = nullptr, bool ps = false, bool debug = false, bool bypassRating = false, bool bypassBlacklist = false);
		int addSeed(int digits = 3);
		void addList(int arr[][2], int size, bool whitelist = false);
		void blacklist(int type);
		void printStats(bool debug = false);
};
#endif