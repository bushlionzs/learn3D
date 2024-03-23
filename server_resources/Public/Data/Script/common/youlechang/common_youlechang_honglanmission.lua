

--MisDescBegin
x310320_g_ScriptId = 310320
--x310320_g_MissionIdPre ={67,69,70,71}
x310320_g_MissionId = 9045 

x310320_g_MissionName="�����ˡ���������ս"
x310320_g_MissionTarget				= "ѡ��֧��@npc_145001��@npc_145002" 
x310320_g_MissionCompleted			= "\t�������α�������ս�����ˣ������˫���Ľ�������������Ŀ�Դ�......"
x310320_g_MissionInfo				= "\t�٣���ã���������ı�������Ա��\n\t��μӱ�������ս����������˽�һ�¹���\n\t������ڱ�����߱�����ѡ�����һ����������ʱ�����֮ǰ�������ȥ����һ�ߵı���ת����֧�ֵĶ���\n\t����һ����֧�ֵ��������ж�ʤ����\n\tע�⣺#G֧������#R����#G�ı�������#Rʤ��#G�����˫���Ľ�������֧�������϶�ı�����ֻ������ͨ�Ľ�����#W�������ʱһ����Ҫ���ߣ�����Ҫ�ȵ��´��������ʱ������ɱ�����"            --������Ϣ
x310320_g_ContinueInfo				= "\t���ļ�����һ����Ҿͻ�����ʤ����"  --���������Ϣ
  --���������Ϣ
x310320_g_MissionHelp				= "#G֧���������ٵı�������ʤ�������˫���Ľ�������֧�������϶�ı�����ֻ������ͨ�Ľ�����"          --������ʾ��Ϣ
-- ���������ʾ��Ϣ
x300320_g_strMissionAbandon         = "�����������񣺡����ˡ���������ս"


--MisDescEnd
--**********************************
x310320_g_MissionTarget1				= "  ѡ��֧��@npc_145001��@npc_145002"       --����Ŀ��
x310320_g_MissionCompleted1			= "\t��ϲ�㣡������ѡ��ı���֧���������٣����ڱ��α�������ս��Ӯ����˫���Ľ�����"
x310320_g_MissionCompleted2			= "\t���ź���������ѡ��ı���֧������̫�࣬���ڱ��α�������ս�л������ͨ�Ľ�����" 
x310320_g_HongNum	= 0
x310320_g_LanNum	= 0
x310320_g_MinLevel	= 65
x310320_g_MaxLevel	= 84

x310320_g_HongBuff		= 7536
x310320_g_LanBuff		= 7537


x310320_g_TotalTime	= 10 * 60  --10����

x310320_g_State		= 0

x310320_g_CostGold	= 1000 --1���ֽ�
x310320_g_IsEnableId = 1039

-- ���������¼��־ID
x310320_g_AcceptMissionLogID        = 1631
-- ��������¼��־ID
x310320_g_FinishMissionLogID        = 1632

x310320_g_SelfId        = 0

-- ���齱��ϵ��  
x310320_g_CoffExp      =125000

--MD_HONGLAN_DATE		����			9
--MD_HONGLAN_COUNT      ����			4


-- ����������˼䡤�������˳���Ϸ����ߣ��ٴν�����Ϸʱ�Ĵ���
function x310320_ProcMapPlayerNewConnectEnter( sceneId, selfId)
	local today = GetDayOfYear()
    local hour = GetHourMinSec()
    
	local lastDay = GetQuestData(sceneId, selfId, MD_YOULECHANG_DATE[1], MD_YOULECHANG_DATE[2], MD_YOULECHANG_DATE[3])
	if hour == 23 or hour < 9 or today ~= lastDay then
		-- �������ϴν�������ֳ�����ʱ��Ͱѽ�ɫ�����ȥ���Żش���
		-- ��һ��T�˱�ǣ���Buff����ɣ�ֱ��T������ɿ�MapServer���ݶ�ʧ
		CancelSpecificImpact( sceneId, selfId, x310320_g_LanBuff)
		CancelSpecificImpact( sceneId, selfId, x310320_g_HongBuff)
		--SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 1)
		SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, 8400, 0)
	end
