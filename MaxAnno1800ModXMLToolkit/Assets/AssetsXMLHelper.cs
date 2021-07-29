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
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace MaxAnno1800ModXMLToolkit.Assets
{
    class AssetsXMLHelper
    {
        public static IEnumerable<XElement> GetAssetsByKey(XDocument assetXML, string key, string val)
        {
            return assetXML.Descendants("Asset").Where(a => a.Descendants(key).Where(k => k.Value == val).Any());
        }

        public static XElement GetAssetByName(XDocument assetXML, string name)
        {
            return GetAssetsByKey(assetXML, "Name", name).FirstOrDefault();
        }

        public static XElement GetAssetByGUID(XDocument assetXML, string guid)
        {
            return GetAssetsByKey(assetXML, "GUID", guid).FirstOrDefault();
        }

        public static IEnumerable<XElement> GetAssetPools(XDocument assetsXML, params string[] names)
        {
            return names.Select(name => GetAssetByName(assetsXML, name)?.Descendants("Item")?.FirstOrDefault()?.Parent);
        }

        public static IEnumerable<XElement> GetConstructionCategories(XDocument assetsXML, params string[] names)
        {
            return names.Select(name => GetAssetByName(assetsXML, name)?.Descendants("BuildingList")?.FirstOrDefault());
        }

    }
}
