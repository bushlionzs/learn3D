--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300578_g_MissionId 				= 	9334                     --����ID
x300578_g_ScriptId 					= 	300578                  --�ű�ID
x300578_g_MissionKind 				= 	1                       --��������
x300578_g_LevelLess					= 	40                      --�������ŵȼ�  <=0 ��ʾ������


x300578_g_MissionName				= 	"�����ˡ��Ƶ�����"
x300578_g_MissionName1				= 	"��ʲôʱ����Գ���"
x300578_g_MissionTarget				= 	"ǰ��@npc_85055��@npc_85056��ѯ������ŵ�ˮ���ǣ�ȷ����������"
x300578_g_MissionTarget1				= 	"ѯ��ˮ���ǣ�ȷ����������"
x300578_g_MissionInfo				= 	""
x300578_g_ContinueInfo				= 	""
x300578_g_MissionCompleted			= 	""
x300578_g_MissionHelp				=	""          --������ʾ��Ϣ

--Ŀ��
x300578_g_ExtTarget					=	{ {type=20,n=1,target="�Ƶ�����"}}

--����

x300578_g_ExpBonus					= 	0;--x300578_AddExpAward               	--����������
x300578_g_BonusItem					=	{{item=11050003, n=8}}	--��������Ʒ

x300578_g_BonusMoney1               = 	0
x300578_g_BonusMoney2               =   0
x300578_g_BonusMoney3               =   0
x300578_g_BonusMoney5				=	0

x300578_g_BonusChoiceItem           =   {}


--MisDescEnd


x300578_g_NpcList = {143099,143100,143101,143102,143103,143104,143105,143106}
x300578_g_ReplyNpcId = 143145


-- Mission Text list

x300578_g_GameId			= 1015

