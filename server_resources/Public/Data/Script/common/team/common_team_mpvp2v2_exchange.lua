--##############################################
--##���2v2���ƶһ��ű� by rj 2010-11-4 ##
--##############################################

x303105_g_ScriptId          		= 303105
x303105_g_MissionName       		= "���һ���Ӣ��ѫ�¶һ�����"

--Դ������ƷID
x303105_g_Need_SrcItemID			= 12266663

-- ��¼�һ�����Ʒ��ID
x303105_g_ChangeintoItemID 			= {}
			
-- ��¼��ǰ���������� 0 ��ʾ�һ�����, 1��ʾ�һ��ƺ�
x303105_g_OperateType 				= {}						
-- ����Ŀ¼��ʾ���ı�
x303105_g_Text 						= "#Y���һ���Ӣ��ѫ��#W \n \n\tӢ��ѫ�²����������Լ�����ҫ��ʵ����Ҳ��������һ��ḻʵ�õĵ��ߡ�ϡ�����е������ս��ר�еĳƺš���������Ҫ�һ�ʲô��?"
-- һ��Ŀ¼��ʾ���ı�																	
x303105_g_ShowDemoText				= "\t�����ڿ��2V2ս���л�ʤ֮�󣬿�����Ӣ��ѫ�µ���������жһ���"

--AddQuestNumText��֧
x303105_g_MoonCake 					= 1
-- x303105_g_ThawRed					= 2
x303105_g_ColouredGlaze				= 3
x303105_g_Gem 						= 4
x303105_g_Azoth						= 5
x303105_g_Horse						= 6
x303105_g_Title						= 7
x303105_g_Majiang					= 8
x303105_g_Jewel						= 9

x303105_g_Back						= 100

--Ŀ�Ľ�Ʒ���ϣ�id��Ʒ��id  num���� , neednum�۳����µ�����
x303105_g_Need_DstItemInfo 		= 
{ 
{itemid = 12030254, num = 1, neednum = 4}, 
{itemid = 12030255, num = 1, neednum = 5}, 
{itemid = 12030256, num = 1, neednum = 6}, 
{itemid = 12030257, num = 1, neednum = 7}, 
{itemid = 12030259, num = 1, neednum = 8}, 
-- {itemid = 12050093, num = 1, neednum = 12}, 
-- {itemid = 12050094, num = 1, neednum = 13}, 
{itemid = 11000702, num = 1, neednum = 236}, 
{itemid = 11000701, num = 1, neednum = 236}, 
{itemid = 11000500, num = 1, neednum = 140}, 
{itemid = 11000502, num = 1, neednum = 100}, 
{itemid = 11000503, num = 1, neednum = 160}, 
{itemid = 11000504, num = 1, neednum = 120}, 
{itemid = 11030620, num = 1, neednum = 60}, 
{itemid = 11030636, num = 1, neednum = 60}, 
{itemid = 10297200, num = 1, neednum = 568}, 
{itemid = 10287200, num = 1, neednum = 568}, 
{itemid = 10297201, num = 1, neednum = 1420}, 
{itemid = 10287201, num = 1, neednum = 1420}, 
{itemid = 12030511, num = 1, neednum = 228}, 
{itemid = 12030512, num = 1, neednum = 288}, 
{itemid = 12050262, num = 1, neednum = 192}, 
{itemid = 12050263, num = 1, neednum = 768}, 
{itemid = 12050264, num = 1, neednum = 1728}, 

}

-- �ƺŽ�����, id �ƺ�ID, name ����, neednum ��Ҫ��������
x303105_g_AttackTitle 			= 
{
	{id = 119, name = "������ʯ��һ", neednum =24},
	{id = 120, name = "������ʯ����", neednum = 25},
	{id = 121, name = "������ʯ����", neednum = 26},
	{id = 122, name = "ͭǽ���ڡ�һ", neednum = 27},
	{id = 123, name = "ͭǽ���ڡ���", neednum = 29},
	{id = 124, name = "ͭǽ���ڡ���", neednum = 63},
	{id = 125, name = "�᲻�ɴݡ�һ", neednum = 69},
	{id = 126, name = "�᲻�ɴݡ���", neednum = 115},
	{id = 127, name = "�᲻�ɴݡ���", neednum = 130},
	{id = 128, name = "��ղ���", neednum = 144},
}

