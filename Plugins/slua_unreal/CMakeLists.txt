cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Debug)

project(lua)

set(EXT_SRC_ROOT External)
set(LUA_INC_PATH ${EXT_SRC_ROOT}/lua)
set(LUA_SRC_PATH ${EXT_SRC_ROOT}/lua)

set(LUA_SRC_FILES 
    ${LUA_SRC_PATH}/lapi.cpp
    ${LUA_SRC_PATH}/lauxlib.cpp
    ${LUA_SRC_PATH}/lbaselib.cpp
    ${LUA_SRC_PATH}/lbitlib.cpp
    ${LUA_SRC_PATH}/lcode.cpp
    ${LUA_SRC_PATH}/lcorolib.cpp
    ${LUA_SRC_PATH}/lctype.cpp
    ${LUA_SRC_PATH}/ldblib.cpp
    ${LUA_SRC_PATH}/ldebug.cpp
    ${LUA_SRC_PATH}/ldo.cpp
    ${LUA_SRC_PATH}/ldump.cpp
    ${LUA_SRC_PATH}/lfunc.cpp
    ${LUA_SRC_PATH}/lgc.cpp
    ${LUA_SRC_PATH}/linit.cpp
    ${LUA_SRC_PATH}/liolib.cpp
    ${LUA_SRC_PATH}/llex.cpp
    ${LUA_SRC_PATH}/lmathlib.cpp
    ${LUA_SRC_PATH}/lmem.cpp
    ${LUA_SRC_PATH}/loadlib.cpp
    ${LUA_SRC_PATH}/lobject.cpp
    ${LUA_SRC_PATH}/lopcodes.cpp
    ${LUA_SRC_PATH}/loslib.cpp
    ${LUA_SRC_PATH}/lparser.cpp
    ${LUA_SRC_PATH}/lstate.cpp
    ${LUA_SRC_PATH}/lstring.cpp
    ${LUA_SRC_PATH}/lstrlib.cpp
    ${LUA_SRC_PATH}/ltable.cpp
    ${LUA_SRC_PATH}/ltablib.cpp
    ${LUA_SRC_PATH}/ltm.cpp
    ${LUA_SRC_PATH}/lundump.cpp
    ${LUA_SRC_PATH}/lutf8lib.cpp
    ${LUA_SRC_PATH}/lvm.cpp
    ${LUA_SRC_PATH}/lzio.cpp
)

set(THIRDPART_INC_PATH "")
set(THIRDPART_SRC_FILES "")

include_directories(
    ${LUA_INC_PATH}
    ${THIRDPART_INC_PATH}
)

# add_definitions("-DLUA_USE_C89")

if(APPLE)
    if(IOS)
        set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD)")
    else()
        set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD_64_BIT)")
    endif()
endif()

add_library(lua STATIC
    ${LUA_SRC_FILES}
    ${THIRDPART_SRC_FILES}
)
