require ('assets/scripts/level/level')

local scenery = {
	{
		Name = "camera",
		Transform = {
			position = { x = 0, y = 0, z = 10 }
		},
		Camera = {},
	}
}

local scene = {}

function scene:start()
	
	Game.makeActors(scenery)

   	Game.makeActor {
		Name = "ButtonsPanel",
		Transform = {},
		UIRect = {
			anchorMin	= {0.4, 0.15},
			anchorMax	= {0.6, 0.85}
		}
	}

	Game.makeActor {
		Name = "StartButton",
		Transform = {
			parent = "ButtonsPanel"
		},
		UIRect = {
			anchorMin	= {0, 0.85},
			anchorMax	= {1, 1}
		},
		Sprite = {
			material = {
				shader		= "sprite",
				texture		= "textures/runicfloor.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					print("start")
					Game.loadScene(Level:new {
						definitionPath = Config.firstLevelDefinition
					})
				end
			end
		}
	}

	Game.makeActor {
		Name = "ChoseLevelButton",
		Transform = {
			parent = "ButtonsPanel"
		},
		UIRect = {
			anchorMin = {0, 0.65},
			anchorMax = {1, 0.8}
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
					Game.find("ButtonsPanel"):get("UIRect").isEnabled	= false
				end
			end
		}
	}

	Game.makeActor {
		Name = "CreditsButton",
		Transform = {
			parent = "ButtonsPanel"
		},
		UIRect = {
			anchorMin = {0, 0.45},
			anchorMax = {1, 0.6}
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
					Game.find("ButtonsPanel"):get("UIRect").isEnabled		= false
				end
			end
		}
	}

	Game.makeActor {
		Name = "Exitutton",
		Transform = {
			parent = "ButtonsPanel"
		},
		UIRect = {
			anchorMin = {0, 0.25},
			anchorMax = {1, 0.4}
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
					Game.find("ButtonsPanel"):get("UIRect").isEnabled		= false
				end
			end
		}
	}

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
end

return scene
