require('assets/scripts/level/level')

local materials = {
    {
        shader = 'pbr',
        metallicMultiplier = 0,
        smoothnessMultiplier = 0.5,
        aoMultiplier = 1,
        albedoColor = {1, 0, 0, 1}
    },
    {
        shader = 'pbr',
        metallicMultiplier = 0,
        smoothnessMultiplier = 0.5,
        aoMultiplier = 1,
        albedoColor = {0, 0, 1, 1}
    },
    {
        shader = 'pbr',
        metallicMultiplier = 0,
        smoothnessMultiplier = 0.5,
        aoMultiplier = 1,
        albedoColor = {1, 0, 0.7361612, 1}
    },
    {
        shader = 'pbr',
        albedo = 'objects/tile/diffuse.png',
        metallicMultiplier = 0,
        smoothnessMultiplier = 0.5,
        aoMultiplier = 1,
    },
    {
        shader = 'pbr',
        metallicMultiplier = 0,
        smoothnessMultiplier = 0,
        aoMultiplier = 1,
        albedoColor = {0.8, 0.8, 0.8, 1}
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

grid[1][3].tile = {
    Name = "Tile",
    Transform = {
        position = {0, 0, 2},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
                }
            },
        }
    },
}

grid[1][4].tile = {
    Name = "Tile",
    Transform = {
        position = {0, 0, 3},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
                }
            },
        }
    },
}

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
                    material = materials[4]
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
                    material = materials[4]
                }
            },
        }
    },
}

grid[2][4].tile = {
    Name = "Tile",
    Transform = {
        position = {1, 0, 3},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
                }
            },
        }
    },
}

grid[2][5].tile = {
    Name = "Tile",
    Transform = {
        position = {1, 0, 4},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
                }
            },
        }
    },
}

grid[3][1].tile = {
    Name = "Tile",
    Transform = {
        position = {2, 0, 0},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
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
                    material = materials[4]
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
                    material = materials[4]
                }
            },
        }
    },
}

grid[3][4].tile = {
    Name = "Tile",
    Transform = {
        position = {2, 0, 3},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
                }
            },
        }
    },
}

grid[3][5].tile = {
    Name = "Tile",
    Transform = {
        position = {2, 0, 4},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
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
                    material = materials[4]
                }
            },
        }
    },
}

grid[4][4].tile = {
    Name = "Tile",
    Transform = {
        position = {3, 0, 3},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
                }
            },
        }
    },
}

grid[4][5].tile = {
    Name = "Tile",
    Transform = {
        position = {3, 0, 4},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
                }
            },
        }
    },
}

grid[4][6].tile = {
    Name = "Tile",
    Transform = {
        position = {3, 0, 5},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
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
                    material = materials[4]
                }
            },
        }
    },
}

grid[4][8].tile = {
    Name = "Tile",
    Transform = {
        position = {3, 0, 7},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
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
                    material = materials[4]
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
                    material = materials[4]
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
                    material = materials[4]
                }
            },
        }
    },
}

grid[6][4].tile = {
    Name = "Tile",
    Transform = {
        position = {5, 0, 3},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
                }
            },
        }
    },
}

grid[7][2].tile = {
    Name = "Tile",
    Transform = {
        position = {6, 0, 1},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
                }
            },
        }
    },
}

grid[7][3].tile = {
    Name = "Tile",
    Transform = {
        position = {6, 0, 2},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
                }
            },
        }
    },
}

grid[7][4].tile = {
    Name = "Tile",
    Transform = {
        position = {6, 0, 3},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
                }
            },
        }
    },
}

grid[8][2].tile = {
    Name = "Tile",
    Transform = {
        position = {7, 0, 1},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
                }
            },
        }
    },
}

grid[8][3].tile = {
    Name = "Tile",
    Transform = {
        position = {7, 0, 2},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
                }
            },
        }
    },
}

grid[8][4].tile = {
    Name = "Tile",
    Transform = {
        position = {7, 0, 3},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
                }
            },
        }
    },
}

grid[4][8].goal = {
    startActive = true,
    actor = {
        Name = "LevelGoal",
        Transform = {
            position = {3, 0, 7},
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

grid[7][2].button = {
    targetPositions = {
        {x = 4, y = 6},
    },
    actor = {
        Name = "Button",
        Transform = {
            position = {6, 0.2, 1},
            scale = {0.3, 0.2, 0.3},
            children = {
                {
                    Name = "cube_flat",
                    Transform = {
                        children = {
                            {
                                Name = "default",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/tile/cube_flat.obj',
                                    material = materials[3]
                                }
                            },
                        }
                    },
                },
            }
        },
    }
}

grid[4][6].door = {
    actor = {
        Name = "Door",
        Transform = {
            position = {3, 0, 5},
            children = {
                {
                    Name = "cube_flat",
                    Transform = {
                        position = {-0.5, 0.5, 0},
                        scale = {0.1, 0.52, 0.2},
                        children = {
                            {
                                Name = "default",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/tile/cube_flat.obj',
                                    material = materials[5]
                                }
                            },
                        }
                    },
                },
                {
                    Name = "cube_flat (1)",
                    Transform = {
                        position = {0.5, 0.5, 0},
                        scale = {0.1, 0.52, 0.2},
                        children = {
                            {
                                Name = "default",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/tile/cube_flat.obj',
                                    material = materials[5]
                                }
                            },
                        }
                    },
                },
            }
        },
    },
    swingLeft = {
        Name = "SwingLeft",
        Transform = {
            position = {0.5, 0, 0},
            children = {
                {
                    Name = "cube_flat",
                    Transform = {
                        position = {-0.25, 0.5, 0},
                        scale = {0.25, 0.5, 0.09999999},
                        children = {
                            {
                                Name = "default",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/tile/cube_flat.obj',
                                    material = materials[5]
                                }
                            },
                        }
                    },
                },
            }
        },
    },
    swingRight = {
        Name = "SwingRight",
        Transform = {
            position = {-0.5, 0, 0},
            children = {
                {
                    Name = "cube_flat",
                    Transform = {
                        position = {0.25, 0.5, 0},
                        scale = {0.25, 0.5, 0.1},
                        children = {
                            {
                                Name = "default",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/tile/cube_flat.obj',
                                    material = materials[5]
                                }
                            },
                        }
                    },
                },
            }
        },
    }
}

grid[3][1].player = {
    Name = "Player",
    Transform = {
        position = {2, 0, 0},
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
            position = {-4.29, 10.77, -4.45},
            rotation = {315, 225, -2.414836E-06},
        },
        Camera = {
            isOrthographic = true,
            orthographicHalfSize = 3.78,
            nearPlaneDistance = 0.3,
            farPlaneDistance = 1000
        }
    },
    {
        Name = "Directional Light",
        Transform = {
            position = {0, 3, 0},
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
    map = map,
    extras = extras,
    nextLevelPath = 'assets/scripts/scenes/level3.lua',
    maxNumUndos = {
        threeStars = 2,
        twoStars = 5,
        oneStar = 10
    }
}
