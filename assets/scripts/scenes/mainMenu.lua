require ('assets/scripts/level/level')

local isBlocked = false
local isChooseLevelOpened = false
local mainButtonPanel
local chooseLevelPanel
local creditsPanel
local levelIndex = 1
local numberOfLevels = 2
local ratio

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


function scene:start()
	
	Game.makeActors(scenery)

--Start Main Buttons Panel
   	Game.makeActor {
		Name = "MainButtonsPanel",
		Transform = {},
		UIRect = {
			anchorMin	= {0, 0},
			anchorMax	= {1, 1}
		}
	}

	local startButton = Game.makeActor {
		Name = "StartButton",
		Transform = {
			scale	= {1,1,1},
			parent	= "MainButtonsPanel"
		},
		Text = {
			font = "fonts/Menlo.ttc",
			color = {0, 0, 0, 1},
			string = "START"
        },
		UIRect = {
			anchorMin	= {0.5, 0.8},
			anchorMax	= {0.5, 0.8}
		},
		Sprite = {
			material = {
				shader		= "sprite",
				texture		= "textures/button.png",
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					Game.loadScene(Config.firstLevelDefinition)
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

	local chooseLevelButton = Game.makeActor {
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
			anchorMin = {0.5, 0.6},
			anchorMax = {0.5, 0.6}
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
					chooseLevelPanel:get("UIRect").isEnabled	= true
					mainButtonPanel:get("UIRect").isEnabled		= false
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

	local creditsButton = Game.makeActor {
		Name = "CreditsButton",
		Transform = {
			parent = "MainButtonsPanel"
		},
		UIRect = {
			anchorMin = {0.5, 0.4},
			anchorMax = {0.5, 0.4}
		},
		Text = {
			font = "fonts/Menlo.ttc",
			color = {0, 0, 0, 1},
			string = "CREDITS"
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
					creditsPanel:get("UIRect").isEnabled	= true
					mainButtonPanel:get("UIRect").isEnabled	= false
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

	local exitButton = Game.makeActor {
		Name = "ExitButton",
		Transform = {
			parent = "MainButtonsPanel"
		},
		UIRect = {
			anchorMin = {0.5, 0.2},
			anchorMax = {0.5, 0.2}
		},
		Text = {
			font = "fonts/Menlo.ttc",
			color = {0, 0, 0, 1},
			string = "EXIT"
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
--End Main Buttons Panel

--Start ChooseLevel Panel
	
	Game.makeActor {
		Name = "ChooseLevelPanel",
		Transform = {},
		UIRect = {
			anchorMin = {0, 0},
			anchorMax = {1, 1}
		},		
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/transparent.png"
			}
		},
	}
	
	local chooseLevelImage = Game.makeActor {
		Name = "ChooseLevelImage",
		Transform = {
			parent = "ChooseLevelPanel"
		},
		UIRect = {
			anchorMin = {0.5, 0.6},
			anchorMax = {0.5, 0.6}
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
							print("Is pressed right")
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
							print("Is pressed left")
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
			end,

			onMouseDown = function(self, button)
				if button == 1 then
					Game.loadScene(Level:new {
						definitionPath = "assets/scripts/scenes/definition"..levelIndex..".lua"
					})
					print("Loaded scene : " ..levelIndex)
				end
			end
		}
	}

	local backButtonChooseLevel = Game.makeActor {
		Name = "BackButtonChooseLevel",
		Transform = {
			parent = "ChooseLevelPanel"
		},
		UIRect = {
			anchorMin = {0.5, 0.1},
			anchorMax = {0.5, 0.1}
		},
		Text = {
			font = "fonts/Menlo.ttc",
			color = {0, 0, 0, 1},
			string = "BACK"
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
					print("Go back to main")
					mainButtonPanel:get("UIRect").isEnabled		= true
					chooseLevelPanel:get("UIRect").isEnabled	= false
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
--End ChooseLevel Panel

--Start Credits Panel

	Game.makeActor{
		Name = "CreditsPanel",
		Transform = {},
		UIRect = {
			anchorMin = {0.3, 0.2},
			anchorMax = {0.7, 1}
		},
		Text = {
			font	= "fonts/Menlo.ttc",
			color	= {0, 0, 0, 1},
			string	= "CREDITS"
        },
	}

	local backButtonCredits = Game.makeActor {
		Name = "BackButtonCredits",
		Transform = {
			parent = "CreditsPanel"
		},
		UIRect = {
			anchorMin = {0.5, -0.1},
			anchorMax = {0.5, -0.1}
		},
		Text = {
			font	= "fonts/Menlo.ttc",
			color	= {0, 0, 0, 1},
			string	= "BACK"
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
					creditsPanel:get("UIRect").isEnabled		= false
					mainButtonPanel:get("UIRect").isEnabled		= true
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


--End Credits Panel

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

	mainButtonPanel		= Game.find("MainButtonsPanel")
	chooseLevelPanel	= Game.find("ChooseLevelPanel")
	creditsPanel		= Game.find("CreditsPanel")

	creditsPanel:get("UIRect").isEnabled		= false
	chooseLevelPanel:get("UIRect").isEnabled	= false

	keepAspectRatio(chooseLevelImage,600)
	keepAspectRatio(startButton,125)
	keepAspectRatio(chooseLevelButton,125)
	keepAspectRatio(creditsButton,125)
	keepAspectRatio(exitButton,125)
	keepAspectRatio(backButtonChooseLevel,125)
	keepAspectRatio(backButtonCredits,125)
end

return scene
