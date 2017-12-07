filename = arg[1]
if not filename then return end
f = io.open(filename, "rb")
if f then f:close() else return end

memory_banks = {}

for line in io.lines(filename) do
    for str in string.gmatch(line, "%S+") do 
        table.insert(memory_banks, tonumber(str))
    end
end

function get_iterations(memory_banks, start_from)
    local st = ""
    for _, v in pairs(memory_banks) do
        st = st .. v .. " "
    end
    local seen_states = {}
    if start_from then
        seen_states[st] = true
    end
    local iterations = 0
    local keep_looping = true
    while keep_looping do
        local highest = memory_banks[1]
        local highest_i = 1

        for i=2, #memory_banks do
            if highest < memory_banks[i] then
                highest = memory_banks[i]
                highest_i = i
            end
        end

        local blocks_to_redistribute = highest
        memory_banks[highest_i] = 0
        local j = highest_i + 1
        for i=1, blocks_to_redistribute do
            if j > #memory_banks then
                j = 1
            end
            memory_banks[j] = memory_banks[j] + 1
            j = j + 1 
        end
        local key = ""
        for _,v in pairs(memory_banks) do
            key = key .. v .. " "
        end

        keep_looping = not seen_states[key]
        iterations = iterations + 1
        seen_states[key] = true
    end
    return iterations, memory_banks
end

_, new_memory_banks = get_iterations(memory_banks)

print(get_iterations(new_memory_banks, true))