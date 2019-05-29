#cs
Tree Node ADT
public interface BinNode<E> {
	E element();
	void setElement(E v);
	BinNode<E> left();
	void setLeft(BinNode<E> l);
	BinNode<E> right();
	void setRight(BinNode<E> r);
	boolean isLeaf();
}

Array-Based Implementation
	$aTree[][2] = [$parent, $element]
	The 1st dimension is expanded as needed

Minimax Pseudocode
01 function minimax(node, depth, maximizingPlayer)
02     if depth = 0 or node is a terminal node
03         return the heuristic value of node

04     if maximizingPlayer
05         bestValue := -inf
06         for each child of node
07             v := minimax(child, depth - 1, FALSE)
08             bestValue := max(bestValue, v)
09         return bestValue

10     else    (* minimizing player *)
11         bestValue := +inf
12         for each child of node
13             v := minimax(child, depth - 1, TRUE)
14             bestValue := min(bestValue, v)
15         return bestValue
#ce

Global $aTree[6][2] = [[-1, 0], [0, 4], [0, 3], [1, 2], [2, 1], [2, 3]]
; MsgBox(0, IsLeaf(2), IsLeaf(5))
; MsgBox(0, IsLeaf(0), MinimaxIndex(0, 2, 1))
MsgBox(0, NodeDepth($aTree, 1), NodeDepth($aTree, 5))

Func NodeDepth(ByRef Const $Tree, $NodeIndex)
	Local $node = $NodeIndex, $result = 0
	While $node > 0
		$node = $Tree[$node][0]
		$result += 1
	WEnd
	Return $result
EndFunc

Func IsLeaf(ByRef Const $Tree, $NodeIndex)
	For $i = 0 To UBound($Tree) - 1
		If $Tree[$i][0] = $NodeIndex Then Return False
	Next
	Return True
EndFunc

Func MinimaxIndex(ByRef Const $Tree, $NodeIndex, $Depth, $Maximize)
	Local $Best = Minimax($Tree, $NodeIndex, $Depth, $Maximize)
	For $i = 0 To UBound($Tree)
		If $Tree[$i][1] = $Best Then Return $Tree[$i][0]
	Next
	Return 0
EndFunc

Func Minimax(ByRef Const $Tree, $NodeIndex, $Depth, $Maximize)
	If $Depth = 0 Or IsLeaf($Tree, $NodeIndex) Then Return $Tree[$NodeIndex][1]
	Local $Best
	If $Maximize Then
		$Best = -1E9
		For $i = 0 To UBound($Tree) - 1
			If $Tree[$i][0] = $NodeIndex Then $Best = Max($Best, Minimax($Tree, $i, $Depth - 1, 0))
		Next
	Else
		$Best = 1E9
		For $i = 0 To UBound($Tree) - 1
			If $Tree[$i][0] = $NodeIndex Then $Best = Min($Best, Minimax($Tree, $i, $Depth - 1, 1))
		Next
	EndIf
	Return $Best
EndFunc

Func Min($a, $b)
	Return ($a < $b) ? $a : $b
EndFunc

Func Max($a, $b)
	Return ($a > $b) ? $a : $b
EndFunc
