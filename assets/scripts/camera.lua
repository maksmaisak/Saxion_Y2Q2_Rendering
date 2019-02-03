--
-- User: maks
-- Date: 2019-02-03
-- Time: 01:16
--

require('assets/scripts/steering')

return function(o)

    o = o or {}
    o.targets = o.targets or {}

    local transform
    local steering = Steering:new()

    function o:start()

        transform = self.actor:get("Transform")
    end

    function o:update(dt)

        steering.position:set(transform.position)

        local numTargets = 0
        local targetPosition = Vector:new()
        for i, target in ipairs(self.targets) do
            if (not target.isDestroyed) then
                targetPosition:add(target:get("Transform").position)
                numTargets = numTargets + 1
            end
        end

        if (numTargets > 0) then
            targetPosition:div(numTargets)
            targetPosition.y = steering.position.y
            steering:arrive(targetPosition)
        else
            steering:brake()
        end

        steering:update(dt)
        transform.position = steering.position
    end

    return o
end

