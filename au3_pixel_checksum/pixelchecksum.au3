#NoTrayIcon
Opt("PixelCoordMode", 2)
GUICreate("Pixel Checksum", 200, 135)
GUISetFont(8.5, 0, 0, "Tahoma")
GUICtrlCreateLabel("Window:", 5, 5, 50, 20)
$wnd = GUICtrlCreateInput("", 55, 5, 135, 20)
GUICtrlCreateLabel("Left/X:", 5, 30, 50, 20)
$left = GUICtrlCreateInput("", 55, 30, 35, 20, 0x2000)
GUICtrlCreateLabel("Top/Y:", 105, 30, 50, 20)
$top = GUICtrlCreateInput("", 155, 30, 35, 20, 0x2000)
GUICtrlCreateLabel("Right/X:", 5, 55, 50, 20)
$right = GUICtrlCreateInput("", 55, 55, 35, 20, 0x2000)
GUICtrlCreateLabel("Bottom/Y:", 105, 55, 50, 20)
$bottom = GUICtrlCreateInput("", 155, 55, 35, 20, 0x2000)
$crc32 = GUICtrlCreateCheckbox("CRC32", 5, 80, 100, 20)
GUICtrlCreateLabel("Step:", 105, 80, 50, 20)
$step = GUICtrlCreateInput(1, 155, 80, 35, 20, 0x2000)
$check = GUICtrlCreateButton("Get Pixel Checksum!", 25, 105, 150, 25, 1)
GUISetState(@SW_SHOW)
Do
	$msg = GUIGetMsg()
	If $msg = $check Then GUICtrlSetData($check, _
		PixelChecksum(GUICtrlRead($left), GUICtrlRead($top), _
		GUICtrlRead($right), GUICtrlRead($bottom), _
		StringIsDigit(GUICtrlRead($step)) ? GUICtrlRead($step) : 1, _
		WinGetHandle(GUICtrlRead($wnd)), _
		(GUICtrlRead($crc32) = 1) ? 1 : 0))
Until $msg = -3
