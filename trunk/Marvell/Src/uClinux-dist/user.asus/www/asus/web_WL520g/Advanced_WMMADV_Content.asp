<head>
<title>WL520g Web Manager</title>
<meta http-equiv="Content-Type" content="text/html; charset=euc-kr">
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link rel="stylesheet" type="text/css" href="style.css" media="screen"></link>
<script language="JavaScript" type="text/javascript" src="overlib.js"></script>
<script language="JavaScript" type="text/javascript" src="general.js"></script>
</head>  
<div id="overDiv" style="position:absolute; visibility:hidden; z-index:1000;"></div>    
<body onLoad="load_body()" onunLoad="return unload_body();">
<form method="GET" name="form" action="apply.cgi">
<!-- Table for the conntent page -->	    
<table width="666" border="0" cellpadding="0" cellspacing="0">     	      
    	
<input type="hidden" name="current_page" value="Advanced_WMMADV_Content.asp"><input type="hidden" name="next_page" value="Advanced_WMMADV_Content.asp"><input type="hidden" name="next_host" value=""><input type="hidden" name="sid_list" value="WLANConfig11a;WLANConfig11b;"><input type="hidden" name="group_id" value=""><input type="hidden" name="modified" value="0"><input type="hidden" name="action_mode" value=""><input type="hidden" name="first_time" value=""><input type="hidden" name="action_script" value="">
<tr>
<td>
<table width="666" border="1" cellpadding="0" cellspacing="0" bordercolor="E0E0E0">
<tr class="content_header_tr">
<td class="content_header_td_title" colspan="2">무선 - 고급</td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('Please input string as CWmin CWmax AIFSN TXOP(b) TXOP(a,g) Admin Forced.', LEFT);" onMouseOut="return nd();">WMM Background Parameters for AP:
           </td><td class="content_input_td"><input type="text" maxlength="256" class="content_input_fd" size="32" name="wl_wme_ap_bk" value="<% nvram_get_x("WLANConfig11b","wl_wme_ap_bk"); %>" onKeyPress="return is_string(this)" onBlur="validate_string(this)"></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('Please input string as CWmin CWmax AIFSN TXOP(b) TXOP(a,g) Admin Forced.', LEFT);" onMouseOut="return nd();">WMM Best-Effect Parameters for AP:
           </td><td class="content_input_td"><input type="text" maxlength="256" class="content_input_fd" size="32" name="wl_wme_ap_be" value="<% nvram_get_x("WLANConfig11b","wl_wme_ap_be"); %>" onKeyPress="return is_string(this)" onBlur="validate_string(this)"></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('Please input string as CWmin CWmax AIFSN TXOP(b) TXOP(a,g) Admin Forced.', LEFT);" onMouseOut="return nd();">WMM Video Parameters for AP:
           </td><td class="content_input_td"><input type="text" maxlength="256" class="content_input_fd" size="32" name="wl_wme_ap_vi" value="<% nvram_get_x("WLANConfig11b","wl_wme_ap_vi"); %>" onKeyPress="return is_string(this)" onBlur="validate_string(this)"></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('Please input string as CWmin CWmax AIFSN TXOP(b) TXOP(a,g) Admin Forced.', LEFT);" onMouseOut="return nd();">WMM Voice Parameters for AP:
           </td><td class="content_input_td"><input type="text" maxlength="256" class="content_input_fd" size="32" name="wl_wme_ap_vo" value="<% nvram_get_x("WLANConfig11b","wl_wme_ap_vo"); %>" onKeyPress="return is_string(this)" onBlur="validate_string(this)"></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('Please input string as CWmin CWmax AIFSN TXOP(b) TXOP(a,g) Admin Forced.', LEFT);" onMouseOut="return nd();">WMM Background Parameters for STA:
           </td><td class="content_input_td"><input type="text" maxlength="256" class="content_input_fd" size="32" name="wl_wme_sta_bk" value="<% nvram_get_x("WLANConfig11b","wl_wme_sta_bk"); %>" onKeyPress="return is_string(this)" onBlur="validate_string(this)"></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('Please input string as CWmin CWmax AIFSN TXOP(b) TXOP(a,g) Admin Forced.', LEFT);" onMouseOut="return nd();">WMM Best-Effect Parameters for STA:
           </td><td class="content_input_td"><input type="text" maxlength="256" class="content_input_fd" size="32" name="wl_wme_sta_be" value="<% nvram_get_x("WLANConfig11b","wl_wme_sta_be"); %>" onKeyPress="return is_string(this)" onBlur="validate_string(this)"></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('Please input string as CWmin CWmax AIFSN TXOP(b) TXOP(a,g) Admin Forced.', LEFT);" onMouseOut="return nd();">WMM Video Parameters for STA:
           </td><td class="content_input_td"><input type="text" maxlength="256" class="content_input_fd" size="32" name="wl_wme_sta_vi" value="<% nvram_get_x("WLANConfig11b","wl_wme_sta_vi"); %>" onKeyPress="return is_string(this)" onBlur="validate_string(this)"></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('Please input string as CWmin CWmax AIFSN TXOP(b) TXOP(a,g) Admin Forced.', LEFT);" onMouseOut="return nd();">WMM Voice Parameters for STA:
           </td><td class="content_input_td"><input type="text" maxlength="256" class="content_input_fd" size="32" name="wl_wme_sta_vo" value="<% nvram_get_x("WLANConfig11b","wl_wme_sta_vo"); %>" onKeyPress="return is_string(this)" onBlur="validate_string(this)"></td>
