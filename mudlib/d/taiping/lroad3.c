 inherit ROOM;
void create()
{
        set("short", "鹅卵小道");
        set("long", @LONG
花树假山交错，鹅卵石砌成的路，小径纵横，迷朦夜色中，简直八阵图也似，
建造这座庄园的人必非寻常之辈。白玉般的三重石阶尽处，一座大堂。大堂中灯火
通明，光如白昼。
LONG
        );
        set("exits", ([ 
                "north" : __DIR__"village2",
                "south" : __DIR__"lroad2",
        ]));
        set("outdoors", "taiping");
        set("no_fly",1);
        set("item_desc", ([
                    
        ]));
        set("coor/x",0);
        set("coor/y",0);
        set("coor/z",0);
        setup();
        replace_program(ROOM);
}   
