--
-- User: maks
-- Date: 2019-01-20
-- Time: 17:28
--

local cubeMaterial = {
    diffuse = "textures/container/diffuse.png",
    specular = "textures/container/specular.png",
    shininess = 100
}

local scenery = {
    {
        Name = "Plane",
        Transform = {
            position = { 0, -1, 0 },
            scale    = { 10, 10, 10 }
        },
        RenderInfo = {
            mesh = "models/plane.obj",
            material = {
                shininess = 10
            }
        },
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
        },
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

local makePlayerAI_A = require("./assets/scripts/playerAI_A")
local makePlayerAI_B = require("./assets/scripts/playerAI_B")

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

    local radius = 1
    local step = radius * 1

    for x = -halfSideLength,halfSideLength,step do
        for y = -halfSideLength,halfSideLength,step do
            if ((x == -halfSideLength or x == halfSideLength) or (y == -halfSideLength or y == halfSideLength)) then
                makeBorderPiece({x, 0, y}, radius)
            end
        end
    end
end

function scene.start()

    Game.makeActors(scenery)
    makeBorders(20)

    local function makePlayer(name, position)

        name = name or "unnamed"
        position = position or {0,0,0}

        return Game.makeActor {
            Name = name,
            Transform = {
                position = position,
                scale = {1,1,1}
            },
            RenderInfo = {
                mesh = "models/cube_flat.obj",
                material = cubeMaterial
            },
            Rigidbody = {
                isKinematic = true,
                useGravity = false
            }
        }
    end

    local player1Actor = makePlayer("Player1", {5, 0, -5})
    local player2Actor = makePlayer("Player2", {-5, 0, 5})

    local camera = Game.makeActor {
        Name = "Camera",
        Transform = {
            position = {0, 20, 0},
            rotation = {-90, 0, 0}
        },
        Camera = {}
    }
    cameraTransform = camera:get("Transform")

    player1 = makePlayerAI_A {
        actor = player1Actor,
        enemy = player2Actor
    }

    player2 = makePlayerAI_B {
        actor = player2Actor,
        enemy = player1Actor
    }

    player1:start()
    player2:start()
end

function scene.update(dt)

    Game.find("PointLight"):get("Light").intensity = math.sin(Game.getTime()) ^ 2
    --Game.find("DirectionalLight"):get("Transform"):rotate(60 * dt, 1, 0, 0)

    if (player1.actor.isValid) then player1:update(dt) end
    if (player2.actor.isValid) then player2:update(dt) end

    local position1 = player1.actor.isValid and player1.actor:get("Transform").position or {x = 0, y = 0, z = 0}
    local position2 = player2.actor.isValid and player2.actor:get("Transform").position or {x = 0, y = 0, z = 0}
    cameraTransform.position = {
        (position1.x + position2.x) * 0.5,
        cameraTransform.position.y,
        (position1.z + position2.z) * 0.5
    }

    if (not player1.actor.isValid or not player2.actor.isValid) then
        Game.loadScene("scripts/arena.lua")
    end
end

function scene.onCollision(a, b)

    print("scene.onCollision:", a.name, b.name)

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

    if (not bullet) then return end

    local light = bullet:get("Light")
    local color = light.color
    light.color = {color.y, color.z, color.x }

    if (not player) then return end

    player:destroy()
end

return scene
