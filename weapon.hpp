#ifndef WEAPON
#define WEAPON
#include "stats.hpp" //also includes data.cpp, <algorithm>, <array>, <cmath>, <string>, <vector>, & namespace:std
#include <ctime> //for rand seed
class Wep {
	public:
		string tempString, wepType, wepSlot, tfClass, fullSeed;
		bool hasMeter = false, whenActive = false, statMade = false, multiClass = false, wearable = false;
		vector<int> statsUsed[5];
		vector<Stat> wepStats;
		vector<int> seed;
		vector<int> seedSegLengths; //for deconstructing user seeds
		//vector<string> tempVector; //for find function in multidimesional array because idk how else to do so lol
		int wepIndexFloor, wepIndexCeiling, statPhase, statNum, statAttempts, classIndex, wepIndex;
		double wepRating, newWepRating;
		int addSeed(int digits = 3);
		Wep(int num, bool preSeed = false);
		void printStats(bool debug = false);
};
#endif