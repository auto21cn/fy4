 // a skeleton for user rooms
#include <ansi.h>
#define X_COOR 10
#define Y_COOR 2050
#define Z_COOR 50
#define R_FLAG 17
#define OWNER "tonic"
#define CLASS "财神庙"
inherit ROOM;
void create()
{
set("short", "河边");
set("long", @long
如同一声惊蛰春雷，惊醒了冻土层里的一条条蚯蚓，「团河」这
个字眼，使人有了热力。这儿确是一块风水宝地，有了亭、台、楼、
榭，还紧挨着一条小河。
long
);
        set("exits", ([
        
"south" : __DIR__"tonic1",
"north" : __DIR__"tonic3",

]));
set("objects", ([
//"/p/residence/npc/tonicwa" : 1,
       ]) );
        set("coor/x",X_COOR);
        set("coor/y",Y_COOR);
        set("coor/z",Z_COOR);
        set("room_flag",R_FLAG);
        set("owner", OWNER);
        set("class", CLASS);
        set("outdoors","residence");
        set("resource/water", 1);
        set("liquid/container", "流水");  
        setup();
}
void init()
{
        int flag;
        flag = (int) query("room_flag");
        if(flag & 1) set("valid_startroom",1);
   if(flag & 2) set("NONPC",1);
        if(flag & 4) set("no_fight",1);
        if(flag & 8) set("no_magic",1);
        if(flag & 16) set("outdoors","residence");
        add_action("do_invite","invite");
        add_action("do_setowner","setowner");
        add_action("do_list","list");
        add_action("do_jump", "wash");
        add_action("do_go","go"); 
        
}
int valid_enter(object me)
{
        int flag;
// means no enter at the beginning.
        int enter = 0;
    flag = (int) query("room_flag");
// always let owner go in:
        if((string)me->query("id") == (string)query("owner"))
        enter = 1;
        if(flag & 16)
        enter = 1;
        if(flag & 512)
        if((string)me->query("id") == (string)query("owner"))
        enter = 1;
        if(flag & 1024)
        if((string)me->query("class") == (string)query("class"))
        enter = 1;
        if(flag & 2048) 
        {
                if(strlen(query("invite")) && strsrch((string)query("invite"),"["+(string)me->query("id")+"]") != -1)
                enter = 1;
        }
//      write(sprintf("%d", enter));    
        return enter;
}
int do_list()
{
        object me;
        string *list,invitelist;
        me = this_player();
        if((string)me->query("id") != (string)query("owner"))
        return 0;
   invitelist = query("invite");
        if (strlen(invitelist))
        {
                list = explode("]"+invitelist+"[", "][");
                write("你邀请了下列玩家到你的房间:\n");
                for(int i=0;i<sizeof(list);i++)
                        write(list[i]+"\n");
        }else
                write("你没有邀请任何人到你的房间。\n");
        return 1;
} 
int do_invite(string arg)
{
        object me;
        string invitelist;
        me= this_player();
        if((string)me->query("id") != (string)query("owner"))
        return 0;
        if( !arg )
        {
                write("你要邀请谁? \n");
                return 1;
        }
        invitelist = (string)query("invite");
        if(strlen(invitelist) && strsrch(invitelist,"["+arg+"]") != -1)
        {
                //if the person has already been invited, remove it from invite list.
                invitelist = replace_string(invitelist,"["+arg+"]","");
                set("invite",invitelist);
                write("你将"+arg+"从你的邀请名单中除去。\n");
        }else
        {
                //invite the person.
                if( find_player(arg))
                {
                        if(!strlen(invitelist))
                                set("invite","["+arg+"]");
                        else
                                set("invite",invitelist+"["+arg+"]");
                        write("你邀请"+arg+"来你的房间。\n");
           }else
                {
                        write("咦... 有这个人吗?\n");
                }
        }
        return 1;
} 
int do_setowner(string arg)
{
        string oldowner;
        oldowner = (string)query("owner");
        set("owner",arg);
        write("你将房间的主人暂时设为"+arg+"。\n");
        call_out("set_back",60, oldowner);
        return 1;
} 
int set_back(string oldowner)
{
        set("owner", oldowner);
        return 1;
}
  
int do_jump()
{
        object me;
        int wait;
        me = this_player();
        wait = 15;
        message_vision("$N脱光衣服走入河中．．．\n",me);
        tell_object(me,"你感到全身无比的舒泰．．．\n");
        remove_call_out("curehimup");
   call_out("curehimup", wait, me);
return 1;
}  

void curehimup(object me)
{
        int gin,kee,sen;
        if(!me) return;
        gin=(int)me->query("max_gin");
        kee=(int)me->query("max_kee");
        sen=(int)me->query("max_sen");
if( me && environment(me) == this_object())
        {
        message_vision("$N的精气神全恢复了！！\n", me);
        me->set("eff_gin",gin);
        me->set("eff_kee",kee);
        me->set("eff_sen",sen);
        me->set("gin", gin);
        me->set("kee", kee);
        me->set("sen", sen);
        }
return;
}   
int do_go()
{
if(random(5)){
this_player()->move(this_object());
return 1;
}
}