end



function x310320_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	x310320_g_SelfId        = selfId
	if IsHaveQuest(sceneId,selfId, x310320_g_MissionId) <= 0 then
		if GetLevel( sceneId, selfId) < x310320_g_MinLevel then 
	 		return 0
		end
	end	
	--local n = CostMoney(sceneId,selfId,2,1000)
	--print("x310320_ProcEnumEvent",n)
	--if GetGameOpenById( x310320_g_IsEnableId) <= 0  then
       --return 0
   -- end
    
    --if IsHaveQuest(sceneId,selfId, x310320_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x310320_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x310320_g_MissionId, state, 0 )
	--end
	AddQuestNumText(sceneId,x310320_g_MissionId,"����������ս˵����" ,0,1)
	--AddQuestNumText(sceneId,x310320_g_MissionId,"��ȡ����" ,3,2)
end
function x310320_ProcQuestAttach( sceneId, selfId, NPCId, npcGuid, misIndex, MissionId)
	--print("x310320_ProcQuestAttach")
end

function x310320_GetHongNum(sceneId ,selfId)
	return x310320_g_HongNum
end

function x310320_SetHongNumInc(sceneId ,selfId, inc)
	x310320_g_HongNum = x310320_g_HongNum + inc
	if x310320_g_HongNum <= 0 then
		x310320_g_HongNum = 0
	end
	return x310320_g_HongNum
end

function x310320_GetLanNum(sceneId ,selfId)
	--print("x310320_GetLanNum",x310320_g_LanNum)
	return x310320_g_LanNum
end

function x310320_SetLanNumInc(sceneId ,selfId, inc)
	x310320_g_LanNum = x310320_g_LanNum + inc
	if x310320_g_LanNum <= 0 then
		x310320_g_LanNum = 0
	end
	--print("x310320_SetLanNumInc",x310320_g_LanNum)
	return x310320_g_LanNum
end



function x310320_CheckTime(sceneId ,selfId, npcId)
	local hour,minute,sec =GetHourMinSec();
	if hour >= 12 and hour <= 22 and minute >= 0 and minute < 10 then
		return 1
	end
	return 0
end

function x310320_GetCountMD(sceneId ,selfId)
	local today = GetDayOfYear()
	local lastDay = GetQuestData(sceneId, selfId, MD_HONGLAN_DATE[1], MD_HONGLAN_DATE[2], MD_HONGLAN_DATE[3])
	if today == lastDay then
		local count = GetQuestData(sceneId, selfId, MD_HONGLAN_COUNT[1], MD_HONGLAN_COUNT[2], MD_HONGLAN_COUNT[3])
		return count
	else
		SetQuestData(sceneId,selfId,MD_HONGLAN_DATE[1],MD_HONGLAN_DATE[2],MD_HONGLAN_DATE[3], today)
       	SetQuestData(sceneId,selfId,MD_HONGLAN_COUNT[1],MD_HONGLAN_COUNT[2],MD_HONGLAN_COUNT[3], 0)    
		return 0
    end  
end

function x310320_IncCountMD(sceneId ,selfId)
	local today = GetDayOfYear()
	local lastDay = GetQuestData(sceneId, selfId, MD_HONGLAN_DATE[1], MD_HONGLAN_DATE[2], MD_HONGLAN_DATE[3])
	if today == lastDay then
		local count = GetQuestData(sceneId, selfId, MD_HONGLAN_COUNT[1], MD_HONGLAN_COUNT[2], MD_HONGLAN_COUNT[3])
		count = count + 1
		SetQuestData(sceneId,selfId,MD_HONGLAN_COUNT[1],MD_HONGLAN_COUNT[2],MD_HONGLAN_COUNT[3], count)
		return count
	else
		SetQuestData(sceneId,selfId,MD_HONGLAN_DATE[1],MD_HONGLAN_DATE[2],MD_HONGLAN_DATE[3], today)
       	SetQuestData(sceneId,selfId,MD_HONGLAN_COUNT[1],MD_HONGLAN_COUNT[2],MD_HONGLAN_COUNT[3], 1)    
       	return 1
    end  
