// zhen.c ��ȭ�����־�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int damage;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (objectp(me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʹ�á����־���\n");		
		
        if ((int)me->query_skill("houquan", 1) < 50)
		return notify_fail("��ĺ�ȭ������죬����ʹ�á����־���\n");
	                        
        if ((int)me->query("neili", 1) < 100)
		return notify_fail("����������̫��������ʹ�á����־���\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = CYN "$N" CYN "Ĭ���񹦣�ʹ����ȭ�����־�����ͼ����������$n"
              CYN "��\n" NOR;
	me->add("neili", -80);

	if (random(me->query_skill("force")) > target->query_skill("force") / 2)
	{
		me->start_busy(3);
		target->start_busy(random(3));
		
		damage = (int)me->query_skill("force", 1);
                damage = damage / 3 + random(damage / 3);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30, "����:?");
	} else 
	{
		me->start_busy(3);
		msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ����û���ϵ���\n" NOR;
	}
	message_combatd(msg, me, target);
	return 1;
}