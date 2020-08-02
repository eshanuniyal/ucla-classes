function [pN, his] = newton(p0,f,df,tol,maxIter)
% Newton function
%   performs newton to find roots of 1D functions
%
%   inputs:
%       p0      - initial guess
%       f       - function
%       df      - derivative function
%       tol     - tolerance
%       maxIter - maximum number of iterations
%   
%   outputs:
%       p       - approximate root 
%       his     - store looping history
%
%

pNm1 = p0; % p at N-1 
his  = zeros(maxIter,4); % stores iter, pN, f(pN), and relerr at each iter

fprintf('\n\n ---- newton ---- \n\n')
fprintf('iter\t\tpN\t\tfc\t\tabsErr\n');

iter = 1;
while iter<=maxIter
    
    % newton step
    pN = pNm1 - f(pNm1)/df(pNm1);
    
    fc = f(pN); dfc = df(pN);
    
    absErr = abs(pN-pNm1);
    
    his(iter,:) = [iter pN fc absErr];
    
    
    % print results
    fprintf('%d\t\t%1.4e\t%1.4e\t%1.4e\n',iter,pN,fc,absErr);
    
    % check stopping tolerance
    if absErr<tol || abs(f(pN))<tol
        his = his(1:iter,:);
        break;
    end 
    
    pNm1 = pN; iter = iter+1;
end

