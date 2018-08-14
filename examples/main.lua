local mylualib = require "mylualib"

local foo = mylualib.new_vec3()

-- Should get pretty contents of our struct
print(foo)

-- Getters
assert(foo.x == 1)
assert(foo.y == 2)
assert(foo.z == 3)

-- This will fail with a type error:
assert(not pcall(function()
	foo.x = "invalid"
end), "should have thrown")

foo.y = 42
assert(foo.y == 42)


local demo = mylualib.new_demo()
print(demo)
