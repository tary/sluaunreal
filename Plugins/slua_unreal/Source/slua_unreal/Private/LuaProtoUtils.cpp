#include "LuaProtoUtils.h"
#include "CoreMinimal.h"
#include "lua/lua.h"
#include "lua/lua.hpp"
#include "lua/lstate.h"
namespace slua {

 	int LuaProtoUtils::init(lua_State* L)
 	{
		lua_pushcfunction(L, iostring_new);
		lua_setglobal(L, "iostring_new");
 
		lua_pushcfunction(L, iostring_get);
		lua_setglobal(L, "iostring_get");
 
		lua_pushcfunction(L, iostring_len);
		lua_setglobal(L, "iostring_len");
 
		lua_pushcfunction(L, iostring_clear);
		lua_setglobal(L, "iostring_clear");
 
		lua_pushcfunction(L, encodeVarintSizeL);
		lua_setglobal(L, "encodeVarintSize");
 
		lua_pushcfunction(L, encodeVarintL);
		lua_setglobal(L, "encodeVarint");
 
		lua_pushcfunction(L, encodeVarint32L);
		lua_setglobal(L, "encodeVarint32");
 
		lua_pushcfunction(L, encodeVarint64L);
		lua_setglobal(L, "encodeVarint64");
 
		lua_pushcfunction(L, encodeDoubleL);
		lua_setglobal(L, "encodeDouble");
 
		lua_pushcfunction(L, encodeFloatL);
		lua_setglobal(L, "encodeFloat");
 
		lua_pushcfunction(L, encodeFixed64L);
		lua_setglobal(L, "encodeFixed64");
 
		lua_pushcfunction(L, encodeFixed32L);
		lua_setglobal(L, "encodeFixed32");
 
		lua_pushcfunction(L, encodeSFixed64L);
		lua_setglobal(L, "encodeSFixed64");
 
		lua_pushcfunction(L, encodeSFixed32L);
		lua_setglobal(L, "encodeSFixed32");
 
		lua_pushcfunction(L, encodeStringL);
		lua_setglobal(L, "encodeString");
 
		lua_pushcfunction(L, encodeBytesL);
		lua_setglobal(L, "encodeBytes");
 
		lua_pushcfunction(L, decodeVarintL);
		lua_setglobal(L, "decodeVarint");
 
		lua_pushcfunction(L, decodeVarint32L);
		lua_setglobal(L, "decodeVarint32");
 
		lua_pushcfunction(L, decodeVarint64L);
		lua_setglobal(L, "decodeVarint64");
 
		lua_pushcfunction(L, decodeFixed32L);
		lua_setglobal(L, "decodeFixed32");
 
		lua_pushcfunction(L, decodeFixed64L);
		lua_setglobal(L, "decodeFixed64");
 
		lua_pushcfunction(L, decodeSFixed32L);
		lua_setglobal(L, "decodeSFixed32");
 
		lua_pushcfunction(L, decodeSFixed64L);
		lua_setglobal(L, "decodeSFixed64");
 
		lua_pushcfunction(L, decodeFloatL);
		lua_setglobal(L, "decodeFloat");
 
		lua_pushcfunction(L, decodeDoubleL);
		lua_setglobal(L, "decodeDouble");
 
		lua_pushcfunction(L, decodeStringL);
		lua_setglobal(L, "decodeString");
 
		lua_pushcfunction(L, decodeBytesL);
		lua_setglobal(L, "decodeBytes");
 
		lua_pushcfunction(L, skipDefaultFieldL);
		lua_setglobal(L, "skipDefaultField");
 		return 0;
 	}
 
 	int LuaProtoUtils::iostring_new(lua_State* L)
 	{
 		IOString* io = (IOString*)lua_newuserdata(L, sizeof(IOString));
 		io->size = 0;
 		return 1;
 	}
 
 	int LuaProtoUtils::iostring_get(lua_State* L)
 	{
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 
 		lua_newtable(L);
 		lua_pushnumber(L, -1);
 		lua_rawseti(L, -2, 0);
 		for (size_t i = 0; i < io->size; i++)
 		{
 			lua_pushinteger(L, io->buf[i]);
 			lua_rawseti(L, -2, i + 1);
 		}
 		return 1;
 	}
 
 	int LuaProtoUtils::iostring_len(lua_State* L)
 	{
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		lua_pushinteger(L, io->size);
 		return 1;
 	}
 
 	int LuaProtoUtils::iostring_clear(lua_State* L)
 	{
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		io->size = 0;
 		return 0;
 	}
 
