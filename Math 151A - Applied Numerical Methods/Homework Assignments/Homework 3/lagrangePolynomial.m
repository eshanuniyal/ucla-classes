function [polynomial] = lagrangePolynomial(xs, fs)
% Generates the Lagrange polynomial of the function func given nodes

    n = length(xs) - 1; % degree of polynomial
    syms Ln [1 n+1];    % array (or row vector) for the Lagrange basis  
    
    %computing lagrange basis
    for i = 1:n+1
        syms Lni(x);    % symbolic function L_{n,i}
        Lni(x) = 1;     % initialising symbolic function to 1
        % iterating for each term in numerator and denominator
        for j = 1:n+1
            % we skip terms with xs(i) in numerator and denominator
            if i ~= j      
                % computing multiplier (numerator term / denominator term)
                syms multiplier(x);
                multiplier(x) = (x - xs(j)) / (xs(i) - xs(j));
                % updating Lni
                Lni(x) = Lni * multiplier;
            end
        end
        % inserting Lni in array
        Ln(i) = Lni;
    end

    % computing polynomial from Lagrange basis
    polynomial = Ln * fs';
end