end
function x310320_GetHonglanState(sceneId ,selfId)
	return x310320_g_State
end

function x310320_DecCountMD(sceneId ,selfId)
	local count = GetQuestData(sceneId, selfId, MD_HONGLAN_COUNT[1], MD_HONGLAN_COUNT[2], MD_HONGLAN_COUNT[3])
	count = count - 1
	if count <= 0 then
		count = 0
	end
	SetQuestData(sceneId,selfId,MD_HONGLAN_COUNT[1],MD_HONGLAN_COUNT[2],MD_HONGLAN_COUNT[3], count)
	return count
end

function x310320_IsWinner(sceneId ,selfId )	--�Ƿ�Ӯ��
	if x310320_g_HongNum > x310320_g_LanNum then
		if IsHaveSpecificImpact( sceneId, selfId, x310320_g_LanBuff) == 1 then
			return 1
		else
			return 0
		end
	elseif x310320_g_HongNum < x310320_g_LanNum then
		if IsHaveSpecificImpact( sceneId, selfId, x310320_g_HongBuff) == 1 then
			return 1
		else
			return 0
		end
	else
		return 0
	end
	
end


---------------------------------------------------------------------------------------------------
--��������Ƿ���ύ
---------------------------------------------------------------------------------------------------
function x310320_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310320_g_MissionId)

    if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
        return 1
    else
        return 0
    end
end


function x310320_ProcEventEntry(sceneId ,selfId, NPCId,idScript,idExt )	--����������ִ�д˽ű�
	local level = GetLevel( sceneId, selfId)
	local exp   = level * x310320_g_CoffExp
	--print("x310320_ProcEventEntry")
	if idExt == 0 then
		if IsQuestHaveDone(sceneId, selfId, x310320_g_MissionId) > 0 then
			BeginQuestEvent(sceneId)
        	AddQuestText(sceneId,"��������ı�������ս�Ѿ���������ȥ�ұ�������ս���񷢲����ύ����ɣ�")
        	EndQuestEvent(sceneId)
        	DispatchQuestEventList(sceneId,selfId,NPCId)
			return
		end
		
		if IsHaveQuest(sceneId,selfId, x310320_g_MissionId) > 0 then
			local bDone = x310320_CheckSubmit( sceneId, selfId, NPCId)
            if bDone > 0 then
                x310320_DispatchCompletedInfo( sceneId, selfId, NPCId) --���������ʾ
            else
                x310320_DispatchContinueInfo( sceneId, selfId, NPCId) --δ���������ʾ
            end
            
            
