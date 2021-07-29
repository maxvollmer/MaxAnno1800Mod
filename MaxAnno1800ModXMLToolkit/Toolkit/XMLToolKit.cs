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
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace MaxAnno1800ModXMLToolkit.Toolkit
{
    class XMLToolKit
    {
        private static readonly string FakeRootOpen = "<MaxAnno1800ModFakeRoot>";
        private static readonly string FakeRootClose = "</MaxAnno1800ModFakeRoot>";

        private static Dictionary<string, XDocument> XmlCache { get; set; } = new Dictionary<string, XDocument>();

        private static XDocument LoadXML(string file)
        {
            if (!XmlCache.ContainsKey(file))
            {
                string rawXML = File.ReadAllText(file);
                int startIndex = rawXML.IndexOf("-->");
                if (startIndex > 0)
                {
                    rawXML = rawXML.Substring(startIndex+3);
                }
                int endIndex = rawXML.IndexOf('\0');
                if (endIndex > 0)
                {
                    rawXML = rawXML.Substring(0, endIndex);
                }
                XmlCache[file] = XDocument.Parse(FakeRootOpen + rawXML.Replace('\0', ' ').Trim() + FakeRootClose);
            }
            return XmlCache[file];
        }

        private static void PrintInstallMessage(string what, bool install)
        {
            Console.WriteLine((install ? "Installing" : "Uninstalling") + " " + what + ", this might take a while...");
        }

        private static void PrintDoneMessage(string what, bool install)
        {
            Console.WriteLine("...done " + (install ? "installing" : "uninstalling") + " " + what + ".");
        }

        public static bool IsZoomInstalled(string viewDistanceSettingsFile, string cameraSettingsFile)
        {
            try
            {
                XDocument viewDistanceXML = LoadXML(viewDistanceSettingsFile);
                XDocument cameraXML = LoadXML(cameraSettingsFile);

                return ZoomInstaller.IsZoomInstalled(viewDistanceXML, cameraXML);
            }
            catch (Exception e)
            {
                Console.WriteLine("IsZoomInstalled caught exception: {0}", e);
                return false;
            }
        }

        public static bool IsSquareOrnamentInstalled(string dataAssetsFile)
        {
            try
            {
                XDocument dataAssetsXML = LoadXML(dataAssetsFile);

                return SquareOrnamentUnlocker.IsSquareOrnamentInstalled(dataAssetsXML);
            }
            catch (Exception e)
            {
                Console.WriteLine("IsSquareOrnamentInstalled caught exception: {0}", e);
                return false;
            }
        }

        public static bool AreCityOrnamentsInstalled(string dataAssetsFile)
        {
            try
            {
                XDocument dataAssetsXML = LoadXML(dataAssetsFile);

                return CityOrnamentUnlocker.AreCityOrnamentsInstalled(dataAssetsXML);
            }
            catch (Exception e)
            {
                Console.WriteLine("AreCityOrnamentsInstalled caught exception: {0}", e);
                return false;
            }
        }

        public static bool AreClubOrnamentsInstalled(string dataAssetsFile)
        {
            try
            {
                XDocument dataAssetsXML = LoadXML(dataAssetsFile);

                return ClubOrnamentUnlocker.AreClubOrnamentsInstalled(dataAssetsXML);
            }
            catch (Exception e)
            {
                Console.WriteLine("AreClubOrnamentsInstalled caught exception: {0}", e);
                return false;
            }
        }
        public static bool AreExtraOrnamentsInstalled(string dataAssetsFile)
        {
            try
            {
                XDocument dataAssetsXML = LoadXML(dataAssetsFile);

                return ExtraOrnamentUnlocker.AreExtraOrnamentsInstalled(dataAssetsXML);
            }
            catch (Exception e)
            {
                Console.WriteLine("AreClubOrnamentsInstalled caught exception: {0}", e);
                return false;
            }
        }
        public static bool AreCheatOrnamentsInstalled(string dataAssetsFile)
        {
            try
            {
                XDocument dataAssetsXML = LoadXML(dataAssetsFile);

                return BuildPermitBuildingToOrnamentalBuildingConverter.AreCheatOrnamentsInstalled(dataAssetsXML);
            }
            catch (Exception e)
            {
                Console.WriteLine("AreCheatOrnamentsInstalled caught exception: {0}", e);
                return false;
            }
        }

        public static bool AreVisualObjectsOrnaments(string dataAssetsFile)
        {
            try
            {
                XDocument dataAssetsXML = LoadXML(dataAssetsFile);

                return VisualObjectToOrnamentalBuildingConverter.AreVisualObjectsOrnaments(dataAssetsXML);
            }
            catch (Exception e)
            {
                Console.WriteLine("AreCheatOrnamentsInstalled caught exception: {0}", e);
                return false;
            }
        }

        public static bool AreOrnamentsBoosted(string dataAssetsFile)
        {
            try
            {
                XDocument dataAssetsXML = LoadXML(dataAssetsFile);

                return OrnamentBooster.AreOrnamentsBoosted(dataAssetsXML);
            }
            catch (Exception e)
            {
                Console.WriteLine("AreOrnamentsBoosted caught exception: {0}", e);
                return false;
            }
        }




        public static void ToggleZoom(string viewDistanceSettingsFile, string cameraSettingsFile, bool install)
        {
            try
            {
                PrintInstallMessage("extended zoom", install);
                XDocument viewDistanceXML = LoadXML(viewDistanceSettingsFile);
                XDocument cameraXML = LoadXML(cameraSettingsFile);
                if (install)
                {
                    ZoomInstaller.InstallZoom(viewDistanceXML, cameraXML);
                }
                else
                {
                    ZoomInstaller.UninstallZoom(viewDistanceXML, cameraXML);
                }
                PrintDoneMessage("extended zoom", install);
            }
            catch (Exception e)
            {
                Console.WriteLine("ToggleZoom caught exception: {0}", e);
            }
        }

        public static void ToggleSquareOrnaments(string dataAssetsFile, bool install)
        {
            try
            {
                PrintInstallMessage("square ornaments", install);
                XDocument dataAssetsXML = LoadXML(dataAssetsFile);
                if (install)
                {
                    SquareOrnamentUnlocker.UnlockSquareOrnament(dataAssetsXML);
                }
                else
                {
                    SquareOrnamentUnlocker.LockSquareOrnament(dataAssetsXML);
                }
                PrintDoneMessage("square ornaments", install);
            }
            catch (Exception e)
            {
                Console.WriteLine("ToggleSquareOrnament caught exception: {0}", e);
            }
        }

        public static void ToggleCityOrnaments(string dataAssetsFile, bool install)
        {
            try
            {
                PrintInstallMessage("city ornaments", install);
                XDocument dataAssetsXML = LoadXML(dataAssetsFile);
                if (install)
                {
                    CityOrnamentUnlocker.UnlockCityOrnaments(dataAssetsXML);
                }
                else
                {
                    CityOrnamentUnlocker.LockCityOrnaments(dataAssetsXML);
                }
                PrintDoneMessage("city ornaments", install);
            }
            catch (Exception e)
            {
                Console.WriteLine("ToggleCityOrnaments caught exception: {0}", e);
            }
        }

        public static void ToggleClubOrnaments(string dataAssetsFile, bool install)
        {
            try
            {
                PrintInstallMessage("club ornaments", install);
                XDocument dataAssetsXML = LoadXML(dataAssetsFile);
                if (install)
                {
                    ClubOrnamentUnlocker.UnlockClubOrnaments(dataAssetsXML);
                }
                else
                {
                    ClubOrnamentUnlocker.LockClubOrnaments(dataAssetsXML);
                }
                PrintDoneMessage("club ornaments", install);
            }
            catch (Exception e)
            {
                Console.WriteLine("ToggleClubOrnaments caught exception: {0}", e);
            }
        }
        public static void ToggleExtraOrnaments(string dataAssetsFile, bool install)
        {
            try
            {
                PrintInstallMessage("extra club ornaments", install);
                XDocument dataAssetsXML = LoadXML(dataAssetsFile);
                if (install)
                {
                    ExtraOrnamentUnlocker.UnlockExtraOrnaments(dataAssetsXML);
                }
                else
                {
                    ExtraOrnamentUnlocker.UnlockExtraOrnaments(dataAssetsXML);
                }
                PrintDoneMessage("extra club ornaments", install);
            }
            catch (Exception e)
            {
                Console.WriteLine("ToggleExtraOrnaments caught exception: {0}", e);
            }
        }

        public static void ToggleCheatOrnaments(string dataAssetsFile, bool install)
        {
            try
            {
                PrintInstallMessage("cheat ornaments", install);
                XDocument dataAssetsXML = LoadXML(dataAssetsFile);
                if (install)
                {
                    BuildPermitBuildingToOrnamentalBuildingConverter.ToOrnamental(dataAssetsXML);
                }
                else
                {
                    BuildPermitBuildingToOrnamentalBuildingConverter.ToPermit(dataAssetsXML);
                }
                PrintDoneMessage("cheat ornaments", install);
            }
            catch (Exception e)
            {
                Console.WriteLine("ToggleCheatOrnaments caught exception: {0}", e);
            }
        }

        public static void ToggleVisualObjectsOrnaments(string dataAssetsFile, bool install)
        {
            try
            {
                PrintInstallMessage("visual object ornaments", install);
                XDocument dataAssetsXML = LoadXML(dataAssetsFile);
                if (install)
                {
                    VisualObjectToOrnamentalBuildingConverter.ToOrnamental(dataAssetsXML);
                }
                else
                {
                    VisualObjectToOrnamentalBuildingConverter.ToVisualObject(dataAssetsXML);
                }
                PrintDoneMessage("visual object ornaments", install);
            }
            catch (Exception e)
            {
                Console.WriteLine("ToggleVisualObjectsOrnaments caught exception: {0}", e);
            }
        }

        public static void ToggleOrnamentBoost(string dataAssetsFile, bool install)
        {
            try
            {
                PrintInstallMessage("ornament boost", install);
                XDocument dataAssetsXML = LoadXML(dataAssetsFile);
                if (install)
                {
                    OrnamentBooster.InstallBoost(dataAssetsXML);
                }
                else
                {
                    OrnamentBooster.UninstallBoost(dataAssetsXML);
                }
                PrintDoneMessage("ornament boost", install);
            }
            catch (Exception e)
            {
                Console.WriteLine("ToggleOrnamentBoost caught exception: {0}", e);
            }
        }



        public static void ApplyChanges(string xmlFile)
        {
            try
            {
                if (XmlCache.ContainsKey(xmlFile))
                {
                    var stream = new MemoryStream();
                    XmlCache[xmlFile].Save(stream, SaveOptions.DisableFormatting);
                    stream.Position = 0;
                    string xml = new StreamReader(stream).ReadToEnd();
                    int fakeRootOpenIndex = xml.IndexOf(FakeRootOpen);
                    xml = xml.Substring(fakeRootOpenIndex + FakeRootOpen.Length, xml.Length - fakeRootOpenIndex - FakeRootOpen.Length - FakeRootClose.Length);
                    File.Delete(xmlFile);
                    System.IO.File.WriteAllText(xmlFile, xml.Trim(), Encoding.ASCII);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("ApplyChanges caught exception: {0}", e);
            }
        }

    }
}
