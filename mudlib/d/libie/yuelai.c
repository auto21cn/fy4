 // Room: yuelai.c --- by MapMaker
#include <ansi.h>
inherit ROOM; 
void create()
{
        set("short", "悦来客栈"); 
        set("long", @LONG
这算是小县城里最大的客栈了，房子也是新盖的，可前几天却
突然花了数百两银子把楼上的套间重新装修了一遍。客栈老板也贴
出告示拒不待客。私底下老板透出消息说这一切仅仅是因为世袭一
等侯狄青麟小侯爷要在楼上新盖的“麒麟阁”住一晚上。
LONG); 
        set("type","house");
        set("exits",([
        "up":__DIR__"corrider",
        "north":__DIR__"stoneroad2",
        ]) ); 
        set("objects", ([
                __DIR__"npc/owner": 1 ]) ); 
        set("indoors", "libie");
        set("coor/x",40);
        set("coor/y",190);
        set("coor/z",0); 
        setup();
} 
int valid_enter(object me)
{
        object ob,cloth;
        
        if (ob=present("lao ban", this_object()))
        if (!me->query("marks/离别钩") && me->query("libie/离别钩二")&&me->query("libie/离别钩_小虎子的警告")&&me->query("libie/磨刀老人"))
        ob->start_call_out( (: call_other, __FILE__, "owner_leave" ,me,ob:), 1);
        return 1;
}
        
                
         
int valid_leave(object me, string dir)
{
    object ob,cloth;
        if( dir == "up" && ob=present("lao ban", this_object()))
        {
                cloth=present("waiter cloth",me);
                if(objectp(cloth))
                if(cloth->query("equipped"))
                        return 1;
                
                        
         return notify_fail("老板双手一张挡住去路，恨声道：你个" + RANK_D->query_rude(this_player()) + "，不想活了啊，惊了狄小侯爷那还了得！\n");
        }
        return 1;
} 
int owner_leave(object me, object owner)
{
        if (!present(me,this_object())) return 0;
        
        
    message_vision(YEL "客栈老板探头望了望窗外，不耐烦的道：这磨刀老头真是烦，磨他个鬼
啊，吵着狄小侯爷俺可担待不起。非得赶他走不可。\n话一说完，老板便一阵风溜了出去。\n"NOR,me);
        destruct(owner);
        me->set_temp("libie/离别钩_最后结局开始",1);
        return 1;
}      
