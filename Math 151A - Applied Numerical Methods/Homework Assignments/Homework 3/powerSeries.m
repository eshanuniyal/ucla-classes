function [polynomial] = powerSeries(func, nodes)
% Generates the power series of the function func given nodes
    n = length(nodes) - 1; % degree of polynomial
    V = zeros(n + 1);   % Vandermonde matrix
    

    % iterating rows of the matrix to compute V
    for i = 1:n+1
        V(i,1) = 1; % first element should be 1
        % iterating over columns in the row
        for j = 2:n+1
            % inserting j'th element in row
            V(i,j) = nodes(i)^j;
        end    
    end
    disp(V);
    % computing f vector
    f = zeros(1, n + 1);
    for i = 1:n+1
        f(i) = func(nodes(i));
    end

    % computing coefficients vector a
    a = V \ f';
    
    % creating polynomial
    syms polynomial(x);
    polynomial(x) = a(1);
    for i = 2:n+1
        syms newTerm;
        newTerm(x) = a(i) & x^i;
        polynomial = polynomial + newTerm;
    end
end