--�ƺŽ�����, ͬ��
x303105_g_DefenceTitle 			= 
{
	{id = 129, name = "��������һ", neednum =24},
	{id = 130, name = "�������񡤶�", neednum = 25},
	{id = 131, name = "����������", neednum = 26},
	{id = 132, name = "�ݿ����ࡤһ", neednum = 27},
	{id = 133, name = "�ݿ����ࡤ��", neednum = 29},
	{id = 134, name = "�ݿ����ࡤ��", neednum = 63},
	{id = 135, name = "��ɨǧ����һ", neednum = 69},
	{id = 136, name = "��ɨǧ������", neednum = 115},
	{id = 137, name = "��ɨǧ������", neednum = 130},
	{id = 138, name = "�Ƿ��켫", neednum = 144},
}

-- ����� title ���� event �¼�ID id �һ�����ƷID,�����ID��Ӧx303105_g_Need_DstItemInfo���itemid,Ҫ�һ�����Ʒ
x303105_g_MoonCakelevel 			=
 { {title = "��ζ�±�", event = 10, id = 12030254},
   {title = "�����±�", event = 11, id = 12030255},
   {title = "�˱��±�", event = 12, id = 12030256},
   {title = "�����±�", event = 13, id = 12030257},
   {title = "ʮȫ�±�", event = 14, id = 12030259}}
-- x303105_g_ThawRedlevel 			= 
   -- { {title = "�ļ���ѩ��", event = 15, id = 12050093},
	-- {title = "�弶��ѩ��", event = 16, id = 12050094}}
x303105_g_ColouredGlazelevel 			= 
{{title = "��������", event = 17, id = 11000702},
 {title = "�켶����", event = 18, id = 11000701}}
 
x303105_g_Azothlevel 			=
 { {title = "���Ϻ���ˮ��", event = 19, id = 11000500},
	 {title = "����ˮ��ˮ��", event = 20, id = 11000502}, 
	 {title = "�����ι�ˮ��", event = 21, id = 11000503},
	 {title = "�����Ų�ˮ��", event = 22, id = 11000504}}	
	 														  
x303105_g_Gemlevel 			= 
{   {title = "�߼���ʯͼ��", event = 23, id = 11030620},
	{title = "������ͼ��", event = 24, id = 11030636}}
	
x303105_g_Jewellevel 			= 
{ 	{title = "�촫Զ������", event = 25, id = 10297200},
	{title = "�촫Զ����ָ", event = 26, id = 10287200}, 
	{title = "ڤ��Զ������", event = 27, id = 10297201},
	{title = "ڤ��Զ����ָ", event = 28, id = 10287201}}
	
x303105_g_Majianglevel 			= 
{ 	{title = "�����ƣ�������(7��)���", event = 29, id = 12030511},
	{title = "�����ƣ���һɫ(7��)���", event = 30, id = 12030512}}
	
x303105_g_Horselevel 			= 
{ 	{title = "�ƶ�Ы�ӽ�����(50��ȫ��)", event = 31, id = 12050262},
	{title = "������뽵����(70��ȫ��)", event = 32, id = 12050263}, 
	{title = "��צ����������(80��ȫ��)", event = 33, id = 12050264}}


-- �ƺ���ʾ��, title��ʾ�ı�������, event �¼���ID,id, �����������Ӧ, �����id��Ӧ���ǳƺŽ�����������	
x303105_g_TitleLevel				= 
{{title = "�����ƺ�", event = 40, id = x303105_g_AttackTitle},
 {title = "�����ƺ�", event = 41, id = x303105_g_DefenceTitle} }																 

