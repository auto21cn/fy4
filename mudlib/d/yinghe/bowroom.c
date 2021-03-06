 // Room: bowroom.c --- by MapMaker
#include <ansi.h>
inherit ROOM; 
void create()
{
        object bow, wall, arrow1, arrow2;
        
        set("short", "霹雳绝鸟堂");
        set("long", 
"这是一间开阔的大厅，周围的墙壁上装饰着各种各样的鸟羽。墙壁正中挂着一
张奇特的大弓。弓两侧有一对垂联，上书： 
"YEL"
            鸟          弦         
            尽          惊        
            弓          电         
            藏          闪         "NOR" 
");
        set("objects", ([
                __DIR__"obj/wall" : 1,
                __DIR__"npc/laonu" : 1,
        ]));
        set("indoors","yinghe");
        set("exits",([
                "north":__DIR__"irongate3",
                "southeast":__DIR__"stonepath",
        ]) );
        //}} 
        setup();
        wall = present("墙壁", this_object());
        bow = new(__DIR__"obj/bow");
        arrow1 = new(__DIR__"obj/arrow");
        arrow2 = new(__DIR__"obj/smallarrow");
        if(objectp(bow)){
                bow->move(wall);
                arrow1->move(wall);
                arrow2->move(wall);
        }
} 
void reset(){
        object bow, wall, arrow1, arrow2, *inv;
   int i;
        
        ::reset();
        
        inv = all_inventory(this_object());
        for(i=0; i<sizeof(inv); i++) {
                if( userp( inv[i]) ) return;
        }
        add("refresh_counter", 1);
        wall = present("墙壁", this_object());
        if ( (int) query("refresh_counter") > 2 ) {
                bow = new(__DIR__"obj/bow");
                arrow1 = new(__DIR__"obj/arrow");
                arrow2 = new(__DIR__"obj/smallarrow");          
                arrow1->move(wall);
                arrow2->move(wall);
                bow->move(wall);
                delete("refresh_counter");
        }
        return;
} 
