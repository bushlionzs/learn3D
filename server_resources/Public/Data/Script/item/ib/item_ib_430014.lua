
-----------------------------------------------------------------------
x430014_g_scriptId = 430014 
x430014_g_NeedItemId = 12030031
x430014_g_UICommandID = 103
x430014_g_CDTime = 120
x430014_g_lingdicheck 	= {							
							  { sceneId= 6,	time1 = 960,time2 = 1020,x1 = 28,x2 = 107,z1 =41,z2 =123},	--���ݳ�
							  { sceneId= 9,	time1 = 960,time2 = 1020,x1 = 132,x2 = 187,z1 =15,z2 =97},	--��Ҷ��
							  { sceneId= 13,time1 = 960,time2 = 1020,x1 = 31,x2 = 126,z1 =165,z2 =236},   --�͸��
							  { sceneId= 18,time1 = 960,time2 = 1020,x1 = 180,x2 = 210,z1 =28,z2 =60},  	--��������
							  { sceneId= 21,time1 = 960,time2 = 1020,x1 = 130,x2 = 288,z1 =70,z2 =191},	--��ʥ����۹�
							  { sceneId= 24,time1 = 960,time2 = 1020,x1 = 84,x2 = 174,z1 =55,z2 =136},	--Ү·����
							  --{ sceneId= 27,time1 = 960,time2 = 1020,x1 = 100,x2 = 100,z1 =100,z2 =100},   --����
							  --{ sceneId= 31,time1 = 960,time2 = 1020,x1 = 100,x2 = 100,z1 =100,z2 =100},	--���
							  --{ sceneId= 34,time1 = 960,time2 = 1020,x1 = 100,x2 = 100,z1 =100,z2 =100},	--צ�۵�
							}
x430014_g_Impact1 = 7721   --Ч����ID

function x430014_ProcEventEntry( sceneId, selfId, BagIndex )
	--��֪�ͻ��˴򿪺ϳɽ���
		BeginUICommand(sceneId);
		UICommand_AddInt(sceneId, BagIndex);
		DispatchUICommand(sceneId,selfId, x430014_g_UICommandID );
		EndUICommand(sceneId);
		
end

function x430014_CheckCanTrans(sceneId, selfId, BagIndex, index ,newSceneId )
	if GetItemIDByIndexInBag(sceneId, selfId, BagIndex) ~= x430014_g_NeedItemId then
		return 0
	end
	
	--����Ƿ����������ս�ڼ����ڽ�ֹ�ټ���Χ��
	if  GetWeek() == 6 then
		if 	x430014_lingdicheck(sceneId, selfId, index) == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ�����������ս�ڼ䣬���޷�ͨ�����з����������ͼ�ڸ�����")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����������ս�ڼ䣬���޷�ͨ�����з����������ͼ�ڸ�����",8,2)		
			return 0	
		end
	end
	
	local continuance = GetCurrentTime() - GetQuestData(sceneId, selfId, MD_TRANS_TIME[1], MD_TRANS_TIME[2], MD_TRANS_TIME[3])
	if continuance < x430014_g_CDTime then
		local msg = format("%d���ſ�ʹ����һ�����з�", x430014_g_CDTime-continuance)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 0
	end

	if IsBusMember(sceneId, selfId) == 1 then
		local msg = "���ڡ��������������߻���״̬ʱ����ʹ�����з���"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 0
	end

	if IsHaveSpecificImpact( sceneId, selfId, 7610) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7607) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7608) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7605) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7616) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7613) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7614) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7611) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7622) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7619) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7620) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7617) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7628) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7625) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7626) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7623) == 1 then
		local msg = "�ܱ�Ǹ��δ���������������ʱ�޷�ͨ������������"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 0
	end

	if sceneId == 14 then
		local msg = "�����в���ʹ�����з���"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 0
	end

	if sceneId == 12 then
		local msg = "�����в���ʹ�����з���"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 0
	end

	if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�������Ӳ���ʹ�����з���");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"�������Ӳ���ʹ�����з���",8,2)
		return 0
	end

	if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
		return 0
	end
	if GetSceneType(sceneId) == 2 then

		local msg = "��ǰ��������ʹ�����з���"
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 0
	end
	
	
	--�Ƿ������ֳ������ڱ���״̬
	local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7536  )
    if IsHaveFlag ~= 0 then
    	local msg = "�ڱ�������ս�ڼ䣬���ܴ���"
    	BeginQuestEvent(sceneId)
			AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 0
    end
    
    IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7537 )
    if IsHaveFlag ~= 0 then
    	local msg = "�ڱ�������ս�ڼ䣬���ܴ���"
    	BeginQuestEvent(sceneId)
			AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return 0
    end

	
	
	SetQuestData(sceneId, selfId, MD_TRANS_TIME[1], MD_TRANS_TIME[2], MD_TRANS_TIME[3], GetCurrentTime())

	return 1