--			BeginQuestEvent(sceneId)
--        	AddQuestText(sceneId,"�����д�����")
--        	EndQuestEvent(sceneId)
--        	DispatchQuestEventList(sceneId,selfId,NPCId)
			return
		end
		
		
		
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x310320_g_MissionName)
        AddQuestText(sceneId,x310320_g_MissionInfo)
        AddQuestText( sceneId,"#Y����Ŀ��:")
        AddQuestText( sceneId,x310320_g_MissionTarget)
        --AddQuestItemBonus(sceneId,10011001,1)
        AddQuestExpBonus(sceneId, exp )
        --6����ѡ��Ʒ
		--AddQuestRadioItemBonus(sceneId, item.item, item.n)
        --AddQuestText(sceneId,format("����ֵ��%d",10000))
        EndQuestEvent(sceneId)
        --DispatchQuestEventList(sceneId,selfId,NPCId)
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x310320_g_ScriptId, x310320_g_MissionId)
        

	elseif idExt == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y����������ս����˵����")
        AddQuestText(sceneId,"#Y��ȡ����\n\t#W65�����ϵ���ң�ÿ��������12��00-����22��00ÿ��������Խ�ȡ����ÿ�ο���#Y10����#W��������10������\n\tÿ�����ÿ�������Խ�ȡ�������񡣵�һ�ν�ȡ������ѣ��������ξ�Ҫ����#R1���ֽ�/��#W��")
        AddQuestText(sceneId,"#Y�淨���̣�\n\t#W��ȡ���������Ҫ���ڱ��������ֻ������ѡ��֧��һ����������ʱ�����֮ǰ�����㿪�ź�10�����ڣ���������ʱ����һֻ����ת�����֧�ֶ���\n\t������ʱ�������#G֧������#R����#G�ı�������ʤ�������#R˫���Ľ���#G����֧������#R�϶�#G�ı�����ֻ������ͨ�Ľ�����")
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
    elseif idExt == 2 then
    	if x310320_CheckSubmit( sceneId, selfId, NPCId) ~= 1 then
    		BeginQuestEvent(sceneId)
	        AddQuestText(sceneId,"����δ����")
	        EndQuestEvent(sceneId)
	        DispatchQuestEventList(sceneId,selfId,NPCId)
    		return
    	end
    	if x310320_IsWinner(sceneId ,selfId ) == 1 then
    		BeginQuestEvent(sceneId)
	        AddQuestText(sceneId,"Ӯ��")
	        EndQuestEvent(sceneId)
	        DispatchQuestEventList(sceneId,selfId,NPCId)
    	else
	    	BeginQuestEvent(sceneId)
	        AddQuestText(sceneId,"�䷽")
	        EndQuestEvent(sceneId)
	        DispatchQuestEventList(sceneId,selfId,NPCId)
    	end
	end
	

end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x310320_DispatchContinueInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x310320_g_MissionName)
    AddQuestText( sceneId, x310320_g_ContinueInfo)
    AddQuestText( sceneId, " ")
 
    DispatchQuestEventList( sceneId, selfId, NPCId)
	
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x310320_DispatchCompletedInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x310320_g_MissionName)
    AddQuestText( sceneId, x310320_g_MissionCompleted)
    AddQuestText( sceneId, " ")
    local level = GetLevel( sceneId, selfId)
    
	EndQuestEvent( sceneId)
    DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x310320_g_ScriptId, x310320_g_MissionId)
end

function x310320_DispatchMissionInfo( sceneId, selfId, NPCId)
	
	BeginQuestEvent( sceneId)

    --������Ϣ
    AddQuestText( sceneId, "#Y"..x310320_g_MissionName)
    AddQuestText( sceneId, x310320_g_MissionInfo)
    AddQuestText( sceneId, " ")
           
    --����Ŀ��
    AddQuestText( sceneId, "#Y����Ŀ�꣺")
    AddQuestText( sceneId, x310320_g_MissionTarget)
    AddQuestText( sceneId, " ")

    --��ʾ��Ϣ
    if x310320_g_MissionHelp ~= "" then
        AddQuestText( sceneId, "#Y������ʾ��")
        AddQuestText( sceneId, x310320_g_MissionHelp)
        AddQuestText( sceneId, " ")
    end                 

	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x310320_g_ScriptId, x310320_g_MissionId)
end

function x310320_OnTimerDoingStart( sceneId, TimerId, Param1, Param2, Param3, Param4, Param5)
	--print("x310320_OnTimerDoingStart")
    SetSystemTimerTick( sceneId, 310320, "OnTimer", TimerId, 10000)
    LuaAllScenceM2Wrold (sceneId, "��һ�ֱ�������ս��ʼ�ˣ���λ��ҿ���ͨ�����ϵ�#G�����˼䴫���ˣ�128��70��#R���������˼䡤���룬�ҵ�#G��������ս�����ˣ�70��59��#R�μӣ�", 1, 1)
    
end

