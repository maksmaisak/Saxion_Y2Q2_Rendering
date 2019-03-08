require('assets/scripts/object')

HudArrows = Object:new()

function HudArrows:init()
	self.arrows = { up = {}, left = {}, down = { }, right = {}}
	print("Arrow size"..#self.arrows)
	self:createArrows()
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

function createArrow(rotation,anchorMin,anchorMax)
	return Game.makeActor {
		Name = "Arrow",
		Transform = {
			parent = "ArrowsPanel",
			rotation = rotation
		},
		UIRect = {
			anchorMin = anchorMin,
			anchorMax = anchorMax,
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
	self.arrows[key].actor:get("Transform"):tweenScale({0,0,0}, 0.3,Ease.inOutQuart)
end

function HudArrows:pickUpKey(key)
	self.arrows[key].actor:tweenKill()
	self.arrows[key].actor:get("Transform"):tweenScale({1,1,1}, 0.3,Ease.inOutQuart)
end


function HudArrows:createArrows()
	self.hudArrowsPanel = Game.makeActor {
		Name = "ArrowsPanel",
		Transform = {},
		UIRect = {
			anchorMin = {0, 0},
			anchorMax = {1, 1}
		},
	}

	self.arrows["up"].actor  = createArrow({0,0,0},{0.1,0.9},{0.1,0.9})
	self.arrows["left"].actor  = createArrow({0,0,90},{0.075,0.85},{0.075,0.85})
	self.arrows["down"].actor  = createArrow({0,0,180},{0.1,0.8},{0.1,0.8})
	self.arrows["right"].actor  = createArrow({0,0,-90},{0.125,0.85},{0.125,0.85})


	for k, v in pairs(self.arrows) do
		keepAspectRatio(self.arrows[k].actor, 90)
	end

end