

--MisDescBegin
x310322_g_ScriptId = 310322
--x310322_g_MissionIdPre ={67,69,70,71}
x310322_g_MissionId = 9050 

x310322_g_MissionName="�����ˡ����ı���"
x310322_g_MissionTarget				= "��5�������˼䡤�����ڵ�#G����#W"      --����Ŀ��
x310322_g_MissionInfo				= "\t��ӭ�㣬���װ������ѡ�\n\t���������˼䡤�����У����������������ʯ�Ļƽ��䡣��˵ÿ�������ﶼ����#G���������ϡ�еı���#W��Ҳ��һЩ�����з�ӡ��#G���µ�ħ��#W��\n\tÿ����������������ȡ5���������е�һ�������ȡ����4��ÿ�ν�ȡ��#Y����1���ֽ���#W��\n\t������ֵ�ʱ����ÿ�������յģ�\n#G12��35��12��50#W��#G13��35��13��50#W��\n#G14��35��14��50#W��#G15��35��15��50#W��\n#G16��35��16��50#W��#G17��35��17��50#W��\n#G18��35��18��50#W��#G19��35��19��50#W��\n#G20��35��20��50#W��#G21��35��21��50#W��\n#G22��35��22��50#W"            --������Ϣx310322_g_ContinueInfo				= "\t�ѵ��㺦������ճ�����ħ����"  --���������Ϣ
x310322_g_ContinueInfo				= "\t�򿪱���֮ǰ��˭Ҳ��֪��������ŵ���ʲô��"
x310322_g_MissionCompleted			= "\t��ϲ������ˡ����ˡ����ı��������ڿ����ƽ�����һ�̣����ǲ��ǳ������ڴ���"  --���������Ϣ
x310322_g_MissionHelp				= ""          --������ʾ��Ϣ
-- ���������ʾ��Ϣ
x300320_g_strMissionAbandon         = "�����������񣺡����ˡ����ı���"


--MisDescEnd
--**********************************

x310322_g_MinLevel	= 65
x310322_g_MaxLevel	= 84
x310322_g_strGongLue = "#G����#W�����ض�ʱ������������˼䡤������#G����������#W��#G��������#W��#G��תľ����#W��#GĦ������#W�ȵط���"




x310322_g_CostGold	= 1000 --1���ֽ�

--MD_XIANGZI_DATE			--����			9
--MD_XIANGZI_COUNT        	--����			5


function x310322_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsHaveQuest(sceneId,selfId, x310322_g_MissionId) <= 0 then
		if GetLevel( sceneId, selfId) < x310322_g_MinLevel then 
	 		return 0
		end
	end	
	
	local state = GetQuestStateNM(sceneId,selfId,NPCId,x310322_g_MissionId)
	AddQuestTextNM( sceneId, selfId, NPCId, x310322_g_MissionId, state, 0 )

 	AddQuestNumText(sceneId,x310322_g_MissionId,"�����ı���˵����" ,13,1)
	--AddQuestNumText(sceneId,x310322_g_MissionId,"��ȡ����" ,3,2)
	

end
function x310322_ProcQuestAttach( sceneId, selfId, NPCId, npcGuid, misIndex, MissionId)
	--print("x310322_ProcQuestAttach")
end

function x310322_GetCount(sceneId ,selfId, npcId)
	local hour,minute,sec =GetHourMinSec();
	local nowtime = hour*60+minute
	
	local today = GetDayOfYear()
	local lastDay = GetQuestData(sceneId, selfId, MD_XIANGZI_DATE[1], MD_XIANGZI_DATE[2], MD_XIANGZI_DATE[3])
	if today ~= lastDay then
		return 0
	end
	
	local count = GetQuestData(sceneId, selfId, MD_XIANGZI_COUNT[1], MD_XIANGZI_COUNT[2], MD_XIANGZI_COUNT[3])
	
	return count
end

function x310322_CheckTime(sceneId ,selfId, npcId)
	local hour,minute,sec =GetHourMinSec();
	if hour >= 12 and hour <= 23 then
		return 1
	end
	return 0
