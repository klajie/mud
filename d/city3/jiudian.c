inherit ROOM;
void create()
{
        set("short", "�سǾ�¥");
        set("long", @LONG
����һ����������������Ĵ��¥����˵���ϵ�������ȴ
Ҳ���ɲ��������������Ϲ���һ�������ң���д���񶼾�¥��
��������֡�¥�������ξ������п������κ��ݣ�ʮ���Ǹ���
��֡�����һ�Ұ����ϵ꣬�������ڵ���λ�ƹ��Ѿ��ǵ��Ĵ�
��˵���ᶽ�����е㲻�����ȴҲ����������¥���ս�����
���Ͻ���һ������ͨ��¥������������������Գ�������֡�
LONG );
        set("exits", ([
                "southwest" : __DIR__"eastroad1",
                "east" : __DIR__"chufang",
        ]));
        set("objects", ([
                __DIR__"npc/tanghua" : 1,
                __DIR__"npc/xiaoer2" : 1,
        ]) );
        setup();
        replace_program(ROOM);
}