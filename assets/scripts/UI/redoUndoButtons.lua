require('assets/scripts/object')
require('assets/scripts/vector')
require('assets/scripts/Utility/uiUtilities')

RedoUndoButtons = Object:new()

function RedoUndoButtons:init()	
	self:createButtons()
end

function RedoUndoButtons:createButtons()

	local level = self.level

	self.redoUndoPanel = Game.makeActor {
		Name = "RedoUndoPanel",
		Transform = {},
		UIRect = {
			anchorMin = {0, 0},
			anchorMax = {1, 1}
		}
	}

	local function makeButton(name, texturePath, offset, update)

		local side = 80

		local child = Game.makeActor {
			Name = name.."_Image",
			Transform = {},
			UIRect = {},
			Sprite = {
				material = {
					shader	= "sprite",
					texture	= texturePath,
				}
			}
		}

		local actor = Game.makeActor {
			Name = name,
			Transform = { parent = self.redoUndoPanel },
			UIRect = {
				anchorMin = {0, 0.1},
				anchorMax = {0, 0.1},
				offsetMin = {-side * 0.5 + offset, -side * 0.5},
				offsetMax = { side * 0.5 + offset,  side * 0.5}
			},
			LuaBehavior = {
				start = function(self)

					self.transform = self.actor:get("Transform")
					self.uiRect    = self.actor:get("UIRect")

					self.imageActor     = child
					self.imageTransform = child:get("Transform")
					self.imageUIRect    = child:get("UIRect")
				end,
				update = update,
				onMouseEnter = function(self)
					self.imageActor:tweenComplete()
					self.imageTransform:tweenScale({1.2, 1.2, 1.2}, 0.05)
				end,
				onMouseLeave = function(self)
					self.imageActor:tweenComplete()
					self.imageTransform:tweenScale({1,1,1}, 0.05)
				end
			}
		}

		child:get("Transform").parent = actor
		return actor
	end

	self.undoButton = makeButton("UndoButton", "textures/Undo.png", 80, function(self, dt)

		if not level.player.canControl then
			return
		end

		if Game.keyboard.isDown('q') or (Game.mouse.isDown(1) and self.uiRect.isMouseOver) then

			self.imageActor:tweenComplete()
			self.imageTransform:tweenScale(Vector.mul(self.imageTransform.scale, 1.2), 0.2, Ease.punch)

			Config.audio.ui.buttonPress:play()
			level.player:undoMove()
		end
	end)

	self.redoButton = makeButton("RedoButton", "textures/Redo.png", 160, function(self, dt)

		if not level.player.canControl then
			return
		end

		if Game.keyboard.isDown('e') or (Game.mouse.isDown(1) and self.uiRect.isMouseOver) then

			self.imageActor:tweenComplete()
			self.imageTransform:tweenScale(Vector.mul(self.imageTransform.scale, 1.2), 0.2, Ease.punch)

			Config.audio.ui.buttonPress:play()
			level.player:redoMove()
		end
	end)
end