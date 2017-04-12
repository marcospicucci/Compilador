program err9;
 var a,b:boolean; {en un factor, en una asig. se espera id de variable}
  procedure q(l:integer);
  begin
   write(l)
  end;
begin
 read(a);
 b := a or not q;
{etc}

