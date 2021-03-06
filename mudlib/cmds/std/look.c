 // look.c
// Copyright (C) 1995 - 2001, by FengYun Workshop. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
// 
// Last modification:
//              - 07/03/2001 by Daniel Q. Yu.
//
// Last modification:
//              - 10/17/2001 by neon
// 
#include <room.h>
#include <ansi.h>
#include <combat.h>
#include <armor.h>
#include <weapon.h>
inherit F_CLEAN_UP; 
int look_room(object me, object env);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_corpse(object me, object obj);
int look_room_item(object me, string arg);
string getfigure(object me);
string getper(object me, object obj);
string tough_level(int power);
string gettof(object me, object obj);
string getdam(object me, object obj);
string *tough_level_desc = ({
        BLU "不堪一击" NOR,
        BLU "毫不足虑" NOR,
        BLU "不足挂齿" NOR,
        BLU "初学乍练" NOR,
        HIB "初窥门径" NOR,
        HIB "略知一二" NOR,
        HIB "普普通通" NOR,
        HIB "平平淡淡" NOR,
        HIB "平淡无奇" NOR,
        HIB "粗通皮毛" NOR,
        HIB "半生不熟" NOR,
        HIB "马马虎虎" NOR,
   HIB "略有小成" NOR,
        HIB "已有小成" NOR,
        HIB "驾轻就熟" NOR,
        CYN "心领神会" NOR,
        CYN "了然於胸" NOR,
        CYN "略有大成" NOR,
        CYN "已有大成" NOR,
        CYN "豁然贯通" NOR,
        CYN "出类拔萃" NOR,
        CYN "无可匹敌" NOR,
        CYN "技冠群雄" NOR,
        CYN "神乎其技" NOR,
        CYN "出神入化" NOR,
        CYN "傲视群雄" NOR,
        HIC "登峰造极" NOR,
        HIC "所向披靡" NOR,
        HIC "一代宗师" NOR,
        HIC "神功盖世" NOR,
        HIC "举世无双" NOR,
        HIC "惊世骇俗" NOR,
        HIC "震古铄今" NOR,
        HIC "深藏不露" NOR,
        HIR "深不可测" NOR
});  
string *female_weight_desc = ({
        MAG "看来有点弱不禁风" NOR,
        BLU "显得纤弱无力" NOR,
        CYN "体态轻盈" NOR,
        CYN "身材苗条" NOR,
    HIG "曲线窈窕，玲珑有致" NOR,
        HIG "身材恰到好处" NOR,
        NOR "不胖不瘦" NOR,
        YEL "体态微丰" NOR,
        YEL "身材丰满" NOR,
        WHT "心宽体胖" NOR,
        HIR "似乎该减肥了" NOR
});
string *male_strength_desc = ({
        BLU "看来弱不禁风" NOR,
        HIB "好像手无缚鸡之力" NOR,
   CYN "让人微觉瘦弱" NOR,
        CYN "让人觉得气质文弱" NOR,
        HIG "体格刚健英武" NOR,
        NOR "长的不胖不瘦" NOR,
        YEL "行动间孔武有力" NOR,
        YEL "魁梧彪悍" NOR,
        WHT "心宽体胖" NOR,
        HIR "似乎该减肥了" NOR
});  
string *heavy_level_desc= ({
        "极轻",
        "很轻",
        "不重",
        "不轻",
        "很重",
        "极重"  
}); 
void create() { seteuid(getuid()); } 
// main function of this command.
int main(object me, string arg) {
        object obj;
        int result; 
        if(!arg) {
                result = look_room(me, environment(me));
        } else if((obj = present(arg, me)) || (obj = present(arg, environment(me)))) {
                if(obj->is_character()) {
                        if(obj->is_corpse()) result = look_corpse(me, obj);
                        else result = look_living(me, obj);
                        
                } else {
                        result = look_item(me, obj);
                }
        } else {
                result = look_room_item(me, arg);
        }
        
        return result;
} 
// give out room description.
int look_room(object me, object env) {
   int i;
        object *inv;
        mapping exits;
        string roomdesc, str, *dirs; 
        if(!env) {
                write("你的四周灰蒙蒙地一片，什麽也没有。\n");
                return 1;
        } 
        // room descriptions.
        str = sprintf( "%s - %s\n    %s%s",
                        env->query("short"),
                        wizardp(me)? file_name(env)+sprintf(" - (%d,%d,%d)",env->query("coor/x"),
                                        env->query("coor/y"),env->query("coor/z")): "",
                        env->long(),
                        env->query("outdoors")? NATURE_D->outdoor_room_description() : "" ); 
        // exits.
        if(mapp(exits = env->query("exits"))) {
                dirs = keys(exits);
                for(i=0; i<sizeof(dirs); i++) {
                        if((int)env->query_door(dirs[i], "status") & DOOR_CLOSED ) {
                                dirs[i] = 0;
                        }
                }
                dirs -= ({ 0 });
                if(sizeof(dirs)==0) {
                        str += "    这里没有任何明显的出路。\n";
                } else if(sizeof(dirs)==1) {
                        str += "    这里唯一的出口是 " + BOLD + dirs[0] + NOR + "。\n";
                } else {
                        str += sprintf("    这里明显的出口是 " + BOLD + "%s" + NOR + 
                                        " 和 " + BOLD + "%s" + NOR + "。\n",
                                        implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
                }
        } else {
                str += "    这里没有任何明显的出路。\n";
        }
        
        // all things in the room.
        inv = all_inventory(env);
        for(i=0; i<sizeof(inv); i++) {
           if(inv[i]==me || inv[i]->query("no_shown") || !me->visible(inv[i])) {
                        continue;
                }
                str += "  " + inv[i]->short() + "\n";
        } 
        write(str);
        return 1;
} 
// give out item description.
int look_item(object me, object obj) {
        mixed *inv;
        string objdesc, prep; 
        write(obj->long());
        inv = all_inventory(obj);
        if(!obj->is_closed() && sizeof(inv)) {
                switch((string)obj->query("prep")) {
                        case "on":
                                prep = "上";
                                break;
                        case "under":
                                prep = "下";
                                break;
                        case "behind":
                                prep = "后";
                                break;
                        case "inside":
                                prep = "里";
                                break;
                        default:
                                prep = "里";
                                break;
                        }
                inv = map_array(inv, "inventory_look", this_object() );
                message("vision", sprintf("%s面有：\n  %s\n", prep,
                        implode(inv, "\n  ") ), me);
        }
        return 1;
} 
// get personality of the person.
string getper(object me, object obj) {
   int per;
        int spi; 
        int weight, score;
        string str; 
        per = obj->query_per();
        spi = me->query_spi();
        score = (int) obj->query("score");
        
        // 灵性差的人看的不准
        if(spi>35) {
                weight = 0;
        } else {
                weight = (int)(35 - spi)/4 ;
        } 
        if(random(10)>6) {
                per = per - weight;
        } else {
                per = per + weight ;
        }
        //ding->query_default_object(), "/obj/specials/ding/ding")== -1) 
        if((string)obj->query("gender") == "男性") {
                if (per >= 35) {
                        str = "相貌出众,百里挑一。\n";
                } else if(per >= 30) { 
                        str = "风度翩翩，如玉树临风。\n";
                } else if(per >= 25) { 
                        str = "英俊潇洒，貌似潘安。\n";
                } else if(per >= 20) {
                        str = "长身玉立，面如冠玉。\n";
                } else if(per >= 15) {
                        str = "五官端正。\n";
                } else if(per >= 10) {
                        str = "的尊容实在无法恭维。\n";
                        //str = "虎头虎脑，很机灵的样子。\n";
                } else {
                        str = "相貌平平。\n";
                }
        } else if((string)obj->query("gender") == "女性") {
                if(per >= 45) {
                        str = HIG"的美已经难以用笔墨形容，相见之下令人不由魂失神夺！\n"NOR;
           } else if(per >= 40) {
                        str = score > 1000 ? 
                                 "美奂美仑，堪称人间仙子！\n" 
                                :"妖艳绝伦，美目流动间让人神魂颠倒！\n" ;
                } else if(per >= 33) {
                        str = score > 1000 ?  
                                 "娇丽如花，令人情不自禁心生爱怜。\n"
                                :"柔媚娇艳，浑身上下散发着无穷的诱惑。\n";
                } else if(per >= 29) {
                        str = "有沉鱼落雁之容，避月羞花之貌。\n";
                } else if(per >= 24) { 
                        str = score > 1000 ?  
                                 "俏丽可人，一颦一笑间，总是让人怦然心动。\n"
                                :"天生丽质，一双眼睛很会勾人。\n";
                } else if(per >= 18) {
                        str = "风情万种，楚楚动人。\n"; 
                } else if(per >= 14) {
                        str = "玲珑可爱，娇俏喜人。\n"; 
                } else if(per >= 10) {
                        str = "相貌平平，还看得过去。\n";
                } else {
                        str = "的相貌嘛...马马虎虎吧。\n";
                }
        } else {
                if (per >= 35) {
                        str = "非常漂亮可爱。\n";
                } else if(per >= 30) { 
                        str = "还算赏心悦目。\n";
                } else if(per >= 26) {
                        str = "看来挺机灵的。\n";
                } else if(per >= 15) {
                        str = "看来呆头呆脑的。\n";
                } else {
                        str = "怪模怪样,挺吓人的。\n";
                }
        }
        
        return str;
} 
// use skill_power function to calculate the diff between 2 players.
string gettof(object me, object ob) {
        int melevel, oblevel;
//      melevel = COMBAT_D->skill_power(me, SKILL_USAGE_ATTACK) +
//                      COMBAT_D->skill_power(me, SKILL_USAGE_PARRY) + 
//                      COMBAT_D->skill_power(me, SKILL_USAGE_DODGE);
        
        oblevel = COMBAT_D->skill_power(ob, SKILL_USAGE_ATTACK) +
                        COMBAT_D->skill_power(ob, SKILL_USAGE_PARRY) + 
                        COMBAT_D->skill_power(ob, SKILL_USAGE_DODGE); 
        return  tough_level(oblevel);
} 
// give out character description.
int look_living(object me, object obj) {
        string str, limb_status, pro;
        mixed *inv;
        mapping my_fam, fam,my_org,org; 
        if(me!=obj) {
                message("vision", me->name() + "正盯著你看，不知道打些什麽主意。\n", obj);
        }
        
        str = obj->long();
        pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender")); 
        // get age and nationality.
        if((string)obj->query("race")=="人类" && intp(obj->query("age"))) {
                if(userp(obj)) {
                        str +=  sprintf("%s看起来象%s多岁的%s人。\n", pro, 
                                        chinese_number(obj->query("age") / 10 * 10), obj->query("national"));
                } else {
                        str += sprintf("%s看起来约%s多岁。\n", pro, 
                                        chinese_number(obj->query("age") / 10 * 10));
                }
        }
        
        if(!obj->is_corpse()) {
                // Get personality.
                str += pro + getper(me,obj);
                // Get body figure look .. heeheehee
                if ( (string) obj->query_default_object()== "/adm/daemons/race/human.c") 
                        str += pro + getfigure(obj) +"，";
                
           // Get relative skill level and damage level
                str += "武功看起来好象" + gettof(me,obj) + "，";
                str += "出手似乎" + getdam(me,obj) + "。\n";
        }
        
        // If we both has family, check if we have any relations.
        if(obj!=me && mapp(org = obj->query("organization"))
                        && mapp(my_org = me->query("organization"))
                        && org["org_name"] == my_org["org_name"] ) {
                if(org["generation"]==my_org["generation"]){
                	if( org["org_level"] < my_org["org_level"]) {
                		str += pro + "和你同一辈分，是你的上司。\n";
                	} else if ( org["org_level"] > my_org["org_level"] ) {
                		str += pro + "和你同一辈分，是你的下属。\n";
                	} else  str += pro + "和你同一辈分，和你职务一样。\n";
                } else if( org["generation"] < my_org["generation"] ) {
                	if(my_org["leader_name"] == obj->query("name")){
                		str += pro + "是你们组织的首领。\n";
                	} else {
                                if( (string)obj->query("gender") == "男性" )
                                   {str += pro + "是你的大哥。\n";}
                                 else {str += pro + "是你的大姐。\n";}
                	}
                } else{
                	if( (string)obj->query("gender") == "男性" )
                	   {str += pro + "是你的兄弟。\n";}
                	else {str += pro + "是你的小妹。\n";}
                }
        }
                     	
        if(obj!=me && mapp(fam = obj->query("family")) 
                        && mapp(my_fam = me->query("family")) 
                        && fam["family_name"] == my_fam["family_name"] ) {
                if(fam["generation"]==my_fam["generation"]) {
                        if((string)obj->query("gender") == "男性") {
                                str += sprintf( pro + "是你的%s%s。\n",
                                                my_fam["master_id"] == fam["master_id"] ? "": "同门",
                                                my_fam["enter_time"] > fam["enter_time"] ? "师兄": "师弟");
                        } else {
                                str += sprintf( pro + "是你的%s%s。\n",
                                                my_fam["master_id"] == fam["master_id"] ? "": "同门",
                                                my_fam["enter_time"] > fam["enter_time"] ? "师姐": "师妹");
                        }
                } else if( fam["generation"] < my_fam["generation"] ) {
                        if(my_fam["master_id"] == obj->query("id")) {
                                str += pro + "是你的师父。\n";
                        } else if(my_fam["generation"] - fam["generation"] > 1) {
                                str += pro + "是你的同门长辈。\n";
                        } else if(fam["enter_time"] < my_fam["enter_time"]) {
                                str += pro + "是你的师伯。\n";
                        } else {
                                str += pro + "是你的师叔。\n";
                        }
                } else {
                        if(fam["generation"] - my_fam["generation"] > 1) {
                                str += pro + "是你的同门晚辈。\n";
                        } else if(fam["master_id"] == me->query("id")) {
                                str += pro + "是你的弟子。\n";
                        } else {
                                str += pro + "是你的师侄。\n";
                        }
                }
        } 
        // current kee status.
   if(obj->query("max_kee")) {
                str += pro + COMBAT_D->eff_status_msg((int)obj->query("eff_kee") * 100 
                                / (int)obj->query("max_kee")) + "\n";
        }
        
        // inventory message.
        if(obj->query("race") == "人类") {
                str += pro + (obj->is_naked() ? "赤身裸体。\n" : "");
        }
        inv = all_inventory(obj);
        if(sizeof(inv)) {
                inv = map_array(inv, "inventory_look", this_object(), (obj == me || obj->is_corpse()) ? 0 : 1 );
                inv -= ({ 0 });
                if(sizeof(inv)) {
                        str += sprintf("%s\n", implode(inv, "\n  "));
                }
        }
        
        // send out message
        message("vision", str + "\n", me); 
        // reaction from look at other person.
        if(obj!=me  && living(obj) 
                        && random((int)obj->query("bellicosity")/10) > (int)me->query_per()) {
                write(obj->name() + "突然转过头来瞪你一眼。\n");
                COMBAT_D->auto_fight(obj, me, "berserk");
        } 
        return 1;
} 
// give out corpse description.
int look_corpse(object me, object obj) {
        string str, limb_status, pro;
        mixed *inv;
        mapping my_fam, fam; 
        if(me!=obj) {
                message("vision", me->name() + "正盯著你看，不知道打些什麽主意。\n", obj);
        }
        
        str = obj->long();
        pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender")); 
        // Give the corpse looking.
   str +=  sprintf("%s的相貌吗... 都已经死了，还有什么好看的！\n", pro);  
        inv = all_inventory(obj);
        if(sizeof(inv)) {
                inv = map_array(inv, "inventory_look", this_object(), (obj == me || obj->is_corpse()) ? 0 : 1 );
                inv -= ({ 0 });
                if(sizeof(inv)) {
                        str += sprintf("这里面有：\n");
                        str += sprintf("%s\n", implode(inv, "\n  "));
                }
        }
        else str += sprintf("这里面什么都没有。"); 
        // send out message
        message("vision", str + "\n", me);
        return 1;
}  
// inventory messages.
string inventory_look(object obj, int flag) {
        string str, desc;
        object me, left, right; 
        str = obj->short();
        if(obj->query("equipped")) {
                if(!desc = obj->query("armor_worn")) {
                        if(!desc=obj->query("weapon_wielded")) {
                                desc = "√";
                        } else {
                                me = environment(obj);
                                left = me->query_temp("left_hand");
                                right = me->query_temp("right_hand");
                                if(obj == left && obj == right) {
                                        desc = "双手" + desc + "着";
                                } else if(obj == right) {
                                        desc = "右手" + desc + "着";
                                } else {
                                        desc = "左手" + desc + "着";
                                }
                        }
                }
                str = desc + str;
        } else if(!flag) {
                str = (environment(obj)->is_character() && !environment(obj)->is_corpse() ? 
                           "怀藏" : "  ") + str;
        } else {
                return 0;
        }
        
        return str;
} 
int look_room_item(object me, string arg)
{
        object env;
        mapping item, exits; 
        if( !objectp(env = environment(me)) )
                return notify_fail("这里只有灰蒙蒙地一片，什麽也没有。\n"); 
        if( mapp(item = env->query("item_desc")) && !undefinedp(item[arg]) ) {
                if( stringp(item[arg]) )
                        write(item[arg]);
                else if( functionp(item[arg]) )
                        write((string)(*item[arg])(me));
                        
                return 1;
        }
        if( mapp(exits = env->query("exits")) && !undefinedp(exits[arg]) ) {
                if( objectp(env = find_object(exits[arg])) )
                        look_room(me, env);
                else {
                        call_other(exits[arg], "???");
                        look_room(me, find_object(exits[arg]));
                }
                return 1;
        }
        return notify_fail("你要看什麽？\n");
} 
// return power level.
string tough_level(int power) {
        int lvl;
        
        if(power <= 1) {
                lvl = 0;
        } else { 
                lvl = pow(power, 0.25);
   }
        if(lvl >= sizeof(tough_level_desc)) {
                lvl = sizeof(tough_level_desc)-1;
        } else if(lvl < 0) {
                lvl = 0;
        } 
        return tough_level_desc[lvl];
} 
string getdam(object me, object obj) {  
        int str, level, max_str, max_level;
        
        max_str = 100;
        max_level = sizeof(heavy_level_desc) - 1;
        
        str = obj->query_str();
        level = str * max_level / max_str;
        level = level > max_level ? max_level : level; 
        
        return heavy_level_desc[level];
} 
string getfigure(object me) {   
        int str, ruler, level, exp, agi;
        exp =(int) me->query("combat_exp");
        str = me->query("str");
        agi = me->query("agi");
        if (me->query("gender")=="女性") {
            str = str>50 ? 25 + str/2 : str;
            str = str >25 ? str*10/(agi+1) + 20 : str;
            ruler = sizeof(female_weight_desc)-1;
            level = str >120 ? ruler : ( str/5 - str*str/1440) ;
            level = level > ruler ? ruler : level; 
            return female_weight_desc[level];
        }
        else {
            str = str>60 ? 30 + str/3 : str;
            str = str >30 ? str*10/(agi+1) + 20 : str;
            ruler = sizeof(male_strength_desc)-1;
            level = str >120 ? ruler : ( str/6 - str*str/1440) ;
            level = level > ruler ? ruler : level; 
            return male_strength_desc[level];
   }
}  
int help (object me) {
        write(@HELP
指令格式: look [<物品>|<生物>|<方向>]
 
这个指令让你查看你所在的环境、某件物品、生物、或是方向。
 
HELP
);
        return 1;
}   
