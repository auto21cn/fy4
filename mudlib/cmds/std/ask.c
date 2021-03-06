 // ask.c
#include <ansi.h> 
inherit F_CLEAN_UP; 
string *msg_dunno = ({
        "$n根本不想回答$N的问题。\n",
        "$n睁大眼睛望著$N：这么简单的问题都要问吗？\n",
        "$n耸了耸肩，很惋惜地对$N说：你真是不可救药！\n",
        "$n对$N说道：嗯....这问题你可以问问自己吗！\n",
        "$n对$N说道：对不起，太多人问我同样的问题了！\n"
}); 
int main(object me, string arg)
{
        string dest, topic, msg;
        string *chat_msg;
        object ob;
        int i;
        mapping inquiry; 
        seteuid(getuid()); 
        if( !arg || sscanf(arg, "%s about %s", dest, topic)!=2 )
                return notify_fail("你要问谁什麽事？\n"); 
        if( !objectp(ob = present(dest, environment(me))) )
                return notify_fail("这里没有这个人。\n"); 
        if( !ob->is_character() ) {
                message_vision("$N对著$n自言自语....\n", me, ob);
                return 1;
        } 
        if( !ob->query("can_speak") ) {
                message_vision("$N向$n打听有关『" + topic + "』的消息，但是$p显然听不懂人话。\n", me, ob);
                return 1;
        } 
        if( !INQUIRY_D->parse_inquiry(me, ob, topic) )
                message_vision("$N向$n打听有关『" + topic + "』的消息。\n", me, ob); 
        if( userp(ob) ) return 1;
        if( !living(ob) ) {
                message_vision("但是很显然的，$n现在的状况没有办法给$N任何答覆。\n",
                        me, ob);
                return 1;
        }
        if(topic == "here"){
                chat_msg = ob->query("chat_msg");
           i = random(sizeof(chat_msg));
                if(sizeof(chat_msg) > 0) {
                        if (stringp(chat_msg[i])){
                                message_vision(chat_msg[i], me, ob);
                                
                        } else { 
                                message_vision("$n说道：嗯....这个问题嘛，让我想一下先！\n", me, ob);
                        }
                } else {
                        message_vision(msg_dunno[random(sizeof(msg_dunno))], me, ob);
                }       
                return 1;
        }
        if( msg = ob->query("inquiry/" + topic) ) {
                if( stringp(msg) ) {
                        message_vision( CYN "$N说道：" + msg + "\n" NOR, ob);
                        return 1;
                }
        } else if (msg = ob->query("inquiry/" + "*")){
                if( stringp(msg) ) {
                message_vision( CYN "$N说道：" + msg + "\n" NOR, ob);
                return 1;
                }
        } else {
                message_vision(msg_dunno[random(sizeof(msg_dunno))], me, ob);
        }
        return 1; 
} 
int help(object me)
{
   write( @HELP
指令格式: ask <someone> about <something>  or ask <someone> about here 
这个指令在解谜时很重要, 通常必须藉由此一指令才能
获得进一步的资讯。
HELP
   );
   return 1;
}     
