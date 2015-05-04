#ifndef RENDERSYSTEM_H_
#define RENDERSYSTEM_H_

#include "entity/systems/System.h"
#include "display/Window.h"

/**
 * System responsible for rendering @link Entity Entities @endlink in a Window
 * object.
 */
class RenderSystem : public System
{
	public:
		/**
		 * Default constructor.
		 */
		RenderSystem();
		/**
		 * This constructor allows you to set the Window object it will render
		 * within.
		 *
		 * @param win Pointer to the Window for rendering
		 */
		RenderSystem(Window* win);

		/**
		 * Render all @link Entity Entities  @endlink in the provided
		 * EntityManager.
		 *
		 * @param em Reference to the EntityManager
		 */
		virtual void execute(EntityManager& em);

		/**
		 * Set the Window that this System will render in.
		 *
		 * @param win Pointer to the Window for rendering
		 */
		void setWindow(Window* win);

	private:
		/**
		 * Pointer to the Window we'll be rendering within.
		 */
		Window* _win;
};

#endif
