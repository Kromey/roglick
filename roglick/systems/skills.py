from roglick.engine.ecs import System, exceptions
from roglick.components import SkillsComponent,SkillSubComponent
from roglick.engine import event,random
from roglick.events import SkillCheckEvent
from roglick.skills import skill_tree


class SkillSystem(System):
    @event.event_handler(SkillCheckEvent)
    def skill_check_handler(self, checkevent):
        checkevent.result = self.check_skill(
                checkevent.entity, checkevent.skill, checkevent.modifier)

    def check_skill(self, entity, skill, modifier=0):
        skill_level = self.get_skill_level(entity, skill_tree[skill])
        skill_level += modifier

        roll = random.roll_dice(3)

        success = roll <= skill_level or roll <= 4
        critical = roll <= 6 and roll*3 <= skill_level
        dos = skill_level - roll

        if success and critical:
            dos += random.roll_dice()
            # Degree of Success on a critical is always at least 1
            dos = max(dos, 1)
        elif success:
            # Degree of Success is always at least 0 for a success
            dos = max(dos, 0)

        return SkillCheckEvent.Result(success, critical, roll, dos)

    def get_skill_level(self, entity, skill):
        if skill is None:
            return 0

        parent_level = self.get_skill_level(entity, skill.parent)

        return self.get_skill(entity, skill.key).ranks + parent_level/2

    def get_skill(self, entity, skill):
        try:
            c = self._entity_manager.get_component(
                    entity, SkillsComponent)
        except exceptions.NoComponentForEntityError:
            c = SkillsComponent()
            self._entity_manager.set_component(entity, e)

        try:
            comp = c[skill]
        except KeyError:
            comp = SkillSubComponent()
            c[skill] = comp

        return comp

