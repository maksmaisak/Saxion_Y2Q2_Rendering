require('assets/scripts/object')

ResultScreen = Object:new()

function ResultScreen:init()
	self:crateResultPanel()
	self.resultPanel:get("UIRect").isEnabled = false
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

local function createStar(aMinX,aMinY,aMaxX,aMaxY)
	
	local star = Game.makeActor{
		Name = "Star",
		Transform = {
			scale = {0.1,0.1,0.1}
			parent = "ResultPanel"
		},
		UIRect = {
			anchorMin = {aMinX, aMinY},
			anchorMax = {aMaxX, aMaxY}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture	= "textures/star.png",
			}
		}
	}

	keepAspectRatio(star, 100)
end

function ResultScreen:crateResultPanel()
	
	self.resultPanel = Game.makeActor{
		Name = "ResultPanel",
		Trasform = {
			scale = {1,1,1}
		},
		UIRect ={
			anchorMin = {0, 0},
			anchorMax = {1, 1}
		}
	}

	createStar(0.5,1,0.5,0)
	createStar(0.5,1,0.5,0)
	createStar(0.5,1,0.5,0)
end

function ResultScreen:activate()

end