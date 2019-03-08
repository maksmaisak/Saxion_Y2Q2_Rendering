require('assets/scripts/object')

HudArrows = Object:new()

function HudArrows:init()
	self.arrows = { up = {}, left = {}, down = { }, right = {}}
	print("Arrow size"..#self.arrows)
	self:createArrows()
end

function createArrow(rotation,offsetMin,offsetMax)
	return Game.makeActor {
		Name = "Arrow",
		Transform = {
			parent = "ArrowsPanel",
			rotation = rotation
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
				texture	= "textures/arrow.png",
			}
		}
	}
end

function HudArrows:dropKey(key)
	self.arrows[key].actor:tweenKill()
	self.arrows[key].actor:get("Transform"):tweenScale({0,0,0}, 0.3, Ease.inOutQuart)
end

function HudArrows:pickUpKey(key)
	self.arrows[key].actor:tweenKill()
	self.arrows[key].actor:get("Transform"):tweenScale({1,1,1}, 0.3, Ease.inOutQuart)
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

	self.arrows["up"   ].actor  = createArrow({0,0,0}  ,{-40,0}  ,{40,80})
	self.arrows["left" ].actor  = createArrow({0,0,90} ,{-80,-40},{0,40} )
	self.arrows["down" ].actor  = createArrow({0,0,180},{-40,-80},{40,0} )
	self.arrows["right"].actor  = createArrow({0,0,-90},{0,-40}  ,{80,40})

end