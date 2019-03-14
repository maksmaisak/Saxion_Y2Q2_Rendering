require('assets/scripts/object')
require('assets/scripts/Utility/uiUtilities')

PauseMenu = Object:new()
local pauseCanvas

function PauseMenu:init()	
	self:createPanel()
	self.pauseMenuPanel:get("UIRect").isEnabled = false
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

	self.resumeButton = UIUtilities.makeButton("ResumeButton", "PauseMenuPanel", "Resume", {0.5, 0.6}, {0.5, 0.6}, "textures/buttonBackground.png", function(self)
		pauseCanvas:get("UIRect").isEnabled = false
		self.player.canControl = true
	end)

	local mainMenuButton = UIUtilities.makeButton("MainMenuButton", "PauseMenuPanel", "Main Menu", {0.5, 0.5}, {0.5, 0.5}, "textures/buttonBackground.png", function(self)
		Game.loadScene(Config.startScene)
	end)

	pauseCanvas	= Game.find("PauseMenuPanel")

	UIUtilities.keepAspectRatio(mainMenuButton   , 64)
	UIUtilities.keepAspectRatio(self.resumeButton, 64)
end

function PauseMenu:activate()

	if not self.pauseMenuPanel:get("UIRect").isEnabled then
		self.pauseMenuPanel:get("UIRect").isEnabled = true
	else
		self.pauseMenuPanel:get("UIRect").isEnabled = false
	end
end