program ej3;
 var a:integer;
  function fun(x,y:integer;z:boolean):integer;
   var f,g:integer;
  begin
   f:= x+y;
   g:= f*2 +1;
   write(g);
   if(z or (g<10)) then
    fun:= g
   else
    fun:= 0
  end;
begin
 a:= 4;
 write(fun(a,1,false))
end.    