x300578_g_QuestionCount		= 9	
x300578_g_QuestionTextList	= {
								{	title="�����ˡ��Ƶ�����",  --��������
								  title1="��ʲôʱ����Գ���", 
									info="\t��һ�ܵ��������Щˮ���Ǹ��Զ��м��첻Ը�ϴ���#Y@myname#W����ɷ�����������ǣ��ҳ������������Ƕ����ԵǴ�������", --����
									task="ǰ��@npc_85055��@npc_85056��ѯ������ŵ�ˮ���ǣ�ȷ����������",
									text1="\t���������������ң�����һ���������Ǵ���",
									text2="\t�ҵ�ϰ���ǣ��������壬�������Ҷ����ԵǴ���",
									text3="\t�����ˣ�ÿ����ֻ����һ�����ģ����յǴ���",
									text4="\t���Ǹ�ϲ���й��ɵ�ˮ�֣�ÿ���պ������Ҳ��Ǵ���",
									text5="\t�����������������������մӲ��Ǵ�",
									text6="\t��һ���ܶ��Ҳ��Ǵ���",
									text7="\t�������������ģ��������⣬�Ҷ����Ǵ���",
									text8="\t��˵��һ������������籩�����������첻�Ǵ���",
									answer="\t����������ˣ��������ܼ������ԵǴ���\n\t#Y(���������������в鿴ˮ����˵���Ļ����Ա������)",
									answer1="��һ",
									answer2="�ܶ�",
									answer3="����",
									answer4="����",
									answer5="����",
									answer6="����",
									answer7="����",
									
									gonglue1="#G��һ�������Ǵ�#W��",
									gonglue2="#G���壬�����Ǵ�#W��",
									gonglue3="#G��һ���ģ��յǴ�#W��",
									gonglue4="#G�������ղ��Ǵ�#W��",
									gonglue5="#G�����������ղ��Ǵ�#W��",
									gonglue6="#G��һ�������Ǵ�#W��",
									gonglue7="#G�������ģ����Ǵ�#W��",
									gonglue8="#G��һ�����岻�Ǵ�#W��",

									
									result = 4  -- ��

								},
								{title="�����ˡ��Ƶ�����",  --��������
								 title1="��ʲôʱ����Գ���", 
									info="\t��һ�ܵ��������Щˮ���Ǹ��Զ��м��첻Ը�ϴ���#Y@myname#W����ɷ�����������ǣ��ҳ������������Ƕ����ԵǴ�������", --����
									task="ǰ��@npc_85055��@npc_85056��ѯ������ŵ�ˮ���ǣ�ȷ����������",
									text1="\t���������������ң�����һ���������Ǵ���",
									text2="\t�ҵ�ϰ���ǣ��������壬�������Ҷ����ԵǴ���",
									text3="\t�����ˣ�ÿ����ֻ���ܶ������ģ����յǴ���",
									text4="\t���Ǹ�ϲ���й��ɵ�ˮ�֣�ÿ���պ������Ҳ��Ǵ���",
									text5="\t�����������������������մӲ��Ǵ�",
									text6="\t��һ�������Ҳ��Ǵ���",
									text7="\t�����ܶ������ģ��������⣬�Ҷ����Ǵ���",
									text8="\t��˵��һ������������籩�����������첻�Ǵ���",
									answer="\t����������ˣ��������ܼ������ԵǴ���\n\t#Y(���������������в鿴ˮ����˵���Ļ����Ա������)",
									answer1="��һ",
									answer2="�ܶ�",
									answer3="����",
									answer4="����",
									answer5="����",
									answer6="����",
									answer7="����",
									
									gonglue1="#G��һ�������Ǵ�#W��",
									gonglue2="#G���壬�����Ǵ�#W��",
									gonglue3="#G�ܶ����ģ��յǴ�#W��",
									gonglue4="#G�������ղ��Ǵ�#W��",
									gonglue5="#G�����������ղ��Ǵ�#W��",
									gonglue6="#G��һ���Ĳ��Ǵ�#W��",
									gonglue7="#G�ܶ����ģ����Ǵ�#W��",
									gonglue8="#G��һ�����岻�Ǵ�#W��",

                 	result = 2  -- ��
								},
								{
									title="�����ˡ��Ƶ�����",  --��������
									 title1="��ʲôʱ����Գ���", 
									info="\t��һ�ܵ��������Щˮ���Ǹ��Զ��м��첻Ը�ϴ���#Y@myname#W����ɷ�����������ǣ��ҳ������������Ƕ����ԵǴ�������", --����
									task="ǰ��@npc_85055��@npc_85056��ѯ������ŵ�ˮ���ǣ�ȷ����������",
									text1="\t���������������ң����ܶ����������Ǵ���",
									text2="\t�ҵ�ϰ���ǣ��������壬�������Ҷ����ԵǴ���",
									text3="\t�����ˣ�ÿ����ֻ����һ�����������ģ����յǴ���",
									text4="\t���Ǹ�ϲ���й��ɵ�ˮ�֣�ÿ���պ������Ҳ��Ǵ���",
									text5="\t�����������������������մӲ��Ǵ�",
									text6="\t�ܶ��������Ҳ��Ǵ���",
									text7="\t������һ�����ģ��������⣬�Ҷ����Ǵ���",
									text8="\t��˵���ĺ�����������籩�����������첻�Ǵ���",
									answer="\t����������ˣ��������ܼ������ԵǴ���\n\t#Y(���������������в鿴ˮ����˵���Ļ����Ա������)",
									answer1="��һ",
									answer2="�ܶ�",
									answer3="����",
									answer4="����",
									answer5="����",
									answer6="����",
									answer7="����",
									
									gonglue1="#G�ܶ��������Ǵ�#W��",
									gonglue2="#G���壬�����Ǵ�#W��",
									gonglue3="#G��һ�������ģ��յǴ�#W��",
									gonglue4="#G�������ղ��Ǵ�#W��",
									gonglue5="#G�����������ղ��Ǵ�#W��",
									gonglue6="#G�ܶ����岻�Ǵ�#W��",
									gonglue7="#G��һ���ģ����Ǵ�#W��",
									gonglue8="#G���ģ����岻�Ǵ�#W��",

									
									result = 1  -- ��
								},
								{title="�����ˡ��Ƶ�����",  --��������
								 title1="��ʲôʱ����Գ���", 
									info="\t��һ�ܵ��������Щˮ���Ǹ��Զ��м��첻Ը�ϴ���#Y@myname#W����ɷ�����������ǣ��ҳ������������Ƕ����ԵǴ�������", --����
									task="ǰ��@npc_85055��@npc_85056��ѯ������ŵ�ˮ���ǣ�ȷ����������",
									text1="\t���������������ң�����һ���ܶ����Ǵ���",
									text2="\t�ҵ�ϰ���ǣ��������壬�������Ҷ����ԵǴ���",
									text3="\t�����ˣ�ÿ����ֻ�����������ģ����յǴ���",
									text4="\t���Ǹ�ϲ���й��ɵ�ˮ�֣�ÿ���պ������Ҳ��Ǵ���",
									text5="\t����������һ�����������մӲ��Ǵ�",
									text6="\t�ܶ��������Ҳ��Ǵ���",
									text7="\t�������������ģ��������⣬�Ҷ����Ǵ���",
									text8="\t��˵���ĺ�����������籩�����������첻�Ǵ���",
									answer="\t����������ˣ��������ܼ������ԵǴ���\n\t#Y(���������������в鿴ˮ����˵���Ļ����Ա������)",
									answer1="��һ",
									answer2="�ܶ�",
									answer3="����",
									answer4="����",
									answer5="����",
									answer6="����",
									answer7="����",
									
									gonglue1="#G��һ�������Ǵ�#W��",
									gonglue2="#G���壬�����Ǵ�#W��",
									gonglue3="#G�������ģ��յǴ�#W��",
									gonglue4="#G�������ղ��Ǵ�#W��",
									gonglue5="#G��һ�������ղ��Ǵ�#W��",
									gonglue6="#G�ܶ����岻�Ǵ�#W��",
									gonglue7="#G�������ģ����Ǵ�#W��",
									gonglue8="#G���ģ����岻�Ǵ�#W��",

									
									result = 3 -- ��
								},
								
								{
								title="�����ˡ��Ƶ�����",  --��������
								 title1="��ʲôʱ����Գ���", 
									info="\t��һ�ܵ��������Щˮ���Ǹ��Զ��м��첻Ը�ϴ���#Y@myname#W����ɷ�����������ǣ��ҳ������������Ƕ����ԵǴ�������", --����
									task="ǰ��@npc_85055��@npc_85056��ѯ������ŵ�ˮ���ǣ�ȷ����������",
									text1="\t���������������ң����ܶ����������Ǵ���",
									text2="\t�ҵ�ϰ���ǣ��������ģ��������Ҷ����ԵǴ���",
									text3="\t�����ˣ�ÿ����ֻ�����������壬���յǴ���",
									text4="\t���Ǹ�ϲ���й��ɵ�ˮ�֣�ÿ���պ������Ҳ��Ǵ���",
									text5="\t����������һ�����������մӲ��Ǵ�",
									text6="\t�ܶ��������Ҳ��Ǵ���",
									text7="\t�������������壬�������⣬�Ҷ����Ǵ���",
									text8="\t��˵���ĺ�����������籩�����������첻�Ǵ���",
									answer="\t����������ˣ��������ܼ������ԵǴ���\n\t#Y(���������������в鿴ˮ����˵���Ļ����Ա������)",
									answer1="��һ",
									answer2="�ܶ�",
									answer3="����",
									answer4="����",
									answer5="����",
									answer6="����",
									answer7="����",
									
									gonglue1="#G�ܶ��������Ǵ�#W��",
									gonglue2="#G���ģ������Ǵ�#W��",
									gonglue3="#G�������壬�յǴ�#W��",
									gonglue4="#G�������ղ��Ǵ�#W��",
									gonglue5="#G��һ�������ղ��Ǵ�#W��",
									gonglue6="#G�ܶ��������Ǵ�#W��",
									gonglue7="#G�������壬���Ǵ�#W��",
									gonglue8="#G���ģ��������Ǵ�#W��",

									
									result = 5 -- ��
								},
								
								{title="�����ˡ��Ƶ�����",  --��������
								 title1="��ʲôʱ����Գ���", 
									info="\t��һ�ܵ��������Щˮ���Ǹ��Զ��м��첻Ը�ϴ���#Y@myname#W����ɷ�����������ǣ��ҳ������������Ƕ����ԵǴ�������", --����
									task="ǰ��@npc_85055��@npc_85056��ѯ������ŵ�ˮ���ǣ�ȷ����������",
									text1="\t���������������ң����ܶ����������Ǵ���",
									text2="\t�ҵ�ϰ���ǣ��������ģ��Ҷ����ԵǴ���",
									text3="\t�����ˣ�ÿ����ֻ�����������壬�����Ǵ���",
									text4="\t���Ǹ�ϲ���й��ɵ�ˮ�֣�ÿ����������Ҳ��Ǵ���",
									text5="\t����������һ�����壬���մӲ��Ǵ�",
									text6="\t�ܶ��������Ҳ��Ǵ���",
									text7="\t�������������壬�������⣬�Ҷ����Ǵ���",
									text8="\t��˵���ĺ�����������籩�����������첻�Ǵ���",
									answer="\t����������ˣ��������ܼ������ԵǴ���\n\t#Y(���������������в鿴ˮ����˵���Ļ����Ա������)",
									answer1="��һ",
									answer2="�ܶ�",
									answer3="����",
									answer4="����",
									answer5="����",
									answer6="����",
									answer7="����",
									
									gonglue1="#G�ܶ��������Ǵ�#W��",
									gonglue2="#G���Ĳ��Ǵ�#W��",
									gonglue3="#G�������壬���Ǵ�#W��",
									gonglue4="#G���壬�ղ��Ǵ�#W��",
									gonglue5="#G��һ���壬�ղ��Ǵ�#W��",
									gonglue6="#G�ܶ��������Ǵ�#W��",
									gonglue7="#G�������壬���Ǵ�#W��",
									gonglue8="#G���ģ����岻�Ǵ�#W��",

									
									result = 6 -- ��
								
								},
								{title="�����ˡ��Ƶ�����",  --��������
								 title1="��ʲôʱ����Գ���", 
									info="\t��һ�ܵ��������Щˮ���Ǹ��Զ��м��첻Ը�ϴ���#Y@myname#W����ɷ�����������ǣ��ҳ������������Ƕ����ԵǴ�������", --����
									task="ǰ��@npc_85055��@npc_85056��ѯ������ŵ�ˮ���ǣ�ȷ����������",
									text1="\t���������������ң����ܶ����������Ǵ���",
									text2="\t�ҵ�ϰ���ǣ��������ģ��Ҷ����ԵǴ���",
									text3="\t�����ˣ�ÿ����ֻ�����������壬���յǴ���",
									text4="\t���Ǹ�ϲ���й��ɵ�ˮ�֣�ÿ����������Ҳ��Ǵ���",
									text5="\t����������һ�����壬�����Ӳ��Ǵ�",
									text6="\t�ܶ��������Ҳ��Ǵ���",
									text7="\t�������������壬�������⣬�Ҷ����Ǵ���",
									text8="\t��˵���ĺ�����������籩�����������첻�Ǵ���",
									answer="\t����������ˣ��������ܼ������ԵǴ���\n\t#Y(���������������в鿴ˮ����˵���Ļ����Ա������)",
									answer1="��һ",
									answer2="�ܶ�",
									answer3="����",
									answer4="����",
									answer5="����",
									answer6="����",
									answer7="����",
									
									gonglue1="#G�ܶ��������Ǵ�#W��",
									gonglue2="#G���Ĳ��Ǵ�#W��",
									gonglue3="#G�������壬�յǴ�#W��",
									gonglue4="#G���壬�����Ǵ�#W��",
									gonglue5="#G��һ���壬�����Ǵ�#W��",
									gonglue6="#G�ܶ��������Ǵ�#W��",
									gonglue7="#G�������壬�յǴ�#W��",
									gonglue8="#G���ģ����岻�Ǵ�#W��",

									
									result = 7 -- ��
								
								},
								{title="�����ˡ��Ƶ�����",  --��������
								 title1="��ʲôʱ����Գ���", 
									info="\t��һ�ܵ��������Щˮ���Ǹ��Զ��м��첻Ը�ϴ���#Y@myname#W����ɷ�����������ǣ��ҳ������������Ƕ����ԵǴ�������", --����
									task="ǰ��@npc_85055��@npc_85056��ѯ������ŵ�ˮ���ǣ�ȷ����������",
									text1="\t���������������ң�����һ���ܶ����Ǵ���",
									text2="\t�ҵ�ϰ���ǣ������ܶ��������Ҷ����ԵǴ���",
									text3="\t�����ˣ�ÿ����ֻ������������Ǵ���",
									text4="\t���Ǹ�ϲ���й��ɵ�ˮ�֣�ÿ����������Ҳ��Ǵ���",
									text5="\t����������һ�����壬�����Ӳ��Ǵ�",
									text6="\t�ܶ��������Ҳ��Ǵ���",
									text7="\t�������������壬�������⣬�Ҷ����Ǵ���",
									text8="\t��˵���ĺ�����������籩�����������첻�Ǵ���",
									answer="\t����������ˣ��������ܼ������ԵǴ���\n\t#Y(���������������в鿴ˮ����˵���Ļ����Ա������)",
									answer1="��һ",
									answer2="�ܶ�",
									answer3="����",
									answer4="����",
									answer5="����",
									answer6="����",
									answer7="����",
									
									gonglue1="#G��һ�������Ǵ�#W��",
									gonglue2="#G�ܶ����岻�Ǵ�#W��",
									gonglue3="#G��������Ǵ�#W��",
									gonglue4="#G���壬�����Ǵ�#W��",
									gonglue5="#G��һ���壬�����Ǵ�#W��",
									gonglue6="#G�ܶ����Ĳ��Ǵ�#W��",
									gonglue7="#G�������壬�յǴ�#W��",
									gonglue8="#G���ģ����岻�Ǵ�#W��",

									
									result = 3 -- ��
								
								},
								{title="�����ˡ��Ƶ�����",  --��������
								 title1="��ʲôʱ����Գ���", 
									info="\t��һ�ܵ��������Щˮ���Ǹ��Զ��м��첻Ը�ϴ���#Y@myname#W����ɷ�����������ǣ��ҳ������������Ƕ����ԵǴ�������", --����
									task="ǰ��@npc_85055��@npc_85056��ѯ������ŵ�ˮ���ǣ�ȷ����������",
									text1="\t���������������ң����ܶ����������Ǵ���",
									text2="\t�ҵ�ϰ���ǣ������ܶ��������Ҷ����ԵǴ���",
									text3="\t�����ˣ�ÿ����ֻ����һ�����壬���յǴ���",
									text4="\t���Ǹ�ϲ���й��ɵ�ˮ�֣�ÿ����������Ҳ��Ǵ���",
									text5="\t���������ܶ������壬�����Ӳ��Ǵ�",
									text6="\t�����������Ҳ��Ǵ���",
									text7="\t������һ���������⣬�Ҷ����Ǵ���",
									text8="\t��˵���ĺ�����������籩�����������첻�Ǵ���",
									answer="\t����������ˣ��������ܼ������ԵǴ���\n\t#Y(���������������в鿴ˮ����˵���Ļ����Ա������)",
									answer1="��һ",
									answer2="�ܶ�",
									answer3="����",
									answer4="����",
									answer5="����",
									answer6="����",
									answer7="����",
									
									gonglue1="#G�ܶ��������Ǵ�#W��",
									gonglue2="#G�ܶ����岻�Ǵ�#W��",
									gonglue3="#G��һ���壬�յǴ�#W��",
									gonglue4="#G���壬�����Ǵ�#W��",
									gonglue5="#G�ܶ����壬�����Ǵ�#W��",
									gonglue6="#G�������Ĳ��Ǵ�#W��",
									gonglue7="#G��һ����Ǵ�#W��",
									gonglue8="#G���ģ����岻�Ǵ�#W��",

									
									result = 1 -- ��
								
								},
							   }	
				

