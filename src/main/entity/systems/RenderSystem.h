#ifndef RENDERSYSTEM_H_
#define RENDERSYSTEM_H_

#include "entity/systems/System.h"
#include "display/Interface.h"

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
		 * @param iface Pointer to the Interface
		 * @param win Window to draw the map in
		 */
		RenderSystem(Interface* iface, Window win);

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
		 * @param iface Pointer to the Interface
		 * @param win Window to draw the map in
		 */
		void setWindow(Interface* iface, Window win);

	private:
		/**
		 * Pointer to the Interface we'll be rendering within.
		 */
		Interface* _iface;

		/**
		 * The Window we'll render within.
		 */
		Window _win;
};

#endif
