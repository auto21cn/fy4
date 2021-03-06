 inherit NPC;
inherit F_VENDOR;
#include <ansi.h>
void create()
{
        set_name("诸葛小雷", ({ "zhuge" }) );
        set("gender", "男性" );
        set("age", 18);
        set("title", HIG "小急风剑"NOR);
        set("long",
                "当年金狮镖局大镖头诸葛雷的儿子，年纪轻轻，但手下的功夫已经有相当的火候。\n");
        set("combat_exp", 500000);
        set("attitude", "friendly");
        set("per",30);
        set("vendor_goods", ([
               "/obj/weapon/whip":20,
               "/obj/weapon/sword":20,
               "/obj/weapon/axe":20,
               "/obj/weapon/spear":20,
               "/obj/weapon/dart":20,
               "/obj/armor/shield":20,
               "/obj/weapon/hammer_eight":20,
               "/obj/weapon/sword_thin":20,
               "/obj/weapon/dagger.c":20,
               "/obj/weapon/blade.c":20,
              __DIR__"obj/1staff.c":20,
               __DIR__"obj/knife.c":20,
               __DIR__"obj/dual_ring.c":20,
        ]) );
        set_skill("sword",50);
        set_skill("six-chaos-sword",50);
        set_skill("pyrobat-steps",50);
        set_skill("dodge",50);
        set_skill("parry",50);
        map_skill("dodge","pyrobat-steps");
        map_skill("parry", "six-chaos-sword");
        map_skill("sword","six-chaos-sword");
        setup();
        carry_object(__DIR__"obj/jinzhuang")->wear();
        carry_object("/obj/weapon/sword")->wield();
}
void init()
{
        add_action("do_vendor_list", "list");
}  
void reset()
{
        set("vendor_goods", ([
               "/obj/weapon/whip":20,
               "/obj/weapon/sword":20,
               "/obj/weapon/axe":20,
               "/obj/weapon/spear":20,
               "/obj/weapon/dart":20,
               "/obj/armor/shield":20,
               "/obj/weapon/hammer_eight":20,
               "/obj/weapon/sword_thin":20,
               "/obj/weapon/dagger.c":20,
               "/obj/weapon/blade.c":20,
              __DIR__"obj/1staff.c":20,
               __DIR__"obj/knife.c":20,
               __DIR__"obj/dual_ring.c":20,
        ]) );
} 
