#ifndef LBS_TYPES_H
#define LBS_TYPES_H

#include <stddef.h>	/* offsetof() */

#include "lbs.h"

/* Pre-processor hackery: */
#define LBS_NARG_(_15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1, N, ...) N
#define LBS_NARG(...) LBS_NARG_(__VA_ARGS__, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define LBS_PASTE(a, b) a ## b
#define LBS_XPASTE(a, b) LBS_PASTE(a, b)


void lbs_float_getter(lbs_field_info*, lua_State*, const void*);
void lbs_float_setter(lbs_field_info*, lua_State*, void*);
void lbs_float_tostring(lbs_field_info*, lua_State*, const void*);

#define lbs_register_float_field(L, struct_name, type, field) \
	lbs_register_field(L, struct_name, #field, &(lbs_field_info){ \
		.offset = offsetof(type, field), \
		.getter = lbs_float_getter, \
		.setter = lbs_float_setter, \
		.tostring = lbs_float_tostring, \
	})


void lbs_double_getter(lbs_field_info*, lua_State*, const void*);
void lbs_double_setter(lbs_field_info*, lua_State*, void*);
void lbs_double_tostring(lbs_field_info*, lua_State*, const void*);

#define lbs_register_double_field(L, struct_name, type, field) \
	lbs_register_field(L, struct_name, #field, &(lbs_field_info){ \
		.offset = offsetof(type, field), \
		.getter = lbs_double_getter, \
		.setter = lbs_double_setter, \
		.tostring = lbs_double_tostring, \
	})


void lbs_char_getter(lbs_field_info*, lua_State*, const void*);
void lbs_char_setter(lbs_field_info*, lua_State*, void*);
void lbs_char_tostring(lbs_field_info*, lua_State*, const void*);

#define lbs_register_char_field(L, struct_name, type, field) \
	lbs_register_field(L, struct_name, #field, &(lbs_field_info){ \
		.offset = offsetof(type, field), \
		.getter = lbs_char_getter, \
		.setter = lbs_char_setter, \
		.tostring = lbs_char_tostring, \
	})


void lbs_int8_getter(lbs_field_info*, lua_State*, const void*);
void lbs_int8_setter(lbs_field_info*, lua_State*, void*);
void lbs_int8_tostring(lbs_field_info*, lua_State*, const void*);

#define lbs_register_int8_field(L, struct_name, type, field) \
	lbs_register_field(L, struct_name, #field, &(lbs_field_info){ \
		.offset = offsetof(type, field), \
		.getter = lbs_int8_getter, \
		.setter = lbs_int8_setter, \
		.tostring = lbs_int8_tostring, \
	})


void lbs_int16_getter(lbs_field_info*, lua_State*, const void*);
void lbs_int16_setter(lbs_field_info*, lua_State*, void*);
void lbs_int16_tostring(lbs_field_info*, lua_State*, const void*);

#define lbs_register_int16_field(L, struct_name, type, field) \
	lbs_register_field(L, struct_name, #field, &(lbs_field_info){ \
		.offset = offsetof(type, field), \
		.getter = lbs_int16_getter, \
		.setter = lbs_int16_setter, \
		.tostring = lbs_int16_tostring, \
	})


void lbs_int32_getter(lbs_field_info*, lua_State*, const void*);
void lbs_int32_setter(lbs_field_info*, lua_State*, void*);
void lbs_int32_tostring(lbs_field_info*, lua_State*, const void*);

#define lbs_register_int32_field(L, struct_name, type, field) \
	lbs_register_field(L, struct_name, #field, &(lbs_field_info){ \
		.offset = offsetof(type, field), \
		.getter = lbs_int32_getter, \
		.setter = lbs_int32_setter, \
		.tostring = lbs_int32_tostring, \
	})


void lbs_int64_getter(lbs_field_info*, lua_State*, const void*);
void lbs_int64_setter(lbs_field_info*, lua_State*, void*);
void lbs_int64_tostring(lbs_field_info*, lua_State*, const void*);

#define lbs_register_int64_field(L, struct_name, type, field) \
	lbs_register_field(L, struct_name, #field, &(lbs_field_info){ \
		.offset = offsetof(type, field), \
		.getter = lbs_int64_getter, \
		.setter = lbs_int64_setter, \
		.tostring = lbs_int64_tostring, \
	})


void lbs_pointer_getter(lbs_field_info*, lua_State*, const void*);
void lbs_pointer_setter(lbs_field_info*, lua_State*, void*);
void lbs_pointer_tostring(lbs_field_info*, lua_State*, const void*);

#define lbs_register_pointer_field(L, struct_name, type, field) \
	lbs_register_field(L, struct_name, #field, &(lbs_field_info){ \
		.offset = offsetof(type, field), \
		.getter = lbs_pointer_getter, \
		.setter = lbs_pointer_setter, \
		.tostring = lbs_pointer_tostring, \
	})


#define lbs_register_generic_field_(L, struct_name, type, field) _Generic( (*&(type){}.field), \
	float:   lbs_register_float_field((L), (struct_name), type, field), \
	double:  lbs_register_double_field((L), (struct_name), type, field), \
	char:    lbs_register_char_field((L), (struct_name), type, field), \
	int8_t:  lbs_register_int8_field((L), (struct_name), type, field), \
	int16_t: lbs_register_int16_field((L), (struct_name), type, field), \
	int32_t: lbs_register_int32_field((L), (struct_name), type, field), \
	int64_t: lbs_register_int64_field((L), (struct_name), type, field), \
	void*:   lbs_register_pointer_field((L), (struct_name), type, field) \
)
#define lbs_register_generic_field4(L, struct_name, type, field) \
	lbs_register_generic_field_((L), (struct_name), type, field)
#define lbs_register_generic_field3(L, type, field) \
	lbs_register_generic_field_((L), #type, type, field)
#define lbs_register_generic_field(...) LBS_XPASTE(lbs_register_generic_field, LBS_NARG(__VA_ARGS__))(__VA_ARGS__)

#endif /* LBS_TYPES_H */
