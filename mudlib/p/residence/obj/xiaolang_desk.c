 inherit ITEM;
void create()
{
    set_name("红木大桌", ({ "desk" , "红木大桌"}) );
        set_weight(500);
        set_max_encumbrance(8000000);
        set("no_get", 1);
        set("no_shown", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
        set("unit", "张");
        set("long", "一张非常好的红木桌子。\n");
                set("value", 1);
        }
        ::init_item();
} 
int is_container() { return 1; }    
