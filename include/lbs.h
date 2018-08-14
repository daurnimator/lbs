#ifndef LBS_H
#define LBS_H

#include <lua.h> /* lua_State */

typedef struct lbs_field_info lbs_field_info;

typedef void (*lbs_getter)(lbs_field_info*, lua_State*, const void *);
typedef void (*lbs_setter)(lbs_field_info*, lua_State*, void *);
typedef void (*lbs_tostring)(lbs_field_info*, lua_State*, const void *);

struct lbs_field_info {
	ptrdiff_t offset;
	lbs_getter getter;
	lbs_setter setter;
	lbs_tostring tostring;
	const char *name;
};

void lbs_register_field(lua_State *L, const char *name,
	const char *field, const lbs_field_info* user_field_info);

void lbs_register_type(lua_State *L, const char *name);

#define lbs_push_value(L, name, value) { \
	typeof(value)* dest = lua_newuserdata(L, sizeof(value)); \
	*dest = (value); \
	luaL_setmetatable(L, (name)); \
}

#endif /* LBS_H */
