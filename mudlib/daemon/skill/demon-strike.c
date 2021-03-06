 // Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
inherit SKILL;
void setup() {
        set("name", "如意地魔连环八掌");
        set("usage/unarmed", 1);
        set("learn_bonus", 10);
        set("practice_bonus", 5);
        set("black_white_ness", -10);
        set("effective_level",160);
        set("skill_class", "bandit");
        set("parry_msg", ({
        "$n使出「粘」字诀，双掌一划，引偏了$N的$w。\n",
        }) );
        set("unarmed_parry_msg", ({
        "$n施展出如意地魔连环八掌，轻描淡写的化解了$N的攻势。\n",
        }) );
        action = ({
        ([      "action":               
"$N双掌一错，一招“魔火天焚”幻出漫天掌影拢向$n的$l",
                "dodge":                30,
                "parry":                10,
                "damage":                50,
                "damage_type":  "瘀伤"
        ]),
        ([      "action":               
"$N双掌纷飞，一招“魔王食飧”直取$n的$l",
                "dodge":                10,
                "parry":                30,
                "damage":                30,
                "damage_type":  "瘀伤"
        ]),
        ([      "action":               
"$N暴喝一声，双掌连环推出，一招“魔吼天地”强劲的掌风直扑$n的$l",
                "dodge":                30,
                "parry":                10,
                "damage":                50,
                "damage_type":  "瘀伤"
        ]),
        ([      "action":               
"$N使出如意地魔连环八掌中的“魔弑森森”，完全将$n的$l笼罩在双掌之下",
                "dodge":                10,
                "parry":                30,
                "damage":                60,
                "damage_type":  "瘀伤"
        ]),
        ([      "action":               
"$N化掌为刀，一招“乾坤尽魔”，左右掌分砍$n的两处要害",
                "dodge":                20,
                "parry":                30,
                "damage":                40,
                "damage_type":  "瘀伤"
        ]),
        ([      "action":               
"$N内气上提，全身拔起，一招“魔高和寡”，双掌凌空拍下",
                "dodge":                70,
                "parry":                10,
                "damage":                80,
                "damage_type":  "瘀伤"
        ]),
        ([      "action":               
"$N提气游走，一招“魔海漭漭”，森森掌风无孔不入般地击向$n的$l",
                "parry":                40,
                "force":                120,
                "damage_type":  "瘀伤"
        ]),
        ([      "action":
"$N使出如意地魔连环八掌中的“璞宇浑魔”双掌携天地魔神之威击向$n的$l",
                "parry":                40,
                "force":                120,
                "damage" :              50,
                "damage_type":  "瘀伤"
        ]),
        });
}
int valid_learn(object me)
{
        if(!::valid_learn(me)) {
                return 0;
   }
    if( (int)me->query_skill("demon-force", 1) < 10) {
        return notify_fail("你的天地人魔心法火候不足，无法练如意地魔连环八掌。\n");
    }
    return 1;
}  
int practice_skill(object me)
{
                if(!::practice_skill(me)) {
                        return 0;
                }
        if( (int)me->query("force") < 5 ) {
            return notify_fail("你的内力不够了，休息一下再练吧。\n");
        }
        me->add("force", -5);
        return 1;
}
void skill_improved(object me)
{
    int s;
    s = me->query_skill("demon-strike", 1);
    if (s== 150 && me->query("class")=="bandit") {
           me->set("once_menpai/bandit",1);
       } 
}   