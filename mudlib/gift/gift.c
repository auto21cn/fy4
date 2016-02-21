#include <ansi.h>
inherit ITEM;
void create()
{
    set_name( RED "圣诞礼物" NOR, ({ "gift" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "件");
            set("material", "cloth");
            set("long", "一个大大的礼包，提在手里沉甸甸的，好像里面塞满了东西，你似乎可以打开(open)。\n");
        

          }
    ::init_item();
} 
void init()
{ 
        if(environment()==this_player())
                add_action("do_open","open");
} 
int do_open(string arg)
{
        object gold, note,gift,me;
        object weapon,obj;
        int exp,pot,score,gold1;
        me = this_player();
        exp=10000+random(5000);
        pot=5000+random(2500);
        score=500+random(500);
        gold1=800+random(200);
        if(arg != "gift" && arg != "圣诞礼物") return 0;
        if (me->query("open"))
            return notify_fail("你已经开过礼物了，做人不能太贪心！\n");
        if(query("opened"))
                return notify_fail("圣诞礼包好像被人打开过了，里面的东西被人拿光了！\n");
        gold = new("/obj/money/gold");
        gold->set_amount(gold1);
        gold->set("name","金叶子");
        gold->set("base_unit","张");
        gold->move(this_player());
        me->add("combat_exp",exp);
        me->add("potential",pot);
        me->add("score",score);
        note = new("/gift/note");
        switch(random(5))
        {
        	case 0:
        	    gift=new("/d/wolfmount/npc/obj/zhuguo");
        	    gift->move(this_player());
        	    break;
        	case 2:
        	    gift=new("/d/daimiao/obj/forcedan");
        	    gift->move(this_player());
        	    break;
        	case 3:
        	    gift=new("/d/xinjiang/obj/salt");
        	    gift->move(this_player());
        	    obj=new("/d/xinjiang/obj/salt");
        	    obj->move(this_player());
        	    break;
        } 
        switch(random(5))
        {
        	case 0:
        	      weapon=new("/d/wolfmount/npc/obj/shield");
        	      weapon->move(this_player());
        	      break;
        	case 1:
        	      weapon=new("/d/wolfmount/npc/obj/tigersoul");
        	      weapon->move(this_player());
        	      break;
        	case 2:
        	      weapon=new("/d/wolfmount/npc/obj/putistaff");
        	      weapon->move(this_player());
        	      break;
        	case 3:
        	      weapon=new("/d/wolfmount/npc/obj/skull_whip");
        	      weapon->move(this_player());
        	      break;
        	case 4:
        	      weapon=new("/d/wolfmount/npc/obj/wolf-fist");
        	      weapon->move(this_player());
        	      break;  
        	}   	
        if ( random(80) == 1)
            {
            	note->move(this_player());
            	tell_object(me,WHT"\n恭喜你得到圣诞礼物，圣诞快乐！，你得到了:\n" + chinese_number(gold1) + "张金叶子！\n"+chinese_number(exp)+"点经验！\n"+chinese_number(pot)+"点潜能！\n"+chinese_number(score)+"点评价！\n"NOR);
            	tell_object(me,HIC"\n这时，你突然发现礼包内还有一张红色的"NOR+RED"纸条\n"NOR);
            }
        else
            	tell_object(me,WHT"\n恭喜你得到圣诞礼物，圣诞快乐！，你得到了:\n" + chinese_number(gold1) + "张金叶子！\n"+chinese_number(exp)+"点经验！\n"+chinese_number(pot)+"点潜能！\n"+chinese_number(score)+"点评价！\n"NOR);
        set("opened",1);
        me->set("open",1);
        return notify_fail(HIR "\n你打开圣诞礼包，两眼发光，一阵窃喜！\n\n" NOR);
}