function x310320_OnMissionFinish( sceneId )
		
	local nHumanCount = GetScenePlayerCount( sceneId)
    if nHumanCount > 0 then
        for i = 0, nHumanCount do
            local objId = GetScenePlayerObjId( sceneId,i)
            if objId >= 0 then
            	if IsHaveQuest(sceneId,objId, x310320_g_MissionId) > 0 then
	                CancelSpecificImpact( sceneId, objId, x310320_g_LanBuff)
	                CancelSpecificImpact( sceneId, objId, x310320_g_HongBuff)
                local misIndex = GetQuestIndexByID( sceneId, objId, x310320_g_MissionId)               
                if x310320_IsWinner(sceneId,objId) == 1 then   --6��ʶΪ���Ӯ��
                	SetQuestByIndex( sceneId, objId, misIndex, 6, 1)
                else
                	SetQuestByIndex( sceneId, objId, misIndex, 6, 0)                	
                end
                if x310320_g_HongNum > x310320_g_LanNum then
                	Msg2Player( sceneId, objId, format("���ֱ�������ս�Ѿ�������#G�����뱩��#R��֧����������#G%d��%d#R��",x310320_g_HongNum,x310320_g_LanNum), 0, 1)
        					Msg2Player( sceneId, objId, format("���ֱ�������ս�Ѿ������������뱩����֧����������#G%d��%d#cffcf00��",x310320_g_HongNum,x310320_g_LanNum), 0, 2)
        					Msg2Player( sceneId, objId, format("����#G����#R��֧���߿��Ի��˫���Ľ�����",x310320_g_HongNum,x310320_g_LanNum), 0, 1)
        					Msg2Player( sceneId, objId, format("����#G����#cffcf00��֧���߿��Ի��˫���Ľ�����",x310320_g_HongNum,x310320_g_LanNum), 0, 2)
                elseif  x310320_g_LanNum > x310320_g_HongNum then
                	Msg2Player( sceneId, objId, format("���ֱ�������ս�Ѿ�������#G�����뱩��#R��֧����������#G%d��%d#R��",x310320_g_HongNum,x310320_g_LanNum), 0, 1)
        					Msg2Player( sceneId, objId, format("���ֱ�������ս�Ѿ������������뱩����֧����������#G%d��%d#cffcf00��",x310320_g_HongNum,x310320_g_LanNum), 0, 2)
        					Msg2Player( sceneId, objId, format("����#G����#R��֧���߿��Ի��˫���Ľ�����",x310320_g_HongNum,x310320_g_LanNum), 0, 1)
        					Msg2Player( sceneId, objId, format("����#G����#cffcf00��֧���߿��Ի��˫���Ľ�����",x310320_g_HongNum,x310320_g_LanNum), 0, 2)
        				else
        					Msg2Player( sceneId, objId, format("���ֱ�������ս�Ѿ�������#G�����뱩��#R��֧����������#G%d��%d#R��",x310320_g_HongNum,x310320_g_LanNum), 0, 1)
        					Msg2Player( sceneId, objId, format("���ֱ�������ս�Ѿ������������뱩����֧����������#G%d��%d#cffcf00��",x310320_g_HongNum,x310320_g_LanNum), 0, 2)
        					Msg2Player( sceneId, objId, format("˫��֧���߶�ֻ�ܻ����ͨ�Ľ�����",x310320_g_HongNum,x310320_g_LanNum), 0, 1)
        					Msg2Player( sceneId, objId, format("˫��֧���߶�ֻ�ܻ����ͨ�Ľ�����",x310320_g_HongNum,x310320_g_LanNum), 0, 2)
        				end	
                SetQuestByIndex( sceneId, objId, misIndex, 0, 1)
        		SetQuestByIndex( sceneId, objId, misIndex, 7, 1)
        		
        		--Msg2Player(sceneId, objId, "���������", 0, 3)
	        	end
            end
        end
    end
    
    if x310320_g_HongNum > x310320_g_LanNum then
       LuaThisScenceM2Wrold( sceneId, format("������ʤ��",x310320_g_HongNum,x310320_g_LanNum), 5, 1)
    elseif  x310320_g_LanNum > x310320_g_HongNum then
      LuaThisScenceM2Wrold( sceneId, format("�����ʤ��",x310320_g_HongNum,x310320_g_LanNum), 5, 1)
    else
      LuaThisScenceM2Wrold( sceneId, format("��������δ��ʤ����",x310320_g_HongNum,x310320_g_LanNum), 5, 1)
    end	
    
  x310320_g_HongNum	= 0
	x310320_g_LanNum	= 0
