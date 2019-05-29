var a: array[1..100] of byte; n, i, j, k, temp: byte;

begin
    (* Data Entry *)
    write('Number of elements: ');
    readln(n);
    for i := 1 to n do begin
        write('Element ', i, ': ');
        readln(a[i]);
    end;
    
    (* Bubble Sort *)
    for i := 1 to n - 1 do
        for j := n downto i + 1 do
            if a[j] < a[j - 1] then begin
                temp := a[j];
                a[j] := a[j - 1];
                a[j - 1] := temp
            end;
    
    (* Selection Sort *)
    for i := 1 to n - 1 do begin
        k := i;
        for j := i + 1 to n do
            if a[j] < a[k] then k := j;
        if k <> i then begin
            temp := a[i];
            a[i] := a[k];
            a[k] := temp
        end
    end;
    
    (* Insertion Sort *)
    for i := 2 to n do begin
        j := i - 1;
        temp := a[i];
        while (temp < a[j]) and (j >= 1) do begin
            a[j + 1] := a[j];
            j := j - 1;
        end;
        a[j + 1] := temp;
    end;
    
    (* Result Display *)
    writeln('Results: ');
    for i := 1 to n do
        write(a[i]:8);
    readln
end.
