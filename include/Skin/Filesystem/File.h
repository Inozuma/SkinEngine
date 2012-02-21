#pragma once

#include <string>

namespace Skin
{
	class File
	{
	private:
		bool mOK;
		std::string mName;
		std::string mPath;
		std::string mExtension;
		std::string mRelativePath;
		int mSize;

	public:
		File();
		File(const std::string&);
		File(const std::string&, const std::string&, const std::string&, int);
		~File();

		bool exists() const;
		const std::string& getName() const;
		const std::string& getPath() const;
		const std::string& getExtension() const;
		const std::string& getRelativePath() const;
	};
}