-- �һ�ʱ��ʾ���ı�, �Ա�����е�eventΪkey��Ӧ��ʾ������, �ƺŵĶһ�,��û��
-- �ƺŵ�ʱ���һ����ʾ���ı�Ҳ����������, ������ʾ���ı���x303105_g_TitleText,������
-- [event] = "text"
x303105_g_title = 
{
-- [8] = "�һ���ϲ�±�Ҫ5��Ӣ��ѫ��,ȷ���һ���?",
 -- [9] = "�һ������±�Ҫ5��Ӣ��ѫ��,ȷ���һ���?",
 [10] = "\t�һ�#G��ζ�±�#W��Ҫ#R4��#WӢ��ѫ��,ȷ���һ���?",
 [11] = "\t�һ�#G�����±�#W��Ҫ#R5��#WӢ��ѫ��,ȷ���һ���?",
 [12] = "\t�һ�#G�˱��±�#W,��Ҫ#R6��#WӢ��ѫ��,ȷ���һ���?",
 [13] = "\t�һ�#G�����±�#W,��Ҫ#R7��#WӢ��ѫ��,ȷ���һ���?",
 [14] = "\t�һ�#Gʮȫ�±�#W,��Ҫ#R8��#WӢ��ѫ��,ȷ���һ���?",
 -- [15] = "�һ��ļ���ѩ��,��Ҫ12��Ӣ��ѫ��,ȷ���һ���?",
 -- [16] = "�һ��弶��ѩ��,��Ҫ24��Ӣ��ѫ��,ȷ���һ���?",
 [17] = "\t�һ�#G��������#W,��Ҫ#R236��#WӢ��ѫ��,ȷ���һ���?",
 [18] = "\t�һ�#G�켶����#W,��Ҫ#R236��#WӢ��ѫ��,ȷ���һ���?",
 [19] = "\t�һ�#G���Ϻ���ˮ��#W,��Ҫ#R140��#WӢ��ѫ��,ȷ���һ���?",
 [20] = "\t�һ�#G����ˮ��ˮ��#W,��Ҫ#R100��#WӢ��ѫ��,ȷ���һ���?",
 [21] = "\t�һ�#G�����ι�ˮ��#W,��Ҫ#R160��#WӢ��ѫ��,ȷ���һ���?",
 [22] = "\t�һ�#G�����Ų�ˮ��#W,��Ҫ#R120��#WӢ��ѫ��,ȷ���һ���?",
 [23] = "\t�һ�#G�߼���ʯͼ��#W,��Ҫ#R60��#WӢ��ѫ��,ȷ���һ���?",
 [24] = "\t�һ�#G������ͼ��#W,��Ҫ#R60��#WӢ��ѫ��,ȷ���һ���?",
 [25] = "\t�һ�#G�촫Զ������#W,��Ҫ#R568��#WӢ��ѫ��,ȷ���һ���?",
 [26] = "\t�һ�#G�촫Զ����ָ#W,��Ҫ#R568��#WӢ��ѫ��,ȷ���һ���?",
 [27] = "\t�һ�#Gڤ��Զ������#W,��Ҫ#R1420��#WӢ��ѫ��,ȷ���һ���?",
 [28] = "\t�һ�#Gڤ��Զ����ָ#W,��Ҫ#R1420��#WӢ��ѫ��,ȷ���һ���",
 [29] = "\t�һ�#G�����ƣ�������(7��)���#W,��Ҫ#R228��#WӢ��ѫ��,ȷ���һ���?",
 [30] = "\t�һ�#G�����ƣ���һɫ(7��)���#W,��Ҫ#R288��#WӢ��ѫ��,ȷ���һ���",
 [31] = "\t�һ�#G�ƶ�Ы�ӽ�����(50��ȫ��)#W,��Ҫ#R192��#WӢ��ѫ��,ȷ���һ���?",
 [32] = "\t�һ�#G������뽵����(70��ȫ��)#W,��Ҫ#R768��#WӢ��ѫ��,ȷ���һ���?",
 [33] = "\t�һ�#G��צ����������(80��ȫ��)#W,��Ҫ#R1728��#WӢ��ѫ��,ȷ���һ���?",
 [40] = "\t�һ�#G������ʯ��һ#W�ƺţ�����+30����Ҫ#R24��#WӢ��ѫ�£��Ƿ�ȷ�϶һ���",
 [41] = "\t�һ�#G��������һ#W�ƺţ�����+30����Ҫ#R24��#WӢ��ѫ�£��Ƿ�ȷ�϶һ���",}														  																
  
