#include <ansi.h>
inherit NPC;
inherit F_PAWNOWNER;
inherit F_VENDOR;
void create()
{
        set_name("好心的伙计", ({ "good waiter" }) );
        set("gender", "男性" );
        set("age", 33);
        set("richness",1000000000);
        set("combat_exp", 50);
        set("no_arrest",1);
        set("attitude", "friendly");
        setup();
        carry_object("/obj/armor/cloth")->wear();
} 
void init()
{       
        object ob; 
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_value", "value");
        add_action("do_pawn", "pawn");
        add_action("do_sell", "sell");
        add_action("do_redeem", "redeem");
        add_action("do_vendor_list","list"); 
} 
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(5) ) {
                case 0:
message_vision("$N说道：这位"+RANK_D->query_respect(ob)+
"，风味的牛肉，试过了吗？\n",this_object(),ob);
                        break;
                case 1:
message_vision("$N说道："
+ "侬还是将身上所有值钱的东西典在这吧，最近外面太多强盗了！\n",this_object(),ob);
                        break;
                case 2:
message_vision("$N抬头环扫了一眼四周：咦，又一个去生面孔。\n"
,this_object(),ob);
                        break;
                                }
}  