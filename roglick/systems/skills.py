from roglick.engine.ecs import System, exceptions
from roglick.components import SkillComponent,SkillSubComponent
from roglick.engine import event,random
from roglick.events import SkillCheckEvent
from roglick import skill_tree


class SkillSystem(System):
    @event.event_handler(SkillCheckEvent)
    def skill_check_handler(self, checkevent):
        checkevent.result = self.check_skill(
                checkevent.entity, checkevent.skill, checkevent.modifier)

    def check_skill(self, entity, skill, modifier=0):
        skill_level = self.get_skill_level(entity, skill) + modifier

        roll = 100
        for n in range(3):
            roll = min(roll, random.roll_dice(3))

        success = roll <= skill_level or roll <= 4
        critical = roll <= 6 and roll*3 <= skill_level
        dos = skill_level - roll

        if critical:
            dos += random.roll_dice()

        return (roll, dos, success, critical)

    def get_skill_level(self, entity, skill):
        if skill is None:
            return 0

        parent_level = self.get_skill_level(entity, skill_tree.get(skill).parent_name)

        return self.get_skill(entity, skill).ranks + parent_level/2

    def get_skill(self, entity, skill):
        try:
            e = self._entity_manager.get_component(
                    entity, SkillComponent)
        except exceptions.NoComponentForEntityError:
            e = SkillComponent()
            self._entity_manager.set_component(entity, e)

        try:
            comp = e.skills[skill]
        except KeyError:
            comp = SkillSubComponent()
            e.skills[skill] = comp

        return comp

