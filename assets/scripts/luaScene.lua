--
-- User: maks
-- Date: 30/12/18
-- Time: 20:15
--

return {
    {
        Name = "camera",
        Transform = {
            position = {
                x = 0,
                y = 0,
                z = 10
            }
        },
        Camera = {},
        CameraOrbitBehavior = {
            target = "left" -- maybe create all entities and assign names, and then add all these components.
        }
    },
    {
        Name = "left",
        Transform = {
            position = {
                x = 1,
                y = 2,
                z = 0
            }
        },
        RenderInfo = {
            mesh = "mge/models/suzanna_flat.obj",
            texture = "mge/textures/bricks.jpg" -- TODO add support for materials
        }
    },
    {
        Name = "right",
        Transform = {
            position = {
                x = -1,
                y = 2,
                z = 0
            }
        },
        RenderInfo = {
            mesh = "mge/models/teapot_smooth.obj",
            texture = "mge/textures/bricks.jpg" -- TODO add support for materials
        }
    }
}