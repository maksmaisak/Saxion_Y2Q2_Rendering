require('assets/scripts/vector')
require('assets/scripts/object')
require('assets/scripts/level/map')
require('assets/scripts/UI/pauseMenu')

Player = Object:new {
	gridPosition = { x = 1, y = 1 },
	lastPosition = { x = 1, y = 1 },
	map			 = nil
}

local disabledKeys = {left = false, right = false, up = false, down = false}
local inputKeys = { left = { x = 1, y = 0}, right = {x = -1, y = 0}, up = {x = 0, y = 1}, down = {x = 0, y = -1} }

function Player:getPositionFromGridPosition(gridPosition)

	return Vector:new {
		x = gridPosition.x - 1,
		y = self.map:calculateYOffset(gridPosition),
		z = gridPosition.y - 1
	}
end

function Player:makeKey(gridPosition, keyName)

    local position = {
        x = gridPosition.x - 1,
        y = 0.2 + self.map:calculateYOffset(gridPosition),
        z = gridPosition.y - 1
    }

	local keyColor = {0.0, 1.0, 0.0}

	if keyName == "up" then
		keyColor[1] = 1
	elseif keyName == "down" then
		keyColor[3] = 1
	elseif keyName == "left" then
		keyColor = {0, 0, 0}
	end

    return Game.makeActor {
        Name = "Key."..gridPosition.x.."."..gridPosition.y,
        Transform = {
            position = position,
            scale = {0.9 * 0.5, 0.2, 0.9 * 0.5}
        },
        RenderInfo = {
            mesh = "models/cube_flat.obj",
            material = {
				diffuseColor = keyColor
			}
        }
	}
end

function Player:activateGoal(gridPosition)

	local gridItem	= self.map:getGridAt(gridPosition)
	local goal		= gridItem.goal
	if not gridItem.isButtonTargetEnabled then
		return
	end

	if goal.isActivated then
		return
	end

	goal.isActivated = true
	Game.loadScene(self.level.nextLevelPath)
	print("activating goal")
end

function Player:activateButton(gridPosition)

	local button = self.map:getGridAt(gridPosition).button
	if button.isActivated then
		return
	end

	button.isActivated = true

	local buttonPosition	  = button.transform.position
	buttonPosition.y		  = buttonPosition.y - 0.5
	button.transform.position = buttonPosition

	self:activateButtonTarget(button)

	print("Button activated")
end

function Player:disableButton(gridPosition)

	local button = self.map:getGridAt(gridPosition).button
	if not button.isActivated then
		return
	end

	-- if there is one key left on the droppable button don't do the animation
	for k, v in pairs(self.map:getDroppedKeysGridAt(gridPosition).hasKeyDropped) do
		if v then
			return
		end
	end

	button.isActivated	= false

	local buttonPosition	  = button.transform.position
	buttonPosition.y		  = buttonPosition.y + 0.5
	button.transform.position = buttonPosition

	self:deactivateButtonTarget(button)
	print("Button Deactivated")
end

function Player:activateButtonTarget(button)
	local target = self.map:getGridAt(button.targetPosition)

	target.isButtonTargetEnabled = true

	if target.goal ~= nil then
		print("Activating goal")
		local goal = target.goal

		-- play goal activation "animation" this is a placeholder (it moves the position)
		-- replace it when with the real one when is done
		local goalPosition		= goal.transform.position
		goalPosition.y 			= goalPosition.y + 0.5
		goal.transform.position	= goalPosition
	elseif target.door ~= nil then

		print("Activating door")
		local door = target.door
		door.swingLeftTransform:rotate ( 90, 0, 1, 0)
		door.swingRightTransform:rotate(-90, 0, 1, 0)
	end
end

function Player:deactivateButtonTarget(button)
	local target = self.map:getGridAt(button.targetPosition)

	target.isButtonTargetEnabled = false

	if target.goal ~= nil then
		print("Deactivating goal")

		local goal		= target.goal

		-- play goal activation "animation" this is a placeholder (it moves the position)
		-- replace it when with the real one when is done
		local goalPosition		= goal.transform.position
		goalPosition.y 			= goalPosition.y - 0.5
		goal.transform.position	= goalPosition
	elseif target.door ~= nil then
		print("Deactivating door")

		local door = target.door
		door.swingLeftTransform:rotate (-90, 0, 1, 0)
		door.swingRightTransform:rotate( 90, 0, 1, 0)
	end
end

function Player:registerMove(undoFunction, redoFunction)

	print("move registered")

	for k, v in pairs(self.moves) do
		if k >= self.currentMoveIndex then
			self.moves[k] = nil
			v = nil
			k = nil
		end
	end

	self.currentMoveIndex = self.currentMoveIndex + 1

	self.moves[#self.moves + 1]	= { 
		undo = undoFunction,
		redo = redoFunction
	}
end

