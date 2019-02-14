--
-- User: maks
-- Date: 2019-02-12
-- Time: 11:59
--

require('assets/scripts/vector')
require('assets/scripts/player')
require('assets/scripts/map')

local map
local player
local playerStartPosition = {x = 2, y = 3}

local tileData = {
	name			= "Tile",
	startYPosition	= 0,
	scale			= { 0.9 * 0.5, 0.5, 0.9 * 0.5 },
	mesh			= "models/cube_flat.obj",
	material		= Game.makeMaterial {
		shininess = 100
	}
}

local buttonData = {
	name			= "Presable Button",
	startYPosition	= 0.8,
	scale			= { 0.9 * 0.3, 0.5, 0.9 * 0.5 },
	mesh			= "models/cube_flat.obj",
	material		= Game.makeMaterial {
		diffuseColor = {1, 0.2, 0.5}
	}
}

local obstacleData = {
	name			= "Obstacle",
	startYPosition	= 1,
	scale			= { 0.9 * 0.5, 0.5, 0.9 * 0.5 },
	mesh			= "models/cube_flat.obj",
	material		=  Game.makeMaterial {
		diffuseColor = {0.8, 0.3, 0.2}
	}
}

local goalData = {
	name			= "Goal",
	startYPosition	= 0.8,
	scale			= { 0.9 * 0.5, 0.3, 0.9 * 0.5},
	mesh			= "models/cube_flat.obj",
	material		=  Game.makeMaterial {
		diffuseColor = {0, 0, 1}
	}
}

local scene = {}

function scene.start()

	map = Map:new {
		gridSize = { x = 10, y = 10}
	}

	map:initializeGrid()

	map.grid[1][2].isObstacle = true
	map.grid[5][5].isObstacle = true
	map.grid[3][3].isButton = true

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
    for x = 1, map:getGridSize().x do
        for y = 1, map:getGridSize().y do

			local gridPosition = { x = x, y = y}

			map:getGridAt(gridPosition).tile = map:makeGameObject(gridPosition, tileData)

			if map:getGridAt(gridPosition).isObstacle then
				map:makeGameObject(gridPosition, obstacleData)
			end

			if map:getGridAt(gridPosition).isButton then

				local buttonActor			= map:makeGameObject(gridPosition, buttonData)
				local actionTargetPosition	= { x = 8, y= 8}
				local actionTargetActor		= map:makeGameObject(actionTargetPosition, goalData)

				map:getGridAt(gridPosition).button = {
					actor		= buttonActor,
					transform	= buttonActor:get("Transform"),

					actionTarget = {
						actor		= actionTargetActor,
						transform	= actionTargetActor:get("Transform"),
						isEnabled	= false,
						isActivated = false
					},

					isActivated = false
				}

				map:getGridAt(actionTargetPosition).isGoal	= true
				map:getGridAt(actionTargetPosition).goal	= map:getGridAt(gridPosition).button.actionTarget
			end
        end
    end

	local playerActor = Game.makeActor {
        Name = "Player",
        Transform = {
            scale = {0.3, 0.5, 0.3}
        },
        RenderInfo = {
            mesh = "models/cube_flat.obj",
            material = {
                diffuseColor = {0.5, 0, 0}
            }
        },
		LuaBehavior = Config.player
    }

	playerActor:get("LuaBehavior").startPosition = playerStartPosition
	playerActor:get("LuaBehavior").map = map

	player = {actor = playerActor}

end

return scene

