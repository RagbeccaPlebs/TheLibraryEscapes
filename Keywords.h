#pragma once
#include <string>

class Keywords
{
public:
	//Keywords
	static const inline std::string SIMPLE_BOOK_KEYWORD = "simplebook";
	static const inline std::string DOOR_KEYWORD = "door";
	static const inline std::string KEY_KEYWORD = "key";

	//File locations
	static const inline std::string FOUND_BOOKS_FILE = "assets/save/foundBooks.json";
	static const inline std::string ACTIVE_DOORS_FILE = "assets/save/doors.json";
	static const inline std::string KEYS_FOUND_FILE = "assets/save/keysFound.json";
};
