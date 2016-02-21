 //TIE@FY3
inherit SKILL;
void setup(){
        set("name", "�������");
        set("usage/blade", 1);
        set("usage/parry", 1);
        set("practice_damage", 40);
        set("effective_level", 180);
        set("learn_bonus", -150);
        set("practice_bonus", -150);
        set("black_white_ness", 30);
        set("skill_class", "emei");
        
        set("parry_msg", ({
                "$nʹ��һ�С�͵��������������$v���һ�У�ͻȻ���л�ʽ����ס$n��ȫ����\n",
                "$n����$v��̣���;ͻȻ��ת��һ�С�ָɣ�������סȫ��Ҫ����\n",
                "$nһ�С���ʬ���꡹����Ӱ��������Ʈ��ԭ�أ�����$v��������һ���Ŀ���$N��$w��\n",
                "$nһ�С�������ɽ����������Σ���$N����ʽ������$vȴֱϮ$N֮�ؾȡ�\n",
        }) ); 
        set("unarmed_parry_msg", ({
                "$nһ�С�����Ϊ�����������е�$v������$N����ʽ��\n",
                "$n���ⶪ��������һ�С���ש���񡹣����е���������$N֮�ؾȡ�\n",
                "$n����$v��÷��겻͸��һ�С�������������Ƶ�$N���ֳ��С�\n",
                "$nһ�С�Χκ���ԡ���ȫȻ����$N�Ĺ�����$vֱ��$N��ȥ���Ƶ�$N�����Ա���\n",
        }) );   
        action = ({
                ([      "action":               "$N���ϸ��ֳ�һ˿�����Ц�ݣ�ͻȻʹ��һ�С�Ц��ص���������$wֱ��$n��$l��",
                        "damage":               70,
                        "dodge":                200,
                        "parry":                200,    
                        "damage_type":  "����"
                ]),
                ([      "action":               "$Nʹ��һ�С��û��١�����$w�����������⣬ӳ��$n�ۻ����ң��û�ƽ��$n��$l��",
                        "damage":               80,
                        "dodge" :               100,
                        "parry" :               100,
                        "damage_type":  "����"
                ]),
                ([      "action":               "$N������Σ�$w����һ�С������������ݺݿ���$n��$l",
                        "damage":               80,
                   "dodge" :               100,
                        "parry" :               100,
                        "damage_type":  "����"
                ]),
                ([      "action":               "$N����һ����һ�С����׳�н����$w��$n��$lбб�ó�һ��",
                        "damage":               40,
                        "dodge" :               10,
                        "parry" :               10,
                        "damage_type":  "����"
                ]),
                ([      "action":               "$N����$w�ó����쵶�⣬һ�С���ˮ���㡹��������ɣ�������Ϣ��ת��$n�ı����Ͷ�$n��$l",
                        "damage":               90,
                        "dodge" :               200,
                        "parry" :               100,
                        "damage_type":  "����"
                ]),
                ([      "action":               "$N��$w�߻��Σ�һ�С����Ŵ򹷡�����ס$n����·������ֱ��$n��$l",
                        "damage":               30,
                        "dodge" :               200,
                        "parry" :               100,
                        "damage_type":  "����"
                ]),
                ([      "action":               "$Nһ�С�������������$w�ҷ磬���϶��£������㿳��$n��$l",
                        "damage":               50,
                        "dodge" :               200,
                        "parry" :               100,
                        "damage_type":  "����"
                ]),
        ([      "action":               "$Nһ�С���ݾ��ߡ���$w�����񿳣�����$n�ľ���ս��",
                "damage":               200,
                "dodge" :               200,
                "parry" :               100,
                "damage_type":  "����"
        ]),
        ([      "action":               "$Nʹ��һ�С�˳��ǣ�򡹣�$w������������$n����һ����б����˳��һ��",
                "damage":               50,
                "dodge" :               100,
                "parry" :               100,
                "damage_type":  "����"
        ]),
        ([      "action":               "$N����һ��������$w�󿪴�ϣ�һ�С�Զ������������Բ�����������磬��$n����Χס",
                "damage":               80,
                "dodge" :               80,
                "parry" :               80,
                "damage_type":  "����"
        ]),
        ([      "action":               "$N����$wһ�С���;��뽡������˺�һ����ɱ��ȥ��ͻȻ����һ��������$n��$l",
                "damage":               100,
                "dodge" :               200,
                "parry" :               100,
                "damage_type":  "����"
        ]),
        ([      "action":               "$Nһ�С��赶ɱ�ˡ�������������һ������$n��$l",
                "damage":               10,
                "dodge" :               200,
                "parry" :               100,
                "damage_type":  "����"
        ]), 
        });
}
int valid_learn(object me)
{
    if( (int)me->query("max_force") < 200 ){
            return notify_fail("�������������û�а취�����������\n");
        }
        if(!::valid_learn(me)){
                return 0;
        }
    return 1;
} 
int practice_skill(object me)
{
        if((int)me->query("force") < 10 ){
                return notify_fail("��������������������������������\n");
        }
        if(!::practice_skill(me)){
                return 0;
        }
        me->add("force", -10);
        return 1;
}     