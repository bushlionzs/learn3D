--���ܣ���Ϧ�̵�

x560900_g_ScriptId = 560900
x560900_g_MissionName="��Ϧ��Ե��"
x560900_g_ShopList={900,900,900,900,900,900}
x560900_g_MissionDay = 812


--**********************************

--������ں���

--**********************************

function x560900_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

		DispatchShopItem( sceneId, selfId, targetId, x560900_g_ShopList[1] )


end



--**********************************

--�о��¼�

--**********************************

function x560900_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	if x560900_CheckDay( sceneId,selfId ) == 1 then
		AddQuestNumText(sceneId, x560900_g_ScriptId, x560900_g_MissionName,10)
	else 
		return
	end

end



--**********************************

--����������

--**********************************

function x560900_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560900_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560900_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560900_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560900_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560900_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560900_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560900_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

--**********************************

--�������

--**********************************
function x560900_CheckDay( sceneId,selfId )

	local year,month,day = GetYearMonthDay()
	local nDay = month*100+day

	if x560900_g_MissionDay == nDay then
		return 1
	end

	return 0

end