-- ��������Ʒ�б�
x300578_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}


function x300578_GetMissionId( sceneId, selfId )
	return x300578_g_MissionId
end

function x300578_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local level = GetLevel( sceneId,selfId )
    if level < x300578_g_LevelLess then
       return
    end

	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300578_g_MissionName,8,1);
	else
		local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		AddQuestNumText(sceneId, myMissionId, x300578_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300578_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		x300578_ShowTips(sceneId, selfId, "�˻���첻���ţ������뵽�󶼰�������ѯÿ��������")
		return
	end

	local myMissionId = x300578_GetMissionId( sceneId, selfId )	
	
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId )>0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

		

		local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
		local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

		if bCompleted>0 then
			local bAnswerQuestion = GetQuestParam( sceneId, selfId, misIndex, 5 )

			if bAnswerQuestion>1 then
				x300578_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
			else
				if nExt==7 then
					
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300578_g_QuestionTextList[nQuestionId].title)
						AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].info)
						AddQuestNumText(sceneId, myMissionId, "��֪�������ܳ�����",2,20);
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, targetId, x300578_g_ScriptId, myMissionId);
				elseif nExt==20 then
					
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300578_g_QuestionTextList[nQuestionId].title)
						--AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].info)
						--AddQuestText(sceneId," ")
						AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].answer)
						
						AddQuestNumText(sceneId, myMissionId, x300578_g_QuestionTextList[nQuestionId].answer1,2,21);
						AddQuestNumText(sceneId, myMissionId, x300578_g_QuestionTextList[nQuestionId].answer2,2,22);
						AddQuestNumText(sceneId, myMissionId, x300578_g_QuestionTextList[nQuestionId].answer3,2,23);
						AddQuestNumText(sceneId, myMissionId, x300578_g_QuestionTextList[nQuestionId].answer4,2,24);
						AddQuestNumText(sceneId, myMissionId, x300578_g_QuestionTextList[nQuestionId].answer5,2,25);
						AddQuestNumText(sceneId, myMissionId, x300578_g_QuestionTextList[nQuestionId].answer6,2,26);
						AddQuestNumText(sceneId, myMissionId, x300578_g_QuestionTextList[nQuestionId].answer7,2,27);
						
						
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, targetId, x300578_g_ScriptId, myMissionId);
				elseif nExt>=21 then
					local nAnswer = nExt-20
					local nResult = x300578_g_QuestionTextList[nQuestionId].result;

					if nResult == nAnswer then
						x300578_ShowTips(sceneId, selfId, "̫���ˣ�����ͷԸ���ȥ�����ǿ�ʼ׼����")
						SetQuestByIndex( sceneId, selfId, misIndex, 5, 2 )
						x300578_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
					else
						x300578_ShowTips(sceneId, selfId, "������ҿ�δ�ذɣ��㻹����ȥ���ʣ������˿������Ǵ��¡�")
						x300578_GiveQuestion(sceneId, selfId, targetId, MissionId,2)
					end
				end
			end
			return
		end
	end
	
	
	if nExt>10 then --��npc�Ի�ʱ
		if nExt>=20 then
			return
		end

		local iIndex = nExt-10

		if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
			return
		end

		x300578_DispatchNpcTalkInfo( sceneId, selfId, targetId,myMissionId,iIndex )

	
	else
		
		if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
			x300578_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
		else
			if nExt==7 then -- �������
				--x300578_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
				
				
			else
				
				x300578_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
			end
		end
	end