end

function x310320_OnTimer( sceneId, TimerId, uTime)
	--print("x310320_OnTimer", uTime,x310320_g_State)
	local hour,minute,sec =GetHourMinSec();
	if hour >= 12 and hour <= 22 and minute >= 0 and minute <= 10 then
		x310320_g_State = 1
	else
		x310320_g_State = 0
	end
	
	local msg = format("start timer minute =%d sec =%d",minute,sec)
	--Msg2Player(sceneId, x310320_g_SelfId, msg, 0, 2)
	local nHumanCount = GetScenePlayerCount( sceneId)
    if nHumanCount > 0 then
        for i = 0, nHumanCount do
            local objId = GetScenePlayerObjId( sceneId,i)
            if objId >= 0 then
               --Msg2Player(sceneId, objId, msg , 0, 3)
            end
        end
    end
    
	--print("hour",hour)
	--print("minute",minute)
	if hour >= 12 and hour <= 22 and minute == 10 then
		--if x310320_g_State == 1 then
		--	print("x310320_OnMissionFinish")
			
			--print("------------------2")
			x310320_OnMissionFinish( sceneId )
			x310320_g_State = 0
			return
		--end
	end
	
	SetSystemTimerTick( sceneId, 310320, "OnTimer", TimerId, 1000)
end

function x310320_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	local level =GetLevel(sceneId, selfId)
	local exp   =level *x310320_g_CoffExp
	BeginQuestEvent( sceneId)
	AddQuestLogCustomText( sceneId,
                                   x310320_g_MissionName,               -- ����
                                   x310320_g_MissionName,               -- ��������
                                   x310320_g_MissionTarget1,                   				 -- ����Ŀ��
                                   "@npc_145000",              -- ����NPC
                                   "������",               -- ������
                                   x310320_g_MissionInfo,    -- ��������
                                   "") 
                                                -- ������ʾ
                                                
    AddQuestExpBonus( sceneId, exp)
    --AddQuestItemBonus(sceneId,10018001,1)
    --AddQuestMoneyBonus1( sceneId, money)                                            
    EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId)
end


function x310320_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end


-------------------------------------------------------------------------------
--���״̬�Ƿ�����
-------------------------------------------------------------------------------
function x310320_CheckPlayerState( sceneId,selfId )
    

    local state
    local ErrorMsg

    state = IsPlayerStateNormal(sceneId,selfId )
    if state == 0 then
        ErrorMsg = "״̬�쳣"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_MENTALGAME )
    if state == 1 then
        ErrorMsg = "���ڴ���״̬�����ܽ�������"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_STALL )
    if state == 1 then
        ErrorMsg = "���ڰ�̯״̬�����ܽ�������"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE )
    if state == 1 then
        ErrorMsg = "��������״̬�����ܽ�������"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_CRASHBOX )
    if state == 1 then
        ErrorMsg = "��������״̬�����ܽ�������"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_AUTOPLAY )
    if state == 1 then
        ErrorMsg = "���ڹһ�״̬�����ܽ�������"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_SUBTRAIN )
    if state == 1 then
        ErrorMsg = "���ڴ���״̬�����ܽ�������"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_BUS )
    if state == 1 then
        ErrorMsg = "����BUS״̬�����ܽ�������"
        return 1,ErrorMsg
    end

--    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_PKMODE )
--    if state == 1 then
--        ErrorMsg = "PKֵ���߻��ڿ�ģʽ�����ܽ�������"
--        return 1,ErrorMsg
--    end

    return 0

end


