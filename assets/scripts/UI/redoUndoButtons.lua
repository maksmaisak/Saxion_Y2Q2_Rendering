require('assets/scripts/object')


RedoUndoButtons = Object:new()

function RedoUndoButtons:init()	
	self:createButtons()
end

local function playSoundObject(filepath, offset, loop, volume)
	local music = Game.audio.getSound(filepath)
	music.playingOffset = music.duration * offset
    music.loop = loop
    music.volume = volume
    music:play()
end

function RedoUndoButtons:createButtons()

	local level = self.level

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
			offsetMin = {-40,-40},
			offsetMax = {40,40}
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
						playSoundObject('audio/UIButtonSound.wav',0,false,60)
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
			anchorMin = {0.9, 0.1},
			anchorMax = {0.9, 0.1},
			offsetMin = {-40,-40},
			offsetMax = {40,40}
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
						playSoundObject('audio/UIButtonSound.wav',0,false,60)
						level.player:redoMove()
					end
				end
			end
		}
	}
end