require('assets/scripts/object')
require('assets/scripts/vector')
require('assets/scripts/level/map')
require('assets/scripts/UI/pauseMenu')
require('assets/scripts/UI/redoUndoButtons')
require('assets/scripts/UI/hudArrows')
require('assets/scripts/UI/tutorialScreen')

Level = Object:new {
	map = nil,
	nextLevelPath = nil
}

function Level:start()

	if not self.map then
		print('Level: no map')
		return
	end

	local music = Game.audio.getMusic('audio/ambiance.wav')
	if music.status ~= "Playing" then
		print("Music Status", music.status)
		music.loop	= true
		music.volume = 100
		music:play()
	end

	self.redoUndoButtons = RedoUndoButtons:new {level = self}
	self.hudArrows = HudArrows:new()
	self.pauseMenu = PauseMenu:new()

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
					pauseMenu  = self.pauseMenu,
				})
				self.player = gridItem.player:get("LuaBehavior")
			end

			if gridItem.goal then

                local goal		= gridItem.goal
                goal.actor		= Game.makeActor(goal.actor)
				goal.transform	= goal.actor:get("Transform")

				if goal.light then
					local light				= goal.light
					light.actor				= Game.makeActor(goal.light)
					light.transform			= light.actor:get("Transform")
					light.transform.parent	= goal.actor
					light.initialIntensity  = light.Light.intensity
					if not goal.startActive then
						light.actor:get("Light").intensity = 0
					end
				end
			end

			if gridItem.button then

				local button	 = gridItem.button
				button.actor	 = Game.makeActor(button.actor)
				button.transform = button.actor:get("Transform")
			end

			if gridItem.portal then
				gridItem.portal.actor = Game.makeActor(gridItem.portal.actor)
			end

			if gridItem.door then

				local door	   = gridItem.door
				door.actor	   = Game.makeActor(door.actor)
				door.transform = door.actor:get("Transform")

				door.swingLeft					= Game.makeActor(door.swingLeft)
				door.swingLeftTransform			= door.swingLeft:get("Transform")
				door.swingLeftTransform.parent	= door.actor

				door.swingRight					= Game.makeActor(door.swingRight)
				door.swingRightTransform		= door.swingRight:get("Transform")
				door.swingRightTransform.parent = door.actor
			end

			if gridItem.laser then

				local laser = gridItem.laser

				laser.actor = Game.makeActor(laser.actor)
				laser.beam  = Game.makeActor(laser.beam)
				laser.beam:get("Transform").parent = laser.actor

				laser.actor:add("LuaBehavior", dofile(Config.laser) {
					level		 = self,
					map			 = self.map,
					direction	 = {x = laser.direction.x, y = laser.direction.y},
					gridPosition = {x = x, y = y}
				})

				self.map.lasers[#self.map.lasers + 1] = laser
			end
        end
	end

	if self.extras then
		Game.makeActors(self.extras)
	end

	self.tutorialScreen = TutorialScreen:new()
end