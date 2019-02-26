require('assets/scripts/object')

ResultScreen = Object:new()

function ResultScreen:init()
	self:crateResultPanel()
	self.resultPanel:get("UIRect").isEnabled = false
end

function createStar(aMinX,aMinY,aMaxX,aMaxY)
	
	local star = Game.makeActor{
		Name = "Star",
		Transform = {
			scale = {0.1,0.1,0.1},
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

	stars[#stars + 1] = star
end

function animateStar(actor)
    tf = actor:get("Transform")
	scale = 0.1 * Game.getTime()

	tf.scale = {scale, scale, scale}
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

function ResultScreen:crateResultPanel()

	self.resultPanel = Game.makeActor{
		Name = "ResultPanel",
		Transform = {
			scale = {1,1,1}
		},
		UIRect ={
			anchorMin = {0, 0},
			anchorMax = {1, 1}
		}
	}

	local anchorValue = 0.4
	local anchorStep = 0.1
	for i = 1, 3 do
		createStar(anchorValue,0.5,anchorValue,0.5)
		anchorValue = anchorValue + anchorStep
	end
	
end

function ResultScreen:activate()

end

function ResultScreen:update(dt)
	for i=1, #stars do
		animateStar(stars[i])
	end
end