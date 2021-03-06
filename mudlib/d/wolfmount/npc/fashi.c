#include <ansi.h>
inherit NPC; 
void create()
{
        set_name("大法师", ({"da fashi","fashi"}) );
        set("gender", "男性" );
        set("class", "taoist");
        set("nickname", HIR"食人狼王"NOR);
        set("long", "一个态度很严肃的老人，戴着顶圆盆般的斗签，一身血红的袈裟长垂\n及地，雪白的胡子使得他看来更受人尊敬。\n");
        set("attitude", "friendly");
        set("reward_npc", 1);
        set("difficulty", 10); 
        set("fly_target",1);
        set("cor", 35);
        set("cps", 3);
        set("age", 54);
        set("atman", 1000);
        set("max_atman", 1000);
        set("mana", 1000);
        set("max_mana", 1000);
        set("mana_factor", 100);
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: cast_spell, "invocation" :),
            (: cast_spell, "drainerbolt" :),
        }) );
        set("combat_exp", random(800000)+2500000);
        
        set_skill("spells", 200);
        set_skill("necromancy", 150);
        set_skill("blade", 160);
        set_skill("parry", 160);
        set_skill("dodge", 160);
        set_skill("move", 160);
        set_skill("unarmed",100);
        set_skill("flame-strike",100);
        set_skill("notracesnow", 150);
        
        map_skill("spells", "necromancy");
        map_skill("dodge","notracesnow");
        map_skill("unarmed", "flame-strike");
        
        set("chat_chance", 1);
        set("chat_msg", ({
        "大法师嘿嘿笑道：小姑娘的肉不但好吃，而且滋补得很。\n",
        }) );
        set_temp("apply/armor", 50);
        setup();
        carry_object(__DIR__"obj/cassock")->wear();
        carry_object(__DIR__"obj/hat")->wear();
} 
void init()
{
        object ob; 
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) 
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        if( !query_heart_beat(this_object()) ) {
                set_heart_beat(1); 
        }
} 
void greeting(object ob)
{   
        if (ob->query("gender") == "女性")
        {
                message_vision("$N流着口水，盯着$n：“细皮嫩肉的，胸脯一定很好吃。”\n", this_object(),ob );
                this_object()->kill_ob(ob);
        }
        return;
} 
