require('assets/scripts/vector')
require('assets/scripts/object')
require('assets/scripts/level/map')

Player = Object:new {
	startPosition	= { x = 1, y = 1 },
	gridPosition	= { x = 1, y = 1 },
	lastPosition	= { x = 1, y = 1 },
	map				= {}
}

local disabledKeys = {left = false, right = false, up = false, down = false}
local inputKeys = { left = { x = 1.0, y= 0}, right = {x = -1, y = 0}, up = {x = 0, y = 1}, down = {x = 0, y = -1} }

function Player:getPositionFromGridPosition(gridPosition)
	local yOffSet = self.map:calculateYOffset(gridPosition)
    return Vector.from {0, 1 + yOffSet, 0} + self.map:getGridAt(gridPosition).tile:get("Transform").position
end

function Player:makeKey(gridPosition, keyName)

	local xNorm = (gridPosition.x - 1) / self.map:getGridSize().x
    local yNorm = (gridPosition.y - 1) / self.map:getGridSize().y
    local position = {
        x = (xNorm - 0.5) * self.map:getGridSize().x,
        y = 1 + self.map:calculateYOffset(gridPosition),
        z = (yNorm - 0.5) *  self.map:getGridSize().y
    }

	local keyColor = { 0.0, 1.0, 0}

	if keyName == "up" then
		keyColor[1] = 1
	elseif keyName == "down" then
		keyColor[3] = 10
	elseif keyName == "left" then
		keyColor = { 0, 0, 0}
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
	local goal = self.map:getGridAt(gridPosition).goal
	if not goal.isEnabled then
		return
	end

	if goal.isActivated then
		return
	end

	goal.isActivated = true
	Game.loadScene(Level:new {
		definitionPath = self.level.definition.nextLevelDefinitionPath
	})
	print("activating goal")
end

function Player:activateButton(gridPosition)
	local button = self.map:getGridAt(gridPosition).button

	if(button.isActivated) then
		return
	end

	button.isActivated				= true
	button.actionTarget.isEnabled	= true

	local buttonPosition		= button.transform.position
	buttonPosition.y			= buttonPosition.y - 0.5
	button.transform.position	= buttonPosition

	local actionTargetPosition 	= button.actionTarget.transform.position
	actionTargetPosition.y 		= actionTargetPosition.y + 0.5

	button.actionTarget.transform.position = actionTargetPosition
	print("Button activated")
end

function Player:disableButton(gridPosition)
	local button = self.map:getGridAt(gridPosition).button

	if(not button.isActivated) then
		return
	end

	-- if there is one key left on the droppable button don't do the animation
	for k, v in pairs(self.map:getDroppedKeysGridAt(gridPosition).hasKeyDropped) do
		if(v == true) then
			return
		end
	end

	button.isActivated				= false
	button.actionTarget.isEnabled	= false

	local buttonPosition		= button.transform.position
	buttonPosition.y			= buttonPosition.y + 0.5
	button.transform.position	= buttonPosition

	local actionTargetPosition 	= button.actionTarget.transform.position
	actionTargetPosition.y 		= actionTargetPosition.y - 0.5

	button.actionTarget.transform.position = actionTargetPosition

	print("Button Deactivated")
end

