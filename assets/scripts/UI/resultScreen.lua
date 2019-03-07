require('assets/scripts/object')

ResultScreen = Object:new()

local stars = {}

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

local function lerp(a, b, t)
	return (1 - t) * a + t * b;
end

function ResultScreen:animateStar(actor, dt)

    local tf = actor:get("Transform")

	local temp = {x = tf.scale.x, y = tf.scale.y, z = tf.scale.z}

	temp.x = lerp(temp.x, 1, 2 * dt)
	temp.y = lerp(temp.y, 1, 2 * dt)
	temp.z = lerp(temp.z, 1, 2 * dt)

	tf.scale = temp
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
				texture	= "textures/button.png",
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					playSoundObject('audio/UIButtonSound.wav',0,false,60)
					Game.currentLevel = Game.currentLevel + 1

					-- this condition should be checked somewhere else
					-- ex: When the player finishes the last level the nextLevelButton
					-- should not be shown
					if Game.currentLevel > Game.maxLevel then
						return
					end

					Game.loadScene(Game.levels[Game.currentLevel].path)
				end
			end,

			--Mouse Over Start
			onMouseEnter = function(self, button)
				self.actor:get("Transform").scale = {1.2,1.2,1.2}
			end,

			onMouseLeave = function(self, button)
				self.actor:get("Transform").scale = {1,1,1}
			end
			--Mouse Over End
		}
	}

	nextLevelButton:get("LuaBehavior").level = self.level

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
				texture	= "textures/button.png",
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					playSoundObject('audio/UIButtonSound.wav',0,false,60)
					Game.loadScene(Config.startScene)
				end
			end,

			--Mouse Over Start
			onMouseEnter = function(self, button)
				self.actor:get("Transform").scale = {1.2,1.2,1.2}
			end,

			onMouseLeave = function(self, button)
				self.actor:get("Transform").scale = {1,1,1}
			end
			--Mouse Over End
		}
	}

	self.totalNumberOfStars = self:CalculateTotalStars()

	local anchorValue = 0.4
	local anchorStep = 0.1

	for i = 1, self.totalNumberOfStars do
		self:createStar(anchorValue,0.6,anchorValue,0.6)
		anchorValue = anchorValue + anchorStep
	end

	self:keepAspectRatio(mainMenuButton,125)
	self:keepAspectRatio(nextLevelButton,125)

	local entry = { level = "level"..Game.currentLevel, stars = self.totalNumberOfStars}

	local serializer = Game.serializer
	if serializer == nil then
		return
	end

	serializer:saveNewEntry(entry)
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