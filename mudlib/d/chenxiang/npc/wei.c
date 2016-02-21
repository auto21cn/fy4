 inherit NPC;
#include <ansi.h> 
void create()
{
        set_name("����ӥ", ({ "wei tianying", "wei"}) );
        set("gender", "����" );
        set("age", 34);
        set("per", 35);
        set("agi",30);
        set("int",30);
        set("class","legend");
        set("attitude","friendly");
        set("max_force", 1000);
        set("force", 1000);
        set("force_factor",30);
        set("nickname", HIR"ħ��"NOR);
        set("title", "������ ʮ��ɷ");
        set("long","һ�����£�ӥצ��ɿݵ��ֽ������Űѵ�����ǲ�ʱ¶����Ū��Ц�ݡ�\n");
        set("combat_exp", 2900000);
        
        set_skill("move", 130);
        set_skill("dodge", 130);
        set_skill("force", 130);
        set_skill("literate", 130);
        set_skill("blade",130);
        set_skill("puti-steps",120);
        set_skill("shortsong-blade", 120);
        set_skill("xiaochengforce",130);
        set_skill("lingxi-zhi",150);
        set_skill("unarmed",150);
        set_skill("move",150);
        
        map_skill("unarmed","lingxi-zhi");
        map_skill("move","lingxi-zhi");
        map_skill("dodge", "puti-steps");
        map_skill("force", "xiaochengforce");
        map_skill("blade", "shortsong-blade");
        
        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "blade.duangechangmeng" :),
        }) );
        
        set("chat_chance", 1);
        set("chat_msg", ({
                "����ӥ���¶���п����Ц���ٺٵ���һ���Ʋ����ͽ���������Ǯ\n��������������������Ȥ��\n",
                "����ӥ�ٺ���Ц�������ϰ��񾩣�����ſ�ڵ��ϸ�����һ�������ã�\n������ȥ��������\n",
        }) );
        set("inquiry",([
        "��ȸͼ"  :"�ٺ١������ô����˵������˵����\n",
        "design"  :"�ٺ١������ô����˵������˵����\n",
        "����"  :"ʲô���ϰ��񾩣�����������ӥ�����ǵ���һ�����ࡣ����������\n",
        "bai"  :"ʲô���ϰ��񾩣�����������ӥ�����ǵ���һ�����ࡣ����������\n",
        "Ԭ��ϼ"  :"������������е�֡�����Ī�ǡ�����\n",
        "yuan"  :"������������е�֡�����Ī�ǡ�����\n",
                ]) ); 
        setup();
        carry_object(__DIR__"obj/black_cloth")->wear();
        carry_object(__DIR__"obj/long_blade")->wield();
        add_money("gold", 5);
} 
void init()
{
        object ob;
        ::init();
        ob = this_player();
        call_out("greeting", 1, ob);
} 
int greeting(object ob)
{       
        object room;
        object hotel;
        room = find_object("/d/chenxiang/fyyard");
        if(!objectp(room)) room = load_object("/d/chenxiang/fyyard");
        hotel = find_object("/d/chenxiang/tingfengge");
        if(!objectp(hotel)) hotel = load_object("/d/chenxiang/tingfengge");
        
        if (room == environment(this_object()) && ob->query_temp("marks/longlife_getmap"))  
        {
                message_vision("$N������Ц�ţ�ɱ���ҵ����£�͵���ҵ��鱦�����Ӳ�С����\n",this_object());
           this_object()->kill_ob(ob);
                ob->kill_ob(this_object());
                return 1; 
        }
        if( hotel == environment(this_object()) && ob->query_temp("marks/longlife_getmap") ) {
                this_object()->remove_all_killer();
                ob->remove_all_killer();
        }
        return 0;
}   