 // TIE@FY3
#include <armor.h>
inherit NECK;
#include <ansi.h>
void create()
{
        set_name(HIY"最佳新人奖牌"NOR, ({ "gold pai" }) );
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "串");
                set("long", @LONG
ｓｕｍｘｉｎ风云对一些有贡献的新人的奖牌，标志着这个玩家曾为大家服务
很多。虽然名利只是身外物，但这些进取的精神值得我们所有人学习。奖牌後
面刻着『鞠躬尽瘁　风云人物』。
LONG);
                set("material", "stone");
                set("armor_prop/armor", 300);
                set("armor_prop/composure",50);
        }
        ::init_neck();
} 
