--
-- User: maks
-- Date: 2019-01-23
-- Time: 10:51
--

require('math')
require('assets/scripts/vector')

local scene = {}

local boids = {}

local position = Vector:new()
local otherPosition = Vector:new()

local function getAcceleration(i, boid, acceleration)

    acceleration = acceleration or Vector:new()

    position:set(boid.transform.position)
    --local velocity = Vector.from(boid.rigidbody.velocity)

    for j, other in ipairs(boids) do

        if i ~= j then

            otherPosition:set(other.transform.position)
            --local otherVelocity = Vector.from(other.rigidbody.velocity)

            local delta = otherPosition - position
            local sqrDistance = delta:sqrMagnitude()
            if (sqrDistance > 0.01) then
                acceleration:add(delta:normalized() / sqrDistance);
            end

            --separation
            --local separation = Vector:new()
        end
    end

    return acceleration
end

function scene.start()

    local function makeBoid(position)

        local radius = 0.2

        local actor = Game.makeActor {
            Name = "Boid",
            Transform = {
                position = position,
                scale = {radius, radius, radius}
            },
            Rigidbody = {
                useGravity = false,
                radius = radius
            },
            RenderInfo = {
                mesh = "models/cube_flat.obj",
                material = {
                    shininess = 100
                }
            }
        }

        local boid = {
            actor = actor,
            transform = actor:get("Transform"),
            rigidbody = actor:get("Rigidbody")
        }

        table.insert(boids, boid)

        return boid
    end

    local pi2 = math.pi * 2.0
    for radius = 1,5,1 do
        for theta = 0.0,pi2,pi2/6.0 do

            local position = {
                x = math.cos(theta) * radius,
                y = 0,
                z = math.sin(theta) * radius
            }

            makeBoid(position)
        end
    end

    Game.makeActor {
        Name = "Camera",
        Transform = {
            position = {0, 20, 0},
            rotation = {-90, 0, 0}
        },
        Camera = {}
    }

    Game.makeActor {
        Name = "DirectionalLight",
        Light = {
            intensity = 0.1,
            color = {0, 0, 1},
            colorAmbient = {1, 1, 1},
            kind = "DIRECTIONAL"
        },
        Transform = {
            rotation = { -20, 0, 0},
        }
    }

    Game.makeActor {
        Name = "PointLight",
        Light = {
            intensity = 2
        },
        Transform = {
            position = {0, 2, 0}
        }
    }
end

function scene.update(dt)

    for i, boid in ipairs(boids) do

        local acceleration = getAcceleration(i, boid)

        local rb = boid.rigidbody
        local newVelocity = Vector.from(rb.velocity) + acceleration * dt
        --print("setting:", newVelocity)
        rb.velocity = newVelocity
        --print("set: ", rb.velocity.x, rb.velocity.y, rb.velocity.z)
    end
end

return scene