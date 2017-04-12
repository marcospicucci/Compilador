program err1;
var a:integer;
 function fun(x:integer;k:boolean):integer;
  begin			
   if(k and (x< 9)) then 
	 fun:= 1
   else 
     fun:= 0
  end;
begin
 a:= fun(1,true,99,maxint);      
{etc} 
