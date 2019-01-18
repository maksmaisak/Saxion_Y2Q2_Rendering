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
            mesh = "models/plane.obj",
            texture = "textures/land.jpg" -- TODO add support for materials
        },
    },
    {
        Name = "head",
        Transform = {
            position = { x = 0, y = 2, z = 0 }
        },
        RenderInfo = {
            mesh = "models/suzanna_flat.obj",
            texture = "textures/bricks.jpg" -- TODO add support for materials
        },
        Scripts = { "mover" }
    },
    {
        Name = "teapot",
        Transform = {
            position = { x = 0, y = 4, z = 0 }
        },
        RenderInfo = {
            mesh = "models/teapot_smooth.obj",
            texture = "textures/bricks.jpg" -- TODO add support for materials
        }
    }
}

function scene.update(dt)

    print(Game.testValue)
    print(Game.testFreeFunction())
    print(Game.testMemberFunction())

    local head = Game.findByName("head")
    if (head) then
        print(head:isValid())
        print(head:getName())
        print(head:getTransform())
        print(head:getComponent("Transform"))
        print(head:getComponent("RenderInfo"))
        print(head:getComponent("Rigidbody"))
        head:getTransform():move(0, dt, 0)
        head:getTransform():rotate(10 * dt, 0, 1, 0)
    end

    local actor = Game.makeActor("name")
    print(actor:getComponent("Transform"))
    actor:addComponent("Transform")
    print(actor:getComponent("Transform"))
    print(actor:getComponent("Transform") == actor:getComponent("Transform"))
end

return scene