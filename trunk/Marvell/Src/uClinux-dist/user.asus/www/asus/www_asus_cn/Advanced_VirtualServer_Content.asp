<head>
<title>ZVMODELVZ Web Manager</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
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
    	
<input type="hidden" name="current_page" value="Advanced_VirtualServer_Content.asp"><input type="hidden" name="next_page" value="Advanced_Exposed_Content.asp"><input type="hidden" name="next_host" value=""><input type="hidden" name="sid_list" value="IPConnection;PPPConnection;"><input type="hidden" name="group_id" value=""><input type="hidden" name="modified" value="0"><input type="hidden" name="action_mode" value=""><input type="hidden" name="first_time" value=""><input type="hidden" name="action_script" value="">
<tr>
<td>
<table width="666" border="1" cellpadding="0" cellspacing="0" bordercolor="E0E0E0">
<tr class="content_header_tr">
<td class="content_header_td_title" colspan="2">NAT设置 - 虚拟服务器</td>
</tr>
<tr>
<td class="content_desc_td" colspan="2">要从您所在网络中的服务器对网外用户提供WWW、FTP等网络服务时，您应该先要指定一个连接服务器的本地IP地址。接着，将IP地址及网络通讯协议的类型、端口号及网络服务名称增加到下列的列表之中。以此列表为前题，网关会将网络服务要求从网外用户转递给相应的本地服务器。
         </td>
</tr>
<tr>
<td class="content_header_td">打开虚拟服务器？
           </td><td class="content_input_td"><input type="radio" value="1" name="vts_enable_x" class="content_input_fd" onClick="return change_common_radio(this, 'IPConnection', 'vts_enable_x', '1')" <% nvram_match_x("IPConnection","vts_enable_x", "1", "checked"); %>>Yes</input><input type="radio" value="0" name="vts_enable_x" class="content_input_fd" onClick="return change_common_radio(this, 'IPConnection', 'vts_enable_x', '0')" <% nvram_match_x("IPConnection","vts_enable_x", "0", "checked"); %>>No</input></td>
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
<table width="666" border="2" cellpadding="0" cellspacing="0" bordercolor="E0E0E0"></table>
</td>
</tr>
<tr>
<td>
<table width="666" border="2" cellpadding="0" cellspacing="0" bordercolor="E0E0E0">
<tr class="content_list_header_tr">
<td class="content_list_header_td" width="60%" id="VSList">虚拟服务器列表
         <input type="hidden" name="vts_num_x_0" value="<% nvram_get_x("IPConnection", "vts_num_x"); %>" readonly="1"></td><td width="10%">
<div align="center">
<input class="inputSubmit" type="submit" onMouseOut="buttonOut(this)" onMouseOver="buttonOver(this)" onClick="return markGroup(this, 'VSList', 24, ' Add ');" name="VSList" value="增加" size="12">
</div>
</td><td width="10%">
<div align="center">
<input class="inputSubmit" type="submit" onMouseOut="buttonOut(this)" onMouseOver="buttonOver(this)" onClick="return markGroup(this, 'VSList', 24, ' Del ');" name="VSList" value="删除" size="12">
</div>
</td><td width="5%"></td>
</tr>
<table class="content_list_table" width="640" border="0" cellspacing="0" cellpadding="0">
<tr>
<td colspan="3" height="10"></td>
</tr>
<tr>
<td colspan="3">
<div align="center">
<table class="content_list_value_table" border="1" cellspacing="0" cellpadding="0">
<tr>
<td></td><td class="content_list_field_header_td" colspan="2">知名应用程序：         
         </td><td class="content_list_field_header_td" colspan="4"><select name="KnownApps" class="content_input_fd" onChange="change_widzard(this, 'KnownApps');"><option value="User Defined">User Defined</option></select></td>
</tr>
<tr>
<td></td><td class="content_list_field_header_td" colspan="">端口范围	                
           	        </td><td class="content_list_field_header_td" colspan="">本地IP	                
           	        </td><td class="content_list_field_header_td" colspan="">本地通讯端口	                
           	        </td><td class="content_list_field_header_td" colspan="">协议	                
           	        </td><td class="content_list_field_header_td" colspan="">协议编号	                
           	        </td><td class="content_list_field_header_td" colspan="">说明	                
           	        </td><td></td>
