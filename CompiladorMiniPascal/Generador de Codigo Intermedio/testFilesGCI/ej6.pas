program ej6;{case sin else}
 var a,b:integer; c:boolean;
begin
 read(a);
 read(b);
 c := (a <> b) or (a > (b + 5/2)); 
 case a of
  10: write(c);
  55: a:= b - 1;
 end 
end.
