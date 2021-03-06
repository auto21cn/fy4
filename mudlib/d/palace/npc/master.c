 inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int ask_challenge();
int leave();
void create()
{
    set_name("箫王孙", ({ "master xiao", "xiao","master" }) );
    set("gender", "男性" );
    set("nickname",HIY "黄衣客" NOR);
    set("reward_npc", 1);
    set("difficulty", 15);
    set("age", 45);
    set("int", 30);
    set("per", 30);
    set("attitude","friendly");
    set("class","yinshi");
    set("apprentice_available", 50);
    create_family("帝王谷", 1, "谷主");
    set("rank_nogen",1);
    set("ranks",({ "弟子","领班","小管家","管家","大管家",
                        CYN"隐者"NOR,CYN"隐士"NOR,HIC"侠隐"NOR }));; 
    set("long",
        "箫王孙的来历没有任何人知道．．．\n"
        );
    set("force_factor", 40);
    set("max_force", 2200);
    set("force", 2200);
    set("combat_exp", 9999999);
    set("score", 90000);
    set_skill("unarmed", 200);
    set_skill("whip", 200);
    set_skill("force", 190);
    set_skill("parry", 150);
    set_skill("literate", 140);
    set_skill("dodge", 150);
    set_skill("move",150);
    set_skill("cursism",200);
    set_skill("celecurse",200);
    set_skill("flying-dragon", 180);
    set_skill("thunderwhip", 180);
    set_skill("iceheart", 150);
    set_skill("zuixian-steps", 140);
    set_skill("perception", 100);
    map_skill("cursism","celecurse");
    map_skill("unarmed", "flying-dragon");
    map_skill("whip", "thunderwhip");
    map_skill("force", "iceheart");
    map_skill("parry", "thunderwhip");
    map_skill("dodge", "zuixian-steps");
        set("inquiry",([
        "challenge" : (: ask_challenge :),
        "挑战": (: ask_challenge :),
                "tiaozhan": (: ask_challenge :),
                "蓝天锤" : (: ask_challenge :),
                "master lan" : (: ask_challenge :),
                "leave" : (: leave :),
    ]) );
    set("agi",25);
    set("int",30);
    set("chat_chance_combat", 40);
    set("chat_msg_combat", ({
        (: perform_action, "whip.tianleiyiji" :),
        (: perform_action, "whip.yunlongjiuxian" :),
            }) );
    setup();
    carry_object(__DIR__"obj/shenxue")->wear();
    carry_object(__DIR__"obj/baojia")->wear();
    carry_object(__DIR__"obj/zhiai")->wear();
    carry_object(__DIR__"obj/sidai")->wield();
}
void reset()
{
    delete_temp("learned");
    set("apprentice_available", 20);
}
void attempt_apprentice(object ob)
{
    if( query("apprentice_available") ) {
        if( find_call_out("do_recruit") != -1 )
            command("say 慢著，一个一个来。");
        else
            call_out("do_recruit", 2, ob);
    } else {
        command("say 本谷主今天已经收了二十个弟子，不想再收徒了。");
    }
}
void do_recruit(object ob)
{
    if((int) ob->query_temp("wait_time") < 360)
    {
        command("think");
        command("say 你心不诚．．．\n");
        ob->set_temp("xiao_failed",1);
        return;
    }
    else { 
        command("smile");
        command("say 你日后必有大成！");
        command("smile");
        command("recruit " + ob->query("id") );
    }
}
int recruit_apprentice(object ob)
{
    if( ::recruit_apprentice(ob) )
        ob->set("class", "yinshi");
    add("apprentice_availavble", -1);
} 
int ask_challenge()
{
        object me;
        me = this_player();
        if ((string) me->query("class") == "yinshi" && me->query("marks/challenge_xiao_forlan"))
        {       
                say(HIW"\n箫王孙冷笑了一声：“蓝老儿还不死心吗？”\n"NOR);
                if (me->query("combat_exp")>1500000 && me->query("score")>10000)
                {
                        me->delete("marks/challenge_xiao_forlan");
                        message_vision(HIW"$N淡淡的对$n说：“你已学业有成，那么就替为师走一遭吧。用天雷破试试蓝天锤的盘古九式(challenge master lan).”\n"NOR,this_object(),me);
                   me->set("marks/challenge_lan",1);
                }else
                {
                        message_vision("$N冷笑到：“蓝老儿的锤法不堪一击，只可惜你火候未到，不能代为师教训他。。。”\n ",this_object());
                }
                return 1;
        }
        return 0;
} 
void init()
{       
        ::init();
        add_action("do_killing", "kill"); 
} 
int do_killing(string arg)
{
    object player, victim;
    string id,id_class;
    player = this_player();
    if(!arg || arg == "") return 0;
    victim = present(arg, environment(player));
        if(!objectp(victim))
                return notify_fail("这里没有这个人。\n");
    if(living(victim))
    {
        id_class=victim->query("class");
        id=victim->query("id");
        if(id_class == "yinshi"&& userp(victim)&& player!=victim)
        {
            message_vision(HIW
"$N对$n喝道：箫某的徒弟，容不得阁下来管教！\n"NOR, this_object(),player);
            this_object()->kill_ob(player);
            player->kill_ob(this_object());
            if (!player->is_busy()) player->start_busy(2);
            return 0;
        } 
    }
    return 0;
}  
int leave() {
   if (this_player()->query("class")!="yinshi") return 0;
        message_vision(CYN"$N道，“我不勉强你留下。“\n"NOR, this_object());
        message_vision(CYN"$N说：只是这通天降太为险恶，不能落在外人手里。\n"NOR,this_object());
        return 1;
}
