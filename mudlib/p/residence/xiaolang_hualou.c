#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
  set("short",HIG"画楼"NOR);
  set("long",@LONG
萧十一郎十七岁开始接触中国画，后从师学艺，善于画梅，传说当年
主人为追求一女子，连续两年为其画各种山水花鸟，此女并不为其恒心所
动，主人心灰意冷，决意此生不在画画，虽如此，这里也收藏了古往今来
各大家名画，都乃价值连城的传奇之作。
LONG
  );
  set("exits",([
                 "southdown" : __DIR__"xiaolang2", 
                 "southwest" : __DIR__"xiaolang_shulou",
                 "southeast" : __DIR__"xiaolang_qinlou",                
               ]));
    set("indoors", "residence");
        set("coor/x",15);
        set("coor/y",2036);
        set("coor/z",40);
        set("no_death_penalty",1);
        setup();
    replace_program(ROOM); 
}       