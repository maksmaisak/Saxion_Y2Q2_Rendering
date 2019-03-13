require('assets/scripts/object')


RedoUndoButtons = Object:new()

function RedoUndoButtons:init()	
	self:createButtons()
end

function RedoUndoButtons:createButtons()

	local level = self.level

	self.reduUndoPanel = Game.makeActor {
		Name = "ReduUndoPanel",
		Transform = {},
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
			anchorMin = {0, 0.1},
			anchorMax = {0, 0.1},
			offsetMin = {40,-40},
			offsetMax = {120,40}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture	= "textures/Undo.png",
			}
		},
		LuaBehavior = {
			update = function(self, dt)
				if level.player.canControl then
					if Game.keyboard.isHeld("q") or (Game.mouse.isHeld(1) and self.actor:get("UIRect").isMouseOver) then
						self.actor:get("Transform").scale = {1.2,1.2,1.2}
					else
						self.actor:get("Transform").scale = {1,1,1}
					end
				
					if Game.mouse.isDown(1) and self.actor:get("UIRect").isMouseOver then
						Config.audio.ui.buttonPress:play()
						level.player:undoMove()
					end
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
			anchorMin = {0, 0.1},
			anchorMax = {0, 0.1},
			offsetMin = {120,-40},
			offsetMax = {200,40}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture	= "textures/Redo.png",
			}
		},
		LuaBehavior = {
			update = function(self, dt)
				if level.player.canControl then
					if Game.keyboard.isHeld("e") or (Game.mouse.isHeld(1) and self.actor:get("UIRect").isMouseOver) then
						self.actor:get("Transform").scale = {1.2,1.2,1.2}
					else
						self.actor:get("Transform").scale = {1,1,1}
					end

					if Game.mouse.isDown(1) and self.actor:get("UIRect").isMouseOver then
						Config.audio.ui.buttonPress:play()
						level.player:redoMove()
					end
				end
			end
		}
	}
end