end


function x300578_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )

	return 1;

end

function x300578_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		x300578_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	local myMissionId = x300578_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300578_g_LevelLess then
		x300578_ShowTips(sceneId, selfId, "��ȼ�����")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300578_ShowTips(sceneId, selfId, "���Ѿ������������������������")
		return 0;
	end

    local day = GetDayOfYear()
    if day == GetQuestData( sceneId, selfId, MD_HDJR_DATE[1], MD_HDJR_DATE[2],MD_HDJR_DATE[3] ) then
        Msg2Player( sceneId, selfId, "�ܱ�Ǹ���������Ѿ����������񣬲����ٴ���ȡ", 8, 3)
        return 0
    end

    if GetQuestData( sceneId, selfId, MD_RICHANG_DAY[ 1], MD_RICHANG_DAY[ 2], MD_RICHANG_DAY[ 3] ) == day then
        if GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[ 1], MD_RICHANG_COUNT[ 2], MD_RICHANG_COUNT[ 3] ) >= 3 then
            Msg2Player( sceneId, selfId, "�㲻������ȡ������ճ�������", 8, 3)
            return 0
        end
    else
        SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 0)
    end

	return 1;

end

function x300578_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		x300578_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0
	end
	
	if x300578_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300578_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300578_ShowTips(sceneId, selfId, "�����������޷���������")
		return 0
	end
	---------------------------- add end -------------------------------
	
	--���ǰ������
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,myMissionId  )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 0
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 0
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return 0
		end
	end

	local ret = AddQuest( sceneId, selfId, myMissionId, x300578_g_ScriptId, 0, 0, 0,1)-- ������������		
		
	if ret > 0 then
		local str = "������������"..x300578_g_MissionName;
		x300578_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		local myMissionId = x300578_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 0 )
		
		x300578_GiveQuestion(sceneId, selfId, targetId, MissionId,1)

		GamePlayScriptLog(sceneId, selfId, 851)
		return 1
	else
		
		x300578_ShowTips(sceneId, selfId, "�����������")
	
	end


