#pragma once
#include "LuaVar.h"
#include "LuaVarUtil.h"

#include "LuaTable.generated.h"

template <typename T>
struct TIsLuaTable { enum { Value = false }; };

template <>
struct TIsLuaTable<FLuaTable> { enum { Value = true }; };

template <typename T>
struct TIsLuaVar { enum { Value = false }; };
template <>
struct TIsLuaVar<slua::LuaVar> { enum { Value = true }; };

USTRUCT(BlueprintType)
struct SLUA_UNREAL_API FLuaTable
{
	GENERATED_USTRUCT_BODY()
	slua::LuaVar Table;

	template<typename R, typename T>
	typename std::enable_if<TIsTArray<R>::Value || slua::TIsTMap<R>::Value, bool>::type GetFromTable(T key, R& OutResult) const
	{
		if (Table.isNil() || !Table.isValid() || !Table.isTable()) { return false; }
		slua::LuaVar arrVar;
		Table.getFromTable<slua::LuaVar>(key, arrVar);
		return slua::getFromVar(arrVar, OutResult);
	}

	template<typename R, typename T>
	typename std::enable_if<slua::TIsFString<R>::Value, bool>::type GetFromTable(T key, R& OutResult) const
	{
		if (Table.isNil() || !Table.isValid() || !Table.isTable()) { return false; }
		slua::LuaVar strVar;
		Table.getFromTable<slua::LuaVar>(key, strVar);
		return slua::getFromVar(strVar, OutResult);
	}

	template<typename R, typename T>
	typename std::enable_if<TIsLuaVar<R>::Value, bool>::type GetFromTable(T key, R& OutResult) const
	{
		if (Table.isNil() || !Table.isValid() || !Table.isTable()) { return false; }
		Table.getFromTable<slua::LuaVar>(key, OutResult);
		return true;
	}

	template<typename R, typename T>
	typename std::enable_if<TIsLuaTable<R>::Value, bool>::type GetFromTable(T key, R& OutResult) const
	{
		if (Table.isNil() || !Table.isValid() || !Table.isTable()) { return false; }
		slua::LuaVar tabVar;
		Table.getFromTable<slua::LuaVar>(key, tabVar);

		if (tabVar.isNil() || !tabVar.isValid()) { return false; }
		OutResult.Table = tabVar;
		return true;
	}

	template<typename R, typename T>
	typename std::enable_if<!slua::TIsFString<R>::Value && !TIsLuaTable<R>::Value && !TIsLuaVar<R>::Value && !slua::TIsTMap<R>::Value && !TIsTArray<R>::Value, bool>::type GetFromTable(T key, R& OutResult) const
	{
		if (Table.isNil() || !Table.isValid() || !Table.isTable()) { return false; }
		Table.getFromTable<R>(key, OutResult);
		return true;
	}
};

namespace slua {
	static UScriptStruct* FLuaTableStruct = nullptr;
	struct FLuaTableWrapper
	{
		static int __ctor(lua_State* L) {
			auto argc = lua_gettop(L);
			if (argc == 1) {
				lua_newtable(L);
				return 1;
			}
			if (argc == 2) {
				lua_pushvalue(L, 2);
				return 1;
			}
			luaL_error(L, "call FLuaTable() error, argc=%d", argc);
			return 0;
		}

		static void bind(lua_State* L)
		{
			FLuaTableStruct = FLuaTable::StaticStruct();
			AutoStack autoStack(L);
			LuaObject::newType(L, "FLuaTable");
			LuaObject::finishType(L, "FLuaTable", __ctor, nullptr);
		}
	};

	static void __pushLuaTable(lua_State* L, UStructProperty* p, uint8* parms)
	{
		FLuaTable temp;
		p->CopyCompleteValue(&temp, parms);
		temp.Table.push(L);
	}

	static void __checkLuaTable(lua_State* L, UStructProperty* p, uint8* parms, int i)
	{
		FLuaTable v;
		v.Table.set(L, i);
		p->CopyCompleteValue(parms, &v);
	}
}