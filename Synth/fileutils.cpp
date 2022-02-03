// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment1:		Cheats:Enabled
// Student Name:	Eugene Long - [Engine Designer]
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// File Utility Class Specification
// ===========================================================================

// include specification
#include "fileutils.h"


// ===========================================================================
// memoized game directory path state
// ===========================================================================
std::string FileUtils::gameDirectory = "";

// ===========================================================================
// get path to game directory path under Documents
// ===========================================================================
std::string FileUtils::getGameDirectoryPath()
{
	// use memoized state where possible,
	if (gameDirectory == "") {

		// else retrieve and store game directory path

		PWSTR pPath;

		// retrieve actual user document directory path - this is needed because
		// user document paths can vary between devices and windows versions.
		// this is the best practice to get an accurate filepath to Documents.
		SHGetKnownFolderPath(
			FOLDERID_Documents,
			KF_FLAG_DEFAULT,
			NULL,
			&pPath
		);

		// save path as string
		std::string dirpath = StringUtilities::UTF8ws2s(std::wstring(pPath));

		// deallocate pPath
		CoTaskMemFree(pPath);

		// calculate and store final game directory filepath
		gameDirectory = dirpath + "\\PlanetCollision";

		// ensure game directory exists
		CreateDirectoryA(gameDirectory.c_str(), NULL);
	}

	// return game directory path
	return gameDirectory;
}

// ===========================================================================
// read text from file
// ===========================================================================
std::string FileUtils::readFromFile(
	std::string	filename
) {
	// initialize path to file
	std::string filepath = "Levels/" + filename;

	// initialize file content container
	std::string content = "";

	// attempt to create input file stream for file
	std::ifstream file(filepath);

	// ensure file is open before reading from file
	if (file.is_open()) {

		std::string line;

		// while there are still lines that can be read from file,
		while (std::getline(file, line)) {

			// append line to file contents
			content += (line + "\n");
		}

		// close file when finished
		file.close();
	}
	else throw (
		GameError(
			gameErrorNS::WARNING,
			"Warning: Could not open file " + filepath
		)
		);

	// return file contents
	return content;
}

// ===========================================================================
// write text to file
// ===========================================================================
void FileUtils::writeToFile(
	std::string	filename,
	std::string	text
) {
	std::ofstream myfile;
	myfile.open("Levels/" + filename);
	myfile << text;
	myfile.close();
	//// initialize path to file
	//std::string filepath = getGameDirectoryPath() + "\\" + filename;

	//// attempt to create output file stream for file
	//std::ofstream file(filepath);

	//// ensure file is open before writing to file
	//if (file.is_open()) {

	//	// write text to file
	//	file << text;

	//	// close file when finished
	//	file.close();
	//}
	//else throw (
	//	InkdotError(
	//		InkdotErrorType::WARNING,
	//		"Warning: Could not open file " + filepath
	//	)
	//);
}


vector<string> FileUtils::getFiles(string folder) {
	//vector<string> names;
	//string search_path = folder + "/*.*";
	//WIN32_FIND_DATA fd;
	//HANDLE hFind = ::FindFirstFile(LPWSTR(search_path.c_str()), &fd);
	//if (hFind != INVALID_HANDLE_VALUE) {
	//	do {
	//		// read all (real) files in current folder
	//		// , delete '!' read other 2 default folder . and ..
	//		if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
	//			string str(1, fd.cFileName[0]);
	//			names.push_back(str);
	//			string s = str;
	//			std::wstring stemp = std::wstring(s.begin(), s.end());
	//			LPCWSTR sw = stemp.c_str();
	//			OutputDebugStringA("FILE:");
	//			OutputDebugStringW(sw);
	//		}
	//	} while (::FindNextFile(hFind, &fd));
	//	::FindClose(hFind);
	//}
	//return names;
	WIN32_FIND_DATAA findData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	std::string full_path = folder + "\\*";
	std::vector<std::string> dir_list;

	hFind = FindFirstFileA(full_path.c_str(), &findData);

	if (hFind == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Invalid handle value! Please check your path...");

	while (FindNextFileA(hFind, &findData) != 0)
	{
		dir_list.push_back(std::string(findData.cFileName));
	}

	FindClose(hFind);
	dir_list.erase(dir_list.begin());
	return dir_list;
}