end
function x310322_IncCountMD(sceneId ,selfId)
	local today = GetDayOfYear()
	local lastDay = GetQuestData(sceneId, selfId, MD_XIANGZI_DATE[1], MD_XIANGZI_DATE[2], MD_XIANGZI_DATE[3])
	if today == lastDay then
		local count = GetQuestData(sceneId, selfId, MD_XIANGZI_COUNT[1], MD_XIANGZI_COUNT[2], MD_XIANGZI_COUNT[3])
		count = count + 1
		SetQuestData(sceneId,selfId,MD_XIANGZI_COUNT[1],MD_XIANGZI_COUNT[2],MD_XIANGZI_COUNT[3], count)
		return count
	else
		SetQuestData(sceneId,selfId,MD_XIANGZI_DATE[1],MD_XIANGZI_DATE[2],MD_XIANGZI_DATE[3], today)
       	SetQuestData(sceneId,selfId,MD_XIANGZI_COUNT[1],MD_XIANGZI_COUNT[2],MD_XIANGZI_COUNT[3], 1)    
       	return 1
    end  
end

function x310322_DecCountMD(sceneId ,selfId)
	local count = GetQuestData(sceneId, selfId, MD_XIANGZI_COUNT[1], MD_XIANGZI_COUNT[2], MD_XIANGZI_COUNT[3])
	count = count - 1
	if count <= 0 then
		count = 0
	end
	SetQuestData(sceneId,selfId,MD_XIANGZI_COUNT[1],MD_XIANGZI_COUNT[2],MD_XIANGZI_COUNT[3], count)
	return count
end


---------------------------------------------------------------------------------------------------
--��������Ƿ���ύ
---------------------------------------------------------------------------------------------------
function x310322_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310322_g_MissionId)

    if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
        return 1
    else
        return 0
    end
end


function x310322_ProcEventEntry(sceneId ,selfId, NPCId,idScript,idExt )	--����������ִ�д˽ű�
	--print("x310322_ProcEventEntry")
	if idExt == 0 then
		if IsQuestHaveDone(sceneId, selfId, x310322_g_MissionId) > 0 then
			BeginQuestEvent(sceneId)
        	AddQuestText(sceneId,"������ɴ�����")
        	EndQuestEvent(sceneId)
        	DispatchQuestEventList(sceneId,selfId,NPCId)
			return
		end
		
		if IsHaveQuest(sceneId,selfId, x310322_g_MissionId) > 0 then
			local bDone = x310322_CheckSubmit( sceneId, selfId, NPCId)
            if bDone > 0 then
                x310322_DispatchCompletedInfo( sceneId, selfId, NPCId) --���������ʾ
            else
                x310322_DispatchContinueInfo( sceneId, selfId, NPCId) --δ���������ʾ
            end
            
            
--			BeginQuestEvent(sceneId)
--        	AddQuestText(sceneId,"�����д�����")
--        	EndQuestEvent(sceneId)
--        	DispatchQuestEventList(sceneId,selfId,NPCId)
			return
		end
		
		
		
		
		BeginQuestEvent(sceneId)
		local level =GetLevel( sceneId, selfId)
		local exp =  level *64800
		AddQuestText(sceneId,"#Y"..x310322_g_MissionName)
        AddQuestText(sceneId,x310322_g_MissionInfo)
        AddQuestText( sceneId,"#Y����Ŀ��:")
        AddQuestText( sceneId,x310322_g_MissionTarget)        
        AddQuestExpBonus(sceneId, exp )
        EndQuestEvent(sceneId)
        --DispatchQuestEventList(sceneId,selfId,NPCId)
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x310322_g_ScriptId, x310322_g_MissionId)
        

	elseif idExt == 1 then
		BeginQuestEvent(sceneId)
				local Readme_1 = "#Y�����ı���˵����#r#W"
				AddQuestText(sceneId,"#Y��ȡ����\n\t#W65�����ϵ���ң�ÿ��������12��30-22��50���Խ�ȡ����\n\tÿ�����ÿ�������Խ�ȡ������񡣵�һ�ν�ȡ������ѣ������Ĵξ�Ҫ����#R1���ֽ�/��#W��")
        AddQuestText(sceneId,"#Y�淨���̣�\n\t#W��ȡ���������Ҫ��#G�ض�ʱ��#W��,�ҵ�ɢ���������˼䡤���������#G����#W��\n\t�ɼ�������п��ܻ������¼��ֽ�����\n\t1.��������ó��������顣\n\t2.��õ��������˼䡤����ر�ͼ��Ƭ���������Ҳ����Ӻϳ������˼䡤����ر�ͼ����\n\t3.��õ���ħ�������ٻ�����\n\t4.ԭ���ͷų�һ��ʮ��ħ����\n \n#Y������ֵ�ʱ��:#W\n#G12��35��12��50#W��#G13��35��13��50#W��\n#G14��35��14��50#W��#G15��35��15��50#W��\n#G16��35��16��50#W��#G17��35��17��50#W��\n#G18��35��18��50#W��#G19��35��19��50#W��\n#G20��35��20��50#W��#G21��35��21��50#W��\n#G22��35��22��50#W��")
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
    elseif idExt == 2 then
    	
	end
	

