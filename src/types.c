#include <lua.h>
#include <lauxlib.h>

#include "types.h"

/* Based on code from lua 5.3's lauxlib.c but without argerror */
static void fielderror(lbs_field_info* field_info, lua_State *L, int arg, const char *tname) {
	const char *msg;
	const char *typearg;  /* name for the type of the actual argument */
	if (luaL_getmetafield(L, arg, "__name") == LUA_TSTRING)
		typearg = lua_tostring(L, -1);  /* use the given type name */
	else if (lua_type(L, arg) == LUA_TLIGHTUSERDATA)
		typearg = "light userdata";  /* special name for messages */
	else
		typearg = luaL_typename(L, arg);  /* standard name */
	luaL_error(L, lua_pushfstring(L, "bad type for field %s.%s (%s expected, got %s)",
		lua_tostring(L, lua_upvalueindex(1)), field_info->name,
		tname, typearg));
}


/* Floats */

void lbs_float_getter(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	lua_pushnumber(L, *(const float*)(ptr+field_info->offset));
}

void lbs_float_setter(lbs_field_info* field_info, lua_State *L, void* ptr) {
	int isnum;
	lua_Number d = lua_tonumberx(L, -1, &isnum);
	if (!isnum)
		return fielderror(field_info, L, -1, lua_typename(L, LUA_TNUMBER));
	*(float*)(ptr+field_info->offset) = d;
}

void lbs_float_tostring(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	lua_pushfstring(L, "%f", *(const float*)(ptr+field_info->offset));
}


/* Doubles */

void lbs_double_getter(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	lua_pushnumber(L, *(const double*)(ptr+field_info->offset));
}

void lbs_double_setter(lbs_field_info* field_info, lua_State *L, void* ptr) {
	int isnum;
	lua_Number d = lua_tonumberx(L, -1, &isnum);
	if (!isnum)
		return fielderror(field_info, L, -1, lua_typename(L, LUA_TNUMBER));
	*(double*)(ptr+field_info->offset) = d;
}

void lbs_double_tostring(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	lua_pushfstring(L, "%f", *(const double*)(ptr+field_info->offset));
}


/* char */

void lbs_char_getter(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	char tmp[2] = {*(const char*)(ptr+field_info->offset), 0};
	lua_pushstring(L, tmp);
}

void lbs_char_setter(lbs_field_info* field_info, lua_State *L, void* ptr) {
	size_t len;
	const char *s = lua_tolstring(L, -1, &len);
	if (!s || len != 1)
		return fielderror(field_info, L, -1, "single character string");
	*(char*)(ptr+field_info->offset) = s[0];
}

void lbs_char_tostring(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	lua_pushfstring(L, "%c", *(const char*)(ptr+field_info->offset));
}


/* int8 */

void lbs_int8_getter(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	lua_pushinteger(L, *(const int8_t*)(ptr+field_info->offset));
}

void lbs_int8_setter(lbs_field_info* field_info, lua_State *L, void* ptr) {
	int isnum;
	lua_Integer n = lua_tointegerx(L, -1, &isnum);
	if (!isnum)
		return fielderror(field_info, L, -1, lua_typename(L, LUA_TNUMBER));
	*(int8_t*)(ptr+field_info->offset) = n;
}

void lbs_int8_tostring(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	lua_pushfstring(L, "%d", *(const int8_t*)(ptr+field_info->offset));
}


/* int16 */

void lbs_int16_getter(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	lua_pushinteger(L, *(const int16_t*)(ptr+field_info->offset));
}

void lbs_int16_setter(lbs_field_info* field_info, lua_State *L, void* ptr) {
	int isnum;
	lua_Integer n = lua_tointegerx(L, -1, &isnum);
	if (!isnum)
		return fielderror(field_info, L, -1, lua_typename(L, LUA_TNUMBER));
	*(int16_t*)(ptr+field_info->offset) = n;
}

void lbs_int16_tostring(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	lua_pushfstring(L, "%d", *(const int16_t*)(ptr+field_info->offset));
}


/* int32 */

void lbs_int32_getter(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	lua_pushinteger(L, *(const int32_t*)(ptr+field_info->offset));
}

void lbs_int32_setter(lbs_field_info* field_info, lua_State *L, void* ptr) {
	int isnum;
	lua_Integer n = lua_tointegerx(L, -1, &isnum);
	if (!isnum)
		return fielderror(field_info, L, -1, lua_typename(L, LUA_TNUMBER));
	*(int32_t*)(ptr+field_info->offset) = n;
}

void lbs_int32_tostring(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	lua_pushfstring(L, "%d", *(const int32_t*)(ptr+field_info->offset));
}


/* int64 */

void lbs_int64_getter(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	lua_pushinteger(L, *(const int64_t*)(ptr+field_info->offset));
}

void lbs_int64_setter(lbs_field_info* field_info, lua_State *L, void* ptr) {
	int isnum;
	lua_Integer n = lua_tointegerx(L, -1, &isnum);
	if (!isnum)
		return fielderror(field_info, L, -1, lua_typename(L, LUA_TNUMBER));
	*(int64_t*)(ptr+field_info->offset) = n;
}

void lbs_int64_tostring(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	lua_pushfstring(L, "%d", *(const int64_t*)(ptr+field_info->offset));
}


/* pointer */

void lbs_pointer_getter(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	lua_pushlightuserdata(L, *(void**)(ptr+field_info->offset));
}

void lbs_pointer_setter(lbs_field_info* field_info, lua_State *L, void* ptr) {
	if (lua_type(L, -1) != LUA_TLIGHTUSERDATA)
		return fielderror(field_info, L, -1, lua_typename(L, LUA_TLIGHTUSERDATA));
	*(void**)(ptr+field_info->offset) = lua_touserdata(L, -1);
}

void lbs_pointer_tostring(lbs_field_info* field_info, lua_State *L, const void* ptr) {
	lua_pushfstring(L, "%p", *(const void**)(ptr+field_info->offset));
}
