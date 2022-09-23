#include "weapon.hpp"
int Wep::addSeed(int digits) {
	int newSeed = time(NULL) * seedSegLengths.size();
	//idk why I have to use a tempInt compiler is being cringe
	tempInt = pow(10, digits);
	newSeed %= tempInt;
	while (to_string(newSeed).length() < digits) {
		tempInt = newSeed % 10;
		newSeed *= 10;
		newSeed += tempInt;
	}
	newSeed = abs(newSeed);
	srand(newSeed);
	seed.push_back(newSeed);
	seedSegLengths.push_back(digits);
	fullSeed += to_string(newSeed);
	cout << "Added seed: " << newSeed << endl;
	return newSeed;
}
Wep::Wep(int num, bool preSeed){
	//this seed segment does nothing it just puts the version inside to make sure the seed isn't old
	tempInt = floor(version*10);
	seed.push_back(tempInt);
	fullSeed += to_string(tempInt);
	seedSegLengths.push_back(to_string(tempInt).length());
	//stats Used Chart fill with 0
	tempInt = sizeof(statCatNum) / sizeof(statCatNum[0]);
 	for (int i = 0; i < tempInt; i++) {
		if (statCatNum[i] != 0) {
			for (int j = 0; j < statCatNum[i]; j++) {
				statsUsed[i].push_back(0);
			}
		}
	}
	//slot & weapon choice
	addSeed();
	tempInt = rand() % 100;
	if (tempInt < 40) {
		//40% chance
		wepSlot = "primary";
		wepIndexFloor = 0;
		wepIndexCeiling = 15;
	} else if (tempInt >= 40 && tempInt <= 65) {
		//35% chance
		wepSlot = "secondary";
		wepIndexFloor = 15;
		wepIndexCeiling = 33;
	} else {
		//25% chance
		wepSlot = "melee";
		wepIndexFloor = 33;
		wepIndexCeiling = 64;
	}
	wepIndexCeiling -= wepIndexFloor;
	wepIndex = rand() % wepIndexCeiling + wepIndexFloor;
	wepType = weaponList[wepIndex];
	
	for (int i = 0; i < 10; i++) {
		/*cant use find() in multidimesional array so... take the array to a vector lol I have no idea if this works :) 
ANYWAYS this determens the class based on the weapon*/
		vector<string> tempVector(begin(classWeapons[i]), end(classWeapons[i])); /* old code:
tempInt = distance(begin(classWeapons), find(begin(classWeapons[classIndex]), end(classWeapons[classIndex]), weaponList[tempInt]));
		if (find(tempVector.begin(), tempVector.end(), weaponList[tempInt]) != tempVector.end()) {
			break;
		}
		*/ 
		if (find(tempVector.begin(), tempVector.end(), wepType) != tempVector.end()) {
			classIndex = i;
			tfClass = classList[i];
			break;
		}
	}
	//removes * on "Boots*", "Parachute*", & "Shotgun*"
	if (wepType.find("*") != string::npos) {
		wepType.replace(wepType.find("*"), 1, "");
	}
	tempInt = distance(begin(wearables), find(begin(wearables), end(wearables), wepType));
	if (tempInt != distance(begin(wearables), end(wearables))) {
		wearable = true;
		wepRating -= wearBoost[tempInt];
	}
	cout << "Wearable! Wep: " << wepType << "; Index: " << tempInt << endl;
	tempInt = distance(begin(alreadyBad), find(begin(alreadyBad), end(alreadyBad), wepType));
	if (tempInt != distance(begin(alreadyBad), end(alreadyBad))) {
		cout << "Bad weapon! (lol) Wep: " << wepType << "; Index: " << tempInt << endl;
		wepRating -= howBad[tempInt];
	}
	//whenActive
	tempInt = rand() % 100;
	cout << wepSlot << "; " << tempInt << endl;
	if (wepSlot == "primary" && tempInt < 5 || wepSlot == "secondary" && tempInt < 20 || wepSlot == "melee" && tempInt < 75) {
		whenActive = true;
	} else {
		whenActive = false;
	}
	statPhase = 1;
	//n loop is for downsides
	for (int n = 0; n < 2; n++) {
		cout << "statPhase = " << to_string(statPhase);
		for (int i = 0; i < num; i++) {
			if (statPhase == 1) {
				statNum = i;
			} else {
				statNum = num + 1;
			}
			cout << "\n\nstat " << to_string(i + 1) << " of " << to_string(num) << endl;
			statMade = false;
			/*stat modifier calculation; 
			range is -8 through 20 but negatives are turned positive, so its twice as likely to get 0-8.
			The +2 turns it into 2-10 being most likely to be gotten because no tf2 stat modifes base less than 10%*/
			//makes sure no duplicate stats I think... I hope lol
			//also checks to make sure weapon is balanced during phase 2
			statAttempts = 0;
			while (statMade == false) {
				addSeed();
				mod = rand() % 29 - 8;
				if (mod < 0) {
					mod *= -1;
				}
				if (mod <= 8) {
					mod += 2;
				}
				if (statPhase == 2 && mod > 0) {
					mod *= -1;
				}
				statCat = rand() % 4;
				subStat = rand() % statCatNum[statCat];
				if (statsUsed[statCat][subStat] != 1) {
					cout << "Generating stat...";
					wepStats.emplace_back(mod, statCat, subStat, wepType, wepSlot, tfClass, whenActive, hasMeter, wearable);
					newWepRating = wepRating + wepStats[statNum].rating;
					cout << "...stat coordinates = (" << statCat << ", " << subStat << ")\n";
					if (statPhase == 2 && 0.1 * (abs(newWepRating) + 1) <= 0.6) {
						wepRating = newWepRating;
						cout << wepStats.back().statString;
						cout << "\nWeapon Complete\n";
						cout << "wepRating = " << wepRating;
						return; //weapon is balanced; end stat creation
					} else if (statPhase == 1 or newWepRating >= -5) {
						cout << "Stat creation successful!\n";
						statsUsed[statCat][subStat] = 1;
						wepRating = newWepRating;
						cout << wepStats.back().statString;
						cout << "\nstat coordinates = (" << statCat << ", " << subStat << ")\n";
						cout << "\nwepRating = " << wepRating << endl;
						//except for some reason this if else works ???
						if (statPhase == 1) {
							statMade = true; //breaks while loop for first phase
						} else {
							statNum += 1;
							statAttempts = 0;
						}
					} else {
						cout << "Stat creation failed; retrying...\n";
						//undo changes
						seed.pop_back();
						wepStats.pop_back();
						//temp solution / fallback:
						statAttempts++;
						if (statAttempts > 50) {
								cout << "Stat creation aborted...Weapon Complete\n";
							cout << "wepRating = " << wepRating;
								return;
						}
					}
				} else {
					cout << "Stat taken! Seed removed\n";
					seed.pop_back();
				}
			}
		}
		statPhase = 2;
		num = 1;
	}
	cout << seed.size();
};
void Wep::printStats(bool debug) {
	//for debug :)
	cout << "\nWEAPON\n\n";
	cout << "Level " << rand() % 100 << " " << wepType << " (" << tfClass << " " << wepSlot << ")\n\n";
	if (whenActive == true) {
		cout << "When weapon is active:\n";
	}
	for (int i = 0; i < wepStats.size(); i++) {
		cout << wepStats[i].statString << endl;
	}
	if (debug == true) {
		cout << "\n\nDEBUG INFO\n\nWeapon Rating: " << to_string(wepRating) << endl;
		cout << "Seed: ";
		for (int i = 0; i < seed.size(); i++) {
			if (i != 0) {
				cout << "-";
			}
			cout << seed[i];
		}
		//prolly add more later
	}
	cout << "\n\nEND WEAPON\n\n";
}