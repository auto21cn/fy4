 // reaction.c
#include <ansi.h>
#include <combat.h> 
inherit SSERVER; 
void reacted(object me, int skill, int extra, int luck, object ding); 
int conjure(object me, object target)
{
        object ding, env;
        int skill, value, extra, luck;
        
        if(me->query("class")!="taoist")
                return notify_fail("只有三清宫的弟子才可以练丹！\n");
        if(me->query("gender")!="男性")
                return notify_fail("你的身体不适合炼丹的严酷环境！\n");
        if(me->is_fighting())
                return notify_fail("战斗中烧丹会玩火自焚！\n");
        if( !target)
                return notify_fail("你要用什么炼丹？\n");
        target = present(target->query("id"), me);
        if( !target)
                return notify_fail("你身上没有这东西。\n");
        if (target->query("id")=="ding")
                return notify_fail("你不能用这件物品来炼丹。\n");
                                
        if( living(target) )
                return notify_fail(target->name() + "还活着，你就想烧丹？？\n"); 
        if( target->query("no_burn") )
                return notify_fail(target->name() + "不能再用来烧丹了。\n"); 
        
        env = environment(me);
        skill = (int) me->query_skill("alchemy",1);
    
        if(skill < 31)
                return notify_fail("你的炼丹术不够高深！\n");
        
        
        if( !objectp(ding = present("ding", env)) && !objectp(ding=present("ding",me)) )
                        return notify_fail("这里没有可以炼丹的宝鼎。\n");
                                
        if (strsrch(ding->query_default_object(), "/obj/specials/ding/ding")== -1) 
                   return notify_fail("这个鼎稀奇古怪，恐怕会炼出妖精。\n");
        
        if (target->query_weight()>10000 && ding->query("small_ding"))
                        return notify_fail("这个东西太大太重，小鼎里放不下。\n");
        
        if(ding->query_temp("in_use"))
                    return notify_fail("有人正在用这个鼎炼丹，你还是等一等吧。\n");
        if(ding->query_temp("broken"))
                    return notify_fail("这个鼎已经失去鼎神，不能炼丹了。\n"); 
        if( (int)me->query("atman") < 80 ) return notify_fail("你的灵力不够！\n");
        if( me->query("sen") <= 60 )
                return notify_fail("你的神不够！\n");
        me->add("atman", -80);
        me->receive_damage("sen", 60);
        message_vision( HIC "$N将$n"HIC"投入"NOR + ding->name()+ HIC"。\n$N运起法力，只见一片青光从"NOR+ding->name()+HIC"中腾起...\n" NOR, me, target);
        ding->set_temp("in_use", 1);
        
        extra = (int) target->query("value");
        
        target->move(env);
        destruct(target);
        luck = (int) me->query("kar");
        call_out("reacted", 3 ,me, skill, extra, luck , ding); 
        me->start_busy(3);
        return 1;
} 
        
