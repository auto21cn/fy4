 // tie@fengyun
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra;
        if( !target ) target = offensive_target(me); 
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("［飞天腿］只能对战斗中的对手使用。\n");
        
        extra = me->query_skill("doomsteps",1);
        message_vision(HIR "$N"HIR"猛一个翻身，迅捷无比地向$n"HIR"踢出飞天一腿！\n"NOR, me, target);
        if(target->query("combat_exp") < random(me->query("combat_exp"))*extra/30) {
        msg =HIW "$N"HIW"只觉得耳边风声呼啸，说不出的心烦意乱。\n" NOR;
        message_vision(msg, target);
        target->receive_damage("sen",extra+random(extra*3),me);
        COMBAT_D->report_status(target);
		COMBAT_D->win_lose_check(me,target,1);
		
		}
		else COMBAT_D->do_attack(me,target,TYPE_PERFORM);

        if (me->query_busy()<2) 
                me->start_busy(2);
        return 1;
}       
