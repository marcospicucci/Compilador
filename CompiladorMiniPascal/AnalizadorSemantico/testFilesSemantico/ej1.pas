program ej1;
 var a,b:integer; k,l:boolean;
  function f1(x,y:integer;p:boolean):boolean;  
   var t:integer;
  begin
   t:= (x+y)-(x/2 + y*3)*10;
    if((t<-1) and p) then
     f1:= true
    else
     f1:= pred(t*2) >= 45  
  end;
begin
 a:= 9;
 read(b);
 l:= (b <> 0) and not(a=b);
 k:= f1(a,b,l);
 write(k)
end.  
