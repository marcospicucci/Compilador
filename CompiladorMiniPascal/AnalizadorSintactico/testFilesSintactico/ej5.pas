program ej5;{recursivo}
  var x:integer;
   function f1(c:integer): integer;	
   begin
    if c = 1 then
	 f1:= 1
	else	
	 f1:= f1(c-1) + c
   end;
begin
 x:= f1(999)
end.		
