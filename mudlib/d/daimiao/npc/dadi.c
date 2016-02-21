 inherit NPC;
#include <ansi.h>
inherit F_MASTER;
void create()
{
    set_name(HIY"�������"NOR, ({ "master dadi", "master", "dadi" }) ); 
    set("gender", "����");
    set("age", 99);
    set("long", "������۸����ߣ���ò������֣���������һ�㡣\n");
    set("attitude", "peaceful");
    set("str", 2600);
    set("cor", 30);
    set("int", 24);
    set("cps", 30);
    set("force", 40000);
    set("max_force", 80000);
    set("force_factor", 1000);
    set("combat_exp", 10000000);
    set("score", 200000);
    set_skill("unarmed", 120);
    set_skill("force", 100);
    set_skill("iron-cloth", 100);
    set_skill("yiqiforce", 60);
    set_skill("literate",100);
    set_skill("incarnation",320);
    set_skill("dodge",100);
    set_temp("apply/attack",300);
    set_temp("apply/damage",30000);
    map_skill("iron-cloth", "yiqiforce");
    map_skill("force", "yiqiforce");
    map_skill("unarmed", "yiqiforce");
    set("no_shown",1);
    set("rank_nogen",1);
    create_family("������", 1, "��ʦ");
    set("ranks",({"����","����","����","���޽���"}));
    set("rank_levels",({320000,5187000,26244000}));
    setup();
}
int accept_fight(object me)
{
    return 0;
}
void attempt_apprentice(object me)
{
    command("recruit " + me->query("id") );
} 
void recruit_apprentice(object ob)
{
    if( ::recruit_apprentice(ob) )
        ob->set("class", "xianren");
}
void init()
{
    add_action("do_look","look");
} 
int do_look(string arg)
{
    if (arg == "master dadi" || arg == "dadi" || arg =="master")
    {
        write("������۸����ߣ���ò������֣���������һ�㡣\n");
        return 1;
    }
    return 0;
}   