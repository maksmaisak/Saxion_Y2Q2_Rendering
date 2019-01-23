--
-- User: maks
-- Date: 2019-01-23
-- Time: 12:18
--

return function(actor)

    local o = {}

    local transform

    function o:start()

        transform = actor.get("Transform");
    end

    function o:update(dt)

        transform:move(dt);
    end

    return
end

