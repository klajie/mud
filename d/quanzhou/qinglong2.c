// Room: /d/quanzhou/bamboo.c


#include <room.h>
inherit ROOM;


void create()
{
	set("short", "�������ͥ");
	set("long", @LONG
����һƬ���ܵ����֡������˼�������Ω�����ߵ��·�棬��ɮ
��ľ������΢�紵����Ҷ�������������������˳���Ϊ֮һ�ӣ�
���Ǿ��ѵ��������ڡ�
LONG );
	set("exits", ([
		"north" : __DIR__"qinglong",
	]));
//	set("objects",([
//		__DIR__"npc/tang2" : 1,
//	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
