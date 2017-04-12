program ej1;{con while}
 var a,b:integer;
begin
 a:=0;
 b:=9;
 while a < 3 do
  begin
   a:= a + (b/9 - 3)* 7;
   b:= b+a
  end;
 write(a);
 write(b)
end.  
