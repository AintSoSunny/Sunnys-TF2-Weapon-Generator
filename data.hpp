#ifndef DATA
#define DATA
#include <array>
#include <algorithm>
#include <cctype>
#include <iterator>
#include <string>
#include <iostream> 
#include <vector>
using namespace std;
extern const array<string,69> weaponList;
extern const array<string,10> classList;
extern const array<array<string,14>,10> classWeapons; //weapons sorted by class
extern const array<string,5> weaponSlots;
extern const array<double,5> weaponSlotMods;
extern const array<string,8> wearables; //list of wearable weapons
extern const array<double,7> wearBoost; //values to boost weapon rating on wearables (based on how much you give up)
extern const array<string,4> alreadyBad; //list of bad weapon types - e.g. syringe gun, heavy shotgun, gas canister
extern const array<double,3> howBad; //values to boost weapon rating
extern const array<string,14> projectileBased;
extern const array<string,14> meterWeapons;
extern const array<string,14> meterNames;
extern const array<array<string,3>,9> classMeterNames;
extern const array<string,14> altFireWeapons;
extern const array<string,10> cliplessWeapons;
extern const array<string,8> rapidFireWeapons;
extern const array<string,8> primaryLike;
extern const array<string,6> secondaryLike;
extern const array<string,5> throwableWeapons; 
extern const array<string,9> ammoTypes;
extern const array<array<string,5>,9> weaponAmmoGroups;
extern double version;
extern int subVersion;
extern string betaTag;
extern string versionFull;
extern string lineBreak(string ref = ">========<", bool firstNL = true, bool secNL = true);
extern int isInputSetInt(int c); 
extern int isInputSingleInt(int c); 
extern int isInputSetWords(int c); 
#endif