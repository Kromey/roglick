from roglick.engine import colors
"""Argument sets for the Tile constructor to create pre-defined Tiles"""

WallTile = {'name': 'Wall', 'glyph': '#', 'is_passable': False, 'color_lit': colors.rope}
FloorTile = {'name': 'Floor', 'glyph': '.', 'is_passable': True, 'color_lit': colors.oiled_cedar}

