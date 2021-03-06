function [] = exercise2(func, a, b, nValues)
% function to create graphs for exercise 3 given interval [a,b] and degree
% n of the Lagrange interpolating polynomial of func
% command for exercise 2: exercise2(@(x) 1/(1+x^2), -5, 5, [5 10 25 50])

    polynomials = zeros(length(nValues), 3);  % a matrix that stores the 
        % Newton's form polynomials generated by each value of n in the corresponding column
        % first element in each column is the value of n, second element is the
        % polynomial generated with equally spaced nodes, and the third element
        % in each column is the polynomial generated with Chebyshev nodes

    % converting func to a symbolic function
    sym(func);
    xTicks = -5:1:5;    % x-axis ticks for graphs

    % iterating over nValues ( = [5, 10, 25, 50] in exercise 3)
    for n = nValues
        disp(n);
        
        % computing equally spaced and Chebyshev nodes
        equal_xs = nodes(a, b, n, 'equally spaced');
        equal_fs = arrayfun(func, equal_xs);
        % computing function values for equally spaced and Chebyshev nodes
        chebyshev_xs = nodes(a, b, n, 'chebyshev');
        chebyshev_fs = arrayfun(func, chebyshev_xs);

        % computing Lagrange polynomial for equally spaced nodes
        equalPolynomial = lagrangePolynomial(equal_xs, equal_fs);
        disp(equalPolynomial);
        % computing Lagrange polynomial for Chebyshev nodes
        chebyshevPolynomial = lagrangePolynomial(chebyshev_xs, chebyshev_fs);
        disp(chebyshevPolynomial);
        
        % graphing figures in 2*2 layout
        figure(n);
        t = tiledlayout(2,2);
        
        % graphing func, equalPolynomial
        equalPlot = nexttile;
        fplot(equalPlot, points, [funcPoints' equalPPoints']);
        title(equalPlot, "f(x) and p_n(x) for " + n + " equally spaced nodes");
        xticks(xTicks);
        % graphing func, chebyshevPolynomial
        chebyshevPlot = nexttile;
        plot(chebyshevPlot, points, [funcPoints' chebyshevPPoints']);
        title(chebyshevPlot, "f(x) and p_n(x) for " + n + " Chebyshev nodes");
        xticks(xTicks);
        
        
        % graphing absolute error for equalPolynomial
        equalError = nexttile;
        plot(equalError, points, abs(funcPoints - equalPPoints));
        title(equalError, "Absolute error |e_n|(x) for " + n + " equally spaced nodes");
        xticks(xTicks);
        % graphing absolute error for chebyshevPolynomial
        chebyshevError = nexttile;
        fplot(chebyshevError, points, abs(funcPoints - chebyshevPPoints));
        title(chebyshevError, "Absolute error |e_n|(x) for " + n + " Chebyshev nodes");
        xticks(xTicks);
        
        % decreasing spacing between plots
        t.Padding = 'none';
    end


end

