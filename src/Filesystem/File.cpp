#include "Skin/Filesystem/File.h"

#include <iostream>
#include <boost/filesystem.hpp>

using namespace Skin;
namespace bfs = boost::filesystem;

File::File() :
mSize(0)
{
}

File::File(const std::string& path) :
mOK(false),
mSize(0)
{
	bfs::path p(path);

	try
	{
		if (bfs::exists(p))
		{
			if (bfs::is_regular_file(p))
			{
				mOK = true;
				mName = p.filename().string();
				mPath = bfs::absolute(p).string();
				mExtension = p.extension().string();
				mRelativePath = p.relative_path().string();
				mSize = static_cast<unsigned int>(bfs::file_size(p));
			}
		}
	}
	catch (const bfs::filesystem_error& e)
	{
		std::cout << e.what() << std::endl;
	}
}

File::File(const std::string& name, const std::string& path, const std::string& relative_path, int size) :
mName(name),
mPath(path),
mRelativePath(relative_path),
mSize(size)
{
}

File::~File()
{
}

bool File::exists() const
{
	return mOK;
}

const std::string& File::getExtension() const
{
	return mExtension;
}

const std::string& File::getName() const
{
	return mName;
}

const std::string& File::getPath() const
{
	return mPath;
}

const std::string& File::getRelativePath() const
{
	return mRelativePath;
}