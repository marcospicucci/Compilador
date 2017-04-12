program ej2;
 var x,y,z:integer;
begin
 x:= 1;
 while (x <= 53) do
 begin
  z:= 33;
  y:= funcNoDecl(4,22+z);
  x:= x + 1
 end
end.
