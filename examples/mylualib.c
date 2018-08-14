#include <lua.h>
#include <lauxlib.h>

#include "lbs.h"
#include "types.h"

typedef struct {
  float x, y, z;
} vec3;

static int new_vec3(lua_State *L) {
	vec3 foo = {1,2,3};
	lbs_push_value(L, "vec3", foo);
	return 1;
}

typedef struct {
  float f;
  double d;
  char x;
  int8_t i8;
  int16_t i16;
  int32_t i32;
  int64_t i64;
  void *p;
} demo;

static int new_demo(lua_State *L) {
	demo foo = {};
	lbs_push_value(L, "demo", foo);
	return 1;
}

static const luaL_Reg lib[] = {
	{ "new_vec3", new_vec3 },
	{ "new_demo", new_demo },
	{ NULL, NULL }
};

int luaopen_mylualib(lua_State *L) {
	lbs_register_type(L, "vec3");
	lbs_register_float_field(L, "vec3", vec3, x);
	lbs_register_float_field(L, "vec3", vec3, y);
	lbs_register_float_field(L, "vec3", vec3, z);

	lbs_register_type(L, "demo");
	lbs_register_float_field(   L, "demo", demo, f);
	lbs_register_double_field(  L, "demo", demo, d);
	lbs_register_char_field(    L, "demo", demo, x);
	lbs_register_int8_field(  L, "demo", demo, i8);
	lbs_register_int16_field( L, "demo", demo, i16);
	lbs_register_int32_field( L, "demo", demo, i32);
	lbs_register_int64_field( L, "demo", demo, i64);
	lbs_register_pointer_field(    L, "demo", demo, p);

	luaL_newlib(L, lib);
	return 1;
}
