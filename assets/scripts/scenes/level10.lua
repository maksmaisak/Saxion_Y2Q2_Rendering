require('assets/scripts/level/level')

local materials = {
    {
        shader = 'pbr',
        albedo = 'objects/Player/Texture/Main_Character_01_AlbedoTransparency.png',
        metallicSmoothness = 'objects/Player/Texture/Main_Character_01_MetallicSmoothness.png',
        ao = 'objects/Player/Texture/Main_Character_01_AO.png',
        smoothnessMultiplier = 1,
        aoMultiplier = 1,
    },
    {
        shader = 'pbr',
        albedo = 'objects/tile/Blocks/FoundationBlock/Textures/AlbedoTransparency 1.png',
        metallicSmoothness = 'objects/tile/Blocks/FoundationBlock/Textures/MetallicSmoothness.png',
        ao = 'objects/tile/Blocks/FoundationBlock/Textures/Grayscale.png',
        smoothnessMultiplier = 1,
        aoMultiplier = 1,
    },
    {
        shader = 'pbr',
        albedo = 'objects/ExitFinish/Textures/AlbedoTransparency.png',
        metallicSmoothness = 'objects/ExitFinish/Textures/MetallicSmoothness.png',
        ao = 'objects/ExitFinish/Textures/Grayscale.png',
        smoothnessMultiplier = 1,
        aoMultiplier = 1,
    },
    {
        shader = 'pbr',
        albedo = 'objects/decorations/MenuFloor/Texture/UvMappedFlooring_initialShadingGroup_AlbedoTransparency.png',
        metallicSmoothness = 'objects/decorations/MenuFloor/Texture/UvMappedFlooring_initialShadingGroup_MetallicSmoothness.png',
        smoothnessMultiplier = 1,
        aoMultiplier = 1,
    },
    {
        shader = 'pbr',
        albedo = 'objects/tile/Blocks/TerrainBlockVar2/Texture/TerrainBlockV2_AlbedoTransparency.png',
        metallicSmoothness = 'objects/tile/Blocks/TerrainBlockVar2/Texture/TerrainBlockV2_MetallicSmoothness.png',
        ao = 'objects/tile/Blocks/TerrainBlockVar2/Texture/TerrainBlockV2_AO.png',
        smoothnessMultiplier = 1,
        aoMultiplier = 1,
    },
    {
        shader = 'pbr',
        albedo = 'objects/tile/Blocks/TerrainBlockVar3/Texture/TerrainBlockV3_AlbedoTransparency.png',
        metallicSmoothness = 'objects/tile/Blocks/TerrainBlockVar3/Texture/TerrainBlockV3_MetallicSmoothness.png',
        ao = 'objects/tile/Blocks/TerrainBlockVar3/Texture/TerrainBlockV3_AO.png',
        smoothnessMultiplier = 1,
        aoMultiplier = 1,
    },
    {
        shader = 'pbr',
        renderMode = 'cutout',
        albedo = 'objects/decorations/Plants/Material/Plant_All (3).tga',
        metallicMultiplier = 0,
        smoothnessMultiplier = 0,
        aoMultiplier = 1,
    },
    {
        shader = 'pbr',
        albedo = 'objects/tile/Blocks/TerrainBlockVar1/Texture/TerrainBlockV1_AlbedoTransparency.png',
        metallicSmoothness = 'objects/tile/Blocks/TerrainBlockVar1/Texture/TerrainBlockV1_MetallicSmoothness.png',
        ao = 'objects/tile/Blocks/TerrainBlockVar1/Texture/TerrainBlockV1_AO.png',
        smoothnessMultiplier = 1,
        aoMultiplier = 1,
    },
    {
        shader = 'pbr',
        albedo = 'objects/portal/PortalIn_AlbedoTransparency (7).png',
        metallicSmoothness = 'objects/portal/PortalIn_MetallicSmoothness.png',
        ao = 'objects/portal/PortalIn_AO.png',
        smoothnessMultiplier = 0,
        aoMultiplier = 1,
    },
    {
        shader = 'pbr',
        albedo = 'objects/tile/Blocks/TerrainBlockVar4/Texture/TerrainBlockV4_AlbedoTransparency.png',
        metallicSmoothness = 'objects/tile/Blocks/TerrainBlockVar4/Texture/TerrainBlockV4_MetallicSmoothness.png',
        ao = 'objects/tile/Blocks/TerrainBlockVar4/Texture/TerrainBlockV4_AO.png',
        smoothnessMultiplier = 1,
        aoMultiplier = 1,
    },
    {
        shader = 'pbr',
        albedo = 'objects/Door/Texture/Door_01_AlbedoTransparency 1.png',
        metallicSmoothness = 'objects/Door/Texture/Door_01_MetallicSmoothness.png',
        ao = 'objects/Door/Texture/Door_01_AO.png',
        smoothnessMultiplier = 1,
        aoMultiplier = 1,
    },
    {
        shader = 'pbr',
        albedo = 'objects/Door/Texture/DoorPilars_01_AlbedoTransparency 1.png',
        metallicSmoothness = 'objects/Door/Texture/DoorPilars_01_MetallicSmoothness.png',
        ao = 'objects/Door/Texture/DoorPilars_01_AO.png',
        smoothnessMultiplier = 1,
        aoMultiplier = 1,
    },
    {
        shader = 'pbr',
        albedo = 'objects/tile/ButtonTile/Texture/ButtonTile_AlbedoTransparency.png',
        metallicSmoothness = 'objects/tile/ButtonTile/Texture/ButtonTile_MetallicSmoothness.png',
        ao = 'objects/tile/ButtonTile/Texture/ButtonTile_AO.png',
        smoothnessMultiplier = 1,
        aoMultiplier = 1,
    },
}

