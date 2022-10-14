# TF2-Weapon-Generator Full Changelog

## v.0.2.2
- **Added more weapon stats, such as weapon & class specific stats, meters, and some stats that came in pairs, e.g. The Beggar's Bazooka's barrage mechanic.**
- **Added stat flags in order to be able to pair stats together, as well as uphold the rule that all passive upsides must be paired with a passive downside.**
 - **Added the blacklist / whitelist system**
 	- This system makes sure weapons don't have stats that are impossible and / or don't make sense, as well as whitelists stats that are closed off to other weapons.
	- It is split into 4 parts: weapon slot, weapon type, class, & other weapon properties. Each part relates to a different attribute of the weapon. They are split in order to give each part a priority. From lowest to highest, the priotity is as follows: class, slot, properties, type. The priority is used to resolve conflicts if there are multple blacklists for each weapon.
	- This system utilizes the stats used system, changing the values of a stat's corresponding slot to allow / disallow stats from being generated from the get-go.
- **Added new stat categories: Projectile, Exclusive, & Special**
	- **Projectile**: Any stat exclusive to projectile & explosive based weapons e.g. projectile speed, blast radius, etc.
  - **Exclusive**: Any stat that is class or weapon exclusive. The projectile stats are excluded because they all relate to one specific property of the weapon besides the class or weapon type. This category is also already pretty bulky without the projectiles.
  - **Special**: This category does not contain stats, but constructors for special weapons such as coatables and lunchboxes that previously weren't able to be generated correctly. So far we have constructors for Lunchboxes, Battle Banners, coatables, & adding custom meters

- **Added new weapon properties: Has Meter, Projectile, Explosive, Coatable, Throwable, Clipless, Rapid Fire**
	- **Has Meter:** Weapons that already have a meter; e.g. Sniper Rifle, Sheild, etc.
  - **Projectile:** Projectile based weapons (including explosives); e.g. Crossbow, Grendade Launcher, etc.
  - **Explosive:** Projectile based weapons that explode, e.g. Rocket Launcher, Flare Gun, Grenade Launcher.
  - **Coatable:** Weapons that coat players in liquid giving them a debuff; e.g. Non-Milk Substance, Jar-Based Karate, Gas Canister
  - **Throwable:** Like coatables but weapons that can either be thrown or consumed (not always useable); e.g. Cleaver, Battle Banner, Lunchbox, etc.
  - **Clipless:** Weapons that do not have a clip; e.g. Flare Gun, Minigun, Sniper Rifle, etc.
  - **Rapid Fire:** Weapons with a high rate of fire; e.g. Pistol, Minigun, SMG

- **Combined some stats that don't have an upside / downside into one**
	- The stat that is chosen depends on if you're generating an upside or a downside.
  - These stats only add '1' to the used stat system in order to be able to have both stats able to be generated.
- **Updated the stats used system to work with the new blacklist system, new stat categories, & split stats**
- **Added more debugging tools & fixed other bugs**
- **Updated non-exsistant localization files**

## v.0.2
- **Finished adding universal weapon stats**

- **Added weapon properties: Wearable, Already Bad**
	- **Wearable:** Weapons that are worn on the body; e.g. Boots, Sheild, etc.
  - **Already Bad:** Weapons that are, well, bad; e.g. Syringe Gun, Gas Canister, etc.
  - **Has Alt-Fire:** Weapons that already have an alt-fire; e.g. Flame Thrower, Minigun, Sniper Rifle, etc.  
  - The first two categories have a modified rating from the start depending on the weapon, such as Boots replacing Demoman's Grenade Launcher will have less of a rating deficit than the Sheild replacing Demoman's Stickybomb Launcher.

- **Added a system to track the stats used on a weapon to make sure duplicate stats are not generated**
	 - The system uses an array of vectors filled with zeros, each slot representing a stat. Once a stat is used, the number is changed to 1.
   - The coordinates of the numbers are reflective of the stat category number and the substat number. For example, attack has a category number of one, and reload time has a substat value of 9, so its co-ordinates are {1,9}.
- **Added non-exsistant localization files**

## v.0.1
- **Started adding weapon types as well as basic, universal stats from all of the weapons in Team Fortress 2**
	- Until the blacklist is implemented, some class & weapon specific stats like cloak duration and spin up time will not be included. Weapons like Lunchboxes, Battle Banners, Jars, and Mediguns will also remain

- **Added stat categories: Uncaregorized, Attack, Defense, Utility**
	- **Uncategorized**: Any stat that doesn't fit in the categories and / or does not have any varying values; e.g. The 'Sword Atrribute' (melee range & switch speed), The Machina's 'tracer rounds', etc.
  - **Attack**: Any stat that affects your ability to deal damage, e.g. damage, attack speed, conditional crits & buffs, etc.
  - **Defense**: Any stat that affects your ability to tank damage, e.g. damage resistance, max health, etc.
  - **Utility**: Any stat that affects general uses & aspects of the weapon; e.g. movement speed, switch speed, capture rate, etc

- **Weapon rating system created**
	- Each stat has a seperate rating determined by a base rating, the value modifier, a rating modifier, and a rating bonus / penalty.
  - The complete stats rating is determined by (v * b + s) * m where v = the value modifier, b = the rating base, s = the rating bonus, and m = the rating modifier.
  - The value modifier is a number, usually ranging from 2-20 (some stats have different ranges), determines the number value on the stat, e.g. +20%, -15%, or +4. This modifier is multiplied with the value interval, usually 5, and then displayed on the stat. The value interval does not affect rating. 
  - The base rating is from the stat's template. For example, a damage bonus / penalty has a base rating of 5. Most of the rating system uses this as a baseline. More complex stats, such as conditional crits / minicrits, can have multiple base ratings determined by, in this case, which type of crits are used.
  - The stat modifier affects the rating of a weapon, usually determined by a condition or property of a stat, such as 'vs burning players'.
  - The stat bonus is currently unused but it will add or subtract a flat value to the rating before the weapon modifier is applied.
  - The weapon stats are calculated by generating a given number of upsides, and then generating downsides until the weapon is 'balanced', or the rating is in a range of 5 to -5.

- **Randomly generated the localization files**