 	int LuaProtoUtils::encodeVarintSize(uint64_t x) {
 		int n = 0;
 		while (x > 0) {
 			n++;
 			x >>= 7;
 		}
 		return n;
 	}
 
 	int LuaProtoUtils::encodeVarintSizeL(lua_State* L) {
 		lua_Number l_x = luaL_checknumber(L, 1);
 		uint64_t x = (uint64_t)l_x;
 		int size = encodeVarintSize(x);
 		lua_pushnumber(L, (lua_Number)size);
 		return 1;
 	}
 
 	int LuaProtoUtils::encodeVarsintSizeL(lua_State* L) {
 		lua_Number l_x = luaL_checknumber(L, 1);
 		int64_t x = (int64_t)l_x;
 		uint64_t nx = (uint64_t)((x << 1) ^ (x >> 63));
 		int size = encodeVarintSize(nx);
 		lua_pushnumber(L, (lua_Number)size);
 		return 1;
 	}
 
 	void LuaProtoUtils::encodeVarint(IOString *io, uint64_t v) {
 		while (v >= 1 << 7) {
 			io->buf[io->size] = (uint8_t)((v & 0x7f) | 0x80);
 			v >>= 7;
 			io->size++;
 		}
 		io->buf[io->size] = (uint8_t)(v);
 		io->size++;
 	}
 
 	int LuaProtoUtils::encodeVarintL(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		uint64_t x = (uint64_t)luaL_checknumber(L, 2);
 		encodeVarint(io, x);
 		return 0;
 	}
 
 	int LuaProtoUtils::encodeVarint32L(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		uint32_t x = (uint32_t)luaL_checknumber(L, 2);
 		uint64_t nx = (uint64_t)((x << 1) ^ (x >> 31));
 		encodeVarint(io, nx);
 		return 0;
 	}
 
 	int LuaProtoUtils::encodeVarint64L(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		uint64_t x = (uint64_t)luaL_checknumber(L, 2);
 		x = ((x << 1) ^ (x >> 63));
 		encodeVarint(io, x);
 		return 0;
 	}
 
 	int LuaProtoUtils::encodeDoubleL(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		lua_Number l_x = luaL_checknumber(L, 2);
 		double x = (double)l_x;
 		*((double*)(&io->buf[io->size])) = x;
 		io->size += 8;
 		return 0;
 	}
 
 	int LuaProtoUtils::encodeFloatL(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		float x = (float)luaL_checknumber(L, 2);
 		*((float*)(&io->buf[io->size])) = x;
 		io->size += 4;
 		return 0;
 	}
 
 	int LuaProtoUtils::encodeFixed64L(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		uint64_t x = (uint64_t)luaL_checknumber(L, 2);
 		*((uint64_t*)(&io->buf[io->size])) = x;
 		io->size += 8;
 		return 0;
 	}
 
 	int LuaProtoUtils::encodeFixed32L(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		uint32_t x = (uint32_t)luaL_checknumber(L, 2);
 		*((uint32_t*)(&io->buf[io->size])) = x;
 		io->size += 4;
 		return 0;
 	}
 
 	int LuaProtoUtils::encodeSFixed64L(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		int64_t x = (int64_t)luaL_checknumber(L, 2);
 		*((int64_t*)(&io->buf[io->size])) = x;
 		io->size += 8;
 		return 0;
 	}
 
 	int LuaProtoUtils::encodeSFixed32L(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		int32_t x = (int32_t)luaL_checknumber(L, 2);
 		*((int32_t*)(&io->buf[io->size])) = x;
 		io->size += 4;
 		return 0;
 	}
 
 	int LuaProtoUtils::encodeStringL(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		size_t size;
 		const char* str = luaL_checklstring(L, 2, &size);
 		encodeVarint(io, (uint64_t)size);
 		if (io->size + size > IOSTRING_BUF_LEN) {
 			luaL_error(L, "Out of range");
 		}
 		FMemory::Memcpy(io->buf + io->size, str, size);
 		io->size += size;
 		return 0;
 	}
 
 	int LuaProtoUtils::encodeBytesL(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		luaL_checktype(L, 2, LUA_TTABLE);
 		size_t len = (size_t)luaL_len(L, 2);
 		encodeVarint(io, (uint64_t)len);
 		for (size_t i = 1; i <= len; i++)
 		{
 			lua_rawgeti(L, 2, i);
 			io->buf[io->size] = (uint8_t)lua_tointeger(L, -1);
 			io->size++;
 			lua_pop(L, 1);
 		}
 		return 0;
 	}
 
