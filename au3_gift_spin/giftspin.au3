; Gift Spin by T.D. Stoneheart
#Region Customization
Global $SpinGUIWidth = 300, $SpinGUIHeight = 580
Global $BackstageViewWidth = 300, $BackstageViewHeight = 500
Const $SpinButtonString = "Spin"

Global $gift[][] = [ _
		["Song", 1, "a song from audiences"], _
		["Snack", 3, "a pack of snacks"], _
		["Socks", 1, "a pair of socks"], _
		["Lollipop", 7, "a lollipop"], _
		["Handbook", 1, "a handbook"] _
    ]
Func GiftAnnouncement($choice)
	MsgBox(0, "Congratulations!", "Your prize is " & $gift[$choice][2] & "!", 0, $SpinGUI)
	; MsgBox(0, "", $gift[$choice][0])
EndFunc
Func EndingMessage()
	MsgBox(0, "End of the gift spin", "No more prizes! :(")
EndFunc
#EndRegion

Opt("TrayAutoPause", 0)
Global $list, $last = 0
For $i = 0 To UBound($gift) - 1
	$list &= "|" & $gift[$i][0]
Next
$SpinGUI = GUICreate("Lucky Spin", $SpinGUIWidth + 16, $SpinGUIHeight + 80)
GUISetFont(24, 0, 0, "Tahoma", $SpinGUI)
$GiftList = GUICtrlCreateList("", 8, 8, $SpinGUIWidth, $SpinGUIHeight, 0)
GUICtrlSetData($GiftList, $list)
$SpinButton = GUICtrlCreateButton($SpinButtonString, 8, $SpinGUIHeight + 16, $SpinGUIWidth, 50, 1)
$BackstageView = GUICreate("Backstage View", $BackstageViewWidth + 16, $BackstageViewHeight + 8)
GUISetFont(16, 0, 0, "Tahoma", $BackstageView)
$GiftDetails = GUICtrlCreateList("", 8, 8, $BackstageViewWidth, $BackstageViewHeight, 0)
GUICtrlSetData($GiftDetails, BackstageGiftList())
GUISetState(@SW_SHOW, $BackstageView)
GUISetState(@SW_SHOW, $SpinGUI)
EndingCheck()

While 1
	$msg = GUIGetMsg(1)
	; If $msg[1] = $BackstageView And $msg[0] = -3 Then Exit
	If $msg[1] = $SpinGUI And $msg[0] = $SpinButton Then Spin()
WEnd

Func SelectItem(ByRef $choice, ByRef $sleep, $min, $max)
	$choice = Mod($choice + 1, UBound($gift))
	ControlCommand($SpinGUI, "", "ListBox1", "SetCurrentSelection", $choice)
	If $min <> $max Then $sleep *= Random($min, $max)
	Sleep($sleep)
EndFunc

Func Spin()
	Local $choice = $last - 1, $sleep = 20, $probability = .1, $select = $choice
	For $i = 1 To Random(UBound($gift), UBound($gift) * 3, 1)
		Do
			$select = Mod($select + 1, UBound($gift))
		Until $gift[$select][1] > 0
	Next
	For $i = 1 To Random(UBound($gift) * 3, UBound($gift) * 6, 1)
		SelectItem($choice, $sleep, 1, 1)
	Next
	Do
		SelectItem($choice, $sleep, 1.1, 1.3)
	Until $sleep >= 250
	Do
		SelectItem($choice, $sleep, 1.0, 1.1)
	Until $sleep >= 500 And $choice = $select
	For $i = 1 To 4
		ControlCommand($SpinGUI, "", "ListBox1", "SetCurrentSelection", -1)
		Sleep(250)
		ControlCommand($SpinGUI, "", "ListBox1", "SetCurrentSelection", $choice)
		Sleep(250)
	Next
	$last = $choice
	$gift[$choice][1] -= 1
	GUICtrlSetData($GiftDetails, BackstageGiftList())
	ControlCommand($BackstageView, "", "ListBox1", "SetCurrentSelection", $choice)
	GiftAnnouncement($choice)
	EndingCheck()
EndFunc

Func EndingCheck()
	For $i = 0 To UBound($gift) - 1
		If $gift[$i][1] > 0 Then Return
	Next
	EndingMessage()
	Exit
EndFunc

Func BackstageGiftList()
	Global $return = ""
	For $i = 0 To UBound($gift) - 1
		$return &= "|" & $gift[$i][0] & ": " & $gift[$i][1]
	Next
	Return $return
EndFunc
