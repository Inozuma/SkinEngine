#pragma once

#include "Skin/Filesystem/File.h"

#include <string>
#include <map>

namespace Skin
{
	class Directory
	{
	private:
		std::string mName;
		std::string mPath;
		std::string mRelativePath;
		std::map<std::string, Directory*> mDirectories;
		std::map<std::string, File*> mFiles;

	public:
		Directory();
		Directory(const std::string&);
		~Directory();

		bool hasFile(const std::string&);
		bool hasDirectory(const std::string&);
		File* getFile(const std::string&);
		Directory* getDirectory(const std::string&);
	};
}