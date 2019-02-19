require('assets/scripts/level/map')

return {
	map = Map:new { 
		gridSize = {x = 6, y = 9}
	},

	obstaclePositions = {
		{ x = 1, y = 2},
		{ x = 5, y = 5},
	},

	buttonPositions = {
		--{ x = 3, y = 3, actionTargetPosition = {x = 6, y = 6}}
	},

	playerStartPosition = {x = 2, y = 3},

	nextLevelDefinitionPath = 'assets/scripts/scenes/definition3.lua'
}