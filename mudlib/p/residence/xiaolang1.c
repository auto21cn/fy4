 // a skeleton for user rooms
#include <ansi.h>
#include <room.h>
#define X_COOR 15
#define Y_COOR 2030
#define Z_COOR 30
#define R_FLAG 2561
#define OWNER "xiaolang"
#define CLASS "万梅山庄"
#include <ansi.h>
inherit ROOM;
void create()
{
set("short", HIG"忘忧山庄"NOR);
set("long", 
"你绕过小道，眼前一片豁朗，抬头望去，红漆大门敞开，门楣上书“忘忧”二字，
门框上有两句小诗：\n"
+HIG"                    自          此
                    古          恨
                    多          绵
                    情          绵
                    空          无
                    余          绝
                    恨          期\n"NOR
+"  诗下写着：萧十一郎自题，大门两侧各立一只玉石所雕的狼王。狼王两侧梅树
林立，花草与灌木丛茂密异常，冬天的时候，微风吹起，梅花传来的香味让人心旷
神怡，但深夜站在这里会感到莫名的紧张，你觉得好像哪里有一双眼睛盯着自己。\n\n"
);
        set("exits", ([
		"west" : __DIR__"room4",
		"north" : __DIR__"xiaolang_xiaodao",
		]));
		 set("objects", ([
                __DIR__"npc/xiaolang_guard" : 1,
       ]) );
        set("coor/x",X_COOR);
        set("coor/y",Y_COOR);
        set("coor/z",Z_COOR);
        set("room_flag",R_FLAG);
//        set("owner", OWNER);
        set("class", CLASS);
        set("no_steal",1);
//        set("no_fight",1);
        set("no_death_penalty",1);
        setup();
}
void init()
{
        int flag;
        flag = (int) query("room_flag");
        if(flag & 1) set("valid_startroom",1);
        if(flag & 8) set("no_magic",1);
        if(flag & 16) set("outdoors","residence");
}
int valid_leave(object me, string dir)
{
        object ob, shiwei;    
            
        if (!shiwei=present("xiao qiushui",this_object()))
                return 1;
        
        if ( userp(me) && dir=="north" ) {
                if((string)me->query("id") != "xiaolang" && (string)me->query("id") != "lsky"){
                			if (!ob=present("qingtie",me))
                        		return notify_fail(shiwei->name()+"冷笑一声道：没有庄主的请帖，你凭什么进去？\n");
                			if (!me->query_temp("忘忧山庄/请帖"))
                        		return notify_fail(shiwei->name()+"说：“难道你还没有认真读(read)过庄主的请帖？”\n");
               																					 }
                return 1;
        }
        
        return 1;
}    
