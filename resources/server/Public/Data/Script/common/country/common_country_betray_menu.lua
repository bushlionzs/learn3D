x300819_g_ScriptId	= 300819
x300819_g_MissionName = "�����ҡ��ı����"
x300819_g_SubMissions = {
						{countryid=0,scriptid=300820,name="ǰ��¥������"},
						{countryid=1,scriptid=300821,name="ǰ����ɽ����"},
						{countryid=2,scriptid=300822,name="ǰ����������"},
						{countryid=3,scriptid=300823,name="ǰ���ػ�����"}
						}

function x300819_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	local level = GetLevel(sceneId, selfId)
	if level >= 40 then
		AddQuestNumText(sceneId,300819,x300819_g_MissionName,3)
	end
end

--�������ť������������ִ�д˽ű�
function x300819_ProcEventEntry( sceneId, selfId, targetId)

	BeginQuestEvent(sceneId)

		local Readme_1 = "#Y�����ҡ��ı����#r#W #r"
		local Readme_2 = "   ���Ƿ���ȥһ��ո�µĹ��ȷ�չ�أ�#r"
		local Readme_3 = "   ���ܰ���ʵ������Ը����ֻҪ����һЩ#Y�ֽ�#W�������̿��԰����͵�����Ҫȥ�Ĺ��ң�����Ϊ���ǹ��ҵ�һԱ��#r#r"
		local Readme_4 ="    ������ͨ��ѡ�����°�ť�����иı������#r"
		local Readme_5= "#G��ʾ������������Ҫ�۳���50���ֽ�"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText( sceneId,Readme)

		local cid = GetCurCountry(sceneId, selfId)
		for i,item in x300819_g_SubMissions do
			if cid ~= item.countryid then
				local nCost = x300819_GetBetrayCost(item.countryid)
				local name = item.name .. "(#c780000�ֽ�" .. floor(nCost/1000) .. "��#K)"
				AddQuestNumText( sceneId, item.scriptid, name, 3, item.countryid );
			end
		end

	EndQuestEvent(sceneId)

	DispatchQuestEventList(sceneId,selfId,targetId);

end



--�����ȷ����
function x300819_ProcAcceptCheck( sceneId, selfId, NPCId )
end

--**********************************
--����
--**********************************
function x300819_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300819_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300819_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300819_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300819_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300819_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300819_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300819_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end


-- ȡ���ѹ���Ҫ�Ľ�Ǯ������λ��
function x300819_GetBetrayCost( countryId )

	local nRank = GetCountryRank(countryId)
	local nCost = 0
	
	if nRank == 0 then 
		nCost = 50000		--ǿ��
	elseif nRank == 1 or nRank == 2 then 
		nCost = 50000		--�еȹ�
	elseif nRank == 3 then 
		nCost = 50000		--����
	end	
	
	return nCost
	
end