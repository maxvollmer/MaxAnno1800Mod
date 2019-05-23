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
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace MaxAnno1800ModXMLToolkit.Toolkit
{
    class BuildPermitBuildingToOrnamentalBuildingConverter
    {
        public static readonly string ASSET_BACKUP_NAME = "MaxAnno1800ModAssetBackup";

        private static readonly OrderedDictionary UnusedOrnamentsToBuildPermits = new OrderedDictionary()
        {
            /*order important, as this is the order assets will appear in the building menu */

            { /*Cultural Ornaments*/ 102173         , /*Mosaic Paving*/ 102466 },

            { /*Hedge End*/ 102167                  , /*Morris Column*/ 102464 },
            { /*Hedge Wall (T-Junction)*/ 102169    , /*Billboard*/ 102465 },
            { /*Hedge Crossing*/ 102171             , /*Flagpole*/ 102467 },

            { /*Fence (Straight)*/ 102161           , /*Channel (Straight)*/ 102472 },
            { /*Railings Wall (T-Junction)*/ 102170 , /*Channel Fountain (Straight)*/ 102468 },
            { /*Railings Door (Archway)*/ 102162    , /*Channel Bridge*/ 102469 },
            { /*Railings Corner*/ 102163            , /*Channel (Angle)*/ 102471 },
            { /*Railings End*/ 102164               , /*Channel (End)*/ 102470 },

            { /*Hedge (Straight)*/ 102165           , /*Columns (Straight)*/ 102461 },
            { /*Hedge Corner*/ 102166               , /*Columns (Angle)*/ 102463 },

            { /*Railings Crossing*/ 102172          , /*World Fair Pavillion*/ 102474 },
            { /*Benches*/ 102160                    , /*World Fair Gate*/ 102473 },
            { /*Statue*/ 102168                     , /*World Fair Tower*/ 102475 },
        };

        private static string GetPath(XElement node)
        {
            string path = node.Name.ToString();
            XElement currentNode = node;
            while (currentNode.Parent != null)
            {
                currentNode = currentNode.Parent;
                path = currentNode.Name.ToString() + @"\" + path;
            }
            return path;
        }

        public static void ToOrnamental(XDocument assetsXML)
        {
            var assetPools = AssetsXMLHelper.GetAssetPools(assetsXML, "asset pool splendour elements (all)", "asset pool park investors", "asset pool park obreros");
            var constructionCategories = AssetsXMLHelper.GetConstructionCategories(assetsXML, "moderate investors city (tier)", "moderate city decorations (category)", "sa obrero city (tier)", "sa city decorations (category)");

            foreach (DictionaryEntry pair in UnusedOrnamentsToBuildPermits)
            {
                var unusedOrnamentAsset = AssetsXMLHelper.GetAssetByGUID(assetsXML, pair.Key.ToString());
                var buildPermitBuildingAsset = AssetsXMLHelper.GetAssetByGUID(assetsXML, pair.Value.ToString());

                // Create backup
                unusedOrnamentAsset.Parent.Add(new XElement(ASSET_BACKUP_NAME, unusedOrnamentAsset.Attributes(), unusedOrnamentAsset.Elements()));

                // Copy simple values
                unusedOrnamentAsset.Descendants("Name").First().ReplaceWith(new XElement(buildPermitBuildingAsset.Descendants("Name").First()));
                unusedOrnamentAsset.Descendants("IconFilename").First().ReplaceWith(new XElement(buildPermitBuildingAsset.Descendants("IconFilename").First()));
                unusedOrnamentAsset.Descendants("Variations").First().ReplaceWith(new XElement(buildPermitBuildingAsset.Descendants("Variations").First()));
                try
                {
                    var bla = unusedOrnamentAsset.Descendants("OrnamentUnit").First();
                    bla.ReplaceWith(new XElement(buildPermitBuildingAsset.Descendants("OrnamentUnit").First()));
                }
                catch(Exception)
                {
                    Console.WriteLine("\n\n\nunusedOrnamentAsset:\n" + unusedOrnamentAsset + "\n\n\n");
                    Console.WriteLine("\n\n\nbuildPermitBuildingAsset:\n" + buildPermitBuildingAsset + "\n\n\n");
                    throw;
                }
                unusedOrnamentAsset.Descendants("OrnamentDescritpion").First().ReplaceWith(new XElement(buildPermitBuildingAsset.Descendants("OrnamentDescritpion").First()));
                unusedOrnamentAsset.Descendants("Text").First().ReplaceWith(new XElement(buildPermitBuildingAsset.Descendants("Text").First()));

                // Copy (or clear) BuildModeRandomRotation
                unusedOrnamentAsset.Descendants("BuildModeRandomRotation").FirstOrDefault()?.Remove();
                var buildModeRandomRotation = buildPermitBuildingAsset.Descendants("BuildModeRandomRotation").FirstOrDefault();
                if (buildModeRandomRotation != null)
                {
                    unusedOrnamentAsset.Descendants("Building").First().Add(new XElement(buildModeRandomRotation));
                }

                // Set price
                int ornamentUnit = Math.Max(Convert.ToInt32(buildPermitBuildingAsset.Descendants("OrnamentUnit").FirstOrDefault()?.Value ?? "1"), 1);
                unusedOrnamentAsset.Descendants("Cost").First().ReplaceWith(
                    new XElement("Cost",
                        new XElement("Costs",
                            new XElement("Item", new XElement("Ingredient", "1010017"), new XElement("Amount", ornamentUnit * 1000)),
                            new XElement("Item", new XElement("Ingredient", "1010196")),
                            new XElement("Item", new XElement("Ingredient", "1010205")),
                            new XElement("Item", new XElement("Ingredient", "1010218")),
                            new XElement("Item", new XElement("Ingredient", "1010207")),
                            new XElement("Item", new XElement("Ingredient", "1010202"))
                        )
                    )
                );

                // Add asset to asset pools and construction categories
                string guid = pair.Key.ToString();
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

        public static void ToPermit(XDocument assetsXML)
        {
            var assetPools = AssetsXMLHelper.GetAssetPools(assetsXML, "asset pool splendour elements (all)", "asset pool park investors", "asset pool park obreros");
            var constructionCategories = AssetsXMLHelper.GetConstructionCategories(assetsXML, "moderate investors city (tier)", "moderate city decorations (category)", "sa obrero city (tier)", "sa city decorations (category)");

            foreach (DictionaryEntry pair in UnusedOrnamentsToBuildPermits)
            {
                string guid = pair.Key.ToString();

                var unusedOrnamentAsset = AssetsXMLHelper.GetAssetByGUID(assetsXML, pair.Key.ToString());
                var unusedOrnamentAssetBackup = assetsXML.Descendants(ASSET_BACKUP_NAME).Descendants("GUID").FirstOrDefault(x => x.Value == guid).Ancestors(ASSET_BACKUP_NAME).First();

                if (!unusedOrnamentAssetBackup.Descendants("OrnamentUnit").Any())
                {
                    Console.WriteLine("\n\n\nunusedOrnamentAsset:\n" + unusedOrnamentAsset + "\n\n\n");
                    Console.WriteLine("\n\n\nunusedOrnamentAssetBackup:\n" + unusedOrnamentAssetBackup + "\n\n\n");
                }

                // Delete cheat asset
                unusedOrnamentAsset.Remove();

                // Restore backup
                unusedOrnamentAssetBackup.Name = "Asset";

                // Remove asset from asset pools and construction categories
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

        public static bool AreCheatOrnamentsInstalled(XDocument assetsXML)
        {
            return assetsXML.Descendants(ASSET_BACKUP_NAME).Any();
        }
    }
}
