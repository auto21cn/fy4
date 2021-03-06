 // hu.c
inherit NPC;
#include <ansi.h>
 
void create()
{
        set_name(HIW"白衣人"NOR, ({ "whitecloth man", "man" }) );
        set("gender", "男性" );
        set("age", 32);
        set("str", 30);
        set("int", 20);
        set("cor", 40); 
    set("long",
"清清爽爽的一身白衣裳，文文雅雅的一张笑脸，再加上秋星明月般的一对笑
眼，笑眼中还仿佛不时有白云飘过，悠悠远远的那么样一朵白云。 
\n"
    );
    set("max_gin", 6000);
    set("max_kee", 6000);
    set("max_sen", 6000);
        set("max_force", 10000);
        set("force_factor", 100);
        set("combat_exp", 5000000+random(3000000));
        set("attitude", "friendly");
        set("str", 200);
        set_skill("move",200);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set_skill("unarmed", 200);
        set_skill("force", 130);
        set_skill("flying-dragon", 100);
        set_skill("zuixian-steps", 100);
        set_skill("cloudforce", 90);
        map_skill("move", "zuixian-steps");
        map_skill("dodge", "zuixian-steps");
        map_skill("force", "cloudforce");
        map_skill("unarmed", "flying-dragon");
        map_skill("parry", "flying-dragon");
    set("chat_chance_combat", 15);
    set("chat_msg_combat", ({
        (: perform_action, "longwujiutian" :),
            }) );
        setup();
        carry_object("/obj/armor/cloth", 
                ([      "name"  :       HIW"白衣"NOR ,
                        "long" : "白色长衫，干净平整的没有一丝折痕。"])
                )->wear();
}     
