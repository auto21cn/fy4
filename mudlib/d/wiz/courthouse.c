 // Room: /d/wiz/courthouse.c
#include <ansi.h>
void test_me(object me);
inherit ROOM; 
void create()
{
        set("short", "法院");
        set("long", @LONG
这里是风云的管理审问机器人的法院，你一定是被人检举或是
行为太像机器人，才会来到这里，如果你答不出审判官的三个问题，会
被做上记号，超过三次的人将会被处以极刑，好好回答吧。
LONG
        );
        set("no_fight", 1);
        set("no_magic", 1);
        set("no_spells", 1);
        set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"jobroom"
]));
        set("objects", ([
                __DIR__"npc/judge":1 ]) ); 
        set("coor/x",0);
        set("coor/y",10);
        set("coor/z",10);
        setup();
}
void init()
{       object ob;
        if(interactive(ob = this_player()))
                test_me(ob);
}       
void test_me(object me)
{
        me->set_temp("old_startroom", me->query("startroom"));
        me->set("startroom", __FILE__);
}      
