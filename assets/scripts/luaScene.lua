--
-- User: maks
-- Date: 30/12/18
-- Time: 20:15
--

return {
    {
        Name = "camera",
        Transform = {
            position = { x = 0, y = 0, z = 10 }
        },
        Camera = {},
        CameraOrbitBehavior = {
            target = "left"
        }
    },
    {
        Name = "plane",
        Transform = {
            position = { x = 0, y = -4, z = 0 },
            scale = { x = 5, y = 5, z = 5 }
        },
        RenderInfo = {
            mesh = "mge/models/plane.obj",
            texture = "mge/textures/land.jpg" -- TODO add support for materials
        }
    },
    {
        Name = "left",
        Transform = {
            position = { x = 2, y = 2, z = 0 }
        },
        RenderInfo = {
            mesh = "mge/models/suzanna_flat.obj",
            texture = "mge/textures/bricks.jpg" -- TODO add support for materials
        }
    },
    {
        Name = "right",
        Transform = {
            position = { x = -2, y = 2, z = 0 }
        },
        RenderInfo = {
            mesh = "mge/models/teapot_smooth.obj",
            texture = "mge/textures/bricks.jpg" -- TODO add support for materials
        }
    }
}