require ('assets/scripts/level/level')

local isBlocked = false
local isChooseLevelOpened = false
local mainButtonPanel
local chooseLevelPanel
local levelIndex = 1
local numberOfLevels = 2




local scenery = {
	{
		Name = "Camera",
		Transform = {
			position = { x = 0, y = 0, z = 10 }
		},
		Camera = {},
	}
}

local scene = {}

function scene:start()
	
	Game.makeActors(scenery)

--Start Main Buttons Panel
   	Game.makeActor {
		Name = "MainButtonsPanel",
		Transform = {},
		UIRect = {
			anchorMin	= {0.4, 0.15},
			anchorMax	= {0.6, 0.85}
		}
	}

	Game.makeActor {
		Name = "StartButton",
		Transform = {
			parent = "MainButtonsPanel"
		},
		Text = {
			font = "fonts/Menlo.ttc",
			color = {0, 0, 0, 1},
			string = "START"
        },
		UIRect = {
			anchorMin	= {0, 0.85},
			anchorMax	= {1, 1}
		},
		Sprite = {
			material = {
				shader		= "sprite",
				texture		= "textures/button.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					Game.loadScene(Level:new {
						definitionPath = Config.firstLevelDefinition
					})
				end
			end
		}
	}

	Game.makeActor {
		Name = "ChooseLevelButton",
		Transform = {
			parent = "MainButtonsPanel"
		},
		Text = {
			font = "fonts/Menlo.ttc",
			color = {0, 0, 0, 1},
			string = "CHOOSE LEVEL"
        },
		UIRect = {
			anchorMin = {0, 0.65},
			anchorMax = {1, 0.8}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/button.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					isChooseLevelOpened = true
					mainButtonPanel:get("UIRect").isEnabled		= false
					chooseLevelPanel:get("UIRect").isEnabled	= true
				end
			end
		}
	}

	Game.makeActor {
		Name = "CreditsButton",
		Transform = {
			parent = "MainButtonsPanel"
		},
		UIRect = {
			anchorMin = {0, 0.45},
			anchorMax = {1, 0.6}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/button.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					mainButtonPanel:get("UIRect").isEnabled	= false
				end
			end
		}
	}

	Game.makeActor {
		Name = "ExitButton",
		Transform = {
			parent = "MainButtonsPanel"
		},
		UIRect = {
			anchorMin = {0, 0.25},
			anchorMax = {1, 0.4}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/button.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					mainButtonPanel:get("UIRect").isEnabled	= false
				end
			end
		}
	}
--End Main Buttons Panel

--Start ChoseLevel Panel
	
	Game.makeActor {
		Name = "ChooseLevelPanel",
		Transform = {},
		UIRect = {
			anchorMin = {0.2, 0.2},
			anchorMax = {0.8, 0.8}
		},		
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/level" .. levelIndex .. ".jpg"
			}
		},
		LuaBehavior = {
			update = function(self, dt)
				if(isChooseLevelOpened) then
					if(levelIndex < numberOfLevels) then
						if Game.keyboard.isDown("right") then
							print("is pressed right")
							levelIndex = levelIndex + 1
						
							if(levelIndex > numberOfLevels) then
								levelIndex = numberOfLevels
							end

							self.actor:remove("Sprite")
							self.actor:add("Sprite", {
								material = {
									shader	= "sprite",
									texture = "textures/level" .. levelIndex .. ".jpg"
								}
							})
						end
					end
					
					if(levelIndex > 1) then
						if Game.keyboard.isDown("left") then
							print("is pressed left")
							levelIndex = levelIndex - 1

							if(levelIndex < 1) then
								levelIndex = 1
							end

							self.actor:remove("Sprite")
							self.actor:add("Sprite", {
								material = {
									shader	= "sprite",
									texture = "textures/level" .. levelIndex .. ".jpg"
								}				
							})
						end
					end
				end
			end
		}
	}

	Game.makeActor {
		Name = "BackButtonChoseLevel",
		Transform = {
			parent = "ChooseLevelPanel"
		},
		UIRect = {
			anchorMin = {0.35, -0.25},
			anchorMax = {0.65, -0.05}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/button.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					isChooseLevelOpened = false
					chooseLevelPanel:get("UIRect").isEnabled	= false
					mainButtonPanel:get("UIRect").isEnabled		= true
				end
			end
		}
	}
--End ChoseLevel Panel

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

	mainButtonPanel = Game.find("MainButtonsPanel")
	chooseLevelPanel = Game.find("ChooseLevelPanel")

	chooseLevelPanel:get("UIRect").isEnabled	= false
end

return scene