function x310320_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310320_g_MissionId)
   	SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
    SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        		
        		
	--print("x310320_ProcQuestAccept")
	if IsQuestHaveDone(sceneId, selfId, x310320_g_MissionId) > 0 then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"\t���Ѿ����ܡ����ˡ���������ս�����ˡ�")
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
        return 
    end

	local state,msg = x310320_CheckPlayerState( sceneId,selfId )
    if state == 1 then
       	BeginQuestEvent(sceneId)
    	AddQuestText( sceneId, msg );
    	EndQuestEvent(sceneId)
    	DispatchQuestTips(sceneId,selfId)
    	return
    end	

	
    
    local level = GetLevel(sceneId, selfId)
	if GetLevel( sceneId, selfId) > x310320_g_MaxLevel then
    	Msg2Player(sceneId, selfId, "ֻ�е���85������Ҳ��ܽ��ܱ�����", 0, 2)
   		Msg2Player(sceneId, selfId, "ֻ�е���85������Ҳ��ܽ��ܱ�����", 0, 3)   
		return
	end
		
		
    if IsQuestFullNM(sceneId,selfId)==1 then
 				Msg2Player(sceneId, selfId, "�����������������ʧ��", 0, 2)
   			Msg2Player(sceneId, selfId, "�����������������ʧ��", 0, 3)  
        return 
    end
	local level = GetLevel(sceneId, selfId)
	if GetLevel( sceneId, selfId) < x310320_g_MinLevel or GetLevel( sceneId, selfId) > x310320_g_MaxLevel then
 				Msg2Player(sceneId, selfId, "ֻ�е���85������Ҳ��ܽ�������", 0, 2)
   			Msg2Player(sceneId, selfId, "ֻ������85������Ҳ��ܽ�������", 0, 3)      	
		return
	end
	
	local weekDay = GetWeek()
	if weekDay ~= 0 and weekDay ~= 6 then
 				Msg2Player(sceneId, selfId, "�ܱ�Ǹ�������ˡ���������ս��ÿ�������տ���", 0, 2)
   			Msg2Player(sceneId, selfId, "�ܱ�Ǹ�������ˡ���������ս��ÿ�������տ���", 0, 3)   	
		return --TEST
	end
	if x310320_CheckTime(sceneId ,selfId, npcId) < 1 then
 				Msg2Player(sceneId, selfId, "�ܱ�Ǹ�������ˡ���������ս������12��00-����22��00֮�䣬ÿ�����㿪��", 0, 2)
   			Msg2Player(sceneId, selfId, "�ܱ�Ǹ�������ˡ���������ս������12��00-����22��00֮�䣬ÿ�����㿪��", 0, 3)     	
		return --TEST
	end
	
	local count = x310320_GetCountMD(sceneId ,selfId)
	if count >= 3 then
 				Msg2Player(sceneId, selfId, "������Ѿ�����3�Ρ����ˡ���������ս�ˣ����������", 0, 2)
   			Msg2Player(sceneId, selfId, "������Ѿ�����3�Ρ����ˡ���������ս�ˣ����������", 0, 3)
		return
	end
		
	if count >= 1 then  --���ǵ�һ����Ҫ��Ǯ
		if CostMoney(sceneId,selfId,3,x310320_g_CostGold) ~= -1 then
			Msg2Player(sceneId, selfId, "��ȡ����ɹ����۳�1���𿨣�", 0, 3)
			Msg2Player(sceneId, selfId, "��ȡ����ɹ����۳�1���𿨣�", 0, 2)
			Msg2Player(sceneId, selfId, "�۳�1����ң�", 0, 2)
		else
			if CostMoney(sceneId,selfId,2,x310320_g_CostGold,324) ~= -1 then
				Msg2Player(sceneId, selfId, "��ȡ����ɹ����۳�1���ֽ�", 0, 3)
				Msg2Player(sceneId, selfId, "��ȡ����ɹ����۳�1���ֽ�", 0, 2)
				Msg2Player(sceneId, selfId, "�۳�1����ң�", 0, 2)
			else
				BeginQuestEvent(sceneId)
	    	Msg2Player(sceneId, selfId, "���ź�������ֽ�/�𿨲���1��", 0, 3)
				Msg2Player(sceneId, selfId, "���ź�������ֽ�/�𿨲���1��", 0, 2)
	    		return
			end
		end
	end
	
	local retmiss = AddQuest( sceneId, selfId, x310320_g_MissionId, x310320_g_ScriptId, 0, 0, 0, 1)
   	if retmiss ==0 then
       Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
       return 0
   	end
   	
	
   	x310320_IncCountMD(sceneId ,selfId)  
   	local hour,minute,sec =GetHourMinSec()   	
    BeginQuestEvent(sceneId)
   	AddQuestText(sceneId,"\t��ɹ��Ľ����ˡ����ˡ���������ս�������ȥѡ��֧�ֱ������߱�������ͷ����֮һ�����Ǿ����ҵ����ߡ�\n\t��Ҫ�ٴ������㣺#G֧���������ٵı�������ʤ����#W����������#Y"..hour.."��10��".."#W���������ƿغ����ʱ�䡣")
   	EndQuestEvent(sceneId)
   	DispatchQuestEventList(sceneId,selfId,NPCId)
	
	x310320_ProcQuestLogRefresh( sceneId, selfId, x310320_g_MissionId)
	
	-- д��־
    GamePlayScriptLog( sceneId, selfId, x310320_g_AcceptMissionLogID)
