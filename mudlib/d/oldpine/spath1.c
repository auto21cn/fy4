 // Room: /d/oldpine/spath1.c
inherit ROOM; 
void create()
{
        set("short", "�ּ�С·");
        set("long", @LONG
������������һƬ�������е�С·�ϣ�С·����ͨ��һ���յأ�һ
��޴���������������ڿյ����룬С·������һ�����������µ�����
��·���㼣�ܶ࣬��Ȼ�����˾�����
LONG
        );
        set("objects", ([ /* sizeof() == 3 */
  __DIR__"npc/tall_bandit" : 1,
  __DIR__"npc/fat_bandit" : 1,
  __DIR__"npc/bandit" : 1,
]));
        set("outdoors", "oldpine");
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"clearing",
  "south" : __DIR__"spath2",
]));
        set("no_clean_up", 0); 
        set("coor/x",520);
        set("coor/y",2360);
        set("coor/z",100);
        setup();
        replace_program(ROOM);
}       