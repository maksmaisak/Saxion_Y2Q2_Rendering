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
            position = { x = 0, y = 0, z = 0 },
            scale    = { x = 5, y = 5, z = 5 }
        },
        RenderInfo = {
            mesh = "models/plane.obj",
            material = {
                diffuse = "textures/land.jpg",
                shininess = 10
            }
        },
    },
    {
        Name = "cube",
        Transform = {
            position = { x = 0, y = 2, z = 0 },
            scale    = { x = 1, y = 1, z = 1 }
        },
        RenderInfo = {
            mesh = "models/cube_flat.obj",
            material = {
                diffuse = "textures/container/diffuse.png",
                specular = "textures/container/specular.png",
                shininess = 100
            }
        },
    },
    {
        Name = "head",
        Transform = {
            position = { x = 0, y = 5, z = 0 }
        },
        RenderInfo = {
            mesh = "models/suzanna_flat.obj",
            material = {
                diffuse = "textures/bricks.jpg",
                shininess = 100
            }
        },
        Scripts = { "mover" }
    },
    {
        Name = "teapot",
        Transform = {
            position = { x = 0, y = 7, z = 0 }
        },
        RenderInfo = {
            mesh = "models/teapot_smooth.obj",
            material = {
                diffuse = "textures/bricks.jpg"
            }
        }
    }
}

local didStart = false

local function start()

    local actor = Game.makeActor("Light")
    actor:add("Transform"):move(-5, 3, 0)
    actor:add("Light")

    local actor2 = Game.makeActor("Light")
    actor2:add("Transform"):move(5, 3, 0)
    actor2:add("Light")
end

function scene.update(dt)

    if (not didStart) then
        start()
        didStart = true
    end

    print(Game.testValue)
    print(Game.testFreeFunction())
    print(Game.testMemberFunction())

    local head = Game.find("head")
    if (head) then
        print(head.isValid)
        print(head.name)
        print(head:getTransform())
        print(head:get("Transform"))
        print(head:get("RenderInfo"))
        print(head:get("Rigidbody"))
        --head:getTransform():move(0, dt, 0)
        --head:getTransform():rotate(10 * dt, 0, 1, 0)
    end

    local actor = Game.makeActor("name")
    print(actor:get("Transform"))
    actor:add("Transform")
    print(actor:get("Transform"))
    print(actor:get("Transform") == actor:get("Transform"))
end

return scene