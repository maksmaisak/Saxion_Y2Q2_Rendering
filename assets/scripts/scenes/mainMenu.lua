local scenery = {
	{
		Name = "camera",
		Transform = {
		position = { x = 0, y = 0, z = 10 }
		},
		Camera = {},
	}
}

local scene ={}

function scene.start()

	Game.makeActors(scenery)

	Game.makeActor {
		Name = "MainPanel",
		Transform = {},
		UIRect = {
			anchorMin = {0,0},
			anchorMax = {1,1}
		},
		Sprite = {
			material = {
				shader		= "sprite",
				texture		= "textures/background.png"
			}
		}
	}

	Game.makeActor {
		Name = "StartButton",
		Transform = {
			parent = "MainPanel"
		},
		UIRect = {
			anchorMin	= {0.4, 0.75},
			anchorMax	= {0.6, 0.85},
		},
		Sprite = {
			material = {
				shader = "sprite",
				texture = "textures/runicfloor.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					Game.loadScene("assets/scripts/scenes/level.lua")
				end
			end
		}
	}

	Game.makeActor {
		Name = "ChoseLevelButton",
		Transform = {
			parent = "MainPanel"
		},
		UIRect = {
			anchorMin = {0.4, 0.6},
			anchorMax = {0.6, 0.7}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/runicfloor.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					self.actor:get("Sprite").isEnabled					= false
					Game.find("StartButton"):get("Sprite").isEnabled	= false
					Game.find("CreditsButton"):get("Sprite").isEnabled	= false
				end
			end
		}
	}

	Game.makeActor {
		Name = "CreditsButton",
		Transform = {
			parent = "MainPanel"
		},
		UIRect = {
			anchorMin = {0.4, 0.45},
			anchorMax = {0.6, 0.55}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/runicfloor.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					self.actor:get("Sprite").isEnabled						= false
					Game.find("StartButton"):get("Sprite").isEnabled		= false
					Game.find("ChoseLevelButton"):get("Sprite").isEnabled	= false
				end
			end
		}
	}
end

return scene
