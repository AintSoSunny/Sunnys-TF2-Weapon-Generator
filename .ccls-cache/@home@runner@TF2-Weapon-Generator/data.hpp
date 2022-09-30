#ifndef DATA
#define DATA
#include <array>
#include <string>
#include <vector>
#include <iostream> //for debug
using namespace std;
extern const string weaponList[68];
extern const string classList[10];
extern const string classWeapons[10][15];
extern const string weaponSlots[5]; //idk if I still need this but oh well
extern const string wearables[7]; //list of wearable weapons
extern const double wearBoost[6]; //values to boost weapon rating on wearables (based on how much you give up)
extern const string alreadyBad[4]; //list of bad weapon types - e.g. syringe gun, heavy shotgun, gas canister
extern const double howBad[3]; //values to boost weapon rating
extern const string projectileBased[13];
extern const string meterWeapons[14];
extern const string meterNames[14];
extern const string cliplessWeapons[9];
extern const string rapidFireWeapons[8];
extern double version;
extern bool posNegSplit;
#endif