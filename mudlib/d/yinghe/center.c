 // FY4
#include <ansi.h>
inherit ROOM; 
string stone();
void create()
{
        set("short", "荧河灵界");
        set("long", @LONG
这是一块空旷的土地，土地的中央是一个石台。河水似乎被什么神奇的力量
凌空阻在上方。借着幽幽的河光，可以看到西面似乎是一道金光闪闪的大门。东
面黑沉沉的，好像有间小屋。时而从北面飘来凛凛寒气，时而又从南面吹过阵阵
热风，让人很不舒服。
LONG); 
        //{{ --- by MapMaker
        set("exits",([
        "east":__DIR__"woodcabin",
        "west":__DIR__"golddoor",
        "south":__DIR__"firecave",
        "north":__DIR__"icehall",
        ]) );
        //}}
        set("item_desc", ([
                "stone" : (: stone :),
                "石台" : (: stone :),
        ]));
        set("indoors", "yinghe");
        setup();
} 
string stone(){
        object me;
        
        me = this_player();
        if(me->query("attribute_mark")&& me->query("attribute_mark")!="earth") {        
                tell_object(me, "石台上刻着几个模糊的符号。\n");
        } else {
                tell_object(me, "是台上刻着"HIY"金"HIG"木"HIC"水"HIR"火"NOR + YEL"土"NOR"几个远古的文字。（ｔｏｕｃｈ）\n");
                add_action("do_touch", "touch");
        }
        return "";
} 
int do_touch(string arg){
        object me;
        
        me = this_player();
        if(me->query("attribute_mark")&& me->query("attribute_mark")!="earth" ){
                return 0;
        }
        if(arg == "金" || arg == "jin" || arg == "gold"){
                message_vision("$N把手放在“金”字上。\n", me);
                tell_object(me, HIY"你觉得眼前金光一闪，疑似自己眼花。\n"NOR);
                me->set("attribute_mark", "gold");
        } else if (arg == "木" || arg == "mu" || arg == "wood"){
                message_vision("$N把手放在“木”字上。\n", me);
                tell_object(me, HIG"你似乎透过木门看到一片苍翠的林木。\n"NOR);
                me->set("attribute_mark", "wood");              
        } else if(arg == "水" || arg == "water" || arg == "shui"){
                message_vision("$N把手放在“水”字上。\n", me);
                tell_object(me, HIC"你耳边隐约传来潺潺水声。\n"NOR);
                me->set("attribute_mark", "water");
        } else if(arg == "火" || arg == "fire" || arg == "huo"){
                message_vision("$N把手放在“火”字上。\n", me);
                tell_object(me, HIR"一股灼热之气从你手底的石头上传来。\n"NOR);
                me->set("attribute_mark", "fire");
        } else if(arg == "土" || arg == "earth" || arg == "tu"){
                message_vision("$N把手放在“土”字上。\n", me);
                message_vision(YEL"$N脚下忽然一松，整个人倏地沉了下去！\n"NOR, me);
                me->set("attribute_mark", "earth");
                me->move("/d/yinghe/earthtemple");
        } else {
                return notify_fail("你要摸哪里？\n");
        }
        return 1;
} 
int valid_leave(object who, string dir){
        if(dir == "north" && who->query("attribute_mark") == "water"){
                return 1;
        } else if(dir == "south" && who->query("attribute_mark") == "fire"){
                return 1;
        } else if(dir == "west" && who->query("attribute_mark") == "gold"){
                return 1;
   } else if(dir == "east" && who->query("attribute_mark") == "wood") {
                return 1;
        } else if(dir == "down" && who->query("attribute_mark") == "earth"){
                return 1;
        } else {
                return notify_fail("一股巨大的力量让你无法前进。\n");
        } 
}  
