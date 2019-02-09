--
-- User: maks
-- Date: 30/12/18
-- Time: 20:15
--

local scenery = {
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
            position = { x = 0 , y = 0 , z = 0 },
            scale    = { x = 10, y = 10, z = 10 }
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

local scene = {}

function scene.start()

    Game.makeActors(scenery)

    local actor = Game.makeActor {
        Name = "Light",
        Transform = {
            scale = {0.1, 0.1, 0.1}
        },
        RenderInfo = {
            mesh = "models/sphere2.obj",
            material = {}
        },
        Light = {
            intensity = 5
        }
    }

    local actor2 = Game.makeActor {
        Name = "Light2",
        Transform = {
            position = {3, 3, 0},
            scale = {0.1, 0.1, 0.1}
        },
        RenderInfo = {
            mesh = "models/sphere2.obj",
            material = {}
        },
--        Light = {
--			intensity = 5
--		}
    }

    local actor2 = Game.makeActor {
        Name = "LightDirectional",
        Transform = {
            scale = {0.1, 0.1, 0.1},
            rotation = {-45, 0, 0}
        },
        Light = {
            kind = "directional",
            intensity = 0.1
        }
    }
end

function scene.update(dt)

    Game.find("Light"):get("Transform").position = {-4, 3 + math.sin(Game.getTime()), 0}
    --Game.find("LightDirectional"):get("Transform"):rotate(45 * dt, 1, 0, 0);
end

return scene