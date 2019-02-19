require('assets/scripts/level/map')

return {
	map = Map:new { 
		gridSize = {x = 10, y = 10}
	},

	obstaclePositions = {
		{ x = 1, y = 2},
		{ x = 5, y = 5},
	},

	buttonPositions = {
		{ x = 3, y = 3, actionTargetPosition = { x = 8, y = 8}}
	},

	portalPositions = {
		{ x = 8, y = 4, teleportPosition = { x = 1, y = 3 }},
		{ x = 2, y = 4, teleportPosition = { x = 9, y = 5 }}
	},

	playerStartPosition = {x = 2, y = 3},

	nextLevelDefinitionPath = 'assets/scripts/scenes/definition2.lua'
}