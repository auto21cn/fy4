 // surcoat.c
// Copyright (C) 1995 - 2001, by FengYun Workshop. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
// 
#include <armor.h>
inherit SURCOAT; 
void create() {
        set_name("����", ({ "surcoat" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "��");
                set("value", 30);
                set("armor_prop/armor", 2);
                set("armor_prop/personality", -1);
        }
        ::init_surcoat();
} 
