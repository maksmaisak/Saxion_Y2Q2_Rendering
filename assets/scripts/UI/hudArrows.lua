require('assets/scripts/object')

HudArrows = Object:new()

local offset = 40

function HudArrows:init()
	self.arrows = {up = {}, left = {}, down = {}, right = {}}
	print("Arrow size"..#self.arrows)
	self:createArrows()
end

local function createArrow(offsetMin, offsetMax, texture)

	return Game.makeActor {
		Name = "Arrow",
		Transform = {
			parent = "ArrowsPanel",
		},
		UIRect = {
			anchorMin = {0,0},
			anchorMax = {0,0},
			offsetMin = offsetMin,
			offsetMax = offsetMax,
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture	= texture,
			}
		}
	}
end

function HudArrows:dropKey(key)

	local actor = self.arrows[key].actor
	actor:tweenKill()
	actor:get("Transform"):tweenScale({0,0,0}, 0.3, Ease.inOutQuart)
end

function HudArrows:pickUpKey(key)

	local actor = self.arrows[key].actor
	actor:tweenKill()
	actor:get("Transform"):tweenScale({1,1,1}, 0.3, Ease.inOutQuart)
end

function HudArrows:keyPressed(key)

	print('HudArrows:keyPressed('..key..')')
	local actor = self.arrows[key].actor
	actor:tweenComplete()
	actor:get("Transform"):tweenScale({1.2,1.2,1.2}, 0.2, Ease.punch)
end

function HudArrows:createArrows()

	self.hudArrowsPanel = Game.makeActor {
		Name = "ArrowsPanel",
		Transform = {},
		UIRect = {
			anchorMin = {0.9, 0.1},
			anchorMax = {0.9, 0.1},
			offsetMin = {0.0, -offset},
			offsetMax = {0.0, -offset}
		},
	}

	self.arrows["up"   ].actor  = createArrow({offset-40 , offset+40}, {offset+40 , offset+120}, "textures/keyUp.png"   )
	self.arrows["left" ].actor  = createArrow({offset-120, offset-40}, {offset-40 , offset+40 }, "textures/keyLeft.png" )
	self.arrows["down" ].actor  = createArrow({offset-40 , offset-40}, {offset+40 , offset+40 }, "textures/keyDown.png" )
	self.arrows["right"].actor  = createArrow({offset+40 , offset-40}, {offset+120, offset+40 }, "textures/keyRight.png")
end