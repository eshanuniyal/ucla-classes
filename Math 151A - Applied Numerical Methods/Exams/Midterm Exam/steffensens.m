function [pNhat, his] = steffensens(p0,g,tol,maxIter)
% Steffensen's Accelerated Convergence
%   performs aitken's to find fixed point of function g
%
%   inputs:
%       p0      - initial guess
%       g       - function
%       tol     - tolerance
%       maxIter - maximum number of iterations
%   
%   outputs:
%       p       - approximate root 
%       his     - store looping history

pN      = p0

% stores iter, pNhat, |g(pN)-pN|, |pN - pNm1|, each iter
his  = zeros(maxIter, 4); 

fprintf('\n\n ---- steffensens ---- \n\n')
fprintf('iter\t\tpN\t\t|pN - g(pN)|\tabsErr\n');

iter = 1;
while iter<=maxIter
    pNp1 = g(pN); 
    pNp2 = g(pNp1);
    pNhat   = pN - ((pNp1 - pN)^2)/(pNp2 - 2*pNp1 + pN);
    
    fc      = abs(pNhat - g(pNhat));
    absErr  = abs(pNhat - pNp2);
    
    % print results
    fprintf('%d\t\t%1.4e\t%1.4e\t%1.4e\n',iter,pNhat,fc,absErr);
    
    his(iter,:) = [iter pNhat fc absErr];
    
    % check stopping tolerance
    if absErr<tol || fc<tol
        his = his(1:iter,:);
        break;
    end 
    
    pN = pNhat; 
    iter = iter+1;
    
end
    