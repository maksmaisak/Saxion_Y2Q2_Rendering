require('assets/scripts/object')

ResultScreen = Object:new()

local stars = {}
local allowButtonControl = false

function ResultScreen:keepAspectRatio(actor , tHeight)

	local textureSize = actor:get("Sprite").textureSize

	local ratio = textureSize.x / textureSize.y
	local height = tHeight
	local width = height * ratio
	local minWidth = (width / 2) * -1
	local minHeight =  (height / 2) * -1
	actor:get("UIRect").offsetMin = { minWidth, minHeight }
	actor:get("UIRect").offsetMax = { width / 2, height / 2}
end

local function playSoundObject(filepath, offset, loop, volume)
	local music = Game.audio.getSound(filepath)
	music.playingOffset = music.duration * offset
    music.loop = loop
    music.volume = volume
    music:play()
end

function ResultScreen:createStar(aMinX,aMinY,aMaxX,aMaxY)
	
	local star = Game.makeActor{
		Name = "Star",
		Transform = {
			scale = {0, 0, 0},
			parent = "ResultPanel",
			rotation = {0,0, 180}
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

function ResultScreen:animateStar(actor, scaleTarget, rotationTarget, duration)

    local tf = actor:get("Transform")

	tf:tweenScale(scaleTarget, duration)
	tf:tweenRotation(rotationTarget, duration)
end

function ResultScreen:CalculateTotalStars()

	local undosUsed = self.level.undoCounts

	local totalNumberOfStars = 3
	for k, v in pairs(self.level.maxNumUndos or {}) do
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

	local mainMenuButton = Game.makeActor {
		Name = "MainMenuButton",
		Transform = {
			scale  = {1,1,1},
			parent = "ResultPanel"
		},
		Text = {
			font   = "fonts/kenyanCoffee.ttf",
			color  = {0, 0, 0, 1},
			string = "Main Menu"
        },
		UIRect = {
			anchorMin = {0.4, 0.45},
			anchorMax = {0.4, 0.45}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture	= "textures/buttonBackground.png",
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					if not allowButtonControl then return end
					playSoundObject('audio/UIButtonSound.wav',0,false,60)
					Game.loadScene(Config.startScene)
				end
			end,

			--Mouse Over Start
			onMouseEnter = function(self, button)
				if not allowButtonControl then return end
				self.actor:get("Transform").scale = {1.2,1.2,1.2}
			end,

			onMouseLeave = function(self, button)
				self.actor:get("Transform").scale = {1,1,1}
			end
			--Mouse Over End
		}
	}

	self:keepAspectRatio(mainMenuButton,64)

	if Game.currentLevel >= Game.maxLevel then
		local mainMenuButtonUIRect = mainMenuButton:get("UIRect")
		mainMenuButtonUIRect.anchorMin = {0.5,0.45}
		mainMenuButtonUIRect.anchorMax = {0.5,0.45}
	end

	if Game.currentLevel < Game.maxLevel then		
		local nextLevelButton = Game.makeActor {
			Name = "NextLevelButton",
			Transform = {
				scale  = {1,1,1},
				parent = "ResultPanel"
			},
			Text = {
				font   = "fonts/kenyanCoffee.ttf",
				color  = {0, 0, 0, 1},
				string = "Next Level"
			},
			UIRect = {
				anchorMin = {0.6, 0.45},
				anchorMax = {0.6, 0.45}
			},
			Sprite = {
				material = {
					shader	= "sprite",
					texture	= "textures/buttonBackground.png",
				}
			},
			LuaBehavior = {
				onMouseDown = function(self, button)
					if button == 1 then
						if not allowButtonControl then return end
						playSoundObject('audio/UIButtonSound.wav',0,false,60)
						Game.currentLevel = Game.currentLevel + 1
						Game.loadScene(Game.levels[Game.currentLevel].path)
					end
				end,

				--Mouse Over Start
				onMouseEnter = function(self, button)
					if not allowButtonControl then return end
					self.actor:get("Transform").scale = {1.2,1.2,1.2}
				end,

				onMouseLeave = function(self, button)
					self.actor:get("Transform").scale = {1,1,1}
				end
				--Mouse Over End
			}
		}

		nextLevelButton:get("LuaBehavior").level = self.level
		self:keepAspectRatio(nextLevelButton,64)
	end

	self.totalNumberOfStars = self:CalculateTotalStars()

	local anchorValue = 0.4
	local anchorStep = 0.1

	for i = 1, self.totalNumberOfStars do
		self:createStar(anchorValue,0.6,anchorValue,0.6)
		anchorValue = anchorValue + anchorStep
	end

	self.animationTargetScale	 = { x = 1, y = 1, z = 1 }
	self.animationTargetRotation = { x = 0, y = 0, z = 0 }
	self.animationDuration		 = 1
	 
	allowButtonControl	       = false
	self.animatedStarIndex     = 1
	self.nextAnimatedStartTime = 0
	self.animationTimer		   = 0
	self.maxAnimationTimer     = self.totalNumberOfStars * self.animationDuration + 0.05

	local entry = { level = "level"..Game.currentLevel, stars = self.totalNumberOfStars}

	local serializer = Game.serializer
	if serializer == nil then
		return
	end

	serializer:saveNewEntry(entry)
end

function ResultScreen:update(dt)
	self.animationTimer = self.animationTimer + dt

	local totalStars = self.totalNumberOfStars
	if self.animatedStarIndex <= totalStars and self.animationTimer >= self.nextAnimatedStartTime then	
		playSoundObject('audio/UIButtonSound.wav',0,false,60) -- TODO: replace this sound with the actual one
		self:animateStar(stars[self.animatedStarIndex], self.animationTargetScale, self.animationTargetRotation, self.animationDuration)
		self.animatedStarIndex     = self.animatedStarIndex + 1
		self.nextAnimatedStartTime = self.nextAnimatedStartTime + self.animationDuration
	end

	if self.animationTimer >= self.maxAnimationTimer and not allowButtonControl then
		playSoundObject('audio/UIButtonSound.wav',0,false,60) -- TODO: replace this sound with the actual one
		allowButtonControl = true
	end
end

function ResultScreen:activate()
	self:createResultPanel()
end

return function(o)
    return ResultScreen:new(o)
end