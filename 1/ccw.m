function f = ccw(p,q,r)
f = ( p(1)*q(2)-p(2)*q(1) )+( q(1)*r(2)-q(2)*r(1) )+( p(2)*r(1)-p(1)*r(2) );
end