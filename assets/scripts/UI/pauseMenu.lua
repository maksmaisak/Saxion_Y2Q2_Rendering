require('assets/scripts/object')

PauseMenu = Object:new()
local pauseCanvas

function PauseMenu:init()	
	self:createPanel()
	self.pauseMenuPanel:get("UIRect").isEnabled = false
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

local function playSoundObject(filepath, offset, loop, volume)
	local music = Game.audio.getSound(filepath)
	music.playingOffset = music.duration * offset
    music.loop = loop
    music.volume = volume
    music:play()
end

function PauseMenu:createPanel()	
	
	self.pauseMenuPanel = Game.makeActor {
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
			scale = {1,1,1},
			parent = "PauseMenuPanel"
		},
		UIRect = {
			anchorMin = {0.002, 0.002},
			anchorMax = {1.002, 1.5002}
		},
		Text = {
			font = "fonts/arcadianRunes.ttf",
			fontSize = 120,
			color = {25/255,14/255,4/255,0.8},
			string = "PAUSED"
        }
	}

	Game.makeActor {
		Name = "PauseText",
		Transform = {
			scale = {1,1,1},
			parent = "PauseMenuPanel"
		},
		UIRect = {
			anchorMin = {0, 0},
			anchorMax = {1, 1.5}
		},
		Text = {
			font = "fonts/arcadianRunes.ttf",
			fontSize = 120,
			color = {168/255,130/255,97/255,1},
			string = "PAUSED"
        }
	}

	self.resumeButton = Game.makeActor {
		Name = "ResumeButton",
		Transform = {
			scale  = {1,1,1},
			parent = "PauseMenuPanel"
		},
		Text = {
			font   = "fonts/arcadianRunes.ttf",
			fontSize = 40,
			color  = {0, 0, 0, 1},
			string = "Resume"
        },
		UIRect = {
			anchorMin = {0.5, 0.6},
			anchorMax = {0.5, 0.6}
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
					playSoundObject('audio/UIButtonSound.wav',0,false,60)
					pauseCanvas:get("UIRect").isEnabled = false
					self.player.canControl = true
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
			font   = "fonts/arcadianRunes.ttf",
			fontSize = 40,
			color  = {0, 0, 0, 1},
			string = "Main Menu"
        },
		UIRect = {
			anchorMin = {0.5, 0.5},
			anchorMax = {0.5, 0.5}
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

	pauseCanvas	= Game.find("PauseMenuPanel")

	keepAspectRatio(mainMenuButton,64)
	keepAspectRatio(self.resumeButton,64)
end

function PauseMenu:activate()

	if not self.pauseMenuPanel:get("UIRect").isEnabled then
		self.pauseMenuPanel:get("UIRect").isEnabled = true
	else
		self.pauseMenuPanel:get("UIRect").isEnabled = false
	end
end