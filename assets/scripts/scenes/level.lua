--
-- User: maks
-- Date: 2019-02-12
-- Time: 11:59
--

require('assets/scripts/vector')

local gridSize = {x = 10, y = 10 }
local grid = {} -- grid[x][y] is a table that describes the tile at integer coordinates x and y
for x = 1,gridSize.x do
    grid[x] = {}
    for y = 1,gridSize.y do
        grid[x][y] = {}
    end
end

grid[1][2].isObstacle = true
grid[5][5].isObstacle = true
grid[3][3].isButton = true

local playerStartPosition = {x = 2, y = 3}
local player

local droppedKeysGrid = {}

for x = 1,gridSize.x do
    droppedKeysGrid[x] = {}
    for y = 1,gridSize.y do
        droppedKeysGrid[x][y]				= {}
		droppedKeysGrid[x][y].keys			= {up = nil, down = nil, left = nil, right = nil }
		droppedKeysGrid[x][y].hasKeyDropped = {up = false, down = false, left = false, right = false}
    end
end

local disabledKeys = {left = false, right = false, up = false, down = false}
local inputKeys = { left = { x = 1.0, y= 0}, right = {x = -1, y = 0}, up = {x = 0, y = 1}, down = {x = 0, y = -1} }

local tileMaterial = Game.makeMaterial {
    shininess = 100
}

local obstacleMaterial = Game.makeMaterial {
	diffuseColor = {0.8, 0.3, 0.2}
}

local function getGridAt(gridPosition)
	return grid[gridPosition.x][gridPosition.y]
end

local function getDroppedKeysGridAt(gridPosition)
	return droppedKeysGrid[gridPosition.x][gridPosition.y]
end

local function calculateYOffset(gridPosition)
	local yOffset = 0.0

	for k, v in pairs(getDroppedKeysGridAt(gridPosition).keys) do
		
		for m, p in pairs(v) do
			if(p) then
				yOffset = yOffset + 2 * p:get("Transform").scale.y
			end
		end
	end

	return yOffset
end

local function getPlayerPositionFromGridPosition(gridPosition)
	local yOffSet = calculateYOffset(gridPosition)
    return Vector.from {0, 1 + yOffSet, 0} + grid[gridPosition.x or 1][gridPosition.y or 1].tile:get("Transform").position
end

local function makeTile(gridPosition)

    local xNorm = (gridPosition.x - 1) / gridSize.x
    local yNorm = (gridPosition.y - 1) / gridSize.y
    local position = {
        x = (xNorm - 0.5) * gridSize.x,
        y = 0,
        z = (yNorm - 0.5) * gridSize.y
    }

    return Game.makeActor {
        Name = "Tile."..gridPosition.x.."."..gridPosition.y,
        Transform = {
            position = position,
            scale = {0.9 * 0.5, 0.5, 0.9 * 0.5}
        },
        RenderInfo = {
            mesh = "models/cube_flat.obj",
            material = tileMaterial
        }
    }
end

local function makeObstacle(gridPosition)

	local xNorm = (gridPosition.x - 1) / gridSize.x
    local yNorm = (gridPosition.y - 1) / gridSize.y
    local position = {
        x = (xNorm - 0.5) * gridSize.x,
        y = 1,
        z = (yNorm - 0.5) * gridSize.y
    }

    return Game.makeActor {
        Name = "Obstacle."..gridPosition.x.."."..gridPosition.y,
        Transform = {
            position = position,
            scale = {0.9 * 0.5, 0.5, 0.9 * 0.5}
        },
        RenderInfo = {
            mesh = "models/cube_flat.obj",
            material = obstacleMaterial
        }
    }
end

local function makeKey(gridPosition, key)

	local xNorm = (gridPosition.x - 1) / gridSize.x
    local yNorm = (gridPosition.y - 1) / gridSize.y
    local position = {
        x = (xNorm - 0.5) * gridSize.x,
        y = 1 + calculateYOffset(gridPosition),
        z = (yNorm - 0.5) * gridSize.y
    }

	local keyColor = { 0.0, 1.0, 0}

	if key == "up" then
		keyColor[1] = 1
	elseif key == "down" then
		keyColor[3] = 10
	elseif key == "left" then
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