</tr>
<tr>
<td></td><td class="content_list_input_td" colspan=""><input type="text" maxlength="11" class="content_input_list_fd" size="10" name="vts_port_x_0" value="" onKeyPress="return is_portrange(this)"></td><td class="content_list_input_td" colspan=""><input type="text" maxlength="15" class="content_input_list_fd" size="14" name="vts_ipaddr_x_0" onKeyPress="return is_ipaddr(this)" onKeyUp="change_ipaddr(this)"></td><td class="content_list_input_td" colspan=""><input type="text" maxlength="10" size="5" class="content_input_list_fd" name="vts_lport_x_0" onKeyPress="return is_number(this)"></td><td class="content_list_input_td" colspan=""><select name="vts_proto_x_0" class="content_input_list_fd"><option value="TCP" <% nvram_match_list_x("IPConnection","vts_proto_x", "TCP","selected", 0); %>>TCP</option><option value="UDP" <% nvram_match_list_x("IPConnection","vts_proto_x", "UDP","selected", 0); %>>UDP</option><option value="BOTH" <% nvram_match_list_x("IPConnection","vts_proto_x", "BOTH","selected", 0); %>>BOTH</option><option value="OTHER" <% nvram_match_list_x("IPConnection","vts_proto_x", "OTHER","selected", 0); %>>OTHER</option></select></td><td class="content_list_input_td" colspan=""><input type="text" maxlength="5" style="font-family: fixedsys; font-size: 10pt;" size="10" name="vts_protono_x_0" onKeyPress="return is_number(this)"></td><td class="content_list_input_td" colspan=""><input type="text" maxlength="20" size="20" name="vts_desc_x_0" class="content_input_list_fd" onKeyPress="return is_string(this)"></td>
</tr>
<tr>
<td></td><td colspan="10"><select size="8" name="VSList_s" multiple="true" style="font-family: 'fixedsys'; font-size: '8pt'">
<% nvram_get_table_x("IPConnection","VSList"); %>
</select></td>
</tr>
</table>
</div>
</td>
</tr>
<tr>
<td colspan="3" height="10"></td>
</tr>
</table>
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
<table width="666" border="1" cellpadding="0" cellspacing="0" bordercolor="E0E0E0"></table>
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
   <div align="center"><font face="Arial"> <input class=inputSubmit onMouseOut=buttonOut(this) onMouseOver="buttonOver(this)" onClick="onSubmitCtrl(this, ' Restore ')" type="submit" value=" 还原 " name="action"></font></div> 
   </td>  
   <td height="25" width="33%">  
   <div align="center"><font face="Arial"> <input class=inputSubmit onMouseOut=buttonOut(this) onMouseOver="buttonOver(this)" onClick="onSubmitCtrl(this, ' Finish ')" type="submit" value=" 保存 " name="action"></font></div> 
   </td>
   <td height="25" width="33%">  
   <div align="center"><font face="Arial"> <input class=inputSubmit onMouseOut=buttonOut(this) onMouseOver="buttonOver(this)" onClick="onSubmitCtrl(this, ' Apply ')" type="submit" value=" 应用 " name="action"></font></div> 
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
    <td class="content_header_td_15" align="left">还原: </td>
    <td class="content_input_td_padding" align="left">清除上述设置并还原有效设置。</td>
</tr>
<tr bgcolor="#FFFFFF">
    <td class="content_header_td_15" align="left">保存: </td>
    <td class="content_input_td_padding" align="left">现在确认所有设置并重新启动ZVMODELVZ。</td>
</tr>
<tr bgcolor="#FFFFFF">
    <td class="content_header_td_15" align="left">应用: </td>
    <td class="content_input_td_padding" align="left">确认上述设置并继续。</td>
</tr>
</table>
</td>
</tr>

</table>
</form>
</body>
