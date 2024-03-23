

--MisDescBegin
x310164_g_ScriptId = 310164
--x310164_g_MissionIdPre ={67,69,70,71}
x310164_g_MissionId = 9315

x310164_g_MissionIdNext = -1
x310164_g_Name	={}
x310164_g_ExtTarget={{type=20,n=1,target="�ҵ�@npc_141540���ش��������⡣"},{type=20,n=1,target="�ҵ�@npc_141541���ش��������⡣"},{type=20,n=1,target="�ҵ�@npc_141542���ش��������⡣"},{type=20,n=1,target="�ҵ�@npc_141543���ش��������⡣"}}
x310164_g_MissionName="���ǡ��󶼵��ջ�"
x310164_g_MissionInfo="\t������ֵ�󶼵��ջ��ؿ�֮ʱ����λ������Ȥ�����ɲμӡ�\n\t��÷�������񡢾ա�4λ������Ů���ڴ󶼳��еĶ��������������Ϻ������ĸ���λ�߶����ش�����ǵ����⣬��������������ȡ������"  --��������
x310164_g_MissionTarget={{type=20,n=1,target="�ҵ�������Ů#G÷#W���ش��������⡣"},{type=20,n=1,target="�ҵ�������Ů#G��#W���ش��������⡣"},{type=20,n=1,target="�ҵ�������Ů#G��#W���ش��������⡣"},{type=20,n=1,target="�ҵ�������Ů#G��#W���ش��������⡣"}}		
x310164_g_MissionCompleted="\t��ϲ����������еĵ��ա�\n\t���ջ�ÿ�춼���Բμӣ����ң�ÿ�춼���Ų�ͬ������ȴ��������⿪��"					--�������npc˵���Ļ�
x310164_g_ContinueInfo="\t���#G÷#W��#G��#W��#G��#W��#G��#W4λ������Ů����������"
x310164_g_MissionHelp =	"ÿ����¶�һ�����գ������5����֣����´�Ҳ����1����֡����������λ��Ů�ĵ���֮���һ�������õĻ��ָ�������Ľ�����"

x310164_g_BonusItemId	=	11990117    --���֎�
x310164_g_LevelLess = 40
x310164_g_NpcGUID ={{ guid = 139133, name = "�̵³�"} }
--MisDescEnd
x310164_g_TianfuItems				= {11010100,11010101,11010102}
--**********************************

x310164_g_MissionNpcTab =	{ 
								{ QuestIndex = 1, guid = 141506, name = "÷" },    	--141506		÷ 
								{ QuestIndex = 2, guid = 141507, name = "��" },  	--141507		�� 
								{ QuestIndex = 3, guid = 141508, name = "��" },   	--141508		�� 
								{ QuestIndex = 4, guid = 141509, name = "��" }   	--141509		�� 
							}
x310164_g_MinLevel	= 10
x310164_g_MaxLevel  = 160

function x310164_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	local level = GetLevel(sceneId, selfId)
	
	if IsQuestHaveDone(sceneId, selfId, x310164_g_MissionId) > 0 then
		return 
	end

	if level <40 then
		return
	end
	if IsHaveQuest(sceneId,selfId, x310164_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x310164_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x310164_g_MissionId, state, -1 )
	end
end

function x310164_DispatchMissionInfo( sceneId, selfId, NPCId )
	--BeginQuestEvent( sceneId)

    local exp = x310164_GetGiveExp(sceneId, selfId)
    
   	AddQuestExpBonus( sceneId, exp)
   
   	local money,type = x310164_GetGiveMoney( sceneId, selfId)

   	if type == 0 then
        AddQuestMoneyBonus2( sceneId, money)
   	else
		AddQuestMoneyBonus1( sceneId, money)
    end
    local score = x310164_GetScore( sceneId, selfId)
    AddQuestItemBonus(sceneId, x310164_g_BonusItemId, score)
    	
    --EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x310164_g_ScriptId, x310164_g_MissionId)
end

function x310164_IsAlreadySubmit( sceneId, selfId )  --�����Ƿ��Ѿ���������
	local nDate   = GetQuestData(sceneId,selfId,MD_DENGMI_DATE[1], MD_DENGMI_DATE[2], MD_DENGMI_DATE[3] )
	local nCurDay = GetDayOfYear()
	if nCurDay == nDate then
		return 1
	end
	return 0
