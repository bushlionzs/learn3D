--�ű���
x310187_g_ScriptId = 310187

function x310187_OnTimerDoingStart( SceneId, actId, Param1, Param2, Param3, Param4, Param5 )

	if GetWeek() ~= 0 then
		return
	end
	
	if SceneId ~= 0 then
		return
	end
	
	if WULONGCIDIAN_STEPIN_COUNT  <= 0 then
		return
	end
	
	local msg = ""
	local count =0
	local msg1=""
	local msg2=""
	local msg3=""

	for i=1, WULONGCIDIAN_STEPIN_COUNT do
		count = count +1
		if count<=10 then
			msg1 = msg1.."#Y "..WULONGCIDIAN_STEPIN_NAME[i]
		elseif count<=20 then
			msg2 = msg2.."#Y "..WULONGCIDIAN_STEPIN_NAME[i]
		else
			msg3 = msg3.."#Y "..WULONGCIDIAN_STEPIN_NAME[i]
		end
		SendSystemMail(SceneId, WULONGCIDIAN_STEPIN_NAME[i], "��ϲ����������ǵ�����ֲ����ʸ���������16��30-17��00֮��ǰ�����ҵ������ܹܺ��ܹܲμ����վ�����" )
		
	end
	if count<=10 then
		msg = "#G��ϲ"
		msg = msg..msg1.."#G��������ǵ�����ֲ����ʸ���������16��30-17��00֮��ǰ�����ҵ������ܹܺ��ܹܲμ����վ�����"
	LuaAllScenceM2Wrold(SceneId, msg, CHAT_LEFTDOWN, 0)
		return
	end
	
	if count<=20 then
		msg = "#G��ϲ"
		msg = msg..msg1.."#G��������ǵ�����ֲ����ʸ���������16��30-17��00֮��ǰ�����ҵ������ܹܺ��ܹܲμ����վ�����"
		LuaAllScenceM2Wrold(SceneId, msg, CHAT_LEFTDOWN, 0)
	 msg = "#G��ϲ"
	 msg = msg..msg2.."#G��������ǵ�����ֲ����ʸ���������16��30-17��00֮��ǰ�����ҵ������ܹܺ��ܹܲμ����վ�����"
	LuaAllScenceM2Wrold(SceneId, msg, CHAT_LEFTDOWN, 0)
		return
	end
	
	 msg = "#G��ϲ"
	msg = msg..msg1.."#G��������ǵ�����ֲ����ʸ���������16��30-17��00֮��ǰ�����ҵ������ܹܺ��ܹܲμ����վ�����"
	LuaAllScenceM2Wrold(SceneId, msg, CHAT_LEFTDOWN, 0)
	msg = "#G��ϲ"
	msg = msg..msg2.."#G��������ǵ�����ֲ����ʸ���������16��30-17��00֮��ǰ�����ҵ������ܹܺ��ܹܲμ����վ�����"
	LuaAllScenceM2Wrold(SceneId, msg, CHAT_LEFTDOWN, 0)
	msg = "#G��ϲ"
	msg = msg..msg3.."#G��������ǵ�����ֲ����ʸ���������16��30-17��00֮��ǰ�����ҵ������ܹܺ��ܹܲμ����վ�����"
	LuaAllScenceM2Wrold(SceneId, msg, CHAT_LEFTDOWN, 0)
	
end