 	int LuaProtoUtils::decodeVarintL(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		size_t idx = (size_t)luaL_checknumber(L, 2);
 		uint64_t wire = 0;
 		for (uint64_t shift = 0; ; shift += 7) {
 			if (shift >= 64) {
 				luaL_error(L, "proto: negative length found during unmarshaling");
 			}
 			if (idx >= io->size) {
 				luaL_error(L, "proto: unexpected EOF");
 			}
 			uint8_t b = io->buf[idx];
 			idx++;
 			wire |= ((uint64_t)b & 0x7F) << shift;
 			if (b < 0x80) {
 				break;
 			}
 		}
 		lua_pushnumber(L, (lua_Number)wire);
 		lua_pushnumber(L, (lua_Number)idx);
 		return 2;
 	}
 
 	int LuaProtoUtils::decodeVarint32L(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		lua_Number l_idx = luaL_checknumber(L, 2);
 		size_t idx = (size_t)l_idx;
 		uint32_t wire = 0;
 		for (uint64_t shift = 0; ; shift += 7) {
 			if (shift >= 64) {
 				luaL_error(L, "proto: negative length found during unmarshaling");
 			}
 			if (idx >= io->size) {
 				luaL_error(L, "proto: unexpected EOF");
 			}
 			uint8_t b = io->buf[idx];
 			idx++;
 			wire |= ((uint32_t)b & 0x7F) << shift;
 			if (b < 0x80) {
 				break;
 			}
 		}
 		wire = (wire >> 1) ^ (((wire & 1) << 31) >> 31);
 		lua_pushnumber(L, (lua_Number)wire);
 		lua_pushnumber(L, (lua_Number)idx);
 		return 2;
 	}
 
 	int LuaProtoUtils::decodeVarint64L(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		lua_Number l_idx = luaL_checknumber(L, 2);
 		size_t idx = (size_t)l_idx;
 		uint64_t wire = 0;
 		for (uint64_t shift = 0; ; shift += 7) {
 			if (shift >= 64) {
 				luaL_error(L, "proto: negative length found during unmarshaling");
 			}
 			if (idx >= io->size) {
 				luaL_error(L, "proto: unexpected EOF");
 			}
 			uint8_t b = io->buf[idx];
 			idx++;
 			wire |= ((uint64_t)b & 0x7F) << shift;
 			if (b < 0x80) {
 				break;
 			}
 		}
 		wire = (wire >> 1) ^ (((wire & 1) << 63) >> 63);
 		lua_pushnumber(L, (lua_Number)wire);
 		lua_pushnumber(L, (lua_Number)idx);
 		return 2;
 	}
 
 	int LuaProtoUtils::decodeFixed32L(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		int idx = (int)luaL_checknumber(L, 2);
 		uint32_t num = *((uint32_t*)(&io->buf[idx]));
 		idx += 4;
 		lua_pushnumber(L, (lua_Number)num);
 		lua_pushnumber(L, (lua_Number)idx);
 		return 2;
 	}
 
 	int LuaProtoUtils::decodeFixed64L(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		int idx = (int)luaL_checknumber(L, 2);
 		uint64_t num = *((uint64_t*)(&io->buf[idx]));
 		idx += 8;
 		lua_pushnumber(L, (lua_Number)num);
 		lua_pushnumber(L, (lua_Number)idx);
 		return 2;
 	}
 
 	int LuaProtoUtils::decodeSFixed32L(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		int idx = (int)luaL_checknumber(L, 2);
 		int32_t num = *((int32_t*)(&io->buf[idx]));
 		idx += 4;
 		lua_pushnumber(L, (lua_Number)num);
 		lua_pushnumber(L, (lua_Number)idx);
 		return 2;
 	}
 
 	int LuaProtoUtils::decodeSFixed64L(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		int idx = (int)luaL_checknumber(L, 2);
 		int64_t num = *((int64_t*)(&io->buf[idx]));
 		idx += 8;
 		lua_pushnumber(L, (lua_Number)num);
 		lua_pushnumber(L, (lua_Number)idx);
 		return 2;
 	}
 
 	int LuaProtoUtils::decodeFloatL(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		int idx = (int)luaL_checknumber(L, 2);
 		lua_pushnumber(L, (lua_Number)*(float *)(&io->buf[idx]));
 		idx += 4;
 		lua_pushnumber(L, (lua_Number)idx);
 		return 2;
 	}
 
 	int LuaProtoUtils::decodeDoubleL(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		int idx = (int)luaL_checknumber(L, 2);
 
 		lua_pushnumber(L, (lua_Number)*(double *)(&io->buf[idx]));
 		idx += 8;
 		lua_pushnumber(L, (lua_Number)idx);
 		return 2;
 	}
 