-- �ƺ�������ʾ�ı� �����������ͳƺŵ�������ʾ���ı�,�Գƺŵ�IDΪKEY��Ӧ��ʾ���ı�
x303105_g_TitleText = 
{
[129] = "\t�����ڵĳƺ���#G��������һ#W�ƺţ�����+30������Ҫ#R25��#WӢ��ѫ�¿�����Ϊ#G�������񡤶�#W�ƺţ�����+60�����Ƿ�ȷ�϶һ���",
[130] = "\t�����ڵĳƺ���#G�������񡤶�#W�ƺţ�����+60������Ҫ#R26��#WӢ��ѫ�¿�����Ϊ#G����������#W�ƺţ�����+90�����Ƿ�ȷ�϶һ���",
[131] = "\t�����ڵĳƺ���#G����������#W�ƺţ�����+90������Ҫ#R27��#WӢ��ѫ�¿�����Ϊ#G�ݿ����ࡤһ#W�ƺţ�����+120�����Ƿ�ȷ�϶һ���",
[132] = "\t�����ڵĳƺ���#G�ݿ����ࡤһ#W�ƺţ�����+120������Ҫ#R29��#WӢ��ѫ�¿�����Ϊ#G�ݿ����ࡤ��#W�ƺţ�����+180�����Ƿ�ȷ�϶һ���",
[133] = "\t�����ڵĳƺ���#G�ݿ����ࡤ��#W�ƺţ�����+180������Ҫ#R63��#WӢ��ѫ�¿�����Ϊ#G�ݿ����ࡤ��#W�ƺţ�����+240�����Ƿ�ȷ�϶һ���",
[134] = "\t�����ڵĳƺ���#G�ݿ����ࡤ��#W�ƺţ�����+240������Ҫ#R69��#WӢ��ѫ�¿�����Ϊ#G��ɨǧ����һ#W�ƺţ�����+300�����Ƿ�ȷ�϶һ���",
[135] = "\t�����ڵĳƺ���#G��ɨǧ����һ#W�ƺţ�����+300������Ҫ#R115��#WӢ��ѫ�¿�����Ϊ#G��ɨǧ������#W�ƺţ�����+390�����Ƿ�ȷ�϶һ���",
[136] = "\t�����ڵĳƺ���#G��ɨǧ������#W�ƺţ�����+390������Ҫ#R130��#WӢ��ѫ�¿�����Ϊ#G��ɨǧ������#W�ƺţ�����+480�����Ƿ�ȷ�϶һ���",
[137] = "\t�����ڵĳƺ���#G��ɨǧ������#W�ƺţ�����+480������Ҫ#R144��#WӢ��ѫ�¿�����Ϊ#G�Ƿ��켫#W�ƺţ�����+600�����Ƿ�ȷ�϶һ���",
[138] = "\t�����ڵĳƺ���#G�Ƿ��켫#W�ƺţ�����+600������Ҫ#R144��#WӢ��ѫ�¿�������15�գ��Ƿ�ȷ�϶һ���",

[119] = "\t�����ڵĳƺ���#G������ʯ��һ#W�ƺţ�����+30������Ҫ#R25��#WӢ��ѫ�¿�����Ϊ#G������ʯ����#W�ƺţ�����+60�����Ƿ�ȷ�϶һ���",
[120] = "\t�����ڵĳƺ���#G������ʯ����#W�ƺţ�����+60������Ҫ#R26��#WӢ��ѫ�¿�����Ϊ#G������ʯ����#W�ƺţ�����+90�����Ƿ�ȷ�϶һ���",
[121] = "\t�����ڵĳƺ���#G������ʯ����#W�ƺţ�����+90������Ҫ#R27��#WӢ��ѫ�¿�����Ϊ#Gͭǽ���ڡ�һ#W�ƺţ�����+120�����Ƿ�ȷ�϶һ���",
[122] = "\t�����ڵĳƺ���#Gͭǽ���ڡ�һ#W�ƺţ�����+120������Ҫ#R29��#WӢ��ѫ�¿�����Ϊ#Gͭǽ���ڡ���#W�ƺţ�����+180�����Ƿ�ȷ�϶һ���",
[123] = "\t�����ڵĳƺ���#Gͭǽ���ڡ���#W�ƺţ�����+180������Ҫ#R63��#WӢ��ѫ�¿�����Ϊ#Gͭǽ���ڡ���#W�ƺţ�����+240�����Ƿ�ȷ�϶һ���",
[124] = "\t�����ڵĳƺ���#Gͭǽ���ڡ���#W�ƺţ�����+240������Ҫ#R69��#WӢ��ѫ�¿�����Ϊ#G�᲻�ɴݡ�һ#W�ƺţ�����+300�����Ƿ�ȷ�϶һ���",
[125] = "\t�����ڵĳƺ���#G�᲻�ɴݡ�һ#W�ƺţ�����+300������Ҫ#R115��#WӢ��ѫ�¿�����Ϊ#G�᲻�ɴݡ���#W�ƺţ�����+390�����Ƿ�ȷ�϶һ���",
[126] = "\t�����ڵĳƺ���#G�᲻�ɴݡ���#W�ƺţ�����+390������Ҫ#R130��#WӢ��ѫ�¿�����Ϊ#G�᲻�ɴݡ���#W�ƺţ�����+480�����Ƿ�ȷ�϶һ���",
[127] = "\t�����ڵĳƺ���#G�᲻�ɴݡ���#W�ƺţ�����+480������Ҫ#R144��#WӢ��ѫ�¿�����Ϊ#G��ղ���#W�ƺţ�����+600�����Ƿ�ȷ�϶һ���",
[128] = "\t�����ڵĳƺ���#G��ղ���#W�ƺţ�����+600������Ҫ#R144��#WӢ��ѫ�¿�������15�գ��Ƿ�ȷ�϶һ���",

}  
  
