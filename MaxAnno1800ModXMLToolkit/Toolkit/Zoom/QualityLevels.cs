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

namespace MaxAnno1800ModXMLToolkit.Toolkit.Zoom
{
    class QualityLevels
    {
        public class QualityLevel
        {
            public double ViewDistance { get; }
            public double ObjectViewDistance { get; }
            public double TerrainCacheSizeFactor { get; }
            public double MinimumObjectSizeInPixels { get; }
            public double PropFadeDistanceMultiplier { get; }
            public Dictionary<int, double> LODDistances { get; }
            public QualityLevel(double viewDistance, double objectViewDistance, double terrainCacheSizeFactor, double minimumObjectSizeInPixels, double propFadeDistanceMultiplier, Dictionary<int, double> lodDistances)
            {
                ViewDistance = viewDistance;
                ObjectViewDistance = objectViewDistance;
                TerrainCacheSizeFactor = terrainCacheSizeFactor;
                MinimumObjectSizeInPixels = minimumObjectSizeInPixels;
                PropFadeDistanceMultiplier = propFadeDistanceMultiplier;
                LODDistances = lodDistances;
            }
        }

        public static readonly Dictionary<int, QualityLevel> Default = new Dictionary<int, QualityLevel>()
        {
            { 0, new QualityLevel(300, 300, 1, 12, 120, new Dictionary<int, double>()
                {
                    { 0, 0 },
                    { 1, 0 },
                    { 2, 40 },
                    { 3, 110 },
                    { 4, 300 },
                })
            },
            { 1, new QualityLevel(325, 325, 1.1, 12, 50, new Dictionary<int, double>()
                {
                    { 0, 0 },
                    { 1, 20 },
                    { 2, 40 },
                    { 3, 130 },
                    { 4, 325 },
                })
            },
            { 2, new QualityLevel(350, 350, 1.2, 10, 30, new Dictionary<int, double>()
                {
                    { 0, 20 },
                    { 1, 40 },
                    { 2, 70 },
                    { 3, 150 },
                    { 4, 350 },
                })
            },
            { 3, new QualityLevel(400, 400, 1.35, 8, 20, new Dictionary<int, double>()
                {
                    { 0, 20 },
                    { 1, 50 },
                    { 2, 90 },
                    { 3, 180 },
                    { 4, 400 },
                })
            },
            { 4, new QualityLevel(500, 500, 1.5, 6, 20, new Dictionary<int, double>()
                {
                    { 0, 30 },
                    { 1, 60 },
                    { 2, 100 },
                    { 3, 200 },
                    { 4, 500 },
                })
            }
        };

        public static readonly Dictionary<int, QualityLevel> Extended = new Dictionary<int, QualityLevel>()
        {
            { 0, new QualityLevel(5000, 300, 1, 12, 120, new Dictionary<int, double>()
                {
                    { 0, 0 },
                    { 1, 0 },
                    { 2, 40 },
                    { 3, 110 },
                    { 4, 300 },
                })
            },
            { 1, new QualityLevel(5000, 325, 1.1, 12, 50, new Dictionary<int, double>()
                {
                    { 0, 0 },
                    { 1, 20 },
                    { 2, 40 },
                    { 3, 130 },
                    { 4, 325 },
                })
            },
            { 2, new QualityLevel(5000, 350, 1.2, 10, 30, new Dictionary<int, double>()
                {
                    { 0, 20 },
                    { 1, 40 },
                    { 2, 70 },
                    { 3, 150 },
                    { 4, 350 },
                })
            },
            { 3, new QualityLevel(5000, 400, 1.35, 8, 20, new Dictionary<int, double>()
                {
                    { 0, 20 },
                    { 1, 50 },
                    { 2, 90 },
                    { 3, 180 },
                    { 4, 400 },
                })
            },
            { 4, new QualityLevel(5000, 2000, 3, 4, 10, new Dictionary<int, double>()
                {
                    { 0, 60 },
                    { 1, 100 },
                    { 2, 200 },
                    { 3, 1000 },
                    { 4, 5000 },
                })
            }
        };
    }
}