end

function x430014_lingdicheck( sceneId, selfId, index )

	local ret = 0
    local minute = GetMinOfDay()
	local mapId = x430014_GetTransMap(sceneId, selfId, index)
	local posX = x430014_GetTransPosX(sceneId, selfId, index)
	local posZ = x430014_GetTransPosZ(sceneId, selfId, index)

	for i,itm in x430014_g_lingdicheck do
		if mapId == itm.sceneId and minute >=itm.time1 and minute <= itm.time2 and posX >=itm.x1 and posX <=itm.x2 and posZ >=itm.z1 and posZ <=itm.z2 then
			ret = 1
			break
		end
	end
	return ret
end	

function x430014_GetTransMap(sceneId, selfId, index)

	local value = 0
	if index == 0 then
		value = GetQuestData(sceneId, selfId, MD_TRANS_MAP1[1], MD_TRANS_MAP1[2], MD_TRANS_MAP1[3])	
	elseif index == 1 then
		value =  GetQuestData(sceneId, selfId, MD_TRANS_MAP2[1], MD_TRANS_MAP2[2], MD_TRANS_MAP2[3])
	elseif index == 2 then
		value = GetQuestData(sceneId, selfId, MD_TRANS_MAP3[1], MD_TRANS_MAP3[2], MD_TRANS_MAP3[3])
	elseif index == 3 then
		value = GetQuestData(sceneId, selfId, MD_TRANS_MAP4[1], MD_TRANS_MAP4[2], MD_TRANS_MAP4[3])
	elseif index == 4 then
		value = GetQuestData(sceneId, selfId, MD_TRANS_MAP5[1], MD_TRANS_MAP5[2], MD_TRANS_MAP5[3])
	end
	return value
end

function x430014_GetTransPosX(sceneId, selfId, index)
	local value = 0
	if index == 0 then
		value = GetQuestData(sceneId, selfId, MD_TRANS_POS_X1[1], MD_TRANS_POS_X1[2], MD_TRANS_POS_X1[3])	
	elseif index == 1 then
		value = GetQuestData(sceneId, selfId, MD_TRANS_POS_X2[1], MD_TRANS_POS_X2[2], MD_TRANS_POS_X2[3])
	elseif index == 2 then
		value = GetQuestData(sceneId, selfId, MD_TRANS_POS_X3[1], MD_TRANS_POS_X3[2], MD_TRANS_POS_X3[3])
	elseif index == 3 then
		value = GetQuestData(sceneId, selfId, MD_TRANS_POS_X4[1], MD_TRANS_POS_X4[2], MD_TRANS_POS_X4[3])
	elseif index == 4 then
		value = GetQuestData(sceneId, selfId, MD_TRANS_POS_X5[1], MD_TRANS_POS_X5[2], MD_TRANS_POS_X5[3])
	end
	return value
end

function x430014_GetTransPosZ(sceneId, selfId, index)
	local value = 0
	if index == 0 then
		value = GetQuestData(sceneId, selfId, MD_TRANS_POS_Z1[1], MD_TRANS_POS_Z1[2], MD_TRANS_POS_Z1[3])	
	elseif index == 1 then
		value = GetQuestData(sceneId, selfId, MD_TRANS_POS_Z2[1], MD_TRANS_POS_Z2[2], MD_TRANS_POS_Z2[3])
	elseif index == 2 then
		value = GetQuestData(sceneId, selfId, MD_TRANS_POS_Z3[1], MD_TRANS_POS_Z3[2], MD_TRANS_POS_Z3[3])
	elseif index == 3 then
		value = GetQuestData(sceneId, selfId, MD_TRANS_POS_Z4[1], MD_TRANS_POS_Z4[2], MD_TRANS_POS_Z4[3])
	elseif index == 4 then
		value = GetQuestData(sceneId, selfId, MD_TRANS_POS_Z5[1], MD_TRANS_POS_Z5[2], MD_TRANS_POS_Z5[3])
	end
	return value
