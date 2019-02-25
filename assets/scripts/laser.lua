require ('assets/scripts/object')
require ('assets/scripts/vector')
require ('assets/scripts/level/map')
require ('assets/scripts/player')

Laser = Object:new {
	level = nil,
	map   = nil
}

function Laser:start()

	self.timer		   = 0
	self.checkInterval = 0.5
	self.gridItem	   = self.map:getGridAt(self.gridPosition)
	self.transform	   = self.actor:get("Transform")

	self.beamRenderInfo = self.gridItem.laser.beam:getInChildren("RenderInfo")
end

function Laser:update(dt)

	if self.beamRenderInfo then
		self.beamRenderInfo.isEnabled = self.gridItem.isButtonTargetEnabled or false
	end

	self.timer = self.timer + dt
	if self.gridItem.isButtonTargetEnabled then
		if self.timer >= self.checkInterval then
			self:hitDroppedKeys()
			self.timer = 0
		end
	end
end

function Laser:hitDroppedKeys()

	print("hitting dropped keys")

	local position = {x = self.gridPosition.x, y = self.gridPosition.y}
	for i = 1, 20 do

		local gridItem = self.map:getGridAt(position)
		if gridItem ~= nil then
			-- end if we hit an obstacle or empty tile
			if gridItem.obstacle or not gridItem.tile then
				return
			end

			for k, v in pairs(self.map:getDroppedKeysGridAt(position).hasKeyDropped) do
				if v then -- if has this currentKey dropped at this position
					self.level.player:moveByLaser(k)
				end
			end
		end

		position.x = position.x + self.direction.x
		position.y = position.y + self.direction.y

		if position.x > self.map.gridSize.x or position.x < 1 then
			break
		end

		if position.y > self.map.gridSize.y or position.y < 1 then
			break
		end
	end
end

return function(o)
    return Laser:new(o)
end