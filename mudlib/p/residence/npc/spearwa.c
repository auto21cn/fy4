 // banker.c
#include <ansi.h>
inherit NPC;
inherit F_BANKPAWNOWNER;
inherit F_VENDOR;
string ask_me(object who); 
void create()
{
        set_name("林翁", ({ "waiter", "mentong" }) );
        set("title", "忠仆");
        set("gender", "男性" );
        set("age", 88);
        set("richness",1000000);
        set("str", 82);
        set("cor", 30);
        set("cps", 30);
        set("int", 26);
        set("per", 53);
        set("con", 24);
        set("spi", 30);
        set("kar", 25);
        set("long",
"一个童颜鹤发的仆人，负责帮主人打扫房间，看管物品。\n"
                );
        set("chat_chance", 2);
        set("chat_msg", ({
                "林翁咳嗽了两声，捶了捶背。\n",
                }) );
        set("combat_exp", 60000000);
        set("fly_target",1);
        set("attitude", "friendly");
        set("env/wimpy", 70);
        set("max_atman", 1000);
        set("atman", 1000);             
        set("atman_factor", 3);
        set("max_force", 1000);
        set("force", 1000);
        set("force_factor", 3);
        set("max_mana", 1000);
        set("mana", 1000);
   set("mana_factor", 3);
//      set("price_index",0);
        set_skill("parry", 200);
        set_skill("axe", 200);
        set_skill("dodge", 200);
        set_skill("force", 100);
        set_skill("xuanyuan-axe", 100);
        map_skill("axe","xuanyuan-axe");
        map_skill("parry","xuanyuan-axe");

        setup();
        carry_object("/obj/armor/cloth")->wear();
        carry_object("/obj/weapon/axe")->wield();
  
} 
void init()
{
        ::init();
        
        add_action("do_value", "value");
        add_action("do_pawn", "pawn");
        add_action("do_sell", "sell");
        add_action("do_redeem", "redeem");
        add_action("do_vendor_list","list");
        add_action("do_loan","loan");
        add_action("do_convert", "convert");
        add_action("do_deposit", "deposit");
        add_action("do_balance", "balance");
        add_action("do_withdraw", "withdraw");
} 
int accept_fight(object me)
{
        command("say 想打架？！毛头小子居然来捣乱？！");
        command("heng");
        kill_ob(me);
        return 1;
}
       
