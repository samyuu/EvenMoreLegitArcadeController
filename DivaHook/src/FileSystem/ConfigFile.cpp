#include <stdio.h>
#include "ConfigFile.h"
#include "../Utilities/Operations.h"

namespace DivaHook::FileSystem
{
	ConfigFile::ConfigFile(const std::string &path) : TextFile(path)
	{
		return;
	}

	ConfigFile::ConfigFile(const std::string &directory, const std::string &file) : TextFile(directory, file)
	{
		return;
	}

	void ConfigFile::Parse(std::ifstream &fileStream)
	{
		std::string line;

		while (std::getline(fileStream, line))
		{
			if (IsComment(line))
				continue;

			auto splitline = Utilities::Split(line, "=");

			for (auto &line : splitline)
				Utilities::Trim(line);

			ConfigMap.insert(std::make_pair(splitline[0], splitline[1]));
		}
	}

	bool ConfigFile::IsComment(std::string &line)
	{
		return line[0] == '#' || line._Starts_with("//");
	}
}
