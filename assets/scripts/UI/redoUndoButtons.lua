require('assets/scripts/object')

RedoUndoButtons = Object:new()

function RedoUndoButtons:init()	
	self:createButtons()
end

local function keepAspectRatio(actor , theight)
	local textureSize = actor:get("Sprite").textureSize

	ratio = textureSize.x/textureSize.y
	local height = theight
	local width = height * ratio
	local minWidth = (width / 2) * -1
	local minHeight =  (height / 2) * -1
	actor:get("UIRect").offsetMin = { minWidth, minHeight }
	actor:get("UIRect").offsetMax = { width / 2, height / 2}
end

function RedoUndoButtons:createButtons()
		
	self.reduUndoPanel = Game.makeActor {
		Name = "ReduUndoPanel",
		Transform = {
			scale  = {1,1,1}
		},
		UIRect = {
			anchorMin = {0, 0},
			anchorMax = {1, 1}
		},
	}

	self.undoButton = Game.makeActor {
		Name = "UndoButton",
		Transform = {
			parent = "ReduUndoPanel"
		},
		UIRect = {
			anchorMin = {0.1, 0.1},
			anchorMax = {0.1, 0.1},
			offsetMin = {-50,-50},
			offsetMax = {50,50}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture	= "textures/Undo.png",
			}
		},
		LuaBehavior = {
			update = function(self, dt)
				if Game.keyboard.isHeld("q") or (Game.mouse.isHeld(1) and self.actor:get("UIRect").isMouseOver) then
					self.actor:get("Transform").scale = {1.2,1.2,1.2}
				else
					self.actor:get("Transform").scale = {1,1,1}
				end
			end,
		}
	}

	self.redoButton = Game.makeActor {
		Name = "RedoButton",
		Transform = {
			parent = "ReduUndoPanel"
		},
		UIRect = {
			anchorMin = {0.9, 0.1},
			anchorMax = {0.9, 0.1},
			offsetMin = {-50,-50},
			offsetMax = {50,50}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture	= "textures/Redo.png",
			}
		},
		LuaBehavior = {
			update = function(self, dt)
				if Game.keyboard.isHeld("e") or (Game.mouse.isHeld(1) and self.actor:get("UIRect").isMouseOver) then
					self.actor:get("Transform").scale = {1.2,1.2,1.2}
				else
					self.actor:get("Transform").scale = {1,1,1}
				end
			end
		}
	}
end