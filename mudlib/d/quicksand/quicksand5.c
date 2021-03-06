 // Room: /d/chuenyu/trap_castle.c
#include <ansi.h>
#include <room.h> 
inherit ROOM;
int do_sanddrop(object me, object obj);
void create()
{
        set("short", "流沙");
        set("long", @LONG
你已经陷入流沙之中，四周没有一点着力的地方。你一点点地向下落去。除非
有人拉(pull)你一把，想活着离开这里恐怕比登天还难。你似乎已经看到黑白无常
在向你招手。
LONG
        ); 
        set("NONPC",1);
        set("coor/x",-1060);
        set("coor/y",-20);
        set("coor/z",-10);
        setup();
} 
void init()
{       object ob;
        if( interactive( ob = this_player()))
        {
        remove_call_out("sinking");
        call_out("sinking", 1, ob);
        }
} 
int sinking(object ob) 
{
        int i;
        int damage;
        if( ob && environment(ob) == this_object())
        {
        message_vision(HIW"$N又在流沙中陷深了一些！！", ob);
        message_vision("$N几乎在绝望中哭了出来！！\n"NOR, ob);
        damage = random(5)+1;
        i =  (int)ob->query("kee");
        ob->set("kee",(int) i - damage);
        if( environment(ob) == this_object())
   call_out("sinking",random(5)+5, ob);    
        }
        else 
        return 1;
}
int do_quit()
{
        object me, *inv;
        int i;
        me = this_player();
                inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++) {
                        do_sanddrop(me, inv[i]);
                }
}
int do_sanddrop(object me, object obj)
{
        mixed no_drop;
        if( no_drop = obj->query("no_drop") )
                return 0;
        if (obj->move(environment(me))) {
                if( obj->is_character() )
                        message_vision("$N将$n从背上放了下来，躺在地上。\n", me, obj);
                else {
                        message_vision( sprintf("$N丢下一%s$n。\n",     obj->query("unit")),
                                me, obj );
                        me->save();
                        if( !obj->query("value") && !obj->value() ) {
                                write("因为这样东西并不值钱，所以人们并不会注意到它的存在。\n");
                                destruct(obj);
                        }
                }
                return 1;
        }
        return 0;  
}
