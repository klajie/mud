#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC "�����͡�" NOR, ({ "shanshang book", "shanshang", "book" }));
        set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
                set("unit", "��");
		set("long", HIC "����һ�������ȵ�С�ᣬû�¿���"
                            "����(read)��\n" NOR);
		set("value", 50);
		set("material", "paper");
	}
	setup();
}

void init()
{
	add_action("do_read", "read");

}

int do_read(string arg)
{
        if (arg == "shanshang book"
           || arg == "shanshang"
           || arg == "book")
                return notify_fail(HIC "\n"
"----------------------------------------------------------\n\n"
NOR + WHT "                         ��ë��\n\n"
"  ����ʼ��������ʱ��������ȡȵ��Ϊ��֮˵������ë���Ѿ���\n"
"  ����ǧ�����ʷ�ˡ���ë����������Ҫԭ���Ǵ����������ë��\n\n"
"                         ��  ��\n\n"
"  ����ֽ����ȡ����ȡ����ȣ�������������֮��ߡ����ǰ��\n"
"  �����ɵ۵����ɰ���д��һ�����������ȸ裺������������\n"
"  ����˪ѩ����Ϊ�ϻ��ȣ����������¡���������䣬��ҡ΢\n"
"  �緢���������������쭶����ȡ����������У������е�������\n\n"
"                         ��  ��\n\n"
"  �����������磬����С�����磬Я�����㣬��Ϊ����ͨ����Ʒ��\n\n"
"                         �����\n\n"
"  ��֮����ɽ�������Χ���������ߡ��̺�֮���ܹ��ض���֮\n"
"  ȡ����������硢����������֮ʹƽ�������Ͽ�����ɱ����\n"
"  ��ľ�����ǡ���裣����Ϊ����ɫ������������Ϊ������ȡ�\n\n"
"                         ̴����\n\n"
"  ̴��������ȡ̴ľ�Ƴɣ���������С���������磬������������\n\n"
"                         ������\n\n"
"  �����ȶ�Ϊ�赸���ȣ��а��ȫ��֮�֣��ȹ�����Ϊ����Ҳ��\n"
"  ��̴��ľ��ţ�ǵġ�������ø�ʽ˿��ӡ�ϻ���ϻ���ͼ����\n"
"  �еĻ�����������Ƭ���趯ʱѤ����ʽ�����ڡ�\n\n"
"                         �Ž���\n\n"
"  �Ž��ȣ��ֽ����ȡ����ȡ��ѿ��ȡ��������ɣ���������֮ʹ\n"
"  ƽ������Բ�Σ���ϸ��˿���ӽ���Ե��ߣ����������Ϊ����\n"
"  Ϊ���ߡ��н������������ľ�����ᡢ���������Ϊ֮����\n"
"  �Դ��������Ե�Խ��ߣ���Ϊϸ�ߡ���������Ҽ۸������\n\n"
HIC "----------------------------------------------------------\n"
"\n\n" NOR);
}