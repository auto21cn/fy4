 inherit ROOM;
#include <ansi.h> 
void create() 
{
        set("short", "�޲��ֿ�");
        set("long", @LONG
���ѳ������������԰�֣�������ֿ�����Щ����ɮ�׹�Ա�����������ֵ�
�ط�����ȥɮ����ɮ�ٵ��ֿ����׹����׹ٵ��ֿ���ÿ�ҹ��塢ÿ����Ժ�����Լ�
��һƬ԰�֡�ǡ�˲���ɽ���µ��޲��ֿ���������������������������ס�أ�����
�ֳƴ����Ĺ���
LONG
        );
        set("exits", ([ 
                "northeast":  __DIR__"lake2",
                "southwest":    __DIR__"sela",
        ]));
        set("objects", ([
                
        ]) );
        set("outdoors", "guanwai");
        set("coor/x",0);
        set("coor/y",0);
        set("coor/z",0);
        setup(); 
}       