end

function x430014_SetTransMap(sceneId, selfId, index, value)
	if index == 0 then
		SetQuestData(sceneId, selfId, MD_TRANS_MAP1[1], MD_TRANS_MAP1[2], MD_TRANS_MAP1[3], value)	
	elseif index == 1 then
		SetQuestData(sceneId, selfId, MD_TRANS_MAP2[1], MD_TRANS_MAP2[2], MD_TRANS_MAP2[3], value)
	elseif index == 2 then
		SetQuestData(sceneId, selfId, MD_TRANS_MAP3[1], MD_TRANS_MAP3[2], MD_TRANS_MAP3[3], value)
	elseif index == 3 then
		SetQuestData(sceneId, selfId, MD_TRANS_MAP4[1], MD_TRANS_MAP4[2], MD_TRANS_MAP4[3], value)
	elseif index == 4 then
		SetQuestData(sceneId, selfId, MD_TRANS_MAP5[1], MD_TRANS_MAP5[2], MD_TRANS_MAP5[3], value)
	end
end

function x430014_SetTransPosX(sceneId, selfId, index, value)
	if index == 0 then
		SetQuestData(sceneId, selfId, MD_TRANS_POS_X1[1], MD_TRANS_POS_X1[2], MD_TRANS_POS_X1[3], value)	
	elseif index == 1 then
		SetQuestData(sceneId, selfId, MD_TRANS_POS_X2[1], MD_TRANS_POS_X2[2], MD_TRANS_POS_X2[3], value)
	elseif index == 2 then
		SetQuestData(sceneId, selfId, MD_TRANS_POS_X3[1], MD_TRANS_POS_X3[2], MD_TRANS_POS_X3[3], value)
	elseif index == 3 then
		SetQuestData(sceneId, selfId, MD_TRANS_POS_X4[1], MD_TRANS_POS_X4[2], MD_TRANS_POS_X4[3], value)
	elseif index == 4 then
		SetQuestData(sceneId, selfId, MD_TRANS_POS_X5[1], MD_TRANS_POS_X5[2], MD_TRANS_POS_X5[3], value)
	end
end

function x430014_SetTransPosZ(sceneId, selfId, index, value)
	if index == 0 then
		SetQuestData(sceneId, selfId, MD_TRANS_POS_Z1[1], MD_TRANS_POS_Z1[2], MD_TRANS_POS_Z1[3], value)	
	elseif index == 1 then
		SetQuestData(sceneId, selfId, MD_TRANS_POS_Z2[1], MD_TRANS_POS_Z2[2], MD_TRANS_POS_Z2[3], value)
	elseif index == 2 then
		SetQuestData(sceneId, selfId, MD_TRANS_POS_Z3[1], MD_TRANS_POS_Z3[2], MD_TRANS_POS_Z3[3], value)
	elseif index == 3 then
		SetQuestData(sceneId, selfId, MD_TRANS_POS_Z4[1], MD_TRANS_POS_Z4[2], MD_TRANS_POS_Z4[3], value)
	elseif index == 4 then
		SetQuestData(sceneId, selfId, MD_TRANS_POS_Z5[1], MD_TRANS_POS_Z5[2], MD_TRANS_POS_Z5[3], value)
	end
end

function x430014_BeforeTrans(sceneId, selfId,index)
	if x430014_g_Impact1 >= 0 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x430014_g_Impact1, 0);
	end
end

function x430014_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x430014_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x430014_OnConditionCheck( sceneId, selfId )
	return 0
end

function x430014_OnDeplete( sceneId, selfId )

	return 0
end

function x430014_OnActivateOnce( sceneId, selfId )
end

function x430014_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

