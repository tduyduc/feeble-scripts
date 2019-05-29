#NoTrayIcon
AutoItSetOption("GUIOnEventMode", 1)
$file = "Windows10_TechnicalPreview_x32_EN-US_10041.iso"
$url = "http://iso.esd.microsoft.com/W9TPI/ECF708991AAA0C729E4A489622E686AB/Windows10_TechnicalPreview_x32_EN-US_10041.iso"
$size = InetGetSize($url)
If Not $size Then $size = 2719621120
$bytes = 2E9
$rate = 1E8
$interval = 100
$increasing = False
$quit = True
$GUI = GUICreate(Percentage($bytes, $size, 0) & " " & $file, 525, 235)
GUISetOnEvent(-3, "_")
GUISetFont(8.5, 0, 0, "Tahoma")
GUICtrlCreateTab(10, 8, 504, 165)
GUICtrlCreateTabItem("Download status")
GUICtrlCreateLabel($url, 26, 37, 462, 17)
GUICtrlCreateLabel("Status", 26, 55, 65, 17)
GUICtrlCreateLabel("Receiving data...", 96, 55, 392, 17)
GUICtrlSetColor(-1, 0x0000FF)
GUICtrlCreateLabel("File size", 26, 77, 98, 17)
GUICtrlCreateLabel(ByteSuffix($size), 129, 77, 359, 17)
GUICtrlCreateLabel("Downloaded", 26, 93, 98, 17)
$downloaded = GUICtrlCreateLabel(ByteSuffix($bytes) & " (" & Percentage($bytes, $size, 1) & ")", 129, 93, 359, 17)
GUICtrlCreateLabel("Transfer rate", 26, 109, 98, 17)
$speed = GUICtrlCreateLabel(ByteSuffix($rate) & "/sec", 129, 109, 359, 17)
GUICtrlCreateLabel("Time left", 26, 125, 98, 17)
$timeleft = GUICtrlCreateLabel($rate ? Round(($size - $bytes) / $rate) & " sec" : "", 129, 125, 359, 17)
GUICtrlCreateLabel("Resume capability", 26, 142, 127, 17)
GUICtrlCreateLabel("Yes", 158, 142, 359, 17)
GUICtrlCreateTabItem("")
GUICtrlCreateTabItem("Speed Limiter")
GUICtrlCreateTabItem("")
GUICtrlCreateTabItem("Options on completion")
GUICtrlCreateTabItem("")
$progress = GUICtrlCreateProgress(10, 181, 504, 17)
GUICtrlSetData(-1, Round($bytes / $size * 100))
GUICtrlCreateButton("Show details >>", 23, 205, 115, 25)
GUICtrlCreateButton("Pause", 305, 205, 84, 25)
GUICtrlCreateButton("Cancel", 416, 205, 75, 25)
GUICtrlSetOnEvent(-1, "_")
GUISetState()
While Sleep($interval)
	If $increasing Then
		$rate = Random(9E7, 1E8, 1)
		$bytes += Round($rate / 1000 * $interval)
		If $bytes >= $size Then
			If $quit Then Exit
			$bytes = $size
			$rate = 0
			$increasing = False
		EndIf
		WinSetTitle($GUI, "", Percentage($bytes, $size, 0) & " " & $file)
		GUICtrlSetData($downloaded, ByteSuffix($bytes) & " (" & Percentage($bytes, $size, 1) & ")")
		GUICtrlSetData($speed, ByteSuffix($rate) & "/sec")
		GUICtrlSetData($timeleft, $rate ? Round(($size - $bytes) / $rate) & " sec" : "")
		GUICtrlSetData($progress, Round($bytes / $size * 100))
	EndIf
WEnd

Func _()
	Exit
EndFunc

Func Percentage($iBytes, $iTotal, $iFlag)
	Return Round($iBytes / $iTotal * 100, $iFlag ? 2 : 0) & "%"
EndFunc

Func ByteSuffix($iBytes)
    Local $iIndex, $aArray[9] = [' B', ' KB', ' MB', ' GB', ' TB', ' PB', ' EB', ' ZB', ' YB']
    While $iBytes >= 1024 And $iIndex < 8
        $iIndex += 1
        $iBytes /= 1024
    WEnd
    Return Round($iBytes, 2) & $aArray[$iIndex]
EndFunc
