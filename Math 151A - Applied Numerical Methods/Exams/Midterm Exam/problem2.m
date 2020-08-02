function [pN, his] = problem2(f, df, a, b, tol)
    % Newton function
    %   performs newton to find roots of 1D functions
    %
    %   inputs:
    %       f       - function
    %       df      - derivative function
    %       tol     - tolerance
    %   
    %   outputs:
    %       p       - approximate root 
    %       his     - store looping history

    pNm1 = (a + b) / 2; % initialised to p0 (p at N-1 generally)
    newtonHis  = zeros(0, 2); % stores |f(pn)| and |pn - p_(n-1)| at each iteration
    % secantHis = zeros(0, 2);  % stores |f(pn)| and |pn - p_(n-1)| at each iteration
    % modifiedNewtonhis = zeros(0, 2);  % stores |f(pn)| and |pn - p_(n-1)| at each iteration

    % iterating via Newton's Method
    iter = 1;
    while 1
        % newton step
        pN = pNm1 - f(pNm1)/df(pNm1);
        
        % computing checks on pn
        fc = abs(f(pN));    % |f(pn)|
        absErr = abs(pN-pNm1); % |pn - p_(n-1)|

        newtonHis(iter,:) = [fc absErr];
        
        % check stopping tolerance
        if absErr < tol || fc < tol
            break;
        end 
        % updating iter
        pNm1 = pN; iter = iter + 1;
    end
    fprintf("Test");
    his = newtonHis;
   
end