void reacted(object me, int skill, int extra, int luck, object ding)
{
        object dan, devil;
        string to_cure, desc;
        int rand;
        string *cure_type = ({"gin", "kee", "sen", "kee", "gin", "sen", "all"});
        string *trash = ({"blade", "dart", "leg", "skin", "teapot", "axe", "dagger"});
        string *magic = ({"zhui", "mirror", "chain", "flag"});
    // First have to pass a skill*kar related luck test
        if (random(luck*skill - 240)<3) {
        message_vision( NOR MAG"\n一股股紫烟从鼎中冒出..." , me);
        message_vision( NOR "\n\n"+ding->name()+HIW"轰轰作响，仿佛不胜重荷一般...\n" NOR YEL "\n忽然，一个褚衣霞帔的仙人从鼎中升起，哈哈大笑中，唱道：\n" MAG, me);
        message_vision( "\n             道士妄学仙\n             烧丹得紫烟\n             借尔竹篮水\n             破鼎上青天\n", me);
        message_vision( HIM"\n仙人化作一道霞光，冲天飞去。" , me);
        message_vision( HIR"\n\n轰隆一声巨响！"NOR+ ding->name() +HIR" 炸出一片红光！！\n"NOR, me); 
        call_out("recover_ding", 30 ,ding, ding->name()); 
        ding->set("name", WHT"破裂的 "NOR+ding->name());
        ding->delete_temp("in_use");
        ding->set_temp("broken", 1);
        me->unconcious();
        return;
    } 
    // Start to lian dan
    
    if ( random(skill)+ ( (skill/2 + extra/1000)*random(luck) )/10 >100) {
        seteuid(getuid());
        if ( random(5)>2 ) {
                dan= new("/obj/specials/alchemy/dan");
                dan->set_temp("to_cure", (cure_type[random(sizeof(cure_type))]) );
                dan->set_temp("cure", 8 + random(2) - 200/(random(skill)+20) );
                to_cure=dan->query_temp("to_cure");
                desc = dan->query("long");
                if ( to_cure =="gin" ) dan->set("long", desc + "它能让你迅速恢复精力损伤。\n");
                if ( to_cure =="kee" ) dan->set("long", desc + "它能让你迅速恢复气血损伤。\n");
                if ( to_cure =="sen" ) dan->set("long", desc + "它能让你迅速恢复心神损伤。\n");
                if ( to_cure =="all" ) dan->set("long", desc + "它能让你迅速恢复所有损伤。\n");
                if ((int) me->query_temp("dan_number")>1 && objectp(present("dan", me))  ) {
                        message_vision( HIY "\n\n一粒"+dan->name()+HIY"从"NOR + ding->name()+ HIY"中跃出，化作一团蒙蒙霞光消失了。\n" NOR, me);
                        tell_object(me, WHT"真可惜，大概是因为你炼的丹太多了，它们天性相克。\n"NOR);                    
                        destruct(dan);
                }
                else {        
                        dan->move(me);
                        message_vision( HIY "\n\n一粒"+dan->name()+HIY"从"NOR + ding->name()+ HIY"中跃出，落入$N掌心。\n" NOR, me);
                        me->set_temp("dan_number", 1 + (int )me->query_temp("dan_number"));
                
                }
        }
        else {
            dan= new("/obj/specials/alchemy/magic/"+magic[random(sizeof(magic))]);
            dan->set("level", skill/2);
            dan->move(me);
            message_vision( HIY "\n\n一声激越的清响，"NOR+dan->name()+HIY"从"NOR + ding->name()+ HIY"中跃出，落入$N掌心。\n" NOR, me);
   }
        
    }
    else if ( random(skill)+((random(skill) + extra/1000)*random(luck))/10 <60) {
            
        message_vision( HIB "\n\n只听见"NOR + ding->name()+ HIB"中一阵唧唧乱叫...\n" NOR, me);
        seteuid(getuid());
        devil= new("/obj/specials/alchemy/devil");
        devil->move(environment(me));
        message_vision( HIW "\n一只$N从"NOR + ding->name()+ HIW"中跳了出来！\n" NOR, devil);
        devil->emerge(me, skill);
        devil->set("possessed", me);
    }
    else {
        seteuid(getuid());
        rand = random(5);
        if (rand >3) {
            dan= new("/obj/specials/alchemy/wan");
            dan->move(me);
            message_vision( HIY "\n\n一粒"+dan->name()+HIY"从"NOR + ding->name()+ HIY"中跃出，落入$N掌心。\n" NOR, me);
        }
        else if (rand >2) {
            dan= new("/obj/specials/alchemy/magic/"+magic[random(sizeof(magic))]);
            dan->set("level", skill/2);
            dan->move(me);
            message_vision( HIY "\n\n一声激越的清响，"NOR+dan->name()+HIY"从"NOR + ding->name()+ HIY"中跃出，落入$N掌心。\n" NOR, me);
        }
        else {
            dan= new("/obj/specials/alchemy/trash/"+trash[random(sizeof(trash))]);
            dan->move(me);
            message_vision( HIY "\n\n一声怪响，"NOR+dan->name()+HIY"从"NOR + ding->name()+ HIY"中跃出，落入$N掌心。\n" NOR, me);
        }
        
    }
        ding->delete_temp("in_use"); 
} 
void recover_ding(object ding, string ding_name)
{
        message_vision( MAG "\n\n一缕缕淡淡的紫气从地下涌出，围绕在$N"MAG"周围，\n忽然紫气流转，全部吸入鼎内。\n" NOR, ding);
        ding->set("name", ding_name);
        ding->delete_temp("broken");
        
}      
