-- �ű���
x350014_g_ScriptId          = 350014
-- ���
x350014_g_Name              = "�ڲ��콱"
-- ��ʾ��ȡʱ��
x350014_g_strErrorTime      = "����9��10�գ�9��11�գ�9��12�յ�20��00��20��30��ȡ"
x350014_g_shuoming 		      = "\tΪ���ù��������ڲ��ڼ��г���������������ǵĸ��־����淨�����ǽ������������ѷ��ź�����⡰���á������˶��У����߾��У�9��10�ա�9��11�ա�9��12��ÿ��20:00��20:30��ʱ���ţ��Ͽ�������ȡ�ɣ����ڲ���Ӵ��\n\t\n\t9��10�տɻ������#R100��#W��\n\t9��11�տɻ������#R200��#W��\n\t9��12�տɻ������#R300��#W��"

x350014_g_MD1 =MD_NEICE_LINGJIANG_TIME1
x350014_g_MD2 =MD_NEICE_LINGJIANG_TIME2
x350014_g_MD3 =MD_NEICE_LINGJIANG_TIME3
x350014_g_FeastId	  = 3


function x350014_IsFeastActive()
	
	if x350014_g_FeastId ~= MD_CURRENT_FEAST_ID then
				return 0
	end
	return 1
end

-- ���NPC�ص������NPC���ã���������ӷ���ͽ𿨰�ť��
function x350014_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
	
	if x350014_IsFeastActive() ~= 1	then
		return  
	end 
	
	local day = GetDayOfYear()
	if day < 252 or day > 254 then
		return
	end
	 
    AddQuestNumText( sceneId, x350014_g_ScriptId, x350014_g_Name, 3, 1)
end

-- ��ҵ��NPC�Ի�ѡ�ť��Ļص�������󣬸���x350014_GetMoney( sceneId, selfId)���ص�ֵȷ���Ƿ�����콱���棬��Ϊ0���ܽ��룩
function x350014_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
	if x350014_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "�û�п���", 8, 3)
        return
    end

        BeginQuestEvent( sceneId)  --1
            AddQuestText( sceneId, "#Y"..x350014_g_Name)  --2
            AddQuestText( sceneId, x350014_g_shuoming )
--         AddQuestMoneyBonus3( sceneId, money)
        EndQuestEvent() --3�̶��ĸ�ʽ
        DispatchQuestInfo( sceneId, selfId, NPCId, x350014_g_ScriptId, -1) 
end


-- ��ҵ��ȷ�������ȷ����Ǯ��ͬʱ��¼MD��
function x350014_ProcAcceptCheck( sceneId, selfId, NPCId)
	if x350014_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "�û�п���", 8, 3)
        return
        end
	CallScriptFunction(888894,"Feast_SetCurrentId",sceneId,selfId,x350014_g_FeastId)

		local money = x350014_GetMoney( sceneId, selfId)

    if money ~= 0 then
        AddMoney( sceneId, selfId, 1, money)
    else
    	return 0
    end

    local y, m, d = GetYearMonthDay()
    if d == 10 then
        SetQuestData( sceneId, selfId, x350014_g_MD1[ 1], x350014_g_MD1[ 2], x350014_g_MD1[ 3], 1)
    elseif d == 11 then
        SetQuestData( sceneId, selfId, x350014_g_MD2[ 1], x350014_g_MD2[ 2], x350014_g_MD2[ 3], 1)
    elseif d ==12 then
    	SetQuestData( sceneId, selfId, x350014_g_MD3[ 1], x350014_g_MD3[ 2], x350014_g_MD3[ 3], 1)
    end

    return 1
end


function x350014_ProcAccept( sceneId, selfId, NPCId)
end


function x350014_GetMoney( sceneId, selfId)
	local y, m, d = GetYearMonthDay()
        local minute = GetMinOfDay()

        if m ~= 9 then
        	Msg2Player( sceneId, selfId, x350014_g_strErrorTime, 8, 3)
       		return 0	
        end

   	if d ~= 10 and d ~= 11 and d ~= 12 then
       		Msg2Player( sceneId, selfId, x350014_g_strErrorTime, 8, 3)
        	return 0
        end

        if minute < 1200 or minute > 1230 then
       		Msg2Player( sceneId, selfId,"ֻ����20��00��20��30��ȡ��������", 8, 3)
        	return 0
        end
 

        if d == 10 then
        	if GetQuestData( sceneId, selfId, x350014_g_MD1[ 1], x350014_g_MD1[ 2], x350014_g_MD1[ 3] ) == 1 then
            		Msg2Player( sceneId, selfId, "����Ľ������Ѿ���ȡ����", 8, 3)
            	return 0
        else
            return 100000
        end
    end
    if d == 11 then
        if GetQuestData( sceneId, selfId, x350014_g_MD2[ 1], x350014_g_MD2[ 2], x350014_g_MD2[ 3] ) == 1 then
            Msg2Player( sceneId, selfId, "����Ľ������Ѿ���ȡ����", 8, 3)
            return 0
        else
            return 200000
        end
    end
    if d == 12 then
        if GetQuestData( sceneId, selfId, x350014_g_MD3[ 1], x350014_g_MD3[ 2], x350014_g_MD3[ 3] ) == 1 then
            Msg2Player( sceneId, selfId, "����Ľ������Ѿ���ȡ����", 8, 3)
            return 0
        else
            return 300000
        end
    end
end





















