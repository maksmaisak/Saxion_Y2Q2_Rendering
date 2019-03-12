require('assets/scripts/object')

HudArrows = Object:new()

function HudArrows:init()
	self.arrows = { up = {}, left = {}, down = { }, right = {}}
	print("Arrow size"..#self.arrows)
	self:createArrows()
end

function createArrow(offsetMin,offsetMax,texture)
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


function HudArrows:createArrows()
	self.hudArrowsPanel = Game.makeActor {
		Name = "ArrowsPanel",
		Transform = {},
		UIRect = {
			anchorMin = {0.1, 0.9},
			anchorMax = {0.1, 0.9},
			offsetMin = {0.0, -40},
			offsetMax = {0.0, -40}
		},
	}

	self.arrows["up"   ].actor  = createArrow({-40,0}  ,{40,80}, "textures/keyUp.png")
	self.arrows["left" ].actor  = createArrow({-120,-40},{-40,40},  "textures/keyLeft.png")
	self.arrows["down" ].actor  = createArrow({-40,-80},{40,0},  "textures/keyDown.png")
	self.arrows["right"].actor  = createArrow({40,-40}  ,{120,40}, "textures/keyRight.png")

end