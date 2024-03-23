--���ܣ��ֽ�����

--MisDescBegin
--�ű���
x800056_g_ScriptId = 800056

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800056_g_MissionName="�һ���Ʊ"

x800056_g_LevelLess	= 20
x800056_g_DayCountUntil = 50

x800056_g_ItemList = {11060001,11060002,11060003}

--MisDescEnd

x800056_g_GameId	= 1003


--**********************************
--������ں���
--**********************************

function x800056_ProcEventEntry( sceneId, selfId, NPCId, MissionId,nExt)	--����������ִ�д˽ű�
	if GetGameOpenById(x800056_g_GameId)<=0 then
		x800056_ShowTips(sceneId, selfId,"�˹����ѹر�")
		return
	end

	if nExt==nil then
		return
	end

	if nExt==0 then

		local nLevel = GetLevel( sceneId, selfId)
		if nLevel<x800056_g_LevelLess then
			x800056_ShowTips(sceneId, selfId,format("�ȼ�����%d���޷�ʹ�øù���",x800056_g_LevelLess))
			return 0
		end

		if x800056_g_DayCountUntil>0 then

			
			if x800056_GetDayCount(sceneId, selfId)>=x800056_g_DayCountUntil then
				x800056_ShowTips(sceneId, selfId,format("�������Ѿ�������%d�ţ��޷��ٴλ�ȡ",x800056_g_DayCountUntil))
				return 0
			end
			
		end

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800056_g_MissionName)
			AddQuestText(sceneId,"\t�����������Խ���Ʊ�һ�Ϊ�������ȼ�Խ�ߣ����Զһ�����Ʊ����Խ�ࡣ��Ʊ�����ڽ���̵꣨��ݼ�J������ÿ���������һ�50�š�")

			AddQuestText(sceneId,format("\t#Y  �����컹���Ի�ȡ#G%d#Y��",x800056_g_DayCountUntil-x800056_GetDayCount(sceneId, selfId)))
			if nLevel>=20 then
				AddQuestNumText(sceneId, MissionId, "ȫ���һ�",3,15);
				AddQuestNumText(sceneId, MissionId, "��Ҫ��������Ʊ�һ�",3,1);
			end
			if nLevel>=40 then
				AddQuestNumText(sceneId, MissionId, "��Ҫ�ô�Ԫ��Ʊ�һ�",3,5);
			end
			if nLevel>=60 then
				AddQuestNumText(sceneId, MissionId, "��Ҫ�õ۹���Ʊ�һ�",3,10);
			end
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, NPCId, x800056_g_ScriptId, MissionId);


	end

	if nExt==1 or nExt==5 or nExt==10 or nExt==15 then
		x800056_DispatchExchangeInfo( sceneId, selfId, NPCId,nExt )
	end
end



function x800056_DispatchExchangeInfo( sceneId, selfId, NPCId, nExt )
	if GetGameOpenById(x800056_g_GameId)<=0 then
		x800056_ShowTips(sceneId, selfId,"�˹����ѹر�")
		return
	end

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x800056_g_MissionName)
		if nExt==1 then
			AddQuestText(sceneId,format("\t��Ҫ��#G������Ʊ#W��ȡ%d��������", nExt*18))
		elseif nExt==5 then
			AddQuestText(sceneId,format("\t��Ҫ��#G��Ԫ��Ʊ#W��ȡ%d��������", nExt*18))
		elseif nExt==10 then
			AddQuestText(sceneId,format("\t��Ҫ��#G�۹���Ʊ#W��ȡ%d��������", nExt*18))
		elseif nExt==15 then
			AddQuestText(sceneId,format("\t��Ҫ�ñ�����#Gȫ����Ʊ#W��ȡ������\n \n\t1��#G�۹���Ʊ#W=180������\n\t1��#G��Ԫ��Ʊ#W=90������\n\t1��#G������Ʊ#W=18������\n \n\t��������Ʊ�ȼ��ɸߵ��͵����ȼ���ȡ��ÿ����Ʊ��ȡ��������Ϊ50�š�"))
		else
			return
		end

		--AddQuestItemDemand(sceneId, 10018001, 2)
		--AddQuestText(sceneId," ")

		

	print(nExt)
	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x800056_g_ScriptId, -1);
	x800056_SetSelected(sceneId, selfId, nExt)
