// MaxAnno1800Mod by Max Vollmer (https://github.com/maxvollmer/MaxAnno1800Mod)
// * Adds extended zoom.
// * Adds square ornament that was missing in the original game.
// * Enables chess tables for those who missed the beta.
//
// quickbms by Luigi Auriemma (see quickbms.txt for full license and contact)
//
// 1800.bms script file by kskudlik (from https://github.com/kskudlik/Anno-1800-RDA-Extractor)
//
// Anno 1800 and all related trademarks belong to Ubisoft. Use this mod at your own risk. Mod might break with upcoming game updates.

#include "pch.h"
#include "Mod.h"
#include "InputHelper.h"
#include "Constants.h"
#include "XMLToolKit.h"

int main()
{
	MaxAnno1800Mod::Mod mod;
	mod.DebugPrintLocations();

	MaxAnno1800Mod::ModAction action{ MaxAnno1800Mod::ModAction::CANCEL };
	do
	{
		action = MaxAnno1800Mod::InputHelper::PromptModAction();
		mod.ApplyAction(action);
	}
	while (action != MaxAnno1800Mod::ModAction::RESTORE_BACKUP && action != MaxAnno1800Mod::ModAction::CANCEL && action != MaxAnno1800Mod::ModAction::APPLY);
}
