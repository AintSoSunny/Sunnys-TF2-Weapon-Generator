# Sunny's TF2 Weapon Generator
A Team Fortress 2 (TF2) weapon generator built from the ground up in C++. This was somewhat made for & inspired by TF2 YouTuber [Great Blue](https://www.youtube.com/c/GreatBlueHeron) and his [series of videos](https://youtube.com/playlist?list=PLU9jN5Sm9_UI1cdyviJ1OXiU_kGliucvg) reviewing and tinkering with TF2 Weapon Generators.

### Summary
This generator attempts to construct balanced weapons with a rating system, generating a given number of upsides before generating downsides until the rating reaches near zero. There are also features such as stat organization & templates to condense multple similar stats into one and keep code and stats consistent and organized, as well as settings you can modify, allowing you to select specific weapons, classes, or slots to generate, as well as changing some values and paramaters. Stat wording is directly from TF2, every stat from the base game should be included, along with a few custom stats.
***
### Features
###### This goes more in depth with the mechanics and features of the weapon generator
- **Stat Wording**  
	- The wording of stats is taken directly from Team Fortress 2 in order to avoid confusion and for consistency and (somewhat) believability. If stats have been worded differently for different weapons (such as conditional critical hits), I choose the wording I prefer.   
- **Rating System**  
	- The rating system is the core of this generator and goes hand in hand with the stat generation system. (Read: Weapon Balance System)
  - The *stat modifier* is something randomly generated prior to choosing a stat. This modifier affects the percentage or number value that a stat has, and some stats can modify its value and range.
  - Almost every stat has a *rating base* assigned to it, while some stats get their rating base from wordflags such as $d (damage types) or $o (on hit / kill rewards)
  - Some stats also get a *rating modifier* from wordflags such as $w (on wearer, which reduces rating mod if weapon is only when active based on the weapon slot) or $c (enemy conditions, lowers the rating modifier based on how rare / difficult a condition is).
  - Very few stats have a *rating bonus* (or rating deficit, which is in the same variable, just negative), such as health regeneration.
  - At the end of the stat construction, the number value bis calculated by multplying the stat modifier with the *number interval*, which is usually 5, sometimes 1, but rarely can be other numbers and even decimals. The product is rounded to an integer and is inserted in the '$n' wordflag.
  - After that, the rating is calculated with (n * r + b) * m (n = stat modifier, r = rating base, m = rating modifier, b = rating bonus).
- **Weapon Balance System** 
	- A given (or constant depending on the weapon) number of upside stats are constructed. Afterwards, stats are generated until the weapon balances out with a rating in range [-2.5, 2.5]. A rating closer to 0 means a weapon is more balanced. 
 - **Weapon Construction & Stat Organization Systems**
	 - There are alot of possibilities for stats in TF2, so to prevent having way too many static stat strings to have to search for and manage, I've tried my best to reduce the number of individual stats while still keeping the number of possibilities. Currently, the methods used are stat categories, stat templates, and split & dynamic stats.
    - **Stat Categories**: Stats are currently split into 6 categories: Special, Offensive, Defensive, Utility, Projectile, and Exclusive. Most of these are pretty self explanitory, but I'll still give a short explaination to them.
	    - *Special* stats contain stats without percentage & number values and are mostly gimmicks Some stats (such as No random crits) that have no percentage value are outside of the special category, but they're few & far between.
	    - *Offensive* & *Defensive* stats affect offense & defense abilities respectively.
      - *Utility* stats could be a variety of things, mostly boosting speed & efficency e.g. movement & switch speed & capture rate.
      - *Projectile* stats are stats exclusive to projectile weapons (some stats also being explosive exclusive as well)
      - *Exclusive* stats are the rest of the stats that are either weapon or class specific.
    - **Stat Templates & Dynamic Stats**: Stat templates help with stats that have multiple possibilities but could be condensed into one stat, such as typed damage resistance / vulnerability or critical hit conditions, or stats that have different wording depending on whether its an upside or downside. The way that this is utilized is WordFlags, a '$' sign followed by a letter which would be replaced with a chosen string from its corresponding array. Wordflags (obviously) affect the weapon rating in different ways too, each string has a corresponding value.
    	- For example, typed damage resistance / vulnerability's template is "$n% $d damage $a $w". $n = weapon modifier value, $d = damage type, $a = upside / downside text string ({"resistance","vulnerability"}), $w = "on wearer" string + modifier (if the weapon is only "when active", the rating modifier is decreased since its not passive).
      - Most stats with these wordflags are also considered dynamic stats, which means they could be used as many times as there are possibilities, such as having multiple types of damage resistances or two On Hit rewards, or also one type damage resistance while having another type damage vulnerability (like The Fists of Steel).
    - **Split Stats**: Whilst some stats havent appeared as a downside (such as jump height), they could possibly work perfectly fine as a downside. Some stats can only be an upside though, and the oppisite is true too, some are only negative. Some stats have a downside similar, such as conditional critical hits and no random critical hits, but they're still different stats. To save space, I've grouped together stats that are upside / downside exclusive into one stat slot that changes weather the stat modifier is positive or negative.
- **Stat Flags & Stat Pairs**
	- Some stats, like "Critical hits force victim to laugh" and "Critical hits deal no damage" for The Holiday Punch, always come in pairs, and it would be either unbalanced or just plain confusing if they didnt. So a system was implemented that detects one of these stats and ensures that the other stat in the pair is included.
- **Blacklist / Whitelist System**
	- This system ensures that a weapon's stats make sense. It detects the weapon's class, type, slot, and attributes and blacklists stats (or whitelists exclusive stats in the projectile or exclusive category) based on the aforementioned weapon data.
  - The blacklist system also makes sure stats arent reused unless they are either split, which means each side of the stat can only be used once, or dynamic, which means each possibility can only be used once.
- **Debug Features**
	- There are settings you can modify, allowing you to select specific weapons, classes, or slots to generate, as well as changing some values and paramaters. More explaination is provided when you access the settings.
- **Other Features**
	- Stats with a number value of 35 are changed to 33, and a value of 65 is changed to 66

### Planned Feature Implementation
###### All of these features will be in the full release unless scrapped
- **Weapon Seed Improvements / Redesign**
	- I built the randomization in a way that, in theory, has support for weapon seeds, but it's not fully implemented and could probably be improved to be more efficent and prevent long seeds. I also have a very basic randomizer function that I want to replace with something like random_device.
- **Better Debugging & Logging**
	- Currently, only the console is used for logging and debugging, which has a limited history and is cleared each time the program is ran.
- **Saved Preferences**
	- Currently, if you want to customize generation, you have to enter paramaters every time you run the program. Saving presets & the previous inputs would be a great quality of life improvement.
- **Non-Consle Based UI**
	- The current UI is ok, though a more refined, user friendly interface would make use easier, especially for customization and organization.
***
### Links
**TF2 Generator**:  
Stable Source Code Releases:  
[GitHub](https://github.com/AintSoSunny/Sunnys-TF2-Weapon-Generator) (0.2.8)  
[repl.it](https://replit.com/@SunnySideDown/Sunnys-TF2-Weapon-Generator-Stable-028-Release) (0.2.8)  
Live-ish Nightly Development Builds:  
[GitHub](https://github.com/AintSoSunny/Sunnys-TF2-Weapon-Generator/tree/nightly) (0.2.9a1)
[repl.it](https://replit.com/@AintSoSunny/Sunnys-TF2-Weapon-Generator) (0.2.9a1)

**Contact**:  
Tumblr: [AintSoSunny.tumblr.com](https://AintSoSunny.tumblr.com)  
Twitter: [@AintSoSunny](https://twitter.com)  
Discord: AintSoSunny#0404  
E-mail: [aintsosunny@gmail.com](mailto:aintsosunny@gmail.com)

*Note: If you have issues, I'd rather you post them to the github repo, but if you're unfamiliar with GitHub or want to contact me directly, Tumblr is your best bet.*
***
## Changelog: v.0.2.9a1

Man, its been a while, huh.
- **Updated the README file**
	- Besides the changelog and description, the README is much more in-depth, now showing the features of this generator, a less in-depth summary, planned features, and links related to the generator
- **Debut of 'stable' and 'nightly' builds**
	- I would like to more often push my updates to github so I decided to just make a new branch which contains my disaster WIP builds that are barely stable (and so I can work more easily from desktop instead of exclusively from repl.it)     
- **Added 'Dynamic Stats'**  
	- Dynamic stats are similar to 'Positive-Negative Split Stats' in the sense that they can be used more than once, but instead of only being used twice, they can be used as many times as possible without creating duplicates.
- **Added Weapon Property: Is Sword**  
	- Shows if a weapon has the 'sword' stat (long melee range & deploy & holster penalty).
- **Added Stat: melee range**
- **Slightly tweaked seed system & random number generation**
- **Fixed too many upsides being generated due to trying to add statFlags, now the ability to add max upsides has been limited**
- **Fixed Medigun's downside blacklist copying the crit gimmick blacklist instead of having its own**
- **Fixed 'On Hit temporary stat boosts' having a rating of zero regardless of paramaters**
- **Fixed Sniper Rifles' 'coating enemies' stat being able to show up on 'On Kill' stats**
- **Fixed Sniper Rifles' 'coating enemies' stat being able to show up on Jarate**
- **Fixed stat flag 11 pointing to a non-exsistant stat, causing it to fail every time**
- **Fixed Medic and Sniper having swapped places in the class list causing them to have some of eachother's class specific stats instead of their own**
- **Fixed wording of some group affecting stats for Battle Banners and Mediguns**
- **Modified a 'Per Shot:' outcome that modifies stats for a period of time to not last as long**
- **Modified some names of the stat categories**
	- 'Uncategorized' was renamed to 'Special'
  - 'Special' was renamed to 'Constructor'
- **Modified criteria of statsToOutside to include stats for Battle Banners & Mediguns that are on wearer effects instead of group effects**
- **Fixed debugging tools & other bugs**
- **Updated & balanced some stat ratings**
