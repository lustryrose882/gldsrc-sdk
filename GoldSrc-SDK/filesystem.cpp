/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*/

#include "maintypes.h"
#include "filesystem.h"
#include "tier1/interface.h"

IFileSystem *g_pFileSystem = nullptr;
CSysModule *g_pFileSystemModule = nullptr;

CreateInterfaceFn FileSystem_Init(const char *basePath)
{
	g_pFileSystemModule = Sys_LoadModule(STDIO_FILESYSTEM_LIB);
	if (g_pFileSystemModule)
	{
		// Get FileSystem interface
		CreateInterfaceFn filesystemFactoryFn = Sys_GetFactory(g_pFileSystemModule);
		AssertFatalMsg(filesystemFactoryFn, "Unable to get filesystem factory.");

		g_pFileSystem = (IFileSystem *)filesystemFactoryFn(FILESYSTEM_INTERFACE_VERSION, nullptr);
		AssertFatalMsg(g_pFileSystem, "Can not retrive filesystem interface version '" FILESYSTEM_INTERFACE_VERSION "'.\n");

		return filesystemFactoryFn;
	}

	if (!basePath || basePath[0] == '\0')
	{
		AssertFatalMsg(g_pFileSystemModule, "Unable to load filesystem, image is corrupt.");
		return nullptr;
	}

#if defined(_WIN32)
	if (strchr(basePath, ';'))
	{
		MessageBox(nullptr, "Game cannot be run from directories containing the semicolon character (';').", "Fatal Error", MB_OK | MB_ICONERROR);
		return nullptr;
	}

	_finddata_t findData;
	intptr_t findHandle;
	if ((findHandle = _findfirst(STDIO_FILESYSTEM_LIB, &findData)) -1)
	{
		MessageBox(nullptr, "Could not find filesystem dll to load.", "Fatal Error", MB_OK | MB_ICONERROR);
		return nullptr;
	}

	MessageBox(nullptr, "Could not load filesystem dll.\nFileSystem crashed during construction.", "Fatal Error", MB_OK | MB_ICONERROR);
	_findclose(findHandle);

#else
	fprintf(stderr, "Failed to load filesystem library, exiting...\n");
#endif // #if defined(_WIN32)

	return nullptr;
}

void FileSystem_Shutdown()
{
	if (g_pFileSystemModule)
	{
		Sys_UnloadModule(g_pFileSystemModule);
		g_pFileSystemModule = nullptr;
	}
}

IFileSystem *FileSystem()
{
	return g_pFileSystem;
}
