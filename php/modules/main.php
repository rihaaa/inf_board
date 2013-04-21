<?php 
	if (!defined("ENGINE") or !$auth){
		header("Location: /");
		die();
	}

	$output .= "";
	
	if($_POST){
		$_user = $_POST['username'];
		$_password = $_POST['password'];
		
		$auth = false;
		if($_user == 'pi' & $_password == 'raspberry'){
			$auth = true;
		}
		if($auth){
			$_SESSION['_user'] = $_user;
			$_SESSION['_password'] = md5($_password);
			header("Location: /");
		}
	}
	
	$output .= <<<HTML

HTML;
?>