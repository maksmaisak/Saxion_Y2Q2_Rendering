--
-- User: maks
-- Date: 2019-01-20
-- Time: 17:28
--

local arenaSize = Config.arenaSize or 40

local scenery = {
    {
        Name = "Plane",
        Transform = {
            position = { 0, -1, 0 },
            scale    = { arenaSize / 2, arenaSize / 2, arenaSize / 2}
        },
        RenderInfo = {
            mesh = "models/plane.obj",
            material = {
                diffuse = "textures/terrain/diffuse4.jpg",
                shininess = 10
            }
        }
    },
    {
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
    },
    {
        Name = "PointLight",
        Light = {
            intensity = 4,
        },
        Transform = {
            position = { x = 0, y = 2, z = 0 },
            scale    = { 0.1, 0.1, 0.1 }
        },
        RenderInfo = {
            mesh = "models/sphere2.obj",
            material = {
                shininess = 100
            }
        }
    }
}

local player1
local player2
local cameraTransform

local borderMaterial = Game.makeMaterial {
    shininess = 200
}

local function makeBorders(sideLength)

    sideLength = sideLength or 20
    local halfSideLength = sideLength / 2

    local function makeBorderPiece(position, radius)
        return Game.makeActor {
            Name = "BorderPiece",
            Transform = {
                position = position,
                scale = {radius, radius, radius}
            },
            RenderInfo = {
                mesh = "models/sphere2.obj",
                material = borderMaterial
            },
            Rigidbody = {
                isKinematic = true,
                useGravity = false,
                radius = radius
            }
        }
    end

    local radius = 4
    local step = radius * 1

    for x = -halfSideLength,halfSideLength,step do
        for y = -halfSideLength,halfSideLength,step do
            if x == -halfSideLength or x == halfSideLength or y == -halfSideLength or y == halfSideLength then
                makeBorderPiece({x, 0, y}, radius)
            end
        end
    end
end

local bulletMaterial = Game.makeMaterial {
    shininess = 256,
    diffuseColor = {0, 0, 0}
}

function Game.makeBullet(position, direction, size)

    size = size or 0.2
    local velocity = Vector.from(direction):setMagnitude(Config.bulletSpeed or 1)

    local bullet = Game.makeActor {
        Name = "Bullet",
        Transform = {
            position = position or {0, 0, 0},
            scale = {size, size, size}
        },
        Rigidbody = {
            isKinematic = false,
            useGravity = false,
            velocity = velocity or {0, 0, 0},
            radius = size
        },
        RenderInfo = {
            mesh = "models/sphere2.obj",
            material = bulletMaterial
        },
        Light = {
            intensity = 1,
            color = {1, 0, 0}
        },
        LuaBehavior = {
            update = function(self, dt)
                local tf = self.actor:get("Transform")
                local rb = self.actor:get("Rigidbody")
                if not tf or not rb then
                    print(self.actor.name..": isDestroyed: "..tostring(self.actor.isDestroyed)..", isValid: "..tostring(self.actor.isValid))
                end
                tf.position = { tf.position.x, 0, tf.position.z }
                rb.velocity = { rb.velocity.x, 0, rb.velocity.z }
            end,
            onCollision = function(self, collidee)

                local light = self.actor:get("Light")
                if light then
                    local color = light.color
                    light.color = {color.y, color.z, color.x}
                end

                if string.find(collidee.name, "Player") ~= nil then
                    collidee:destroy()
                end
            end
        }
    }

    table.insert(Game.bullets, bullet)
    if #Game.bullets >= Config.maxNumActiveBullets then
        table.remove(Game.bullets, 1):destroy()
    end

    return bullet
end

local scene = {}

function scene.start()

    Game.bullets = {}

    Game.makeActors(scenery)
    makeBorders(arenaSize)

    local function makePlayer(name, position, config)

        name     = name or "unnamed"
        position = position or {0, 0, 0 }
        config = config or {}
        config.color = config.color or {1,1,1}
        config.ai    = config.ai or {}

        return Game.makeActor {
            Name = name,
            Transform = {
                position = position,
                scale = {1,1,1}
            },
            RenderInfo = {
                mesh = "models/cylinder_smooth.obj",
                material = {
                    diffuseColor = config.color,
                    shininess = 1
                }
            },
            Rigidbody = {
                isKinematic = false,
                useGravity = false
            },
            LuaBehavior = config.ai
        }
    end

    player1 = makePlayer("Player1", {-10, 0, 10}, Config.players[1])
    player2 = makePlayer("Player2", {10, 0, -10}, Config.players[2])

    player1:get("LuaBehavior").enemy = player2
    player2:get("LuaBehavior").enemy = player1

    local camera = Game.makeActor {
        Name = "Camera",
        Transform = {
            position = {0, 40, 0},
            rotation = {-90, 0, 0}
        },
        Camera = {},
        LuaBehavior = require("assets/scripts/camera") {
            targets = {player1, player2}
        }
    }
    cameraTransform = camera:get("Transform")
end

local sceneUpdateCoroutine = coroutine.wrap(function()

    while not player1.isDestroyed and not player2.isDestroyed do
        coroutine.yield()
    end

    local timeToLoadScene = Game.getTime() + Config.levelRestartDelay or 0
    while Game.getTime() < timeToLoadScene do coroutine.yield() end

    Game.loadScene("assets/scripts/arena.lua")
end)

function scene.update(dt)

    Game.find("PointLight"):get("Light").intensity = math.sin(Game.getTime()) ^ 2
    --Game.find("DirectionalLight"):get("Transform"):rotate(60 * dt, 1, 0, 0)

    sceneUpdateCoroutine()
end

return scene
