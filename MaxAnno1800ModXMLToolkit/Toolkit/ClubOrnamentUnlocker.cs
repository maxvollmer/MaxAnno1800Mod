/*
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
*/
using MaxAnno1800ModXMLToolkit.Assets;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace MaxAnno1800ModXMLToolkit.Toolkit
{
    class ClubOrnamentUnlocker
    {
        public static readonly string SCOPE_BACKUP_NAME = "MaxAnno1800ModBackupScope";

        public static void UnlockClubOrnaments(XDocument assetsXML)
        {
            foreach (var scope in AssetsXMLHelper.GetAssetsByKey(assetsXML, "Template", "OrnamentalBuilding").Descendants("Locked").Descendants("Scope").Where(scope => scope.Value == "Account").ToList())
            {
                scope.Parent.Add(new XElement("DefaultLockedState", "0"));
                scope.Name = SCOPE_BACKUP_NAME;
            }
        }

        public static void LockClubOrnaments(XDocument assetsXML)
        {
            foreach (var scope in AssetsXMLHelper.GetAssetsByKey(assetsXML, "Template", "OrnamentalBuilding").Descendants("Locked").Descendants(SCOPE_BACKUP_NAME).ToList())
            {
                scope.Parent.Descendants("DefaultLockedState").Remove();
                scope.Name = "Scope";
            }
        }

        public static bool AreClubOrnamentsInstalled(XDocument assetsXML)
        {
            return assetsXML.Descendants(SCOPE_BACKUP_NAME).Any();
        }
    }
}