end

function x300578_GiveQuestion(sceneId, selfId, targetId, MissionId, nExt)
	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		x300578_ShowTips(sceneId, selfId, "�˻���첻����")
		return
	end

	local myMissionId = x300578_GetMissionId( sceneId, selfId )

	local nQuestionId = random(1,x300578_g_QuestionCount)
		
	

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 6, nQuestionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 5, 1 )  --��û�д���
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 1, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 2, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 3, 0 )

	x300578_ShowQuestion( sceneId, selfId, targetId,MissionId,nQuestionId, nExt )

	x300578_QuestLogRefresh( sceneId, selfId, myMissionId );
end

function x300578_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300578_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "������������"..x300578_g_MissionName;
	    x300578_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

        local today = GetDayOfYear()
		SetQuestData( sceneId, selfId, MD_HDJR_DATE[1], MD_HDJR_DATE[2], MD_HDJR_DATE[3], today)
		if today == GetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3] ) then
            local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
            if count < 3 then
                SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1 + count)
            end
        else
            SetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3], today)
            SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1)
        end
	else
		x300578_ShowTips(sceneId, selfId, "��������ʧ��")
	end

	
end



function x300578_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		x300578_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	
	if x300578_CheckSubmit(sceneId, selfId )>0 then
		
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "������ճ������Ѿ������ٽ��ˣ�����������", 8, 3)
            return 0
        end

		if x300578_GiveReward(sceneId,selfId,selectId)<=0 then
			return
		end
		
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
            CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300578_g_MissionId)

			local str = "�����������:"..x300578_g_MissionName;
			x300578_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

            SetQuestData( sceneId, selfId, MD_HDJR_DATE[1], MD_HDJR_DATE[2], MD_HDJR_DATE[3], GetDayOfYear() )

			GamePlayScriptLog(sceneId, selfId, 852)
			
		else
			x300578_ShowTips(sceneId, selfId, "������ʧ��")
		end
		
	end
