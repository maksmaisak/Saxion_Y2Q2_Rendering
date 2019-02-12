--
-- User: maks
-- Date: 2019-02-12
-- Time: 11:59
--

require('assets/scripts/vector')

local gridSize = {x = 10, y = 10 }
local grid = {} -- grid[x][y] is a table that describes the tile at integer coordinates x and y
for x = 1,gridSize.x do
    grid[x] = {}
    for y = 1,gridSize.y do
        grid[x][y] = {}
    end
end

grid[1][2].isObstacle = true
grid[5][5].isObstacle = true

local playerStartPosition = {x = 2, y = 3}
local player

local tileMaterial = Game.makeMaterial {
    shininess = 100
}

local obstacleMaterial = Game.makeMaterial {
	diffuseColor = {0.8, 0.3, 0.2}
}

local function makeTile(x, y, tile)

    local xNorm = (x - 1) / gridSize.x
    local yNorm = (y - 1) / gridSize.y
    local position = {
        x = (xNorm - 0.5) * gridSize.x,
        y = 0,
        z = (yNorm - 0.5) * gridSize.y
    }

    return Game.makeActor {
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

local function makeObstacle(x, y, tile)

	local xNorm = (x - 1) / gridSize.x
    local yNorm = (y - 1) / gridSize.y
    local position = {
        x = (xNorm - 0.5) * gridSize.x,
        y = 1,
        z = (yNorm - 0.5) * gridSize.y
    }

    return Game.makeActor {
        Name = "Tile."..x.."."..y,
        Transform = {
            position = position,
            scale = {0.9 * 0.5, 0.5, 0.9 * 0.5}
        },
        RenderInfo = {
            mesh = "models/cube_flat.obj",
            material = obstacleMaterial
        }
	}
end

local function getPlayerPositionFromGridPosition(gridPosition)
    return Vector.from {0, 1, 0} + grid[gridPosition.x or 1][gridPosition.y or 1].tile:get("Transform").position
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
            Camera = {
                isOrthographic = true,
                orthographicHalfSize = 8
            }
        },
        {
            Name = "DirectionalLight",
            Transform = {
                rotation = {-70, 0, 0}
            },
            Light = {
                kind = "directional",
                intensity = 0.1
            }
        },
        {
            Name = "PointLight",
            Transform = {
                position = {0, 2, 0}
            },
            Light = {
                intensity = 2
            }
        }
    }

    -- make views
    for x = 1,gridSize.x do
        for y = 1,gridSize.y do
            grid[x][y].tile = makeTile(x, y, grid[x][y])
			if grid[x][y].isObstacle then
				makeObstacle(x, y, grid[x][y])
			end
        end
    end

    local playerActor = Game.makeActor {
        Name = "Player",
        Transform = {
            position = getPlayerPositionFromGridPosition(playerStartPosition),
            scale = {0.3, 0.5, 0.3}
        },
        RenderInfo = {
            mesh = "models/cube_flat.obj",
            material = {
                diffuseColor = {0.5, 0, 0}
            }
        }
    }

    player = {
        actor = playerActor,
        transform = playerActor:get("Transform"),
        gridPosition = {x = playerStartPosition.x, y = playerStartPosition.y}
    }
end

function scene.update()

    local input = {x = 0, y = 0 }
    if Game.keyboard.isDown("left" ) then input.x = input.x + 1 end
    if Game.keyboard.isDown("right") then input.x = input.x - 1 end
    if Game.keyboard.isDown("up"   ) then input.y = input.y + 1 end
    if Game.keyboard.isDown("down" ) then input.y = input.y - 1 end

    if (input.x ~= 0 and input.y ~= 0) then
        input.y = 0
    end

    local nextPosition = {
        x = player.gridPosition.x - input.x,
        y = player.gridPosition.y - input.y
    }

    if nextPosition.x > gridSize.x then
        nextPosition.x = gridSize.x
    elseif nextPosition.x < 1 then
        nextPosition.x = 1
    end

    if nextPosition.y > gridSize.y then
        nextPosition.y = gridSize.y
    elseif nextPosition.y < 1 then
        nextPosition.y = 1
    end

	if not grid[nextPosition.x][nextPosition.y].isObstacle then
		player.gridPosition.x = nextPosition.x
		player.gridPosition.y = nextPosition.y
		player.transform.position = getPlayerPositionFromGridPosition(player.gridPosition)
	end
end

return scene