end

----------------------------------------------------------------------------------------------
--�������ʱ���Ƿ���Ч
----------------------------------------------------------------------------------------------
function x310164_IsStartTimeValid()
	local h,m,s = GetHourMinSec()	
	
	local cur  = h*60  + m
	local from = 19*60 + 30
	local to   = 24*60 + 00
	if cur < from or cur > to then
		return 0
	end
	return 1

end


----------------------------------------------------------------------------------------------
--���ô�NPC���
----------------------------------------------------------------------------------------------
function x310164_ResetDengmiMD( sceneId ,selfId)
	SetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3],0)
	SetQuestData(sceneId,selfId,MD_DENGMI_NPC1[1],MD_DENGMI_NPC1[2],MD_DENGMI_NPC1[3],0)
	SetQuestData(sceneId,selfId,MD_DENGMI_NPC2[1],MD_DENGMI_NPC2[2],MD_DENGMI_NPC2[3],0)
	SetQuestData(sceneId,selfId,MD_DENGMI_NPC3[1],MD_DENGMI_NPC3[2],MD_DENGMI_NPC3[3],0)
	SetQuestData(sceneId,selfId,MD_DENGMI_NPC4[1],MD_DENGMI_NPC4[2],MD_DENGMI_NPC4[3],0)
	
end

function x310164_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x310164_g_MissionId) > 0 then
		return
	end
	
	
	
	if IsHaveQuest(sceneId,selfId, x310164_g_MissionId) > 0 then
        if x310164_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x310164_g_MissionName)
            AddQuestText(sceneId,x310164_g_ContinueInfo)
            EndQuestEvent()
            DispatchQuestEventList(sceneId, selfId, NPCId, x310164_g_ScriptId, x310164_g_MissionId);
        else
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x310164_g_MissionName)
            AddQuestText(sceneId,x310164_g_MissionCompleted)
            AddQuestText(sceneId," ")
            x310164_DispatchMissionInfo( sceneId, selfId, NPCId )
            EndQuestEvent()
            DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x310164_g_ScriptId, x310164_g_MissionId);
        end
        return
    end   
    
    if x310164_IsAlreadySubmit(sceneId,selfId) == 1 then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"#Y"..x310164_g_MissionName)
        AddQuestText(sceneId,"ÿ��ֻ�ܲ���һ�Σ�����������")
        EndQuestEvent()
        DispatchQuestEventList(sceneId, selfId, NPCId, x310164_g_ScriptId, x310164_g_MissionId);
        return
	end
	
	if x310164_IsStartTimeValid() == 0 then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"#Y"..x310164_g_MissionName)
        AddQuestText(sceneId,"ֻ����19��30 ~  24��00 ������")
        EndQuestEvent()
        DispatchQuestEventList(sceneId, selfId, NPCId, x310164_g_ScriptId, x310164_g_MissionId);
        return
	end
	
   if x310164_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
   			local level  = GetLevel(sceneId, selfId)
   			local 	 xp  = level * 350
   			local nmoney = level * 0.3
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"#Y"..x310164_g_MissionName)
        AddQuestText(sceneId,x310164_g_MissionInfo.."\n\t#Gÿ����¶Ե�����Ů�ĵ��գ������5����֣��´��˻��1����֡����������λ��Ů�ĵ��գ��һ������Ļ��ָ�������Ľ�����#W" )
        AddQuestText( sceneId,"#Y����Ŀ�꣺")
        for i, item in x310164_g_ExtTarget do
            AddQuestText( sceneId,item.target)
        end 
        --AddQuestText(sceneId,"\n#GС��ʾ:#W")
        --if x310164_g_MissionHelp ~= "" then
        --    AddQuestText(sceneId,"\n#GС��ʾ:#W")
        --    AddQuestText(sceneId,"\nÿ����¶Ե�����Ů�ĵ��գ������5����֣���ʹ�´���Ҳ����1����֡����������λ��Ů�ĵ��գ��һ������Ļ��ָ�������Ľ�����" )
        --end
      --x310164_DispatchMissionInfo( sceneId, selfId, NPCId )
      	
				AddQuestText(sceneId,format("\n#Y������#W��\n����ֵ������*%d��\n���ң�%d��",xp,nmoney))
        EndQuestEvent()
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x310164_g_ScriptId, x310164_g_MissionId);
        
         SetQuestData(sceneId,selfId,MD_DENGMI_NO1[1],MD_DENGMI_NO1[2],MD_DENGMI_NO1[3],0)
		SetQuestData(sceneId,selfId,MD_DENGMI_NO2[1],MD_DENGMI_NO2[2],MD_DENGMI_NO2[3],0)
		SetQuestData(sceneId,selfId,MD_DENGMI_NO3[1],MD_DENGMI_NO3[2],MD_DENGMI_NO3[3],0)
		SetQuestData(sceneId,selfId,MD_DENGMI_NO4[1],MD_DENGMI_NO4[2],MD_DENGMI_NO4[3],0)
    end