end

function x300578_GiveReward(sceneId,selfId,selectRadioId)
	
	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		x300578_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300578_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                if selectRadioId == iter.id then
                    if j <= 2 then
                        canBind = 1
                    end
                    count = iter.cnt
                    id = iter.id
                    break
                end
            end
            break
        end
    end

    -- ����������������ѡ����Ʒ��������Խ���¸�������ʱ�Ĵ���
    if count == 0 then
        for i, item in x300578_g_RewardTable do
            for j, iter in item.items do
                if selectRadioId == iter.id then
                    if j <= 2 then
                        canBind = 1
                    end
                    count = iter.cnt
                    id = iter.id
                    break
                end
            end
        end
    end

    if id == 0 or count == 0 then
        return 0
    end

	BeginAddItem(sceneId)
    if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
        if canBind == 1 then
            AddItem( sceneId, id, count)
        else
            AddBindItem( sceneId, id, count)
        end
    else
		AddBindItem( sceneId, id, count)
    end
		
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		
		AddItemListToPlayer(sceneId,selfId)
		
		
        Msg2Player( sceneId, selfId, format("���������Ʒ��@itemid_%d",id), 8, 3)

		return 1;
	else
        Msg2Player( sceneId, selfId, "�����ռ䲻�㣬�޷������������Ʒ��������ʧ��", 8, 3)
		return 0;	
	end
end



function x300578_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		x300578_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
	local bAnswered = GetQuestParam( sceneId, selfId, misIndex, 6 )

	if (bCompleted*bAnswered)<=0 then
		return 0
	end

	return 1;
end



