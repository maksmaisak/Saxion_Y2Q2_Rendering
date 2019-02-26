require('assets/scripts/object')

ResultScreen = Object:new()

local stars = {}

function ResultScreen:keepAspectRatio(actor , theight)

	local textureSize = actor:get("Sprite").textureSize

	ratio = textureSize.x/textureSize.y
	local height = theight
	local width = height * ratio
	local minWidth = (width / 2) * -1
	local minHeight =  (height / 2) * -1
	actor:get("UIRect").offsetMin = { minWidth, minHeight }
	actor:get("UIRect").offsetMax = { width / 2, height / 2}
end

function ResultScreen:createStar(aMinX,aMinY,aMaxX,aMaxY)
	
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

	self:keepAspectRatio(star, 100)

	stars[#stars + 1] = star
end

function lerp(a, b, t)
	return (1 - t) * a + t * b;
end

function ResultScreen:animateStar(actor, dt)
    tf = actor:get("Transform")

	local temp = { x = tf.scale.x, y = tf.scale.y, z = tf.scale.z}

	temp.x = lerp(temp.x, 1, 2 * dt)
	temp.y = lerp(temp.y, 1, 2 * dt)
	temp.z = lerp(temp.z, 1, 2 * dt)

	tf.scale = temp
end

function ResultScreen:CalculateTotalStars()
	local undosUsed = self.level.undoCounts

	local totalNumberOfStars = 3
	for k, v in pairs(self.level.starsRating) do
		if undosUsed > v then
			totalNumberOfStars = totalNumberOfStars - 1
		end
	end
	return totalNumberOfStars
end

function ResultScreen:createResultPanel()

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

	self.totalNumberOfStars = self:CalculateTotalStars()

	local anchorValue = 0.4
	local anchorStep = 0.1

	for i = 1, self.totalNumberOfStars do
		self:createStar(anchorValue,0.5,anchorValue,0.5)
		anchorValue = anchorValue + anchorStep
	end
end

function ResultScreen:activate()
	self:createResultPanel()
end

function ResultScreen:update(dt)
	if self.totalNumberOfStars > 0 then
		for i=1, self.totalNumberOfStars do
			self:animateStar(stars[i], dt)
		end
	end
end

return function(o)
    return ResultScreen:new(o)
end