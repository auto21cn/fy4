 //XXDER
inherit NPC;
inherit F_MASTER;
int leave(); 
#include <ansi.h>
void create()
{
    set_name("白水娘娘", ({ "master shenshui", "master", "shenshui" }) );
    set("nickname", HIB"水母阴姬"NOR);
    set("gender", "女性");
    set("class", "shenshui");
    set("age", 33);
    set("long",
        "一位脸上带着面沙的美女，坐在雕花椅上，你虽然看不到她的面容，却可以感觉到她"
        "那绝佳的气质和举手投足间的成熟风韵。\n");
    set("attitude", "peaceful");
    set("class", "shenshui");
    set("apprentice_available", 2);
    
    create_family("神水宫", 11, "掌门");
    set("rank_nogen",1);
    set("ranks",({"弟子","小仙女","仙女","大仙女","神姬",MAG"仙姬"NOR,HIM"圣姬"NOR,
                      HIR"副掌门"NOR}));
    set("reward_npc", 1);
        set("difficulty", 30);
    set("inquiry", ([
        "leave" : (: leave :),
                ]));  
        
    set("int", 28);
    set("spi", 26);
    set("per", 30);
    set("cps", 30);
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
                (: perform_action, "dodge.lianhuanbu"  :),
  //      (: perform_action, "unarmed.suicidal" :),
            }) );
    set("force", 1200);
    set("max_force", 1200);
    set("force_factor", 60); 
    set("combat_exp", 15000000);
    set("score", random(90000)); 
    set_skill("unarmed", 150);
    set_skill("sword", 150);
    set_skill("force", 180);
    set_skill("parry", 140);
    set_skill("dodge", 140);
    set_skill("literate", 140);
    set_skill("move",200);
    set_skill("charm",280);
    set_skill("nine-moon-spirit", 200); 
    set_skill("nine-moon-steps", 180);
    set_skill("nine-moon-claw", 200);
    set_skill("nine-moon-force", 150);
    set_skill("nine-moon-sword", 200); 
    map_skill("dodge", "nine-moon-steps");
    map_skill("unarmed", "nine-moon-claw");
    map_skill("force", "nine-moon-force");
    map_skill("sword", "nine-moon-sword");  
    set_temp("apply/dodge", 100);
        set_temp("apply/parry", 100); 
    setup();
    carry_object(__DIR__"obj/ghostyboots")->wear();
    carry_object(__DIR__"obj/ghostycloth")->wear();
    carry_object(__DIR__"obj/ghostygirth")->wear();
    carry_object(__DIR__"obj/ghostyribbon")->wear();
} 
void reset()
{
    delete_temp("learned");
    set("apprentice_available", 5);
} 
void attempt_apprentice(object ob)
{
    if( query("apprentice_available") ) {
        if( find_call_out("do_recruit") != -1 )
            command("say 慢著，一个一个来。");
        else
            call_out("do_recruit", 2, ob);
    } else {
        command("say 本掌门今天已经收了五个弟子，不想再收徒了。");
    }
} 
void do_recruit(object ob)
{
    object girl; 
   if( ((int)ob->query("cor") < 10) || ((int)ob->query("cps") < 10)
        || ((int)ob->query("int") < 10)
        ||      ((int)ob->query("con") < 10)) {
        command("say 入神水九阴要靠缘份，依我看" +
                RANK_D->query_respect(ob) + "和九阴今生无缘。");
        return;
    }
    if( (string)ob->query("gender") != "女性" )
    {
                command("shake");
                command("say 神水宫的武功，非女子不能修炼到至高境界。"); 
        } else {
        command("smile");
        command("say 很好，很好，很好。");
        command("recruit " + ob->query("id") );
                tell_object(ob, HIY"\n你只听一个细微的声音传了过来：“你即以入我神水，当知神水密径。\n"NOR);
                tell_object(ob, HIY"出入神水可由火岩洞口处推开山石，回路则由出清平山庄后花园门，\n"NOR);
                tell_object(ob, HIY"穿密林，在山崖处推开山石。谨记、谨记。”\n\n"NOR);
                message("vision", ob->name()+ "似乎在侧耳聆听什么，你却什么也听不到。\n",
                                environment(ob), ob);
        }
} 
int recruit_apprentice(object ob)
{
    if( ::recruit_apprentice(ob) )
        ob->set("class", "shenshui");
         ob->set("once_shenshui",1);
    add("apprentice_availavble", -1);
} 
void init()
{
	object ob;
        ::init();
        add_action("do_killing", "kill");
                if( interactive(ob = this_player()) ) {
                remove_call_out("punish_betray");
                call_out("punish_betray",3 , ob);
        }
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
        if(id_class == "shenshui"&& userp(victim)&&player!=victim)
        {
message_vision(HIW"$N对著$n喝道：" + RANK_D->query_rude(player) 
                                                + "竟敢杀" + RANK_D->query_self_rude(this_object()) 
                                                + "的徒弟，去死吧。\n"NOR, this_object(), player);
            this_object()->kill_ob(player);
            player->kill_ob(this_object());
            if (!player->is_busy()) player->start_busy(2);
            return 0;
        } 
    }
    return 0;
} 
int leave() {
        if (this_player()->query("class")!="shenshui") return 0;
        message_vision(CYN"$N冷笑了一声。\n"NOR, this_object(),this_player());
        message_vision(CYN"$N说：想走可以，但从此不能在江湖上使用九阴神功。\n"NOR,this_object(),this_player());
        return 1;
} 
void punish_betray(object ob)
{
        if( ( ob->query("once_shenshui")) && ( (ob->query("class"))!= "shenshui"))
          {      
                tell_object(ob, YEL"\n水母阴姬对你冷笑道：“你既然判出本门，就不配再有本门的武功！”\n"NOR);              
                message("vision", "水母阴姬对"+ ob->name() +"冷笑道：“"+ ob->name() + "！ 你既然判出本门，就不配再有本门的武功！\n", environment(ob), ob);
           tell_object(ob, HIW"水母阴姬手一扬，一支牛毛般细小的飞针射入你灵台！\n"NOR);              
                message("vision", HIW"水母阴姬对着"+ ob->name() +"手一扬，射出一支牛毛般细小的飞针！\n"NOR, environment(ob), ob);
                
                if (ob->query_skill("nine-moon-claw",1)) ob->delete_skill("nine-moon-claw");
                if (ob->query_skill("nine-moon-force",1)) ob->delete_skill("nine-moon-force");
                if (ob->query_skill("nine-moon-steps",1)) ob->delete_skill("nine-moon-steps");
                if (ob->query_skill("nine-moon-sword",1)) ob->delete_skill("nine-moon-sword");
                tell_object(ob, HIR"你只觉血脉一阵逆流，武功全失！！\n"NOR);
                ob->start_busy(10);
                ob->delete("once_shenshui");
  
          }
} 