</tr>
<tr>
<td class="content_header_td">Enable WPA2 Preauthentication?
           </td><td class="content_input_td"><input type="radio" value="1" name="wl_preauth" class="content_input_fd" onClick="return change_common_radio(this, 'WLANConfig11b', 'wl_preauth', '1')" <% nvram_match_x("WLANConfig11b","wl_preauth", "1", "checked"); %>>Yes</input><input type="radio" value="0" name="wl_preauth" class="content_input_fd" onClick="return change_common_radio(this, 'WLANConfig11b', 'wl_preauth', '0')" <% nvram_match_x("WLANConfig11b","wl_preauth", "0", "checked"); %>>No</input></td>
</tr>
<tr>
<td class="content_header_td">Network Re-authentication Innterval:
           </td><td class="content_input_td"><input type="text" maxlength="256" class="content_input_fd" size="32" name="wl_net_reauth" value="<% nvram_get_x("WLANConfig11b","wl_net_reauth"); %>" onKeyPress="return is_string(this)" onBlur="validate_string(this)"></td>
</tr>
</table>
</td>
</tr>
<tr>
<td>
<table width="666" border="2" cellpadding="0" cellspacing="0" bordercolor="E0E0E0"></table>
</td>
</tr>
<tr>
<td>		
<table width="666" border="1" cellpadding="0" cellspacing="0" bordercolor="B0B0B0">
<tr bgcolor="#CCCCCC"><td colspan="3"><font face="arial" size="2"><b>&nbsp</b></font></td></tr>
<tr bgcolor="#FFFFFF">  
   <td id ="Confirm" height="25" width="34%">  
   <div align="center"><font face="Arial"> <input class=inputSubmit onMouseOut=buttonOut(this) onMouseOver="buttonOver(this)" onClick="onSubmitCtrl(this, ' Restore ')" type="submit" value=" 복구 " name="action"></font></div> 
   </td>  
   <td height="25" width="33%">  
   <div align="center"><font face="Arial"> <input class=inputSubmit onMouseOut=buttonOut(this) onMouseOver="buttonOver(this)" onClick="onSubmitCtrl(this, ' Finish ')" type="submit" value=" 마침 " name="action"></font></div> 
   </td>
   <td height="25" width="33%">  
   <div align="center"><font face="Arial"> <input class=inputSubmit onMouseOut=buttonOut(this) onMouseOver="buttonOver(this)" onClick="onSubmitCtrl(this, ' Apply ')" type="submit" value=" 적용 " name="action"></font></div> 
   </td>    
</tr>
</table>
</td>
</tr>

<tr>
<td>
<table width="666" border="1" cellpadding="0" cellspacing="0" bordercolor="B0B0B0">
<tr>
    <td colspan="2" width="616" height="25" bgcolor="#FFBB00"></td> 
</tr>                   
<tr bgcolor="#FFFFFF">
    <td class="content_header_td_15" align="left">복구: </td>
    <td class="content_input_td_padding" align="left">상기 설정을 취소하고 설정복구를 유효화합니다.</td>
</tr>
<tr bgcolor="#FFFFFF">
    <td class="content_header_td_15" align="left">마침: </td>
    <td class="content_input_td_padding" align="left">모든 설정을 확인하고 WL520g를 지금 다시 시작합니다.</td>
</tr>
<tr bgcolor="#FFFFFF">
    <td class="content_header_td_15" align="left">적용: </td>
    <td class="content_input_td_padding" align="left">상기설정을 확인하고 계속합니다.</td>
</tr>
</table>
</td>
</tr>

</table>
</form>
</body>