end

function x310164_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

function x310164_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x310164_g_MissionId)
	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
	    return 1
	else
	    return 0
	end
end

function x310164_GetNPCIndex( sceneId, npcId) 
	 for i, item in x310164_g_MissionNpcTab do
        if item.guid == npcId then
            return i
        end
    end
    return nil
end

function x310164_OnMissionCompleted( sceneId, selfId, npcId) 
	local score = GetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3])
	
end


function x310164_OnMissionStep( sceneId, selfId, npcId)   

	if npcId==nil then
		
		return
	end
	if IsHaveQuestNM( sceneId, selfId, x310164_g_MissionId ) == 0 then
		return
	end
	local index = x310164_GetNPCIndex(sceneId, npcId)
	if index == nil then
		return
	end
	local misIndex = GetQuestIndexByID(sceneId,selfId,x310164_g_MissionId)  
	
	SetQuestByIndex(sceneId,selfId,misIndex,index ,1)

	local n1 = GetQuestParam( sceneId, selfId, misIndex, x310164_g_MissionNpcTab[1].QuestIndex )	
	local n2 = GetQuestParam( sceneId, selfId, misIndex, x310164_g_MissionNpcTab[2].QuestIndex )
	local n3 = GetQuestParam( sceneId, selfId, misIndex, x310164_g_MissionNpcTab[3].QuestIndex )                                                
	local n4 = GetQuestParam( sceneId, selfId, misIndex, x310164_g_MissionNpcTab[4].QuestIndex ) 
	
	x310164_ProcQuestLogRefresh( sceneId, selfId, x310164_g_MissionId)
	
	if n1==1 and n2==1 and n3==1 and n4==1 then
		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
		x310164_OnMissionCompleted( sceneId, selfId, npcId) 
	end
	
	
	 
end


function x310164_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
	if IsQuestHaveDone(sceneId, selfId, x310164_g_MissionId) > 0 then
        return 
    end
    if IsQuestFullNM(sceneId,selfId)==1 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"�ɽ�������������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 
    end

    --���ǰ������
    local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x310164_g_MissionId  )
    if FrontMissiontId1 ~= -1 then
        if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
            return 0
        end
    end
    if FrontMissiontId2 ~= -1 then
        if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
            return 0
        end
    end
    if FrontMissiontId3 ~= -1 then
        if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
            return 0
        end
    end
    
    --��������Ƿ�ӹ���
    if x310164_IsAlreadySubmit( sceneId, selfId ) == 1 then
    	BeginQuestEvent(sceneId)
    	AddQuestText(sceneId,"�����Ѿ��ӹ�������!")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 
    end

    if x310164_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        local retmiss = AddQuest( sceneId, selfId, x310164_g_MissionId, x310164_g_ScriptId, 0, 0, 0, 1)
        if retmiss ==0 then
            Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
            return 0
        else
        	x310164_ResetDengmiMD( sceneId ,selfId)
        	x310164_SetAcceptDate( sceneId,selfId )  --�����������
			SetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3], 0)        	
            local misIndex = GetQuestIndexByID(sceneId,selfId,x310164_g_MissionId)                                                  
            x310164_Msg2toplayer( sceneId, selfId,0)
            
            for i, item in x310164_g_MissionNpcTab do
        		 SetQuestByIndex(sceneId,selfId,misIndex,item.QuestIndex,0)
    		end
            x310164_ProcQuestLogRefresh( sceneId, selfId, x310164_g_MissionId)
        end
    end                                                                    
end

