<?php 
	if (!defined("ENGINE") or !$auth){
		header("Location: /");
		die();
	}

	$widgets = array(
		0 => "Title",
		1 => "Time",
		2 => "Bells",
		3 => "Week",
		4 => "Lesson",
		5 => "Calendar",
		6 => "Termo",
		7 => "Photos",
		8 => "Text"
	);
	
	if($_POST){
		$i = 0;
		$state = (array) $_POST['state'];
		$x =(array)  $_POST['x'];
		$y = (array) $_POST['y'];
		$cell = (array) $_POST['cell'];
		$new_config = (string) "";
		while($i <= (count($_POST['state']) - 1)){
			if($cell[$i] == 0) {
				$x[$i] = 35;
				$y[$i] = 505;
			}
			if($cell[$i] == 1) {
				$x[$i] = 915;
				$y[$i] = 505;
			}
			if($cell[$i] == 2) {
				$x[$i] = 35;
				$y[$i] = 310;
			}
			if($cell[$i] == 3) {
				$x[$i] = 330;
				$y[$i] = 310;
			}
			if($cell[$i] == 4) {
				$x[$i] = 625;
				$y[$i] = 310;
			}
			if($cell[$i] == 5) {
				$x[$i] = 920;
				$y[$i] = 310;
			}
			if($cell[$i] == 6) {
				$x[$i] = 35;
				$y[$i] = 120;
			}
			if($cell[$i] == 7) {
				$x[$i] = 330;
				$y[$i] = 120;
			}
			if($cell[$i] == 8) {
				$x[$i] = 625;
				$y[$i] = 120;
			}
			if($cell[$i] == 9) {
				$x[$i] = 920;
				$y[$i] = 120;
			}
		
		
			$new_config .= $i." ".$state[$i]." ".$x[$i]." ".$y[$i]." ".$cell[$i]."\r\n";
			$i++;
		}		
		
		$load_f = fopen(INF_BOARD_LOCATION."config.dat", "w");
		fwrite($load_f,$new_config);
		fclose($load_f);
	}
	
	$output .= '<div align="center"><h4>Изменение параметров виджетов</h4>';
	
	
	$output .= <<<HTML
	<form method="post" action="">
	<table>
	<tr>
		<td valign="center">
			<label>Название</label>
		</td>
		<td valign="center">
			<label>Состояние</label>
		</td>
		<td valign="center">
			<label>Cell</label>
		</td>
		<td valign="center">
			<label>X</label>
		</td>
		<td valign="center">
			<label>Y</label>
		</td>
	</tr>
HTML;
	
	$load_f = file(INF_BOARD_LOCATION."config.dat");
	$i = 0;
	foreach($load_f as $line_f)
	{
		$conf_array = explode(" ",$line_f);
		
		$sel_0='';
		$sel_1='';
		if($conf_array[1] == 1) $sel_1='selected'; else $sel_0='selected';
		
		$x = $conf_array[2];
		$y = $conf_array[3];
		
		if($conf_array[4] == -1){
			//$x = '<input  type="text" name="x['.$i.']" maxlength="4" size="3" value="'.$conf_array[2].'">';
			$y = '<input  type="text" name="y['.$i.']" maxlength="4" size="3" value="'.$conf_array[3].'">';
		}
		$output .= <<<HTML
		<tr>
			<td valign="center">
				$widgets[$i]
			</td>
			<td valign="center">
				<select name="state[$i]">
					<option disabled>---</option>
					<option $sel_0 value="0">Выключено</option>
					<option $sel_1 value="1">Включено</option>
				</select>
			</td>
			<td valign="center">
				<input  type="text" name="cell[$i]" maxlength="2" size="2" value="$conf_array[4]">
			</td>
			<td valign="center">
				$x
			</td>
			<td valign="center">
				$y
			</td>
		</tr>
HTML;
		$i++;
	}
	
		$output .= <<<HTML
	<tr>
		<td colspan="5" style="text-align:center">
			<input type="submit" value="Сохранить">
		</td>
	</tr>
	<tr>
		<td colspan="5" style="text-align:center">
			<img src="images/cells.png">
		</td>
	</tr>
	</table>
	</form>
HTML;
?>