function [pN, his] = secant(p0,p1,f,tol,maxIter)
% Secant function
%   performs newton to find roots of 1D functions
%
%   inputs:
%       p0,p1   - initial guesses
%       f       - function
%       tol     - tolerance
%       maxIter - maximum number of iterations
%   
%   outputs:
%       p       - approximate root 
%       his     - store looping history
%
%
%   note: f(p0) and f(p1) must have different signs

pNm2 = p0; % p at N-2
pNm1 = p1;
his  = zeros(maxIter,4); % stores iter, pN and f(pN) at each iter

fprintf('\n\n ---- secant ---- \n\n')
fprintf('iter\t\tpN\t\tfc\t\tabsErr\n');

iter = 1;
while iter<=maxIter
    
    % secant step
    fm1 = f(pNm1); fm2 = f(pNm2);
    pN = pNm1 - (fm1*(pNm1-pNm2))/(fm1-fm2);
    
    absErr = abs(pN-pNm1);
    
    fc = f(pN);
    his(iter,:) = [iter pN fc absErr];
    
    % print results
    fprintf('%d\t\t%1.4e\t%1.4e\t%1.4e\n',iter,pN,fc,absErr);
    
    % check stopping tolerance
    if absErr<tol || abs(f(pN))<tol
        his = his(1:iter,:);
        break;
    end 
    
    pNm2 = pNm1; 
    pNm1 = pN; 
    iter = iter+1;
end

