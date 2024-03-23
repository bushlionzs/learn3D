-- �ű���
x350013_g_ScriptId          = 350013
-- ���
x350013_g_Name              = "����콱"
-- ��ʾ��ȡʱ��
x350013_g_strErrorTime      = "����8��10�պ�8��11�յ�20��00��20��30��ȡ"
x350013_g_shuoming 		      = "\tΪ���ù������ڷ���ڼ��г���������������ǵĸ��־����淨�����ǽ������������ѷ��ź�����⡰���á������˶��У����߾��У�8��10�ա�8��11��ÿ��20:00��20:30��ʱ���ţ��Ͽ�������ȡ�ɣ����ڲ���Ӵ��\n\t\n\t8��10�տɻ�ý�#R50��#W��\n\t8��11�տɻ�ý�#R100��#W��"

x350013_g_MD1 =MD_LINGJIANG_TIME1
x350013_g_MD2 =MD_LINGJIANG_TIME2
x350013_g_FeastId	  = 2


function x350013_IsFeastActive()
	
	if x350013_g_FeastId ~= MD_CURRENT_FEAST_ID then
				return 0
	end
	return 1
end

-- ���NPC�ص������NPC���ã���������ӷ���ͽ𿨰�ť��
function x350013_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
	
	if x350013_IsFeastActive() ~= 1	then
		return  
	end 
	
	local day = GetDayOfYear()
	if day < 221 or day > 222 then
		return
	end
	 
    AddQuestNumText( sceneId, x350013_g_ScriptId, x350013_g_Name, 3, 1)
end

-- ��ҵ��NPC�Ի�ѡ�ť��Ļص�������󣬸���x350013_GetMoney( sceneId, selfId)���ص�ֵȷ���Ƿ�����콱���棬��Ϊ0���ܽ��룩
function x350013_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
	if x350013_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "�û�п���", 8, 3)
        return
    end

        BeginQuestEvent( sceneId)  --1
            AddQuestText( sceneId, "#Y"..x350013_g_Name)  --2
            AddQuestText( sceneId, x350013_g_shuoming )
--         AddQuestMoneyBonus3( sceneId, money)
        EndQuestEvent() --3�̶��ĸ�ʽ
        DispatchQuestInfo( sceneId, selfId, NPCId, x350013_g_ScriptId, -1) 
end


-- ��ҵ��ȷ�������ȷ����Ǯ��ͬʱ��¼MD��
function x350013_ProcAcceptCheck( sceneId, selfId, NPCId)
	if x350013_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "�û�п���", 8, 3)
        return
        end
	CallScriptFunction(888894,"Feast_SetCurrentId",sceneId,selfId,x350013_g_FeastId)

		local money = x350013_GetMoney( sceneId, selfId)

    if money ~= 0 then
        AddMoney( sceneId, selfId, 3, money)
    else
    	return 0
    end

    local y, m, d = GetYearMonthDay()
    if d == 10 then
        SetQuestData( sceneId, selfId, x350013_g_MD1[ 1], x350013_g_MD1[ 2], x350013_g_MD1[ 3], 1)
    else
        SetQuestData( sceneId, selfId, x350013_g_MD2[ 1], x350013_g_MD2[ 2], x350013_g_MD2[ 3], 1)
    end

    return 1
end


function x350013_ProcAccept( sceneId, selfId, NPCId)
end


function x350013_GetMoney( sceneId, selfId)
	local y, m, d = GetYearMonthDay()
        local minute = GetMinOfDay()

        if m ~= 8 then
        	Msg2Player( sceneId, selfId, x350013_g_strErrorTime, 8, 3)
       		return 0	
        end

   	if d ~= 10 and d ~= 11 then
       		Msg2Player( sceneId, selfId, x350013_g_strErrorTime, 8, 3)
        	return 0
        end

        if minute < 1200 or minute > 1230 then
       		Msg2Player( sceneId, selfId,"ֻ����20��00��20��30��ȡ�𿨽���", 8, 3)
        	return 0
        end
 

        if d == 10 then
        	if GetQuestData( sceneId, selfId, x350013_g_MD1[ 1], x350013_g_MD1[ 2], x350013_g_MD1[ 3] ) == 1 then
            		Msg2Player( sceneId, selfId, "����Ľ������Ѿ���ȡ����", 8, 3)
            	return 0
        else
            return 50000
        end
    end
    if d == 11 then
        if GetQuestData( sceneId, selfId, x350013_g_MD2[ 1], x350013_g_MD2[ 2], x350013_g_MD2[ 3] ) == 1 then
            Msg2Player( sceneId, selfId, "����Ľ������Ѿ���ȡ����", 8, 3)
            return 0
        else
            return 100000
        end
    end

end





















