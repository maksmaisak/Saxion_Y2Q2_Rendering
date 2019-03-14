require('assets/scripts/object')

TutorialScreen = Object:new()

function TutorialScreen:init()
	self:startTutorial()
end

function TutorialScreen:startTutorial()

	if not Game.currentLevel or Game.currentLevel > 2 then
		return
	end

	local position = {40, -100}

	self.levelTutorial = Game.makeActor {
		Name = "LevelTutorial",
		Transform = {},
		UIRect = {
			anchorMin = {0, 1},
			anchorMax = {0, 1},
			offsetMin = position,
			offsetMax = position
		}
	}

	local textActor = Game.makeActor {
		Name = "LevelTutorial",
		Transform = {
			scale = {1,1,1},
			parent = self.levelTutorial
		},
		UIRect = {
			offsetMin = {0, 0},
			offsetMax = {500, 0}
		},
		Text = {
			font   = "fonts/arcadianRunes.ttf",
			fontSize = 40,
			color  = Config.textColors.primary,
			string = Game.currentLevel == 1 and "Arrow keys to move" or "Shift + Key\nto drop key"
		}
	}

	textActor:get("Transform"):tweenScale({1.1, 1.1, 1.1}, 0.5, Ease.punch):setLoopBounce()
end


