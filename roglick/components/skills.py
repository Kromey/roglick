from roglick.engine.ecs import multi_component


SkillsComponent = multi_component('SkillsComponent', ('ranks','xp'), (0,0))

