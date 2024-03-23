--����ؽ�

--MisDescBegin
x550401_g_ScriptId = 550401
x550401_g_MissionName1 = "ǰ��¥������"
x550401_g_MissionName2 = "ǰ����ɽ����"
x550401_g_MissionName3 = "ǰ�����ر���"
x550401_g_MissionName4 = "ǰ���ػͱ���"   
x550401_g_SceneID1 =51								--¥���߾�����ID
x550401_g_SceneID2 =151	  						 --��ɽ�߾�����ID
x550401_g_SceneID3 =251								--���ر߾�����ID
x550401_g_SceneID4 =351								--�ػͱ߾�����ID
x550401_g_MissionInfo=" "  --��������
x550401_g_MissionInfo2=""
x550401_g_MissionQuestID	=	-1
x550401_g_MissionComplete="  "					--�������npc˵���Ļ�
x550401_g_ContinueInfo="    "
x550401_g_Notice = "���ĵȼ�������#R40��#Y���޷�ǰ���������ң�"
--������
x550401_g_MoneyBonus = 10000
--�̶���Ʒ���������8��
x550401_g_ItemBonus={}

--��ѡ��Ʒ���������8��
x550401_g_RadioItemBonus={}

--MisDescEnd
x550401_g_ExpBonus = 1000
--**********************************

--������ں���

--**********************************

function x550401_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

	local selfType = GetObjType(sceneId, selfId)
	if selfType == 1 then 
		------------------------------------------------------
		if IsHaveQuestNM( sceneId, selfId, 7537) ~= 0 or  IsHaveQuestNM( sceneId, selfId, 7538) ~= 0 or IsHaveQuestNM( sceneId, selfId, 7539) ~= 0 then
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ��δ���������������ʱ�޷�ͨ������������",8,2)
			return
		end
		--�����������������ֹ���͵Ĵ���
		------------------------------------------------------
	end
	
	if selfType == 9 then	--Bus�������� ��bus��bus����˿糡��
		local busType = GetBusType(sceneId, selfId)
		if busType == 1 then --BUS_TYPE_NORMAL
			local memberCount = GetBusMemberCount(sceneId, selfId)
			local daduSceneId = 0
			ReadyBusChangeScene(sceneId, daduSceneId,selfId)--ע�⣺�˲����Ǳ����.BUS�л�������Ҫ����Щ׼������,
			for	i = 0, memberCount - 1 do
				local ObjID = GetBusMemberObjId(sceneId, selfId, i)
				NewWorld(sceneId,ObjID,x550401_g_SceneID2,126.5,198, 550401)
			end
			--ɾ��BUS,����Ա���ڳ���
			DeleteBus(sceneId, selfId,0)
			return
		end
	elseif selfType == 1 then	--���
--		local isBusMember = IsBusMember(sceneId, selfId)
--		if isBusMember == 1 then
--			Msg2Player(sceneId,selfId,"�ܱ�Ǹ��δ����ڳ�����ʱ�޷�ͨ������������",8,2)		
--			return
--		end
	end
	
	local strText = ""
	local CanTrans = IsCashboxState(sceneId,selfId)	
	if CanTrans == 1 then
		BeginQuestEvent(sceneId)
			strText = "#Y���ڻ��߻���״̬�У���������"
			AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

	local nLevel = GetLevel(sceneId, selfId)
	if nLevel < 40 then 
		Msg2Player(sceneId,selfId,"#Y"..x550401_g_Notice.."#W",4,3)
	else
		NewWorld(sceneId,selfId,x550401_g_SceneID2,126.6,197, 550401)
	end
	
end



--**********************************

--�о��¼�

--**********************************

function x550401_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	if sceneId ~= x550401_g_SceneID2 then	
		AddQuestNumText(sceneId, x550401_g_ScriptId, x550401_g_MissionName2)
	end		
end



--**********************************

--����������

--**********************************

function x550401_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end


--**********************************

--���鿴����

--**********************************

function x550401_CheckPushList(sceneId, selfId, targetId)
	
end

--**********************************

--����

--**********************************

function x550401_ProcAccept(sceneId, selfId)

    
end



--**********************************

--����

--**********************************

function x550401_ProcQuestAbandon(sceneId, selfId, MissionId)


end



--**********************************

--����Ƿ�����ύ

--**********************************

function x550401_CheckSubmit( sceneId, selfId, targetId)


end



--**********************************

--�ύ

--**********************************

function x550401_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

	
end


--���������¼�

--**********************************

function x550401_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x550401_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

