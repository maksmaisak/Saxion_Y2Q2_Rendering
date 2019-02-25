require('assets/scripts/object')
require('assets/scripts/vector')
require('assets/scripts/level/map')
require('assets/scripts/UI/pauseMenu')

Level = Object:new {
	map = nil,
	nextLevelPath = nil
}

function Level:start()

	if not self.map then
		print('Level: no map')
		return
	end

	self.pauseMenu = PauseMenu:new()

	self.pauseMenu:init()

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
				self.player = gridItem.player:get("LuaBehavior")
			end

			if gridItem.goal then
				local actor = Game.makeActor(gridItem.goal)
				gridItem.goal = {
					actor = actor,
					transform = actor:get("Transform")
				}
			end

			if gridItem.button then
				local button		= gridItem.button
				button.actor		= Game.makeActor(button.actor)
				button.transform	= button.actor:get("Transform")
			end

			if gridItem.portal then
				gridItem.portal.actor = Game.makeActor(gridItem.portal.actor)
			end

			if gridItem.door then
				local door		= gridItem.door
				door.actor		= Game.makeActor(door.actor)
				door.transform	= door.actor:get("Transform")
			end

			if gridItem.laser then
				local laser		= Game.makeActor(gridItem.laser.actor)
				laser:add("LuaBehavior", dofile(Config.laser) {
					level		 = self,
					map			 = self.map,
					actor		 = laser,
					direction	 = {x = gridItem.laser.direction.x, y = gridItem.laser.direction.y},
					gridPosition = {x = x, y = y}
				})
				self.map.lasers[#self.map.lasers + 1] = laser
			end
        end
	end

	if self.extras then
		Game.makeActors(self.extras)
	end
end