local function makeButton(gridPosition, color)
	local xNorm = (gridPosition.x - 1) / gridSize.x
    local yNorm = (gridPosition.y - 1) / gridSize.y
    local position = {
        x = (xNorm - 0.5) * gridSize.x,
        y = 0.8,
        z = (yNorm - 0.5) * gridSize.y
    }

	return Game.makeActor {
		Name = "Key."..gridPosition.x.."."..gridPosition.y,
		Transform = {
			position = position,
			scale = {0.9 * 0.5, 0.2, 0.9 * 0.5}
		},
		RenderInfo = {
			mesh = "models/cube_flat.obj",
			material = {
				diffuseColor = color
			}
		}
	}
end

local function makeGoal(gridPosition, color)
	local xNorm = (gridPosition.x - 1) / gridSize.x
    local yNorm = (gridPosition.y - 1) / gridSize.y
    local position = {
        x = (xNorm - 0.5) * gridSize.x,
        y = 0.6,
        z = (yNorm - 0.5) * gridSize.y
    }

	return Game.makeActor {
		Name = "Key."..gridPosition.x.."."..gridPosition.y,
		Transform = {
			position = position,
			scale = {0.9 * 0.5, 0.5, 0.9 * 0.5}
		},
		RenderInfo = {
			mesh = "models/cube_flat.obj",
			material = {
				diffuseColor = color
			}
		}
	}
end

local function activateGoal(gridPosition)
	local goal = getGridAt(gridPosition).goal
	if not goal.isEnabled then
		return
	end

	if goal.isActivated then
		return
	end

	goal.isActivated = true
	Game.loadScene("assets/scripts/scenes/level.lua")
	print("activating goal")
end


local function activateButton(gridPosition)
	local button = getGridAt(gridPosition).button

	if(button.isActivated) then
		return
	end

	button.isActivated				= true
	button.actionTarget.isEnabled	= true

	local buttonPosition		= button.transform.position
	buttonPosition.y			= buttonPosition.y - 0.5
	button.transform.position	= buttonPosition

	local actionTargetPosition = button.actionTarget.transform.position
	actionTargetPosition.y = actionTargetPosition.y + 0.5

	button.actionTarget.transform.position = actionTargetPosition
	print("Button activated")
end

local function disableButton(gridPosition)
	local button = getGridAt(gridPosition).button

	if(not button.isActivated) then
		return
	end

	-- if there is one key left on the droppable button don't do the animation
	for k, v in pairs(getDroppedKeysGridAt(gridPosition).hasKeyDropped) do
		if(v == true) then
			return
		end
	end

	button.isActivated				= false
	button.actionTarget.isEnabled	= false

	local buttonPosition		= button.transform.position
	buttonPosition.y			= buttonPosition.y + 0.5
	button.transform.position	= buttonPosition

	local actionTargetPosition = button.actionTarget.transform.position
	actionTargetPosition.y = actionTargetPosition.y - 0.5

	button.actionTarget.transform.position = actionTargetPosition

	print("Button Deactivated")
end

