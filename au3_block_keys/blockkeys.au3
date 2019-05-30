Global $keys[] = ['{pgup}', '{pgdn}']

AutoItSetOption("TrayAutoPause", 0)
For $i = 0 To UBound($keys) - 1
  HotKeySet($keys[i], 'Nothing')
Next
While Sleep(1000)
WEnd

Func Nothing()
EndFunc
