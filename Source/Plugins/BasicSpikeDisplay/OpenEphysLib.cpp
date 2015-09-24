/*
------------------------------------------------------------------

This file is part of the Open Ephys GUI
Copyright (C) 2013 Open Ephys

------------------------------------------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "../../Processors/PluginManager/OpenEphysPlugin.h"
#include "SpikeDetector/SpikeDetector.h"
#include "SpikeDisplayNode/SpikeDisplayNode.h"
#include <string>
#ifdef WIN32
#include <Windows.h>
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

using namespace Plugin;
#define NUM_PLUGINS 2

extern "C" EXPORT void getLibInfo(Plugin::LibraryInfo* info)
{
	info->apiVersion = PLUGIN_API_VER;
	info->name = "Basic Spike Display";
	info->numPlugins = NUM_PLUGINS;
}

extern "C" EXPORT int getPluginInfo(int index, Plugin::PluginInfo* info)
{
	switch (index)
	{
	case 0:
		info->type = Plugin::ProcessorPlugin;
		info->processor.name = "Spike Detector";
		info->processor.type = Plugin::FilterProcessor;
		info->processor.creator = &(Plugin::createProcessor<SpikeDetector>);
		break;
	case 1:
		info->type = Plugin::ProcessorPlugin;
		info->processor.name = "Spike Viewer";
		info->processor.type = Plugin::SinkProcessor;
		info->processor.creator = &(Plugin::createProcessor<SpikeDisplayNode>);
		break;
	default:
		return -1;
		break;
	}
	return 0;
}

#ifdef WIN32
BOOL WINAPI DllMain(IN HINSTANCE hDllHandle,
	IN DWORD     nReason,
	IN LPVOID    Reserved)
{
	return TRUE;
}

#endif
