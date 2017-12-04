filename = arg[1]
if not filename then return end
f = io.open(filename, "rb")
if f then f:close() else return end

valid_lines = 0

for line in io.lines(filename) do
    local words = {}
    duplicates = false
    for word in string.gmatch(line, "%S+") do
        if not words[word] then
            words[word] = true
        else 
            duplicates = true
        end
    end
    if not duplicates then
        valid_lines = valid_lines + 1
    end
end

print(valid_lines)