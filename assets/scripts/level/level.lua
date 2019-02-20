require('assets/scripts/object')
require('assets/scripts/vector')

Level = Object:new {
	definitionPath = nil
}

local function getCameraPosition(gridSize)
	return Vector.from{gridSize.x, 0, gridSize.y} * 0.5 + {x = 8, y = 12, z = 8}
end

function Level:start()

	if not self.definitionPath then
		print('Level: no path to level definition.')
		return
	end

	self.definition	 = dofile(self.definitionPath)
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

			if gridItem.player then
				gridItem.player = Game.makeActor(gridItem.player)
				gridItem.player:add("LuaBehavior", dofile(Config.player) {
					level = self,
					map   = self.map,
				})
			end

			if gridItem.goal then
				local actor = Game.makeActor(gridItem.goal)
				gridItem.goal = {
					actor = actor,
					transform = actor:get("Transform")
				}
			end

			if gridItem.button then
				local button = gridItem.button
				button.actor = Game.makeActor(gridItem.button.actor)
				button.transform = button.actor:get("Transform")
			end

			if gridItem.portal then
				gridItem.portal.actor = Game.makeActor(gridItem.portal.actor)
			end
        end
	end

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
end