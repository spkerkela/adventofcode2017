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
    position = position + jump_offsets[i]
    jump_offsets[i] = jump_offsets[i] + 1
    steps = steps + 1
end

print(steps)
