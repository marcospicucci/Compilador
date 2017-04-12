program err10;
 function fun(x:integer):boolean;
 begin
  if x>1 then
   fun := false
  else
   fun := true;
  x := x+256    
 end;
begin
 fun(22);
 {etc}