---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300578_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300578_g_MissionName)
	AddQuestText(sceneId,"\t������ϵ���Ⱥˮ���ǣ�Ҫ˵���£���������һ�־����Ҫ˵��������Щ��Ƣ����������һ���Ѿ�����\n\t�⼸������ž�Ҫ������������Щ�һ��������ʮ������ɲ�Ը���ϴ���")
	AddQuestText( sceneId,"#Y����Ŀ�꣺")
			
	AddQuestText( sceneId,x300578_g_MissionTarget)
			
	AddQuestText(sceneId," ")

	local level = GetLevel(sceneId, selfId)
    for i, item in x300578_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	-- local nExpBonus = level*0;
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
		
	-- end

	-- if x300578_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300578_g_BonusMoney5)
	-- end

	-- for i, item2 in x300578_g_BonusItem do
		
		-- AddQuestItemBonus(sceneId, item2.item, item2.n)
		
	-- end

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300578_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300578_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300578_g_QuestionTextList[nQuestionId].title)
		AddQuestText(sceneId,"\t������Щˮ��������")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300578_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300578_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300578_g_QuestionTextList[nQuestionId].title)
		AddQuestText(sceneId,"\t̫���ˣ�����ͷԸ���ȥ�����ǿ�ʼ׼���������ҵ�һ��СС�����⣬���ǧ��Ҫ�ƴǡ�")
	
	
	
	local level = GetLevel(sceneId, selfId)
    for i, item in x300578_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	-- local nExpBonus = level*0;
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
		
	-- end

	-- if x300578_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300578_g_BonusMoney5)
	-- end

	-- for i, item2 in x300578_g_BonusItem do
		
		-- AddQuestItemBonus(sceneId, item2.item, item2.n)
		
	-- end
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300578_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�����Ŀ
---------------------------------------------------------------------------------------------------
function x300578_ShowQuestion( sceneId, selfId, NPCId,MissionId,nQuestionId, nExt )


	if nExt==1 then
		BeginQuestEvent(sceneId)
			
			AddQuestText(sceneId,"#Y"..x300578_g_QuestionTextList[nQuestionId].title)
	
			AddQuestText( sceneId,x300578_g_QuestionTextList[nQuestionId].info)
		
			
		EndQuestEvent()
	elseif nExt==2 then
		BeginQuestEvent(sceneId)
			
			AddQuestText(sceneId,"#Y"..x300578_g_QuestionTextList[nQuestionId].title)
			
			AddQuestText( sceneId,"\t������ҿ�δ�ذɣ��㻹����ȥ���ʣ������˿������Ǵ��¡�")
		
			
		EndQuestEvent()
	
	else
		return	
	end
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300578_g_ScriptId, MissionId,1);
	


end


function x300578_DispatchNpcTalkInfo( sceneId, selfId, NPCId,MissionId,iIndex )
	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	
	--��֤���NPC�Ƿ�Թ���
	local npcGuid = GetMonsterGUID(sceneId,NPCId)
	
	local bFind =0;
	local iIndex=0
	for i,item in x300578_g_NpcList do
		iIndex = iIndex+1;
		if npcGuid==item then
			bFind=1;
			break;
		end
	end	

	if bFind==0 then
		return
	else
		
		local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
		if nStep~=1 then
			return
		end
	
		local data1 = GetQuestParam( sceneId, selfId, misIndex, 1 )
		local data2 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	
		local value4 = floor(data1/1000)
		local value3 = floor(mod(data1,1000)/100)
		local value2 = floor(mod(data1,100)/10)
		local value1 = floor(mod(data1,10)/1)
	
		local value8 = floor(data2/1000)
		local value7 = floor(mod(data2,1000)/100)
		local value6 = floor(mod(data2,100)/10)
		local value5 = floor(mod(data2,10)/1)
	
		local temp_list = {value1,value2,value3,value4,value5,value6,value7,value8}
		local value = temp_list[iIndex]
	
		if value~=0 then
			--��NPC�Թ�������ôֱ�ӷ��أ������д���
			return
		end
	end

	
	
	--�����������NPC�ĶԻ�����
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 2 )

	if iIndex<=4 then
		
		local nValue = GetQuestParam( sceneId, selfId, misIndex, 1 )

		local nAdd = 1
		for i=1, iIndex-1 do
			nAdd = 10*nAdd
		end

		SetQuestByIndex( sceneId, selfId, misIndex, 1, nValue+nAdd )
		value1 = nValue+nAdd
	else
		local nValue = GetQuestParam( sceneId, selfId, misIndex, 2 )

		local nAdd = 1
		for i=1, iIndex-5 do
			nAdd = 10*nAdd
		end

		SetQuestByIndex( sceneId, selfId, misIndex, 2, nValue+nAdd )

		value2 = nValue+nAdd
	end

	

	
	if value1==1111 and value2==1111 then
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )

		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )
		
	end
	
	x300578_QuestLogRefresh( sceneId, selfId, myMissionId );

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300578_g_QuestionTextList[nQuestionId].title)
		
		if iIndex==1 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text1)
		elseif iIndex==2 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text2)
		elseif iIndex==3 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text3)
		elseif iIndex==4 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text4)
		elseif iIndex==5 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text5)
		elseif iIndex==6 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text6)
		elseif iIndex==7 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text7)
		elseif iIndex==8 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text8)
		end
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300578_g_ScriptId, myMissionId,0);

	

end