function x310164_ProcQuestAbandon(sceneId, selfId, MissionId)
    if IsHaveQuest(sceneId,selfId, x310164_g_MissionId) <= 0 then
        return 
    end
    DelQuest( sceneId, selfId, x310164_g_MissionId)
    x310164_SetDateMD( sceneId,selfId )	--�����ύ��ʱ��
    x310164_Msg2toplayer( sceneId, selfId, 1)
end

function x310164_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
		AddItem( sceneId, x310164_g_BonusItemId, x310164_GetScore( sceneId, selfId) )
    local ret = EndAddItem(sceneId,selfId)
    if ret <= 0 then
        if result == 1 then
            result = 0
        end
    end
	return result
end

----------------------------------------------------------------------------------------------
--���������������
----------------------------------------------------------------------------------------------
function x310164_SetAcceptDate( sceneId,selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310164_g_MissionId)
	local nCurDay = GetDayOfYear()
	SetQuestByIndex( sceneId, selfId, misIndex, 6, nCurDay)
end

----------------------------------------------------------------------------------------------
--��鲢����������
----------------------------------------------------------------------------------------------
function x310164_SetDateMD( sceneId,selfId )
	local nCurDay = GetDayOfYear()
	SetQuestData(sceneId,selfId,MD_DENGMI_DATE[1],MD_DENGMI_DATE[2],MD_DENGMI_DATE[3],nCurDay)


end


function x310164_AddTianfuItem( sceneId, selfId)
	local level = GetLevel( sceneId, selfId)
	if level >= 80 then
		if random( 1, 100) <= 22 then
			local nIndex = random(1,3)
			BeginAddItem( sceneId)
	        AddItem( sceneId, x310164_g_TianfuItems[nIndex], 1)
	        if EndAddItem( sceneId, selfId) <= 0 then
	            Msg2Player( sceneId, selfId, "������ı����������޷�����츳���߽�����", 8, 2)
	        else
	            AddItemListToPlayer( sceneId, selfId)
	        end
		end
	end
end

function x310164_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

	if x310164_IsAlreadySubmit(sceneId,selfId) == 1 then
        return
	end

	if IsHaveQuest(sceneId,selfId, x310164_g_MissionId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"��û���������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x310164_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"��û�дﵽ���������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x310164_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"�����ռ䲻�㣬�������������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif DelQuest(sceneId, selfId, x310164_g_MissionId) > 0 then
	CallScriptFunction( 256224, "Finishdengmi", sceneId, selfId)	
		x310164_SetDateMD( sceneId,selfId )	--�����ύ��ʱ��
		
		
       
        QuestCom(sceneId, selfId, x310164_g_MissionId)
        x310164_GiveExp( sceneId, selfId)
        x310164_Msg2toplayer( sceneId, selfId,2)
        x310164_GiveMoney( sceneId, selfId)
        local score = x310164_GetScore( sceneId, selfId)
        BeginAddItem(sceneId)
          AddItem( sceneId, x310164_g_BonusItemId, score)
          
        local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
			Msg2Player(sceneId, selfId, "�������"..score.."��#{_ITEM11990117}��", 0, 2)
        end
        
       x310164_AddTianfuItem( sceneId, selfId)
	
       -- AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x310164_g_MissionIdNext )	
end

function x310164_GetScore( sceneId, selfId)
	return GetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3])
end

function x310164_GetGiveExp( sceneId, selfId)
	local score = GetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3])
	local level = GetLevel(sceneId, selfId)
	local exp = level*350*score
	return exp
end

function x310164_GiveExp( sceneId, selfId)
	local exp = x310164_GetGiveExp( sceneId, selfId)
	AddExp(sceneId, selfId, exp)
end

function  x310164_GetGiveMoney( sceneId, selfId)
 	--������
	local level = GetLevel(sceneId, selfId)
	local score = x310164_GetScore(sceneId, selfId)
	local bonusMoney = level*15*score
	local buff 	=	9011
	local buff1 =	9013
	local buff2 =	9012
	if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1  or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
		return bonusMoney,0
	end
	return bonusMoney,1
	
end

function  x310164_GiveMoney( sceneId, selfId)
 	--������
	local level = GetLevel(sceneId, selfId)
	local score = x310164_GetScore(sceneId, selfId)
	local bonusMoney = level*15*score
	local buff 	=	9011
	local buff1 =	9013
	local buff2 =	9012
	if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1  or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
		AddMoney(sceneId,selfId,0,bonusMoney)
	else
		AddMoney(sceneId,selfId,1,bonusMoney)
	end
	
