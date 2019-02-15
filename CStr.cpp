#include <cassert>
#include "CStr.h"

#ifndef CSTR_DEFAULT_CAP
#define CSTR_DEFAULT_CAP 60
#endif

#ifndef CSTR_DEFAULT_PAD_CAP
#define CSTR_DEFAULT_PAD_CAP 10
#endif

#define _CHAR_CAST(mem) static_cast<char*>(mem)

CStr::CStr(): _cap(CSTR_DEFAULT_CAP),
              _len(0),
              _str(_CHAR_CAST(std::malloc(_cap + 1))) /* + 1 for null char*/
{
	std::memset(_str, 0, _cap + 1);
}

CStr::CStr(const char* string)
{
	_len = std::strlen(string);
	_cap = _len + CSTR_DEFAULT_CAP;
	_str = static_cast<char*>(std::malloc(_cap + 1));
	std::strncpy(_str, string, _cap + 1);
}

CStr::CStr(const CStr& other): _cap(other.getCap()),
                               _len(other.getLen()),
                               _str(_CHAR_CAST(std::malloc(_cap + 1)))
{
	std::strncpy(_str, other.getStr(), _cap + 1);
}

void CStr::changeSize(size_t newSize)
{
	_cap = newSize;
	_str = _CHAR_CAST(std::realloc(_str, _cap + 1));
	_len = (_len < _cap) ? _cap : _len;
}

void CStr::rewrite(const char* string)
{
	_len = 0;
	while(*string && _len < _cap) {
		_str[_len++] = *string++;
	}
}

void CStr::rewriteAndExpand(const char* string)
{
	_len = 0;
	while(*string) {
		if(_len == _cap)
			changeSize(_cap * 2);
		_str[_len++] = *string++;
	}
}

void CStr::reserve(size_t size)
{
	_cap += size;
	_str = _CHAR_CAST(std::realloc(_str, _cap + 1));
}

CStr& CStr::operator=(const CStr& other)
{
	if(this != &other) {
		// check if internal string has enough space
		if(_cap < other.getLen())
			changeSize(other.getCap() + CSTR_DEFAULT_PAD_CAP);
		rewrite(other.getStr());
	}
	return *this;
}

CStr& CStr::operator=(const char* string)
{
	rewriteAndExpand(string);
	return *this;
}

CStr::~CStr()
{
		std::free(_str);
}
