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
    class ZoomLevels
    {
        public struct ZoomLevel
        {
            public double Dist { get; }
            public double Fov { get; }
            public ZoomLevel(double dist, double fov)
            {
                Dist = dist;
                Fov = fov;
            }
        }

        public struct ZoomSetting
        {
            public double Default { get; }
            public double Extended { get; }
            public ZoomSetting(double def, double extended)
            {
                Default = def;
                Extended = extended;
            }
        }

        public static ZoomSetting MinFromHeight { get; } = new ZoomSetting(5.0, 1.0);
        public static ZoomSetting MinTerrainDistance { get; } = new ZoomSetting(2.0, 1.0);

        public static readonly Dictionary<int, ZoomLevel> Default = new Dictionary<int, ZoomLevel>()
        {
            { -1, new ZoomLevel(10, 0.675) },
            { 0, new ZoomLevel(12.5, 0.65) },
            { 1, new ZoomLevel(15, 0.625) },
            { 2, new ZoomLevel(17.5, 0.62) },
            { 3, new ZoomLevel(20, 0.61) },
            { 4, new ZoomLevel(25, 0.60) },
            { 5, new ZoomLevel(30, 0.59) },
            { 6, new ZoomLevel(35, 0.58) },
            { 7, new ZoomLevel(40, 0.57) },
            { 8, new ZoomLevel(50, 0.56) },
            { 9, new ZoomLevel(60, 0.55) },
            { 10, new ZoomLevel(75, 0.54) },
            { 11, new ZoomLevel(90, 0.53) },
            { 12, new ZoomLevel(105, 0.52) },
            { 13, new ZoomLevel(120, 0.51) },
            { 14, new ZoomLevel(135, 0.50) }
        };

        public static readonly Dictionary<int, ZoomLevel> Extended = new Dictionary<int, ZoomLevel>()
        {
            { -1, new ZoomLevel(1, 0.7) },
            { 0, new ZoomLevel(3.5, 0.65) },
            { 1, new ZoomLevel(5, 0.625) },
            { 2, new ZoomLevel(10, 0.62) },
            { 3, new ZoomLevel(15, 0.61) },
            { 4, new ZoomLevel(20, 0.60) },
            { 5, new ZoomLevel(25, 0.59) },
            { 6, new ZoomLevel(30, 0.58) },
            { 7, new ZoomLevel(40, 0.57) },
            { 8, new ZoomLevel(50, 0.56) },
            { 9, new ZoomLevel(60, 0.55) },
            { 10, new ZoomLevel(75, 0.54) },
            { 11, new ZoomLevel(90, 0.53) },
            { 12, new ZoomLevel(105, 0.52) },
            { 13, new ZoomLevel(120, 0.51) },
            { 14, new ZoomLevel(135, 0.49) },
            { 15, new ZoomLevel(180, 0.48) },
            { 16, new ZoomLevel(250, 0.47) },
            { 17, new ZoomLevel(350, 0.46) },
            { 18, new ZoomLevel(500, 0.45) },
            { 19, new ZoomLevel(1000, 0.44) },
            { 20, new ZoomLevel(1800, 0.43) }
        };
    }
}
