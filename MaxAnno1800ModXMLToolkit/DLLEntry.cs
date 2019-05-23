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
using MaxAnno1800ModXMLToolkit.Toolkit;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace MaxAnno1800ModXMLToolkit
{
    public class DLLEntry
    {
        [DllExport(ExportName = "IsZoomInstalled", CallingConvention = CallingConvention.StdCall)]
        static public int IsZoomInstalled(IntPtr pViewDistanceSettingsFile, IntPtr pCameraSettingsFile)
        {
            return XMLToolKit.IsZoomInstalled(Marshal.PtrToStringAnsi(pViewDistanceSettingsFile), Marshal.PtrToStringAnsi(pCameraSettingsFile)) ? 1 : 0;
        }

        [DllExport(ExportName = "IsSquareOrnamentInstalled", CallingConvention = CallingConvention.StdCall)]
        static public int IsSquareOrnamentInstalled(IntPtr pdataAssetsFile)
        {
            return XMLToolKit.IsSquareOrnamentInstalled(Marshal.PtrToStringAnsi(pdataAssetsFile)) ? 1 : 0;
        }

        [DllExport(ExportName = "AreCityOrnamentsInstalled", CallingConvention = CallingConvention.StdCall)]
        static public int AreCityOrnamentsInstalled(IntPtr pdataAssetsFile)
        {
            return XMLToolKit.AreCityOrnamentsInstalled(Marshal.PtrToStringAnsi(pdataAssetsFile)) ? 1 : 0;
        }

        [DllExport(ExportName = "AreClubOrnamentsInstalled", CallingConvention = CallingConvention.StdCall)]
        static public int AreClubOrnamentsInstalled(IntPtr pdataAssetsFile)
        {
            return XMLToolKit.AreClubOrnamentsInstalled(Marshal.PtrToStringAnsi(pdataAssetsFile)) ? 1 : 0;
        }

        [DllExport(ExportName = "AreCheatOrnamentsInstalled", CallingConvention = CallingConvention.StdCall)]
        static public int AreCheatOrnamentsInstalled(IntPtr pdataAssetsFile)
        {
            return XMLToolKit.AreCheatOrnamentsInstalled(Marshal.PtrToStringAnsi(pdataAssetsFile)) ? 1 : 0;
        }

        [DllExport(ExportName = "AreVisualObjectsOrnaments", CallingConvention = CallingConvention.StdCall)]
        static public int AreVisualObjectsOrnaments(IntPtr pdataAssetsFile)
        {
            return XMLToolKit.AreVisualObjectsOrnaments(Marshal.PtrToStringAnsi(pdataAssetsFile)) ? 1 : 0;
        }

        [DllExport(ExportName = "AreOrnamentsBoosted", CallingConvention = CallingConvention.StdCall)]
        static public int AreOrnamentsBoosted(IntPtr pdataAssetsFile)
        {
            return XMLToolKit.AreOrnamentsBoosted(Marshal.PtrToStringAnsi(pdataAssetsFile)) ? 1 : 0;
        }



        [DllExport(ExportName = "ToggleZoom", CallingConvention = CallingConvention.StdCall)]
        static public void ToggleZoom(IntPtr pViewDistanceSettingsFile, IntPtr pCameraSettingsFile, int install)
        {
            XMLToolKit.ToggleZoom(Marshal.PtrToStringAnsi(pViewDistanceSettingsFile), Marshal.PtrToStringAnsi(pCameraSettingsFile), install != 0);
        }

        [DllExport(ExportName = "ToggleSquareOrnament", CallingConvention = CallingConvention.StdCall)]
        static public void ToggleSquareOrnament(IntPtr pdataAssetsFile, int install)
        {
            XMLToolKit.ToggleSquareOrnaments(Marshal.PtrToStringAnsi(pdataAssetsFile), install != 0);
        }

        [DllExport(ExportName = "ToggleCityOrnaments", CallingConvention = CallingConvention.StdCall)]
        static public void ToggleCityOrnaments(IntPtr pdataAssetsFile, int install)
        {
            XMLToolKit.ToggleCityOrnaments(Marshal.PtrToStringAnsi(pdataAssetsFile), install != 0);
        }

        [DllExport(ExportName = "ToggleClubOrnaments", CallingConvention = CallingConvention.StdCall)]
        static public void ToggleClubOrnaments(IntPtr pdataAssetsFile, int install)
        {
            XMLToolKit.ToggleClubOrnaments(Marshal.PtrToStringAnsi(pdataAssetsFile), install != 0);
        }

        [DllExport(ExportName = "ToggleCheatOrnaments", CallingConvention = CallingConvention.StdCall)]
        static public void ToggleCheatOrnaments(IntPtr pdataAssetsFile, int install)
        {
            XMLToolKit.ToggleCheatOrnaments(Marshal.PtrToStringAnsi(pdataAssetsFile), install != 0);
        }

        [DllExport(ExportName = "ToggleVisualObjectsOrnaments", CallingConvention = CallingConvention.StdCall)]
        static public void ToggleVisualObjectsOrnaments(IntPtr pdataAssetsFile, int install)
        {
            XMLToolKit.ToggleVisualObjectsOrnaments(Marshal.PtrToStringAnsi(pdataAssetsFile), install != 0);
        }

        [DllExport(ExportName = "ToggleOrnamentBoost", CallingConvention = CallingConvention.StdCall)]
        static public void ToggleOrnamentBoost(IntPtr pdataAssetsFile, int install)
        {
            XMLToolKit.ToggleOrnamentBoost(Marshal.PtrToStringAnsi(pdataAssetsFile), install != 0);
        }


        [DllExport(ExportName = "ApplyChanges", CallingConvention = CallingConvention.StdCall)]
        static public void ApplyChanges(IntPtr pXMLFile)
        {
            XMLToolKit.ApplyChanges(Marshal.PtrToStringAnsi(pXMLFile));
        }

    }

}
