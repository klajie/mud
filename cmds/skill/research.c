// research.c

#include <skill.h>
#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int *query_scale(string skill);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where = environment(me);
        string skill, skill_name;
        int jing_cost, times;
        int is_force_skill;
        int is_parry_skill;
        int lvl;
        string *ks;
        int *ls, *scale;
        int improve;
        int i;
        int t = time();

        if (where->query("pigging"))
                return notify_fail("�㻹��ר�Ĺ����ɣ�\n");

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if (t == me->query_temp("time/research"))
                return notify_fail("��ող��о����������Ҫ�����о�������ָ��"
                                   "�о��Ĵ�������\n");

        if (where->query("no_fight") && me->query("doing") != "scheme")
                return notify_fail("����̫���ӣ���û�����о���\n");

        if (! arg)
                return notify_fail("research|yanjiu <����> <����>\n");

        if (sscanf(arg, "%s %d", skill, times) != 2)
        {
                skill = arg;
                times = 1;
        }

        if (times < 1 || times > 100)
                return notify_fail("�о���������һ�Σ����Ҳ���ܳ���һ�ٴΡ�\n");

        if (me->is_fighting())
                return notify_fail("����ĥǹ������������\n");

        if (! (lvl = me->query_skill(skill, 1)))
                return notify_fail("������㻹���ᣬ�о�ʲô��\n");

        if ((string) SKILL_D(skill)->type() == "knowledge")
                return notify_fail(to_chinese(skill) + "ֻ�ܿ���ѧϰ������ߵġ�\n");

        if (lvl < 180)
                return notify_fail("���" + to_chinese(skill) + "�����ճ̶Ȼ�"
                                   "δ���о��ĳ̶ȡ�\n");

        notify_fail("����Ŀǰ��������û�а취�о����ּ��ܡ�\n");

        if (! SKILL_D(skill)->valid_learn(me)
           || ! SKILL_D(skill)->valid_research(me))
                // ����ѧϰ���ǲ����о�
                return 0;

        if (! XUE_CMD->can_learn(me, skill))
                return 0;

        if ((me->query("potential") - me->query("learned_points")) < times)
                return notify_fail("���Ǳ�ܲ����о���ô����ˡ�\n");

        // Lookup skills for relation skills

        write(HIG "�㿪ʼ�о�" + chinese_number(times) + "���йء�" +
              to_chinese(skill) + HIG "���İ��ء�\n" NOR);
        message("vision", me->name() + "��ڤ��˼����\n", where, ({ me }));

        // calculate the basic effect
        is_force_skill = SKILL_D(skill)->valid_enable("force");
        is_parry_skill = SKILL_D(skill)->valid_enable("parry") && (! is_force_skill);

        ks = keys(me->query_skills());
        ls = ({ });

        for (i = 0; i < sizeof(ks); i++)
        {
                mapping action;
                int eff;

                if (ks[i] == skill)
                        continue;

                if (SKILL_D(ks[i])->main_skill()
                   && SKILL_D(ks[i])->main_skill() != ks[i])
                        continue;

                if (SKILL_D(skill)->valid_enable(ks[i]))
                        ls += ({ me->query_skill(ks[i], 1) });

                if (SKILL_D(ks[i])->valid_enable(skill)
                   || is_force_skill
                   && SKILL_D(ks[i])->valid_enable("force"))
                {
                        // Relation skill
                        action = SKILL_D(ks[i])->query_action(me, 0);
                        eff = (int)me->query_skill(ks[i], 1);

                        if (action)
                        {
                                // do more effect
                                eff += (action["force"] + action["damage"] +
                                        action["attack"] + action["parry"] +
                                        action["dodge"]) * eff / 1000;
                        }
                        ls += ({ eff });
                }
        }
        ls = sort_array(ls, -1);
        scale = query_scale(skill);
        improve = 0;

        for (i = 0; i < sizeof(ls) && i < sizeof(scale); i++)
        {
                /*
                if (lvl >= 500)
                        improve += ls[i] * scale[i] / 4;
                else
                if (lvl >= 300)
                        improve += ls[i] * scale[i] / 2;
                else
                        improve += ls[i] * scale[i];
                        */
                //���ԭ������300����500������о��ٶ� 2016-12-24
                if (lvl >= 500)
                        improve += ls[i] * scale[i] / 2;
                else
                        improve += ls[i] * scale[i];
        }
        improve = improve / 15 / (100 + SKILL_D(skill)->difficult_level());

