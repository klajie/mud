inherit ROOM;

void create()
{
        set("short", "��ʯ̲");
        set("long", @LONG
�����ʯ������·�������ߣ���С�ľ�Ҫˤ������������
��Ƭʯ̲�����ǳ������ߡ�
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "south" : __DIR__"road5", 
                "northeast" : __DIR__"road3",
        ]));

        set("objects", ([
                "/d/beijing/npc/old2" : 1,
        ]));
        setup();
        replace_program(ROOM);
}