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
    class VisualObjectToOrnamentalBuildingConverter
    {
        private static readonly HashSet<string> VISUAL_OBJECT_GUIDS = new HashSet<string>()
        {
            "102289",   // cemetery floor
            "101109",   // blake's mansion
            "101011",   // cemetery church
            "101010",   // cemetery building
            "101041",   // cemetery mausoleum father
        };

        public static readonly string VISUALOBJECT_BACKUP_NAME = "MaxAnno1800ModVisualObjectBackup";
        public static readonly string GRASS_ORNAMENT_GUID = "102083";

        public static void ToOrnamental(XDocument assetsXML)
        {
            var constructionCategory = AssetsXMLHelper.GetConstructionCategories(assetsXML, "U-Club reward menu").First();

            var ornamentalBuildingTemplate = AssetsXMLHelper.GetAssetByGUID(assetsXML, GRASS_ORNAMENT_GUID);

            // foreach (var visualObject in AssetsXMLHelper.GetAssetsByKey(assetsXML, "Template", "VisualObject").ToList())
            foreach (var guid in VISUAL_OBJECT_GUIDS)
            {
                var visualObject = AssetsXMLHelper.GetAssetByGUID(assetsXML, guid);
                if (visualObject == null)
                {
                    Console.WriteLine("guid is null: {0}", guid);
                    continue;
                }

                // create new ornament
                var ornamentalBuilding = new XElement(ornamentalBuildingTemplate);
                visualObject.Parent.Add(ornamentalBuilding);

                // Copy simple values
                ornamentalBuilding.Descendants("GUID").First().ReplaceWith(new XElement(visualObject.Descendants("GUID").First()));
                ornamentalBuilding.Descendants("Name").First().ReplaceWith(new XElement(visualObject.Descendants("Name").First()));
                ornamentalBuilding.Descendants("IconFilename").First().ReplaceWith(new XElement(visualObject.Descendants("IconFilename").First()));
                ornamentalBuilding.Descendants("Variations").First().ReplaceWith(new XElement(visualObject.Descendants("Variations").First()));

                // remove text
                ornamentalBuilding.Descendants("Text").Remove();

                // add construction price
                ornamentalBuilding.Descendants("Cost").First().ReplaceWith(new XElement("Cost",
                        new XElement("Costs",
                            new XElement("Item", new XElement("Ingredient", "1010017"), new XElement("Amount", "1000")),
                            new XElement("Item", new XElement("Ingredient", "1010196")),
                            new XElement("Item", new XElement("Ingredient", "1010205")),
                            new XElement("Item", new XElement("Ingredient", "1010218")),
                            new XElement("Item", new XElement("Ingredient", "1010207")),
                            new XElement("Item", new XElement("Ingredient", "1010202"))
                        )
                    )
                );

                // set description (the typo is "correct")
                ornamentalBuilding.Descendants("OrnamentDescritpion").First()?.SetValue("11149");

                // add to U-Club build menu
                //string guid = visualObject.Descendants("GUID").First().Value;
                constructionCategory.Add(new XElement("Item", new XElement("Building", guid)));

                // make backup
                visualObject.Name = VISUALOBJECT_BACKUP_NAME;
            }
        }

        public static void ToVisualObject(XDocument assetsXML)
        {
            var constructionCategory = AssetsXMLHelper.GetConstructionCategories(assetsXML, "U-Club reward menu").First();

            foreach (var visualObjectBackup in assetsXML.Descendants(VISUALOBJECT_BACKUP_NAME).ToList())
            {
                string guid = visualObjectBackup.Descendants("GUID").First().Value;
                AssetsXMLHelper.GetAssetByGUID(assetsXML, guid).Remove();
                constructionCategory.Descendants("Building").FirstOrDefault(x => x.Value == guid)?.Ancestors("Item")?.FirstOrDefault()?.Remove();
                visualObjectBackup.Name = "Asset";
            }
        }

        public static bool AreVisualObjectsOrnaments(XDocument assetsXML)
        {
            return assetsXML.Descendants(VISUALOBJECT_BACKUP_NAME).Any();
        }
    }
}
