 // tie@fengyun
#include <ansi.h> 
#include <combat.h> 
inherit SSERVER; 
int perform(object me, object target) 
{ 
        string msg; 
        int extra; 
        int orforce; 
 
        if (me->query("class")!="quanli")
                return notify_fail ("［破釜沉舟］只有财神庙的兄弟姐妹才能使用。\n");
        if(me->is_busy()) 
                return notify_fail("你现在没空！！\n"); 
        if( !target ) target = offensive_target(me); 
        if( !target 
        ||      !target->is_character() 
        ||      !me->is_fighting(target) ) 
                return notify_fail("［破釜沉舟］只能对战斗中的对手使用。\n"); 

 
        extra = me->query_skill("unarmed"); 
 
        if ( extra < 300) return notify_fail("你的流氓神拳还不够纯熟！\n"); 
 
        me->set("force_factor",(int)me->query_skill("force")/2); 
        orforce = (int) me->query("force"); 
        me->add("force",extra/3*20); 
        me->add_temp("apply/attack",extra); 
//        me->add_temp("apply/damage",extra/2); 
        msg = HIG  "$N"+HIG"使出独步天下的［破釜沉舟］，略带一丝惋惜之色向$n"+HIG"的全身要穴攻出！\n" NOR; 
        message_vision(msg,me,target); 
        msg = HIG  "第一拳　笑　问　七　剑　一　指　仙！" NOR; 
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg); 
        msg = HIG  "第二拳　叶　落　枫　舞　二　穿　山！！" NOR; 
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg); 
        msg = HIG  "第三拳　袖　里　风　云　叁　点　头！！！" NOR; 
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg); 
        msg = HIG  "第四拳　回　首　太　白　四　气　刀！！！！" NOR; 
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg); 
        msg = HIG  "第五拳　化　月　孤　心　五　看　地！！！！！" NOR; 
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg); 
        msg = HIG  "第六拳　茫　茫　秋　水　六　荒　天！！！！！！" NOR; 
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg); 
        msg = HIG  "第七拳　笑　问　叶　落　看　风　云！！！！！！！" NOR; 
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg); 
        msg = HIG  "最后一拳　回　首　化　月　望　秋　水！！！！！！！！" NOR; 
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg); 
        me->start_busy(5); 
        me->set("force_factor",0); 
        me->set("force", orforce); 
        me->add_temp("apply/attack",-extra); 
//        me->add_temp("apply/damage",-extra/2); 
        return 1; 
}        
