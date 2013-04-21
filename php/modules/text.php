<?php 
	if (!defined("ENGINE") or !$auth){
		header("Location: /");
		die();
	}

	if($_POST){
		$i = 1;
		$state = (array) $_POST['state'];
		$text =(array)  $_POST['text'];
		
		$new_config = (string) "";
		while($i <= (count($state))){
			$text[$i] = strtr($text[$i], array(' ' => '_'));
			if($i == (count($state))){
				$new_config .= $text[$i];
			}
			else{
				$new_config .= $text[$i]."\r\n";
			}
			$i++;
		}		
		
		$load_f = fopen(INF_BOARD_LOCATION."text.dat", "w");
		fwrite($load_f,$new_config);
		fclose($load_f);	
	}
	
	$output .= "<h4>Редактирование обьявлений</h4>";
	
	$output .= <<<HTML
	<form method="post" action="">
	<table>
	<tr>
		<td valign="center">
			<label>Номер</label>
		</td>
		<td valign="center">
			<label>Состояние</label>
		</td>
		<td valign="center">
			<label>Текст</label>
		</td>
	</tr>
HTML;
	
	$load_f = file(INF_BOARD_LOCATION."text.dat");
	$i = 1;
	foreach($load_f as $line_f)
	{
		$conf_array = explode("\n",$line_f);
		
		$sel_0='';
		$sel_1='';
		$sel_1='selected';
		//if($conf_array[1] == 1) $sel_1='selected'; else $sel_0='selected';
		
		//$replace_rule = ;
		$conf_array[0] = strtr($conf_array[0], array('_' => ' '));
		
		$output .= <<<HTML
		<tr>
			<td valign="center">
				$i
			</td>
			<td valign="center">
				<select name="state[$i]">
					<option disabled>---</option>
					<option $sel_0 value="0">Выключено</option>
					<option $sel_1 value="1">Включено</option>
				</select>
			</td>
			<td valign="center">
				<input  type="text" name="text[$i]" maxlength="50" size="50" value="$conf_array[0]">
			</td>
		</tr>
HTML;
		$i++;
	}
	
		$output .= <<<HTML
	<tr>
		<td colspan="4" style="text-align:center">
			<input type="submit" value="Сохранить">
		</td>
	</tr>
	</table>
	</form>
HTML;
?>