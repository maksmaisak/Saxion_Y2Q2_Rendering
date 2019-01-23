--
-- User: maks
-- Date: 2019-01-21
-- Time: 15:36
--

require("./assets/scripts/object")
require("math")

AI = Object:new {
    maxNumActiveBullets = 5
}

function AI:start()

    self.transform = self.actor:get("Transform")
    self.enemyTransform = self.enemy:get("Transform")
    self.bullets = {}

    self.shootIfReady = coroutine.wrap(function()

        while true do

            self:shoot(self.enemyTransform.position, 20)

            local timeToShoot = Game.getTime() + 2
            while Game.getTime() < timeToShoot do
                coroutine.yield()
            end

            if #self.bullets >= self.maxNumActiveBullets then

                local bullet = table.remove(self.bullets, 1)
                bullet:destroy()
            end
        end
    end)
end

function AI:shoot(targetPosition, speed)

    speed = speed or 10
    local startPosition = self.transform.position

    local delta = {
        x = targetPosition.x - startPosition.x,
        y = targetPosition.y - startPosition.y,
        z = targetPosition.z - startPosition.z
    }
    local function length(v) return math.sqrt(v.x * v.x + v.y * v.y + v.z * v.z); end
    local distance = length(delta)
    if (distance == 0) then distance = 1 end
    local direction = {
        x = delta.x / distance,
        y = delta.y / distance,
        z = delta.z / distance
    }

    local velocity = {
        x = direction.x * speed,
        y = direction.y * speed,
        z = direction.z * speed,
    }

    print("velocity: ", velocity.x, velocity.y, velocity.z)

    local size = 0.2

    local bullet = Game.makeActor {
        Name = "Bullet",
        Transform = {
            position = startPosition,
            scale = {size, size, size}
        },
        Rigidbody = {
            isKinematic = false,
            useGravity = false,
            velocity = velocity,
            radius = size
        },
        RenderInfo = {
            mesh = "models/sphere2.obj",
            material = {
                shininess = 256,
                diffuseColor = {1, 0, 0},
                specularColor = {1, 0, 0}
            }
        },
        Light = {
            intensity = 1,
            color = {1, 0, 0}
        }
    }

    table.insert(self.bullets, bullet)

    return bullet
end

function AI:update(dt)

    local time = Game.getTime()
    self.transform.position = {math.cos(time) * 5, self.transform.position.y, math.sin(time * 2) * 5 }

    self.shootIfReady()

    for i, bullet in ipairs(self.bullets) do
        if (bullet) then
            local bulletTransform = bullet:get("Transform")
            local bulletRigidbody = bullet:get("Rigidbody")
            bulletTransform.position = { bulletTransform.position.x, 0, bulletTransform.position.z }
            bulletRigidbody.velocity = { bulletRigidbody.velocity.x, 0, bulletRigidbody.velocity.z }
        end
    end
    --print("bullet position: ", bulletPos.x, bulletPos.y, bulletPos.z)
end

return function(o)
    return AI:new(o)
end