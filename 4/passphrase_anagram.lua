filename = arg[1]
if not filename then return end
f = io.open(filename, "rb")
if f then f:close() else return end

valid_lines = 0

function sort(st)
    local chars = {}
    for i = 1, #st do
        local c = st:sub(i,i)
        table.insert(chars, c)
    end
    local sorted = table.sort(chars)
    local res = chars[1]
    for i=2, #chars do
        res = res .. chars[i]
    end
    return res
end

for line in io.lines(filename) do
    local words = {}
    duplicates = false
    for word in string.gmatch(line, "%S+") do
        sorted = sort(word)
        print(word)
        print(sorted)
        print("--")
        if not words[sorted] then
            words[sorted] = true
        else 
            duplicates = true
        end
    end
    if not duplicates then
        valid_lines = valid_lines + 1
    end
end

print(valid_lines)