 	int LuaProtoUtils::decodeStringL(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		int sidx = (int)luaL_checknumber(L, 2);
 		int eidx = (int)luaL_checknumber(L, 3);
 
 		lua_pushlstring(L, (char*)&io->buf[sidx], eidx - sidx);
 		return 1;
 	}
 
 	int LuaProtoUtils::decodeBytesL(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		size_t sidx = (size_t)luaL_checknumber(L, 2);
 		size_t eidx = (size_t)luaL_checknumber(L, 3);
 
 		lua_newtable(L);
 		lua_pushnumber(L, -1);
 		lua_rawseti(L, -2, 0);
 		for (size_t i = sidx; i < eidx; i++)
 		{
 			lua_pushinteger(L, io->buf[i]);
 			lua_rawseti(L, -2, i - sidx);
 		}
 		return 1;
 	}
 
 	size_t LuaProtoUtils::skipDefaultField(IOString *io, size_t iNdEx) {
 		while (iNdEx < io->size) {
 			uint64_t wire = 0;
 			for (uint64_t shift = 0; ; shift += 7) {
 				if (shift >= 64) {
 					return -1;
 				}
 				if (iNdEx >= io->size) {
 					return -2;
 				}
 				uint8_t b = io->buf[iNdEx];
 				iNdEx++;
 				wire |= ((uint64_t)b & 0x7F) << shift;
 				if (b < 0x80) {
 					break;
 				}
 			}
 			int wireType = (int)(wire & 0x7);
 			switch (wireType) {
 			case 0:
 				for (uint64_t shift = 0; ; shift += 7) {
 					if (shift >= 64) {
 						return -1;
 					}
 					if (iNdEx >= io->size) {
 						return -2;
 					}
 					iNdEx++;
 					if (io->buf[iNdEx - 1] < 0x80) {
 						break;
 					}
 				}
 				return iNdEx;
 			case 1:
 			{
 				iNdEx += 8;
 				return iNdEx;
 			}
 			case 2:
 			{
 				int length = 0;
 				for (uint64_t shift = (0); ; shift += 7) {
 					if (shift >= 64) {
 						return -1;
 					}
 					if (iNdEx >= io->size) {
 						return -2;
 					}
 					uint8_t b = io->buf[iNdEx];
 					iNdEx++;
 					length |= ((int)b & 0x7F) << shift;
 					if (b < 0x80) {
 						break;
 					}
 				}
 				iNdEx += length;
 				if (length < 0) {
 					return -4;
 				}
 				return iNdEx;
 			}
 			case 3:
 			{
 				while (1) {
 					uint64_t innerWire = 0;
 					int start = iNdEx;
 					for (uint64_t shift = 0; ; shift += 7) {
 						if (shift >= 64) {
 							return -1;
 						}
 						if (iNdEx >= io->size) {
 							return -2;
 						}
 						uint8_t b = io->buf[iNdEx];
 						iNdEx++;
 						innerWire |= ((uint64_t)b & 0x7F) << shift;
 						if (b < 0x80) {
 							break;
 						}
 					}
 					int innerWireType = (int)(innerWire & 0x7);
 					if (innerWireType == 4) {
 						break;
 					}
 					iNdEx = skipDefaultField(io, iNdEx);
 					if (iNdEx < 0) {
 						return iNdEx;
 					}
 				}
 				return iNdEx;
 			}
 			case 4:
 				return iNdEx;
 			case 5:
 				iNdEx += 4;
 				return iNdEx;
 			default:
 				return -3;
 			}
 		}
 		return -5;
 	}
 
 	int LuaProtoUtils::skipDefaultFieldL(lua_State* L) {
 		IOString *io = (IOString *)lua_touserdata(L, 1);
 		lua_Number l_idx = luaL_checknumber(L, 2);
 		size_t iNdEx = (size_t)l_idx;
 
 		iNdEx = skipDefaultField(io, iNdEx);
 
 		if (iNdEx == -1) {
 			luaL_error(L, "proto: negative length found during unmarshaling");
 		}
 		else if (iNdEx == -2) {
 			luaL_error(L, "proto: unexpected EOF");
 		}
 		else if (iNdEx == -3) {
 			luaL_error(L, "proto: illegal wireType");
 		}
 		else if (iNdEx == -4) {
 			luaL_error(L, "proto: negative length found during unmarshaling");
 		}
 		else if (iNdEx == -5) {
 			luaL_error(L, "unreachable");
 		}
 		lua_pushnumber(L, (lua_Number)iNdEx);
 		return 1;
 	}
}