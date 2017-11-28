#include <ansi.h>
#include <combat.h>

#define HENG "��" HIG "̤ѩ�޺�" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (userp(me) && ! me->query("can_perform/hanbing-zhang/hen"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HENG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(HENG "ֻ�ܿ���ʩչ��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((int)me->query_skill("hanbing-zhang", 1) < 100)
                return notify_fail("�㺮���Ʋ�����죬����ʩչ" HENG "��\n");

        if (me->query_skill_prepared("strike") != "hanbing-zhang")
                return notify_fail("��û��׼�������ƣ�����ʩչ" HENG "��\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("����Ṧ��Ϊ����������ʩչ" HENG "��\n");

        if ((int)me->query("neili") < 400)
                return notify_fail("�����ڵ���������������ʩչ" HENG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = me->query_skill("hanbing-zhang", 1) +
             me->query_skill("dodge", 1) / 2;

        dp = target->query_skill("dodge");

        msg = HIC "\n$N" HIC "ŭ��һ����ʩ�����С�" HIG "̤ѩ�޺�" HIC 
              "��ɲʱ�䣬����Ϯ�����죬����$N" HIC "˫��������ת������"
              "����$n" HIC "������$n" HIC "�����Ʒ�֮�¡�\n" NOR;
        message_sort(msg, me, target);
        
        if (random(ap) > dp / 2)
        {
		msg = HIR "$n" HIR "����һ����һʱ�侹�޴�Ӧ�ԣ�"
                      "��������$N" HIR "���Ʒ�֮�С�\n" NOR;

                target->start_busy(ap / 40 + 2);
               	me->start_busy(1);
                me->add("neili", -100);
        } else
        {
                msg = CYN "$n" CYN "����$N" CYN "���޹���֮�⣬��"
                      "�Ǵ󵨷�������$N" CYN "���о������⡣\n" NOR;

                me->start_busy(2);
                me->add("neili", -30);
        }
        message_vision(msg, me, target);

        return 1;
}