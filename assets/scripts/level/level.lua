require('assets/scripts/object')
require('assets/scripts/vector')
require('assets/scripts/level/map')

Level = Object:new {
	map = nil,
	nextLevelPath = nil
}

function Level:start()

	if not self.map then
		print('Level: no map')
		return
	end

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

	if self.extras then
		Game.makeActors(self.extras)
	end

	Game.makeActors {
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