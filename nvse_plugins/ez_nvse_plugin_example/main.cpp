// User Defines
#include "config.h"
// NVSE
#include "nvse/GameAPI.h"
#include "nvse/PluginAPI.h"
#include "nvse/SafeWrite.h"
// Legacy SDK
#include "nvse/CommandTable.h" // Required for new functions
#include "nvse/ParamInfos.h"
#include "nvse/GameObjects.h"
#include "nvse/GameOSDepend.h"
#include <string>
// Windows
#include <shlobj.h>	// CSIDL_MYCODUMENTS

// ================================
// Handles
// ================================

// Handle for the plugin
PluginHandle g_pluginHandle = kPluginHandle_Invalid;

// Handle for other things...

/* // Uncomment to use the NVSE interface
// Handle for the interface
NVSEInterface* g_interface;
*/

/* // Uncomment to use the script interface
// Handle for the script interface
NVSEScriptInterface* g_script;
#define ExtractArgsEx(...) g_script->ExtractArgsEx(__VA_ARGS__)
#define ExtractFormatStringArgs(...) g_script->ExtractFormatStringArgs(__VA_ARGS__)
*/

/* // Uncomment to use the command table interface
// Handle for the command table interface
NVSECommandTableInterface* g_cmdTable;
const CommandInfo* g_TFC;
*/

/* // Uncomment to use messaging
// Handle for the messaging interface
static NVSEMessagingInterface* g_messaging = NULL;
*/

// ================================
// User Code
// ================================

// If is RUNTIME PreProc, not in the Editor
#ifdef RUNTIME

// Example test bool function to print Hello World! to the plugin log and console
// Note: New functions are prepended with "Cmd_" and appended with "_Execute"
// And are enclosed within the #ifdef RUNTIME preprocessor definition
bool Cmd_PluginExampleFunctionsTest_Execute(COMMAND_ARGS)
{
	_MESSAGE("Hello World!"); // print to the plugin log
	Console_Print("Hello Console!"); // print to the in-game console

	//*result = 42;

	return true;
}

#endif

// Define the example test bool function, including a description of what it does
// Note: Outside of the RUNTIME def, for the editor also
DEFINE_COMMAND_PLUGIN(PluginExampleFunctionsTest, "Prints Hello to the Log and Console", 0, 0, NULL)

// ================================
// Plugin Listener
// ================================

/* // Uncomment to use messaging
// Listener for the plugin
static void PluginListener(NVSEMessagingInterface::Message* msg) noexcept
{
	switch (msg->type) {
		// case NVSEMessagingInterface::kMessage_PostLoad:
		case NVSEMessagingInterface::kMessage_PostPostLoad: // facilitate the correct dispatching/registering of messages/listeners
		{
			_MESSAGE("PluginListener: kMessage_PostPostLoad");
			break;
		}
		// case NVSEMessagingInterface::kMessage_ExitGame:
		// case NVSEMessagingInterface::kMessage_ExitToMainMenu:
		// case NVSEMessagingInterface::kMessage_LoadGame:
		// case NVSEMessagingInterface::kMessage_SaveGame:
		// case NVSEMessagingInterface::kMessage_Precompile:
		// case NVSEMessagingInterface::kMessage_ExitGame_Console:
		// case NVSEMessagingInterface::kMessage_RuntimeScriptError:
		// case NVSEMessagingInterface::kMessage_DeleteGame:			// kV2
		// case NVSEMessagingInterface::kMessage_RenameGame:			// kV2
		// case NVSEMessagingInterface::kMessage_RenameNewGame:			// kV2
		// case NVSEMessagingInterface::kMessage_NewGame:				// kV2
		// case NVSEMessagingInterface::kMessage_DeleteGameName:		// kV3
		// case NVSEMessagingInterface::kMessage_RenameGameName:		// kV3
		// case NVSEMessagingInterface::kMessage_RenameNewGameName:		// kV3
		// case NVSEMessagingInterface::kMessage_PreLoadGame:
		// case NVSEMessagingInterface::kMessage_PostLoadGame:
	}
}
*/

// ================================
// Plugin Compatibility Check
// ================================

// Check that the runtime and plugin versions are compatible
const bool IsCompatible(const NVSEInterface* nvse)
{
	// check if it's being loaded into the editor
	if(nvse->isEditor)
	{
		// FIXME - can i use the prop global variable here? it's only set for the editor which plugins don't need?
		// check that it's the supported editor
		if(nvse->editorVersion < SUPPORTED_RUNTIME_VERSION_CS) { // CS_VERSION_1_4_0_518
			_MESSAGE("ERROR::IsCompatible: Editor incorrect editor version (got %08X need at least %08X)", nvse->editorVersion, SUPPORTED_RUNTIME_VERSION_CS); // CS_VERSION_1_4_0_518
			_ERROR("ERROR::IsCompatible: Editor incorrect editor version (got %08X need at least %08X)", nvse->editorVersion, SUPPORTED_RUNTIME_VERSION_CS); // CS_VERSION_1_4_0_518
			return false;
		}
#ifdef NOGORE
		_ERROR("Editor only uses standard edition, closing.");
		return false;
#endif
	}
	// check for compatible version. if strict=true, runtime and supported versions must match. if strict=false, runtime version must be above the minimum
	else if (!IVersionCheck::IsCompatibleVersion(nvse->runtimeVersion, MINIMUM_RUNTIME_VERSION, SUPPORTED_RUNTIME_VERSION, SUPPORTED_RUNTIME_VERSION_STRICT)) { // not strict
		_MESSAGE("ERROR::IsCompatible: Plugin is not compatible with runtime version, disabling");
		_FATALERROR("ERROR::IsCompatible: Plugin is not compatible with runtime version, disabling");
		
#ifdef NOGORE
		if(!nvse->isNogore) { // if is no gore, but gore is set
			_MESSAGE("ERROR::IsCompatible: Incorrect runtime edition (got %08X need %08X (nogore))", nvse->isNogore, 1);
			_ERROR("ERROR::IsCompatible: Incorrect runtime edition (got %08X need %08X (nogore))", nvse->isNogore, 1);
			return false;
		}
#else
		if(nvse->isNogore) { // if is gore, but no gore is set
			_MESSAGE("ERROR::IsCompatible: Incorrect runtime edition (got %08X need %08X (standard))", nvse->isNogore, 0);
			_ERROR("ERROR::IsCompatible: Incorrect runtime edition (got %08X need %08X (standard))", nvse->isNogore, 0);
			return false;
		}
#endif
		
		// not compatible
		return false;
	}
	
	// compatible
	return true;
}

