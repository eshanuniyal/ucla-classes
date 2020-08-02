function [fixedPoint, pns, fixedPointError] = fixedPointIteration(func, a, b, accuracy, actualFixedPoint)
% Function call for exercise 4: fixedPointIteration(@(x) pi + 0.5*sin(x/2), 0, 2*pi, 10^-4, 3.626942015)
% Fixed point iteration function: find a fixed point of the function func in [a,b]
    % error checking: a >= b
    if (a >= b)
        fprintf("Error: a is not less than b.\n");
        fixedPoint = nan;
        return;
    end
    
    % array to store absolute value of pn's
    pns = zeros(0);
    
    % starting with p_0 = (a+b)/2
    pCurrent = (a+b)/2;
    iter = 1;
    pns(iter) = pCurrent;
    
    % iterating until we reach desired accuracy 
        % on |g(p_n)-p_n| or |p_n - p_{n-1}|
    while 1
        % updating p and inserting into pns
        pNew = func(pCurrent);
        iter = iter + 1;
        pns(iter) = pNew;
        % checking whether we've reached desired accuracy
        if abs(func(pNew) - pNew) < accuracy || abs(pNew - pCurrent) < accuracy
            pCurrent = pNew;
            break % out of while loop
        end
        % update pCurrent
        pCurrent = pNew;
    end
    
    fixedPointError = abs(pCurrent - actualFixedPoint); % final error
    fixedPoint = pCurrent;
    
    % graphing plots
    figure();
    plot(abs(pns - func(pns)));
    title("Difference between g(p_n), p_n vs. number of iterations");
    xlabel("Iteration number (n)");
    ylabel("Value of |g(p_n) - p_n|");
    curtick = get(gca, 'xTick');
    xticks(unique(round(curtick)));
    
    % creating array to find |p_n - p_{n-1}| for all n
    diffs = zeros(0);
    for iter = 1:(iter - 1)
        diffs(iter) = abs(pns(iter + 1) - pns(iter));
    end
    figure();
    plot(1:(iter), diffs);
    title("Difference b/w consecutive fixed point candidates vs. number of iterations");
    xlabel("Iteration number (n)");
    ylabel("Value of |p_n - p_{n-1}|");
    curtick = get(gca, 'xTick');
    xticks(unique(round(curtick)));    
    
    figure();
    plot(abs(pns - actualFixedPoint));
    title("Difference between fixed point candidate and solution vs. number of iterations");
    xlabel("Iteration number (n)");
    ylabel("Value of |p_n - p|");
    curtick = get(gca, 'xTick');
    xticks(unique(round(curtick)));
end