local function blockKey(key)
	print(key.." key blocked")
	disabledKeys[key] = true
	getDroppedKeysGridAt(player.gridPosition).hasKeyDropped[key] = true

	local pair = {}
	pair[key] = makeKey(player.gridPosition, key)

	local tempArray = getDroppedKeysGridAt(player.gridPosition).keys
	getDroppedKeysGridAt(player.gridPosition).keys [#tempArray+1] = pair

	player.transform.position = getPlayerPositionFromGridPosition(player.gridPosition)
end

local function unblockKey(key)
	print(key.." key unblocked")

	disabledKeys[key] = false
	getDroppedKeysGridAt(player.gridPosition).hasKeyDropped[key] = false

	for k, v in pairs(getDroppedKeysGridAt(player.gridPosition).keys) do
		local currentActor = v[key]
		if(currentActor ~= nil) then
			currentActor:destroy()
			currentActor = nil
			v[key] = nil
			break
		end
	end

	local index = 0

	for k, v in pairs(getDroppedKeysGridAt(player.gridPosition).keys) do
		for m, p in pairs(v) do
			if (p) then
				local xNorm = (player.gridPosition.x - 1) / gridSize.x
				local yNorm = (player.gridPosition.y - 1) / gridSize.y

				local position = {
					x = (xNorm - 0.5) * gridSize.x,
					y = 1 + (index * 2 * p:get("Transform").scale.y),
					z = (yNorm - 0.5) * gridSize.y
				}

				index = index + 1
				p:get("Transform").position = position 
			end
		end
	end

	player.transform.position = getPlayerPositionFromGridPosition(player.gridPosition)
end

local scene = {}

function scene.start()

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
    for x = 1,gridSize.x do
        for y = 1,gridSize.y do
			local gridPosition = { x = x, y = y}
            grid[x][y].tile = makeTile(gridPosition)
			if grid[x][y].isObstacle then
				makeObstacle(gridPosition)
			end
			if grid[x][y].isButton then

				local buttonActor =  makeButton(gridPosition, {1, 0.2, 0.5})
				local actionTargetPosition = { x = 8, y= 8}
				local actionTargetActor = makeGoal(actionTargetPosition, {0, 0, 1})

				grid[x][y].button = {
					actor = buttonActor,
					transform = buttonActor:get("Transform"),
					actionTarget = {
						actor = actionTargetActor,
						transform = actionTargetActor:get("Transform"),
						isEnabled = false,
						isActivated = false
					},
					isActivated = false
				}

				grid[actionTargetPosition.x][actionTargetPosition.y].isGoal = true
				grid[actionTargetPosition.x][actionTargetPosition.y].goal = grid[x][y].button.actionTarget
			end
        end
    end

    local playerActor = Game.makeActor {
        Name = "Player",
        Transform = {
            position = getPlayerPositionFromGridPosition(playerStartPosition),
            scale = {0.3, 0.5, 0.3}
        },
        RenderInfo = {
            mesh = "models/cube_flat.obj",
            material = {
                diffuseColor = {0.5, 0, 0}
            }
        }
    }

    player = {
        actor = playerActor,
        transform = playerActor:get("Transform"),
        gridPosition = { x = playerStartPosition.x, y = playerStartPosition.y },
		lastPosition = { x = playerStartPosition.x, y = playerStartPosition.y }
    }
end

local function wobbleGrid()

    require('math')
    for x = 1,gridSize.x do
        for y = 1,gridSize.y do
            local xNorm = (x - 1) / gridSize.x
            local yNorm = (y - 1) / gridSize.y
            local position = {
                x = (xNorm - 0.5) * gridSize.x,
                y = 1,
                z = (yNorm - 0.5) * gridSize.y
            }

            grid[x][y].tile:get("Transform").position = Vector.from({0, -1 + math.sin(xNorm * (1 - yNorm) * 2 * 3.14 + Game.getTime()), 0}):add(position)
        end
    end
end

function scene.update()

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
		Game.loadScene("assets/scripts/scenes/level.lua")
		return
	end

	if Game.keyboard.isHeld("LShift") or Game.keyboard.isHeld("RShift") then
		for key, value in pairs(inputKeys) do
			if(Game.keyboard.isDown(key)) then
				if (not getDroppedKeysGridAt(player.gridPosition).hasKeyDropped[key]) and not disabledKeys[key] then
					blockKey(key)
				elseif getDroppedKeysGridAt(player.gridPosition).hasKeyDropped[key] and disabledKeys[key] then
					unblockKey(key)
				end
				input = {x = 0, y = 0}
			end
		end
	end

    local nextPosition = {
        x = player.gridPosition.x - input.x,
        y = player.gridPosition.y - input.y
    }

    if nextPosition.x > gridSize.x then
        nextPosition.x = gridSize.x
    elseif nextPosition.x < 1 then
        nextPosition.x = 1
    end

    if nextPosition.y > gridSize.y then
        nextPosition.y = gridSize.y
    elseif nextPosition.y < 1 then
        nextPosition.y = 1
    end

	if not getGridAt(nextPosition).isObstacle then
		if nextPosition.x ~= player.gridPosition.x or nextPosition.y ~= player.gridPosition.y then
			player.lastPosition.x = player.gridPosition.x
			player.lastPosition.y = player.gridPosition.y

			player.gridPosition.x = nextPosition.x
			player.gridPosition.y = nextPosition.y

			if getGridAt(player.gridPosition).isButton then
				activateButton(player.gridPosition)
			end

			-- if the tile changed then we gotta check if there was a button and disable it
			if player.lastPosition.x ~= player.gridPosition.x or player.lastPosition.y ~= player.gridPosition.y then
				if(getGridAt(player.lastPosition).isButton) then
					disableButton(player.lastPosition)
				end
			end

			if getGridAt(player.gridPosition).isGoal then
				activateGoal(player.gridPosition)
			end

			player.transform.position = getPlayerPositionFromGridPosition(player.gridPosition)
		end
	end
end

return scene

