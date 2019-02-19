require('assets/scripts/object')
require('assets/scripts/vector')

Level = Object:new {
	definitionPath = nil
}

local function getCameraPosition(gridSize)
	return Vector.from{gridSize.x, 0, gridSize.y} * 0.5 + {x = 8, y = 12, z = 8}
end

function Level:start()

	self.definition			 = dofile(self.definitionPath)
	self.playerStartPosition = self.definition.playerStartPosition
	self.map = self.definition.map

    for x = 1, self.map:getGridSize().x do
        for y = 1, self.map:getGridSize().y do

			local gridItem = self.map:getGridAt({x = x, y = y})

			if gridItem.tile then
				gridItem.tile = Game.makeActor(gridItem.tile)
			end

			if gridItem.obstacle then
				gridItem.obstacle = Game.makeActor(gridItem.obstacle)
			end

			if gridItem.goal then
				gridItem.goal = Game.makeActor(gridItem.goal)
			end

			if gridItem.player then
				gridItem.player = Game.makeActor(gridItem.player)
			end

			if gridItem.button then

				local actor = Game.makeActor(gridItem.button)
				gridItem.button = {
					actor = actor,
					transform = actor.get("Transform")
				}
			end

			if gridItem.portal then
				gridItem.portal = Game.makeActor(gridItem.portal)
			end
        end
	end

--	-- spawn buttons
--	for k, v in pairs(self.definition.buttonPositions or {}) do
--		local gridPosition = { x = v.x, y = v.y }
--
--		self.map:getGridAt(gridPosition).isButton = true
--
--		local buttonActor			= self.map:makeGameObject(gridPosition, buttonData)
--		local actionTargetPosition	= { x = v.actionTargetPosition.x, y = v.actionTargetPosition.y }
--		local actionTargetActor		= self.map:makeGameObject(actionTargetPosition, goalData)
--
--		self.map:getGridAt(gridPosition).button = {
--			actor		= buttonActor,
--			transform	= buttonActor:get("Transform"),
--
--			actionTarget = {
--				actor		= actionTargetActor,
--				transform	= actionTargetActor:get("Transform"),
--				isEnabled	= false,
--				isActivated = false
--			},
--
--			isActivated = false
--		}
--
--		self.map:getGridAt(actionTargetPosition).isGoal	= true
--		self.map:getGridAt(actionTargetPosition).goal	= self.map:getGridAt(gridPosition).button.actionTarget
--	end

--	-- spawn portals
--	for k,v in pairs(self.definition.portalPositions or {}) do
--		local gridPosition = { x = v.x, y = v.y }
--
--		self.map:makeGameObject(gridPosition, portalData)
--
--		self.map:getGridAt(gridPosition).isPortal	= true
--		self.map:getGridAt(gridPosition).portal		= {
--			teleportPosition = { x = v.teleportPosition.x, y = v.teleportPosition.y }
--		}
--	end

--	if self.definition.decorations then
--		Game.makeActors(self.definition.decorations)
--	end

	Game.makeActors {
        {
            Name = "Camera",
            Transform = {
                position = getCameraPosition(self.map:getGridSize()),
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

	local player = Game.find("Player")
	if player then
		player:add("LuaBehavior", dofile(Config.player) {
			startPosition = self.playerStartPosition,
			map = self.map,
			level = self
		})
	end
end