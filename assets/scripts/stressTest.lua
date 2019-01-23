--
-- User: maks
-- Date: 2019-01-23
-- Time: 10:51
--

require('math')

local scene = {}

local boids = {}

function scene.start()

    local function makeBoid(position)

        local radius = 0.2

        local boid = Game.makeActor {
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

        table.insert(boids, boid)

        return boid
    end

    local pi2 = math.pi * 2.0
    for radius = 0,5,1 do
        for theta = 0.0,pi2,pi2/5.0 do

            local position = {
                x = math.cos(theta) * radius,
                y = 0,
                z = math.sin(theta) * radius
            }

            makeBoid(position)
        end
    end

    Game.makeActor({
        Name = "Camera",
        Transform = {
            position = {0, 20, 0},
        },
        Camera = {}
    }):get("Transform"):rotate(-90, 1, 0, 0)

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

        local tf = boid:get("Transform")

        local acceleration = {x = 0, y = 0, z = 0}

        for j, other in ipairs(boids) do

            if i ~= j then

                local otherTf = other:get("Transform")

                local position = tf.position
                local otherPosition = otherTf.position
                local delta = {
                    x = otherPosition.x - position.x,
                    y = otherPosition.y - position.y,
                    z = otherPosition.z - position.z
                }
                local distanceSqr = delta.x ^ 2 + delta.y ^ 2 + delta.z ^ 2
                if distanceSqr > 0.01 then
                    local distance = math.sqrt(distanceSqr)
                    local direction = {
                        x = delta.x / distance,
                        y = delta.y / distance,
                        z = delta.z / distance
                    }
                    acceleration.x = acceleration.x + direction.x * 4 / distanceSqr
                    acceleration.y = acceleration.y + direction.y * 4 / distanceSqr
                    acceleration.z = acceleration.z + direction.z * 4 / distanceSqr
                end
            end
        end

        local rb = boid:get("Rigidbody")
        local oldVelocity = rb.velocity
        rb.velocity  = {
            x = oldVelocity.x + acceleration.x * dt,
            y = oldVelocity.y + acceleration.y * dt,
            z = oldVelocity.z + acceleration.z * dt
        }
        --print(rb.velocity.x, rb.velocity.y, rb.velocity.z)
    end
end

return scene