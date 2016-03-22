from roglick.engine.ecs import Entity,EntityManager
from roglick.components import SkillComponent,SkillSubComponent
from roglick.systems import SkillSystem
from roglick.engine import event
from roglick.events import SkillCheckEvent


def test_skill_check():
    wins = 0
    iters = 1000

    em = EntityManager()
    em.set_component(em.pc, SkillComponent())

    skills = em.get_component(em.pc, SkillComponent)
    # 7 has ~41% odds of success
    skills.skills['Dagger'] = SkillSubComponent(7)

    sys = SkillSystem()
    sys.set_entity_manager(em)
    event.register(sys)

    for x in range(iters):
        ch = SkillCheckEvent(em.pc, "Dagger")
        event.dispatch(ch)

        if ch.result[2]:
            wins += 1

    # Use a fudge factor, because random
    assert wins >= (iters * 0.38)
    assert wins <= (iters * 0.44)

