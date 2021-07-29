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
    class OrnamentBooster
    {
        public static void InstallBoost(XDocument assetsXML)
        {
            foreach (var ornamentalBuilding in AssetsXMLHelper.GetAssetsByKey(assetsXML, "Template", "OrnamentalBuilding"))
            {
                var ornamentUnit = ornamentalBuilding.Descendants("OrnamentUnit").FirstOrDefault();
                if (ornamentUnit == null)
                    continue;

                ornamentUnit.Name = "MaxAnno1800ModOrnamentUnitBackup";

                double price = double.Parse(ornamentalBuilding.Descendants("Costs").FirstOrDefault()?.Descendants("Amount")?.FirstOrDefault()?.Value ?? "0", System.Globalization.CultureInfo.InvariantCulture);
                double originalOrnamentUnit = double.Parse(ornamentUnit.Value, System.Globalization.CultureInfo.InvariantCulture);
                double newOrnamentUnit = originalOrnamentUnit + (price / 1000.0);

                ornamentUnit.Parent.Add(new XElement("OrnamentUnit", newOrnamentUnit.ToString(System.Globalization.CultureInfo.InvariantCulture)));
            }
        }

        public static void UninstallBoost(XDocument assetsXML)
        {
            foreach (var ornamentUnitBackup in assetsXML.Descendants("MaxAnno1800ModOrnamentUnitBackup").ToList())
            {
                ornamentUnitBackup.Parent.Descendants("OrnamentUnit").Remove();
                ornamentUnitBackup.Name = "OrnamentUnit";
            }
        }

        public static bool AreOrnamentsBoosted(XDocument assetsXML)
        {
            return assetsXML.Descendants("MaxAnno1800ModOrnamentUnitBackup").Any();
        }
    }
}
