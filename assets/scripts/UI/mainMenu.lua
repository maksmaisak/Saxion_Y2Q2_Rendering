require ('assets/scripts/level/level')


local isBlocked = false
local isChooseLevelOpened = false
local mainButtonsPanel
local chooseLevelPanel
local creditsPanel
local levelIndex = 1
local numberOfLevels = 2
local ratio
local buttonSize = 60

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

	IsMenuOpened = true

	Game.makeActors(scenery)

	-- Start Main Buttons Panel
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
			scale  = {1,1,1},
			parent = "MainButtonsPanel"
		},
		Text = {
			font   = "fonts/kenyanCoffee.ttf",
			fontSize = 50,
			color  = {1, 1, 1, 1},
			string = "Start"
        },
		UIRect = {
			anchorMin = {0.85, 0.32},
			anchorMax = {0.85, 0.32}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture	= "textures/transparent.png",
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					Game.loadScene(Config.firstLevelPath)
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
			font = "fonts/kenyanCoffee.ttf",
			fontSize = 50,
			color = {1, 1, 1, 1},
			string = "Choose Level"
        },
		UIRect = {
			anchorMin = {0.85, 0.24},
			anchorMax = {0.85, 0.24}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/transparent.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					isChooseLevelOpened = true
					chooseLevelPanel:get("UIRect").isEnabled = true
					mainButtonsPanel:get("UIRect").isEnabled = false
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
			anchorMin = {0.85, 0.16},
			anchorMax = {0.85, 0.16}
		},
		Text = {
			font = "fonts/kenyanCoffee.ttf",
			fontSize = 50,
			color = {1, 1, 1, 1},
			string = "Credits"
        },
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/transparent.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					creditsPanel:get("UIRect").isEnabled		= true
					mainButtonsPanel:get("UIRect").isEnabled	= false
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
			anchorMin = {0.85, 0.08},
			anchorMax = {0.85, 0.08}
		},
		Text = {
			font = "fonts/kenyanCoffee.ttf",
			fontSize = 50,
			color = {1, 1, 1, 1},
			string = "Exit"
        },
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/transparent.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					Game.quit()
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
					Game.loadScene("assets/scripts/scenes/level"..levelIndex..".lua")
					print("Loaded scene : " ..levelIndex)
				end
			end
		}
	}

	local arrowLeft = Game.makeActor {
		Name = "ArrowLeft",
		Transform = {
			parent = "ChooseLevelPanel"
		},
		UIRect = {
			anchorMin = {0.05, 0.6},
			anchorMax = {0.05, 0.6}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/arrowLeft.png"
			}
		},
		LuaBehavior = {
			update = function(self, dt)
				if Game.keyboard.isHeld("left") then
					self.actor:get("Transform").scale = {1.2,1.2,1.2}
				else
					self.actor:get("Transform").scale = {1,1,1}
				end
			end
		}
	}

	local arrowRight = Game.makeActor {
		Name = "ArrowRight",
		Transform = {
			parent = "ChooseLevelPanel"
		},
		UIRect = {
			anchorMin = {0.95, 0.6},
			anchorMax = {0.95, 0.6}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/arrowRight.png"
			}
		},
		LuaBehavior = {
			update = function(self, dt)
				if Game.keyboard.isHeld("right") then
					self.actor:get("Transform").scale = {1.2,1.2,1.2}
				else
					self.actor:get("Transform").scale = {1,1,1}
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
			font = "fonts/kenyanCoffee.ttf",
			fontSize = 50,
			color = {1, 1, 1, 1},
			string = "Back"
        },
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/transparent.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					isChooseLevelOpened = false
					print("Go back to main")
					mainButtonsPanel:get("UIRect").isEnabled = true
					chooseLevelPanel:get("UIRect").isEnabled = false
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
			anchorMin = {0, 0},
			anchorMax = {1, 1}
		},
		Text = {
			font	= "fonts/kenyanCoffee.ttf",
			fontSize = 50,
			color	= {1, 1, 1, 1},
			string	= "CREDITS"
        },
	}

	local backButtonCredits = Game.makeActor {
		Name = "BackButtonCredits",
		Transform = {
			parent = "CreditsPanel"
		},
		UIRect = {
			anchorMin = {0.5, 0.1},
			anchorMax = {0.5, 0.1}
		},
		Text = {
			font	= "fonts/kenyanCoffee.ttf",
			fontSize = 50,
			color	= {1, 1, 1, 1},
			string	= "Back"
        },
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/transparent.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					creditsPanel:get("UIRect").isEnabled	 = false
					mainButtonsPanel:get("UIRect").isEnabled = true
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
				shader	= "sprite",
				texture	= "textures/menuBackgrond.jpg"
			}
		}
	}

	mainButtonsPanel = Game.find("MainButtonsPanel")
	chooseLevelPanel = Game.find("ChooseLevelPanel")
	creditsPanel	 = Game.find("CreditsPanel")

	creditsPanel:get("UIRect").isEnabled	 = false
	chooseLevelPanel:get("UIRect").isEnabled = false

	keepAspectRatio(chooseLevelImage,500)
	keepAspectRatio(startButton,buttonSize)
	keepAspectRatio(chooseLevelButton,buttonSize)
	keepAspectRatio(creditsButton,buttonSize)
	keepAspectRatio(exitButton,buttonSize)
	keepAspectRatio(backButtonChooseLevel,buttonSize)
	keepAspectRatio(backButtonCredits,buttonSize)
	keepAspectRatio(arrowLeft,256)
	keepAspectRatio(arrowRight,256)

end

return scene
