program err11;
 var x:integer;
  procedure pro(a:integer);
  begin
   read(a);
   x:= a
  end;   
begin
 x:= 1 + pro(-512)
end.
