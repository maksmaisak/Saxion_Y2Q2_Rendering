require('assets/scripts/level/level')

local materials = {
    {
        shader = 'lit',
        diffuseColor = {1, 0, 0, 1}
    },
    {
        shader = 'lit',
        diffuseColor = {0, 0, 1, 1}
    },
    {
        shader = 'lit',
        diffuse = 'objects/tile/diffuse.png',
        diffuseColor = {1, 1, 1, 1}
    },
}

local map = Map:new {
    gridSize = {x = 10, y = 10},
    grid = {
        {{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{}}
    }
}

local grid = map.grid

grid[2][2].tile = {
    Name = "Tile",
    Transform = {
        position = {1, 0, 1},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[2][3].tile = {
    Name = "Tile",
    Transform = {
        position = {1, 0, 2},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[3][2].tile = {
    Name = "Tile",
    Transform = {
        position = {2, 0, 1},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[3][3].tile = {
    Name = "Tile",
    Transform = {
        position = {2, 0, 2},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[3][7].tile = {
    Name = "Tile",
    Transform = {
        position = {2, 0, 6},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[3][8].tile = {
    Name = "Tile",
    Transform = {
        position = {2, 0, 7},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[3][9].tile = {
    Name = "Tile",
    Transform = {
        position = {2, 0, 8},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[4][1].tile = {
    Name = "Tile",
    Transform = {
        position = {3, 0, 0},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[4][2].tile = {
    Name = "Tile",
    Transform = {
        position = {3, 0, 1},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[4][3].tile = {
    Name = "Tile",
    Transform = {
        position = {3, 0, 2},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[4][7].tile = {
    Name = "Tile",
    Transform = {
        position = {3, 0, 6},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[4][9].tile = {
    Name = "Tile",
    Transform = {
        position = {3, 0, 8},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[5][2].tile = {
    Name = "Tile",
    Transform = {
        position = {4, 0, 1},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[5][3].tile = {
    Name = "Tile",
    Transform = {
        position = {4, 0, 2},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[5][4].tile = {
    Name = "Tile",
    Transform = {
        position = {4, 0, 3},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[5][5].tile = {
    Name = "Tile",
    Transform = {
        position = {4, 0, 4},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[5][6].tile = {
    Name = "Tile",
    Transform = {
        position = {4, 0, 5},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[5][7].tile = {
    Name = "Tile",
    Transform = {
        position = {4, 0, 6},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[5][9].tile = {
    Name = "Tile",
    Transform = {
        position = {4, 0, 8},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[6][2].tile = {
    Name = "Tile",
    Transform = {
        position = {5, 0, 1},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[6][3].tile = {
    Name = "Tile",
    Transform = {
        position = {5, 0, 2},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[6][7].tile = {
    Name = "Tile",
    Transform = {
        position = {5, 0, 6},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[6][9].tile = {
    Name = "Tile",
    Transform = {
        position = {5, 0, 8},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[7][7].tile = {
    Name = "Tile",
    Transform = {
        position = {6, 0, 6},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[7][8].tile = {
    Name = "Tile",
    Transform = {
        position = {6, 0, 7},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[7][9].tile = {
    Name = "Tile",
    Transform = {
        position = {6, 0, 8},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[8][7].tile = {
    Name = "Tile",
    Transform = {
        position = {7, 0, 6},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[8][8].tile = {
    Name = "Tile",
    Transform = {
        position = {7, 0, 7},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[8][9].tile = {
    Name = "Tile",
    Transform = {
        position = {7, 0, 8},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[8][10].tile = {
    Name = "Tile",
    Transform = {
        position = {7, 0, 9},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[9][7].tile = {
    Name = "Tile",
    Transform = {
        position = {8, 0, 6},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[9][8].tile = {
    Name = "Tile",
    Transform = {
        position = {8, 0, 7},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[9][9].tile = {
    Name = "Tile",
    Transform = {
        position = {8, 0, 8},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[10][7].tile = {
    Name = "Tile",
    Transform = {
        position = {9, 0, 6},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[10][8].tile = {
    Name = "Tile",
    Transform = {
        position = {9, 0, 7},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[10][9].tile = {
    Name = "Tile",
    Transform = {
        position = {9, 0, 8},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[8][10].goal = {
    startActive = true,
    actor = {
        Name = "LevelGoal",
        Transform = {
            position = {7, 0, 9},
            children = {
                {
                    Name = "Cube",
                    Transform = {
                        position = {0, 0.5, 0},
                        scale = {0.45, 0.5, 0.45},
                    },
                    RenderInfo = {
                        mesh = 'objects/tile/cube_flat.obj',
                        material = materials[2]
                    }
                },
            }
        },
    }
}

grid[4][1].player = {
    Name = "Player",
    Transform = {
        position = {3, 0, 0},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, 0.5, 0},
                    scale = {0.3, 0.5, 0.3},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[1]
                }
            },
        }
    },
}

local extras = {
    {
        Name = "Main Camera",
        Transform = {
            position = {-3.26, 10.81, -2.58},
            rotation = {315, 225, -2.414836E-06},
        },
        Camera = {
            isOrthographic = true,
            orthographicHalfSize = 5.36,
            nearPlaneDistance = 0.3,
            farPlaneDistance = 1000
        }
    },
    {
        Name = "Directional Light",
        Transform = {
            position = {1, 3, 2},
            rotation = {331.14, 235.539, -3.899392E-06},
        },
        Light = {
            kind = 'directional',
            intensity = 1,
            color = {1, 0.9568627, 0.8392157, 1},
        }
    },
    {
        Name = "LevelExporter",
        Transform = {
        },
    },
    {
        Name = "Tiles",
        Transform = {
        },
    },
    {
        Name = "Obstacles",
        Transform = {
        },
    },
    {
        Name = "Buttons",
        Transform = {
        },
    },
    {
        Name = "Portals",
        Transform = {
        },
    },
    {
        Name = "Decorations",
        Transform = {
        },
    },
    {
        Name = "Doors",
        Transform = {
        },
    },
}

return Level:new {
	starsRating = {
		threeStars = 2,
		twoStars = 5,
		oneStar = 10,
	},
    map = map,
    extras = extras,
    nextLevelPath = 'assets/scripts/scenes/level1.lua'
}
