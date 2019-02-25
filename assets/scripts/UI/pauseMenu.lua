require('assets/scripts/object')

PauseMenu = Object:new()
local pauseCanvas

function PauseMenu:init()
	self:createPanel()
	self.resultPanel:get("UIRect").isEnabled = false
	--[[self:createPanel()
	self.pauseMenuPanel:get("UIRect").isEnabled = false--]]
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

function createStar(aMinX,aMinY,aMaxX,aMaxY)
	
	star = Game.makeActor{
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
end

function animateStar(actor)
    tf = actor:get("Transform")
	scale = 2

	tf.scale = {scale, scale, scale}
end

function PauseMenu:update(dt)
	animateStar(star)
end

function PauseMenu:createPanel()	
	
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

	createStar(0.4,0.5,0.4,0.5)
	createStar(0.5,0.5,0.5,0.5)
	createStar(0.6,0.5,0.6,0.5)

	animateStar(star)
	
	--[[self.pauseMenuPanel = Game.makeActor {
		Name = "PauseMenuPanel",
		Transform = {
			scale  = {1,1,1}
		},
		UIRect = {
			anchorMin = {0, 0},
			anchorMax = {1, 1}
		},
	}

	Game.makeActor {
		Name = "PauseText",
		Transform = {
			scale = {3,3,3},
			parent = "PauseMenuPanel"
		},
		UIRect = {
			anchorMin = {0, 0},
			anchorMax = {1, 1.5}
		},
		Text = {
			font = "fonts/Menlo.ttc",
			color = {0, 0, 1, 1},
			string = "PAUSED"
        }
	}

	local resumeButton = Game.makeActor {
		Name = "ResumeButton",
		Transform = {
			scale  = {1,1,1},
			parent = "PauseMenuPanel"
		},
		Text = {
			font   = "fonts/Menlo.ttc",
			color  = {0, 0, 0, 1},
			string = "RESUME"
        },
		UIRect = {
			anchorMin = {0.5, 0.6},
			anchorMax = {0.5, 0.6}
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
					pauseCanvas:get("UIRect").isEnabled = false
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

	local mainMenuButton = Game.makeActor {
		Name = "MainMenuButton",
		Transform = {
			scale  = {1,1,1},
			parent = "PauseMenuPanel"
		},
		Text = {
			font   = "fonts/Menlo.ttc",
			color  = {0, 0, 0, 1},
			string = "MAIN MENU"
        },
		UIRect = {
			anchorMin = {0.5, 0.4},
			anchorMax = {0.5, 0.4}
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

	pauseCanvas	= Game.find("PauseMenuPanel")

	keepAspectRatio(mainMenuButton,125)
	keepAspectRatio(resumeButton,125)--]]
end

function PauseMenu:activate()
	
	if not self.resultPanel:get("UIRect").isEnabled then
		self.resultPanel:get("UIRect").isEnabled = true
	else
		self.resultPanel:get("UIRect").isEnabled = false
	end

	--[[if not self.pauseMenuPanel:get("UIRect").isEnabled then
		self.pauseMenuPanel:get("UIRect").isEnabled = true
	else
		self.pauseMenuPanel:get("UIRect").isEnabled = false
	end--]]
end