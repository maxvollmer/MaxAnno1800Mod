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
using MaxAnno1800ModXMLToolkit.Toolkit.Zoom;

namespace MaxAnno1800ModXMLToolkit.Toolkit
{
    class ZoomInstaller
    {
        private static void SetViewDistances(XDocument viewDistanceXML, Dictionary<int, QualityLevels.QualityLevel> viewDistanceSettings)
        {
            foreach (var pair in viewDistanceSettings)
            {
                var index = pair.Key;
                var qualityLevel = viewDistanceXML.Descendants("QualityLevel" + index);

                qualityLevel.Descendants("ViewDistance").First().Value = pair.Value.ViewDistance.ToString(System.Globalization.CultureInfo.InvariantCulture);
                qualityLevel.Descendants("ObjectViewDistance").First().Value = pair.Value.ObjectViewDistance.ToString(System.Globalization.CultureInfo.InvariantCulture);
                qualityLevel.Descendants("TerrainCacheSizeFactor").First().Value = pair.Value.TerrainCacheSizeFactor.ToString(System.Globalization.CultureInfo.InvariantCulture);
                qualityLevel.Descendants("MinimumObjectSizeInPixels").First().Value = pair.Value.MinimumObjectSizeInPixels.ToString(System.Globalization.CultureInfo.InvariantCulture);
                qualityLevel.Descendants("PropFadeDistanceMultiplier").First().Value = pair.Value.PropFadeDistanceMultiplier.ToString(System.Globalization.CultureInfo.InvariantCulture);

                foreach (var lodPair in pair.Value.LODDistances)
                {
                    qualityLevel.Descendants("LOD" + lodPair.Key).First().Value = lodPair.Value.ToString(System.Globalization.CultureInfo.InvariantCulture);
                }
            }
        }

        public static void InstallZoom(XDocument viewDistanceXML, XDocument cameraXML)
        {
            var cameraPresets = cameraXML.Descendants("Normal").First().Descendants("Presets").First();
            var cameraSettings = cameraXML.Descendants("Normal").First().Descendants("Settings").First();

            foreach (var pair in ZoomLevels.Extended)
            {
                string id = pair.Key.ToString();
                var cameraPreset = cameraPresets.Descendants("Preset").Where(p => p.Attribute("ID").Value == id).FirstOrDefault();
                if (cameraPreset == null)
                {
                    cameraPreset = new XElement(cameraPresets.Descendants("Preset").First());
                    cameraPreset.Attribute("ID").Value = id;
                    cameraPresets.Add(cameraPreset);
                }
                cameraPreset.Attribute("Height").Value = pair.Value.Dist.ToString(System.Globalization.CultureInfo.InvariantCulture);
                cameraPreset.Attribute("Fov").Value = pair.Value.Fov.ToString(System.Globalization.CultureInfo.InvariantCulture);
            }

            cameraSettings.Attribute("MinZoomPreset").Value = ZoomLevels.Extended.Keys.Min().ToString();
            cameraSettings.Attribute("MaxZoomPreset").Value = ZoomLevels.Extended.Keys.Max().ToString();
            cameraSettings.Attribute("MinFromHeight").Value = ZoomLevels.MinFromHeight.Extended.ToString(System.Globalization.CultureInfo.InvariantCulture);
            cameraSettings.Attribute("MinTerrainDistance").Value = ZoomLevels.MinTerrainDistance.Extended.ToString(System.Globalization.CultureInfo.InvariantCulture);

            SetViewDistances(viewDistanceXML, QualityLevels.Extended);
        }

        public static void UninstallZoom(XDocument viewDistanceXML, XDocument cameraXML)
        {
            var cameraPresets = cameraXML.Descendants("Normal").First().Descendants("Presets").First();
            var cameraSettings = cameraXML.Descendants("Normal").First().Descendants("Settings").First();

            foreach (var cameraPreset in cameraPresets.Descendants("Preset").ToList())
            {
                int id = Convert.ToInt32(cameraPreset.Attribute("ID").Value);

                if (ZoomLevels.Default.Keys.Contains(id))
                {
                    cameraPreset.Attribute("Height").Value = ZoomLevels.Default[id].Dist.ToString(System.Globalization.CultureInfo.InvariantCulture);
                    cameraPreset.Attribute("Fov").Value = ZoomLevels.Default[id].Fov.ToString(System.Globalization.CultureInfo.InvariantCulture);
                }
                else
                {
                    cameraPreset.Remove();
                }
            }

            cameraSettings.Attribute("MinZoomPreset").Value = ZoomLevels.Default.Keys.Min().ToString();
            cameraSettings.Attribute("MaxZoomPreset").Value = ZoomLevels.Default.Keys.Max().ToString();
            cameraSettings.Attribute("MinFromHeight").Value = ZoomLevels.MinFromHeight.Default.ToString(System.Globalization.CultureInfo.InvariantCulture);
            cameraSettings.Attribute("MinTerrainDistance").Value = ZoomLevels.MinTerrainDistance.Default.ToString(System.Globalization.CultureInfo.InvariantCulture);

            SetViewDistances(viewDistanceXML, QualityLevels.Default);
        }

        public static bool IsZoomInstalled(XDocument viewDistanceXML, XDocument cameraXML)
        {
            foreach (var pair in QualityLevels.Extended)
            {
                var index = pair.Key;
                var qualityLevel = viewDistanceXML.Descendants("QualityLevel" + index);
                var viewDistance = qualityLevel?.Descendants("ViewDistance").FirstOrDefault()?.Value ?? "0";
                var extendedViewDistance = pair.Value.ViewDistance.ToString(System.Globalization.CultureInfo.InvariantCulture);
                if (viewDistance == extendedViewDistance)
                {
                    return true;
                }
            }

            var cameraSettings = cameraXML.Descendants("Normal").First().Descendants("Settings").First();
            return cameraSettings.Attribute("MaxZoomPreset").Value == ZoomLevels.Extended.Keys.Max().ToString();
        }
    }
}