function Player:blockKey(key)
	print(key.." key blocked")
	disabledKeys[key] = true
	self.map:getDroppedKeysGridAt(self.gridPosition).hasKeyDropped[key] = true

	local pair = {}
	pair[key] = self:makeKey(self.gridPosition, key)

	local tempArray = self.map:getDroppedKeysGridAt(self.gridPosition).keys
	self.map:getDroppedKeysGridAt(self.gridPosition).keys [#tempArray+1] = pair

	self.transform.position = self:getPositionFromGridPosition(self.gridPosition)
end

function Player:unblockKey(key)
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
			if (p) then
				local xNorm = (self.gridPosition.x - 1) /  self.map:getGridSize().x
				local yNorm = (self.gridPosition.y - 1) /  self.map:getGridSize().y

				local position = {
					x = (xNorm - 0.5) *  self.map:getGridSize().x,
					y = 1 + (index * 2 * p:get("Transform").scale.y),
					z = (yNorm - 0.5) *  self.map:getGridSize().y
				}

				index = index + 1
				p:get("Transform").position = position 
			end
		end
	end

	self.transform.position = self:getPositionFromGridPosition(self.gridPosition)
end

function Player:moveToPosition(nextPosition, canRegisterMove)
	if not self.map:getGridAt(nextPosition).isObstacle then
		if nextPosition.x ~= self.gridPosition.x or nextPosition.y ~= self.gridPosition.y then
			self.lastPosition.x = self.gridPosition.x
			self.lastPosition.y = self.gridPosition.y

			self.gridPosition.x = nextPosition.x
			self.gridPosition.y = nextPosition.y

			if canRegisterMove then
				self.moves[#self.moves + 1] = { x = self.gridPosition.x, y = self.gridPosition.y }
				self.currentMoveIndex = self.currentMoveIndex + 1
			end

			if self.map:getGridAt(self.gridPosition).isButton then
				self:activateButton(self.gridPosition)
			end

			-- if the tile changed then we gotta check if there was a button and disable it
			if self.lastPosition.x ~= self.gridPosition.x or self.lastPosition.y ~= self.gridPosition.y then
				if(self.map:getGridAt(self.lastPosition).isButton) then
					self:disableButton(self.lastPosition)
				end
			end

			if self.map:getGridAt(self.gridPosition).isGoal then
				self:activateGoal(self.gridPosition)
			end

			self.transform.position = self:getPositionFromGridPosition(self.gridPosition)
		end
	end
end

function  Player:redoMove()
	-- there are no redo moves left for us so do nothing here
	if self.currentMoveIndex >= #self.moves then
		print("No redos left")
		return
	end

	self.currentMoveIndex	= self.currentMoveIndex + 1
	local nextPosition		= self.moves[self.currentMoveIndex]

	self:moveToPosition(nextPosition, false)
end

function Player:undoMove()
	-- there are no undo moves left for us so do nothing here
	if self.currentMoveIndex <= 1 then
		print("No undos left")
		return
	end

	self.currentMoveIndex	= self.currentMoveIndex - 1
	local nextPosition		= self.moves[self.currentMoveIndex]

	print("undoing move")

	self:moveToPosition(nextPosition, false)
end

function Player:start()
	self.gridPosition.x = self.startPosition.x
	self.gridPosition.y = self.startPosition.y
	self.lastPosition.x = self.startPosition.x
	self.lastPosition.y = self.startPosition.y

	self.transform			= self.actor:get("Transform")
	self.transform.position = self:getPositionFromGridPosition(self.gridPosition)

	self.moves = { { x = self.gridPosition.x, y = self.gridPosition.y} }
	self.currentMoveIndex = 1
end

function Player:update()
   local input = {x = 0, y = 0 }

	for key, value in pairs(inputKeys) do
		if (not disabledKeys[key] and Game.keyboard.isDown(key)) then
			input.x = input.x + value.x
			input.y = input.y + value.y
		end
	end

    if (input.x ~= 0 and input.y ~= 0) then
        input.y = 0
    end

	if Game.keyboard.isDown("r") then
		Game.loadScene("assets/scripts/scenes/level1.lua")
		return
	end

	if Game.keyboard.isDown("e") then
		self:redoMove()
	end

	if Game.keyboard.isDown("q") then
		self:undoMove()
	end

	if Game.keyboard.isHeld("LShift") or Game.keyboard.isHeld("RShift") then
		for key, value in pairs(inputKeys) do
			if(Game.keyboard.isDown(key)) then
				if (not self.map:getDroppedKeysGridAt(self.gridPosition).hasKeyDropped[key]) and not disabledKeys[key] then
					self:blockKey(key)
				elseif self.map:getDroppedKeysGridAt(self.gridPosition).hasKeyDropped[key] and disabledKeys[key] then
					self:unblockKey(key)
				end
				input = {x = 0, y = 0}
			end
		end
	end

    local nextPosition = {
        x = self.gridPosition.x - input.x,
        y = self.gridPosition.y - input.y
    }

    if nextPosition.x >  self.map:getGridSize().x then
        nextPosition.x =  self.map:getGridSize().x
    elseif nextPosition.x < 1 then
        nextPosition.x = 1
    end

    if nextPosition.y >  self.map:getGridSize().y then
        nextPosition.y =  self.map:getGridSize().y
    elseif nextPosition.y < 1 then
        nextPosition.y = 1
    end

	self:moveToPosition(nextPosition, true)
end

return function(o)
    return Player:new(o)
end