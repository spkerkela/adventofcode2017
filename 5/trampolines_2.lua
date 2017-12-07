filename = arg[1]
if not filename then return end
f = io.open(filename, "rb")
if f then f:close() else return end

jump_offsets = {}
position = 1
steps = 0

for line in io.lines(filename) do
    table.insert(jump_offsets, tonumber(line))
end

while position <= #jump_offsets and position > 0 do
    local i = position
    local offset = jump_offsets[i]
    local value_mod = offset >= 3 and -1 or 1
    position = position + jump_offsets[i]
    jump_offsets[i] = jump_offsets[i] + value_mod
    steps = steps + 1
end

print(steps)