/*
        if (lvl >= 500)
                improve += lvl / 100 + me->query("int") / 10;
        else
        if (lvl >= 300)
                improve += lvl / 75 + me->query("int") / 6;
        else
                improve += lvl / 50 + me->query("int") / 3;
*/    
//���ԭ������300����500������о��ٶ� 2016-12-24
        if (lvl >= 500)
                //improve += lvl / 75 + me->query("int") / 6;
                //����500����ļ����о��ٶȡ� 2017-02-18
                improve += lvl / 50 + me->query("int") / 6;
        else
                improve += lvl / 50 + me->query("int") / 3;            
       // ת�������������������ڹ����ܵ��о��ٶ�
        if (me->query("special_skill/guimai") && SKILL_D(skill)->valid_enable("force"))
                improve += improve * 50 / 100; 

       //ת���ؼ�����ת�� by н������
        if (me->query("special_skill/wuxing"))
                improve += improve * 20 / 100; 
                
        improve += improve * where->query("research_improve") / 100;
        jing_cost = 1000 / (int)me->query("int");

        if ((int)me->query("eff_jing") < jing_cost)
                return notify_fail("������㾫�����ã�ʵ��û�а취�����о���\n");

        if (! me->can_improve_skill(skill))
        {
                write("Ҳ����ȱ��ʵս���飬��е����Լ����о�" +
                      to_chinese(skill) + "�������ˡ�\n");
                return 1;
        }

        me->set_temp("time/research", t);

        for (i = 0; i < times; i++)
        {
                if ((int)me->query("jing") < jing_cost)
                {
                        if (me->query("env/auto_regenerate")
                           && SKILL_D("force/regenerate")->exert(me, me))
                        {
                                // try to regenerate & learn again
                                write("����þ������һЩ�����������о���\n");
                                i--;
                                continue;
                        } else
                        {
                                me->set("jing", 0);
                                break;
                        }
                }
                me->receive_damage("jing", jing_cost);

                if (! i)
                {
                        skill_name = SKILL_D(skill)->query_skill_name(lvl);
                        if (skill_name)
                                write(sprintf(HIM "���о���һ�ᣬ�ԡ�%s����һ"
                                              "���ƺ���ͨ��Щʲô��\n" NOR,
                                               skill_name));
                        else
                                write(sprintf(HIM "���о���һ�ᣬ�ƺ��ԡ�%s��"
                                              "��Щ�µ�����\n" NOR,
                                              to_chinese(skill)));
                }
                me->improve_skill(skill, random(improve));
                me->add("learned_points", 1);
        }

        if (! i)
                write("�����̫���ˣ����ʲôҲû���о��ɡ�\n");
        else
        if (i > 0 && i < times)
                write("�����̫���ˣ��о���" + chinese_number(i) +
                      "�κ�ֻ��ͣ������Ϣ��\n");

        return 1;
}

int *query_scale(string skill)
{
        if (SKILL_D(skill)->valid_enable("force"))
                skill = "force";

        switch (skill)
        {
        case "parry":
                return ({ 5, 20, 140, 70, 50, 30, 10, 5, 4, 3, 2, 1 });

        case "dodge":
                return ({ 80, 100, 30, 10, 8, 5, 2, 1 });

        case "force":
                return ({ 150, 120, 50, 40, 20, 8, 5, 2, 1 });

        default:
                return ({ 80, 120, 90, 55, 30, 15, 5, 2, 1 });
        }
}

int help(object me)
{
        write(@HELP
ָ���ʽ��research | yanjiu <����> <����>
 
���ָ����������о�һ�ּ��ܵ��������⣬����ʦ������ܵļ�
�������ʱ�򣬿���ͨ���о��Լ�����ߣ����ȵ��ٶ�Ҫ�������
��ܵ����ճ̶Ⱥ���ؼ��ܵ���Ϥ�����أ���Ȼ����Ҳ�����һ
�������ã����ǹؼ����ǿ����ܵ�ˮƽ��һ����˵��صļ���Խ��Խ
�ã��о��������ܻ��°빦����������̫�٣�����ǡǡ�෴��

�������ָ�apprentice, practice, skills, study, learn
HELP);
        return 1;
}