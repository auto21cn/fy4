 // TIE@FY3 ALL RIGHTS RESERVED
//XXDER
inherit ROOM;
void create()
{
        object con,item;
        set("short", "迷雾天梯");
        set("long", @LONG
穿过一片谷地，在雾峰之中，云海之后，居然有一条人工开凿的登山路，
天梯青石铺就，上面雕花以防打滑，极为精致，显见得当年铺造之时花了无数
的气力及心血。
LONG
        );
        set("outdoors","shenshui");
        set("exits", ([ 
  "southwest" : __DIR__"gudi",
  "northup" : __DIR__"tianti2",
]));
        set("objects", ([
                __DIR__"obj/rock" : 1,
                __DIR__"npc/qinggirl" : 2,
        ]) );
        set("outdoors","shenshui");
        set("coor/x",160);
        set("coor/y",12220);
        set("coor/z",10);
        setup();
        con = present("rock",this_object());

}    