end
 
function x310164_Msg2toplayer( sceneId, selfId,type)
    if type == 0 then
        Msg2Player(sceneId, selfId, "������������"..x310164_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "������������"..x310164_g_MissionName.."��", 0, 3)
    elseif type == 1 then
        Msg2Player(sceneId, selfId, "������������"..x310164_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "������������"..x310164_g_MissionName.."��", 0, 3)
    elseif type == 2 then
        Msg2Player(sceneId, selfId, "�����������"..x310164_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "�����������"..x310164_g_MissionName.."��", 0, 3)
        if x310164_GetGiveExp( sceneId, selfId) > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x310164_GetGiveExp( sceneId, selfId).."��#Y�Ľ���", 0, 2)
        end
        local money,type = x310164_GetGiveMoney( sceneId, selfId)
        if money > 0 then
        	if type == 1 then
             	Msg2Player(sceneId, selfId, "#Y���#R����"..money.."��#Y�Ľ���", 0, 2)
            else
            	Msg2Player(sceneId, selfId, "#Y���#R����"..money.."��#Y�Ľ���", 0, 2)
            end
        end
    end
    
end

function x310164_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

function x310164_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x310164_ProcTiming(sceneId, selfId, ScriptId, MissionId)
    CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
end

function x310164_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x310164_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end

function x310164_LevelUp( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x310164_g_MissionId) < 1 then
        return
    end


end

function x310164_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x310164_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
    if IsHaveQuest(sceneId,selfId, x310164_g_MissionId) > 0 then
        local state = GetQuestStateNM(sceneId,selfId,npcId,x310164_g_MissionId)
        AddQuestTextNM( sceneId, selfId, npcId, x310164_g_MissionId, state, -1 )
    end
end

function x310164_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x310164_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x310164_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x310164_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x310164_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x310164_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x310164_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
    
    local ns1 = GetQuestParam( sceneId, selfId, misIndex, x310164_g_MissionNpcTab[1].QuestIndex)
    local ns2 = GetQuestParam( sceneId, selfId, misIndex, x310164_g_MissionNpcTab[2].QuestIndex)
    local ns3 = GetQuestParam( sceneId, selfId, misIndex, x310164_g_MissionNpcTab[3].QuestIndex)
    local ns4 = GetQuestParam( sceneId, selfId, misIndex, x310164_g_MissionNpcTab[4].QuestIndex)
    
	local strTarget = format( "\n  �ر�@npc_%d", 139133)
    if ns1== 1 and ns2 == 1 and ns3 == 1 and ns4 == 1 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    else
        if ns1== 0 then
            strTarget = "\n#W  �³�@npc_141540�ĵ���(0/1)\n"
        else
            strTarget = "\n#G  �³�@npc_141540�ĵ���(1/1)\n"
        end
        if ns2 == 0 then
            strTarget = strTarget.."#W  �³�@npc_141541�ĵ���(0/1)\n"
        else
            strTarget = strTarget.."#G  �³�@npc_141541�ĵ���(1/1)\n"
        end
        if ns3 == 0 then
            strTarget = strTarget.."#W  �³�@npc_141542�ĵ���(0/1)\n"
        else
            strTarget = strTarget.."#G  �³�@npc_141542�ĵ���(1/1)\n"
        end
        
        if ns4 == 0 then
            strTarget = strTarget.."#W  �³�@npc_141543�ĵ���(0/1)"
        else
            strTarget = strTarget.."#G  �³�@npc_141543�ĵ���(1/1)"
        end
    end
    
    local score = x310164_GetScore(sceneId, selfId)
    
    strTarget = "  ��ǰ���֣�#G"..score.."#W"..strTarget
	BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- ����
                                x310164_g_MissionName,          -- ��������
                                strTarget,
                                "",                             --����NPC
                                "�ڴ��ڵ�#G���������������Ϻ�����#W�ĸ��ص��ҵ�#G�߶�#W�ġ�÷�������񡢾ա�4λ������Ů���ش����ǵ����⡣",
                                x310164_g_MissionInfo,
                                ""
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

