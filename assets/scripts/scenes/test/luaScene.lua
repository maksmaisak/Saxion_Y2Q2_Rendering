--
-- User: maks
-- Date: 30/12/18
-- Time: 20:15
--

local planeRenderInfo = {
    mesh = "models/plane.obj",
    material = Game.makeMaterial {
        shader = "pbr",
        albedo             = "textures/testPBR/oldTiledStone/tiledstone1_basecolor.png",
        metallicSmoothness = "textures/testPBR/oldTiledStone/tiledstone1_metallicSmoothness.psd",
        normal             = "textures/testPBR/oldTiledStone/tiledstone1_normal.png",
        ao                 = "textures/testPBR/oldTiledStone/tiledstone1_AO.png",
    }
}

local defaultMaterial = Game.makeMaterial {shader = "pbr"}

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
            minTilt  = -60,
            maxTilt  =  60,
        }
    },
    {
        Name = "plane",
        Transform = {
            position = { x = 0 , y = 0 , z = 0 },
            scale    = { x = 10, y = 10, z = 10 }
        },
        RenderInfo = planeRenderInfo
    },
    {
        Name = "wallXP",
        Transform = {
            position = { 10, 10, 0 },
            scale    = { 10, 10, 10 },
            rotation = { 0, 0, 90}
        },
        RenderInfo = planeRenderInfo
    },
    {
        Name = "wallXN",
        Transform = {
            position = { -10, 10, 0 },
            scale    = { 10, 10, 10 },
            rotation = { 0, 0, -90}
        },
        RenderInfo = planeRenderInfo
    },
    {
        Name = "wallZP",
        Transform = {
            position = { 0, 10, 10 },
            scale    = { 10, 10, 10 },
            rotation = { -90, 0, 0 }
        },
        RenderInfo = planeRenderInfo
    },
    {
        Name = "wallZN",
        Transform = {
            position = { 0, 10, -10 },
            scale    = { 10, 10, 10 },
            rotation = { 90, 0, 0 }
        },
        RenderInfo = planeRenderInfo
    },
    {
        Name = "ceiling",
        Transform = {
            position = { 0, 20, 0 },
            scale    = { 10, 10, 10 },
            rotation = { 180, 0, 0 }
        },
        RenderInfo = planeRenderInfo
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
                shader = "pbr",
                albedo = "textures/container/diffuse.png",
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
                shader = "pbr",
                albedo = "textures/bricks.jpg"
            }
        }
    },
    {
        Name = "teapot",
        Transform = {
            position = { x = 0, y = 7, z = 0 }
        },
        RenderInfo = {
            mesh = "models/teapot_smooth.obj",
            material = {
                shader = "pbr",
                albedo = "textures/bricks.jpg",
                metallicMultiplier   = 0.1,
                smoothnessMultiplier = 0.05,
            }
        }
    }
}

local scene = {}

function scene:start()

    Game.makeActors(scenery)

    Game.makeActor {
        Name = "Light",
        Transform = {
            scale = {0.1, 0.1, 0.1}
        },
        RenderInfo = {
            mesh = "models/sphere2.obj",
            material = defaultMaterial
        },
        Light = {
            color = {1, 0, 0},
            intensity = 100
        }
    }

    Game.makeActor {
        Name = "Light2",
        Transform = {
            position = {3, 2, 0},
            scale = {0.1, 0.1, 0.1}
        },
        RenderInfo = {
            mesh = "models/sphere2.obj",
            material = defaultMaterial
        },
        Light = {
            color = {0, 1, 0},
			intensity = 20
		}
    }

    Game.makeActor {
        Name = "LightAmbient",
        Transform = {
            scale = {0.1, 0.1, 0.1},
            rotation = {-45, 0, 0}
        },
        Light = {
            kind = "directional",
            intensity = 0,
            ambientColor = {0.02, 0.02, 0.02}
        }
    }

    Game.makeActor {
        Name = "LightDirectional",
        Transform = {
            scale = {0.1, 0.1, 0.1},
            rotation = {-45, 0, 0}
        },
        Light = {
            kind = "directional",
            intensity = 1
        }
    }

    Game.makeActor {
        Name = "LightDirectional2",
        Transform = {
            scale = {0.1, 0.1, 0.1},
            rotation = {0, 0, 0}
        },
        Light = {
            kind = "directional",
            intensity = 0.1
        }
    }

    Game.audio.getMusic('audio/test/test.wav'):play()
end

function scene:update(dt)

    Game.find("Light"):get("Transform").position = {-4, 3 + 2 * math.sin(Game.getTime()), 0}
    --Game.find("LightDirectional"):get("Transform"):rotate(45 * dt, 1, 0, 0);

    if (Game.keyboard.isHeld("Up")) then
        Game.find("Light2"):get("Transform"):move(0, 2 * dt, 0)
    elseif (Game.keyboard.isHeld("Down")) then
        Game.find("Light2"):get("Transform"):move(0, -2 * dt, 0)
    end
end

return scene