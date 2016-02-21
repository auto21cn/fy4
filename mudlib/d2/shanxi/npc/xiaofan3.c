 inherit NPC;
inherit F_VENDOR;
#include <ansi.h>
void create()
{
        set_name("货郎",({"seller","xiaofan"}));
        set("title","山西七义");
        set("long","一个白脸无须，斯文含蓄的中年商人。\n");
        set("gender","男性");
        set("age",33);
        set("combat_exp", 2500000);
        set("attitude", "friendly");
        set("per",30);
        set("vendor_goods", ([
               
                "/d2/shanxi/npc/obj/huafen":10, 
        ]) );
         set("class","beggar");
         
        set_skill("move", 200);
        set_skill("force", 200);
        set_skill("unarmed", 160);
        set_skill("parry", 150);
        set_skill("dodge", 150);
        set_skill("staff",1);
                        
        set_skill("qidaoforce", 150);
        set_skill("doggiesteps",200);
        set_skill("dragonstrike",170);
        set_skill("dagou-stick",180);
        
        map_skill("unarmed","dragonstrike");
        map_skill("force", "qidaoforce");
        map_skill("dodge","doggiesteps");
        map_skill("move","doggiesteps");
        map_skill("parry","dagou-stick");
        map_skill("staff","dagou-stick");
        
         set("chat_chance_combat", 100);
         set("chat_msg_combat", ({

            (: perform_action, "staff.tianxiawugou" :),
            }) ); 
       // set("chat_chance_combat", 1);
        set("chat_chance",1);
        set("chat_msg",({
                //"小贩瞪眼道：“你知不知道肉包子本来就是用来打狗的。”\n",
                //  (: random_move :),
        }) );
        
        setup();
        carry_object("/obj/armor/cloth")->wear();    
        carry_object(__DIR__"obj/biandan")->wield();  
} 
void init()
{       
   
        add_action("do_vendor_list", "list");
} 

void reset()
{
        set("vendor_goods", ([
            "/d2/shanxi/npc/obj/huafen":10, 
                 
        ]) );
} 