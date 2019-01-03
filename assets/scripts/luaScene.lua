--
-- User: maks
-- Date: 30/12/18
-- Time: 20:15
--

local scene = {
    {
        Name = "camera",
        Transform = {
            position = { x = 0, y = 0, z = 10 }
        },
        Camera = {},
        CameraOrbitBehavior = {
            target   = "head",
            distance =  10,
            minTilt  = -15,
            maxTilt  =  60,
        }
    },
    {
        Name = "plane",
        Transform = {
            position = { x = 0, y = -4, z = 0 },
            scale    = { x = 5, y =  5, z = 5 }
        },
        RenderInfo = {
            mesh = "mge/models/plane.obj",
            texture = "mge/textures/land.jpg" -- TODO add support for materials
        },
    },
    {
        Name = "head",
        Transform = {
            position = { x = 0, y = 2, z = 0 }
        },
        RenderInfo = {
            mesh = "mge/models/suzanna_flat.obj",
            texture = "mge/textures/bricks.jpg" -- TODO add support for materials
        },
        Scripts = { "mover" }
    },
    {
        Name = "teapot",
        Transform = {
            position = { x = 0, y = 4, z = 0 }
        },
        RenderInfo = {
            mesh = "mge/models/teapot_smooth.obj",
            texture = "mge/textures/bricks.jpg" -- TODO add support for materials
        }
    }
}

function scene.update(dt)

    print(Game.testFreeFunction())
    Game.testMemberFunction()

--    local floor = Game.find("Floor")
--    if (floor) then
--        floor.getComponent("Transform").move(0, dt, 0)
--    end
end

return scene