end



--**********************************
--�о��¼�
--**********************************
function x800056_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x800056_g_GameId)<=0 then
		
		return
	end
	AddQuestNumText(sceneId,x800056_g_ScriptId,x800056_g_MissionName,3,0);
end


--********************
--����������
--**********************************
function x800056_ProcAcceptCheck( sceneId, selfId, NPCId )
	if GetGameOpenById(x800056_g_GameId)<=0 then
		x800056_ShowTips(sceneId, selfId,"�˹����ѹر�")
		return 0
	end
		return 1
end

--**********************************
--����
--**********************************
function x800056_ProcAccept( sceneId, selfId )

	if GetGameOpenById(x800056_g_GameId)<=0 then
		x800056_ShowTips(sceneId, selfId,"�˹����ѹر�")
		return
	end

	local nLevel = GetLevel( sceneId, selfId)
	if nLevel<x800056_g_LevelLess then
		x800056_ShowTips(sceneId, selfId,format("�ȼ�����%d���޷�ʹ�øù���",x800056_g_LevelLess))
		return
	end

	if x800056_g_DayCountUntil>0 then
		if x800056_GetDayCount(sceneId, selfId)>=x800056_g_DayCountUntil then
			x800056_ShowTips(sceneId, selfId,format("�������Ѿ�������%d�ţ��޷��ٴλ�ȡ",x800056_g_DayCountUntil))
			return
		end
		
	end

	local nExt = x800056_GetSelected(sceneId, selfId)
	print(nExt)
	local nHaveCount = 0

	local nIndex = 0
	
	if nExt==1 then
		nIndex = 1;
	elseif nExt==5 then
		nIndex = 2;
	elseif nExt==10 then
		nIndex = 3;
	elseif nExt==15 then
		nIndex = 4;
	else
		return
	end
	
	local nHaveCount1 = GetItemCount( sceneId, selfId, x800056_g_ItemList[1] )
	local nHaveCount2 = GetItemCount( sceneId, selfId, x800056_g_ItemList[2] ) 
	local nHaveCount3 = GetItemCount( sceneId, selfId, x800056_g_ItemList[3] )

	if nExt==15 then 
	
		nHaveCount = nHaveCount1
		
		if nLevel >= 40 then
			nHaveCount = nHaveCount1 + nHaveCount2
		end
		
		if nLevel >= 60 then
	 	nHaveCount = nHaveCount1 + nHaveCount2 + nHaveCount3
	 	end
	else
		nHaveCount = GetItemCount( sceneId, selfId, x800056_g_ItemList[nIndex] )
	end

	if nHaveCount<1 then
		if nExt==1 then
			local str = format("������û���㹻��#G@item_%d",x800056_g_ItemList[nIndex])
			x800056_ShowTips(sceneId, selfId,str)
		elseif nExt==5 then
			local str = format("������û���㹻��#G@item_%d",x800056_g_ItemList[nIndex])
			x800056_ShowTips(sceneId, selfId,str)
		elseif nExt==10 then
			local str = format("������û���㹻��#G@item_%d",x800056_g_ItemList[nIndex])
			x800056_ShowTips(sceneId, selfId,str)
		elseif nExt==15 then
			x800056_ShowTips(sceneId, selfId,"������û�пɶһ���#G��Ʊ")
		else
			return
		end

		return
	end
	
	local nDelCount = 1
	
	if nExt==15 then 
		if nLevel >= 60 and nHaveCount3 > 0 then
			nExt = 10 
			nIndex = 3
			local nCanCount = x800056_g_DayCountUntil-x800056_GetDayCount(sceneId, selfId)
			if nHaveCount3 < nCanCount then 
				nDelCount = nHaveCount3
				x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)
			else
				nDelCount = nCanCount
				x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)
				return
			end
		end
		if nLevel >= 40 and nHaveCount2 > 0 then 
			nExt = 5 
			nIndex = 2
			local nCanCount = x800056_g_DayCountUntil-x800056_GetDayCount(sceneId, selfId)
			if nHaveCount2 < nCanCount then 
				nDelCount = nHaveCount2
				x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)
			else
				nDelCount = nCanCount
				x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)
				return
			end
		end
		if nLevel >= 20 and nHaveCount1 > 0 then 
			nExt = 1 
			nIndex =1
			local nCanCount = x800056_g_DayCountUntil-x800056_GetDayCount(sceneId, selfId)
			if nHaveCount1 < nCanCount then 
				nDelCount = nHaveCount1
				x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)
			else
				nDelCount = nCanCount
				x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)
				return
			end
		end	
		
	else
		x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)
		
	end
