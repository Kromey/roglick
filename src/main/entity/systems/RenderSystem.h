#ifndef RENDERSYSTEM_H_
#define RENDERSYSTEM_H_

#include "entity/systems/System.h"
#include "display/Display.h"

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
		 * This constructor allows you to set the Window it will render within.
		 *
		 * @param display Pointer to the Display
		 * @param win Window to draw the map in
		 */
		RenderSystem(Display* display, Window win);

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
		 * @param display Pointer to the Display
		 * @param win Window to draw the map in
		 */
		void setWindow(Display* display, Window win);

	private:
		/**
		 * Pointer to the Display we'll be rendering within.
		 */
		Display* _display;

		/**
		 * The Window we'll render within.
		 */
		Window _win;
};

#endif
