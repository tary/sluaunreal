#pragma once
#include "LuaVar.h"

#include "LuaTable.generated.h"


USTRUCT(BlueprintType)
struct SLUA_UNREAL_API FLuaTable
{
	GENERATED_USTRUCT_BODY()
	slua::LuaVar Table;
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