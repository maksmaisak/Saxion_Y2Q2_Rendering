--
-- User: maks
-- Date: 2019-02-12
-- Time: 11:59
--

local gridSize = {x = 10, y = 10 }
local grid = {} -- grid[x][y] is a table that describes the tile at integer coordinates x and y
for x = 1,gridSize.x do
    grid[x] = {}
    for y = 1,gridSize.y do
        grid[x][y] = {}
    end
end

local tileMaterial = Game.makeMaterial {
    shininess = 100
}

local function makeTile(x, y, tile)

    local xNorm = (x - 1) / gridSize.x
    local yNorm = (y - 1) / gridSize.y
    local position = {
        x = (xNorm - 0.5) * gridSize.x,
        y = 0,
        z = (yNorm - 0.5) * gridSize.y
    }

    Game.makeActor {
        Name = "Tile."..x.."."..y,
        Transform = {
            position = position,
            scale = {0.9 * 0.5, 0.5, 0.9 * 0.5}
        },
        RenderInfo = {
            mesh = "models/cube_flat.obj",
            material = tileMaterial
        }
    }
end

local scene = {}

function scene.start()

    Game.makeActors {
        {
            Name = "Camera",
            Transform = {
                position = {8, 12, 8},
                rotation = {-45, 45, 0}
            },
            Camera = {}
        },
        {
            Name = "DirectionalLight",
            Transform = {
                rotation = {-30, 0, 0}
            },
            Light = {
                kind = "directional"
            }
        }
    }

    -- make views
    for x = 1,gridSize.x do
        for y = 1,gridSize.y do
            print(x.."."..y)
            makeTile(x, y, grid[x][y])
        end
    end
end

return scene

