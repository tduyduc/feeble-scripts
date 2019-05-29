; When too many Chrome windows have spawned…
$l = ProcessList("chrome.exe")
For $i = 1 To $l[0][0]
	ProcessClose($l[$i][1])
Next
