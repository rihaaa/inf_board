<?php
	if (!defined("ENGINE")){
		header("Location: /");
		die();
	}

	$output .= "<h4>Lūdzu ievadiet savus akreditācijas datus</h4>";
	
	if($_POST){
		$_p_user = $_POST['username'];
		$_p_password = $_POST['password'];
		
		$auth = false;
		if($_p_user == 'pi' & md5($_p_password) == 'b89749505e144b564adfe3ea8fc394aa'){
			$auth = true;
		}
		if($auth){
			$_SESSION['_user'] = $_p_user;
			$_SESSION['_password'] = md5($_p_password);
			header("Location: /");
		}
	}
	
	$output .= <<<HTML
	<form method="post" action="">
	<table class="top-menu">
		<tr>
			<td valign="center">
				Lietotājvārds:
			</td>
			<td valign="center">
				<input  type="text" name="username" maxlength="50" size="20" value="">
			</td>
		</tr>
		<tr>
			<td valign="center">
				Parole:
			</td>
			<td valign="center">
				<input type="password" name="password" maxlength="50" size="20" value="">
			</td>
		</tr>
		<tr>
			<td colspan="4" style="text-align:center">
				<input type="submit" value="Ienākt">
			</td>
		</tr>
	</table>
	</form>
HTML;
?>