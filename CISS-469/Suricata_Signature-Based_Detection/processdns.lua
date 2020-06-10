--Joshua Stuifbergen and Niko Fricker
--2/16/2020
--CISS469

--Gets the payload from the file
function init (args)
    local needs = {}
    needs["payload"] = tostring(true)
    return needs
end

--This function will remove all symbols that are not A-Z and a-z
--and dashes and form a new string. After the string is returned and process
--through the entropy fuctionl. It will then calculat the max entropy of the 
--string. A zero or one will be returned if the value meets the threshold.
function match (args)
    local dns = args["payload"]
    tempDNS = ""
    if dns == nil then
        return 0
    end
    for i = 1, string.len(dns), 1 do
        if string.match(string.sub(dns, i, i), "%a") then
            tempDNS = (tempDNS .. string.sub(dns, i, i))
        end
        if (string.sub(dns, i, i) == "-") then
            tempDNS = (tempDNS .. string.sub(dns, i, i))
        end
    end
    print(tempDNS)
    sum = entropy(tempDNS)
    maxEnt = math.log(tempDNS:len(), 2)
    --print("maxENt", maxEnt)
    --print("sum", sum)
    if (sum > 3) then
        p = (sum/maxEnt)
        if (p > 0.85) then
            return 1

        else
            return 0
            
        end
    end
end

--These two functions below calculate the entropy of the dns string
--and the sum to the match function
function log2 (x) return math.log(x) / math.log(2) end

function entropy (tempDNS)
    local N, count, sum, i = tempDNS:len(), {}, 0
    for char = 1, N do
        i = tempDNS:sub(char, char)
        if count[i] then
            count[i] = count[i] + 1
        else
            count[i] = 1
        end
    end
    for n_i, count_i in pairs(count) do
        sum = sum + count_i / N * log2(count_i / N)
    end    
    return -sum
end

--Sources:
--Shannon's Entropy
--https://rosettacode.org/wiki/Entropy#Lua