end

--**********************************
--����
--**********************************
function x800056_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800056_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800056_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800056_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800056_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800056_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800056_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

function x800056_ShowTips(sceneId, selfId,str)
	
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, str);
	EndQuestEvent(sceneId);

	DispatchQuestTips(sceneId, selfId);
end

---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x800056_GetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_DATE[1], MD_XIANJIN2YINKA_DATE[2],MD_XIANJIN2YINKA_DATE[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_DAYCOUNT[1], MD_XIANJIN2YINKA_DAYCOUNT[2],MD_XIANJIN2YINKA_DAYCOUNT[3] );
	return daycount;
end

---------------------------------------------------------------------------------------------------
--���õ�������
---------------------------------------------------------------------------------------------------
function x800056_SetDayCount(sceneId, selfId, flag)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_DATE[1], MD_XIANJIN2YINKA_DATE[2], MD_XIANJIN2YINKA_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_DATE[1], MD_XIANJIN2YINKA_DATE[2], MD_XIANJIN2YINKA_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_DAYCOUNT[1], MD_XIANJIN2YINKA_DAYCOUNT[2], MD_XIANJIN2YINKA_DAYCOUNT[3], flag)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_DAYCOUNT[1], MD_XIANJIN2YINKA_DAYCOUNT[2], MD_XIANJIN2YINKA_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_DAYCOUNT[1], MD_XIANJIN2YINKA_DAYCOUNT[2], MD_XIANJIN2YINKA_DAYCOUNT[3], daycount+flag)
	end
end


---------------------------------------------------------------------------------------------------
--�õ���Ҹղ�ѡ��Ľ���ѡ��
---------------------------------------------------------------------------------------------------
function x800056_GetSelected(sceneId, selfId)
	local flag = GetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_FLAG[1], MD_XIANJIN2YINKA_FLAG[2],MD_XIANJIN2YINKA_FLAG[3] )
	return flag
end


---------------------------------------------------------------------------------------------------
--������Ҹղ�ѡ��Ľ���ѡ��
---------------------------------------------------------------------------------------------------
function x800056_SetSelected(sceneId, selfId, flag)
	SetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_FLAG[1], MD_XIANJIN2YINKA_FLAG[2], MD_XIANJIN2YINKA_FLAG[3], flag)
end


function x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)

	local nMoney1 = GetMoney(sceneId, selfId, 1) --����
	if(nMoney1+nExt*nDelCount*1000*18)>999999999 then
		x800056_ShowTips(sceneId, selfId,"�����Ѵ�����")
		return
	end
	
	local	nRet = DelItem(sceneId, selfId,x800056_g_ItemList[nIndex],nDelCount)

	if nRet<=0 then
		x800056_ShowTips(sceneId, selfId,"ʹ����Ʒʧ��")
		return
	end
	
	AddMoney(sceneId, selfId, 1, nExt*nDelCount*1000*18)

	local str = format("��ʹ��%d��#G@item_%d#o��ȡ��%d������",nDelCount,x800056_g_ItemList[nIndex], nExt*nDelCount*18 );

	x800056_ShowTips(sceneId, selfId,str)

	Msg2Player(sceneId, selfId, str, 4, 2);

	x800056_SetDayCount(sceneId, selfId ,nDelCount)

	
	GamePlayScriptLog(sceneId, selfId, 921)

	--// ������־
	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u",myGuid)
	local strName = GetName(sceneId,selfId)
	local nDayCount = x800056_GetDayCount(sceneId, selfId)
	local msg = "DHYP,"..myGuid..","..strName..","..nExt..","..nDayCount;

	WriteLog(1,msg)
end