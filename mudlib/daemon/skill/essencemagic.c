 // essencemagic.c
#include <ansi.h>
inherit SKILL; 
void setup() {
        set("name", "八识神通");
        set("effective_level", 150);
        set("learn_bonus", -10);
        set("practice_bonus", -5);
        set("black_white_ness", 60);
        set("usage/magic", 1);
        set("skill_class", "bonze");
} 
int valid_learn(object me)
{
        if( (int)me->query_skill("buddhism",1) < 10
        ||      (int)me->query_skill("buddhism",1) < (int)me->query_skill("essencemagic",1) )
                return notify_fail("你的佛法修为还不够高深，无法学习八识神通。\n");
        return 1;
}
int practice_skill(object me)
{
        return notify_fail("八识神通只能用学的\n");
}  

void skill_improved(object me)
{
    int s;
    s = me->query_skill("essencemagic", 1);
    if (s== 280) {
       tell_object(me,HIW " 突然你对八识神通有了更加深层的了解。\n"NOR);
       tell_object(me,HIW"恭喜你！你以后可以移动自己的队伍了！\n"NOR);
       me->set("open_sesame",1);
      } 
} 