end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x310322_DispatchContinueInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x310322_g_MissionName)
    AddQuestText( sceneId, x310322_g_ContinueInfo)
    AddQuestText( sceneId, " ")
 
    DispatchQuestEventList( sceneId, selfId, NPCId)
	
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x310322_DispatchCompletedInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x310322_g_MissionName)
    AddQuestText( sceneId, x310322_g_MissionCompleted)
    AddQuestText( sceneId, " ")
    local level = GetLevel( sceneId, selfId)
    
	EndQuestEvent( sceneId)
    DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x310322_g_ScriptId, x310322_g_MissionId)
end

function x310322DispatchMissionInfo( sceneId, selfId, NPCId)
	
	BeginQuestEvent( sceneId)

    --������Ϣ
    AddQuestText( sceneId, "#Y"..x310322_g_MissionName)
    AddQuestText( sceneId, x310322_g_MissionInfo)
    AddQuestText( sceneId, " ")
           
    --����Ŀ��
    AddQuestText( sceneId, "#Y����Ŀ�꣺")
    AddQuestText( sceneId, x310322_g_MissionTarget)
    AddQuestText( sceneId, " ")

    --��ʾ��Ϣ
    if x310322_g_MissionHelp ~= "" then
        AddQuestText( sceneId, "#Y������ʾ��")
        AddQuestText( sceneId, x310322_g_MissionHelp)
        AddQuestText( sceneId, " ")
    end                 

	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x310322_g_ScriptId, x310322_g_MissionId)
end

function x310322_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	BeginQuestEvent( sceneId)
	local level =GetLevel( sceneId, selfId)
	local exp =  level *64800
	local misIndex = GetQuestIndexByID(sceneId,selfId,x310322_g_MissionId)
	local num = GetQuestParam( sceneId,selfId,misIndex,1)
	local strTarget = " ���������˼䡤�����ڵ�#G����#W��"..num.."/".."#W"..5
	AddQuestLogCustomText( sceneId,
                                   x310322_g_MissionName,               -- ����
                                   x310322_g_MissionName,               -- ��������
                                   strTarget,                   				 -- ����Ŀ��
                                   "",              -- ����NPC
                                   x310322_g_strGongLue,               -- ������
                                   x310322_g_MissionInfo,    -- ��������
                                   x310322_g_MissionHelp) 
                                                -- ������ʾ
                                                
    AddQuestExpBonus( sceneId, exp)                                            
    EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, x310322_g_MissionId)
end


function x310322_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end



