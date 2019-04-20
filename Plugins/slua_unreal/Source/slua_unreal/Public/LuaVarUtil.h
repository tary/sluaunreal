#pragma once
#include "LuaVar.h"

namespace slua 
{
	template <typename T>
	struct TIsFString { enum { Value = false }; };

	template <>
	struct TIsFString<FString> { enum { Value = true }; };

	template<typename R>
	inline typename std::enable_if<TIsFString<R>::Value, bool>::type getFromVar(LuaVar& strVar, R& OutResult)
	{
		if (strVar.isNil() || !strVar.isValid() || !strVar.isString()) { return false; }
		OutResult = UTF8_TO_TCHAR(strVar.asString());
		return true;
	}

	template<typename R>
	inline typename std::enable_if<TIsTArray<R>::Value, bool>::type getFromVar(LuaVar& arrVar, R& OutResult)
	{
		if (arrVar.isNil() || !arrVar.isValid() || !arrVar.isTable()) { return false; }
		LuaVar key, value;
		while (arrVar.next(key, value))
		{
			R::ElementType OutItem;
			if (slua::getFromVar(value, OutItem))
			{
				OutResult.Add(OutItem);
			}
		}
		return true;
	}

	template<typename R>
	inline typename std::enable_if<slua::TIsTMap<R>::Value, bool>::type getFromVar(slua::LuaVar& arrVar, R& OutResult)
	{
		if (arrVar.isNil() || !arrVar.isValid() || !arrVar.isTable()) { return false; }
		LuaVar key, value;
		while (arrVar.next(key, value))
		{
			R::ElementType::KeyType OutKeyVal;
			R::ElementType::ValueType OutValVal;
			if (slua::getFromVar(key, OutKeyVal) && slua::getFromVar(value, OutValVal))
			{
				OutResult.Add(OutKeyVal, OutValVal);
			}
		}
		return true;
	}

	template<typename R>
	inline typename std::enable_if<!TIsFString<R>::Value && !TIsTArray<R>::Value && !slua::TIsTMap<R>::Value, bool>::type getFromVar(slua::LuaVar& intVar, R& OutResult)
	{
		if (intVar.isNil() || !intVar.isValid()) { return false; }
		intVar.castTo(OutResult);
		return true;
	}	
}