require('assets/scripts/object')

TutorialScreen = Object:new()

function TutorialScreen:init()
	self:startTutorial()
end

function TutorialScreen:startTutorial()

	if not Game.currentLevel or Game.currentLevel > 2 then
		return
	end

	self.levelTutorial = Game.makeActor {
		Name = "LevelTutorial",
		Transform = {scale = {0,0,0}},
		UIRect = {
			anchorMin = {0, 0},
			anchorMax = {0, 1},
			offsetMin = {100,  60},
			offsetMax = {100, -60},
			pivot = {0.5, 1}
		}
	}

	local textActor = Game.makeActor {
		Name = "LevelTutorial",
		Transform = {
			scale = {1,1,1},
			parent = self.levelTutorial
		},
		Text = {
			font   = "fonts/arcadianRunes.ttf",
			fontSize = 40,
			color  = Config.textColors.primary,
			alignment = {0, 1},
			string = Game.currentLevel == 1 and "Arrow keys to move" or "Shift + Key\nto drop key"
		}
	}

	textActor:get("Transform"):tweenScale({1.1, 1.1, 1.1}, 0.5, Ease.punch):setLoopBounce()
end


