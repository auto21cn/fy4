 inherit ITEM;
void create()
{
        set_name("血衣", ({ "bloodcloth", "cloth"}) );
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else 
        {
                set("unit", "件");
                set("long", "一件浸满鲜血的衣服，上面用血写了几个触目惊心的大字：
        “大哥，我在狼山，帮我！”
        
        小马．
\n");
        }
        set("value", 0);
          set("skill", ([
                        "name":         "dagger",             
                        "exp_required": 50000,                          
                        "sen_cost":     50,                     
                        "difficulty":   50,                     
                        "max_skill":    50              
                        ]) );
        ::init_item();
}  