// ================================
// Plugin Export, Query and Load - Start Extern-C
// ================================

extern "C" { // Start: extern "C"

// ================================
// Plugin Version Data - Not Used In All SE SDK's
// ================================

/*
// NVSE does not use this
__declspec(dllexport) NVSEPluginVersionData NVSEPlugin_Version =
{
};
*/

// ================================
// Plugin Query - Not Used In All SE SDK's
// ================================

// NVSE Plugin Query - Called when the plugin is queried
bool NVSEPlugin_Query(const NVSEInterface* nvse, PluginInfo* info)
{
	// open the plugin log file
	gLog.OpenRelative(CSIDL_MYDOCUMENTS, PLUGIN_LOG_FILE);
	
	_MESSAGE(PLUGIN_VERSION_INFO); // write the plugin version to the log
	_MESSAGE("Plugin_Query: Querying");

	// populate info structure
	info->infoVersion =	PluginInfo::kInfoVersion;
	info->name =		PLUGIN_NAME_LONG;		// set in config.h
	info->version =		PLUGIN_VERSION_DLL;		// set in config.h
	
	// check for compatible versions
	if (!IsCompatible(nvse)) {
		_MESSAGE("ERROR::Plugin_Query: Incompatible | Disabling Plugin");
		_FATALERROR("ERROR::Plugin_Query: Incompatible | Disabling Plugin");
		// incompatible
		return false;
	}
	
	// ######################################################
	// Note: Nothing should be assigned below this point
	// Get the necessary info about the plugin and return
	// ######################################################
	
	_MESSAGE("Plugin_Query: Queried Successfully"); // log the successful query

	// supported runtime version
	return true;
}

// ================================
// Plugin Preload - Not Used In All SE SDK's
// ================================

/*
// NVSE does not use this
bool NVSEPlugin_Preload(const NVSEInterface* nvse)
{
}
*/

// ================================
// Plugin Load - Used In All SE SDK's
// ================================

// NVSE Plugin Load - Called when the plugin loads everytime
bool NVSEPlugin_Load(const NVSEInterface* nvse)
{
	// open the plugin log file
	gLog.OpenRelative(CSIDL_MYDOCUMENTS, PLUGIN_LOG_FILE);

	_MESSAGE(PLUGIN_VERSION_INFO); // write the plugin version to the log
	_MESSAGE("Plugin_Load: Loading");
	
	// check for compatible versions
	if (!IsCompatible(nvse)) {
		_MESSAGE("ERROR::Plugin_Load: Incompatible | Disabling Plugin");
		_FATALERROR("ERROR::Plugin_Load: Incompatible | Disabling Plugin");
		// incompatible
		return false;
	}
	
	// store plugin handle for later
	g_pluginHandle = nvse->GetPluginHandle();
	
	/* // Uncomment to use the NVSE interface
	// save the NVSEinterface in case we need it later
	g_interface = (NVSEInterface *)nvse;
	*/
	
	/* // Uncomment to use the script interface
	// store script handle for later
	g_script = (NVSEScriptInterface*)nvse->QueryInterface(kInterface_Script);
	*/
	
	/* // Uncomment to use messaging
	// register the listener
	g_messaging = (NVSEMessagingInterface*)nvse->QueryInterface(kInterface_Messaging);
	if (g_messaging) {
		if (g_messaging->RegisterListener(g_pluginHandle, "NVSE", PluginListener)) {
			_MESSAGE("Plugin_Load: Listener Registered");
		}
	}
	*/
	
	/***************************************************************************
	 *	
	 *	IMPORTANT::READ THIS!
	 *	
	 *	Before releasing your plugin, you need to request an opcode range from
	 *	the NVSE team and set it in your first SetOpcodeBase call. If you do not
	 *	do this, your plugin will create major compatibility issues with other
	 *	plugins, and will not load in release versions of NVSE. See
	 *	nvse_readme.txt for more information.
	 *	
	 **************************************************************************/
	 
	// register the new functions
	nvse->SetOpcodeBase(0x2000);
	if (nvse->RegisterCommand(&kCommandInfo_PluginExampleFunctionsTest)) {
		_MESSAGE("Plugin_Load: Functions Registered");
	}
	
	_MESSAGE("Plugin_Load: Loaded Successfully"); // log the successful load

	// initialized
	return true;
}

}; // Stop: extern "C"

// ================================
