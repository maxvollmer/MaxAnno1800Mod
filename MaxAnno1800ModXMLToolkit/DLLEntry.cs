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
        static public int IsSquareOrnamentInstalled(IntPtr pdata0AssetsFile, IntPtr pdata10AssetsFile)
        {
            return XMLToolKit.IsSquareOrnamentInstalled(Marshal.PtrToStringAnsi(pdata0AssetsFile), Marshal.PtrToStringAnsi(pdata10AssetsFile)) ? 1 : 0;
        }

        [DllExport(ExportName = "AreClubOrnamentsInstalled", CallingConvention = CallingConvention.StdCall)]
        static public int AreClubOrnamentsInstalled(IntPtr pdata0AssetsFile, IntPtr pdata10AssetsFile)
        {
            return XMLToolKit.AreClubOrnamentsInstalled(Marshal.PtrToStringAnsi(pdata0AssetsFile), Marshal.PtrToStringAnsi(pdata10AssetsFile)) ? 1 : 0;
        }

        [DllExport(ExportName = "AreCheatOrnamentsInstalled", CallingConvention = CallingConvention.StdCall)]
        static public int AreCheatOrnamentsInstalled(IntPtr pdata0AssetsFile, IntPtr pdata10AssetsFile)
        {
            return XMLToolKit.AreCheatOrnamentsInstalled(Marshal.PtrToStringAnsi(pdata0AssetsFile), Marshal.PtrToStringAnsi(pdata10AssetsFile)) ? 1 : 0;
        }



        [DllExport(ExportName = "ToggleZoom", CallingConvention = CallingConvention.StdCall)]
        static public void ToggleZoom(IntPtr pViewDistanceSettingsFile, IntPtr pCameraSettingsFile, int install)
        {
            XMLToolKit.ToggleZoom(Marshal.PtrToStringAnsi(pViewDistanceSettingsFile), Marshal.PtrToStringAnsi(pCameraSettingsFile), install != 0);
        }

        [DllExport(ExportName = "ToggleSquareOrnament", CallingConvention = CallingConvention.StdCall)]
        static public void ToggleSquareOrnament(IntPtr pdata0AssetsFile, IntPtr pdata10AssetsFile, int install)
        {
            XMLToolKit.ToggleSquareOrnament(Marshal.PtrToStringAnsi(pdata0AssetsFile), Marshal.PtrToStringAnsi(pdata10AssetsFile), install != 0);
        }

        [DllExport(ExportName = "ToggleClubOrnaments", CallingConvention = CallingConvention.StdCall)]
        static public void ToggleClubOrnaments(IntPtr pdata0AssetsFile, IntPtr pdata10AssetsFile, int install)
        {
            XMLToolKit.ToggleClubOrnaments(Marshal.PtrToStringAnsi(pdata0AssetsFile), Marshal.PtrToStringAnsi(pdata10AssetsFile), install != 0);
        }

        [DllExport(ExportName = "ToggleCheatOrnaments", CallingConvention = CallingConvention.StdCall)]
        static public void ToggleCheatOrnaments(IntPtr pdata0AssetsFile, IntPtr pdata10AssetsFile, int install)
        {
            XMLToolKit.ToggleCheatOrnaments(Marshal.PtrToStringAnsi(pdata0AssetsFile), Marshal.PtrToStringAnsi(pdata10AssetsFile), install != 0);
        }


    }

}
