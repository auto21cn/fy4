 // tie@fengyun
#include <ansi.h> 
#include <combat.h> 
inherit SSERVER; 
int perform(object me, object target) 
{ 
        string msg; 
        int extra; 
        object weapon; 
        if(me->query("gender")!="Ů��")
                return notify_fail("������һ���������������á����衹����\n");
        extra = me->query_skill("jianqi-dagger",1); 
        if ( extra < 70) return notify_fail("��ģۺ�����ݻ��������죡\n"); 
        if( !target ) target = offensive_target(me); 
        if( !target 
        ||      !target->is_character() 
        ||      !me->is_fighting(target) ) 
                return notify_fail("�۽����ֻ�ܶ�ս���еĶ���ʹ�á�\n"); 
        weapon = me->query_temp("weapon"); 
		message_vision(HIM"$N"HIM"������������Ծ����������ĸ�����ʹ��--�����衻��\n"NOR, me);
        if(random((int)me->query("combat_exp")*4) > (int)target->query("combat_exp") && !target->is_busy())
        {
        msg = HIR"$N"HIR"���е�" + weapon->name() + HIR"����ǧǧ��������ν�����$n"HIR"��ȥ��\n"HIW"$n"HIW"�鲻�Խ����ܸ����Ի������˽�����\n"NOR;        
        target->start_busy(3);
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg); 
        }
        else{      
			msg = HIR"$N"HIR"���е�" + weapon->name() + HIR"����ǧǧ��������ν�����$n"HIR"��ȥ��\n"NOR;
        me->add_temp("apply/damage", extra); 
        me->add_temp("apply/attack", extra); 
        COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
        me->add_temp("apply/damage", -extra); 
        me->add_temp("apply/attack", -extra); 
        }
        if(me->query_busy()<2) me->start_busy(2);
        return 1;
}     