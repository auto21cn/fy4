#include <ansi.h>
//inherit "/d/taiping/npc/smart_npc"; 
inherit NPC;
void create()
{
        set_name("��С��",({"ma xiaobao","xiaobao"}));
        set("long","
С����С���������е�һ˫�ĸα�������������Ҫʲô����ȫ�������Ӧ��
���������£�������Ҳû���𱸹�����һ�䡣ֻҪһ���������ͻ������ǵ�
��ȥ�档\n");
        
        set("gender","Ů��");
        set("group","ma");
        
        set("age",10);          
        set("int",52);
        set("cor",30);
        set("cps",20);
        
        set_skill("unarmed",200);
        set_skill("dodge",150);
        set_skill("parry",160);
        set_skill("force",180);
        set_skill("move",200); 
                
        
        set("combat_exp",50000);  
        set("attitude", "friendly");
        
        set("inquiry", ([
                "*":    "���¶�ȥ���Ұ�����ɡ�\n",
        ]));
        
        set("nb_chat_chance", 100);
        set("nb_chat_msg_combat", ([ 
        ]) );           
        
        set("chat_chance_combat", 100);
/*        set("chat_msg_combat", ({
             (: auto_smart_fight(30) :),
        }) ); */
        set("chat_chance",1);
        set("chat_msg",({
                "��С�������ıĵش����ݱ������ݣ��ִ����ݳ�����ݡ�\n",
        }) );                   
        
                
   setup();
        carry_object("/obj/armor/cloth")->wear();
 
}        