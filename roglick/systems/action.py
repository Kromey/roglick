from roglick.engine.ecs import System
from roglick.components import FatigueComponent


class FatigueSystem(System):
    def execute(self):
        for entity, components in self._entity_manager.get_entities_with_component(
                FatigueComponent):
            fcomp = components[FatigueComponent]

            if fcomp.fatigue > 0:
                fcomp.fatigue = max(0, fcomp.fatigue - 1)