---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300578_QuestLogRefresh( sceneId, selfId, MissionId)
	
	
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							x300578_GetMissionName(sceneId,selfId),        -- ��������
							x300578_GetMissionTask(sceneId,selfId),		--����Ŀ��
							"@npc_"..x300578_GetReplyNpcId(sceneId,selfId),			--����NPC
							x300578_GetMissionMethod(sceneId,selfId),               --������
							x300578_GetMissionText(sceneId,selfId),	--��������
							x300578_GetMissionHelp(sceneId,selfId)					--����С��ʾ
							)
	
	local level = GetLevel(sceneId, selfId)
    for i, item in x300578_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	-- local nExpBonus = level*0;
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
		
	-- end

	-- if x300578_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300578_g_BonusMoney5)
	-- end

	-- for i, item2 in x300578_g_BonusItem do
		
		-- AddQuestItemBonus(sceneId, item2.item, item2.n)
		
	-- end
	
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300578_GetMissionName(sceneId,selfId)
	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local str = x300578_g_QuestionTextList[nQuestionId].title

	return str
end

function x300578_GetMissionTask(sceneId,selfId)
	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )

	local strTable = "  ";
	local str1 = strTable..(x300578_g_QuestionTextList[nQuestionId].task)..format("(%d/1)",value1)

	if value1>=1 then
		str1 = "#G"..str1
	else
		str1 = "#W"..str1
	end

	return str1
end

function x300578_GetReplyNpcId(sceneId,selfId)
	return x300578_g_ReplyNpcId;
end

function x300578_GetMissionMethod(sceneId,selfId)
	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	local nMissionStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
	



	local data1 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local data2 = GetQuestParam( sceneId, selfId, misIndex, 2 )

	
	local value4 = floor(data1/1000)
	local value3 = floor(mod(data1,1000)/100)
	local value2 = floor(mod(data1,100)/10)
	local value1 = floor(mod(data1,10)/1)

	local value8 = floor(data2/1000)
	local value7 = floor(mod(data2,1000)/100)
	local value6 = floor(mod(data2,100)/10)
	local value5 = floor(mod(data2,10)/1)

	local str=""

	if nMissionStep>0 then
		
		str = x300578_g_MissionTarget1
		
		if value1>=1 then
			str=str.."\n  �󸱣�"..x300578_g_QuestionTextList[nQuestionId].gonglue1;
		end
		if value2>=1 then
			str=str.."\n  ������"..x300578_g_QuestionTextList[nQuestionId].gonglue2;
		end
		if value3>=1 then
			str=str.."\n  ������"..x300578_g_QuestionTextList[nQuestionId].gonglue3;
		end
		if value4>=1 then
			str=str.."\n  ������"..x300578_g_QuestionTextList[nQuestionId].gonglue4;
		end

		if value5>=1 then
			str=str.."\n  ���֣�"..x300578_g_QuestionTextList[nQuestionId].gonglue5;
		end
		if value6>=1 then
			str=str.."\n  ���֣�"..x300578_g_QuestionTextList[nQuestionId].gonglue6;
		end
		if value7>=1 then
			str=str.."\n  ���֣�"..x300578_g_QuestionTextList[nQuestionId].gonglue7;
		end
		if value8>=1 then
			str=str.."\n  �캽��"..x300578_g_QuestionTextList[nQuestionId].gonglue8;
		end
		
		
	else
		str = x300578_g_MissionTarget
	end

	return str
end

function x300578_GetMissionText(sceneId,selfId)
	return "\t����ŵ�ˮ���Ƕ���Щ��Ƣ����ÿ�ܣ����Ǹ��Զ��в�Ը������ļ��죬���ܰ���ȥѯ������һ�����ҳ��������ǿ��Թ�ͬ�Ǵ�������"
end

function x300578_GetMissionHelp(sceneId,selfId)
	return "\tÿ��ˮ�ֶ��������һЩ���Ǻ�ʱ���ԵǴ�����Ϣ��������Щ��Ϣ�������ҳ��������Ƕ����ԵǴ���"
end



function x300578_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300578_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300578_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		
		return
	end
	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	
	local bFind =0;
	local iIndex=0
	for i,item in x300578_g_NpcList do
		iIndex = iIndex+1;
		if npcGuid==item then
			bFind=1;
			break;
		end
	end

	

	if bFind==0 then
		return
	end

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep~=1 then
		return
	end



	local data1 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local data2 = GetQuestParam( sceneId, selfId, misIndex, 2 )

	
	local value4 = floor(data1/1000)
	local value3 = floor(mod(data1,1000)/100)
	local value2 = floor(mod(data1,100)/10)
	local value1 = floor(mod(data1,10)/1)

	local value8 = floor(data2/1000)
	local value7 = floor(mod(data2,1000)/100)
	local value6 = floor(mod(data2,100)/10)
	local value5 = floor(mod(data2,10)/1)

	local temp_list = {value1,value2,value3,value4,value5,value6,value7,value8}

	local value = temp_list[iIndex]

	if value==0 then


		AddQuestNumText(sceneId, x300578_g_MissionId, x300578_g_QuestionTextList[nQuestionId].title1,2,iIndex+10);
	end
	
	

	
end

function x300578_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end



--// system end




