program ej6; {expresiones con al menos 2 operadores y una invoc a func}
  var x, y: integer;
   function chi(a:integer):integer;
	 var k:integer;
   begin
	k:= 1 + a * (5 - a/2);
	chi:= k
   end;
begin
 y:= 99;
 x:= y/2 + chi(20-(3*y)) * 7
end.
