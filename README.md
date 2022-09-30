# TF2-Weapon-Generator
A Team Fortress 2 weapon generator built from the ground up in C++.
Version 0.2
This generator tries to make *semi*-balanced weapons using a rating system, each stat has a rating, a given number of upsides are calculated (2 for right now) and then downsides are generated until the weapon balances out.
Wearable weapons and objectively bad weapons (Syringe gun, Heavy's Shotgun) have a lower rating from the get-go due to the wearables taking a weapon away from a slot and the bad weapons being, well, bad. 
**Special function weapons like Lunchboxes, Battle Banners, Jars, & Mediguns are currently unsupported**. These features, along with multiple types of meters (ex. Soda Popper, Baby Faces Blaster, & Eyelander) & other Alt-Fire functions (ex. Sandman) are coming soon. There may also be custom stats by yours truly implemented in some empty spaces...