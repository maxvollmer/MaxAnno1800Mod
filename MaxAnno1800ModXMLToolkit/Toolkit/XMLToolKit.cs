using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MaxAnno1800ModXMLToolkit.Toolkit
{
    class XMLToolKit
    {
        public static bool IsZoomInstalled(string viewDistanceSettingsFile, string cameraSettingsFile)
        {
            Console.WriteLine("XMLToolKit.IsZoomInstalled: {0}, {1}", viewDistanceSettingsFile, cameraSettingsFile);
            return true;
        }

        public static bool IsSquareOrnamentInstalled(string data0AssetsFile, string data10AssetsFile)
        {
            Console.WriteLine("XMLToolKit.IsSquareOrnamentInstalled: {0}, {1}", data0AssetsFile, data10AssetsFile);
            return false;
        }

        public static bool AreClubOrnamentsInstalled(string data0AssetsFile, string data10AssetsFile)
        {
            Console.WriteLine("XMLToolKit.AreClubOrnamentsInstalled: {0}, {1}", data0AssetsFile, data10AssetsFile);
            return false;
        }

        public static bool AreCheatOrnamentsInstalled(string data0AssetsFile, string data10AssetsFile)
        {
            Console.WriteLine("XMLToolKit.AreCheatOrnamentsInstalled: {0}, {1}", data0AssetsFile, data10AssetsFile);
            return false;
        }


        public static void ToggleZoom(string viewDistanceSettingsFile, string cameraSettingsFile, bool install)
        {
            Console.WriteLine("XMLToolKit.ToggleZoom: {0}, {1}, {2}", viewDistanceSettingsFile, cameraSettingsFile, install);
        }

        public static void ToggleSquareOrnament(string data0AssetsFile, string data10AssetsFile, bool install)
        {
            Console.WriteLine("XMLToolKit.ToggleSquareOrnament: {0}, {1}, {2}", data0AssetsFile, data10AssetsFile, install);
        }

        public static void ToggleClubOrnaments(string data0AssetsFile, string data10AssetsFile, bool install)
        {
            Console.WriteLine("XMLToolKit.ToggleClubOrnaments: {0}, {1}, {2}", data0AssetsFile, data10AssetsFile, install);
        }

        public static void ToggleCheatOrnaments(string data0AssetsFile, string data10AssetsFile, bool install)
        {
            Console.WriteLine("XMLToolKit.ToggleCheatOrnaments: {0}, {1}, {2}", data0AssetsFile, data10AssetsFile, install);
        }

    }
}
