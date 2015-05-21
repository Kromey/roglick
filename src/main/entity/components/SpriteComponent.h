#ifndef SPRITECOMPONENT_H_
#define SPRITECOMPONENT_H_

/**
 * Data structure for a sprite component.
 *
 * Sprites are the visual representations of @link Entity Entities @endlink on
 * the screen, and include the ASCII character representation, any special
 * attributes (bold, underline, etc.), and the color pair to use.
 */
typedef struct
{
	char c; ///< The character to render for this Entity
	int attributes; ///< Any attributes (e.g. bold) to apply
	int color; ///< The color pair to use for this Entity
} SpriteComponent;

#endif