function Player:blockKey(key, canRegisterMove)

	print(key.." key blocked")
	disabledKeys[key] = true
	self.map:getDroppedKeysGridAt(self.gridPosition).hasKeyDropped[key] = true

	local pair = {}
	pair[key] = self:makeKey(self.gridPosition, key)

	local keys = self.map:getDroppedKeysGridAt(self.gridPosition).keys
	keys[#keys + 1] = pair

	self.transform.position = self:getPositionFromGridPosition(self.gridPosition)

	if canRegisterMove then
		self:registerMove(
			function() self:unblockKey(key, false) end,
			function() self:blockKey  (key, false) end
		)
	end
end

function Player:unblockKey(key, canRegisterMove)

	print(key.." key unblocked")
	disabledKeys[key] = false
	self.map:getDroppedKeysGridAt(self.gridPosition).hasKeyDropped[key] = false

	for k, v in pairs(self.map:getDroppedKeysGridAt(self.gridPosition).keys) do
		local currentActor = v[key]
		if(currentActor ~= nil) then
			currentActor:destroy()
			currentActor = nil
			v[key] = nil
			break
		end
	end

	local index = 0

	for k, v in pairs(self.map:getDroppedKeysGridAt(self.gridPosition).keys) do
		for m, p in pairs(v) do
			if p then

				p:get("Transform").position = {
					x = self.gridPosition.x - 1,
					y = index * 2 * p:get("Transform").scale.y,
					z = self.gridPosition.y - 1
				}

				index = index + 1
			end
		end
	end

	self.transform.position = self:getPositionFromGridPosition(self.gridPosition)

	if canRegisterMove then
		self:registerMove(
			function() self:blockKey(key, false) end,
			function() self:unblockKey(key, false) end
		)
	end
end

function Player:moveByKey(keyFound)

	local value = inputKeys[keyFound]
	self:moveByInput({x = value.x, y = value.y})
end

function Player:moveByInput(input)

	if input.x == 0 and input.y == 0 then
		return
	end

	local nextPosition = {
		x = self.gridPosition.x + input.x,
		y = self.gridPosition.y + input.y
	}

	if nextPosition.x > self.map:getGridSize().x then
		nextPosition.x = self.map:getGridSize().x
	elseif nextPosition.x < 1 then
		nextPosition.x = 1
	end

	if nextPosition.y > self.map:getGridSize().y then
		nextPosition.y = self.map:getGridSize().y
	elseif nextPosition.y < 1 then
		nextPosition.y = 1
	end

	self:moveToPosition(nextPosition, true)
end

function Player:moveToPosition(nextPosition, canRegisterMove, didUsePortal)
	local gridItem = self.map:getGridAt(nextPosition);

	if gridItem.obstacle or not gridItem.tile then
		return
	end

	if gridItem.door and not gridItem.isButtonTargetEnabled then
		return
	end

	if nextPosition.x == self.gridPosition.x and nextPosition.y == self.gridPosition.y then
		return
	end

	self.lastPosition.x = self.gridPosition.x
	self.lastPosition.y = self.gridPosition.y

	self.gridPosition.x = nextPosition.x
	self.gridPosition.y = nextPosition.y

	local lastPosition = { x = self.lastPosition.x, y = self.lastPosition.y }
	local gridPosition = { x = self.gridPosition.x, y = self.gridPosition.y }
	if canRegisterMove then
		self:registerMove(
			function()
				self:moveToPosition(lastPosition, false)
			end,
			function()
				self:moveToPosition(gridPosition, false)
			end
		)
	end

	if gridItem.button then
		self:activateButton(self.gridPosition)
	end

	-- if the tile changed then we gotta check if there was a button and disable it
	if self.lastPosition.x ~= self.gridPosition.x or self.lastPosition.y ~= self.gridPosition.y then
		if self.map:getGridAt(self.lastPosition).button then
			self:disableButton(self.lastPosition)
		end
	end

	if gridItem.goal then
		self:activateGoal(self.gridPosition)
	end

	if not didUsePortal and gridItem.portal then
		self:moveToPosition(gridItem.portal.teleportPosition, false, true)
		return
	end

	self.transform.position = self:getPositionFromGridPosition(nextPosition)
end

function Player:redoMove()

	-- there are no redo moves left for us so do nothing here
	if self.currentMoveIndex > #self.moves then
		print("No redos left")
		return
	end

	local move			  = self.moves[self.currentMoveIndex]
	self.currentMoveIndex = self.currentMoveIndex + 1
	move.redo()

	print("redoing move")
end

function Player:undoMove()

	-- there are no undo moves left for us so do nothing here
	if self.currentMoveIndex <= 1 then
		print("No undos left")
		return
	end

	self.currentMoveIndex = self.currentMoveIndex - 1
	if self.currentMoveIndex < 1 then
		self.currentMoveIndex = 1
	end

	local move = self.moves[self.currentMoveIndex]
	move.undo()

	print("undoing move")
end

function Player:start()

	self.transform = self.actor:get("Transform")
	local position = self.transform.position

	self.gridPosition.x = position.x + 1
	self.gridPosition.y = position.z + 1
	self.lastPosition.x = self.gridPosition.x
	self.lastPosition.y = self.gridPosition.y

	self.moves = {}
	self.currentMoveIndex = 1
end

function Player:update()

	if Game.keyboard.isDown("p") then
		self.level.pauseMenu:activate()
	end

	if Game.keyboard.isDown("r") then
		Game.loadScene(Config.startScene)
		return
	end

	if Game.keyboard.isDown("e") then
		self:redoMove()
		return
	end

	if Game.keyboard.isDown("q") then
		self:undoMove()
		return
	end

	if Game.keyboard.isHeld("LShift") or Game.keyboard.isHeld("RShift") then
		for key, value in pairs(inputKeys) do
			if Game.keyboard.isDown(key) then

				if not self.map:getDroppedKeysGridAt(self.gridPosition).hasKeyDropped[key] and not disabledKeys[key] then
					self:blockKey(key, true)
					return
				end

				if self.map:getDroppedKeysGridAt(self.gridPosition).hasKeyDropped[key] and disabledKeys[key] then
					self:unblockKey(key, true)
					return
				end
			end
		end
	end

	local input = {x = 0, y = 0 }
	for key, value in pairs(inputKeys) do
		if (not disabledKeys[key] and Game.keyboard.isDown(key)) then
			input.x = input.x + value.x
			input.y = input.y + value.y
			break;
		end
	end
	if input.x ~= 0 and input.y ~= 0 then
		input.y = 0
	end
	self:moveByInput(input)
end

return function(o)
    return Player:new(o)
end