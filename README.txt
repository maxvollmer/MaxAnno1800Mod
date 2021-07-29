**************************************************************************************
* 
* MaxAnno1800Mod 0.0.1 by Max Vollmer (https://github.com/maxvollmer/MaxAnno1800Mod)
*  - Adds extended zoom.
*  - Adds square ornament that was missing in the original game.
*  - Enables hidden city ornaments.
*  - Enables club ornaments (including pre-order statue and open-beta chess tables).
*  - (Experimental) Turns some visual buildings into ornamental buildings that can be built.
*  - (Cheat) Gives unrestricted access to all World Fair ornaments.
*  - (Cheat) Boosts attractiveness of ornaments based on their building cost.
* 
* Web: https://www.nexusmods.com/anno1800/mods/2
* 
* License: CC BY-NC 4.0 (https://creativecommons.org/licenses/by-nc/4.0/)
* 
* Each feature can be enabled or disabled individually.
* 
* quickbms by Luigi Auriemma (http://quickbms.com)
* 
* 1800.bms script file by kskudlik (https://github.com/kskudlik/Anno-1800-RDA-Extractor)
* 
* DllExport by Denis Kuzmin (https://github.com/3F/DllExport)
* 
* Mod might break with upcoming game updates.
* No warranties whatsoever. Always backup your game files. Use this mod at your own risk.
* 
* Anno 1800 and all related trademarks belong to Ubisoft.
* 
**************************************************************************************

HOW TO USE:

1. Extract archive into any location of your choice

2. Run MaxAnno1800Mod.exe

3. Follow instructions

4. Enjoy

P.S. Everytime you cheat in a multiplayer game without knowledge and consent of your co-players, the AI that runs this universe deletes a kitten.

**************************************************************************************

KNOWN ISSUES:

1. Names and descriptions of some of the ornaments are wrong. For this to work my tool also has to patch all language files, which I might address in a future version.

2. Unfortunately all ornaments unlocked with this mod are available for building immediately (including those on artisan and investor tiers). I haven't figured out yet how to prevent this. There is a "DefaultLockedState" parameter for assets, but the game seems to ignore it. If anyone knows more, please get in touch!

**************************************************************************************

Compatibility with other mods: As of now, most, if not all, mods for Anno 1800 come as prepatched rda files that replace the original game files. This means that if 2 mods replace the same rda file, you can only install 1, but not both mods. Since this mod actively patches the existing rda files, you can first "install" another mod, and then run this tool.

I am thinking about creating a generic mod tool that would allow modders to create mods for Anno 1800, so that multiple mods can co-exist. The tool would allow users to easily add and remove such content mods. (Similar to SMAPI/Content Patcher for SDV.) However before doing so, I want to wait for community feedback, so if you think this is a great idea, please leave a comment!

**************************************************************************************

A bit more detailed explanation what this does:

1) Extended zoom:

 - Adds 6 additional zoom levels.
 - Lowest zoom level goes down to 1m above ground.
 - Highest zoom level goes up to 1800m above ground.
 - Max view distance is increased to 5km in all quality settings.
 - Might affect performance on non-high-end PCs.

2) Square ornament:

 - Adds a square ornament to the artisan city ornaments build menu.
 - It fits perfectly with the other city ornaments, e.g. city benches or the news stand.

 3) Hidden city ornaments:

 - A bunch of ornaments used in the campaign. Some statues, a fountain, another square.
 - Accessible in the artisan city ornaments build menu.

 4) Club ornaments:

 - Enables all Ubisoft club reward ornaments: Chess tables, lion statue, big park fountain and 1602 monument.

 5) (Experimental) Visual buildings ornamentas:

 - Use at own risk. Turns some visual buildings into ornamental buildings:
 - cemetery church, cemetery decorative building, cemetery mausoleum, cemetery ground/square (similar to the city square, but slightly lighter), blake's mansion.
 - Made accessible in U-Club reward build menu.
 - Please note that if you disable this feature you won't be able to move, demolish or otherwise interact with any visual buildings you have built through this feature, as the game won't treat them as buildings without this mod. So make sure you demolish all such buildings before removing this mod.

 6) (Cheat) Unrestricted access to all World Fair ornaments:

 - Ornaments that are usually only available through architecture events in the World's Fair become available in the investor city ornaments build menu.
 - Please note that this is a hack.
 - If you play in multiplayer, and your co-players do not have these ornaments enabled, then your co-players will see a bunch of "normal" ornaments instead.
 - If you uninstall this mod, these ornaments will turn into "normal" ornaments.
 - Normal ornaments: Hedge ornaments, fence ornaments, city square, city statue.
 - (Note that this refers only to the cheat World Fair ornaments, all other ornaments you built through this mod remain on your island after uninstalling and are correctly visible in multiplayer.)

 7) (Cheat) ornament attractiveness boost:

 - Attractiveness of ornaments in the original game is based on how much space they use. With this enabled, the price they cost is added to the effect they have.
 - 1000 coins are equivalent to 1 square of space.
