require('assets/scripts/level/level')

local materials = {
    {
        shader = 'lit',
        diffuseColor = {0.8, 0.8, 0.8, 1}
    },
    {
        shader = 'lit',
        diffuse = 'objects/tile/diffuse.png',
        diffuseColor = {1, 1, 1, 1}
    },
    {
        shader = 'lit',
        diffuseColor = {1, 0.9895964, 0.5707546, 1}
    },
    {
        shader = 'lit',
        diffuseColor = {1, 0, 0.7361612, 1}
    },
    {
        shader = 'lit',
        diffuseColor = {0.8, 0.8, 0.8, 1}
    },
    {
        shader = 'lit',
        diffuseColor = {0.8, 0.8, 0.8, 1}
    },
    {
        shader = 'lit',
        diffuseColor = {0, 0, 1, 1}
    },
    {
        shader = 'lit',
        diffuseColor = {1, 0, 0, 1}
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

grid[1][1].tile = {
    Name = "Tile",
    Transform = {
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[1][2].tile = {
    Name = "Tile",
    Transform = {
        position = {0, 0, 1},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

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
                    material = materials[2]
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
                    material = materials[2]
                }
            },
        }
    },
}

grid[2][1].tile = {
    Name = "Tile",
    Transform = {
        position = {1, 0, 0},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
                }
            },
        }
    },
}

grid[2][6].tile = {
    Name = "Tile",
    Transform = {
        position = {1, 0, 5},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[2][7].tile = {
    Name = "Tile (2)",
    Transform = {
        position = {1, 0, 6},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[2][8].tile = {
    Name = "Tile",
    Transform = {
        position = {1, 0, 7},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[2][9].tile = {
    Name = "Tile",
    Transform = {
        position = {1, 0, 8},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[2][10].tile = {
    Name = "Tile",
    Transform = {
        position = {1, 0, 9},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
                }
            },
        }
    },
}

grid[3][6].tile = {
    Name = "Tile",
    Transform = {
        position = {2, 0, 5},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[3][8].tile = {
    Name = "Tile (3)",
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
                }
            },
        }
    },
}

grid[4][6].tile = {
    Name = "Tile (1)",
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
                }
            },
        }
    },
}

grid[4][10].tile = {
    Name = "Tile",
    Transform = {
        position = {3, 0, 9},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[5][1].tile = {
    Name = "Tile",
    Transform = {
        position = {4, 0, 0},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
                }
            },
        }
    },
}

grid[6][1].tile = {
    Name = "Tile",
    Transform = {
        position = {5, 0, 0},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
                }
            },
        }
    },
}

grid[6][5].tile = {
    Name = "Tile",
    Transform = {
        position = {5, 0, 4},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[6][6].tile = {
    Name = "Tile",
    Transform = {
        position = {5, 0, 5},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
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
                    material = materials[2]
                }
            },
        }
    },
}

grid[6][8].tile = {
    Name = "Tile",
    Transform = {
        position = {5, 0, 7},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
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
                    material = materials[2]
                }
            },
        }
    },
}

grid[7][1].tile = {
    Name = "Tile",
    Transform = {
        position = {6, 0, 0},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
                }
            },
        }
    },
}

grid[7][5].tile = {
    Name = "Tile",
    Transform = {
        position = {6, 0, 4},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[7][6].tile = {
    Name = "Tile",
    Transform = {
        position = {6, 0, 5},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
                }
            },
        }
    },
}

grid[7][10].tile = {
    Name = "Tile",
    Transform = {
        position = {6, 0, 9},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[8][1].tile = {
    Name = "Tile",
    Transform = {
        position = {7, 0, 0},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
                }
            },
        }
    },
}

grid[8][5].tile = {
    Name = "Tile",
    Transform = {
        position = {7, 0, 4},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[8][6].tile = {
    Name = "Tile",
    Transform = {
        position = {7, 0, 5},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
                }
            },
        }
    },
}

