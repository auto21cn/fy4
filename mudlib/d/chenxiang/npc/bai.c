 inherit NPC;
#include <ansi.h>
void create()
{
        set_name("白玉京", ({ "bai yujing", "bai", "yujing" }) );
        set("nickname", HIC"天上"NOR);
        set("title", "长生剑客");
        set("gender", "男性" );
        set("age", 24);
        set("str", 30);
        set("cor", 30);
        set("cps", 30);
        set("int", 30);
        set("per", 20);
        set("attitude","peaceful");
        set("max_force", 1000);
        set("force", 1000);
        set_temp("apply/damage",150);
        set_temp("apply/attack",200);
        set("force_factor", 50);
        set("long",
                "天上白玉京，旧靴子，旧剑鞘，但穿着一身崭新的衣服。\n"
        );
        set("combat_exp", 4000000);
        set("score", 200000);
        set("chat_chance", 1);
        set("chat_msg", ({
                "白玉京喟然长叹一声，默然不语。\n"      
        }) );
        set("inquiry",([
        "袁紫霞"  :"袁姑娘竟会是青龙会的红旗老幺？她为什么骗我？\n",
        "yuan"  :"袁姑娘竟会是青龙会的红旗老幺？她为什么骗我？\n",
        "长生剑"  :"哎。。仙人抚我顶，结发受长生。昔日的长生剑早已不知流落何方？如果能。。\n",
        "sword"  :"哎。。仙人抚我顶，结发受长生。昔日的长生剑早已不知流落何方？如果能。。\n",
                ]) ); 
        set_skill("move", 100);
        set_skill("parry", 100);
        set_skill("dodge", 120);
        set_skill("force", 100);
        set_skill("unarmed", 80);
   set_skill("bai-quan",80);
        set_skill("literate", 100);
        set_skill("sword",130);
        set_skill("qingpingsword",150);
        set_skill("qingpingforce",120);
        set_skill("chaos-steps",120);
        map_skill("force", "qingpingforce");
        map_skill("parry","qingpingsword");
        map_skill("sword","qingpingsword");
        map_skill("dodge","chaos-steps");
        map_skill("move","chaos-steps"); 
        map_skill("unarmed","bai-quan"); 
        setup();
        carry_object("/d/chenxiang/npc/obj/newcloth")->wear();
        carry_object("/d/chenxiang/npc/obj/oldboots")->wear();
} 
void init()
{
        object me;
        ::init();      
        if( interactive(me = this_player()) && !is_fighting() && !random(5)) 
        {
                call_out("greeting", 1, me);
        }
} 
int accept_object(object me, object obj)
{
        object bai, ob, sword;
        bai = this_object();
        if( (string) obj->query("name") == "孔雀图" && obj->query("real"))
        {
                environment(me)->answer_notify(bai,0);
        message_vision(HIY "\n$N对$n缓缓道：为了一张孔雀图，尔虞我诈！人间可还有真情在？\n你可否告知我袁姑娘究竟是爱我还是恨我？（answer love/hate）\n"NOR, this_object(), me);
                return 1;
        }
        else if( (string) obj->query("name") == HIG "长生剑"NOR )
        {
        message_vision(HIW "\n$N颤抖着双手，挣扎着想接过宝剑，但‘噗通’一声，摔倒在地，宝剑也落到地上。\n这绝代剑客，竟连自己的宝剑都拿不稳了。\n"NOR, this_object());
                ob = present("floor", environment(this_object()));
                sword = new("/d/tieflag/obj/csword");
           sword->move(ob);
                return 1;
        }
        else
        {
                tell_object(me,"白玉京说道：这不是我想要的。\n");
                return 0;
        }
}    
