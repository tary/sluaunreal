 #pragma once
 #include <stdint.h>
#include "lua/lua.hpp"
#include "lua/lstate.h"
//struct lua_State;
namespace slua {
#define IOSTRING_BUF_LEN 65535
 	typedef struct {
 		size_t size;
 		uint8_t buf[IOSTRING_BUF_LEN];
 	} IOString;
 
 	class LuaProtoUtils
 	{
 	public:
 		static int init(lua_State* L);
 	private:
 		static int iostring_new(lua_State* L);
 		static int iostring_get(lua_State* L);
 		static int iostring_len(lua_State* L);
 		static int iostring_clear(lua_State* L);
 		static int encodeVarintSize(uint64_t x);
 		static int encodeVarintSizeL(lua_State* L);
 		static int encodeVarsintSizeL(lua_State* L);
 		static void encodeVarint(IOString *io, uint64_t v);
 		static int encodeVarintL(lua_State* L);
 		static int encodeVarint32L(lua_State* L);
 		static int encodeVarint64L(lua_State* L);
 		static int encodeDoubleL(lua_State* L);
 		static int encodeFloatL(lua_State* L);
 		static int encodeFixed64L(lua_State* L);
 		static int encodeFixed32L(lua_State* L);
 		static int encodeSFixed64L(lua_State* L);
 		static int encodeSFixed32L(lua_State* L);
 		static int encodeStringL(lua_State* L);
 		static int encodeBytesL(lua_State* L);
 		static int decodeVarintL(lua_State* L);
 		static int decodeVarint32L(lua_State* L);
 		static int decodeVarint64L(lua_State* L);
 		static int decodeFixed32L(lua_State* L);
 		static int decodeFixed64L(lua_State* L);
 		static int decodeSFixed32L(lua_State* L);
 		static int decodeSFixed64L(lua_State* L);
 		static int decodeFloatL(lua_State* L);
 		static int decodeDoubleL(lua_State* L);
 		static int decodeStringL(lua_State* L);
 		static int decodeBytesL(lua_State* L);
 		static size_t skipDefaultField(IOString *io, size_t iNdEx);
 		static int skipDefaultFieldL(lua_State* L);
 	};
}