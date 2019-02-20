require('assets/scripts/level/map')

local materials = {
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
        diffuse = 'objects/tile/diffuse.png',
        diffuseColor = {1, 1, 1, 1}
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[1][5].tile = {
    Name = "Tile",
    Transform = {
        position = {0, 0, 4},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[1][6].tile = {
    Name = "Tile",
    Transform = {
        position = {0, 0, 5},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[1][7].tile = {
    Name = "Tile",
    Transform = {
        position = {0, 0, 6},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[1][8].tile = {
    Name = "Tile",
    Transform = {
        position = {0, 0, 7},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[1][9].tile = {
    Name = "Tile",
    Transform = {
        position = {0, 0, 8},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[1][10].tile = {
    Name = "Tile",
    Transform = {
        position = {0, 0, 9},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[2][7].tile = {
    Name = "Tile",
    Transform = {
        position = {1, 0, 6},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[3][10].tile = {
    Name = "Tile",
    Transform = {
        position = {2, 0, 9},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[5][8].tile = {
    Name = "Tile",
    Transform = {
        position = {4, 0, 7},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[5][10].tile = {
    Name = "Tile",
    Transform = {
        position = {4, 0, 9},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[6][10].tile = {
    Name = "Tile",
    Transform = {
        position = {5, 0, 9},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, -0.5, 0},
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
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
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[3]
                }
            },
        }
    },
}

grid[4][1].obstacle = {
    Name = "Obstacle",
    Transform = {
        position = {3, 0.5, 0},
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
                                material = materials[2]
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[6][7].goal = {
    Name = "LevelGoal",
    Transform = {
        position = {5, 0, 6},
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, 0.5, 0},
                    scale = {0.45, 0.5, 0.45},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[4]
                }
            },
        }
    },
}

grid[2][4].button = {
    targetPosition = {x = 6, y = 7},
    actor = {
        Name = "Button",
        Transform = {
            position = {1, 0.2, 3},
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
grid[1][1].player = {
    Name = "Player",
    Transform = {
        children = {
            {
                Name = "Cube",
                Transform = {
                    position = {0, 0.5, 0},
                    scale = {0.3, 0.5, 0.3},
                },
                RenderInfo = {
                    mesh = 'objects/tile/cube_flat.obj',
                    material = materials[5]
                }
            },
        }
    },
}

return {
    map = map,
    nextLevel = ''
}