grid[9][1].tile = {
    Name = "Tile",
    Transform = {
        position = {8, 0, 0},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[9][2].tile = {
    Name = "Tile",
    Transform = {
        position = {8, 0, 1},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[9][3].tile = {
    Name = "Tile",
    Transform = {
        position = {8, 0, 2},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[9][4].tile = {
    Name = "Tile",
    Transform = {
        position = {8, 0, 3},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[9][5].tile = {
    Name = "Tile",
    Transform = {
        position = {8, 0, 4},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[9][6].tile = {
    Name = "Tile",
    Transform = {
        position = {8, 0, 5},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
                }
            },
        }
    },
}

grid[9][10].tile = {
    Name = "Tile",
    Transform = {
        position = {8, 0, 9},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[10][1].tile = {
    Name = "Tile",
    Transform = {
        position = {9, 0, 0},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[10][2].tile = {
    Name = "Tile",
    Transform = {
        position = {9, 0, 1},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[10][3].tile = {
    Name = "Tile",
    Transform = {
        position = {9, 0, 2},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[10][4].tile = {
    Name = "Tile",
    Transform = {
        position = {9, 0, 3},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[10][5].tile = {
    Name = "Tile",
    Transform = {
        position = {9, 0, 4},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[10][6].tile = {
    Name = "Tile",
    Transform = {
        position = {9, 0, 5},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
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
                    material = materials[2]
                }
            },
        }
    },
}

grid[10][10].tile = {
    Name = "Tile",
    Transform = {
        position = {9, 0, 9},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.5, 0.5, 0.5},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[2]
                }
            },
        }
    },
}

grid[3][8].obstacle = {
    Name = "Obstacle (4)",
    Transform = {
        position = {2, 0.5, 6.98},
        children = {
            {
                Name = "cube_flat",
                Transform = {
                    scale = {0.45, 0.5, 0.45},
                    children = {
                        {
                            Name = "default",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/cube_flat.obj',
                                material = materials[1]
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[6][6].obstacle = {
    Name = "Obstacle (3)",
    Transform = {
        position = {5, 0.5, 4.98},
        children = {
            {
                Name = "cube_flat",
                Transform = {
                    scale = {0.45, 0.5, 0.45},
                    children = {
                        {
                            Name = "default",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/cube_flat.obj',
                                material = materials[1]
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[7][6].obstacle = {
    Name = "Obstacle",
    Transform = {
        position = {6, 0.5, 4.98},
        children = {
            {
                Name = "cube_flat",
                Transform = {
                    scale = {0.45, 0.5, 0.45},
                    children = {
                        {
                            Name = "default",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/cube_flat.obj',
                                material = materials[1]
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[9][6].obstacle = {
    Name = "Obstacle (1)",
    Transform = {
        position = {8, 0.5, 5},
        children = {
            {
                Name = "cube_flat",
                Transform = {
                    scale = {0.45, 0.5, 0.45},
                    children = {
                        {
                            Name = "default",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/cube_flat.obj',
                                material = materials[1]
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[10][6].obstacle = {
    Name = "Obstacle (2)",
    Transform = {
        position = {9, 0.5, 5},
        children = {
            {
                Name = "cube_flat",
                Transform = {
                    scale = {0.45, 0.5, 0.45},
                    children = {
                        {
                            Name = "default",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/cube_flat.obj',
                                material = materials[1]
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[2][10].goal = {
    Name = "LevelGoal",
    Transform = {
        position = {1, 0, 9},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, 0.5, 0},
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[7]
                }
            },
        }
    },
}

grid[3][6].button = {
    targetPosition = {x = 2, y = 10},
    actor = {
        Name = "Button",
        Transform = {
            position = {2, 0.2, 5},
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
                                    material = materials[4]
                                }
                            },
                        }
                    },
                },
            }
        },
    }
}

grid[5][2].button = {
    targetPosition = {x = 3, y = 2},
    actor = {
        Name = "Button (2)",
        Transform = {
            position = {4, 0.2, 1},
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
                                    material = materials[4]
                                }
                            },
                        }
                    },
                },
            }
        },
    }
}

grid[8][4].button = {
    targetPosition = {x = 8, y = 6},
    actor = {
        Name = "Button (1)",
        Transform = {
            position = {7, 0.2, 3},
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
                                    material = materials[4]
                                }
                            },
                        }
                    },
                },
            }
        },
    }
}

grid[4][2].portal = {
    teleportPosition = {x = 4, y = 10},
    actor = {
        Name = "Portal B",
        Transform = {
            position = {3, 0.5, 1},
            children = {
                {
                    Name = "sphere2",
                    Transform = {
                        scale = {0.4, 0.4, 0.4},
                        children = {
                            {
                                Name = "default",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/portal/sphere2.obj',
                                    material = materials[5]
                                }
                            },
                        }
                    },
                },
                {
                    Name = "Point Light",
                    Transform = {
                        position = {0, 1, 0},
                        scale = {0.3, 0.5, 0.3},
                    },
                    Light = {
                        kind = 'point',
                        intensity = 1.25,
                        color = {0.01408291, 1, 0, 1},
                    }
                },
            }
        },
    }
}

grid[4][10].portal = {
    teleportPosition = {x = 4, y = 2},
    actor = {
        Name = "Portal A",
        Transform = {
            position = {3, 0.5, 9},
            children = {
                {
                    Name = "sphere2",
                    Transform = {
                        scale = {0.4, 0.4, 0.4},
                        children = {
                            {
                                Name = "default",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/portal/sphere2.obj',
                                    material = materials[5]
                                }
                            },
                        }
                    },
                },
                {
                    Name = "Point Light",
                    Transform = {
                        position = {0, 1, 0},
                        scale = {0.3, 0.5, 0.3},
                    },
                    Light = {
                        kind = 'point',
                        intensity = 1.25,
                        color = {0.01408291, 1, 0, 1},
                    }
                },
            }
        },
    }
}

grid[8][6].door = {
    actor = {
        Name = "Door",
        Transform = {
            position = {7, 0, 5},
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
                                    material = materials[1]
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
                                    material = materials[1]
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
                                    material = materials[1]
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
                                    material = materials[1]
                                }
                            },
                        }
                    },
                },
            }
        },
    }
}

grid[3][2].laser = {
    direction = {x = 0, y = 1},
    actor = {
        Name = "Laser",
        Transform = {
            position = {2, 0, 1},
            children = {
                {
                    Name = "cube_flat",
                    Transform = {
                        rotation = {45, 0, 0},
                        scale = {0.4, 0.35, 0.35},
                        children = {
                            {
                                Name = "default",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/tile/cube_flat.obj',
                                    material = materials[1]
                                }
                            },
                        }
                    },
                },
            }
        },
    },
    beam = {
        Name = "Beam",
        Transform = {
            position = {0, 0.245, 0},
            scale = {1, 1, 8.5},
            children = {
                {
                    Name = "cube_flat",
                    Transform = {
                        position = {0, 0, 0.5},
                        scale = {0.2, 0.2, 0.5},
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

grid[7][5].player = {
    Name = "Player",
    Transform = {
        position = {6, 0, 4},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, 0.5, 0},
                    scale = {0.3, 0.5, 0.3},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[8]
                }
            },
        }
    },
}

local extras = {
    {
        Name = "Main Camera",
        Transform = {
            position = {-3.5, 12, -3.5},
            rotation = {315, 225, -2.414836E-06},
        },
        Camera = {
            isOrthographic = true,
            orthographicHalfSize = 8,
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
            children = {
                {
                    Name = "model",
                    Transform = {
                        position = {-1, 0, 10},
                        children = {
                            {
                                Name = "model",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/model.obj',
                                    material = materials[6]
                                }
                            },
                        }
                    },
                },
                {
                    Name = "model (1)",
                    Transform = {
                        position = {-1, 0, -1},
                        rotation = {0, 270, 0},
                        children = {
                            {
                                Name = "model",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/model.obj',
                                    material = materials[6]
                                }
                            },
                        }
                    },
                },
                {
                    Name = "model (2)",
                    Transform = {
                        position = {10, 0, 10},
                        rotation = {0, 89.99982, 0},
                        children = {
                            {
                                Name = "model",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/model.obj',
                                    material = materials[6]
                                }
                            },
                        }
                    },
                },
                {
                    Name = "model (3)",
                    Transform = {
                        position = {10, 0, -1},
                        rotation = {0, 179.9996, 0},
                        children = {
                            {
                                Name = "model",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/model.obj',
                                    material = materials[6]
                                }
                            },
                        }
                    },
                },
            }
        },
    },
    {
        Name = "Doors",
        Transform = {
        },
    },
    {
        Name = "Lasers",
        Transform = {
        },
    },
}

return Level:new {
    map = map,
    extras = extras,
    nextLevelPath = 'assets/scripts/scenes/level2.lua'
}
