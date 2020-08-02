function [root, pns, rootError] = bisection(func, a, b, iterations, actualRoot)
% Function call for exercise 3: bisection(@(x) x^2 - 0.7*x, 0.5, 1, 16, 0.7)
% Function call for exercise 4: bisection(@(x) sqrt(x) - cos(x), 0, 1, 17, 0.641714371)
% Bisection function: find a root of the function func in [a,b]
    % error checking: a >= b
    if (a >= b)
        fprintf("Error: a is not less than b.\n");
        root = nan;
        return;
    end
    % error checking: can't apply intermediate value theorem
    if sign(func(a)) == sign(func(b))
        fprintf("Error: func(a) and func(b) have the same sign, so we can't assume there exists a root in [a,b].");
        root = nan;
        return;
    end
    
    % array to store absolute value of pn's
    pns = zeros(1, iterations);
    
    % iterating "iterations" times
    for iter = 1:iterations
        % updating midpoint
        mid = (a + b) / 2;
        % finding f(mid)
        fMid = func(mid);
        % updating bounds
        if sign(fMid) == sign(func(a))
            a = mid;
        elseif sign(fMid) == sign(func(b))
            b = mid;
        end
        pns(iter) = abs(mid);
    end
    % updating root in final version
    root = (a + b) / 2;
    rootError = abs(root - actualRoot); % final error
    
    % graphing plots
    figure();
    plot(abs(pns - actualRoot));
    title("Absolute error from true root vs. number of iterations");
    xlabel("Iteration number (n)");
    ylabel("Value of |p - p_n)| (for p = " + actualRoot + ")");
    
    % creating array to find |p_n - p_{n-1}| for all n
    diffs = zeros(1, iterations - 1);
    for iter = 1:(iterations - 1)
        diffs(iter) = abs(pns(iter + 1) - pns(iter));
    end
    figure();
    plot(1:(iterations - 1), diffs);
    title("Difference b/w successive midpoints vs. number of iterations");
    xlabel("Iteration number (n)");
    ylabel("Value of |p_n - p_{n-1}|");
        
    figure();
    plot(pns);
    title("Value of function at midpoint vs. number of iterations");
    xlabel("Iteration number (n)");
    ylabel("Value of |f(p_n)|");
    
end