----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x303105_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
 	AddQuestNumText(sceneId, x303105_g_ScriptId, "���һ����ƺ�", 3, x303105_g_Title)
  	AddQuestNumText(sceneId, x303105_g_ScriptId, "���һ����±�", 3, x303105_g_MoonCake)
 	-- AddQuestNumText(sceneId, x303105_g_ScriptId, "��ѩ�������", 3, x303105_g_ThawRed)
 	AddQuestNumText(sceneId, x303105_g_ScriptId, "���һ�������", 3, x303105_g_ColouredGlaze)
 	AddQuestNumText(sceneId, x303105_g_ScriptId, "���һ���ͼ��", 3, x303105_g_Gem)
 	AddQuestNumText(sceneId, x303105_g_ScriptId, "���һ���ˮ��", 3, x303105_g_Azoth)
 	AddQuestNumText(sceneId, x303105_g_ScriptId, "���һ�������", 3, x303105_g_Jewel) 
 	AddQuestNumText(sceneId, x303105_g_ScriptId, "���һ�������", 3, x303105_g_Horse)	
 	AddQuestNumText(sceneId, x303105_g_ScriptId, "���һ���������", 3, x303105_g_Majiang)

end

----------------------------------------------------------------------------------------------
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x303105_ProcEventEntry(sceneId, selfId, targetId, idScript, idExt)

	x303105_g_OperateType[GetGUID(sceneId, selfId)] = 0
	if idExt == x303105_g_MoonCake then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text);
		for i, name in x303105_g_MoonCakelevel do
	  		AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
		end
		AddQuestNumText(sceneId, x303105_g_ScriptId, "�����ϲ�", 1, x303105_g_Back)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)
	-- elseif idExt == x303105_g_ThawRed then
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, x303105_g_Text)
		-- for i, name in x303105_g_ThawRedlevel do
	  		-- AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
		-- end
		-- AddQuestNumText(sceneId, x303105_g_ScriptId, "�����ϲ�", 3, x303105_g_Back)
		-- EndQuestEvent()
		-- DispatchQuestEventList(sceneId, selfId, targetId)
	elseif idExt == x303105_g_ColouredGlaze then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text)
		for i, name in x303105_g_ColouredGlazelevel do
	  		AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
		end
		AddQuestNumText(sceneId, x303105_g_ScriptId, "�����ϲ�", 1, x303105_g_Back)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)	
		
	elseif idExt == x303105_g_Gem then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text)
		for i, name in x303105_g_Gemlevel do
	  		AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
		end
		AddQuestNumText(sceneId, x303105_g_ScriptId, "�����ϲ�", 1, x303105_g_Back)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)	
		
	elseif idExt == x303105_g_Azoth then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text);
		for i, name in x303105_g_Azothlevel do
			AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
		end
		AddQuestNumText(sceneId, x303105_g_ScriptId, "�����ϲ�", 1, x303105_g_Back)  
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)
		
	elseif idExt == x303105_g_Horse then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text);
		for i, name in x303105_g_Horselevel do
	  		AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
	  end
	  AddQuestNumText(sceneId, x303105_g_ScriptId, "�����ϲ�", 1, x303105_g_Back)
	  EndQuestEvent()
	  DispatchQuestEventList(sceneId, selfId, targetId)	
	  
	elseif idExt == x303105_g_Jewel then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text);
		for i, name in x303105_g_Jewellevel do
	  		AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
	  end
	  AddQuestNumText(sceneId, x303105_g_ScriptId, "�����ϲ�", 1, x303105_g_Back)
	  EndQuestEvent()
	  DispatchQuestEventList(sceneId, selfId, targetId)	
	  
	elseif idExt == x303105_g_Majiang then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text);
		for i, name in x303105_g_Majianglevel do
	  		AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
	  end
	  AddQuestNumText(sceneId, x303105_g_ScriptId, "�����ϲ�", 1, x303105_g_Back)
	  EndQuestEvent()
	  DispatchQuestEventList(sceneId, selfId, targetId)	 
	     
	elseif idExt == x303105_g_Title then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text);
		for i, name in x303105_g_TitleLevel do
	  		AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
		end
		AddQuestNumText(sceneId, x303105_g_ScriptId, "�����ϲ�", 1, x303105_g_Back)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)
		
	elseif idExt == x303105_g_Back then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_ShowDemoText)
	 	EndQuestEvent()
 		x303105_ProcEnumEvent(sceneId, selfId, targetId, -1)
 		DispatchQuestEventList(sceneId, selfId, targetId)
	  -- ���������Ӳ˵�	
	elseif idExt >= x303105_g_MoonCakelevel[1].event and  idExt <= x303105_g_MoonCakelevel[getn(x303105_g_MoonCakelevel)].event then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y���һ����±�#W\n")
		for i, it in x303105_g_MoonCakelevel do
			if it.event == idExt then
				-- ��¼Ҫ�һ��ĵ���ID
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
	  		AddQuestText(sceneId, x303105_g_title[idExt])
				AddQuestItemBonus(sceneId, it.id, 1)
				EndQuestEvent()
	 			DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)
	 			return
	 		end
	 	end 	
	-- elseif idExt >= x303105_g_ThawRedlevel[1].event and idExt <= x303105_g_ThawRedlevel[getn(x303105_g_ThawRedlevel)].event then
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "#Y��ѩ������ȡ#W\n")
		-- EndQuestEvent()
		-- for i, it in x303105_g_ThawRedlevel do
			-- if it.event == idExt then
				--��¼Ҫ�һ��ĵ���ID
				-- x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
				-- AddQuestText(sceneId, x303105_g_title[idExt])
	 			-- DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)
	 			-- return
			-- end
		-- end
	elseif idExt >= x303105_g_ColouredGlazelevel[1].event and idExt <= x303105_g_ColouredGlazelevel[getn(x303105_g_ColouredGlazelevel)].event then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y���һ�������#W\n")
		for i, it in x303105_g_ColouredGlazelevel do
			if it.event == idExt then
				-- ��¼Ҫ�һ��ĵ���ID
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
	  		AddQuestText(sceneId, x303105_g_title[idExt])
				AddQuestItemBonus(sceneId, it.id, 1)
				EndQuestEvent()
	 			DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)	 
	 			return					
			end
		end 	
				
	elseif idExt >= x303105_g_Gemlevel[1].event and idExt <= x303105_g_Gemlevel[getn(x303105_g_Gemlevel)].event then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y���һ���ͼ��#W\n")
		for i, it in x303105_g_Gemlevel do
			if it.event == idExt then
				-- ��¼Ҫ�һ��ĵ���ID
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
	  		AddQuestText(sceneId, x303105_g_title[idExt])
				AddQuestItemBonus(sceneId, it.id, 1)
				EndQuestEvent()
	 			DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)	 
	 			return					
			end
		end  		
					
	elseif idExt >= x303105_g_Azothlevel[1].event and idExt <= x303105_g_Azothlevel[getn(x303105_g_Azothlevel)].event then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y���һ���ˮ��#W\n")
		for i, it in x303105_g_Azothlevel do
			if it.event == idExt then
				-- ��¼Ҫ�һ��ĵ���ID
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
	  		AddQuestText(sceneId, x303105_g_title[idExt])
				AddQuestItemBonus(sceneId, it.id, 1)
				EndQuestEvent()
	 			DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)	 
	 			return					
			end
		end  
	
	elseif idExt >= x303105_g_Jewellevel[1].event and idExt <= x303105_g_Jewellevel[getn(x303105_g_Jewellevel)].event then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y���һ�������#W\n")
		for i, it in x303105_g_Jewellevel do
			if it.event == idExt then
				-- ��¼Ҫ�һ��ĵ���ID
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
	  		AddQuestText(sceneId, x303105_g_title[idExt])
				AddQuestItemBonus(sceneId, it.id, 1)
				EndQuestEvent()
	 			DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)	
	 			return 					
			end
		end
		
	elseif idExt >= x303105_g_Majianglevel[1].event and idExt <= x303105_g_Majianglevel[getn(x303105_g_Majianglevel)].event then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y���һ���������#W\n")
		for i, it in x303105_g_Majianglevel do
			if it.event == idExt then
				-- ��¼Ҫ�һ��ĵ���ID
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
	  		AddQuestText(sceneId, x303105_g_title[idExt])
				AddQuestItemBonus(sceneId, it.id, 1)
				EndQuestEvent()
	 			DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)	
	 			return 					
			end
		end 	
		
	elseif idExt >= x303105_g_Horselevel[1].event and idExt <= x303105_g_Horselevel[getn(x303105_g_Horselevel)].event then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y���һ�������#W\n")
		
		for i, it in x303105_g_Horselevel do
			if it.event == idExt then
				-- ��¼Ҫ�һ��ĵ���ID
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
	  		AddQuestText(sceneId, x303105_g_title[idExt])
				AddQuestItemBonus(sceneId, it.id, 1)
				EndQuestEvent()
	 			DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)	
	 			return 					
			end
		end 
	elseif idExt >= x303105_g_TitleLevel[1].event and idExt <= x303105_g_TitleLevel[getn(x303105_g_TitleLevel)].event then
		-- ���Ĳ�������
		local TitleID = 0
		x303105_g_OperateType[GetGUID(sceneId, selfId)] = 1
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y���һ����ƺ�#W\n")
		
		-- ����Ƿ��и����͵ĳƺ�
		for i, it in x303105_g_TitleLevel do
			if it.event == idExt then
				
				for j, title in it.id do
					if IsHaveTitle(sceneId, selfId, title.id) > 0 then
							TitleID = title.id
					end
				end		
				
				--��¼�ƺŶ�Ӧ�ı�
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id	
			
				if TitleID > 0 then
					AddQuestText(sceneId, x303105_g_TitleText[TitleID])
				else
					AddQuestText(sceneId, x303105_g_title[idExt])
				end
				EndQuestEvent()
				DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)
				return	 					
			end
		end  				 											
	end
