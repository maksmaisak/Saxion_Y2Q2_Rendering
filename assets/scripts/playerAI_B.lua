--
-- User: maks
-- Date: 2019-01-21
-- Time: 22:54
--

require('math')

return function(o)

    o = o or {}

    local transform

    function o:start()

        transform = self.actor:get("Transform")
    end

    function o:update(dt)

        local time = Game.getTime()
        transform.position = {math.sin(time) * 5, 0, math.cos(time * 2) * 5 }
        transform.scale = {math.cos(time) ^ 2, 1, math.sin(time) ^ 2}
    end

    return o
end