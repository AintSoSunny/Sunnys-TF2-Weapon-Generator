#include "grammar.hpp"
//the arrays we care about \/
const array<string,50> irregSing {
	"child",
	"corpus",
	"die",
	"fez",
	"foot",
	"gas",
	"goose",
	"louse",
	"man",
	"mouse",
	"opus",
	"ovum",
	"ox",
	"person",
	"quiz",
	"tooth",
	"woman"
};
const array<string,50> irregPlur {
	"children",
	"corpora",
	"dice",
	"fezzes",
	"feet",
	"gas",
	"geese",
	"lice",
	"men",
	"mice",
	"opera",
	"ova",
	"oxen",
	"people",
	"quizzes",
	"teeth",
	"women"
};
const array<string,150> bothSingPlur {
	"advice",
	"aircraft",
	"alms",
	"aluminum",
	"barracks",
	"binoculars",
	"bison",
	"bourgeois",
	"breadfruit",
	"cannon",
	"caribou",
	"cattle",
	"chalk",
	"chassis",
	"chinos",
	"clippers",
	"clothing",
	"cod",
	"concrete",
	"corps",
	"correspondence",
	"crossroads",
	"deer",
	"dice",
	"doldrums",
	"dungarees",
	"education",
	"eggfruit",
	"elk",
	"eyeglasses",
	"fish",
	"flares",
	"flour",
	"food",
	"fruit",
	"furniture",
	"gallows",
	"goldfish",
	"grapefruit",
	"greenfly",
	"grouse",
	"haddock",
	"halibut",
	"headquarters",
	"help",
	"homework",
	"hovercraft",
	"ides",
	"insignia",
	"jackfruit",
	"jeans",
	"knickers",
	"knowledge",
	"kudos",
	"leggings",
	"lego",
	"luggage",
	"monkfish",
	"moose",
	"mullet",
	"nailclippers",
	"news",
	"offspring",
	"oxygen",
	"pants",
	"passionfruit",
	"pike",
	"pliers",
	"police",
	"premises",
	"pyjamas",
	"reindeer",
	"rendezvous",
	"salmon",
	"scissors",
	"series",
	"shambles",
	"sheep",
	"shellfish",
	"shorts",
	"shrimp",
	"smithereens",
	"spacecraft",
	"species",
	"squid",
	"starfruit",
	"stone",
	"sugar",
	"swine",
	"they",
	"tongs",
	"trousers",
	"trout",
	"tuna",
	"tweezers",
	"wheat",
	"whitebait",
	"wood",
	"you",
};
//the ones I dont give a shit about <3 \/
//greek words ending in -on that pluralize by replacing it with a. I will likely not update this array much at all.
const array<string,50> irregGreekPref {
	"criteri", //add -on or -a depending on sing or plur.
	"phenomin"
};
//more bullshit
const array<string,250> aToAESing {
	"abscissa",
	"acanthella",
	"actinula",
	"agenda",
	"agora",
	"ala",
	"alga",
	"alumna",
	"amebula",
	"amenorrhoea",
	"amnesia",
	"amoeba",
	"amœba",
	"amœbula",
	"amphisbana",
	"amphora",
	"anamia",
	"anasthesia",
	"anemia",
	"antenna",
	"aqua",
	"area",
	"arena",
	"areola",
	"arteria",
	"artista",
	"asthesia",
	"aula",
	"aura",
	"aureola",
	"aurora",
	"bacteria",
	"ballista",
	"blennorrhœa",
	"boa",
	"caca",
	"camera",
	"camera obscura",
	"candela",
	"cannula",
	"cappa magna",
	"capsula",
	"carica",
	"cassia",
	"casura",
	"catapulta",
	"cathedra",
	"chimara",
	"choana",
	"cithara",
	"clavicula",
	"clavula",
	"cœlia",
	"conjunctiva",
	"copula",
	"cornea",
	"corolla",
	"corona",
	"coryza",
	"costa",
	"coxa",
	"cupola",
	"cyclopadia",
	"dementia",
	"diarrhœa",
	"diaspora",
	"dysasthesia",
	"empirical formula",
	"encyclopadia",
	"encyclopedia",
	"et cetera",
	"exedra",
	"exuvia",
	"fabella",
	"facula",
	"fascia",
	"fibula",
	"fimbria",
	"fistula",
	"formula",
	"fossa",
	"foveola",
	"fundatrigenia",
	"furcula",
	"fursona",
	"galea",
	"general formula",
	"gingiva",
	"gonorrhœa",
	"habenula",
	"hamaturia",
	"hamorrhagia",
	"hernia",
	"hetaera",
	"hetara",
	"Hora",
	"hyana",
	"hydromedusa",
	"hyena",
	"hyperasthesia",
	"hyperbola",
	"hysteria",
	"idea",
	"incisive fossa",
	"inertia",
	"infant formula",
	"infratemporal fossa",
	"ischamia",
	"ischemia",
	"labia",
	"lacuna",
	"lagena",
	"larva",
	"leucorrhœa",
	"literata",
	"longa",
	"lusus natura",
	"lymphoglandula",
	"macula",
	"mala",
	"mandibula",
	"maxilla",
	"maxima",
	"media",
	"medulla",
	"medusa",
	"melana",
	"membrana",
	"mensa",
	"mentula",
	"metra",
	"microfauna",
	"microflora",
	"micronova",
	"mina",
	"minutia",
	"Mœra",
	"molecula",
	"monomania",
	"mora",
	"myxamoeba",
	"nausea",
	"nebula",
	"noctiluca",
	"nova",
	"odontalgia",
	"oenochoa",
	"œnochoa",
	"oinochoa",
	"onomatopoeia",
	"oötheca",
	"orchestra",
	"ovipara",
	"ozana",
	"palastra",
	"palpebra",
	"panacea",
	"papilla",
	"papilloma",
	"parabola",
	"paranoia",
	"paraphilia",
	"parasthesia",
	"persona",
	"pharmacopœia",
	"phobia",
	"pinna",
	"piriform fossa",
	"planta",
	"pleura",
	"pneumonia",
	"prima donna",
	"prosopopœia",
	"pterygomandibular rapha",
	"pterygomaxillary fossa",
	"pterygopalatine fossa",
	"pupa",
	"pyamia",
	"pyriform fossa",
	"quadragena",
	"retina",
	"rima",
	"sagitta",
	"saliva",
	"sambuca",
	"scapula",
	"sclera",
	"scrofula",
	"septicamia",
	"sequela",
	"seta",
	"spatula",
	"spermatheca",
	"sphenomaxillary fossa",
	"sphenopalatine fossa",
	"spina",
	"squama",
	"stipula",
	"stria",
	"subpœna",
	"summa",
	"superficial fascia",
	"superior nasal concha",
	"synasthesia",
	"tabula",
	"tania",
	"telangiectasia",
	"temporal fossa",
	"testa",
	"tibia",
	"tinea",
	"toga",
	"toxamia",
	"trachea",
	"ulna",
	"urethra",
	"uva",
	"uvula",
	"vagina",
	"vallecula",
	"valvula",
	"vertebra",
	"vesica",
	"via",
	"vibrissa",
	"Victoria",
	"vita",
	"vulva",
	"zona",
	"zona pellucida",
	"zoöglœa",
	"zooxanthella"
};
//ugh
const array<string,50> aToATASing {
	"acanthoma",
	"acanthosoma",
	"adenoma",
	"ænigma",
	"ameloblastoma",
	"anathema",
	"aroma",
	"asthma",
	"atheroma",
	"axioma",
	"chasma",
	"cœloma",
	"comma",
	"dilemma",
	"diploma",
	"dogma",
	"drama",
	"eczema",
	"endothelioma",
	"enigma",
	"fibroma",
	"glioma",
	"gonadoblastoma",
	"gramma",
	"haematoma",
	"hæmatoma",
	"idioma",
	"lemma",
	"lymphœdema",
	"lymphoma",
	"melisma",
	"melodrama",
	"mesothelioma",
	"myeloma",
	"myoma",
	"œdema",
	"pancrea",
	"paradigma",
	"phantasma",
	"platysma",
	"problema",
	"sarcoma",
	"schema",
	"stigma",
	"stoma",
	"tagma",
	"teratoma",
	"trauma",
	"xanthelasma",
	"zeugma"
};
const array<string,50> oToIPref {
	"concert",
	"graffit"
};
//FUNCTIONS HERE

