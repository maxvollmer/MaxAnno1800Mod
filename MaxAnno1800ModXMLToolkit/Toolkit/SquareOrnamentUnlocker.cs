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
    class SquareOrnamentUnlocker
    {
        public static HashSet<string> SquareGuids { get; } = new HashSet<string>()
        {
            "102159",
           // "102114",
        };

        public static void UnlockSquareOrnament(XDocument assetsXML)
        {
            var assetPools = AssetsXMLHelper.GetAssetPools(assetsXML, "asset pool city elements (all)", "asset pool city artisans", "asset pool culture obreros");
            var constructionCategories = AssetsXMLHelper.GetConstructionCategories(assetsXML, "moderate artisans city (tier)", "moderate city decorations (category)", "sa obrero city (tier)", "sa city decorations (category)");

            // Add asset to asset pools and construction categories
            foreach (var guid in SquareGuids)
            {
                foreach (var assetPool in assetPools)
                {
                    assetPool.Add(new XElement("Item", new XElement("Asset", guid)));
                }
                foreach (var constructionCategory in constructionCategories)
                {
                    constructionCategory.Add(new XElement("Item", new XElement("Building", guid)));
                }
            }
        }

        public static void LockSquareOrnament(XDocument assetsXML)
        {
            var assetPools = AssetsXMLHelper.GetAssetPools(assetsXML, "asset pool city elements (all)", "asset pool city artisans", "asset pool culture obreros");
            var constructionCategories = AssetsXMLHelper.GetConstructionCategories(assetsXML, "moderate artisans city (tier)", "moderate city decorations (category)", "sa obrero city (tier)", "sa city decorations (category)");

            // Remove asset from asset pools and construction categories
            foreach (var guid in SquareGuids)
            {
                foreach (var assetPool in assetPools)
                {
                    assetPool.Descendants("Asset").FirstOrDefault(x => x.Value == guid)?.Ancestors("Item")?.FirstOrDefault()?.Remove();
                }
                foreach (var constructionCategory in constructionCategories)
                {
                    constructionCategory.Descendants("Building").FirstOrDefault(x => x.Value == guid)?.Ancestors("Item")?.FirstOrDefault()?.Remove();
                }
            }
        }

        public static bool IsSquareOrnamentInstalled(XDocument assetsXML)
        {
            return AssetsXMLHelper.GetAssetsByKey(assetsXML, "Template", "AssetPool").Descendants("AssetList").Descendants("Asset").Where(a => SquareOrnamentUnlocker.SquareGuids.Contains(a.Value)).Any()
                 || AssetsXMLHelper.GetAssetsByKey(assetsXML, "Template", "ConstructionCategory").Descendants("BuildingList").Descendants("Building").Where(b => SquareOrnamentUnlocker.SquareGuids.Contains(b.Value)).Any();
        }
    }
}
