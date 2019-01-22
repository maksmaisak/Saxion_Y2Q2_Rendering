--
-- User: maks
-- Date: 2019-01-20
-- Time: 17:28
--

local CubeMaterial = {
    diffuse = "textures/container/diffuse.png",
    specular = "textures/container/specular.png",
    shininess = 100
}

local actors = {
    {
        Name = "plane",
        Transform = {
            position = { 0, 0, 0 },
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
        Name = "player1",
        Transform = {
            position = { -5, 1, 5 },
            scale    = { 1, 1, 1 }
        },
        RenderInfo = {
            mesh = "models/cube_flat.obj",
            material = CubeMaterial
        }
    },
    {
        Name = "player2",
        Transform = {
            position = { 5, 1, -5 },
            scale    = { 0.1, 1, 1 }
        },
        RenderInfo = {
            mesh = "models/cube_flat.obj",
            material = CubeMaterial
        }
    },
    {
        Name = "DirectionalLight",
        Transform = {},
        Light = {
            kind = "directional",
            colorAmbient = {0.02, 0.02, 0.04}
        }
    },
    {
        Name = "Light",
        Light = {
            intensity = 1,
        },
        Transform = {
            position = { x = 0, y = 2, z = 2 },
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

function scene.start()

    Game.makeActors(actors)

    Game.makeActor {
        Name = "Light2",
        Light = {
            intensity = 0.1,
            color = {0, 0, 1},
            kind = "DIRECTIONAL"
        },
        Transform = {
            position = { 2, 2, 0},
            rotation = { -20, 0, 0},
            scale    = { 0.1, 0.1, 0.1 }
        },
        RenderInfo = {
            mesh = "models/sphere2.obj",
            material = {
                shininess = 100
            }
        }
    }

    local camera = Game.makeActor("Camera")
    cameraTransform = camera:addComponent("Transform")
        :move(0, 20, 0)
        :rotate(-90, 1, 0, 0)
    camera:addComponent("Camera")

    local player1Actor = Game.findByName("player1")
    local player2Actor = Game.findByName("player2")

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

    player1:update(dt)
    player2:update(dt)

    local position1 = player1.actor:getComponent("Transform").position
    local position2 = player2.actor:getComponent("Transform").position
    cameraTransform.position = {
        (position1.x + position2.x) * 0.5,
        cameraTransform.position.y,
        (position1.z + position2.z) * 0.5
    }
end

return scene

