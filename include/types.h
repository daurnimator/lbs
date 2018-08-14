#ifndef LBS_TYPES_H
#define LBS_TYPES_H

#include <stddef.h>	/* offsetof() */

#include "lbs.h"


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

#endif /* LBS_TYPES_H */
