 inherit ROOM;
#include <ansi.h> 
void create() 
{
        set("short", "山道");
        set("long", @LONG
山路更见崎岖，乱石丛中几棵野草顽强地伸出头来。群山似在远处，又似在近
处，在这孤寂的山谷里，却像哀伤的笛韵，流露出人间侧腓的哀息。
LONG
        );
        set("exits", ([ 
        "southdown" : __DIR__"road0",
        //"southup" : __DIR__"road2",
        "westup" : __DIR__"road1a",
        ]));
        set("objects", ([
                __DIR__"obj/grass": 1,
        ]) );
        set("outdoors", "eren");
set("coor/x",-1020);
        set("coor/y",165);
        set("coor/z",15);
        setup();
        replace_program(ROOM);
}  
