{
	Given a big non-negative integer string n (length < 256). Given a number k.
	Delete k digits from n. Find the smallest possible number.
}
var k, i, j: byte; n: string;
begin
	write('Enter a non-negative integer: ');
	readln(n);
	write('Enter number of digits to be deleted: ');
	readln(k);
	if k >= length(n) then n := '0'
	else if k > 0 then
		for i := 1 to k do begin
			j := 1;
			while (n[j] <= n[j + 1]) and (j < length(n)) do
				inc(j);
			delete(n, j, 1)
		end;
	writeln('Result: ', n);
	readln
end.
