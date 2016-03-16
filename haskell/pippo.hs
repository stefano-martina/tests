raddoppia x = x + x
raddoppiaLimitato x = if x<100 then raddoppia x else 100

fibon :: Integral a => a -> a
fibon n	  |  n<=0      	= error "Number must be positive"
      	  |  n==1	= 1
      	  |  n==2	= 1
	  |  otherwise	= fibon (n-1) + fibon (n-2)

coprim :: Integer -> Integer -> Bool
coprim k n | k==n		= True
       	   | n`mod`k /= 0	= coprim (k+1) n
	   | otherwise		= False

prim :: Integer -> Bool
prim n = coprim 2 n

nextPrim :: Integer -> Integer
nextPrim n  | prim n	= n
	    | otherwise	= nextPrim (n+1)

