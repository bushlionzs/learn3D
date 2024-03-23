
x920007_g_ScriptId 					= 920007
x920007_g_MissionName				= "��ʦͽ������ʦ���ƺ�"

x920007_g_Title_Cachet_Table 					= {
										{titleID = 9, titleName = "��Ϊ��ʦ", cachet = 0, num = 1},
										{titleID = 10, titleName = "Ϊ��ʦ��", cachet = 2500, num = 2},
										{titleID = 11, titleName = "���˲���", cachet = 10000, num = 3},
										{titleID = 12, titleName = "�������", cachet = 30000 , num = 4},
										{titleID = 13, titleName = "�����ĺ�", cachet = 80000,num = 5},
								}

x920007_g_Title_Cachet_Table_Count				=	5


function x920007_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId,x920007_g_ScriptId,x920007_g_MissionName,3,0);
end

function x920007_ProcEventEntry(sceneId, selfId, targetId)
	local nCurTitle = GetTitleForPrenticeCount(sceneId, selfId)
	local str = nil

	if nCurTitle == 0 then
		str = "\t��������ʦ����������һ��ͽ�ܻ��ʦ���ƺ�֮����������ʦ���ƺš�"
		--Msg2Player(sceneId,selfId,ret,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestEventList( sceneId, selfId, targetId)
		--DispatchQuestInfo(sceneId, selfId, targetId, x920007_g_ScriptId,-1)
		return
	end
	
	local i = 1
	for j,item in x920007_g_Title_Cachet_Table do
		if item.titleID == nCurTitle then
			if i >= x920007_g_Title_Cachet_Table_Count then
				str = "\t����ʦͽ�ƺ��Ѿ�Ϊ�����ˣ��޷�������"
				--Msg2Player(sceneId,selfId,ret,8,2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
				EndQuestEvent();
				DispatchQuestEventList( sceneId, selfId, targetId)
				--DispatchQuestInfo(sceneId, selfId, targetId, x920007_g_ScriptId,-1)
				return
			end

			break
		end
		i = i + 1
		
	end

	str = format("\t�Ƿ񻨷�%d������ʦͽ�ƺ�����Ϊ%s?����������������%d��ͽ�ܡ�", x920007_g_Title_Cachet_Table[i + 1].cachet, x920007_g_Title_Cachet_Table[i + 1].titleName , x920007_g_Title_Cachet_Table[i + 1].num)
	local value = GetPlayerGoodBadValue(sceneId, selfId)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, str);
	AddQuestText(sceneId, "\n\t#Y�㵱ǰ����ֵΪ��"..value);
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x920007_g_ScriptId,-1)
	
end

function x920007_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

function x920007_ProcAccept(sceneId, selfId, targetId)
	
	local nCurTitle = GetTitleForPrenticeCount(sceneId, selfId)
	local ret = nil

	if nCurTitle == 0 then
		--ret = "��δ��ù�ʦͽ�ƺţ�������һ��ͽ�ܣ���ó�ʼ���ƺ�"
		--Msg2Player(sceneId,selfId,ret,8,2)
		return
	end
	
	local i = 1
	for j,item in x920007_g_Title_Cachet_Table do
		if item.titleID == nCurTitle then
			if i >= x920007_g_Title_Cachet_Table_Count then
				--ret = "��ĳƺ��Ѿ�����ߵȼ�"
				--Msg2Player(sceneId,selfId,ret,8,2)
				return
			end

			break
		end
		i = i + 1
		
	end
	
	local value = GetPlayerGoodBadValue(sceneId, selfId)
	if value < x920007_g_Title_Cachet_Table[i + 1].cachet then
		ret = "�������ֵ���㣡";
		Msg2Player(sceneId,selfId,ret,8,3)
		Msg2Player(sceneId,selfId,ret,8,2)
		return
	end

	value = value - x920007_g_Title_Cachet_Table[i + 1].cachet

	SetPlayerGoodBadValue(sceneId, selfId, value)

	ChangeTitleForPrenticeCount(sceneId, selfId, x920007_g_Title_Cachet_Table[i + 1].titleID)

	Msg2Player(sceneId,selfId,"ʦ���ƺ������ɹ�",8,3)
	Msg2Player(sceneId,selfId,"ʦ���ƺ������ɹ�",8,2)

end