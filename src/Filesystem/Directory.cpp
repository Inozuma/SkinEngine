#include "Skin/Filesystem/Directory.h"

#include <boost/filesystem.hpp>

using namespace Skin;
namespace bfs = boost::filesystem;

Directory::Directory()
{
}

Directory::Directory(const std::string& path)
{
	bfs::path p(path);
	p.normalize();

	try
	{
		if (bfs::exists(p))
		{
			if (bfs::is_directory(p))
			{
				mName = p.filename().string();
				mPath = bfs::absolute(p).string();
				mRelativePath = p.relative_path().string();

				bfs::directory_iterator it = bfs::directory_iterator(p);
				for (; it != bfs::directory_iterator(); ++it)
				{
					bfs::path pit = *it;
					std::cout << pit << std::endl;
					if (bfs::is_regular_file(pit))
					{
						File* file = new File(pit.string());
						mFiles[file->getName()] = file;
					}
					else if (bfs::is_directory(pit))
					{
						Directory* dir = new Directory(pit.string());
						mDirectories[dir->mName] = dir;
					}
				}
			}
		}
	}
	catch (const bfs::filesystem_error& e)
	{
		std::cout << e.what() << std::endl;
	}
}

Directory::~Directory()
{
	for (std::map<std::string, Directory*>::iterator it = mDirectories.begin(); it != mDirectories.end(); ++it)
		delete it->second;
	mDirectories.clear();
	for (std::map<std::string, File*>::iterator it = mFiles.begin(); it != mFiles.begin(); ++it)
		delete it->second;
	mFiles.clear();
}

bool Directory::hasFile(const std::string& path)
{
	if (mFiles.count(path))
		return true;
	return false;
}

bool Directory::hasDirectory(const std::string& path)
{
	if (mDirectories.count(path))
		return true;
	return false;
}

File* Directory::getFile(const std::string& filename)
{
	if (mFiles.count(filename))
		return mFiles[filename];
	return NULL;
}

Directory* Directory::getDirectory(const std::string& dirname)
{
	if (mDirectories.count(dirname))
		return mDirectories[dirname];
	return NULL;
}