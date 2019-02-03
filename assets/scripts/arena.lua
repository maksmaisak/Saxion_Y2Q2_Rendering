--
-- User: maks
-- Date: 2019-01-20
-- Time: 17:28
--

local arenaSize = 60

--Game.makeMaterial("cubeMaterial", {
--    diffuse = "textures/container/diffuse.png",
--    specular = "textures/container/specular.png",
--    shininess = 100
--})
--
--Game.makeMaterial("planeMaterial", {
--    shininess = 10
--})

local planeMaterial = {
    diffuse = "textures/terrain/diffuse4.jpg",
    shininess = 10
}

local scenery = {
    {
        Name = "Plane",
        Transform = {
            position = { 0, -1, 0 },
            scale    = { arenaSize / 2, arenaSize / 2, arenaSize / 2}
        },
        RenderInfo = {
            mesh = "models/plane.obj",
            material = planeMaterial
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

local scene = {}

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
                material = {}
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
            if ((x == -halfSideLength or x == halfSideLength) or (y == -halfSideLength or y == halfSideLength)) then
                makeBorderPiece({x, 0, y}, radius)
            end
        end
    end
end

function Game.makeBullet(position, velocity, size)

    size = size or 0.2

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

    table.insert(Game.bullets, bullet)
    if #Game.bullets >= Game.maxNumActiveBullets then
        table.remove(Game.bullets, 1):destroy()
    end

    return bullet
end

function scene.start()

    Game.bullets = {}
    Game.maxNumActiveBullets = 10

    Game.makeActors(scenery)
    makeBorders(arenaSize)

    local function makePlayer(name, position, ai, color)

        name = name or "unnamed"
        position = position or {0, 0, 0 }
        color = color or {1,1,1}

        return Game.makeActor {
            Name = name,
            Transform = {
                position = position,
                scale = {1,1,1}
            },
            RenderInfo = {
                mesh = "models/cylinder_smooth.obj",
                material = {
                    diffuseColor = color,
                    shininess = 1
                }
            },
            Rigidbody = {
                isKinematic = false,
                useGravity = false
            },
            LuaBehavior = ai
        }
    end

    player1 = makePlayer("Player1", {5, 0, -5}, "assets/scripts/playerAI_A.lua", {1, 0, 0})
    player2 = makePlayer("Player2", {-5, 0, 5}, "assets/scripts/playerAI_B.lua", {0, 0, 1})

    player1:get("LuaBehavior").enemy = player2
    player2:get("LuaBehavior").enemy = player1

    local camera = Game.makeActor {
        Name = "Camera",
        Transform = {
            position = {0, 20, 0},
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

    local timeToLoadScene = Game.getTime() + 5
    while Game.getTime() < timeToLoadScene do coroutine.yield() end

    Game.loadScene("scripts/arena.lua")
end)

function scene.update(dt)

    Game.find("PointLight"):get("Light").intensity = math.sin(Game.getTime()) ^ 2
    --Game.find("DirectionalLight"):get("Transform"):rotate(60 * dt, 1, 0, 0)

    for i, bullet in ipairs(Game.bullets) do
        if (bullet) then
            local bulletTransform = bullet:get("Transform")
            local bulletRigidbody = bullet:get("Rigidbody")
            bulletTransform.position = { bulletTransform.position.x, 0, bulletTransform.position.z }
            bulletRigidbody.velocity = { bulletRigidbody.velocity.x, 0, bulletRigidbody.velocity.z }
        end
    end

    sceneUpdateCoroutine()
end

function scene.onCollision(a, b)

    local function switchBulletColor(bullet)
        local light = bullet:get("Light")
        local color = light.color
        light.color = {color.y, color.z, color.x }
    end

    if string.find(a.name, "Bullet") ~= nil then
        switchBulletColor(a)
    end

    if string.find(b.name, "Bullet") ~= nil then
        switchBulletColor(b)
    end

    --print("scene.onCollision:", a.name, b.name)

    local bullet
    local player

    if string.find(a.name, "Player") ~= nil then
        player = a
    elseif string.find(b.name, "Player") ~= nil then
        player = b
    end

    if string.find(a.name, "Bullet") ~= nil then
        bullet = a
    elseif string.find(b.name, "Bullet") ~= nil then
        bullet = b
    end

    if (bullet and player) then
        player:destroy()
    end
end

return scene