end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x303105_ProcAcceptCheck(sceneId, selfId, npcId)
	-- ��ȡ��������
	local nSrcItemNum = GetItemCount(sceneId, selfId, x303105_g_Need_SrcItemID)
	
	if x303105_g_OperateType[GetGUID(sceneId, selfId)] == 1 then
		-- �Ƿ��иóƺ�
		local nTitleLevel = 0
		local nIndex = 0
		-- ��ȡ�ƺż���
		for i, it in x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] do
			if IsHaveTitle(sceneId, selfId, it.id) > 0 then
					nTitleLevel = it.id
					nIndex = i
					
			end
		end
		local level = GetLevel(sceneId, selfId)
		local nlevel= floor(level/10)
		local mlevel =(nlevel+1)*10
		
		
		if level < 40 then
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ���ﵽ40���ſɶһ��������ƺ�", 8, 3)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ���ﵽ40���ſɶһ��������ƺ�", 8, 2)
			return
		end
		
		if nIndex >= nlevel and nIndex <10 then
			Msg2Player(sceneId, selfId, format( "�����ﵽ#G%d��#oʱ�ſɶһ���һ���ƺ�",mlevel), 8, 3)
			Msg2Player(sceneId, selfId, format( "�����ﵽ#G%d��#oʱ�ſɶһ���һ���ƺ�",mlevel), 8, 2)
			return
		end		
		
		local num = 0
		if nIndex + 1 <= getn(x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)]) then
			num = x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)][nIndex + 1].neednum
		else
			num = x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)][nIndex].neednum
		end
		
		
		
		-- �����������
		if nSrcItemNum < num then
			Msg2Player(sceneId, selfId, "���Ӣ��ѫ���������㣬�޷��һ�", 8, 3)
			Msg2Player(sceneId, selfId, "���Ӣ��ѫ���������㣬�޷��һ�", 8, 2)
			return
		end
		
		--ɾ������
		if 0 == DelItem(sceneId, selfId, x303105_g_Need_SrcItemID, num) then
			return
		end  	
		
		
		local nTitleID = 0
		if nTitleLevel > 0 then
			-- ɾ���ƺ�
			DeleteTitle(sceneId,selfId, x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)][nIndex].id)
			if nIndex + 1 <= getn(x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)]) then
				nTitleID = x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)][nIndex + 1].id
			else
				nTitleID = x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)][nIndex].id
			end
		else
			nTitleID = x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)][1].id
		end
		
		--��ӳƺ�
		AwardTitle(sceneId,selfId, nTitleID)	
		
		WriteLog(1, format("x303105_ProcAcceptCheck 1 GetTitle OK: SceneId(%d) GUID(%d) GetTitleID(%d)", 
   			sceneId, GetGUID(sceneId, selfId), nTitleID))
   			
	else
		-- ����ǻ�������
		for i, item in x303105_g_Need_DstItemInfo do
			if item.itemid == x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] then
				if nSrcItemNum < item.neednum then
					Msg2Player(sceneId, selfId, "���Ӣ��ѫ���������㣬�޷��һ�", 8, 3)
					Msg2Player(sceneId, selfId, "���Ӣ��ѫ���������㣬�޷��һ�", 8, 2)
					return
				else 
						 --ɾ������
					 if 0 == DelItem(sceneId, selfId, x303105_g_Need_SrcItemID, item.neednum) then
					 		return
					 end
					-- �����Ʒ
					if EndAddItem(sceneId, selfId) > 0 then
						 BeginAddItem(sceneId)
						 AddBindItem(sceneId, item.itemid, item.num)
						 
						 WriteLog(1, format("x303105_ProcAcceptCheck 2 GetItem OK: SceneId(%d) GUID(%d) GetItemID(%d) GetItemNum(%d)", 
					 		sceneId, GetGUID(sceneId, selfId), item.itemid, item.num))
	
						 AddItemListToPlayer(sceneId,selfId)
					     
					     WriteLog(1, format("x303105_ProcAcceptCheck 3 DeleteItem OK: SceneId(%d) GUID(%d) DeleteItemID(%d) DeleteItemNum(%d)", 
    					 	sceneId, GetGUID(sceneId, selfId), x303105_g_Need_SrcItemID, item.neednum))
					else
						Msg2Player(sceneId, selfId, "����ʣ��ռ䲻�㣬�޷��õ��һ���Ʒ", 8, 3)
						return
					end
				end
			end
		end
	end
	
end


----------------------------------------------------------------------------------------------
--�ƺű���ص�
----------------------------------------------------------------------------------------------
function x303105_OnChangeSelfTitle(sceneId, selfId, titleId, type)

	if type ~= 2 then
		return
	end
	
	--��ν����
	for i, item in x303105_g_TitleLevel do
		for j, title in item.id do
			if title.id == titleId then
				if j ~= 1 then
					AwardTitle(sceneId, selfId, item.id[j - 1].id)
					Msg2Player(sceneId, selfId, format("���ڡ�%s���ƺŹ��ڣ�����Ϊ��%s��", title.name, item.id[j - 1].name), 8, 3)
				end
				return
			end
		end
	end
end