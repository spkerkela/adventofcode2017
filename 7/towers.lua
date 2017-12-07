filename = arg[1]
if not filename then return end
f = io.open(filename, "rb")
if f then f:close() else return end

programs = {}
children = {}

for line in io.lines(filename) do
    local line_tokens = {}
    local program = {}
    for str in string.gmatch(line, "%S+") do 
        table.insert(line_tokens, str)
    end
    program['name'] = line_tokens[1]
    _num = string.gsub(line_tokens[2], "%(", "")
    num = string.gsub(_num, "%)", "")
    program['weight'] = tonumber(num)
    program['children'] = {}

    if #line_tokens > 3 then
        for i=4, #line_tokens do
            child = string.gsub(line_tokens[i], ",", "")
            table.insert(program['children'], child)
            children[child] = true
        end
    end
    programs[line_tokens[1]] = program
end

root = ''
for key, value in pairs(programs) do
    if not children[key] then
        root = key
    end
end

function check_weights(prg)
    local kids = prg['children']
    local my_weight = prg['weight']
    local weights = {}
    if kids then 
        for key, kid in pairs(kids) do
            local weight, kid_ob = check_weights(programs[kid])
            table.insert(weights, {weight, kid_ob})
        end
    end
    local end_weight = my_weight
    local all_same = true
    all_same = true
    for _, v in pairs(weights) do
        if v[1] ~= weights[1][1] then
            all_same=false
        end 
        end_weight = end_weight + v[1]
    end
    if not all_same then
        print(prg['name'])
        print(my_weight)
        for _, vl in pairs(weights) do
            print('\t', vl[2]['name'], vl[1], vl[2]['weight'])
        end
        print('--')
    end
    return end_weight, prg
end

print(check_weights(programs[root]))