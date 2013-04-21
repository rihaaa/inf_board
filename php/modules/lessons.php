<?php 
	if (!defined("ENGINE") or !$auth){
		header("Location: /");
		die();
	}
	
	if($_POST){
		$i = 1;
		$state = (array) $_POST['state'];
		$start_h =(array)  $_POST['start_h'];
		$start_min = (array) $_POST['start_min'];
		$end_h =(array)  $_POST['end_h'];
		$end_min = (array) $_POST['end_min'];
		$less_len = (array) $_POST['less_len'];
		$new_config = (string) "";
		
		while($i <= (count($_POST['state']))){
			$start_t = (int) ($start_h[$i] * 3600 + $start_min[$i] * 60);
			$end_t = (int) ($end_h[$i] * 3600 + $end_min[$i] * 60);
			$new_config .= $i." ".$state[$i]." ".$start_t." ".$end_t." ".($less_len[$i] * 60)."\r\n";
			$i++;
		}
		
		$load_f = fopen(INF_BOARD_LOCATION."lessons.dat", "w");
		fwrite($load_f,$new_config);
		fclose($load_f);
	}
	
	$output .= '<div align="center"><h4>Расписание звонков</h4>';
	
	
	$output .= <<<HTML
	<form method="post" action="">
	<table>
	<tr>
		<td valign="center" rowspan="2">
			<label>Номер</label>
		</td>
		<td valign="center" rowspan="2">
			<label>Тип</label>
		</td>
		<td valign="center" colspan="2">
			<label>Начало</label>
		</td>
		<td valign="center" colspan="2">
			<label>Конец</label>
		</td>
		<td valign="center" rowspan="2">
			<label>Длинна урока</label>
		</td>
	</tr>
	<tr>
		<td valign="center">
			<label>Часы</label>
		</td>
		<td valign="center">
			<label>Минуты</label>
		</td>
		<td valign="center">
			<label>Часы</label>
		</td>
		<td valign="center">
			<label>Минуты</label>
		</td>
	</tr>
HTML;
	
	$load_f = file(INF_BOARD_LOCATION."lessons.dat");
	$i = 1;
	foreach($load_f as $line_f)
	{
		$conf_array = explode(" ",$line_f);
		
		$sel_1='';
		$sel_2='';
		if($conf_array[1] == 1) $sel_1='selected'; else $sel_2='selected';
		
		$start_h = floor($conf_array[2] / 3600);
		$start_min = floor($conf_array[2] % 3600 / 60);	
		
		$end_h = floor($conf_array[3] / 3600);
		$end_min = floor($conf_array[3] % 3600 / 60);
		$conf_array[4] = 45;
		$output .= <<<HTML
		<tr>
			<td valign="center">
				$i
			</td>
			<td valign="center">
				<select name="state[$i]">
					<option disabled>---</option>
					<option $sel_1 value="1">---</option>
					<option $sel_2 value="2">---</option>
				</select>
			</td>
			<td valign="center">
				<input  type="text" name="start_h[$i]" maxlength="2" size="2" value="$start_h">
			</td>
			<td valign="center">
				<input  type="text" name="start_min[$i]" maxlength="2" size="2" value="$start_min">
			</td>
			<td valign="center">
				<input  type="text" name="end_h[$i]" maxlength="2" size="2" value="$end_h">
			</td>
			<td valign="center">
				<input  type="text" name="end_min[$i]" maxlength="2" size="2" value="$end_min">
			</td>
			<td valign="center">
				<input  type="text" name="less_len[$i]" maxlength="2" size="2" value="$conf_array[4]">
			</td>
		</tr>
HTML;
		$i++;
	}
	
		$output .= <<<HTML
	<tr>
		<td colspan="7" style="text-align:center">
			<input type="submit" value="Сохранить">
		</td>
	</tr>
	</table>
	</form>
HTML;
?>