<head>
<title>ZVMODELVZ Web Manager</title>
<meta http-equiv="Content-Type" content="text/html; charset=Shift_JIS">
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
    	
<input type="hidden" name="current_page" value="Advanced_BasicFirewall_Content.asp"><input type="hidden" name="next_page" value="Advanced_Firewall_Content.asp"><input type="hidden" name="next_host" value=""><input type="hidden" name="sid_list" value="FirewallConfig;"><input type="hidden" name="group_id" value=""><input type="hidden" name="modified" value="0"><input type="hidden" name="action_mode" value=""><input type="hidden" name="first_time" value=""><input type="hidden" name="action_script" value="">
<tr>
<td>
<table width="666" border="1" cellpadding="0" cellspacing="0" bordercolor="E0E0E0">
<tr class="content_header_tr">
<td class="content_header_td_title" colspan="2">�C���^�[�l�b�g�t�@�C�A�E�H�[�� - ��{�I�ȃR���t�B�O</td>
</tr>
<tr>
<td class="content_desc_td" colspan="2">�t�@�C�A�E�H�[��(SPI Firewall)��L���ɂ���ƁAZVMODELVZ�Ƃ��̔w��ɂ���f�o�C�X�ɑ΂��Ċ�b�I�ی��񋟂��܂��B�w�肳�ꂽ�p�P�b�g����������ɂ́A���y�[�W��WAN��LAN�t�B���^���g�p���Ă��������B
         </td>
</tr>
<tr>
<td class="content_header_td">�t�@�C�A�E�H�[����L���ɂ��܂���?
           </td><td class="content_input_td"><input type="radio" value="1" name="fw_enable_x" class="content_input_fd" onClick="return change_common_radio(this, 'FirewallConfig', 'fw_enable_x', '1')" <% nvram_match_x("FirewallConfig","fw_enable_x", "1", "checked"); %>>Yes</input><input type="radio" value="0" name="fw_enable_x" class="content_input_fd" onClick="return change_common_radio(this, 'FirewallConfig', 'fw_enable_x', '0')" <% nvram_match_x("FirewallConfig","fw_enable_x", "0", "checked"); %>>No</input></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('���̃t�B�[���h�́ALAN��WAN�ԂŃ��O�����p�P�b�g�̎�ނ������܂��B', LEFT);" onMouseOut="return nd();">���O���ꂽ�p�P�b�g�^�C�v:
           </td><td class="content_input_td"><select name="fw_log_x" class="content_input_fd" onChange="return change_common(this, 'FirewallConfig', 'fw_log_x')"><option class="content_input_fd" value="none" <% nvram_match_x("FirewallConfig","fw_log_x", "none","selected"); %>>None</option><option class="content_input_fd" value="drop" <% nvram_match_x("FirewallConfig","fw_log_x", "drop","selected"); %>>Dropped</option><option class="content_input_fd" value="accept" <% nvram_match_x("FirewallConfig","fw_log_x", "accept","selected"); %>>Accepted</option><option class="content_input_fd" value="both" <% nvram_match_x("FirewallConfig","fw_log_x", "both","selected"); %>>Both</option></select></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('���̋@�\�ɂ��A�C���^�[�l�b�g����ZVMODELVZ���Ǘ��ł��܂��B�z�[���Q�[�g�E�F�A���[�h�ɂ���ꍇ�A8080�|�[�g������ZVMODELVZ�ɃA�N�Z�X���Ă��������i�u���E�U��http://192.168.123.1:8080�Ȃǂ�URL����͂��邱�Ƃ��Ӗ����܂��j�B�u���E�U(80)�̊���|�[�g�́A���[�J���l�b�g���[�N����Web�T�[�o�[�p�ɓ��ʂɗ\�񂳂�Ă��邽�߁A���̃I�v�V�����̓t�@�C�A�E�H�[�����L���ɂȂ��Ă���ꍇ�̂݋@�\���܂��B�t�@�C�A�E�H�[���������ɂȂ�ƁA80�|�[�g��ZVMODELVZ�ɒ��ڃA�N�Z�X�ł��܂��B', LEFT);" onMouseOut="return nd();">WAN����Web�A�N�Z�X��L���ɂ��܂���?
           </td><td class="content_input_td"><input type="radio" value="1" name="misc_http_x" class="content_input_fd" onClick="return change_common_radio(this, 'FirewallConfig', 'misc_http_x', '1')" <% nvram_match_x("FirewallConfig","misc_http_x", "1", "checked"); %>>Yes</input><input type="radio" value="0" name="misc_http_x" class="content_input_fd" onClick="return change_common_radio(this, 'FirewallConfig', 'misc_http_x', '0')" <% nvram_match_x("FirewallConfig","misc_http_x", "0", "checked"); %>>No</input></td>
</tr>
<tr>
<td class="content_header_td" onMouseOver="return overlib('���̃t�B�[���h�ɂ��A�C���^�[�l�b�g����Web�T�[�o�[�ɃA�N�Z�X���邽�߂Ɏg�p����|�[�g���w��ł��܂��B', LEFT);" onMouseOut="return nd();">WAN����Web�A�N�Z�X�̃|�[�g:
           </td><td class="content_input_td"><input type="text" maxlength="5" size="5" name="misc_httpport_x" class="content_input_fd" value="<% nvram_get_x("FirewallConfig", "misc_httpport_x"); %>" onBlur="validate_range(this, 1024, 65535)" onKeyPress="return is_number(this)"></td>
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
<table width="666" border="1" cellpadding="0" cellspacing="0" bordercolor="B0B0B0">
<tr bgcolor="#CCCCCC"><td colspan="3"><font face="arial" size="2"><b>&nbsp</b></font></td></tr>
<tr bgcolor="#FFFFFF">  
   <td id ="Confirm" height="25" width="34%">  
   <div align="center"><font face="Arial"> <input class=inputSubmit onMouseOut=buttonOut(this) onMouseOver="buttonOver(this)" onClick="onSubmitCtrl(this, ' Restore ')" type="submit" value=" ���� " name="action"></font></div> 
   </td>  
   <td height="25" width="33%">  
   <div align="center"><font face="Arial"> <input class=inputSubmit onMouseOut=buttonOut(this) onMouseOver="buttonOver(this)" onClick="onSubmitCtrl(this, ' Finish ')" type="submit" value=" �I�� " name="action"></font></div> 
   </td>
   <td height="25" width="33%">  
   <div align="center"><font face="Arial"> <input class=inputSubmit onMouseOut=buttonOut(this) onMouseOver="buttonOver(this)" onClick="onSubmitCtrl(this, ' Apply ')" type="submit" value=" �K�p " name="action"></font></div> 
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
    <td class="content_header_td_15" align="left">����: </td>
    <td class="content_input_td_padding" align="left">��̐ݒ���������A�L���ɂȂ��Ă���ݒ�𕜌����܂��B</td>
</tr>
<tr bgcolor="#FFFFFF">
    <td class="content_header_td_15" align="left">�I��: </td>
    <td class="content_input_td_padding" align="left">���ׂĂ̐ݒ���m�F���āA��ZVMODELVZ���ċN�����܂��B</td>
</tr>
<tr bgcolor="#FFFFFF">
    <td class="content_header_td_15" align="left">�K�p: </td>
    <td class="content_input_td_padding" align="left">��̐ݒ���m�F���āA���s���܂��B</td>
</tr>
</table>
</td>
</tr>

</table>
</form>
</body>