#RequireAdmin
Opt("PixelCoordMode", 2)
$h = WinGetHandle("[CLASS:Crazy Arcade]")
$t = TimerInit()
$p = MemoryReadPixel(761, 589, $h)
MsgBox(0, $p, TimerDiff($t))
$t = TimerInit()
$p = PixelGetColor(761, 589, $h)
MsgBox(0, $p, TimerDiff($t))
$t = TimerInit()
$p = MemorySearchPixel(0, 0, 100, 100, 0xffffff, 2, $h)
MsgBox(0, @error ? @error : ($p[0] & ", " & $p[1]), TimerDiff($t))
$t = TimerInit()
$p = PixelSearch(0, 0, 100, 100, 0xffffff, 0, 2, $h)
MsgBox(0, @error ? @error : ($p[0] & ", " & $p[1]), TimerDiff($t))
$t = TimerInit()
$p = MemoryGetChecksum(0, 0, 9, 9, 2, $h)
MsgBox(0, $p, TimerDiff($t))
$t = TimerInit()
$p = PixelChecksum(0, 0, 9, 9, 2, $h)
MsgBox(0, $p, TimerDiff($t))
;Testing results: MemoryReadPixel is 4 times slower than PixelGetColor!
#Region PixelReadingFunctions
Func _GetDC($hWnd)
	WinSetTrans($hWnd, "", 254)
	WinSetState($hWnd, "", @SW_SHOW)
	$aResult = DllCall("user32.dll", "handle", "GetDC", "hwnd", $hWnd)
	If @error Then Return SetError(@error, @extended, 0)
    Return $aResult[0]
EndFunc

Func _ReleaseDC($hWnd, $hDC)
	WinSetTrans($hWnd, "", 255)
	Return DllCall("user32.dll", "int", "ReleaseDC", "hwnd", $hWnd, "handle", $hDC)
EndFunc

Func _GetPixel($x, $y, $hDC)
	$iColor = DllCall("gdi32.dll", "int", "GetPixel", "int", $hDC, "int", $x, "int", $y)
	If @error Then Return SetError(@error, @extended, 0)
    $color = Hex($iColor[0], 6)
	Return Dec(StringRight($color, 2) & StringMid($color, 3, 2) & StringLeft($color, 2))
EndFunc

Func MemoryReadPixel($x, $y, $hWnd)
    $hDC = _GetDC($hWnd)
	$iColor = _GetPixel($x, $y, $hDC)
	_ReleaseDC($hWnd, $hDC)
	Return $iColor
EndFunc

Func MemorySearchPixel($left, $top, $right, $bottom, $color, $step, $hWnd)
	Local $aRet[] = [0, 0]
	$HStep = $step * ($left > $right ? -1 : 1)
	$VStep = $step * ($top > $bottom ? -1 : 1)
	$hDC = _GetDC($hWnd)
	For $y = $top To $bottom Step $VStep
		For $x = $left To $right Step $HStep
			If _GetPixel($x, $y, $hDC) = $color Then
				$aRet[0] = $x
				$aRet[1] = $y
				WinSetTrans($hWnd, "", 255)
				_ReleaseDC($hWnd, $hDC)
				Return $aRet
			EndIf
		Next
	Next
	_ReleaseDC($hWnd, $hDC)
	Return SetError(1, 0, $aRet)
EndFunc

Func MemoryGetChecksum($left, $top, $right, $bottom, $step, $hWnd)
	; this function is only compatible with 1-step ADLER PixelChecksum!
    Local $x, $y, $color, $s1 = 1, $s2 = 0, $adler
	$HStep = $step * ($left > $right ? -1 : 1)
	$VStep = $step * ($top > $bottom ? -1 : 1)
	$hDC = _GetDC($hWnd)
	For $y = $top To $bottom Step $VStep
		For $x = $left To $right Step $HStep
            $color = Hex(_GetPixel($x, $y, $hDC), 6)
			For $i = 1 To 5 Step 2
				$s1 = Mod($s1 + Dec(StringMid($color, $i, 2)), 65521)
				$s2 = Mod($s2 + $s1, 65521)
				$adler = ($s2 * 65536) + $s1
			Next
        Next
    Next
	WinSetTrans($hWnd, "", 255)
	_ReleaseDC($hWnd, $hDC)
    Return $adler
EndFunc
#EndRegion
