--
-- User: maks
-- Date: 2019-01-20
-- Time: 17:28
--

local scene = {
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
        Name = "cube",
        Transform = {
            position = { 0, 2, 0 },
            scale    = { 1, 1, 1 }
        },
        RenderInfo = {
            mesh = "models/cube_flat.obj",
            material = {
                diffuse = "textures/container/diffuse.png",
                specular = "textures/container/specular.png",
                shininess = 100
            }
        }
    },
    {
        Name = "Light",
        Light = {
            intensity = 1,
            colorAmbient = {0.02, 0.02, 0.04}
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

local didStart = false
local cube

local function start()

    local camera = Game.makeActor("Camera")
    camera:addComponent("Transform")
        :move(0, 20, 0)
        :rotate(-90, 1, 0, 0)
    camera:addComponent("Camera")

    cube = Game.findByName("cube")
end

function scene.update(dt)

    if (not didStart) then
        start()
        didStart = true
    end

    cube:getComponent("Transform"):move(0, 0, -dt)
end

return scene

