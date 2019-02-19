require('assets/scripts/object')

Level = Object:new {
	definitionPath = {}
}

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

local portalData = {
	name			= "Portal",
	startYPosition	= 1,
	scale			= { 0.9 * 0.5, 0.5, 0.9 * 0.5},
	mesh			= "models/cube_flat.obj",
	material		=  Game.makeMaterial {
		diffuseColor = {0, 0.81, 0.82}
	}
}

function Level:start()
	self.definition				= dofile(self.definitionPath)

	self.playerStartPosition	= self.definition.playerStartPosition

	self.map = self.definition.map
	self.map:initializeGrid()

	-- spawn base tiles
    for x = 1, self.map:getGridSize().x do
        for y = 1, self.map:getGridSize().y do

			local gridPosition = { x = x, y = y}

			self.map:getGridAt(gridPosition).tile = self.map:makeGameObject(gridPosition, tileData)
        end
    end

	-- spawn obstacles
	for k, v in pairs(self.definition.obstaclePositions or {}) do
		local gridPosition = { x = v.x, y = v.y }

		self.map:getGridAt(gridPosition).isObstacle = true
		self.map:makeGameObject(gridPosition, obstacleData)
	end
	
	-- spawn buttons
	for k, v in pairs(self.definition.buttonPositions or {}) do
		local gridPosition = { x = v.x, y = v.y }

		self.map:getGridAt(gridPosition).isButton = true

		local buttonActor			= self.map:makeGameObject(gridPosition, buttonData)
		local actionTargetPosition	= { x = v.actionTargetPosition.x, y = v.actionTargetPosition.y }
		local actionTargetActor		= self.map:makeGameObject(actionTargetPosition, goalData)

		self.map:getGridAt(gridPosition).button = {
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

		self.map:getGridAt(actionTargetPosition).isGoal	= true
		self.map:getGridAt(actionTargetPosition).goal	= self.map:getGridAt(gridPosition).button.actionTarget
	end

	-- spawn portals
	for k,v in pairs(self.definition.portalPositions or {}) do
		local gridPosition = { x = v.x, y = v.y }

		self.map:makeGameObject(gridPosition, portalData)

		self.map:getGridAt(gridPosition).isPortal	= true
		self.map:getGridAt(gridPosition).portal		= {
			teleportPosition = { x = v.teleportPosition.x, y = v.teleportPosition.y }
		}
	end

	if self.definition.decorations then
		Game.makeActors(self.definition.decorations)
	end

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

	playerActor:get("LuaBehavior").startPosition = self.playerStartPosition
	playerActor:get("LuaBehavior").map = self.map
	playerActor:get("LuaBehavior").level = self
end

function Level:update(dt)
end
