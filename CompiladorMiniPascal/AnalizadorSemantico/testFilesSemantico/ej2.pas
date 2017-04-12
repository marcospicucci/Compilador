program ej2;
 var i,x:integer; p:boolean;
  function f(t:integer):boolean;
   var p:integer;
   begin
    f:= t = 1 
   end;
begin
 i := 5; 
 while f(i) do 
  begin
   i := i-1;
   if i<>0 then
	write(i)
   else
    begin  
     x := pred(pred(i));
     write(x)  
	end;
   p:= i < x * -1 	
  end; {del while}
write(p)
end.
