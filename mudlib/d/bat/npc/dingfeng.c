#include <ansi.h>
inherit NPC;
void goto_batdao(object ob);
void create()
{
    set_name("����", ({ "ding feng", "ding", "feng" }));
    set("long", "
��������������ƮƮ�������������������Ҳ���ú�Ӣ����
���ϸ���Զ������Ц�ݡ�\n" );
 set("nickname", HIC "�����ٷ�" NOR);
 set("gender", "����");
 set("age", 27);
 set("int", 24);
 set("con", 25);
 set("no_arrest",1); 
 set("force", 500);
 set("max_force", 500);
 set("force_factor", 50);
 set("combat_exp", 800000);
 set("attitude", "friendly");  
 set("chat_chance", 1);
 set("chat_msg", ({
"�����૵�����ɽ����һ�ס����ʮ��ʽ����ȷ�����������������ܼ���
�����صġ��������ʽ�����������硣\n ",
"����΢Ц���������ʮ��ʽ��������ڡ��嵭������,���������ǣ��������ޣ�
��ʵ���飬�Ʊ�δ�� ��\n",
 }) );
 set("inquiry",([
  "���ʮ��ʽ" : "�����˻�ɽ��ɽ֮��������ȴʧ���ˣ�����\n",
 ]) );
        set_skill("unarmed", 70);
        set_skill("move", 100);
        set_skill("dodge", 100);
        set_skill("parry", 90);
        set_skill("force", 90);
        set_skill("sword", 90);
        set_skill("dugu-sword", 140);
        set_skill("zixia-force", 90);
        set_skill("huashan-steps", 90);
        map_skill("force", "zixia-force");
        map_skill("move", "huashan-steps");
        map_skill("parry", "dugu-sword");
        map_skill("sword", "dugu-sword");
        map_skill("dodge", "huashan-steps"); 
        setup();
        carry_object("/obj/armor/cloth")->wear();
        carry_object("/obj/weapon/sword")->wield(); 
}   
void init() 
{ 
     ::init(); 
    if( !query_heart_beat(this_object()) ) set_heart_beat(1); 
}   
int accept_object(object who, object ob)
{
    object room;
    if((string) ob->query("id") == "qing feng book")
    {
 //       remove_call_out("verygood_job");
        call_out("verygood_job",2, who);
        return 1;
    }
    else message_vision("�����$N˵�������������ûʲô��ϵ��\n", who);
    return 0;
} 
int verygood_job(object who)
{
  object room;
  if(!objectp(who)) return 1;
  if (who->is_ghost()) return 1;
  command("smile");
  command("say �ã���������������Ҫ�ҵ����ˣ����ϴ������¹������ȥ��\n");
  tell_object(who, GRN "���ϲ��������������������˴󺣴�.......\n\n" NOR ) ;
  message_vision("����һ�������ϴ���æ����һ��������ඣ�\n", who);
  message_vision("�������𷫣������򶫷����С�\n\n", who);
  room = load_object(AREA_BAT"dahai");
  who->move(room);
//destruct(this_object());
  return 1 ;
}       