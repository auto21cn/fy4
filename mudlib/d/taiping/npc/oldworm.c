#include <ansi.h>
inherit "/d/taiping/npc/smart_npc";
inherit __DIR__"timeshift";
inherit F_VENDOR;
inherit INQUIRY_MSG; 
int blinding();
int bbqthem(object me, object obj); 
void create()
{ 
        set_name("老蛔虫",({"oldworm"}));
        set("long", "
苍白的头发，佝偻着腰，看来不像蛔虫，倒有点像是个虾米。他一张满布皱纹的脸
看来虽然又疲倦，又苍老，一双眼睛里却总是带着恶作剧的笑意。\n");
        set("title","杂货铺老板");
        set("age",60);
        set("combat_exp", 8000000);
        set("reward_npc", 1);
        set("difficulty",15);
                
        set("attitude","friendly");
                
        set("resistance/gin",30);
        set("resistance/kee",50);
        set("resistance/sen",30); 
        set("day_room","/d/taiping/zahuo");
        set("shift/day_leave","$N匆匆忙忙地离开了。\n");
        set("shift/day_arrive","$N笑呵呵地走过来说：“杂货铺开门喽。“\n");
        set("night_room","/d/taiping/droad2");
        set("shift/night_leave","$N探头看了看天色说：“时间不早，关门喽。“随即慢慢走了出去。\n");
        set("shift/night_arrive","$N一声不响地走了过来。\n");
        
        set("dinner_room","/d/taiping/laodian");
        set("shift/dinner_leave","$N伸了个懒腰，“吃饭的时间到喽”，边说边向外走去。\n");
        set("shift/dinner_arrive","$N走过来在八仙桌旁坐了下来。\n");
        set("shift/after_dinner","$N放下筷子，慢慢向门外走去。\n");
        set("shift/back_dinner","$N打着饱嗝走了过来。\n");
                        
        set("nb_chat_chance", 100);
        set("nb_chat_msg_combat", ([
                50:     (: blinding() :),
        ]) );      
        
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
             (: auto_smart_fight(20) :),
        }) );            
        auto_npc_setup("wang",300,200,0,"/obj/weapon/","fighter_w","taiji",2);
        
        set_skill("iron-cloth",150);
        set_skill("xisui",100);
        map_skill("iron-cloth","xisui");
        add_temp("apply/damage",110);
                
        set("vendor_goods", ([
                "/obj/food_item/chicken_egg": 40,
                "/obj/food_item/duck_egg": 40,
                "/obj/food_item/quail_egg":     40,
                "/obj/food_item/goose_egg":     40,
        ]) );
        setup();
        carry_object(__DIR__"obj/hat2")->wear();
        carry_object(__DIR__"obj/pant")->wear();
        add_money("gold", random(8));
}  
void init() {
        
        object me;
        ::init();
        if( interactive(me = this_player()) && !is_fighting() ) {
                remove_call_out("shifting");
                call_out("shifting", 1, me);
        }
        add_action("do_vendor_list", "list"); 
} 
void die() {
        
        object me, ob, owner;
        ob=this_object();
        
        if(objectp(me=query_temp("last_damage_from") ))     
        if(owner=me->query("possessed")) me = owner;
                
        if(file_name(environment(ob))==AREA_TAIPING"droad2") me->set("parrot/杀老蛔虫",1);
        
        ::die();
}
        
int blinding() {
        environment(this_object())->blinding(this_object());
        return 1;
} 
void reset()
{
        set("vendor_goods", ([
                "/obj/food_item/chicken_egg": 40,
                "/obj/food_item/duck_egg": 40,
                "/obj/food_item/quail_egg":     40,
                "/obj/food_item/goose_egg":     40,
        ]) );
}       
