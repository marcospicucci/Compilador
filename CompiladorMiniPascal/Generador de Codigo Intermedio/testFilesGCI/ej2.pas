program ej2;{con case}
 var a:integer;
begin
 read(a);
 case a of
  1: a:= a*10;
  7: a:= a*200;
  9: a:= a*3000;
  else
	a:= -1; 
 end; 
write(a) 
end.
