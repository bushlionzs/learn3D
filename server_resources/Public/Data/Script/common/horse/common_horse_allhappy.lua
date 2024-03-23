--���ܣ�����ҽ��
--NPC������ҽ��

x800048_g_ScriptId = 800048
x800048_g_MissionName="��˻ָ�"
x800048_g_MissionInfo="�ָ�������˵�����ֵ��\n��Ҫ��������"
x800048_g_MissionSuccess="������˵�����ֵ���ָ��ˣ�"
x800048_g_NotNeed="û�������Ҫ�ָ�����ֵ��"

--**********************************

--������ں���

--**********************************

function x800048_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	local money = GetAllHorseHappyMoney(sceneId, selfId)
	--local liang = floor(money /1000);
	--local wen = mod(money, 1000);
	local bNeed = 1;
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y"..x800048_g_MissionName.."\n")
		if(money == 0) then
			AddQuestText(sceneId, x800048_g_NotNeed)
			bNeed = 0
		else
			local str = format("%s#{_MONEY%d}", x800048_g_MissionInfo, money);
			AddQuestText(sceneId, str)
		end
	EndQuestEvent(sceneId)
	if(bNeed > 0) then
		DispatchQuestInfo(sceneId, selfId, targetId, x800048_g_ScriptId,-1)
	else
		DispatchQuestInfo(sceneId, selfId, targetId, x800048_g_ScriptId,-1,1)
	end

end



--**********************************

--�о��¼�

--**********************************

function x800048_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x800048_g_ScriptId, x800048_g_MissionName , 3 )
end



--**********************************

--����������

--**********************************

function x800048_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

--**********************************

--����

--**********************************

function x800048_ProcAccept(sceneId, selfId)
	if( 0 < AllHorseHappy(sceneId, selfId)) then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,x800048_g_MissionSuccess)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
	end
end



--**********************************

--����

--**********************************

function x800048_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x800048_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x800048_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x800048_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x800048_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x800048_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end