local map = Map:new {
    gridSize = {x = 17, y = 17},
    grid = {
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}},
        {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}}
    }
}

local grid = map.grid

grid[1][8].tile = {
    Name = "Tile",
    Transform = {
        position = {-0.03571853, -2.980232E-08, 6.99319},
        rotation = {0, 179.9997, 0},
        children = {
            {
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                        },
                    }
                },
            },
        }
    },
}

grid[1][9].tile = {
    Name = "Tile 3",
    Transform = {
        position = {0, 0, 8},
        children = {
            {
                Name = "TerrainBlockV4",
                Transform = {
                    position = {0, -1, -0.146},
                    children = {
                        {
                            Name = "TerrainBlockV4LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar4/TerrainBlockV4.obj',
                                material = materials[10],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
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
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                        },
                    }
                },
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
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                        },
                    }
                },
            },
        }
    },
}

grid[2][2].tile = {
    Name = "Tile 1 (1)",
    Transform = {
        position = {1, 0, 1},
        children = {
            {
                Name = "TerrainBlockV2",
                Transform = {
                    position = {0, -1, -0.148},
                    children = {
                        {
                            Name = "TerrainBlockV2LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar2/TerrainBlockV2.obj',
                                material = materials[5],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[2][3].tile = {
    Name = "Tile",
    Transform = {
        position = {1.001, 0, 2},
        children = {
            {
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                        },
                    }
                },
            },
        }
    },
}

grid[2][4].tile = {
    Name = "Tile 3",
    Transform = {
        position = {1, 0, 3},
        children = {
            {
                Name = "TerrainBlockV4",
                Transform = {
                    position = {0, -1, -0.146},
                    children = {
                        {
                            Name = "TerrainBlockV4LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar4/TerrainBlockV4.obj',
                                material = materials[10],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[2][5].tile = {
    Name = "Tile (1)",
    Transform = {
        position = {1, 0, 4},
        children = {
            {
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar1/TerrainBlockV1.obj',
                                material = materials[8],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
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
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar1/TerrainBlockV1.obj',
                                material = materials[8],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[2][8].tile = {
    Name = "Tile 1",
    Transform = {
        position = {1, 0, 7},
        children = {
            {
                Name = "TerrainBlockV2",
                Transform = {
                    position = {0, -1, -0.148},
                    children = {
                        {
                            Name = "TerrainBlockV2LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar2/TerrainBlockV2.obj',
                                material = materials[5],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[2][9].tile = {
    Name = "Tile 3",
    Transform = {
        position = {1, 0, 8},
        children = {
            {
                Name = "TerrainBlockV4",
                Transform = {
                    position = {0, -1, -0.146},
                    children = {
                        {
                            Name = "TerrainBlockV4LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar4/TerrainBlockV4.obj',
                                material = materials[10],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[2][10].tile = {
    Name = "Tile 2",
    Transform = {
        position = {1, 0, 9},
        children = {
            {
                Name = "TerrainBlockV3",
                Transform = {
                    position = {0, -1, -0.337},
                    children = {
                        {
                            Name = "TerrainBlockV3LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar3/TerrainBlockV3.obj',
                                material = materials[6],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[3][1].tile = {
    Name = "Tile 2",
    Transform = {
        position = {2, 0, 0},
        children = {
            {
                Name = "TerrainBlockV3",
                Transform = {
                    position = {0, -1, -0.337},
                    children = {
                        {
                            Name = "TerrainBlockV3LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar3/TerrainBlockV3.obj',
                                material = materials[6],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[3][2].tile = {
    Name = "Tile 1",
    Transform = {
        position = {2, 0, 1},
        children = {
            {
                Name = "TerrainBlockV2",
                Transform = {
                    position = {0, -1, -0.148},
                    children = {
                        {
                            Name = "TerrainBlockV2LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar2/TerrainBlockV2.obj',
                                material = materials[5],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
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
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar1/TerrainBlockV1.obj',
                                material = materials[8],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[3][4].tile = {
    Name = "Tile 2",
    Transform = {
        position = {2, 0, 3},
        children = {
            {
                Name = "TerrainBlockV3",
                Transform = {
                    position = {0, -1, -0.337},
                    children = {
                        {
                            Name = "TerrainBlockV3LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar3/TerrainBlockV3.obj',
                                material = materials[6],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[3][5].tile = {
    Name = "Tile 3",
    Transform = {
        position = {2, 0, 4},
        children = {
            {
                Name = "TerrainBlockV4",
                Transform = {
                    position = {0, -1, -0.146},
                    children = {
                        {
                            Name = "TerrainBlockV4LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar4/TerrainBlockV4.obj',
                                material = materials[10],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[3][6].tile = {
    Name = "Tile 2",
    Transform = {
        position = {2, 0, 5},
        children = {
            {
                Name = "TerrainBlockV3",
                Transform = {
                    position = {0, -1, -0.337},
                    children = {
                        {
                            Name = "TerrainBlockV3LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar3/TerrainBlockV3.obj',
                                material = materials[6],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[3][8].tile = {
    Name = "Tile 2",
    Transform = {
        position = {2, 0, 7},
        children = {
            {
                Name = "TerrainBlockV3",
                Transform = {
                    position = {0, -1, -0.337},
                    children = {
                        {
                            Name = "TerrainBlockV3LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar3/TerrainBlockV3.obj',
                                material = materials[6],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[3][9].tile = {
    Name = "Tile 2",
    Transform = {
        position = {2, 0, 8},
        children = {
            {
                Name = "TerrainBlockV3",
                Transform = {
                    position = {0, -1, -0.337},
                    children = {
                        {
                            Name = "TerrainBlockV3LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar3/TerrainBlockV3.obj',
                                material = materials[6],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
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
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar1/TerrainBlockV1.obj',
                                material = materials[8],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[4][2].tile = {
    Name = "Tile (2)",
    Transform = {
        position = {3, 0, 1},
        children = {
            {
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar1/TerrainBlockV1.obj',
                                material = materials[8],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
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
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar1/TerrainBlockV1.obj',
                                material = materials[8],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
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
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar1/TerrainBlockV1.obj',
                                material = materials[8],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
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
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar1/TerrainBlockV1.obj',
                                material = materials[8],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[4][6].tile = {
    Name = "Tile 2",
    Transform = {
        position = {3, 0, 5},
        children = {
            {
                Name = "TerrainBlockV3",
                Transform = {
                    position = {0, -1, -0.337},
                    children = {
                        {
                            Name = "TerrainBlockV3LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar3/TerrainBlockV3.obj',
                                material = materials[6],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
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
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                        },
                    }
                },
            },
        }
    },
}

grid[4][8].tile = {
    Name = "Tile 1",
    Transform = {
        position = {3, 0, 7},
        children = {
            {
                Name = "TerrainBlockV2",
                Transform = {
                    position = {0, -1, -0.148},
                    children = {
                        {
                            Name = "TerrainBlockV2LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar2/TerrainBlockV2.obj',
                                material = materials[5],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[4][9].tile = {
    Name = "Tile 2",
    Transform = {
        position = {3, 0, 8},
        children = {
            {
                Name = "TerrainBlockV3",
                Transform = {
                    position = {0, -1, -0.337},
                    children = {
                        {
                            Name = "TerrainBlockV3LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar3/TerrainBlockV3.obj',
                                material = materials[6],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[4][10].tile = {
    Name = "Tile 2",
    Transform = {
        position = {3, 0, 9},
        children = {
            {
                Name = "TerrainBlockV3",
                Transform = {
                    position = {0, -1, -0.337},
                    children = {
                        {
                            Name = "TerrainBlockV3LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar3/TerrainBlockV3.obj',
                                material = materials[6],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[4][12].tile = {
    Name = "Tile 2",
    Transform = {
        position = {3, 0, 11},
        children = {
            {
                Name = "TerrainBlockV3",
                Transform = {
                    position = {0, -1, -0.337},
                    children = {
                        {
                            Name = "TerrainBlockV3LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar3/TerrainBlockV3.obj',
                                material = materials[6],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[4][13].tile = {
    Name = "Tile 2 (1)",
    Transform = {
        position = {3, 0, 12},
        children = {
            {
                Name = "TerrainBlockV3",
                Transform = {
                    position = {0, -1, -0.337},
                    children = {
                        {
                            Name = "TerrainBlockV3LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar3/TerrainBlockV3.obj',
                                material = materials[6],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[4][14].tile = {
    Name = "Tile 3",
    Transform = {
        position = {3, 0, 13},
        children = {
            {
                Name = "TerrainBlockV4",
                Transform = {
                    position = {0, -1, -0.146},
                    children = {
                        {
                            Name = "TerrainBlockV4LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar4/TerrainBlockV4.obj',
                                material = materials[10],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[4][15].tile = {
    Name = "Tile",
    Transform = {
        position = {3, 0, 14},
        children = {
            {
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar1/TerrainBlockV1.obj',
                                material = materials[8],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[4][16].tile = {
    Name = "Tile",
    Transform = {
        position = {3, 0, 15},
        children = {
            {
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar1/TerrainBlockV1.obj',
                                material = materials[8],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[4][17].tile = {
    Name = "Tile 1",
    Transform = {
        position = {3, 0, 16},
        children = {
            {
                Name = "TerrainBlockV2",
                Transform = {
                    position = {0, -1, -0.148},
                    children = {
                        {
                            Name = "TerrainBlockV2LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar2/TerrainBlockV2.obj',
                                material = materials[5],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
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
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar1/TerrainBlockV1.obj',
                                material = materials[8],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[5][9].tile = {
    Name = "Tile 1",
    Transform = {
        position = {4, 0, 8},
        children = {
            {
                Name = "TerrainBlockV2",
                Transform = {
                    position = {0, -1, -0.148},
                    children = {
                        {
                            Name = "TerrainBlockV2LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar2/TerrainBlockV2.obj',
                                material = materials[5],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[5][10].tile = {
    Name = "Tile 3",
    Transform = {
        position = {4, 0, 9},
        children = {
            {
                Name = "TerrainBlockV4",
                Transform = {
                    position = {0, -1, -0.146},
                    children = {
                        {
                            Name = "TerrainBlockV4LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar4/TerrainBlockV4.obj',
                                material = materials[10],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[5][11].tile = {
    Name = "Tile 2",
    Transform = {
        position = {4, 0, 10},
        children = {
            {
                Name = "TerrainBlockV3",
                Transform = {
                    position = {0, -1, -0.337},
                    children = {
                        {
                            Name = "TerrainBlockV3LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar3/TerrainBlockV3.obj',
                                material = materials[6],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[5][12].tile = {
    Name = "Tile 1",
    Transform = {
        position = {4, 0, 11},
        children = {
            {
                Name = "TerrainBlockV2",
                Transform = {
                    position = {0, -1, -0.148},
                    children = {
                        {
                            Name = "TerrainBlockV2LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar2/TerrainBlockV2.obj',
                                material = materials[5],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[5][13].tile = {
    Name = "Tile",
    Transform = {
        position = {4, 0, 12},
        children = {
            {
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar1/TerrainBlockV1.obj',
                                material = materials[8],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[5][14].tile = {
    Name = "Tile 1",
    Transform = {
        position = {4, 0, 13},
        children = {
            {
                Name = "TerrainBlockV2",
                Transform = {
                    position = {0, -1, -0.148},
                    children = {
                        {
                            Name = "TerrainBlockV2LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar2/TerrainBlockV2.obj',
                                material = materials[5],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[5][15].tile = {
    Name = "Tile",
    Transform = {
        position = {4, 0, 14},
        children = {
            {
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar1/TerrainBlockV1.obj',
                                material = materials[8],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[5][16].tile = {
    Name = "Tile",
    Transform = {
        position = {4, 0, 15},
        children = {
            {
                Name = "TerrainBlockV1",
                Transform = {
                    position = {0, -1, -0.3},
                    children = {
                        {
                            Name = "TerrainBlockV1LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar1/TerrainBlockV1.obj',
                                material = materials[8],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[5][17].tile = {
    Name = "Tile 1",
    Transform = {
        position = {4, 0, 16},
        children = {
            {
                Name = "TerrainBlockV2",
                Transform = {
                    position = {0, -1, -0.148},
                    children = {
                        {
                            Name = "TerrainBlockV2LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar2/TerrainBlockV2.obj',
                                material = materials[5],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[6][10].tile = {
    Name = "Tile 3 (1)",
    Transform = {
        position = {5, 0, 9},
        children = {
            {
                Name = "TerrainBlockV4",
                Transform = {
                    position = {0, -1, -0.146},
                    children = {
                        {
                            Name = "TerrainBlockV4LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar4/TerrainBlockV4.obj',
                                material = materials[10],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[6][11].tile = {
    Name = "Tile 3",
    Transform = {
        position = {5, 0, 10},
        children = {
            {
                Name = "TerrainBlockV4",
                Transform = {
                    position = {0, -1, -0.146},
                    children = {
                        {
                            Name = "TerrainBlockV4LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar4/TerrainBlockV4.obj',
                                material = materials[10],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[6][12].tile = {
    Name = "Tile 1",
    Transform = {
        position = {5, 0, 11},
        children = {
            {
                Name = "TerrainBlockV2",
                Transform = {
                    position = {0, -1, -0.148},
                    children = {
                        {
                            Name = "TerrainBlockV2LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar2/TerrainBlockV2.obj',
                                material = materials[5],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[6][13].tile = {
    Name = "Tile 2 (2)",
    Transform = {
        position = {5, 0, 12},
        children = {
            {
                Name = "TerrainBlockV3",
                Transform = {
                    position = {0, -1, -0.337},
                    children = {
                        {
                            Name = "TerrainBlockV3LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar3/TerrainBlockV3.obj',
                                material = materials[6],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[6][14].tile = {
    Name = "Tile 3",
    Transform = {
        position = {5, 0, 13},
        children = {
            {
                Name = "TerrainBlockV4",
                Transform = {
                    position = {0, -1, -0.146},
                    children = {
                        {
                            Name = "TerrainBlockV4LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar4/TerrainBlockV4.obj',
                                material = materials[10],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[6][15].tile = {
    Name = "Tile 3",
    Transform = {
        position = {5, 0, 14},
        children = {
            {
                Name = "TerrainBlockV4",
                Transform = {
                    position = {0, -1, -0.146},
                    children = {
                        {
                            Name = "TerrainBlockV4LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar4/TerrainBlockV4.obj',
                                material = materials[10],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[6][16].tile = {
    Name = "Tile 1",
    Transform = {
        position = {5, 0, 15},
        children = {
            {
                Name = "TerrainBlockV2",
                Transform = {
                    position = {0, -1, -0.148},
                    children = {
                        {
                            Name = "TerrainBlockV2LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar2/TerrainBlockV2.obj',
                                material = materials[5],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[6][17].tile = {
    Name = "Tile 3",
    Transform = {
        position = {5, 0, 16},
        children = {
            {
                Name = "TerrainBlockV4",
                Transform = {
                    position = {0, -1, -0.146},
                    children = {
                        {
                            Name = "TerrainBlockV4LowPoly1",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/tile/Blocks/TerrainBlockVar4/TerrainBlockV4.obj',
                                material = materials[10],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[2][5].obstacle = {
    Name = "PillarRight",
    Transform = {
        position = {1, 0, 4},
        children = {
            {
                Name = "DoorPilars_03",
                Transform = {
                    position = {1.281, 0, -0.003225},
                    children = {
                        {
                            Name = "DoorPilars_01",
                            Transform = {
                                rotation = {0, 89.99983, 0},
                            },
                            RenderInfo = {
                                mesh = 'objects/Door/DoorPilars_03.obj',
                                material = materials[12],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[3][8].obstacle = {
    Name = "PillarRight",
    Transform = {
        position = {2, 0, 7},
        children = {
            {
                Name = "DoorPilars_03",
                Transform = {
                    position = {1.281, 0, -0.003225},
                    children = {
                        {
                            Name = "DoorPilars_01",
                            Transform = {
                                rotation = {0, 89.99983, 0},
                            },
                            RenderInfo = {
                                mesh = 'objects/Door/DoorPilars_03.obj',
                                material = materials[12],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[4][5].obstacle = {
    Name = "PillarLeft",
    Transform = {
        position = {3, 0, 4},
        children = {
            {
                Name = "DoorPilars_02",
                Transform = {
                    position = {-1.305, -0.004, 0.02299982},
                    rotation = {0, 89.99984, 0},
                    children = {
                        {
                            Name = "DoorPilars_02",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/Door/DoorPilars_02.obj',
                                material = materials[12],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[4][12].obstacle = {
    Name = "PillarRight",
    Transform = {
        position = {3, 0, 11},
        children = {
            {
                Name = "DoorPilars_03",
                Transform = {
                    position = {1.281, 0, -0.003225},
                    children = {
                        {
                            Name = "DoorPilars_01",
                            Transform = {
                                rotation = {0, 89.99983, 0},
                            },
                            RenderInfo = {
                                mesh = 'objects/Door/DoorPilars_03.obj',
                                material = materials[12],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[4][15].obstacle = {
    Name = "Obstacle",
    Transform = {
        position = {3.000006, 0, 13.99999},
        rotation = {0, 179.9997, 0},
        children = {
            {
                Name = "FoundationBlock",
                Transform = {
                    position = {0.006759644, 0.01687413, -0.008},
                    children = {
                        {
                            Name = "TerrainBlockV3",
                            Transform = {
                                position = {0, 0, -0.36},
                                children = {
                                    {
                                        Name = "TerrainBlockV3LowPoly1",
                                        Transform = {
                                            position = {-0.3820662, 0, 0.3415085},
                                            rotation = {0, 89.99983, 0},
                                        },
                                    },
                                }
                            },
                        },
                    }
                },
            },
        }
    },
}

grid[5][8].obstacle = {
    Name = "PillarLeft",
    Transform = {
        position = {4, 0, 7},
        children = {
            {
                Name = "DoorPilars_02",
                Transform = {
                    position = {-1.305, -0.004, 0.02299982},
                    rotation = {0, 89.99984, 0},
                    children = {
                        {
                            Name = "DoorPilars_02",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/Door/DoorPilars_02.obj',
                                material = materials[12],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[5][16].obstacle = {
    Name = "Obstacle (1)",
    Transform = {
        position = {4, 0, 15},
        rotation = {0, 179.9997, 0},
        children = {
            {
                Name = "FoundationBlock",
                Transform = {
                    position = {0.006759644, 0.01687413, -0.008},
                    children = {
                        {
                            Name = "TerrainBlockV3",
                            Transform = {
                                position = {0, 0, -0.36},
                                children = {
                                    {
                                        Name = "TerrainBlockV3LowPoly1",
                                        Transform = {
                                            position = {-0.3820662, 0, 0.3415085},
                                            rotation = {0, 89.99983, 0},
                                        },
                                    },
                                }
                            },
                        },
                    }
                },
            },
        }
    },
}

grid[6][12].obstacle = {
    Name = "PillarLeft",
    Transform = {
        position = {5, 0, 11},
        children = {
            {
                Name = "DoorPilars_02",
                Transform = {
                    position = {-1.305, -0.004, 0.02299982},
                    rotation = {0, 89.99984, 0},
                    children = {
                        {
                            Name = "DoorPilars_02",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/Door/DoorPilars_02.obj',
                                material = materials[12],
                                isBatchingStatic = true
                            }
                        },
                    }
                },
            },
        }
    },
}

grid[6][15].obstacle = {
    Name = "Obstacle (2)",
    Transform = {
        position = {5.000006, 0, 14.00001},
        rotation = {0, 179.9997, 0},
        children = {
            {
                Name = "FoundationBlock",
                Transform = {
                    position = {0.006759644, 0.01687413, -0.008},
                    children = {
                        {
                            Name = "TerrainBlockV3",
                            Transform = {
                                position = {0, 0, -0.36},
                                children = {
                                    {
                                        Name = "TerrainBlockV3LowPoly1",
                                        Transform = {
                                            position = {-0.3820662, 0, 0.3415085},
                                            rotation = {0, 89.99983, 0},
                                        },
                                    },
                                }
                            },
                        },
                    }
                },
            },
        }
    },
}

grid[4][15].goal = {
    startActive = false,
    light = {
        Name = "Point Light",
        Transform = {
            position = {0, 1, 1},
        },
        Light = {
            kind = 'point',
            intensity = 6.283185,
            falloff = {1, 1, 0},
            color = {0, 1, 0, 1},
        }
    },
    actor = {
        Name = "LevelGoal",
        Transform = {
            position = {3, 0, 14},
            children = {
                {
                    Name = "ExitFinishModelLow",
                    Transform = {
                        position = {1, 0, 1},
                        rotation = {0, 179.9997, 0},
                        children = {
                            {
                                Name = "ExitFinishModelLow1",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/ExitFinish/ExitFinishModelLow.obj',
                                    material = materials[3],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
            }
        },
    }
}

grid[1][10].button = {
    targetPositions = {
        {x = 3, y = 5},
    },
    actor = {
        Name = "Button",
        Transform = {
            position = {0, 0.2, 9},
            scale = {0.3, 0.2, 0.3},
            children = {
                {
                    Name = "ButtonTile (1)",
                    Transform = {
                        position = {0, -5.66, 0},
                        scale = {3.333333, 5, 3.333333},
                        children = {
                            {
                                Name = "ButtonTile:Group59432",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/tile/ButtonTile/ButtonTile.obj',
                                    material = materials[13],
                                }
                            },
                        }
                    },
                },
            }
        },
    }
}

grid[2][1].button = {
    targetPositions = {
        {x = 5, y = 12},
    },
    actor = {
        Name = "Button (2)",
        Transform = {
            position = {1, 0.2, 0},
            scale = {0.3, 0.2, 0.3},
            children = {
                {
                    Name = "ButtonTile (1)",
                    Transform = {
                        position = {0, -5.66, 0},
                        scale = {3.333333, 5, 3.333333},
                        children = {
                            {
                                Name = "ButtonTile:Group59432",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/tile/ButtonTile/ButtonTile.obj',
                                    material = materials[13],
                                }
                            },
                        }
                    },
                },
            }
        },
    }
}

grid[4][7].button = {
    targetPositions = {
        {x = 4, y = 15},
        {x = 4, y = 8},
    },
    actor = {
        Name = "Button (1)",
        Transform = {
            position = {3, 0.2, 6},
            scale = {0.3, 0.2, 0.3},
            children = {
                {
                    Name = "ButtonTile (1)",
                    Transform = {
                        position = {0, -5.66, 0},
                        scale = {3.333333, 5, 3.333333},
                        children = {
                            {
                                Name = "ButtonTile:Group59432",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/tile/ButtonTile/ButtonTile.obj',
                                    material = materials[13],
                                }
                            },
                        }
                    },
                },
            }
        },
    }
}

grid[1][8].portal = {
    teleportPosition = {x = 2, y = 3},
    actor = {
        Name = "Portal (1)",
        Transform = {
            position = {-0.002718531, 0.5, 6.99319},
            rotation = {0, 179.9997, 0},
            children = {
                {
                    Name = "PortalTileIn",
                    Transform = {
                        position = {-0.049, -1.413, 0},
                        children = {
                            {
                                Name = "PortalTileOut:Group41898",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/portal/PortalTileIn.obj',
                                    material = materials[9],
                                }
                            },
                        }
                    },
                },
            }
        },
    }
}

grid[2][3].portal = {
    teleportPosition = {x = 1, y = 8},
    actor = {
        Name = "Portal",
        Transform = {
            position = {0.968, 0.5, 2},
            children = {
                {
                    Name = "PortalTileIn",
                    Transform = {
                        position = {-0.049, -1.413, 0},
                        children = {
                            {
                                Name = "PortalTileOut:Group41898",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/portal/PortalTileIn.obj',
                                    material = materials[9],
                                }
                            },
                        }
                    },
                },
            }
        },
    }
}

grid[3][5].door = {
    actor = {
        Name = "Door",
        Transform = {
            position = {2, 0, 4},
        },
    },
    swingLeft = {
        Name = "SwingLeft",
        Transform = {
            position = {0.5, 0, 0},
            children = {
                {
                    Name = "Door_01",
                    Transform = {
                        position = {-0.497, 0, -4.3889E-07},
                        rotation = {0, 270.0002, 0},
                        scale = {1, 1, 0.6418437},
                        children = {
                            {
                                Name = "Door_01",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/Door/Door_01.obj',
                                    material = materials[11],
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
                    Name = "Door_01 (1)",
                    Transform = {
                        position = {-0.04400003, 0, 0},
                        rotation = {0, 270.0002, 0},
                        scale = {1, 1, 0.6418437},
                        children = {
                            {
                                Name = "Door_01",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/Door/Door_01.obj',
                                    material = materials[11],
                                }
                            },
                        }
                    },
                },
            }
        },
    }
}

grid[4][8].door = {
    actor = {
        Name = "Door",
        Transform = {
            position = {3, 0, 7},
        },
    },
    swingLeft = {
        Name = "SwingLeft",
        Transform = {
            position = {0.5, 0, 0},
            children = {
                {
                    Name = "Door_01",
                    Transform = {
                        position = {-0.497, 0, -4.3889E-07},
                        rotation = {0, 270.0002, 0},
                        scale = {1, 1, 0.6418437},
                        children = {
                            {
                                Name = "Door_01",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/Door/Door_01.obj',
                                    material = materials[11],
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
                    Name = "Door_01 (1)",
                    Transform = {
                        position = {-0.04400003, 0, 0},
                        rotation = {0, 270.0002, 0},
                        scale = {1, 1, 0.6418437},
                        children = {
                            {
                                Name = "Door_01",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/Door/Door_01.obj',
                                    material = materials[11],
                                }
                            },
                        }
                    },
                },
            }
        },
    }
}

grid[5][12].door = {
    actor = {
        Name = "Door",
        Transform = {
            position = {4, 0, 11},
        },
    },
    swingLeft = {
        Name = "SwingLeft",
        Transform = {
            position = {0.5, 0, 0},
            children = {
                {
                    Name = "Door_01",
                    Transform = {
                        position = {-0.497, 0, -4.3889E-07},
                        rotation = {0, 270.0002, 0},
                        scale = {1, 1, 0.6418437},
                        children = {
                            {
                                Name = "Door_01",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/Door/Door_01.obj',
                                    material = materials[11],
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
                    Name = "Door_01 (1)",
                    Transform = {
                        position = {-0.04400003, 0, 0},
                        rotation = {0, 270.0002, 0},
                        scale = {1, 1, 0.6418437},
                        children = {
                            {
                                Name = "Door_01",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/Door/Door_01.obj',
                                    material = materials[11],
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
                Name = "Main_Character",
                Transform = {
                    children = {
                        {
                            Name = "Main_Character2",
                            Transform = {
                            },
                            RenderInfo = {
                                mesh = 'objects/Player/Main_Character.obj',
                                material = materials[1],
                            }
                        },
                    }
                },
            },
        }
    },
}

local extras = {
    {
        Name = "Main Camera",
        Transform = {
            position = {-6.3, 12.88, -1.44},
            rotation = {315, 225, -2.414836E-06},
        },
        Camera = {
            isOrthographic = true,
            orthographicHalfSize = 7.44,
            nearPlaneDistance = 0.3,
            farPlaneDistance = 1000
        }
    },
    {
        Name = "Directional Light",
        Transform = {
            position = {0, 3, 0},
            rotation = {28.86, 124.461, 0},
        },
        Light = {
            kind = 'directional',
            intensity = 6.94292,
            falloff = {1, 1, 0},
            color = {1, 1, 1, 1},
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
                    Name = "vine_02",
                    Transform = {
                        position = {-2.43, 4.65, 17.68},
                        rotation = {347.8719, 269.9996, 8.514329E-05},
                        scale = {1.225201, 1.2891, 1},
                        children = {
                            {
                                Name = "vine_02",
                                Transform = {
                                    position = {-3.89, -1.28, -4.72},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/Plants/vine_02.obj',
                                    material = materials[7],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (46)",
                    Transform = {
                        position = {1.5, -0.5, 6},
                        rotation = {0, 90, 0},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (71)",
                    Transform = {
                        position = {-2, -0.5, 4.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (85)",
                    Transform = {
                        position = {-1, -1.49, 6},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "Flower_01",
                    Transform = {
                        position = {-1.56, -0.42, 8.49},
                        children = {
                            {
                                Name = "Flower_01",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/Plants/Flower_01.obj',
                                    material = materials[7],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "grass_02 (4)",
                    Transform = {
                        position = {-0.14, -0.408, 10.69},
                        rotation = {0, 6.011236, 0},
                        children = {
                            {
                                Name = "grass_02",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/Plants/grass_02.obj',
                                    material = materials[7],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "vine_01",
                    Transform = {
                        position = {1.63, -0.449, -2.31},
                        rotation = {0, 179.9996, 0},
                        scale = {0.66715, 0.66715, 0.66715},
                        children = {
                            {
                                Name = "vine_01",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/Plants/vine_01.obj',
                                    material = materials[7],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "vine_03",
                    Transform = {
                        position = {-3.56, -0.57, 10.32},
                        rotation = {0, 270.0002, 0},
                        children = {
                            {
                                Name = "vine_03",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/Plants/vine_03.obj',
                                    material = materials[7],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (47)",
                    Transform = {
                        position = {-0.5, -0.5, 6},
                        rotation = {0, 90, 0},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (72)",
                    Transform = {
                        position = {-3, -0.5, 7.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (73)",
                    Transform = {
                        position = {-3, -0.5, 9.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (74)",
                    Transform = {
                        position = {-4, -0.5, 8.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (48)",
                    Transform = {
                        position = {0.5, -0.5, 10},
                        rotation = {0, 90, 0},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (75)",
                    Transform = {
                        position = {0, -0.5, 10.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (76)",
                    Transform = {
                        position = {1, -0.5, 10.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (77)",
                    Transform = {
                        position = {-1, -0.5, 11.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (78)",
                    Transform = {
                        position = {0, -0.5, 12.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (79)",
                    Transform = {
                        position = {0, -0.5, 14.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (80)",
                    Transform = {
                        position = {0, -0.5, 16.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (81)",
                    Transform = {
                        position = {-2, -0.5, 2.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (82)",
                    Transform = {
                        position = {-2, -0.5, 0.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (49)",
                    Transform = {
                        position = {0.5, -0.5, -1},
                        rotation = {0, 90, 0},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (50)",
                    Transform = {
                        position = {2.5, -0.5, -1},
                        rotation = {0, 90, 0},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (51)",
                    Transform = {
                        position = {3.5, -0.5, 0},
                        rotation = {0, 90, 0},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (83)",
                    Transform = {
                        position = {2, -0.5, 1.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (84)",
                    Transform = {
                        position = {2, -0.5, 3.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (85)",
                    Transform = {
                        position = {3, -0.5, 2.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (86)",
                    Transform = {
                        position = {2, -0.5, 5.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (87)",
                    Transform = {
                        position = {3, -0.5, 4.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (52)",
                    Transform = {
                        position = {5.5, -0.5, 8},
                        rotation = {0, 90, 0},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (53)",
                    Transform = {
                        position = {7.5, -0.5, 4},
                        rotation = {0, 90, 0},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {-13, 0, -2},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (88)",
                    Transform = {
                        position = {3, -0.5, 6.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (89)",
                    Transform = {
                        position = {4, -0.5, 9.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (90)",
                    Transform = {
                        position = {4, -0.5, 11.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (91)",
                    Transform = {
                        position = {4, -0.5, 13.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (92)",
                    Transform = {
                        position = {4, -0.5, 15.5},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                    position = {2, 0, 0},
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "MenuFLoor_01 (54)",
                    Transform = {
                        position = {3.5, -0.5, 17},
                        rotation = {0, 90, 0},
                        children = {
                            {
                                Name = "Group5936",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/MenuFloor/MenuFLoor_01.obj',
                                    material = materials[4],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (86)",
                    Transform = {
                        position = {0, -1.49, 6},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (87)",
                    Transform = {
                        position = {0, -1.49, 5},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (88)",
                    Transform = {
                        position = {0, -1.49, 4},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (89)",
                    Transform = {
                        position = {0, -1.49, 3},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (90)",
                    Transform = {
                        position = {0, -1.49, 2},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (91)",
                    Transform = {
                        position = {0, -1.49, 1},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (92)",
                    Transform = {
                        position = {0, -1.49, 0},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (93)",
                    Transform = {
                        position = {0, -1.49, -1},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (94)",
                    Transform = {
                        position = {-1, -1.49, 7},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (95)",
                    Transform = {
                        position = {-1, -1.49, 8},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (96)",
                    Transform = {
                        position = {-2, -1.49, 8},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (97)",
                    Transform = {
                        position = {-2, -1.49, 9},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (98)",
                    Transform = {
                        position = {-1, -1.49, 10},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (99)",
                    Transform = {
                        position = {1, -1.49, 11},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (100)",
                    Transform = {
                        position = {1, -1.49, 12},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (101)",
                    Transform = {
                        position = {2, -1.49, 13},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (102)",
                    Transform = {
                        position = {2, -1.49, 14},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (103)",
                    Transform = {
                        position = {2, -1.49, 15},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (104)",
                    Transform = {
                        position = {2, -1.49, 16},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (105)",
                    Transform = {
                        position = {2, -1.49, 17},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (106)",
                    Transform = {
                        position = {1, -1.49, -1},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (107)",
                    Transform = {
                        position = {2, -1.49, -1},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (108)",
                    Transform = {
                        position = {3, -1.49, -1},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (109)",
                    Transform = {
                        position = {4, -1.49, 0},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (110)",
                    Transform = {
                        position = {5, -1.49, 2},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "FoundationBlock (111)",
                    Transform = {
                        position = {6, -1.49, 8},
                        children = {
                            {
                                Name = "TerrainBlockV3",
                                Transform = {
                                    position = {0, 0, -0.36},
                                    children = {
                                        {
                                            Name = "TerrainBlockV3LowPoly1",
                                            Transform = {
                                                position = {-0.3820662, 0, 0.3415085},
                                                rotation = {0, 89.99983, 0},
                                            },
                                            RenderInfo = {
                                                mesh = 'objects/tile/Blocks/FoundationBlock/TerrainBlockV3.obj',
                                                material = materials[2],
                                            }
                                        },
                                    }
                                },
                            },
                        }
                    },
                },
                {
                    Name = "grass_02 (5)",
                    Transform = {
                        position = {-2.14, -0.408, 5.69},
                        rotation = {0, 6.011236, 0},
                        children = {
                            {
                                Name = "grass_02",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/Plants/grass_02.obj',
                                    material = materials[7],
                                    isBatchingStatic = true
                                }
                            },
                        }
                    },
                },
                {
                    Name = "grass_01",
                    Transform = {
                        position = {5.331, -0.44, 3.47},
                        children = {
                            {
                                Name = "grass_01",
                                Transform = {
                                },
                                RenderInfo = {
                                    mesh = 'objects/decorations/Plants/grass_01.obj',
                                    material = materials[7],
                                    isBatchingStatic = true
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
            children = {
                {
                    Name = "Door",
                    Transform = {
                        position = {2, 0, 4},
                    },
                },
                {
                    Name = "Door (1)",
                    Transform = {
                        position = {3, 0, 7},
                    },
                },
                {
                    Name = "Door (2)",
                    Transform = {
                        position = {4, 0, 11},
                    },
                },
            }
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
    nextLevelPath = 'assets/scripts/scenes/level11.lua',
    maxNumUndos = {
        threeStars = 7,
        twoStars = 9,
        oneStar = 11
    }
}
