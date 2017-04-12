program ej1;
  var a,b,c:integer;d:boolean;	
begin
 c:= 1;
 b:= 0;
 a:= funcNoDef(2,pred(succ(fun(d))));
 if b > a then
  begin
   if c < b then
	c:= false
   else	
    c:= true	
  end;
procNoDef();
otro(1, false)
end.
