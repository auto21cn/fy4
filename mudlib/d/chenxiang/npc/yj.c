 // (C)1998-2000 Tie Yu
#include <ansi.h>
inherit NPC;
int tell_him();
void create()
{
    set_name("袁姬", ({ "queen yuanji","yuanji" }) );
    set("gender", "女性" );
    set("long","袁姬是当今皇上的新宠，不但相貌非凡，而且还通晓经书和史书。\n");
    set("age", 25);
    set("combat_exp", 500);
    set("attitude", "friendly");
    set("per",30);
    set("chat_chance", 1);
    set("chat_msg", ({
        "袁姬满脸惆怅，轻轻地叹了口气．．．心里似乎有化不开的愁。\n",
            }) );
    set("inquiry", ([
        "清波公子" : (: tell_him :),
        "qingbo" : (: tell_him:),
        ])); 
    setup();
    carry_object(__DIR__"obj/scloth")->wear();
} 
int tell_him()
{
    object me;
    me =this_player();
        if (me->query("m_success/义助袁姬")==1) {
        message_vision("$N说，谢谢你帮助了我们团聚。\n",this_object());
        return 1;
        }
        if (me->query("m_success/义助袁姬")==2) {
        message_vision("$N幽幽道，晚了，晚了。\n",this_object());
        return 1;
        }
        if (me->query("m_success/义助袁姬")==3) {
        message_vision("$N怒道，你这个小人，害了我和公子。\n",this_object());
        this_object()->kill_ob(this_player());
        return 1;
   }
    
    tell_object(me,"袁姬激动地看着你：你．．你．．认识清波公子？\n");
    tell_object(me,"袁姬向你翻了三次手掌，又指了指她身上戴的一面小圆镜子道：请带个话儿给
清波公子。\n");
    me->set_temp("marks/yuanji",1);
    return 1;
} 
int accept_object(object me, object obj)
{
    object ob; 
    if(me->query_temp("marks/ami") &&
       obj->query("real_lawan_id")==me->query("id"))
    {
        command("say 啊！！太好了，多谢这位" + RANK_D->query_respect(me) + "\n");
        command("say 我终于可以和清波公子团聚了！\n");
        ob = new(__DIR__"obj/mirror");  
        command("say 我走了，没有什么可以谢你的，这面小圆镜子就给你作纪念吧！\n");              
        if(!me->query("m_success/义助袁姬")) {
            me->set("m_success/义助袁姬",1);
            tell_object(me,HIR"你解开了义助袁姬之谜。\n"NOR);
                        switch( random(4)){
                        case 0: me->add("score",1000);
                                tell_object(me,HIW"你的评价增加了。\n"NOR);
                        case 1: me->add("max_force",10);
                                me->set("Add_force",10);
                                tell_object(me,HIW"你的内力增加了。\n"NOR);
                                break;
                        case 2: me->add("max_atman",5);
                                me->set("Add_atman",5);
                                tell_object(me,HIW"你的灵力增加了。\n"NOR);
                                break;
                        case 3: me->add("max_mana",5);
                                me->set("Add_mana",5);
                                tell_object(me,HIW"你的法力增加了。\n"NOR);
                                break;
                        default: break;
                }
        }    
        ob->move(environment());
   me->delete_temp("marks/ami");
        me->delete_temp("marks/asked_yaofang");
        me->delete_temp("marks/yaofang");
        me->delete_temp("marks/qingbo");
        me->delete_temp("marks/yuanji");
        me->delete_temp("marks/jiuye");
        call_out("ddddd",1);
        return 1;
    }
    return 0;
} 
int ddddd()
{
    destruct(this_object());
    return 1;
}    
