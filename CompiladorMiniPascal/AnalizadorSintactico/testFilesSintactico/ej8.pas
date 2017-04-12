program ej8;
  var a, b, c:integer;
begin
 a:= funcInexistente();
 case a of
  1,3,5: c:= true;
  2,4,6: c:= false;
 end
end.
