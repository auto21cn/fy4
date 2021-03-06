inherit NPC;
inherit F_MASTER;
int leave();
#include <ansi.h> 
void create()
{
    set_name("华真真", ({ "hua zhenzhen", "zhenzhen", "hua"}) );
    set("gender", "女性" );
    set("age", 18);
    set("int", 30);
    set("per", 30);
    set("reward_npc", 1);
    set("difficulty", 30);
    set("class","huashan");
    set("apprentice_available", 50);
    create_family("华山派", 15, "弟子");
    set("title", "华山派 第十七代弟子");
        set("rank_nogen",1);
    set("long",
        "她斯斯文文，秀秀气气，始终低垂着头，仿佛羞见生人。 
偶然抬头时，一双眼眸如星光般闪动，脸上却现出微微晕红。 \n"
        );
    set("inquiry", ([
                        "leave" : (: leave :),
        ]));
    
    
    set("no_busy",10);
    switch (random(3)) {
                case 0: set("resistance/kee",30);
                        break;
                case 1: set("resistance/gin",30);
                        break;
                default: set("resistance/sen",30);
                }
    
    set("force", 8000);
    set("max_force", 8000);
    set("force_factor",160);
    set("str", 40);
    
    set("score", 5000);
    set("combat_exp", 9999999); 
    set_skill("unarmed",160);
    set_skill("sword", 150);
    set_skill("force", 200);
    set_skill("hanmei-force", 200);
    set_skill("anxiang-steps", 180);
    set_skill("cloud-dance", 200);
    set_skill("move", 180);
    set_skill("literate", 150);
    set_skill("dodge", 160);
        set_skill("perception", 100);
    set_skill("parry", 160);
    set_skill("throwing", 220);
    set_skill("iron-cloth", 180);
    set_skill("spring-water", 180);
    set_skill("qingfeng-sword", 150);
    set_skill("tanzhi-shentong", 200);
    set_skill("zhaixin-claw",150);
    
    map_skill("unarmed", "zhaixin-claw");
    map_skill("force", "hanmei-force");
    map_skill("dodge", "cloud-dance");
    map_skill("sword", "qingfeng-sword");
    map_skill("parry", "qingfeng-sword");
    map_skill("move", "anxiang-steps");
    map_skill("iron-cloth", "spring-water");
    map_skill("throwing", "tanzhi-shentong");
    
    
    set("ranks",({"弟子","小侠","少侠","大侠","奇侠",WHT"剑仙"NOR,WHT"侠圣"NOR,HIW"隐侠"NOR}));
    setup();
    carry_object(__DIR__"obj/ycloth")->wear();
    carry_object(__DIR__"obj/qingfeng")->wield();
}
void reset()
{
        delete_temp("learned");
        set("apprentice_available", 1);
}
void attempt_apprentice(object ob)
{
        if( query("apprentice_available") ) {
                if( find_call_out("do_recruit") != -1 )
                        command("say 慢著，一个一个来。");
                else
                        call_out("do_recruit", 2, ob);
        } 
}
void do_recruit(object ob)
{
        if((string)ob->query("gender") == "女性" 
                        &&(int)ob->query("combat_exp")>1200000&&ob->query("class")=="huashan"){      
                if (ob->query("marks/忠诚")==1 
                        || (ob->query("marks/忠诚")== -1 && ob->query("marks/kill_kumei"))
                        ){
                        message_vision("$N盯着$n看了一会儿，叹了口气说：“也许真的有一天，你能发扬光大华山派。” \n",
                                this_object(), ob);
                        command("recruit " + ob->query("id") );
                        message_vision("\n$N转身走到绝壁边，回身向$n示意跟过来。\n", this_object(),ob); 
                        message_vision("$N身影一晃，竟然从绝壁边消失了。\n", this_object());
                        environment(ob)->go_cliff(ob);
                        destruct(this_object());
                }
                else if (ob->query("marks/忠诚")== -1 && !ob->query("marks/kill_kumei")) {
                        message_vision("$N盯着$n看了一会儿，叹了口气说：“也许你是忠实的华山弟子，\n要知道，本门中的那些见不得人的败类不除掉，华山派就永远不能发扬光大。” \n",
                                this_object(), ob);            
                        command("wave");
                        message_vision("\n\n$N身影一晃，竟然从绝壁边消失了。\n", this_object());
                        destruct(this_object());
                }
                
                else {
                        message_vision("$N叹了口气说：“华山正在多事之秋，师妹该多为师门出力啊。” \n",
                                this_object());
                        command("wave");
                        message_vision("\n\n$N身影一晃，竟然从绝壁边消失了。\n", this_object());
                        destruct(this_object()); 
           }
                
        } 
        else {
                message_vision("虽然是黑暗的夜色下，$N还是不好意思地低下头，小声说：“ 我才是\n", this_object());
                message_vision("个没出道的弟子，怎么配做别人的师傅呢？” \n", this_object());
                message_vision("$N身影一闪，消失在夜幕中。\n", this_object()); 
                destruct(this_object());
        } 
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "huashan");
        add("apprentice_availavble", -1);
} 
void init(){
        ::init();
        call_out("do_leave", 30);
        add_action("do_killing", "kill");
} 
void do_leave(){
        if( find_call_out("do_recruit") != -1 ) {
                call_out("do_leave", 5);
        }
        environment(this_object())->do_leave();
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
           if(id_class == "huashan"&& userp(victim)&& player!= victim)
        {
            message_vision(HIW
"$N叹了口气：杀人者，人杀之！\n"NOR, this_object());
            this_object()->kill_ob(player);
            player->kill_ob(this_object());
            player->start_busy(2);
            return 0;
        } 
    }
    return 0;
} 
int leave() {
        if (this_player()->query("class")!="huashan") return 0;
        message_vision(CYN"$N低着头说，“好吧“\n"NOR, this_object());
        message_vision(CYN"$N说：只是华山门规森严，春水罗衫和摘心的秘诀不能带走。\n"NOR,this_object());
        return 1;
}     
