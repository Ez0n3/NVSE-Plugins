#pragma once
#include "nvse/nvse_version.h" // NVSE
#include "IVersionCheck.h" // Common plugin version check, found in \common\common_plugins\
// #include "../plugin_common/common.h" // EG: Common plugin functions for this sdk if needed

// ================================
// Plugin Information
// ================================

// Plugin info
#define PLUGIN_AUTHOR				"Ez0n3"					// Author of the plugin

#define PLUGIN_NAME_SHORT			"ez_nvse_plugin_example"	// Plugin name without spaces
#define PLUGIN_NAME_LONG			"Ez NVSE Plugin Example"	// Plugin name with spaces

// Plugin version, Major, Minor, Build. EG: (1.0.0) equals (Major.Minor.Build)
#define PLUGIN_VERSION_MAJOR		1
#define PLUGIN_VERSION_MINOR		0
#define PLUGIN_VERSION_BUILD		0

// ================================
// Nothing below this needs changing between plugins except maybe MINIMUM_RUNTIME_VERSION and/or SUPPORTED_RUNTIME_VERSION_STRICT
// ================================

// Plugin log file
#define PLUGIN_LOG_FILE				"\\My Games\\" GAME_SAVE_FOLDER_NAME("FalloutNV") "\\NVSE\\" PLUGIN_LOG_FILE_NAME(PLUGIN_NAME_SHORT) // plugin log file location

// Common definitions
#define SDK_VERSION_STRING			VERSION_TO_STRING(NVSE_VERSION_INTEGER, NVSE_VERSION_INTEGER_MINOR, NVSE_VERSION_INTEGER_BETA)
#define PLUGIN_VERSION_STRING		VERSION_TO_STRING(PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_BUILD)

#define PLUGIN_VERSION_DLL			MAKE_EXE_VERSION(PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_BUILD)
#define PLUGIN_VERSION_INFO			PLUGIN_NAME_SHORT " v%s (0x%08X) (SDK v%s)", PLUGIN_VERSION_STRING, PLUGIN_VERSION_DLL, SDK_VERSION_STRING

// ================================
// Plugin Version Information
// ================================

// The minimum runtime version allowed by the plugin. EG: I need function X, which was added in runtime Y, therefore Y is the minimum runtime version
#define MINIMUM_RUNTIME_VERSION				RUNTIME_VERSION_1_0_0_240 // The lowest version

// The runtime version the plugin was designed for
// #define SUPPORTED_RUNTIME_VERSION		CURRENT_RELEASE_RUNTIME
#define SUPPORTED_RUNTIME_VERSION			RUNTIME_VERSION // Set in /config/_Plugins.props, controls core and plugin versions - normally latest

// Strict runtime version. If strict=true, runtime and supported versions must match. If strict=false, runtime version must be above the minimum
#define SUPPORTED_RUNTIME_VERSION_STRICT	false

// The compatible runtime version - set automatically
#define COMPATIBLE(runtimeVersion)			(runtimeVersion == SUPPORTED_RUNTIME_VERSION)

// The compatible editor version
// #define SUPPORTED_RUNTIME_VERSION_CS		CS_VERSION_1_4_0_518 // latest editor
#define SUPPORTED_RUNTIME_VERSION_CS		CS_VERSION // Set in /config/_Plugins.props

// ================================

/*
// From nvse_version.h

#define RUNTIME_VERSION_1_0_0_240	MAKE_NEW_VEGAS_VERSION(0, 0, 240)		// 0x00000F00
#define RUNTIME_VERSION_1_1_0_240	MAKE_NEW_VEGAS_VERSION(1, 0, 268)		// 0x010010C0
#define RUNTIME_VERSION_1_1_1_271	MAKE_NEW_VEGAS_VERSION(1, 1, 271)		// 0x010110F0
#define RUNTIME_VERSION_1_1_1_280	MAKE_NEW_VEGAS_VERSION(1, 1, 280)		// 0x01011180
#define RUNTIME_VERSION_1_2_0_285	MAKE_NEW_VEGAS_VERSION(2, 0, 285)		// 0x020011D0
#define RUNTIME_VERSION_1_2_0_314	MAKE_NEW_VEGAS_VERSION(2, 0, 314)		// 0x020013A0
#define RUNTIME_VERSION_1_2_0_352	MAKE_NEW_VEGAS_VERSION(2, 0, 352)		// 0x02001600
#define RUNTIME_VERSION_1_3_0_452	MAKE_NEW_VEGAS_VERSION(3, 0, 452)		// 0x03001C40
#define RUNTIME_VERSION_1_4_0_525	MAKE_NEW_VEGAS_VERSION(4, 0, 525)		// 0x040020D0
#define RUNTIME_VERSION_1_4_0_525ng	MAKE_NEW_VEGAS_VERSION_EX(4, 0, 525, 1)	// 0x040020D1 // ng = No Gore

#define CS_VERSION_1_1_0_262		MAKE_NEW_VEGAS_VERSION(1, 0, 262)		// 0x01001060
#define CS_VERSION_1_3_0_452		MAKE_NEW_VEGAS_VERSION(3, 0, 452)		// 0x03001C40
#define CS_VERSION_1_4_0_518		MAKE_NEW_VEGAS_VERSION(4, 0, 518)		// 0x04002060
*/
