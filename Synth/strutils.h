// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment1:		Cheats:EnabledMetatext Platforming
// Student Name:	Eugene Long - [Engine Designer]
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// InkdotEngine - String Utility Class Specification
// ===========================================================================
// * This is a InkdotEngine component, derived from the standard GPP engine
// templates provided by Ms. Lee Ching Yun, modified by Eugene Long.
// ===========================================================================

#ifndef _INKDOT_STRUTIL_H
#define _INKDOT_STRUTIL_H

// import required headers
#include <string>
#include <locale>
#include <codecvt>


// class specification

class StringUtilities
{
public:

	// convert string to wide string for UTF8 strings
	// ref: https://stackoverflow.com/a/18374698
	static std::wstring UTF8s2ws(
		const std::string& str
	) {
		// initialise converter
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

		// convert string
		return converter.from_bytes(str);
	}

	// convert wide string to string for UTF8 strings
	// ref: https://stackoverflow.com/a/18374698
	static std::string UTF8ws2s(
		const std::wstring& wstr
	) {
		// initialise converter
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

		// convert string
		return converter.to_bytes(wstr);
	}
};


#endif // !_INKDOT_STRUTIL_H