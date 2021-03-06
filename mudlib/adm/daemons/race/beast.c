 // beast.c
#include <race/beast.h> 
mapping combat_action =
([
        "hoof": ([
                "action":               "$N用后腿往$n的$l用力狂蹬",
                "damage":               100,
                "damage_type":  "瘀伤",
        ]),
        "bite": ([
                "action":               "$N扑上来张嘴往$n的$l狠狠地一咬",
                "damage":               20,
                "damage_type":  "咬伤",
        ]),
        "claw": ([
                "action":               "$N双爪往$n的$l用力一撕",
                "damage_type":  "抓伤",
        ]),
        "poke": ([
                "action":               "$N冲前往$n的$l一啄",
                "damage":               30,
                "damage_type":  "刺伤",
        ]),
        "kick": ([
                "action":               "$N拼命往$n的$l撞去",
                "damage":               30,
                "damage_type":  "瘀伤",
        ]),
        "endd": ([
                "action":               "$N尾巴拦腰往$n的$l一扫",
                "damage":               30,
                "damage_type":  "瘀伤",
        ]),
        "dragonslash": ([
                "action":               "$N张鳞鼓鬣，跃至$n身前，龙爪往$n的$l一扫",
                "damage":               100,
                "parry" :               400,
                "dodge" :               400,
                "damage_type":  "抓伤",
        ]),
        "dragonbreath": ([
                "action":               "$N一口浊气喷出，顿时天昏地暗，无数飞沙走石铺天盖地地向$n飞去",
                "damage":               100,
                "parry" :               200,
                "dodge" :               200,
                "damage_type":  "瘀伤",
        ]),
        "dragonbite": ([
                "action":               "$N张开血盆大口，冷不防向$n的$l一口咬下",
                "damage":               400,
           "parry" :               400,
                "dodge" :               100,
                "damage_type":  "咬伤",
        ]),
        "dragonswing": ([
                "action":               "$N侧过巨大的身躯，龙尾在空中划个旋，以雷霆之势向$n猛击而下",
                "damage":               200,
                "parry" :               500,
                "dodge" :               100,
                "damage_type":  "抓伤",
        ]),
        "dragonthrow": ([
                "action":               "$N深吸一口气，身躯仿似又长大了数倍，猛然间金光闪耀，数片龙鳞向$n的$l击到",
                "damage":               200,
                "parry" :               100,
                "dodge" :               400,
                "damage_type":  "抓伤",
        ]),
        "dragonpoke": ([
                "action":               "$N巨首左右摆动，龙须若数十根钢针，夹着风雷之势向$n的$l刺去",
                "damage":               100,
                "parry" :               100,
                "dodge" :               100,
                "damage_type":  "抓伤",
        ]),
]); 
string *actions; 
void create()
{
        actions = keys(combat_action);
} 
void setup_beast(object ob)
{
        mapping my;
        my = ob->query_entire_dbase(); 
        my["unit"] = "只"; 
        if( undefinedp(my["actions"]) || !my["actions"]) {
                if( pointerp(my["verbs"]) )
                        ob->set("default_actions", (: call_other, __FILE__, "query_action" :) );
                else
                   my["default_actions"] = ([
                                "action": "$N攻击$n的%s，%s\n",
                        ]);
        }
        
        if( undefinedp(my["gender"]) ) my["gender"] = "雄性";
        if( undefinedp(my["age"]) ) my["age"] = random(30) + 5; 
        if( undefinedp(my["str"]) ) my["str"] = random(25) + 5;
        if( undefinedp(my["cor"]) ) my["cor"] = random(21) + 5;
        if( undefinedp(my["int"]) ) my["int"] = random(21) + 5;
        if( undefinedp(my["spi"]) ) my["spi"] = 0;
        if( undefinedp(my["cps"]) ) my["cps"] = random(21) + 5;
        if( undefinedp(my["per"]) ) my["per"] = random(21) + 5;
        if( undefinedp(my["con"]) ) my["con"] = random(21) + 5;
        if( undefinedp(my["agi"]) ) my["agi"] = random(21) + 15;
        if( undefinedp(my["dur"]) ) my["dur"] = random(2) + 1;
        if( undefinedp(my["fle"]) ) my["fle"] = random(21) + 5;
        if( undefinedp(my["tol"]) ) my["tol"] = random(21) + 5;  
        if( undefinedp(my["max_gin"]) ) {
                if( my["age"] <= 3 ) my["max_gin"] = 50;
                else if( my["age"] <= 10 ) my["max_gin"] = 50 + (my["age"] - 3) * 20;
                else if( my["age"] <= 30 ) my["max_gin"] = 190 + (my["age"] - 10) * 5;
                else my["max_gin"] = my["max_gin"] = 290 + (my["age"] - 30);
        }
        if( undefinedp(my["max_kee"]) ) {
                if( my["age"] <= 5 ) my["max_kee"] = 50;
                else if( my["age"] <= 20 ) my["max_kee"] = 50 + (my["age"] - 5) * 25;
                else my["max_kee"] = my["max_kee"] = 425 + (my["age"] - 20) * 5;
        }
        if( undefinedp(my["max_sen"]) ) {
                if( my["age"] <= 20 ) my["max_sen"] = 50;
                else my["max_sen"] = 50 + (my["age"] - 20) * 10;
        } 
        //      NOTE: beast has no initial limbs defined, you must define it yourself.
        //      ob->init_limbs(LIMBS);
        if( !ob->query_weight() ) ob->set_weight(BASE_WEIGHT + (my["str"] - 10)* 200);
} 
mapping query_action(object me)
{
        string *act; 
   act = me->query("verbs");
        return combat_action[act[random(sizeof(act))]];
} 