function x310322_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
	--print("x310322_ProcQuestAccept")
	
	local count = GetQuestData(sceneId,selfId,MD_XIANGZI_COUNT[1],MD_XIANGZI_COUNT[2],MD_XIANGZI_COUNT[3])    
		

	if IsQuestHaveDone(sceneId, selfId, x310322_g_MissionId) > 0 then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"���Ѿ��д�����")
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
        return 
    end
    
    local level = GetLevel(sceneId, selfId)
	if  GetLevel( sceneId, selfId) > x310322_g_MaxLevel then
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
		if GetLevel( sceneId, selfId) < x310322_g_MinLevel or GetLevel( sceneId, selfId) > x310322_g_MaxLevel then
			BeginQuestEvent(sceneId)
        	AddQuestText(sceneId,"�ȼ�������65����84��֮�䣬�޷���ȡ����")
        	EndQuestEvent(sceneId)
        	DispatchQuestEventList(sceneId,selfId,NPCId)
			return
		end
		
		local weekDay = GetWeek()
		if weekDay ~= 0 and weekDay ~= 6 then
		BeginQuestEvent(sceneId)
        	AddQuestText(sceneId,"\t�ܱ�Ǹ�������δ���ţ�������������12��30�Ժ�������ȡ")
        	EndQuestEvent(sceneId)
        	DispatchQuestEventList(sceneId,selfId,NPCId)       	       	
        Msg2Player(sceneId, selfId, "�ܱ�Ǹ�������δ���ţ�������������12��30�Ժ�������ȡ", 0, 2)
   			Msg2Player(sceneId, selfId, "�ܱ�Ǹ�������δ���ţ�������������12��30�Ժ�������ȡ", 0, 3)   
			return --TEST
		end
		if x310322_CheckTime(sceneId ,selfId, npcId) < 1 then       	
       Msg2Player(sceneId, selfId, "�ܱ�Ǹ���������ʱ��Ϊ12��30-22��50", 0, 2)
   		 Msg2Player(sceneId, selfId, "�ܱ�Ǹ���������ʱ��Ϊ12��30-22��50", 0, 3) 
			return --TEST
		end
		
		local count = x310322_GetCount(sceneId ,selfId, npcId)
		if count >= 5 then
       Msg2Player(sceneId, selfId, "����������5�Ρ����ˡ����ı��䣬���������", 0, 2)
   		 Msg2Player(sceneId, selfId, "����������5�Ρ����ˡ����ı��䣬���������", 0, 3)         	      	
			return
		end
		
		
		
   if count >= 1 then  --���ǵ�һ����Ҫ��Ǯ
		if CostMoney(sceneId,selfId,3,x310322_g_CostGold) ~= -1 then
			Msg2Player(sceneId, selfId, "��ȡ����ɹ����۳�1���𿨣�", 0, 3)
			Msg2Player(sceneId, selfId, "��ȡ����ɹ����۳�1���𿨣�", 0, 2)
		else
			if CostMoney(sceneId,selfId,2,x310322_g_CostGold,318) ~= -1 then
				Msg2Player(sceneId, selfId, "��ȡ����ɹ����۳�1���ֽ�", 0, 3)
				Msg2Player(sceneId, selfId, "��ȡ����ɹ����۳�1���ֽ�", 0, 2)
			else
	    	Msg2Player(sceneId, selfId, "���ź�������ֽ�/�𿨲���1��", 0, 3)
				Msg2Player(sceneId, selfId, "���ź�������ֽ�/�𿨲���1��", 0, 2)
	    		return
			end
		end
	end
   local retmiss = AddQuest( sceneId, selfId, x310322_g_MissionId, x310322_g_ScriptId, 0, 0, 0, 1)
   if retmiss ==0 then
       Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
       return 0
   end
   	x310322_IncCountMD(sceneId ,selfId)     	
   	x310322_ProcQuestLogRefresh( sceneId, selfId, x310322_g_MissionId)	
    --BeginQuestEvent(sceneId)
   	--AddQuestText(sceneId,"�ɹ�������")
   	--EndQuestEvent(sceneId)
   	--DispatchQuestEventList(sceneId,selfId,NPCId)
   	GamePlayScriptLog(sceneId, selfId, 1641)
	
end

function x310322_ProcQuestAbandon(sceneId, selfId, MissionId)
    if IsHaveQuest(sceneId,selfId, x310322_g_MissionId) <= 0 then
        return 
    end
    DelQuest( sceneId, selfId, x310322_g_MissionId)
    Msg2Player(sceneId, selfId, format("������������:%s",x310322_g_MissionName), 0, 2)
    Msg2Player(sceneId, selfId, format("������������:%s",x310322_g_MissionName), 0, 3) 
   	--x310322_DecCountMD(sceneId ,selfId)   --����Ҳ�ƴ�
    
end


function x310322_GiveBonus(sceneId, selfId, NPCId)
end

function x310322_GiveExp( sceneId, selfId)
	local rate = random(1,100)
	if rate == 100 then
		local level = GetLevel(sceneId,selfId)
		local bonusExp = 64800 * level * 3
		AddExp(sceneId,selfId,bonusExp)
		local name = GetName(sceneId,selfId)
		if name == nil then
			name = "ErrorName"
		end

		Msg2Player( sceneId, selfId, "���ǳ����˵Ļ��3�����齱��"..bonusExp.."�㡣", 8, 2)
		return 1
	elseif rate >= 75 then
		local level = GetLevel(sceneId,selfId)
		local bonusExp = 64800 * level * 1.5
		AddExp(sceneId,selfId,bonusExp)
		Msg2Player( sceneId, selfId, "�����˵Ļ��1.5�����齱��"..bonusExp.."�㡣", 8, 2)
		return 1
	else
		local level = GetLevel(sceneId,selfId)
		local bonusExp = 64800 * level
		AddExp(sceneId,selfId,bonusExp)
		Msg2Player( sceneId, selfId, "����þ��齱��"..bonusExp.."�㡣", 8, 2)
		return 1
	end
	return 0
end
function x310322_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x310322_g_MissionId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"��û���������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif DelQuest(sceneId, selfId, x310322_g_MissionId) > 0 then
		x310322_GiveExp( sceneId, selfId)
    Msg2Player(sceneId, selfId, format("�����������:%s",x310322_g_MissionName), 0, 2)
    Msg2Player(sceneId, selfId, format("�����������:%s",x310322_g_MissionName), 0, 3) 
    	
    GamePlayScriptLog( sceneId, selfId, 1642)   
	
       -- AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x310322_g_MissionIdNext )	
end

 