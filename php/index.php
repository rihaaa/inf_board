<?php
	session_start ();
	ob_start ();
	ob_implicit_flush ( 0 );

	//error_reporting ( E_ALL ^ E_WARNING ^ E_NOTICE );
	define ( "ENGINE", true );
	define ( "INF_BOARD_LOCATION", "/home/pi/inf_board/data/" );
	
	if($_SESSION['_user']) $auth = true;
	else $auth = false;
	
	if($auth){
		$_user = $_SESSION['_user'];
	}
	
	$sidebar = '';
	
	if(!$auth) $sidebar .= '<a href="/?page=login">Ienākt</a><br>';

	if($auth){ 
		$sidebar .= '<a href="/?page=widgets">Изменение параметров виджетов</a><br>';
		$sidebar .= '<a href="/?page=text">Редактирование обьявлений</a><br>';
		$sidebar .= '<a href="/?page=lessons">Расписание звонков</a><br>';
		$sidebar .= '<a href="/?page=logout">Выход</a><br>';
	} 
	
	$output = '';
	$load = NULL;
	
	if($_GET) $_page = $_GET['page'];
	
	switch($_page) {
	case 'logout':
		$_SESSION['_user'] = NULL;
		$_SESSION['_password'] = NULL;
		unset($_SESSION['_user']);
		header("Location: /");
		break;
	case 'widgets':
		$load = "modules/widgets.php";
		break;
	case 'text':
		$load = "modules/text.php";
		break;
	case 'lessons':
		$load = "modules/lessons.php";
		break;
	default:
		if(!$auth) $load = "modules/login.php";
		else $load = "modules/main.php";
	break;
	}
	if($load) include($load);

	echo <<<HTML
	<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<title>Информационное табло &raquo; Панель управления</title>
		<link rel="stylesheet" href="/images/style.css" type="text/css" />
	</head>
	<body><br>
	<div align="center">
	<table style="width: 630;" border="1" cellpadding="2" cellspacing="2">
		<tbody>
		<tr>
			<td style="width: 130px; text-align: center; height: 130px;"><a href="/"><img src="/images/raspberry.png"></a></td>
			<td style="width: 500px; text-align: center; height: 130px;">
				<img src="/images/rtu_logo.png">
			</td>
		</tr>
HTML;

	if($_user == 'pi') $_user = 'Rihards.Bodendorfs';

	if($auth) echo <<<HTML
		<tr align="center">
			<td style="text-align: left;" rowspan="1"><h3>$_user</h3></td><td></td>
		</tr>
HTML;

	echo <<<HTML
		<tr>
			<td style="width: 130px; text-align: center; vertical-align: top;">
			$sidebar
			</td>
			<td style="width: 838px;"><div align="center">$output</div></td>
		</tr>
		</tbody>
	</table>

	</body>
	</html>
HTML;
?>