--
-- User: maks
-- Date: 2019-01-29
-- Time: 18:25
--

require('assets/scripts/vector')

local scene = {}

local tf

function scene.start()

    local camera = Game.makeActor("Camera")
    camera:add("Camera")
    camera:add("Transform")
--
--    local cube = Game.makeActor {
--        Name = "Cube",
--        Transform = {
--            position = {0, 0, -10}
--        },
--        RenderInfo = {
--            mesh = "models/cube_flat.obj",
--            material = {
--                shininess = 100
--            }
--        }
--    }
--
--    Game.makeActor {
--        Name = "Light",
--        Transform = {
--            rotation = {45, 45, 0}
--        },
--        Light = {
--            kind = "DIRECTIONAL"
--        }
--    }
--
--    local get = cube.get
--    tf = get(cube, "Transform")
--    local position = tf.position
--    local x = position.x
--    print("get:", get)
--    print("tf:", tf)
--    print("position:", position)
--    print("x:", x)
end

function scene.update(dt)
    --tf.position = Vector.from {0, dt, 0} + tf.position
end

return scene

