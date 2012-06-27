function [ n ] = vec1norm( a, b, dir )
    v = b - a;
    if( dir > 0 )
        n = [ -v(2); v(1) ];
    else
        n = [ v(2); -v(1) ];
    end
    n = n ./ norm( n, 2 );
end