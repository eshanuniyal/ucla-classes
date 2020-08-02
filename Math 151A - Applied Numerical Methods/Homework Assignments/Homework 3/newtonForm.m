function [polynomial] = newtonForm(func, nodes)
% Generates the Newton's form of the function func given nodes
    n = length(nodes) - 1; % degree of polynomial
    L = zeros(n + 1);   % matrix L for Newton's form
    
    L(1, 1) = 1;    % first element in first row should be 1; rest 0's

    % iterating over remaining rows of the matrix to compute L
    for i = 2:n+1
        L(i,1) = 1; % first element should be 1
        % iterating over columns in the row
        for j = 2:i
            % inserting j'th element in row
            L(i,j) = 1;
            % multiplying j'th element by nodes(i) - nodes(k) for all k
            % from 0 to j - 1
            for k = 1:j-1
               L(i,j) = L(i,j) * (nodes(i) - nodes(k));
            end
        end    
    end
    disp(L(:,1));
    disp(L(:, 13);
    
    % computing f vector
    f = zeros(1, n + 1);
    for i = 1:n+1
        f(i) = func(nodes(i));
    end

    % computing coefficients vector a
    a = L \ f';
    
    % creating polynomial
    syms polynomial(x);
    polynomial(x) = a(1);
    for i = 2:n+1
        syms newTerm;
        newTerm(x) = a(i);
        for j = 1:i-1
            syms multiplier;
            multiplier(x) = x - nodes(j);
            newTerm = multiplier*newTerm;
        end
        polynomial = polynomial + newTerm;
    end
end