end

function x310320_ProcQuestAbandon(sceneId, selfId, MissionId)
    if IsHaveQuest(sceneId,selfId, x310320_g_MissionId) <= 0 then
        return 
    end
    
    DelQuest( sceneId, selfId, x310320_g_MissionId)
    Msg2Player(sceneId, selfId, format("������������:%s",x310320_g_MissionName), 0, 2)
    Msg2Player(sceneId, selfId, format("������������:%s",x310320_g_MissionName), 0, 3) 
     
   	--x310320_DecCountMD(sceneId ,selfId)   --����Ҳ�ƴ�
    
   	if IsHaveSpecificImpact( sceneId, selfId, x310320_g_HongBuff ) == 1 then
   		CancelSpecificImpact( sceneId, selfId, x310320_g_HongBuff)
		x310320_g_HongNum	= x310320_g_HongNum	- 1
	elseif IsHaveSpecificImpact( sceneId, selfId, x310320_g_LanBuff) == 1 then
		CancelSpecificImpact( sceneId, selfId, x310320_g_LanBuff)
		x310320_g_LanNum	= x310320_g_LanNum - 1
	end   		
end




function x310320_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	local level =GetLevel( sceneId, selfId)
	local exp 	=x310320_g_CoffExp * level
	if IsHaveQuest(sceneId,selfId, x310320_g_MissionId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"��û���������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	else
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310320_g_MissionId)
   		local IsWin = GetQuestParam( sceneId, selfId, misIndex, 6)
		if DelQuest(sceneId, selfId, x310320_g_MissionId) > 0 then
			if IsWin == 1 then
				exp =exp*2
    		BeginQuestEvent(sceneId)
	        AddQuestText(sceneId,x310320_g_MissionCompleted1)
	        EndQuestEvent(sceneId)
	        DispatchQuestEventList(sceneId,selfId,NPCId)
	        AddExp(sceneId, selfId, exp)
	      EndQuestEvent()
    	else
	    	BeginQuestEvent(sceneId)
	        AddQuestText(sceneId,x310320_g_MissionCompleted2)
	        EndQuestEvent(sceneId)
	        DispatchQuestEventList(sceneId,selfId,NPCId)
	        AddExp(sceneId, selfId, exp)
	      EndQuestEvent()  
    	end
    	Msg2Player( sceneId, selfId, format( "���#R����%d��#cffcf00�Ľ���", exp).."��", 8, 2)
			Msg2Player( sceneId, selfId, format( "���#R����%d��#cffcf00�Ľ���", exp), 8, 3)
       end
	
       -- AddItemListToPlayer(sceneId,selfId)
   end
   
   GamePlayScriptLog( sceneId, selfId, x310320_g_FinishMissionLogID)
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x310320_g_MissionIdNext )	
end

 