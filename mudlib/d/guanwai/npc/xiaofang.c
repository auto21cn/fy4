#include <ansi.h>
inherit NPC; 
void create()
{
        set_name("小方", ({ "xiao fang","fang" }) );
        set("gender", "男性" );
        set("long",
                "一个流浪塞外、漂泊异乡的孤独浪子。\n"
                );
        set("title", HIW"浪子"NOR);
        set("attitude", "peaceful");
        
        set("age", 28);
        set("str", 40);
        set("cor", 36);
        set("agi", 60);
        set("per", 30);
        
        set("combat_exp", 5000000);
        
        set("max_gin", 5000);
        set("max_sen", 5000);
        
        set("force",3000);
        set("max_force",3000);
        set("force_factor",100);
        set("no_busy",4);
        set("class","fighter");
         
        set("chat_chance", 1);
        set("chat_msg", ({
                "小方远望着着窗外的圣母雪峰，哑着嗓子道：卜鹰……我一定会找到\n你，找到一个好好活着的你……\n",
                }) ); 
        set_skill("unarmed", 200);
        set_skill("parry", 200);
        set_skill("dodge", 300);
        set_skill("sword", 300);
        set_skill("doomforce", 150);
        set_skill("lingxi-zhi", 200);
        set_skill("doomsteps", 200);
           set_skill("doomsword",150);
        
        map_skill("unarmed", "lingxi-zhi");
        map_skill("sword", "doomsword");
        map_skill("dodge", "doomsteps");
        map_skill("parry","doomsword"); 
        set("chat_chance_combat", 30);
        set("chat_msg_combat",({
                      (:perform_action,"sword.hunranyijian":),
        }));
        
        setup();
        carry_object("/obj/armor/cloth")->wear();
        carry_object(__DIR__"obj/icesword")->wield();
} 
int accept_object(object me, object obj)
{
        if(obj->query("name") == BLU"魔眼剑"NOR && obj->query("owner") == me->query("id"))
        {
                message_vision("$N紧紧握着魔眼剑，眼中泪光闪烁，苍白的脸上泛出了血色。\n", this_object());
                message_vision("$N向$n感激地点了点头：卜大哥还活着，我早知道他还活着。\n",this_object(),me);
                if(!me->query("imbue/xiaofang")){
                                call_out("imbue_event", 2, me);
                        }
                if(!me->query("m_success/义助卜鹰"))
                {
                        me->set("m_success/义助卜鹰",1);
                        me->add("score",200);
                }
                return 1;
        }
        else
        {
                write("小方拱手道：“君子不夺人所爱，在下不能接受您的东西。”\n");
                return 0;
        }
} 
void imbue_event(object me){
        object weapon, *inv, obj;
        string prop;
   int i;
        if(!interactive(me) || environment(me) != environment(this_object())) {
                return 0;
        }
        obj = me->query_temp("weapon");
        if(objectp(obj) && obj->query("owner")) {
                weapon = me->query_temp("weapon");
        } else { 
                inv = all_inventory(me);        
                for(i=0; i<sizeof(inv); i++) {
                        if(inv[i]->query("weapon_prop") && inv[i]->query("owner")) {
                                weapon = inv[i];
                                break;
                        }
                }       
        }                       
        if(!objectp(weapon)){
                if(!objectp(obj)){
                        message_vision(HIC"\n欣喜的泪水一滴一滴掉落在地上。。。\n"NOR, me);
                } else {
                        message_vision(HIC"\n欣喜的泪水一滴一滴掉在$N的" + obj->name() + HIC"上又滑落到地上。\n", me);
                }
        }else {
                message_vision(HIC"\n欣喜的泪水一滴一滴掉落在$N的" + weapon->name() + HIC"上，不一会便凝成了晶莹闪亮的冰珠儿。。 \n"NOR,
                                me);
                message_vision(HIC"冰珠儿在" + weapon->name() + HIC"上散发出五彩的光芒，可是转瞬间又消失无痕。\n"NOR, me);
                if(weapon->query("weapon_prop")) {
                        prop="weapon_prop/";
                }
                if(weapon->query("equipped") == "wielded") {
                        weapon->unequip();
             if(random(me->query("宿命B/泰山_日出"))==9 ) {
                                weapon->add(prop+"karma", 5);
                                weapon->add(prop+"intelligence", 2);
                                weapon->add(prop+"damage", 10);
                                weapon->add("base_damage", 10);
                        } else {
                weapon->add(prop+"karma", 2);
                                weapon->add(prop+"personality", 2);
                        }
                   weapon->wield();
                } else {
             if(random(me->query("宿命B/泰山_日出"))==9 ) {
                weapon->add(prop+"karma", 5);
                                weapon->add(prop+"intelligence", 2);
                                weapon->add(prop+"damage", 10);
                                weapon->add("base_damage", 10);
                        } else {
                weapon->add(prop+"karma", 2);
                                weapon->add(prop+"personality", 2);
                        }
                }
                weapon->save();                 
                me->set("imbue/xiaofang", 1);
                me->save();
                return;
        } 
        me->set("imbue/xiaofang", 2);
        me->save();
        return;
}   