int isVowel(int c) {
	return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'); 
};
int isPlural(string s) {
	//I will not make this function very complex unless we run into problems. Should work most of the time
	//Actually I don't think I will use it very much.
	int len = s.length();
	if (
		len > 2 && 
		//generic irregulars
		(find(irregPlur.begin(), irregPlur.end(), s) != irregPlur.end()) ||
		//identical irregulars
		(find(bothSingPlur.begin(), bothSingPlur.end(), s) != bothSingPlur.end() || s.substr(len-6, 5) == "craft") ||
		//regular plurals
		(s.back() == 's' && 
		find(irregSing.begin(), irregSing.end(), s) == irregSing.end() ||
		((len == 3 && !isVowel(s[1])) || 
		s[len-2] == 'e' ||
		(s[len-2] == 'a' && len > 4) ||
		!(isVowel(s[len-2]) || s[len-2] == 's'))) || 
		//no vowels (minus e and a) & no 's' behind ending s; e.g. bus, plus, mass 
		//irregulars ending in -a
		(s.back() == 'a') ||
		//irregulars ending in -ae
		(s.substr(len-3, 2) == "ae") ||
		//irregulars ending in -i
		(s.back() == 'i')
	) {
		return true;
	}
	return false;
};
template <class InputIt, class OutputIt, class UnaryFunc>
OutputIt seperateSentence(InputIt first, InputIt last, OutputIt container, char sepChar = ' ', UnaryFunc sepFunc = NULL) { //container is preferred to be a vector, eventually will optimize for other contianers as needed.
	string word;
	if (sepFunc == NULL) {
		sepFunc == [sepChar] (char c) {return (c == sepChar);};
	}
	while (*first != *last) {
		if (sepFunc(first)) {
			container.push_back(word);
		} else {
			word += first;
		}
		first++;
	}
	return container;
}
//these two are quick and easy to use but only capitalize the last word in a string
string toSingular(string s, bool check) {
	//this one is gonna be pretty lazy because I don't know if I'll use it
	return s;
}; 
/*Sing -> Plur rules (for reference) (so far):
if (irregular singular noun) {change to corrosponding irregular plural form}
else if (both singular & plural or ends in -craft) {no change}
else if (ends in -ex or -ix) {replace with -ices}
else if (ends in –is) {replace with –es}
else if (ends in -us or irregular ending in -o) {replace with -i}
else if (ending in –ch, -o, -s, –ss, –sh, –x, or –z) {add -es}
else if (ends in -f or -fe but not -ff or -ffe and word is over 3 letters) {replace with -ves}
else if (ends in –y and letter before –y isn't a vowel) {replace with –ies}
else if (ends in -um and not -aum or greek word ending in -on and more than 4 letters) {replace with -a}
else if (ends in -na) {add -e}
else {add -s}

extra notes:
- "In some cases, singular nouns ending in –s or –z require that you double the –s or –z prior to adding the –es for pluralization." (ex. fezzes) (comes from grammarly, not sure if fezzes is irregular or...)
- Sometimes nouns ending in -f or -fe dont get changed to -ves (ex. roofs, beliefs, chefs, chiefs) (adding to irregulars until I see any pattern)
- There are also exceptions to the -o role for adding -es (ex. photos, pianos, halos) (also adding to irregulars until I see any pattern)
- Again, exceptions occur for the -is role for changing to -es (ex. n/a)

*/
string toPlural(string s, bool check) {
	string fillerStore; //for non-letters appended to the back of string s
	while (!isalpha(s.back()) && s.length() > 0) {
		fillerStore.insert(0, s.back(), 1);
		s.pop_back();
	}
	string::iterator firstLetter = find_if(s.begin(), s.end(), ::isalpha);
	const int len = s.size() - distance(s.begin(), firstLetter);
	if (!check || isPlural(s)) {
		int findWord = distance(irregSing.begin(), find(irregSing.begin(), irregSing.end(), s));
		if (findWord != irregSing.size()) {
			s = irregPlur[findWord];
		} else if (find(bothSingPlur.begin(), bothSingPlur.end(), s) != bothSingPlur.end() || s.substr(len-6) == "craft") {
			return s;
		} else if (s.substr(len-3) == "ex" || s.substr(len-3) == "ix") {
			return s.substr(0, len-3) + "ices" + fillerStore;
		} else if (s.substr(len-3) == "is") {
			return s.substr(0, len-3) + "es" + fillerStore;
		} else if (s.substr(len-3) == "us") {
			return s.substr(0, len-3) + "i" + fillerStore;
		} else if (s.substr(len-3) == "ch" || s.back() == 'o' || s.substr(len-3) == "s" || s.substr(len-3) == "ss" || s.substr(len-3) == "sh" || s.back() == 'x'|| s.back() == 'z') {
			return s + "es" + fillerStore;
		} else if ((s.back() == 'f' && s[len-2] != 'f') || (s.substr(len-3) == "fe" && s[len-3] != 'f') && len > 3) {
			return s.substr(0, s.find_last_of('f') - 1) + "ves" + fillerStore;
		} else if (s.back() == 'y' && !isVowel(s[len-2])) {
			return s.substr(0, len-2) + "ies" + fillerStore;
		} else if ((s.substr(len-3) == "um" && s[len-3] != 'a') || 1==2) {
			return s.substr(0,len-3) + "a" + fillerStore;
		} else if (find(aToAESing.begin(), aToAESing.end(), s) != aToAESing.end()) {
			return s + "e" + fillerStore;	
		} else if (find(aToATASing.begin(), aToATASing.end(), s) != aToATASing.end()) {
			return s + "ta" + fillerStore;
		} else {
			return s + "s" + fillerStore;	
		}
	}
}; 
string autoPlural(string s, int n, bool check) {
	if (n == 1) {
		return toSingular(s);
	} else {
		return toPlural(s);
	}
};
//the other one is usually more practical idk why I should keep this one but oh well. I have no fucking clue what iterators are other than complicated pointers sp this should be fun.
template <class InputIt, class OutputIt>
OutputIt toSingular(InputIt first, InputIt last, OutputIt newStr, bool check) {
	string word;
	while (*first != *last) { //newStr = toSingular(s);
		word += first;
		if (isspace(first)) {
			newStr += toSingular(word);
			word.clear();
		}
	}
	return *newStr;
}; 
template <class InputIt, class OutputIt>
OutputIt toPlural(InputIt first, InputIt last, OutputIt newStr, bool check) {
	string word;
	while (*first != *last) {
		word += first;
		if (isspace(first)) {
			newStr += toPlural(word);
			word.clear();
		}
	}
	return *newStr;
}; 
template <class InputIt, class OutputIt>
OutputIt autoPlural(InputIt first, InputIt last, OutputIt newStr, int n) {
	if (n == 1) {
		toSingular(*first, *last, *newStr);
	} else {
		toPlural(*first, *last, *newStr);
	}
};
string swapSingPlur(string s) {
	if (isPlural(s)) {
		return toSingular(s);
	} else {
		return toPlural(s);
	}
};