#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "lbs.h"


static int lbs__index(lua_State *L) {
	void* p = luaL_checkudata(L, 1, lua_tostring(L, lua_upvalueindex(1)));
	lbs_field_info *field_info;
	lua_settop(L, 2);
	if (lua_rawget(L, lua_upvalueindex(2)) != LUA_TUSERDATA)
		return 0;
	field_info = lua_touserdata(L, -1);
	lua_settop(L, 0);
	field_info->getter(field_info, L, p);
	return 1;
}

static int lbs__newindex(lua_State *L) {
	void* p = luaL_checkudata(L, 1, lua_tostring(L, lua_upvalueindex(1)));
	lbs_field_info *field_info;
	lua_settop(L, 3);
	lua_rotate(L, -2, 1);
	if (lua_rawget(L, lua_upvalueindex(2)) != LUA_TUSERDATA)
		return 0;
	field_info = lua_touserdata(L, -1);
	lua_pop(L, 1);
	field_info->setter(field_info, L, p);
	return 1;
}

static int field_info_cmp(lua_State *L) {
	lbs_field_info *a = lua_touserdata(L, 1);
	lbs_field_info *b = lua_touserdata(L, 2);
	lua_pushboolean(L, a->offset < b->offset);
	return 1;
}

static int lbs__tostring(lua_State *L) {
	void* p = luaL_checkudata(L, 1, lua_tostring(L, lua_upvalueindex(1)));
	lbs_field_info *field_info = NULL;
	luaL_Buffer b;
	int i = 0, n;

	lua_settop(L, 1);
	/* we want output to be sorted by field offset */
	lua_newtable(L); /* table of fields */
	luaL_requiref(L, "table", luaopen_table, 0);
	lua_getfield(L, -1, "sort");
	lua_remove(L, -2); /* remove table library */
	lua_pushvalue(L, -2);

	lua_pushnil(L);
	while (lua_next(L, lua_upvalueindex(2)) != 0) {
		/* stack: ..., output_tbl, field_name, field_info  */
		lua_rawseti(L, -3, ++i);
	}

	lua_pushcfunction(L, field_info_cmp);
	lua_call(L, 2, 0);

	/* table is now sorted. construct output string */
	luaL_buffinit(L, &b);
	lua_pushvalue(L, lua_upvalueindex(1));
	luaL_addvalue(&b);
	luaL_addchar(&b, '{');

	n = i;
	for (i=1; i<=n; i++) {
		if (field_info)
			luaL_addchar(&b, ',');
		lua_rawgeti(L, 2, i);
		field_info = lua_touserdata(L, -1);
		luaL_addstring(&b, field_info->name);
		luaL_addchar(&b, '=');
		field_info->tostring(field_info, L, p);
		luaL_addvalue(&b);
		lua_pop(L, 1);
	}

	luaL_addchar(&b, '}');
	luaL_pushresult(&b);
	return 1;
}

void lbs_register_field(lua_State *L, const char *name,
	const char *field, const lbs_field_info* user_field_info) {
	luaL_getmetatable(L, name);
	lua_getfield(L, -1, "fields");
	lbs_field_info* field_info = lua_newuserdata(L, sizeof(lbs_field_info));
	*field_info = *user_field_info;
	field_info->name = lua_pushstring(L, field);
	lua_setuservalue(L, -2);
	lua_setfield(L, -2, field);
	lua_pop(L, 2);
}

static const luaL_Reg metamethods[] = {
	{ "__index", lbs__index },
	{ "__newindex", lbs__newindex },
	{ "__tostring", lbs__tostring },
	{ NULL, NULL }
};
void lbs_register_type(lua_State *L, const char *name) {
	luaL_newmetatable(L, name);
	lua_pushstring(L, name);
	lua_newtable(L);

	lua_pushvalue(L, -1);
	lua_setfield(L, -4, "fields");

	luaL_setfuncs(L, metamethods, 2);
}
