--
-- User: maks
-- Date: 30/12/18
-- Time: 20:15
--

return {
--    {
--        Camera = {},
--        Transform = {
--            position = {
--                x = 0,
--                y = 0,
--                z = 10
--            }
--        }
--    },
    {
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